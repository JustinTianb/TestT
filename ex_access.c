#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
   int i, num;
   int fd;
   char buf[20];

  if (argc !=2)  {
       printf("Usage:  %s <pathname>\n", argv[0]);
       exit(EXIT_FAILURE);
      }
  if (access(argv[1], F_OK) != 0)  {
     printf("The file '%s' is not existed!\n",argv[1]);
     exit(EXIT_FAILURE);
      }
   else if (access(argv[1], R_OK) != 0)  {
     printf("The file '%s' can not be read!\n",argv[1]);
     exit(EXIT_FAILURE);
      }
    
  if((fd = open(argv[1],O_RDONLY)) < 0) {
      printf("Fail to open file '%s'!\n",argv[1]);
      exit(EXIT_FAILURE);
     }
  if((num = read(fd, buf, 20)) < 0) {
      close(fd);
      printf("Fail to read file '%s'!\n",argv[1]);
      exit(EXIT_FAILURE);
     }

    printf("The starting %d bytes of '%s' is:\n", num, argv[1]);
    for(i=0; i< num; i++) {
      printf("%c(%x) ", buf[i], buf[i]);
      }
     printf("\n");

     close(fd);

     exit(EXIT_SUCCESS);
}
