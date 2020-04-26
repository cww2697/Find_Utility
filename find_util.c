#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

void find_args(const char *path, int nflag, const char* name, int iflag, int inode_num int mflag, int mins, int rflag, int eflag);
void find(const char *path);

int main(int argc, char **argv)
{
    char *dir, *name;
    int inode_num, mins, nflag, iflag, mflag, rflag, eflag;
    dir = argv[1];
    if (argc <3){
        if(argc <2){
	        dir=".";
        }
        else{
	        dir=argv[1];	
        }
    }
        find(dir);
    }
    else{
        /*code for switch*/
    }
    
    return 0;
}


/**
 * Lists all files and sub-directories at given path.
 */
void find(const char *basePath)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    // Unable to open directory stream
    if (!dir){
        return;
    }

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            //printf("%s\n", dp->d_name);
            //printf("%s\n", path);
            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
            printf("%s\n", path);   
            
            listFiles(path);
            
        }
    }

    closedir(dir);
}

void find_args(const char* path, int nflag, const char* name, int iflag, int inode_num, int mflag, int mins int rflag){
    
    /*Checks all flags to see which flag is used and runs the proper code for
    the corresponding flag i.e. iflag == 1, find file with inode_num == inode*/

    if (nflag == 1){
        /*statement*/
    }
    else{
        if (iflag == 1){
            /*statement*/
        }
        else{
            if (mflag == 1){
                /*statement*/
            }
            else{
                if (rflag == 1){
                    /*statement*/
                }
                else{
                    if (eflag == 1){
                        /*statement*/
                    }
                    else{
                        /*Exception handling, since if all these are false code should not 
                        direct to this find function*/
                        break;
                    }
                } 
            }
        }
    }
}
