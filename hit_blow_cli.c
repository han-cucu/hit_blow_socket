
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAX_BUF_SIZE 256

int main(int argc, char *argv[])
{

   
    struct sockaddr_in sa; //sockadder_in 構造体(sa=アドレス)
    int s;
    char buf[MAX_BUF_SIZE+1];
    int len;
    int number;
    int input[4];
    int error;

    int convert;
    int hits,blows;

    if (argc != 3) {
        fprintf(stderr, "Usage: daytime ip_adrress port_number\n");
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
    sa.sin_port = htons(atoi(argv[2]));
    if (inet_pton(AF_INET, argv[1], &sa.sin_addr) <= 0) {
        perror("inet_pton error");
        exit(1);
    }

    //接続の処理
    if (connect(s, (struct sockaddr *)&sa, sizeof(sa)) < 0) {
        perror("connect error");
        exit(1);
    }


  do{
   do{  
     error=0;
     printf("your input:");
     scanf("%d",&number);

     if(number<0 || 9999<number)
        {
	 printf("error:input 4 numbers\n");
	 error++;
        }
 
        input[0]=number/1000;
        input[1]=(number/100)-(input[0]*10);
        input[2]=(number/10)-(input[1]*10)-(input[0]*100);
        input[3]=number-(input[2]*10)-(input[1]*100)-(input[0]*1000);

        if(input[0]==input[1]||input[0]==input[2]||input[0]==input[3]|| input[1]==input[2]||input[1]==input[3]||input[2]==input[3])
       {
         printf("error:there are the same number\n");
     	 error++;
       }
     }while(error!=0);//入力された文字を判定


    write(s,input,sizeof(input));


    if((len = read(s, buf, sizeof(buf))) > 0)
      {
       convert=atoi(buf);
       hits=convert/10;
       blows=convert%10;

        buf[len] = '\0';
       if(len == 10){
         printf("%s\n", buf);
        }
       else if(len != 10){
       printf("%d hit\n%d blow\n",hits,blows);
        }
       }

    if (len < 0) {
        perror("read error");
       }

   }while(len != 10);
    close(s);
}


