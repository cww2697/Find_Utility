#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <time.h>


void find(const char *path, int n, const char *name, int m, int mmin, int m_ident, int i, ino_t inode, int r);

int main(int argc, char **argv)
{


    int		w, n, m, i, e, r, mmin, m_ident;
    ino_t inode;
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
            //printf("%s\n",mmin_string);
                
            if(strncmp(mmin_string, "+", 1)==0){
                m_ident = 1;
            }
            else if(strncmp(mmin_string, "-", 1)==0){
                m_ident = -1;
            }
            else{
                m_ident = 0;
            }
			mmin = atoi(mmin_string);
            mmin=mmin*60;
			//printf("mmin: %d\nm_ident: %d\n", mmin,m_ident);
			break;
		case 'i':   // find by inode number
			i = 1;
			inum = optarg;
            inode = atoi(inum);
			break;
		case 'r':   // remove
			r = 1;
			break;
        case 'e':   // execute
            e = 1;
            action = optarg;
            printf("%s\n", action);
            break;
		case '?':
            // Help case
		default:
			printf("An invalid option detected.\n");
            return 0;
            break;
		}
	}

    if(w==0){
		where = ".";
	}
    
    
    //printf("Variables prior to function call:\nw = %d\nn = %d\nm = %d\ni = %d\ninode = %llu\n", w,n,m,i,inode);
    find(where, n , name, m, mmin, m_ident, i, inode, r);

    return 0;
}






/*
 * Lists all files and sub-directories at given path.
 */
void find(const char *basePath, int n, const char *name, int m, int mmin, int m_ident, int i, ino_t inode, int r)
{
    char path[1000];
    ino_t file_inode = 0;
    time_t mod_time;
    time_t current_epoch;
    struct stat filestat;
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    current_epoch = time(NULL);
    //printf("Variables in function call:\nn = %d\nm = %d\ni = %d\ninode = %llu\nr = %d\n",n,m,i,inode,r);
    
    // Unable to open directory stream
    if (!dir){
        return;
    }

    while ((dp = readdir(dir)) != NULL){
        //printf("\n\n\n\nhello\n\n\n\n");
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            stat(path, &filestat);
            mod_time = filestat.st_mtime;
            file_inode = dp->d_ino;
            //printf("%llu\n", inode);
            
            // Find by name
            if(n==1){
                if(strcmp(dp->d_name, name) == 0){
                    //printf("\n----name compare----\n");
                    // Find by modified time
                    if(m==1){
                        if(m_ident == 1){
                            //printf("Using m_ident = 1\n");
                            if(mod_time < current_epoch-mmin){
                                if(i == 1){
                                    if(file_inode == inode){
                                        strcpy(path, basePath);
                                        strcat(path, "/");
                                        strcat(path, dp->d_name);
                                        printf("%s\n", path);
                                        if(r==1){
                                            printf("Removed the following path: %s\n", path);
                                            remove(path);
                                        }
                                    }
                                    else{
                                        strcpy(path, basePath);
                                        strcat(path, "/");
                                        strcat(path, dp->d_name);
                                    }
                                }
                                // else for i == 1
                                else{
                                    strcpy(path, basePath);
                                    strcat(path, "/");
                                    strcat(path, dp->d_name);
                                    printf("%s\n", path);
                                    if(r==1){
                                        printf("Removed the following path: %s\n", path);
                                        remove(path);
                                    }
                                }
                            }
                            //else for mod_time
                            else{
                                strcpy(path, basePath);
                                strcat(path, "/");
                                strcat(path, dp->d_name);
                            }
                        }
                       
                        else if(m_ident == 0){
                            //printf("Using m_ident = 0\n");
                            if(mod_time == current_epoch-mmin){
                                if(i == 1){
                                    if(file_inode == inode){
                                        strcpy(path, basePath);
                                        strcat(path, "/");
                                        strcat(path, dp->d_name);
                                        printf("%s\n", path);
                                        if(r==1){
                                            printf("Removed the following path: %s\n", path);
                                            remove(path);
                                        }
                                    }
                                    else{
                                        strcpy(path, basePath);
                                        strcat(path, "/");
                                        strcat(path, dp->d_name);
                                    }
                                }
                                // else for i == 1
                                else{
                                    strcpy(path, basePath);
                                    strcat(path, "/");
                                    strcat(path, dp->d_name);
                                    printf("%s\n", path);
                                    if(r==1){
                                        printf("Removed the following path: %s\n", path);
                                        remove(path);
                                    }
                                }
                            }
                           
                       
                            // else for mod_time
                            else{
                                strcpy(path, basePath);
                                strcat(path, "/");
                                strcat(path, dp->d_name);
                            }
                        }
                       
                        else if(m_ident == -1){
                            //printf("Using m_ident = -1\n");
                            if(mod_time > current_epoch-mmin){
                                if(i == 1){
                                    if(file_inode == inode){
                                        strcpy(path, basePath);
                                        strcat(path, "/");
                                        strcat(path, dp->d_name);
                                        printf("%s\n", path);
                                        if(r==1){
                                            printf("Removed the following path: %s\n", path);
                                            remove(path);
                                        }
                                    }
                                    else{
                                        strcpy(path, basePath);
                                        strcat(path, "/");
                                        strcat(path, dp->d_name);
                                    }
                                }
                                // else for i == 1
                                else{
                                    strcpy(path, basePath);
                                    strcat(path, "/");
                                    strcat(path, dp->d_name);
                                    printf("%s\n", path);
                                    if(r==1){
                                        printf("Removed the following path: %s\n", path);
                                        remove(path);
                                    }
                                }
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
                        //printf("Using else case for -m\n");
                        if(i == 1){
                            if(file_inode == inode){
                                //printf("Inode %llu found!", inode);
                                strcpy(path, basePath);
                                strcat(path, "/");
                                strcat(path, dp->d_name);
                                printf("%s\n", path);
                                if(r==1){
                                    printf("Removed the following path: %s\n", path);
                                    remove(path);
                                }
                            }
                            else{
                                strcpy(path, basePath);
                                strcat(path, "/");
                                strcat(path, dp->d_name);
                            }
                        }
                        else{
                            strcpy(path, basePath);
                            strcat(path, "/");
                            strcat(path, dp->d_name);
                            printf("%s\n", path);
                            if(r==1){
                                printf("Removed the following path: %s\n", path);
                                remove(path);
                            }
                        }
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
                //printf("Using else case for name\n");
                // find by time modified
                if(m==1){
                    //printf("Using m = 1\n");
                    if (m_ident == 1){
                        //printf("Using m_ident = 1\n");
                        if(mod_time < current_epoch-mmin){  // files modified more than mmin
                            if(i==1){
                                if(file_inode==inode){
                                    strcpy(path, basePath);
                                    strcat(path, "/");
                                    strcat(path, dp->d_name);
                                    printf("%s\n", path);
                                    if(r==1){
                                        printf("Removed the following path: %s\n", path);
                                        remove(path);
                                    }
                                }
                                else{
                                    strcpy(path, basePath);
                                    strcat(path, "/");
                                    strcat(path, dp->d_name);
                                }
                            }
                            else{
                                strcpy(path, basePath);
                                strcat(path, "/");
                                strcat(path, dp->d_name);
                                printf("%s\n", path);
                                if(r==1){
                                    printf("Removed the following path: %s\n", path);
                                    remove(path);
                                }
                            }
                        }
                        else{
                            strcpy(path, basePath);
                            strcat(path, "/");
                            strcat(path, dp->d_name);
                        }
                    }
                    else if(m_ident == 0){  //files modified exactly mmin
                        //printf("Using m_ident = 0\n");
                        if(mod_time == current_epoch-mmin){
                            if (i==1){
                                if(file_inode==inode){
                                    strcpy(path, basePath);
                                    strcat(path, "/");
                                    strcat(path, dp->d_name);
                                    printf("%s\n", path);
                                    if(r==1){
                                        printf("Removed the following path: %s\n", path);
                                        remove(path);
                                        
                                    }
                                }
                                else{
                                    strcpy(path, basePath);
                                    strcat(path, "/");
                                    strcat(path, dp->d_name);
                                }
                            }
                            else{
                                strcpy(path, basePath);
                                strcat(path, "/");
                                strcat(path, dp->d_name);
                                printf("%s\n", path);
                                if(r==1){
                                    printf("Removed the following path: %s\n", path);
                                    remove(path);
                                }
                            }
                        }
                        else{
                            strcpy(path, basePath);
                            strcat(path, "/");
                            strcat(path, dp->d_name);
                        }
                    }
                    else if(m_ident == -1){ // files modified less than mmin
                        //printf("Using m_ident = -1\n");
                        if(mod_time > current_epoch-mmin){
                            if (i==1){
                                if(file_inode==inode){
                                    strcpy(path, basePath);
                                    strcat(path, "/");
                                    strcat(path, dp->d_name);
                                    printf("%s\n", path);
                                    if(r==1){
                                        printf("Removed the following path: %s\n", path);
                                        remove(path);
                                    }
                                }
                                else{
                                    strcpy(path, basePath);
                                    strcat(path, "/");
                                    strcat(path, dp->d_name);
                                }
                            }
                            else{
                                strcpy(path, basePath);
                                strcat(path, "/");
                                strcat(path, dp->d_name);
                                printf("%s\n", path);
                                if(r==1){
                                    printf("Removed the following path: %s\n", path);
                                    remove(path);
                                }
                            }
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
                    if(i == 1){
                        if(file_inode==inode){
                            strcpy(path, basePath);
                            strcat(path, "/");
                            strcat(path, dp->d_name);
                            printf("%s\n", path);
                            if(r==1){
                                printf("Removed the following path: %s\n", path);
                                remove(path);
                            }
                        }
                        else{
                            strcpy(path, basePath);
                            strcat(path, "/");
                            strcat(path, dp->d_name);
                        }
                    }
                    else{
                        strcpy(path, basePath);
                        strcat(path, "/");
                        strcat(path, dp->d_name);
                        printf("%s\n", path);
                        if(r==1){
                            printf("Removed the following path: %s\n", path);
                            remove(path);
                        }
                    }
                }
               
            }
            
            find(path, n, name, m, mmin, m_ident, i, inode, r);  // recursive call of function
        }
    }

    closedir(dir);  // once finished close the directory
}
