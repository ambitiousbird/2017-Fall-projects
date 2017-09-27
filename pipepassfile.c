
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main()
{
    pid_t pid;
    pid_t p;
    int fd[2];
    size_t r;
    size_t w;
    char* buffer;
    char* buffer1;
    p=pipe(fd);
    printf("%d\n",p);
    pid=fork();
    if(pid)
    {
       close(fd[0]);
       sleep(3);
       buffer=(char*)malloc(4096);
       //int m=write(fd[1],buffer, sizeof(buffer));

       FILE *fp_read;
       fp_read=fopen("ANNA_KARENINA.txt", "r");
       r=1;
       while(r>0)
       {
           //printf("Enter while");
           memset(buffer, 0, sizeof(buffer));
           r=fread(buffer,sizeof(buffer),1,fp_read);
           printf("%d\n",r);
           write(fd[1], buffer, sizeof(buffer));
       }
       fclose(fp_read);
       printf("The parent is running!");
    }
    else
    {
       close(fd[1]);
       sleep(3);
       buffer1=(char*)malloc(4096);
       FILE *fp_write;
       fp_write=fopen("text.txt","w");
       w=1;
       while(w>0)
       {
          memset(buffer1, 0, sizeof(buffer1));
          w=read(fd[0],buffer1,sizeof(buffer1));
          printf("%d\n",r);
          fwrite(buffer1,sizeof(buffer1),1,fp_write);
       }
       fclose(fp_write);
       printf("The child is running!");
    }
    return 0;
}
