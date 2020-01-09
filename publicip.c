#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "block.h"

const char *IPURL = "http://ipecho.net/plain";

typedef struct {
    char *address;
} Ipinfo;

size_t response(void *ptr, size_t size, size_t nmemb, Ipinfo *ipinfo)
{
    (void) nmemb;

    size_t len = size * nmemb;
    if (len >= 15) {
        len = 15;
    }
    ipinfo->address = realloc(ipinfo->address, len * sizeof(char));
    memcpy(ipinfo->address, ptr, len);
    ipinfo->address[15] = '\0';
    return len;
}

void read_ipinfo(Ipinfo *ipinfo)
{
    CURL *curl = curl_easy_init();
    if (curl != NULL) {
        curl_easy_setopt(curl, CURLOPT_URL, IPURL);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, response);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, ipinfo);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
}

void print_ipinfo(Ipinfo *ipinfo)
{
    char color[9];

    set_color(color, 0, 0, 0);
    printf("%s\n", ipinfo->address);
    printf("%s\n", ipinfo->address);
    printf("%s\n", color);
}

int main()
{
    Ipinfo ipinfo;
    ipinfo.address = malloc(8 * sizeof(char));

    strncpy(ipinfo.address, "0.0.0.0", 8);
    ipinfo.address[7] = '\0';

    read_ipinfo(&ipinfo);
    print_ipinfo(&ipinfo);

    free(ipinfo.address);
}
