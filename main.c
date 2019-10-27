#include <stdio.h>
#include <errno.h>

int main(int argc, char const *argv[]) {
	switch (argc) {
		case 3:

			break;
		default:
			if (argc <= 3) {
				printf("Too few arguments\n");
			} else {
				printf("Too many arguments\n");
			}
			printf("usage: main <git-repo dir> <patch-file dir>\n");
	}
	return 0;
}