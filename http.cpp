#include<iostream>
#include"http.h"
#include<stdio.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>

classhttp::classhttp(){
	url="127.0.0.1";
}
classhttp::classhttp(const char* url_in){
//	printf("const create:%s\n",url_in);
	url=url_in;
}
classhttp::classhttp(char* url_in){	
//	printf("create:%s\n",url_in);
	url=url_in;
}
char* classhttp::get(char* buffer){
	return 0;
}
char* classhttp::post(char* buffer){
	return 0;
}
char* classhttp::get(char* url_in,char* buffer){
	return 0;
}

char* classhttp::post(char* url_in,char* buffer){
	return 0;
}
const char* classhttp::geturl(){
	return url.c_str();
}
void classhttp::show(){
	std::cout<<"url:";
	std::cout<<url<<std::endl;
}
#ifdef linux


#else


#endif
