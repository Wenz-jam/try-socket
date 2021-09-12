#include<stdio.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#define PORT 8080
#define IP "127.0.0.1"//the ip for Server
//
//
//
//
//
//
//main
int main(void){
	struct sockaddr_in c_addr,s_addr;
	int addrlen = sizeof(struct sockaddr_in);
//	创建套接字
	int c_sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(c_sockfd==-1){
		perror("socket error!");
		exit(-1);
	}
	memset(&s_addr,0,addrlen);
	s_addr.sin_family=AF_INET;
	s_addr.sin_port=htons(PORT);
	s_addr.sin_addr.s_addr=inet_addr(IP);
//	原来客户端不用opt和bind的，傻了
/*	int opt=1;
	setsockopt(c_sockfd,SOL_SOCKET,SO_REUSEADDR,
			&opt,sizeof(opt));
	if(bind(c_sockfd,(const struct sockaddr *)&s_addr,addrlen)==-1){
		perror("bind error!");
		exit(1);
	}
	printf("bind successful\n");
*/
//	if(connect(c_sockfd,(struct sockaddr*)&s_addr,10)==-1){
	if(connect(c_sockfd,(struct sockaddr*)&s_addr, sizeof(s_addr))==-1){
		perror("liten error!");
		exit(1);
	}
	printf("listen successful\n");
/*	char buffer[40];
	read(c_sockfd, buffer, sizeof(buffer)-1);
	printf("Message form server: %s\n", buffer);		 
//  	关闭套接字
	close(c_sockfd);
*/	
	while(1){
		char buf[200] = {0};
		printf("input> ");fflush(stdout);
		gets(buf);
		write(c_sockfd, buf, 100);
		bzero(buf, 100);
		read(c_sockfd, buf, 100);
		printf("recv: %s\n", buf);

	}
	close(c_sockfd);
	return 0;
}
