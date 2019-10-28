#include <stdio.h>
#include <errno.h>
#include "macros.h"

char * 
updateGitInfo(const char * patchDir, 
			  const char * repoDir) 
{
	
}

int 
main(int argc, 
     char const *argv[]) 
{
	switch (argc) {
		case 3:
			const char * repoDir = argv[1];
			const char * patchDir = argv[2];
			char * updatedResult = updateGitInfo(repoDir, 
							     				 patchDir);
			printf("%s", updatedResult);
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
