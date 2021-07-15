#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <map>
#include <string.h>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
using namespace std;
std::map< string, vector<string> > result;


int getFiles(const char* dir, FILE* fd){
	DIR* dirp = NULL;
	struct dirent *ptr;
	struct stat statbuf;
	char path[512] = {0};
	dirp = opendir(dir);
	if (dirp == NULL){
		return -1;
	}
	
	bool isroot = (strcmp("/", dir) == 0);
	while(NULL != (ptr = readdir(dirp))) {
		sprintf(path, "%s/%s" , (isroot ? "" : (dir)), ptr->d_name);
		if (lstat(path, &statbuf) < 0){
			printf("%s error !!\n", path);
			continue;
		}
		if (S_ISDIR(statbuf.st_mode)){
			if (strcmp(".", ptr->d_name) == 0 || strcmp("..", ptr->d_name) == 0) continue;
			getFiles(path, fd);
		}
		else{
			fprintf(fd, "%s|%s\n", ptr->d_name, path);
			result[ptr->d_name].push_back(path);
		}
	}
	
	return 0;
}
int main(int arg, char** argc)
{
	FILE* fd_w;
	FILE* fd = fopen("./result.txt", "w");
	if (fd == NULL){
		printf("open file error\n");
		return -1;
	}
	
	getFiles("/home/gateway/Desktop/manufacture/rootfs_nogpu" ,fd);
	fclose(fd);
	
	fd = fopen("./source.txt", "r");
	fd_w = fopen("./txt.txt", "w");
	if (fd == NULL || fd_w == NULL){
		printf("open file error\n");
		return -1;
	}
	
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	
	while ((read = getline(&line, &len, fd)) != -1) {
	   printf("Retrieved line of length %zu :\n", read);
	   printf("--%s", line);
	   char* p = line;
	   while(*p != 0){
		   printf("%c", *p);
		   ++p;
		   if (*p == '\r' || *p == '\n'){
			   *p = 0;
			   break;
		   }
	   }
	   printf("\n");
	   string key = line;
	   auto item = result.find(key);
	   if (item != result.end()){
		   cout << "find " << key << endl;
		   for (auto vctit = item->second.begin() ; vctit != item->second.end() ; ++vctit)
			fprintf(fd_w, "%s | %s\n", item->first.c_str(), vctit->c_str());
	   }
	}

	free(line);
	fclose(fd);
	fclose(fd_w);
	return 0;
}
