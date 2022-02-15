#include<stdio.h>
#include<pthread.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<ifaddrs.h>
#include<string.h>
#include<stdlib.h>
#include <sys/ioctl.h>
#include <net/if.h>
#define	PORT 10604

//#define IP GetLocalIp()
#define IP "127.0.0.1"
//###
char* GetLocalIp(){
	int MAXINTERFACES=16;
	char *ip = NULL;
	int fd, intrface, retn = 0;
	struct ifreq buf[MAXINTERFACES];struct ifconf ifc;
    	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) >= 0){
	    ifc.ifc_len = sizeof(buf);
	    ifc.ifc_buf = (caddr_t)buf;
	    if (!ioctl(fd, SIOCGIFCONF, (char *)&ifc)){
		    intrface = ifc.ifc_len / sizeof(struct ifreq);
		    while (intrface-- > 0){
			    if (!(ioctl (fd, SIOCGIFADDR, (char *) &buf[intrface])))
			    {
				    ip=(inet_ntoa(((struct sockaddr_in*)(&buf[intrface].ifr_addr))->sin_addr));
				    break;
			    }
		    }
	    }
	    close(fd);
	    printf("ip:%s\n",ip);
	    return ip;
    }                                                                                          
}
void* process(void* arg){
	int c_sockfd=*((int*)arg);
	char filename[100]={0};
	char c;
	while(1){
		if(read(c_sockfd,&c,1)==0)
			break;
		if(c==' ')
			break;
		//printf("%c",c);
	}
	int i=0;
	while(i<99){
		if(read(c_sockfd,&c,1)==0)
			break;
		if(c==' ')
			break;
		filename[i++]=c;
	}
	printf("filename:%s\n",filename);
	char su[5]={0};
	if(filename[1]==0)
		sprintf(filename,"/index.html");
//	printf("file name:%s",filename);
	i=strlen(filename)-1;
	while(i>=0){
		if(filename[i]=='.')
			break;
		i--;
	}
	if(i==-1)
		sprintf(filename,"%s.html",filename);
	//	printf("1name:%s\n");
	int j=0;i++;	
	while(1){
		c=filename[i];
		if(c==0)
			break;
		i++;
		su[j++]=c;
	}
	printf("%s\n",su);
	char path[100]={0};
	sprintf(path,".%s",filename);
	printf("filepath:%s\n",path);
	int fd =open(path,O_RDONLY);
	printf("fd:%d\n");
	if(fd==-1){
		printf("no res\nfd:%d\n",fd);
		char error_404[1024]={0};
		sprintf(error_404,"HTTP/1.1 404 Not Found\n\n");
		write(c_sockfd,"HTTP/1.1 404 Not Found\n\n",24);
		write(c_sockfd,error_404,strlen(error_404));	
//		write(c_sockfd,"<h1>Resource Not Found</h1>",28);
	//	shutdown(c_sockfd,SHUT_RDWR);
	//	printf("c\n");
		shutdown(c_sockfd,SHUT_RDWR);
		close(c_sockfd);
	//	printf("b\n");
		pthread_exit(NULL);
	//	printf("a\n");
	}
	write(c_sockfd,"HTTP/1.1 200 OK\n\n",15);
	if(strcmp(su,"html")==0||strcmp(su,"txt")==0)
		write(c_sockfd,"Content-Type: text/html; charset=UTF-8 \n\n",40);
	else if(strcmp(su,"jpeg")==0||strcmp(su,"jpg")==0||strcmp(su,"png")==0||strcmp(su,"gif")==0)
		write(c_sockfd,"Content-Type: image/jpeg\n\n",26);
	char buf[1024];
	while(1){
		memset(buf,0,sizeof(buf));
		int len=read(fd,buf,1024);
		write(c_sockfd,buf,len);
		if(len<1024)
			break;
		}
		shutdown(c_sockfd,SHUT_RDWR);
		close(fd);
}
int main(void){
	struct sockaddr_in s_addr , c_addr;
	int addrlen =sizeof(struct sockaddr_in);
	//printf("%d",addrlen);
	int s_sockfd =socket(AF_INET,SOCK_STREAM,0);
	if(s_sockfd==-1){
		perror("socket error!");
		exit(1);
	}
	memset(&s_addr,0,addrlen);
	s_addr.sin_family=AF_INET;
	s_addr.sin_port=htons(PORT);
	s_addr.sin_addr.s_addr=inet_addr(IP);

	int opt=1;
	setsockopt(s_sockfd,SOL_SOCKET,SO_REUSEADDR,
		&opt,sizeof(opt));
	if(bind(s_sockfd,(const struct sockaddr *)&s_addr,addrlen)==-1){
		perror("bind error!");
		exit(1);
	}
	printf("bind successful\n");
	if(listen(s_sockfd,10)==-1){
		perror("liten error!");
		exit(1);
	}
	printf("listen successful\n");
	pthread_t ptid;
	while(1){
		int c_sockfd=accept(s_sockfd,					(struct sockaddr *)&c_addr,					&addrlen);
		//printf("%d/n",c_addr);
		if(c_sockfd==-1){
			perror("accept error");
			exit(1);
		}
		//printf("recieved client: ip=%s,port=%d",	inet_ntoa(c_addr.sin_addr),ntohs(c_addr.sin_port));
		if (pthread_create(&ptid,NULL,process,&c_sockfd)==-1){
			perror("thread_create error");
			exit(1);
		}
		//exit(1);
	}


	return 0;
}
