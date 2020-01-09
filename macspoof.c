#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

#include "block.h"

const char *NETWORK_INTERFACE_DIR = "/sys/class/net";
const char *NETWORK_INTERFACE_MACFILE = "address";
const char *WLAN_CONNECTIONS_FILE = "/proc/net/wireless";

char *read_current_mac(const char *iface)
{
    char *mac = malloc(0);
    struct ifreq ifr;
    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (fd != -1) {
        ifr.ifr_addr.sa_family = AF_INET;
        strncpy(ifr.ifr_name, iface, IFNAMSIZ);
        ioctl(fd, SIOCGIFHWADDR, &ifr);
        close(fd);
        unsigned char *result = (unsigned char *)ifr.ifr_hwaddr.sa_data;
        mac = (char *)realloc(mac, sizeof(char) * 18);
        snprintf(mac, 18, "%.2x:%.2x:%.2x:%.2x:%.2x:%.2x", result[0], result[1], result[2], result[3], result[4], result[5]);
        mac[18] = '\0';
    }
    return mac;
}

char *read_permanent_mac(const char *iface)
{
    char *mac = calloc(0, 0);
    int length = strlen(iface) + 24;
    char command[length];

    snprintf(command, length, "ethtool -P %s 2>/dev/null", iface);
    FILE *file = popen(command, "r");
    if (file != NULL) {
        char *line = NULL;
        size_t size = 0;
        getline(&line, &size, file);
        char *token = strtok(line, " ");
        int i = 0;
        while (token && i < 3) {
            if (i == 2) {
                mac = (char *)realloc(mac, sizeof(char) * 18);
                strncpy(mac, token, 18);
                mac[17] = '\0';
            }
            token = strtok(NULL, " ");
            i++;
        }
        pclose(file);
    }
    return mac;
}

int main()
{
    char *iface = getenv("BLOCK_INSTANCE");

    if (iface != NULL) {
        char *cmac = read_current_mac(iface);
        char *pmac = read_permanent_mac(iface);

        printf("MAC\n");
        printf("MAC\n");

        char color[8];
        color[7] = '\0';
        if (strcmp(cmac, pmac) == 0 || strlen(cmac) == 0 || strlen(pmac) == 0)
            strncpy(color, COLOR_RED, COLOR_LENGTH);
        else
            strncpy(color, COLOR_RED, COLOR_LENGTH);
        printf("%s\n", color);

        free(pmac);
        free(cmac);
    }
    return 0;
}
