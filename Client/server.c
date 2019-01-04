#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc , char *argv[]){
	//socket的建立
	char inputBuffer[1024] = {};
	char message[] = {"Hi,this is server.\n"};
	int sockfd = 0,forClientSockfd = 0;
	sockfd = socket(AF_INET , SOCK_STREAM , 0);
	
	if (sockfd == -1){
		printf("Fail to create a socket.");
	}
	
	//socket的連線
	struct sockaddr_in serverInfo,clientInfo;
	int addrlen = sizeof(clientInfo);
	int flag, number;
	FILE *pFile;
	bzero(&serverInfo,sizeof(serverInfo));
	
	serverInfo.sin_family = PF_INET;
	serverInfo.sin_addr.s_addr = INADDR_ANY;
	serverInfo.sin_port = htons(8700);
	bind(sockfd,(struct sockaddr *)&serverInfo,sizeof(serverInfo));
	listen(sockfd,5);
	
	while(1){
		forClientSockfd = accept(sockfd,(struct sockaddr*) &clientInfo, &addrlen);
		recv(forClientSockfd,inputBuffer,sizeof(inputBuffer),0);
		pFile = fopen("./zip.tgz", "wb");
		flag = inputBuffer[0];
		printf("Start\n",flag);
		//for(int i=0;i<9;i++){
		number=1;
		while(number>0){
			send(forClientSockfd,message,sizeof(message),0);
			recv(forClientSockfd,inputBuffer,sizeof(inputBuffer),0);
			number = inputBuffer[0];
			if(number>0){
				send(forClientSockfd,message,sizeof(message),0);
				recv(forClientSockfd,inputBuffer,sizeof(inputBuffer),0);
				fwrite(inputBuffer,1,1000,pFile);
				//printf("Get:%s\n",inputBuffer);
			}
		}
		send(forClientSockfd,message,sizeof(message),0);
		printf("Finish\n");
		fclose(pFile);
//		break;
//	}
		system("tar zxvf zip.tgz");
		if(system("./busVehicleLicense_test ./CarImage/CarLicense.txt")){
			system("vlc ./CarImage/Video.mp4 > /dev/null 2>&1 &");
			system("leafpad ./CarImage/CarLicense.txt > /dev/null 2>&1 &");
			system("gpicview ./CarImage/CarImage.jpg > /dev/null 2>&1 &");
		}else{
			system("echo 'It is Bus License.' > ./tmp.txt");
			system("leafpad ./tmp.txt > /dev/null 2>&1 &");
		}
	}
	return 0;
}
