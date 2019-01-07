#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(int argc , char *argv[])
{

	int sockfd = 0;
	sockfd = socket(AF_INET , SOCK_STREAM , 0);

	if (sockfd == -1){
		printf("Fail to create a socket.");
	}


	struct sockaddr_in info;
	bzero(&info,sizeof(info));
	info.sin_family = PF_INET;

	info.sin_addr.s_addr = inet_addr("192.168.0.201");
	info.sin_port = htons(8700);


	int err = connect(sockfd,(struct sockaddr *)&info,sizeof(info));
	if(err==-1){
		printf("Connection error");
	}

	// 取得檔案大小
	printf("%s\n", argv[1]);
	FILE *fp = fopen(argv[1], "rb");
	fseek(fp, 0, SEEK_END);
	long long file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	unsigned char message[1024] = {0};
	char receiveMessage[100] = {};
	unsigned char number[] = {0};
	unsigned char sub_number[1]={1};
	long long count_number;
	send(sockfd,sub_number,sizeof(sub_number),0);
	printf("Send Start.\n");
	while(!feof(fp)){
		sub_number[0] = 1;
		fread(message, 1, 1000, fp);
		//printf("%c",message[0]);
		send(sockfd,sub_number,sizeof(sub_number),0);
		recv(sockfd,receiveMessage,sizeof(receiveMessage),0);
		send(sockfd,message,sizeof(message),0);
		recv(sockfd,receiveMessage,sizeof(receiveMessage),0);
	}
	sub_number[0] = 0;
	send(sockfd,sub_number,sizeof(sub_number),0);
	recv(sockfd,receiveMessage,sizeof(receiveMessage),0);
	//printf("close Socket\n");
	printf("%s",receiveMessage);
	close(sockfd);
	return 0;
}
