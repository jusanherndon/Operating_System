#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/resource.h>

// I used this enum to make the consts' more readable
typedef enum FileTypes {
     File,
     Directory,
     SymLink,
     BlockDevice,
     CharacterDevice,
     FIFOPipe,
     Socket,
     Unknown
} FileTypes;

// Used this man page for inspiration of this function
// https://www.man7.org/linux/man-pages/man2/stat.2.html
FileTypes identify_file(int st_mode){
     switch (st_mode & S_IFMT) {
           case S_IFBLK:  
                return BlockDevice;
           case S_IFCHR:  
	        return CharacterDevice;
           case S_IFDIR:  
		return Directory;
           case S_IFIFO:  
		return FIFOPipe;
           case S_IFLNK:  
		return SymLink;
           case S_IFREG: 
		return File;
           case S_IFSOCK:
		return Socket;
           default:       
		return Unknown;
     }
}

int main(int argc, char *argv[]){
struct stat sfile;
struct rusage system_usage;
FileTypes file_type[50];

// This requirement exists to ensure the list can only accept
// 50 file names
if(argc < 51){
     // The for loop starts at 1 to avoid taking in the executable as 
     // a parameter
     for(int i=1; i<argc;i++){
	  // This check makes sure that a valid file name is passed 
          if(argv[i] != NULL){
               stat(argv[i],&sfile);
               int type = sfile.st_mode;
	       int uid = sfile.st_uid;
	       int gid = sfile.st_gid;
	       int hard_links = sfile.st_nlink;
	       int last_access = sfile.st_atime;
	       int last_modification = sfile.st_mtime;
	       int last_status = sfile.st_ctime;
	       int size = sfile.st_size;
	       int inode = sfile.st_ino;

	       file_type[i] = identify_file(type);
	       switch(file_type[i]){
                    case File:
		         printf("%s is a file\n",argv[i]);
			 break;

                    case Directory:
		         printf("%s is a directory\n",argv[i]);
			 break;

                    case SymLink:
		         printf("%s is a symlink\n",argv[i]);
			 break;

                    case BlockDevice:
		         printf("%s is a block device\n",argv[i]);
			 break;

                    case CharacterDevice:
		         printf("%s is a character device\n",argv[i]);
			 break;

                    case FIFOPipe:
		         printf("%s is a FIFO Pipe\n",argv[i]);
			 break;

                    case Socket:
		         printf("%s is a Socket\n",argv[i]);
			 break;

                    case Unknown:
		         printf("%s is unknown\n",argv[i]);
			 break;
	       }
	       printf("This is the user id for %s: %d\n",argv[i],uid);
	       printf("This is the group id for %s: %d\n",argv[i],gid);
               printf("This is the hard links for %s: %d\n",argv[i],hard_links);
               printf("This is the last access time for %s: %d\n",argv[i],last_access);
               printf("This is the last modification time for %s: %d\n",argv[i],last_modification);
               printf("This is the last status for %s: %d\n",argv[i],last_status);
               printf("This is the file size for %s: %d\n",argv[i],size);
               printf("This is the inode number for %s: %d\n",argv[i],inode);
	  }
	  printf("\n");
     }
}

getrusage(RUSAGE_SELF,&system_usage);
struct timeval user_cpu_time = system_usage.ru_utime;
struct timeval system_cpu_time = system_usage.ru_stime;

// Based the formatting of this print statement from this
// stack overflow question:
// https://stackoverflow.com/questions/1469495/unix-programming-struct-timeval-how-to-print-it-c-programming
printf("User cpu time used: %ld.%06ld\n", user_cpu_time.tv_sec, user_cpu_time.tv_usec);
printf("System cpu time used: %ld.%06ld\n", system_cpu_time.tv_sec, system_cpu_time.tv_usec);
}
