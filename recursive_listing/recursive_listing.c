#include <stdio.h>
#include <dirent.h>
#include <string.h>

void modified_print(const char *value, int counter) {
	printf("\n");
	for(int i=0;i<counter;i++) {
		printf(" ");
	}
	printf("|");
	for( int i=0;i<counter;i++) {
		printf("-");
	}
	printf("%s", value);
}

int listdir(const char *path, int depth) {
	struct dirent *dir_entry;
	DIR *dir_ptr;

	dir_ptr = opendir(path);
	if ( dir_ptr == NULL ) {
		perror("opendir");
		return -1;
	}

	while((dir_entry = readdir(dir_ptr))){
		if (dir_entry->d_type == 8){
			modified_print(dir_entry->d_name, depth);
		} else if(dir_entry->d_type == 4){
			if ( !strcmp(dir_entry->d_name, ".") || !strcmp(dir_entry->d_name, "..")) {
				continue;
			}
			modified_print(dir_entry->d_name, depth);
			char full_path[4096] = {"\0"};
			sprintf(full_path, "%s/%s", path, dir_entry->d_name);
			listdir(full_path, depth+1);
		}
	}

	closedir(dir_ptr);
	return 0;
}

int main(int argc, char **argv) {
	if (argc == 1) {
		listdir(".", 0);
	} else {
		listdir(argv[1], 0);
	}
	printf("\n");

	return 0;
}
