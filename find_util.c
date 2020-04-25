#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>


void listFiles(const char *path);

int main(int argc, char **argv)
{
    // Directory path to list files
    char *dir;
    dir = argv[1];
    
    if(argc <2){
	    dir=".";
    }
    else{
	    dir=argv[1];	
    }
    listFiles(dir);

    return 0;
}


/**
 * Lists all files and sub-directories at given path.
 */
void listFiles(const char *basePath)
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
