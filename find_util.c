#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <time.h>


void find(const char *path, int n, const char *name, int m, int mmin, int m_ident);

int main(int argc, char **argv)
{


    int		w, n, m, i, a, mmin, m_ident, inode;
	char  *where, *name, *mmin_string, *inum, *action;
	while (1) {
		char		c;
		c = getopt(argc, argv, "w:n:m:i:re:");

		if (c == -1) {
			break;
		}
		switch (c) {
		case 'w':   // where to look
			w = 1;
			where = optarg;
			break;
		case 'n':   // find by name
			n = 1;
			name = optarg;
			break;
		case 'm':   // find by modified minutes
			m = 1;
			mmin_string = optarg;
            if(strncmp(mmin_string, "-", 1)){
                m_ident = 1;
            }
            else if(strncmp(mmin_string, "+", 1)){
                m_ident = -1;
            }
            else{
                m_ident = 0;
            }
			mmin = atoi(mmin_string);
            mmin=mmin*60;
			printf("mmin: %d\n", mmin);
			break;
		case 'i':   // find by inode number
			i = 1;
			inum = optarg;
            inode = atoi(mmin_string);
			break;
		case 'r':   // remove
			r = 1;
			break;
        case 'e':   // execute
            e = 1;
            action = optarg;
            break;
		case '?':
            // Help case
		default:
			printf("An invalid option detected.\n");
		}
	}

    if(w==0){
		where = ".";
	}
    
    printf("Variables prior to function call:\nw = %d\nn = %d\nm = %d\n", w,n,m);
    find(where, n , name, m, mmin, m_ident);

    return 0;
}


/*
 * Lists all files and sub-directories at given path.
 */
void find(const char *basePath, int n, const char *name, int m, int mmin, int m_ident)
{
    char path[1000];
    ino_t file_inode;
    time_t mod_time;
    time_t current_epoch;
    struct stat filestat;
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    current_epoch = time(NULL);
    
    // Unable to open directory stream
    if (!dir){
        return;
    }

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            stat(path, &filestat);
            mod_time = filestat.st_mtime;
            file_inode = filestat.st_ino;
            
            // Find by name
            if(n==1){
                if(strcmp(dp->d_name, name) == 0){
                    
                    // Find by modified time
                   if(m==1){
                       if(m_ident == 1){
                           if(mod_time < current_epoch-mmin){
                               if(i == 1){
                                   if(mod_time < current_epoch-mmin){
                               }
                               strcpy(path, basePath);
                               strcat(path, "/");
                               strcat(path, dp->d_name);
                               printf("%s\n", path);
                           }
                           else{
                               strcpy(path, basePath);
                               strcat(path, "/");
                               strcat(path, dp->d_name);
                           }
                       }
                       
                       else if(m_ident == 0){
                           if(mod_time == current_epoch-mmin){
                               strcpy(path, basePath);
                               strcat(path, "/");
                               strcat(path, dp->d_name);
                               printf("%s\n", path);
                           }
                           else{
                               strcpy(path, basePath);
                               strcat(path, "/");
                               strcat(path, dp->d_name);
                           }
                       }
                       
                       else if(m_ident == -1){
                           if(mod_time > current_epoch-mmin){
                               strcpy(path, basePath);
                               strcat(path, "/");
                               strcat(path, dp->d_name);
                               printf("%s\n", path);
                           }
                           else{
                               strcpy(path, basePath);
                               strcat(path, "/");
                               strcat(path, dp->d_name);
                           }
                       }
                    }
                    
                    //else for modified time
                    else{
                        strcpy(path, basePath);
                        strcat(path, "/");
                        strcat(path, dp->d_name);

                        printf("%s\n", path);
                    }
                     
                }
            
                else{
                    strcpy(path, basePath);
                    strcat(path, "/");
                    strcat(path, dp->d_name);
                }
            }
            
            // else for case n != 1
            else{
                
                // find by time modified
                if(m==1){
                    if (m_ident == 1){
                        if(mod_time < current_epoch-mmin){  // files modified more than mmin
                            strcpy(path, basePath);
                            strcat(path, "/");
                            strcat(path, dp->d_name);
                            printf("%s\n", path);
                        }
                        else{
                            strcpy(path, basePath);
                            strcat(path, "/");
                            strcat(path, dp->d_name);
                        }
                    }
                    else if(m_ident == 0){  //files modified exactly mmin
                        if(mod_time == current_epoch-mmin){
                            strcpy(path, basePath);
                            strcat(path, "/");
                            strcat(path, dp->d_name);
                            printf("%s\n", path);
                        }
                        else{
                            strcpy(path, basePath);
                            strcat(path, "/");
                            strcat(path, dp->d_name);
                        }
                    }
                    else if(m_ident == -1){ // files modified less than mmin
                        if(mod_time > current_epoch-mmin){
                            strcpy(path, basePath);
                            strcat(path, "/");
                            strcat(path, dp->d_name);
                            printf("%s\n", path);
                        }
                        else{
                            strcpy(path, basePath);
                            strcat(path, "/");
                            strcat(path, dp->d_name);
                        }
                    }
                }
                
                //else for time modified
                else{
                    strcpy(path, basePath);
                    strcat(path, "/");
                    strcat(path, dp->d_name);
                    printf("%s\n", path);
                }
               
            }
            
            find(path, n, name, m, mmin, m_ident);  // recursive call of function
            
            /*strcpy(path, basePath);
            *strcat(path, "/");
            *strcat(path, dp->d_name);
            *find(path, n, name, m, mmin, m_ident);
            *Construct new path from our base path
            */
            
        }
    }

    closedir(dir);  // once finished close the directory
}
