#include<iostream>
#include"http.h"
int main(){
//	classhttp test("www.baidu.com");
	classhttp test("login.live.com");
	test.show();
	std::string buffer;
	buffer="/oauth20_authorize.srf";
	buffer+="?client_id=1695ebdf-ae2f-4efc-bdd3-88c241abadb8";
	buffer+="&response_type=code";
	buffer+="&redirect_uri=https://login.live.com/oauth20_desktop.srf";
	buffer+="&scope=XboxLive.signin\%20offline_access";
	/*?client_id=<your Azure client ID>
 &response_type=code
 &redirect_uri=<your redirect uri>
 &scope=XboxLive.signin%20offline_access //without offline_access you won't get an refresh_token
 &state=<optional; used to prevent CSRF & restoring previous application states>
*/
	test.get((char*)buffer.c_str());
//	printf("%s\n",test.geturl());
}
