#ifndef _JAM_HTTP_CLASS_
#define _JAM_HTTP_CLASS_
#include <iostream>
class classhttp
{
	public:
		classhttp();
		classhttp(const char* url_in);
		classhttp(char* url_in);
		void newurl();
		char* get(char* buffer);
		char* post(char* buffer);
		char* get(char* url_in,char* buffer);
		char* post(char* url_in,char* buffer);
		const char* geturl();
		void show();
//		get(char* buffer);
//		post(char* buffer);
	private:
		std::string url;
		std::string buffer;
};
#endif
//classhttp jamch("www.baifu.com")
