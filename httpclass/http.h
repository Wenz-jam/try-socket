#ifndef _JAM_HTTP_CLASS_
#define _JAM_HTTP_CLASS_
#include <iostream>
class classhttp
{
	public:
		classhttp();
		classhttp(const char* url_in);
		classhttp(char* url_in);
		void newurl(char* url_in);
		char* get(char* buffer);
		char* post(char* buffer);
		char* get(char* url_in,char* buffer);
		char* post(char* url_in,char* buffer);
		const char* geturl();
		int port;
		void show();
//		get(char* buffer);
//		post(char* buffer);
	private:
		std::string url;
		std::string buffer;
		char* getaddr();
		void connect();
	//	std::string buffer;
		std::string buffer_recv;
};
#endif
//classhttp jamch("www.baifu.com")
