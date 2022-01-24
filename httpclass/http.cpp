#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#ifndef win32
#include<fcntl.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>
#else
#endif

#include"http.h"

classhttp::classhttp(){
	port=80;
	url="127.0.0.1";
}
classhttp::classhttp(const char* url_in){
	port=80;
	url=url_in;
	if(isalpha(url_in[0]))
		getaddr();
}
classhttp::classhttp(char* url_in){
	classhttp((const char*)url_in);
}
char* classhttp::get(char* buffer_in){
	buffer="GET ";
	buffer+=buffer_in;
	connect();
	return 0;
}
char* classhttp::post(char* buffer_in){
	return 0;
}
char* classhttp::get(char* url_in,char* buffer){
	newurl(url_in);
	get(buffer);
	return 0;
}

char* classhttp::post(char* url_in,char* buffer){
	newurl(url_in);
	post(buffer);	
	return 0;
}
const char* classhttp::geturl(){
	return url.c_str();
}
void classhttp::show(){
	std::cout<<"url:";
	std::cout<<url<<std::endl;
}
void classhttp::newurl(char* url_in){
	url=url_in;
}
void classhttp::connect()
{
	struct sockaddr_in c_addr,s_addr;
	int addrlen = sizeof(struct sockaddr_in);
	int c_sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(c_sockfd==-1){
		perror("socket error!\n");
		exit(-1);
	}
	memset(&s_addr,0,addrlen);
	s_addr.sin_family=AF_INET;
	s_addr.sin_port=htons(port);
	s_addr.sin_addr.s_addr=inet_addr(url.c_str());
	printf("listening\n");
	if(::connect(c_sockfd,(struct sockaddr*)&s_addr, sizeof(s_addr))==-1){
		perror("liten error!\n");
		exit(1);
	}
	printf("writing:%s\n",buffer.c_str());
	char buf[200] = {0};
	fflush(stdout);
	write(c_sockfd, buffer.c_str(), 1024);
	bzero(buf, 100);
	read(c_sockfd, buf, 100);	
	printf("recv: %s\n", buf);
	buffer_recv=buf;
	close(c_sockfd);
}
char* classhttp::getaddr(){
    char *name =(char*)url.c_str();
    struct hostent *hptr;
 
    hptr = gethostbyname(name);
    if (hptr == NULL) {
        printf("gethostbyname error for host: %s: %s\n", name, hstrerror(h_errno));
        return 0;
    } 
    //输出ip地址
    char str[INET_ADDRSTRLEN];
    switch (hptr->h_addrtype) {
        case AF_INET:
		url=inet_ntop(hptr->h_addrtype, hptr->h_addr, str, sizeof(str));
            break;
        default:
            printf("unknown address type\n");
            break;
    }
 
    return 0;
}
