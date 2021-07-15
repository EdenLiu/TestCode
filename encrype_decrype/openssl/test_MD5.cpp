#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "openssl/md5.h"
#include "openssl/sha.h"

using namespace std;

string MD5(char* data ,size_t lenght){
	string hash;
	MD5_CTX ctx;
	unsigned char md[16];
	char tmp[3] = { };
	
	MD5_Init(&ctx);
	size_t time = lenght / 1024;
	size_t rematin = lenght % 1024;
	size_t index = 0;
	while(time--){
		MD5_Update(&ctx, (const unsigned char*) (data + index*1024), 1024);
		index++;
	}
	if (rematin > 0){
		MD5_Update(&ctx, (const unsigned char*) (data + index*1024), rematin);
	}
	MD5_Final(md, &ctx);
	for (int i = 0; i < 16; i++) {
		sprintf(tmp, "%02X", md[i]);
		hash.append(tmp);
	}
	
	printf("MD5hash=%s\n", hash.c_str());
	return hash;
}

string MD5One(char* data ,size_t lenght){
	string hash;
	MD5_CTX ctx;
	unsigned char md[16];
	char tmp[3] = { };
	
	MD5_Init(&ctx);
	MD5_Update(&ctx, (const unsigned char*) data, lenght);
	MD5_Final(md, &ctx);
	for (int i = 0; i < 16; i++) {
		sprintf(tmp, "%02X", md[i]);
		hash.append(tmp);
	}
	
	printf("MD5hash=%s\n", hash.c_str());
	return hash;
}

string TEST_SHA256(char* data ,size_t lenght){
	string hash;
	SHA256_CTX ctx;
	unsigned char sha[32];
	char tmp[3] = { };
	
	SHA256_Init(&ctx);
	size_t time = lenght / 1024;
	size_t rematin = lenght % 1024;
	size_t index = 0;
	while(time--){
		SHA256_Update(&ctx, (const unsigned char*) (data + index*1024), 1024);
		index++;
	}
	if (rematin > 0){
		SHA256_Update(&ctx, (const unsigned char*) (data + index*1024), rematin);
	}
	SHA256_Final(sha, &ctx);
	for (int i = 0; i < 32; i++) {
		sprintf(tmp, "%02X", sha[i]);
		hash.append(tmp);
	}
	
	printf("SHA256hash=%s\n", hash.c_str());
	return hash;
}

string TEST_SHA256_One(char* data ,size_t lenght){
	string hash;
	SHA256_CTX ctx;
	unsigned char sha[32];
	char tmp[3] = { };
	
	SHA256_Init(&ctx);
	SHA256_Update(&ctx, (const unsigned char*) data, lenght);
	SHA256_Final(sha, &ctx);
	for (int i = 0; i < 32; i++) {
		sprintf(tmp, "%02X", sha[i]);
		hash.append(tmp);
	}
	
	printf("SHA256hash=%s\n", hash.c_str());
	return hash;
}

int main(){
	#define ARRAY_SIZE 10000
	char data[ARRAY_SIZE];
	for (int i = 0 ; i < ARRAY_SIZE; ++i){
		data[i] = i % 254;
	}
	
	MD5(data, ARRAY_SIZE);
	MD5One(data, ARRAY_SIZE);
	TEST_SHA256(data, ARRAY_SIZE);
	TEST_SHA256_One(data, ARRAY_SIZE);
}