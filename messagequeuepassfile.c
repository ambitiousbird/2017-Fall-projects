#include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <errno.h>
    #include <sys/msg.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <mqueue.h>
    #include <sys/msg.h>
    #include <sys/types.h>
    #include <sys/ipc.h>

    struct msg_st
    {
        long int msg_type;
        char buffer[1024];
    };
    int main()
    {
        mqd_t mq;
        key_t key;
        int gflags;
        //int running=1;


        //struct mq_attr attr;
        struct msg_st msgst1;
        struct msg_st msgst2;
        pid_t pid;
        pid=fork();
        if(pid)
        {
             //int qid = -1;

              char* buffer1=(char*)malloc(1024);
              FILE *fp1;
              fp1=fopen("ANNA_KARENINA.txt","r");
              gflags=IPC_CREAT|IPC_EXCL;
              mq = msgget((key_t)1234, 0666 | IPC_CREAT);
             // printf("mq:%d\n",mq);
              if(mq==-1)
              {
                  printf("msg create error\n");
              }
              size_t r=1;

              while(r>0)
              {
                 //printf("Enter the while\n");
                 //sleep(3);
                 r=fread(buffer1,sizeof(buffer1),1,fp1);
                // printf("The r:%d ",r);
                 size_t i=msgsnd(mq,(void*)buffer1,sizeof(buffer1),IPC_NOWAIT);
              }

              fclose(fp1);
              printf("THe parent is running\n");

        }
        else
        {
               sleep(3);
               mqd_t mq1;
               char* buffer1=(char*)malloc(1024);
               FILE *fp2;
               fp2=fopen("text.txt","w");
               mq1 = msgget((key_t)1234, 0666 | IPC_CREAT);
               printf("mq1:%d\n",mq1);
              // int w=msgrcv(mq1,(void*)buffer1,sizeof(buffer1),0,IPC_NOWAIT);
               //printf("The w value: %d\n",w);
               size_t running=1;
               while(running)
               {
                  int w=msgrcv(mq1,(void*)buffer1,sizeof(buffer1),0,IPC_NOWAIT);
                  //printf("The w value: %d",w);
                  fwrite(buffer1,sizeof(buffer1),1,fp2);
                  if(w<=0)
                  {
                     running=0;
                  }

               }
               msgctl(mq1, IPC_RMID, 0);


            fclose(fp2);
            printf("THe child is running\n");

        }

    }
