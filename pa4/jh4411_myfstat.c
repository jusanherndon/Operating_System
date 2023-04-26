#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>

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
FileTypes file_type[50];

if(argc < 51){
     for(int i=1; i<argc;i++){
          if(argv[i] != NULL){
               stat(argv[i],&sfile);
               int type = sfile.st_mode;
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

	  }
     }

}

}
