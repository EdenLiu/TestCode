#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "openssl/md5.h"
#include "openssl/evp.h"
#include <string.h>

using namespace std;
#define ARRAY_SIZE 2048
#define BLOCK_SIZE 16
string EVP_encrypt(char* data ,size_t lenght){
	FILE* fd;
	int ret;
	unsigned char key[32] = {1};
	unsigned char iv[16] = {0};
	EVP_CIPHER_CTX*  ctx;
	ctx = EVP_CIPHER_CTX_new();
	int isEncrypt = 1;//1:encrypt, 0:decrypt
	unsigned char outdata[1024 + 16] = {0};
	int outsize, outsum = 0;
	size_t time = lenght / 1024;
	size_t rematin = lenght % 1024;
	size_t index = 0;
	
	printf("time=%d rematin=%d \n", time, rematin);
	ret = EVP_CipherInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv, 1);
	fd = fopen("./encrypt.txt", "w");
	if (fd == NULL){
		printf("OPEN encrypt FIALED\n");
		return "";
	}
	
	int finalsize;
	while(time--){
		ret = EVP_CipherUpdate(ctx, outdata, &outsize, (const unsigned char*)(data + index*1024), 1024);
		outdata[outsize] = 0;
		outsum += outsize;
		index++;
		fwrite(outdata, 1, outsize, fd);
		printf("outsize=%d outsum=%d\n", outsize, outsum);
	}
	
	if (rematin > 0){
		ret = EVP_CipherUpdate(ctx, outdata, &outsize, (const unsigned char*)(data + index*1024), rematin);
		ret = EVP_CipherFinal_ex(ctx, outdata+outsize, &finalsize);
		outsum += outsize;
		outsum += finalsize;
		fwrite(outdata, 1, outsize + finalsize, fd);
		printf("outsize=%d finalsize=%d outsum=%d\n", outsize, finalsize, outsum);
	}
	else{
		ret = EVP_CipherFinal_ex(ctx, outdata+outsize, &finalsize);
		printf("ret2 = %d\n",ret);
		outsum += finalsize;
		fwrite(outdata+outsize, 1, finalsize, fd);
		printf("finalsize=%d outsum=%d\n", finalsize, outsum);
	}
	printf("finish encrypt\n\n");
	fclose(fd);
	return "";
}

string EVP_decrypt_one(char* data ,size_t lenght){
	FILE* fd;
	unsigned char key[32] = {1};
	unsigned char iv[16] = {0};
	EVP_CIPHER_CTX*  ctx;
	ctx = EVP_CIPHER_CTX_new();
	int isEncrypt = 1;//1:encrypt, 0:decrypt
	unsigned char outdata[lenght] = {0};
	int outsize, outsum = 0;
	
	EVP_CipherInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv, 0);
	fd = fopen("./decrypt.txt", "w");
	if (fd == NULL){
		printf("OPEN decrypt FIALED\n");
		return "";
	}
	
	EVP_CipherUpdate(ctx, outdata, &outsize, (const unsigned char*)(data), lenght);
	int finalsize;
	outsum += outsize;
	EVP_CipherFinal(ctx, outdata+outsum, &finalsize);
	outsum += finalsize;
	fwrite(outdata, 1, outsum, fd);
	printf("one outsize=%d outsum=%d finalsize=%d\ndata=%s \n", outsize, outsum, finalsize, outdata);
	fclose(fd);
	return "";

}

string EVP_decrypt_loop(char* data ,size_t lenght){
	FILE* fd;
	const int blocksize = BLOCK_SIZE;
	unsigned char key[32] = {1};
	unsigned char iv[16] = {0};
	EVP_CIPHER_CTX*  ctx;
	ctx = EVP_CIPHER_CTX_new();
	int isEncrypt = 1;//1:encrypt, 0:decrypt
	unsigned char outdata[blocksize + 16] = {0};
	int outsum = 0;
	size_t time = lenght / blocksize;
	size_t rematin = lenght % blocksize;
	size_t index = 0;
	printf("time=%d rematin=%d \n", time, rematin);
	
	fd = fopen("./decrypt.txt", "w");
	if (fd == NULL){
		printf("OPEN decrypt FIALED\n");
		return "";
	}
	
	int ret,outsize,finalsize, tmp;
	ret = EVP_CipherInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv, 0);
	
	unsigned char outdata1[lenght] = {0};
	memset(outdata1, 0, lenght);
	while(time--){
		int finalsize;
		memset(outdata, 0, blocksize + 16);
		ret = EVP_CipherUpdate(ctx, outdata, &outsize, (const unsigned char*)(data + index*blocksize), blocksize);
		tmp = outsum;
		outsum += outsize;
		index++;
		fwrite(outdata, 1, outsize , fd);
		printf("outsize=%d outsum=%d blocksize=%d outdata=%s\n", outsize, outsum, blocksize, outdata);
		memcpy(outdata1 + tmp, outdata, outsum - tmp);
	}
	
	if (rematin > 0){
		
		memset(outdata, 0, blocksize + 16);
		ret = EVP_CipherUpdate(ctx, outdata, &outsize, (const unsigned char*)(data + index*blocksize), rematin);
		int tmp = outsum;
		outsum += outsize;
		ret = EVP_CipherFinal_ex(ctx, outdata+outsize, &finalsize);
		outsum += finalsize;
		index++;
		fwrite(outdata, 1, outsize + finalsize, fd);
		printf("outsize=%d outsum=%d finalsize=%d blocksize=%d outdata=%s\n", outsize, outsum, finalsize, blocksize, outdata);
		memcpy(outdata1 + tmp, outdata, outsum - tmp);
	}
	else{
		memset(outdata, 0, blocksize + 16);
		ret = EVP_CipherFinal_ex(ctx, outdata + outsize, &finalsize);
		tmp = outsum;
		outsum += finalsize;
		fwrite(outdata+outsize, 1, finalsize, fd);
		printf("outsize=%d outsum=%d finalsize=%d blocksize=%d outdata=%s\n", outsize, outsum, finalsize, blocksize, outdata + outsize);
		memcpy(outdata1 + tmp, outdata, outsum - tmp);
	}
	printf("loop data=%s\n", outdata1);
	fclose(fd);
	return "";

}

int main(){
	
	char data[ARRAY_SIZE];
	char dataw[ARRAY_SIZE + 32];
	size_t n;
	for (int i = 0 ; i < ARRAY_SIZE; ++i){
		data[i] = (i % 10) + 0x30;
	}
	data[ARRAY_SIZE - 1] = 0;
	printf("arraysize=%d block_size=%d data=%s\n", ARRAY_SIZE, BLOCK_SIZE, data);
	EVP_encrypt(data, ARRAY_SIZE);
	FILE* fd = fopen("./encrypt.txt", "r");
	if (fd == NULL){
		printf("OPEN decrypt FIALED\n");
		return 0;
	}
	
	n = fread(dataw, 1, ARRAY_SIZE + 32, fd);
	printf("n=%d\n", n);
	fclose(fd);
	//EVP_decrypt_one(dataw, n);
	EVP_decrypt_loop(dataw, n);
}