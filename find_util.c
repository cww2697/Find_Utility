#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>


void find(const char *path, int n, const char *name, int m, int mmin, int i, const char *inum);

int main(int argc, char **argv)
{
    // Directory path to list files
   /* char *dir;
    dir = argv[1];
    
    if(argc <2){
	    dir=".";
    }
    else{
	    dir=argv[1];	
    }
    find(dir);*/

    int		w, n, m, i, a, mmin;
	char  *where, *name, *mmin_string, *inum, *action;
	while (1) {
		char		c;

	

		c = getopt(argc, argv, "w:n:m:i:a:");	

		if (c == -1) {
			break;
		}
		switch (c) {
		case 'w':
			w = 1;
			where = optarg;
			//printf("where: %s\n", optarg);
			break;
		case 'n':
			n = 1;
			name = optarg;
			//printf("name: %s\n", optarg);
			break;
		case 'm':
			m = 1;
			mmin_string = optarg;
			mmin = atoi(mmin_string);
			//printf("mmin: %d\n", mmin);
			break;
		case 'i':
			i = 1;
			inum = optarg;
			//printf("inum: %s\n", optarg);
			break;
		case 'a':
			a = 1;
			action = optarg;
			//printf("action: %s\n", optarg);
			break;
		case '?':
		default:
			printf("An invalid option detected.\n");
		}
	}

    if(w==0){
		where = ".";
	}

    find(where, n , name, m, mmin);

    return 0;
}


/**
 * Lists all files and sub-directories at given path.
 */
void find(const char *basePath, int n, const char *name)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    //printf("%d %s\n", n ,name);
    
    
    // Unable to open directory stream
    if (!dir){
        return;
    }

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            if(n==1){
                if(strcmp(dp->d_name, name) == 0){
                    if(m==1){

                    }
                    else{

                    }
                    strcpy(path, basePath);
                    strcat(path, "/");
                    strcat(path, dp->d_name);
                    //printf("file name: %s\n", dp->d_name);
                    //printf("Original path: %s\n", path); 
                    printf("%s\n", path);   
            
                }
            }
            else{
                if(m==1){
                    
                }
                 else{
                        
                }
                //printf("file name: %s\n", dp->d_name);
                //printf("Original path: %s\n", path); 
                strcpy(path, basePath);
                strcat(path, "/");
                strcat(path, dp->d_name);
                printf("%s\n", path);   
            
            }

            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
            find(path, n, name);
            //printf("%s\n", dp->d_name);
            //printf("%s\n", path);
            // Construct new path from our base path
            
            
        }
    }

    closedir(dir);
}
