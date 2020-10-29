#include <stdio.h>
#include <dirent.h>

int listdir(const char *path) {
	struct dirent *dir_entry;
	DIR *dir_ptr;

	dir_ptr = opendir(path);
	if (dir_ptr == NULL ) {
		perror("opendir");
		return -1;
	}

	int ctr = 0;
	while((dir_entry = readdir(dir_ptr))) {
		printf("%d. Name : %s\n", ctr++, dir_entry->d_name);
		printf("Type : %d\n", dir_entry->d_type);
	}

	closedir(dir_ptr);
	return 0;
}

int main(int argc, char **argv) {
	
	if (argc == 1){
		listdir(".");
	} else if (argc >= 2) {
		 // For now..I'll just go ahead and ignore more than one paths :p
		 listdir(argv[1]);
	}

	return 0;
}
