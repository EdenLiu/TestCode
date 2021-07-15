#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "openssl/evp.h"
#include <string.h>

using namespace std;
#define ARRAY_SIZE 2049
#define BLOCK_SIZE 64*4
string EVP_encryptBase64(char* data ,size_t lenght){
	FILE* fd;
	int ret;
	unsigned char outdata[lenght*2] = {0};
	//memset(outdata, 0 , lenght*2);
	
	fd = fopen("./encrypt.txt", "w");
	if (fd == NULL){
		printf("OPEN encrypt FIALED\n");
		return "";
	}
	ret = EVP_EncodeBlock(outdata, (unsigned char*)data, lenght);
	fwrite(outdata, 1, ret, fd);
	printf("ret = %d lenght=%d outdata=%s\n", ret, lenght, outdata);
	printf("finish base64 encrypt\n\n");
	fclose(fd);
	return "";
}

string EVP_decryptBase64_one(char* data ,size_t lenght){
	FILE* fd;
	int ret;
	fd = fopen("./decrypt.txt", "w");
	if (fd == NULL){
		printf("OPEN decrypt FIALED\n");
		return "";
	}
	
	unsigned char outdata[lenght];
	ret = EVP_DecodeBlock(outdata, (unsigned char*)data, lenght);
	printf("ret = %d lenght=%d \noutdata=%s\n", ret, lenght, outdata);
	printf("finish base64 decrypt\n\n");
	fclose(fd);
	return "";

}

string EVP_decryptBase64_loop(char* data ,size_t lenght){
	FILE* fd;
	int ret;
	int time = 0, rematin = 0, index=0 ,tmp = 0, sum = 0;
	char dataw[ARRAY_SIZE];
	fd = fopen("./decrypt.txt", "w");
	if (fd == NULL){
		printf("OPEN decrypt FIALED\n");
		return "";
	}
	
	time = lenght / BLOCK_SIZE;
	rematin = lenght % BLOCK_SIZE;
	unsigned char outdata[BLOCK_SIZE*3/4 + 4];
	
	printf("time=%d rematin=%d\n" ,time ,rematin);
	while(time--){
		ret = EVP_DecodeBlock(outdata, (unsigned char*)(data + index*BLOCK_SIZE), BLOCK_SIZE);
		printf("ret = %d, outdata = %s\n", ret, outdata);
		index++;
		tmp = sum;
		sum += ret;
		fwrite(outdata, 1 ,ret ,fd);
		memcpy(dataw + tmp, outdata, ret);
	}
	
	if (rematin > 0){
		ret = EVP_DecodeBlock(outdata, (unsigned char*)(data + index*BLOCK_SIZE), rematin);
		printf("ret = %d, outdata = %s\n", ret, outdata);
		index++;
		tmp = sum;
		sum += ret;
		fwrite(outdata, 1 ,ret ,fd);
		memcpy(dataw + tmp, outdata, ret);
	}
	
	
	printf("loop data=%s\n", dataw);
	fclose(fd);
	return "";

}

int main(){
	
	char data[ARRAY_SIZE];
	char dataw[ARRAY_SIZE*4/3 + 3];
	size_t n;
	for (int i = 0 ; i < ARRAY_SIZE; ++i){
		data[i] = (i % 10) + 0x30;
	}
	data[ARRAY_SIZE - 1] = 0;
	printf("arraysize=%d block_size=%d data=%s\n", ARRAY_SIZE, BLOCK_SIZE, data);
	EVP_encryptBase64(data, ARRAY_SIZE);
	FILE* fd = fopen("./encrypt.txt", "r");
	if (fd == NULL){
		printf("OPEN decrypt FIALED\n");
		return 0;
	}
	
	n = fread(dataw, 1, ARRAY_SIZE*4/3 + 3, fd);
	printf("n=%d (ARRAY_SIZE*4/3 + 3) =%d\n", n, ARRAY_SIZE*4/3 + 3);
	fclose(fd);
	EVP_decryptBase64_one(dataw, n);
	EVP_decryptBase64_loop(dataw, n);
}