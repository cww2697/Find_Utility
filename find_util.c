#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

void find_args(const char *path, int nflag, const char* name, int iflag, int inode_num int mflag, int mins, int rflag, int eflag);
void find(const char *path);

int main(int argc, char **argv)
{
    char *dir, *name;
    int inode_num, mins, nflag, iflag, mflag, rflag, eflag;
    dir = argv[1];
    
    if(argc <2){
	    dir=".";
    }
    else{
	    dir=argv[1];	
    }
    finds(dir);

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
    if (nflag == 1){}
    if (iflag == 1){}
    if (mflag == 1){}
    if (rflag == 1){}
    if (eflag == 1){}
    else{
        break;  //Exception handling, since if all these are false code should not direct to this find function
    }



}
