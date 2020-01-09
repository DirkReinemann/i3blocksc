#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

const char *WIRELESS_FILE = "/proc/net/wireless";
const char *NETWORK_INTERFACE_DIR = "/sys/class/net";
const char *ETHERNET_SPEED_FILE = "speed";
const char *NETWORK_INTERFACE_OPERSTATE_FILE = "operstate";
const char *OPERSTATE_UP = "up";

char *read_ip(const char *iface)
{
    char *ip = NULL;
    struct ifreq ifr;
    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (fd != -1) {
        ifr.ifr_addr.sa_family = AF_INET;
        strncpy(ifr.ifr_name, iface, IFNAMSIZ);
        ioctl(fd, SIOCGIFADDR, &ifr);
        close(fd);
        char *result = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
        int length = strlen(result);
        ip = (char *)malloc(sizeof(char) * (length + 1));
        strncpy(ip, result, length + 1);
        ip[length] = '\0';
    }
    return ip;
}

int read_strength(const char *iface)
{
    int speed = 0;

    if (access(WIRELESS_FILE, F_OK) != -1) {
        FILE *file = fopen(WIRELESS_FILE, "r");
        if (file != NULL) {
            char *line = NULL;
            size_t size = 0;
            ssize_t read = 0;
            regex_t regex;
            regcomp(&regex, iface, 0);
            while ((read = getline(&line, &size, file)) != -1)
                if (!regexec(&regex, line, 0, NULL, 0)) {
                    char *token = strtok(line, " ");
                    int i = 0;
                    while (token && i < 4) {
                        if (i == 3)
                            speed = atol(token);
                        token = strtok(NULL, " ");
                        i++;
                    }
                }
            fclose(file);
            if (speed < 0)
                speed = 110 + speed;
        }
    }
    return speed;
}

int read_speed(const char *iface)
{
    int speed = 0;
    int length = strlen(NETWORK_INTERFACE_DIR) + strlen(iface) + strlen(ETHERNET_SPEED_FILE) + 3;
    char filename[length];

    snprintf(filename, length, "%s/%s/%s", NETWORK_INTERFACE_DIR, iface, ETHERNET_SPEED_FILE);
    if (access(filename, F_OK) != -1) {
        FILE *file = fopen(filename, "r");

        if (file != NULL) {
            char *line = NULL;
            size_t size = 0;
            getline(&line, &size, file);
            speed = atoi(line);
            fclose(file);
        }
    }
    return speed;
}

int read_operstate(const char *iface)
{
    int operstate = 0;
    int length = strlen(NETWORK_INTERFACE_DIR) + strlen(iface) + strlen(NETWORK_INTERFACE_OPERSTATE_FILE) + 3;
    char filename[length];

    snprintf(filename, length, "%s/%s/%s", NETWORK_INTERFACE_DIR, iface, NETWORK_INTERFACE_OPERSTATE_FILE);
    if (access(filename, F_OK) != -1) {
        FILE *file = fopen(filename, "r");

        if (file != NULL) {
            char *line = NULL;
            size_t size = 0;
            getline(&line, &size, file);
            if (line != NULL) {
                line[strlen(line) - 1] = '\0';
                if (strcmp(line, OPERSTATE_UP) == 0)
                    operstate = 1;
            }
            fclose(file);
        }
    }


    return operstate;
}

int get_int_length(const int value)
{
    return value == 0 ? 1 : ((int)(log10(value) + 1) + (value < 0 ? 1 : 0));
}

void print_result(const char *result, const int operstate)
{
    for (int i = 0; i < 2; i++) {
        if (operstate == 0)
            printf("down\n");
        else
            printf("%s\n", result);
    }
}

int main()
{
    char *iface = getenv("BLOCK_INSTANCE");

    if (iface != NULL) {
        int operstate = read_operstate(iface);
        char *ip = read_ip(iface);

        switch (iface[0]) {
        case 'e': {
            int speed = read_speed(iface);
            int length = strlen(ip) + get_int_length(speed) + 6;
            char result[length];
            snprintf(result, length, "%s %iMB/s\n", ip, speed);
            print_result(result, operstate);
            break;
        }
        case 'w': {
            int strength = read_strength(iface);
            int length = strlen(ip) + get_int_length(strength) + 3;
            char result[length];
            snprintf(result, length, "%s %i%%\n", ip, strength);
            print_result(result, operstate);
            break;
        }
        }

        char color[8];
        color[7] = '\0';
        if (operstate == 0)
            strncpy(color, "#F0544C", 8);
        else
            strncpy(color, "#4CF054", 8);
        printf("%s\n", color);
        if (ip != NULL)
            free(ip);
    }
    return 0;
}
