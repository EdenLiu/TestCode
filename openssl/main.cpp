#include <stdio.h>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/engine.h>
#include <string>
#include <memory>

using namespace std;

# define B_FORMAT_TEXT   0x8000
# define FORMAT_UNDEF    0
# define FORMAT_TEXT    (1 | B_FORMAT_TEXT)     /* Generic text */
# define FORMAT_BINARY   2                      /* Generic binary */
# define FORMAT_BASE64  (3 | B_FORMAT_TEXT)     /* Base64 */
# define FORMAT_ASN1     4                      /* ASN.1/DER */
# define FORMAT_PEM     (5 | B_FORMAT_TEXT)
# define FORMAT_PKCS12   6
# define FORMAT_SMIME   (7 | B_FORMAT_TEXT)
# define FORMAT_ENGINE   8                      /* Not really a file format */
# define FORMAT_PEMRSA  (9 | B_FORMAT_TEXT)     /* PEM RSAPubicKey format */
# define FORMAT_ASN1RSA  10                     /* DER RSAPubicKey format */
# define FORMAT_MSBLOB   11                     /* MS Key blob format */
# define FORMAT_PVK      12                     /* MS PVK file format */
# define FORMAT_HTTP     13                     /* Download using HTTP */
# define FORMAT_NSS      14                     /* NSS keylog format */

unsigned char* readFile(const string& filepath, const string& pattern, size_t& len){
	FILE* fd;
	bool ret = false;
	unsigned char* data = NULL;

	fd = fopen(filepath.c_str(), pattern.c_str());
	if (fd == NULL){
		//DEBUG(Debug::WARN, "open filepath :" + filepath + "failed");
		return NULL;
	}

	fseek(fd, 0L, SEEK_END);
	len = ftell(fd);
	fseek(fd, 0L, SEEK_SET);
	data = new unsigned char[len];
	len = fread(data, 1, len ,fd);
	fclose(fd);
	return data;
}

void signText(){
    #define PRIVATEKEYPATH "/home/gateway/Eden/Test/openssl/rsa_key.private"
    EVP_MD_CTX *mdctx = NULL;
    int ret = 0;
    unsigned char *sig = NULL;
    size_t slen, len ,len1;
    FILE* fd;
    const char *msg = (const char*)readFile("/home/gateway/Eden/Test/openssl/config", "r", len);

    std::unique_ptr<BIO, decltype(&BIO_free_all)> keybio(BIO_new_file(PRIVATEKEYPATH, "r"), BIO_free_all);
	std::unique_ptr<EVP_PKEY, decltype(&EVP_PKEY_free)> keyevp(PEM_read_bio_PrivateKey(keybio.get(), NULL,
								NULL,
								/*&cb_data*/ NULL), EVP_PKEY_free);
    size_t siglen = EVP_PKEY_size(keyevp.get());
	cout << "siglen =" << siglen <<  endl;
    /* Create the Message Digest Context */
    if(!(mdctx = EVP_MD_CTX_create())) goto err;
    ret = 1;
    /* Initialise the DigestSign operation - SHA-256 has been selected as the message digest function in this example */
    if(1 != EVP_DigestSignInit(mdctx, NULL, EVP_sha256(), NULL, keyevp.get())) goto err;
    ret = 2;
    /* Call update with the message */
    if(1 != EVP_DigestSignUpdate(mdctx, msg, len)) goto err;
    ret = 3;
    /* Finalise the DigestSign operation */
    /* First call EVP_DigestSignFinal with a NULL sig parameter to obtain the length of the
    * signature. Length is returned in slen */
    if(1 != EVP_DigestSignFinal(mdctx, NULL, &slen)) goto err;
    ++ret;
    /* Allocate memory for the signature based on size in slen */
    if(!(sig = (unsigned char*)OPENSSL_malloc(sizeof(unsigned char) * slen))) goto err;
    ++ret;
    /* Obtain the signature */
    if(1 != EVP_DigestSignFinal(mdctx, sig, &slen)) goto err;
    ++ret;
    /* Success */

    {
        FILE* fd;
        fd = fopen("/home/gateway/Eden/Test/openssl/sgn2.sign", "w");
        if (fd == NULL){
            //DEBUG(Debug::WARN, "open filepath :" + filepath + "failed");
            cout << "open file failed" << endl;
            return ;
        }

        fwrite(sig, slen, 1 ,fd) > 0;
        fclose(fd);
    }

    err:
    if(ret != 6)
    {
        cout << "ret=" << ret <<  endl;
    /* Do some error handling */
    }
    
    /* Clean up */
    if(sig && !ret) OPENSSL_free(sig);
    if(mdctx) EVP_MD_CTX_destroy(mdctx);
}

bool VerifySign(){
#define PUBLICKEYPATH "/home/gateway/Eden/Test/openssl/rsa_key.public"
	size_t siglen, len ;
	int r;
	const char *msg = (const char*)readFile("/home/gateway/Eden/Test/openssl/config", "r", len);
	unsigned char *sig = NULL;

	std::unique_ptr<BIO, decltype(&BIO_free_all)> bmd(BIO_new(BIO_f_md()), BIO_free_all);
	std::unique_ptr<BIO, decltype(&BIO_free_all)> keybio(BIO_new_file(PUBLICKEYPATH, "r"), BIO_free_all);
	std::unique_ptr<EVP_PKEY, decltype(&EVP_PKEY_free)> keyevp(PEM_read_bio_PUBKEY(keybio.get(), NULL,
								NULL,
								/*&cb_data*/ NULL), EVP_PKEY_free);
	std::unique_ptr<BIO, decltype(&BIO_free_all)> sigbio(BIO_new_file("/home/gateway/Eden/Test/openssl/sgn2.sign", "rb"), BIO_free_all);
	siglen = EVP_PKEY_size(keyevp.get());

	if(1 != EVP_DigestSignInit(mdctx.get(), NULL, EVP_sha256(), NULL, keyevp.get())){
		//DEBUG(Debug::WARN, "Error EVP_DigestSignInit\n");
		return false;
	}

	if(1 != EVP_DigestVerifyUpdate(mdctx.get(), msg, len)){
		//DEBUG(Debug::WARN, "Error EVP_DigestSignUpdate\n");
		return false;
	}

    sig = (unsigned char *)OPENSSL_malloc(siglen);
	siglen = BIO_read(sigbio.get(), sig, siglen);
    r=EVP_DigestVerifyFinal(mdctx.get(), sig, siglen);
    OPENSSL_free(sig);
	if(1 == r){
		DEBUG(Debug::NOTICE, "VerifySign true\n");
        
		return true;
	}
	else{
		DEBUG(Debug::WARN, "VerifySign false\n");
		return false;
	}
}

int main(){
    signText();
    VerifySign();
}