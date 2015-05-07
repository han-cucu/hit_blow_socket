
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#define MAX_BUF_SIZE 256
#define BACKLOG 5
#define RIGHT_SIZE 10

int main(int argc, char *argv[])
{
    int s;
    int c;
    struct sockaddr_in sa;
    struct sockaddr_in csa;
    
    char buf[MAX_BUF_SIZE+1];
    int len;
   
   
    int n;
    
    int answer[4];
    int input[4];
    int number;
    int i,j,k;
    int hit=0,blow=0;
    int right=0;
    char message[MAX_BUF_SIZE+1];
    char message_right[RIGHT_SIZE];
    int error;

    //答えの数字を設定
   srand((unsigned)time(NULL));
   {
  do{
      error=0;
      for(k=0;k<4;k++)
       {
	 answer[k] = rand() % 10;
       }

      if(answer[0]==answer[1]||answer[0]==answer[2]||answer[0]==answer[3]||answer[1]==answer[2]||answer[1]==answer[3]||answer[2]==answer[3])
      {
     	 error=1;
      }
    }while(error==1);
   }



#ifndef NOREUSEADDR
    int nonzero = 1;
#endif

    if (argc != 2) {
        fprintf(stderr, "Usage: daytimed port_number\n");
        exit(1);
    }
    
    //ソケットの生成, 処理
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error");
        exit(1);
    }
    //構造体の設定
    bzero(&sa, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(atoi(argv[1]));
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

#ifndef NOREUSEADDR
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &nonzero, sizeof(nonzero));
#endif
    //バインドの生成, 処理
    if (bind(s, (struct sockaddr *)&sa, sizeof(sa)) < 0) {
        perror("bind error");
        exit(1);
    }
    //待ち状態にする
    if (listen(s, BACKLOG) < 0) {
        perror("listen error");
        exit(1);
    }

    //接続の処理
    //while (1) {
        n = sizeof(csa);
        if((c = accept(s,(struct sockaddr *)&csa,(socklen_t *)&n))<0){
            perror("connect error");
            exit(1);
        }
        printf("Connected from %s port %d\n", inet_ntoa(csa.sin_addr), ntohs(csa.sin_port));
       

     printf("%d%d%d%d\n",answer[0],answer[1],answer[2],answer[3]);
       
     do{       
       hit = 0;
       blow =0;
       right=0;
       read(c,input,sizeof(input));

       for(i=0; i<=3; i++){
          for(j=0; j<=3; j++){ 
             if(input[i]==answer[j])
                    blow = blow + 1;
            }
          if(input[i]==answer[i]){
                hit = hit + 1;
                blow = blow - 1;
            }
        }
        
       if(hit == 4){
          sprintf(message,"right!\n");
          right = 1;
          write(c,message,sizeof(message_right));
	  printf("right!\n");
	  exit(1);
         }
       else{
        sprintf(message,"%d%d",hit,blow);
        write(c,message,sizeof(message));
         }        
      
      }while(right!=1);
     
     
    

}
