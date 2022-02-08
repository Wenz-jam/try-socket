#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
int main(int argc, char *argv[]){
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_URL, "https://login.live.com/oauth20_authorize.srf?client_id=1695ebdf-ae2f-4efc-bdd3-88c241abadb8&redirect_uri=https://login.live.com/oauth20_desktop.srf&response_type=code&scope=XboxLive.signin\%20offline_access");
  	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Content-Length: 0");
 	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
     //   struct curl_slist *headers = NULL;
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        res = curl_easy_perform(curl);
    }
    curl_easy_cleanup(curl);
    return (int)res;
}
