#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

const char *FILENAME = "/etc/hostname";

int main()
{
    char *username = NULL;
    char *user = getenv("USER");

    if (user != NULL) {
        username = (char *)malloc(strlen(user) * sizeof(char));
        strncpy(username, user, strlen(user));
    } else {
        username = (char *)malloc(1 * sizeof(char));
        username[0] = '\0';
    }

    char *hostname = NULL;
    if (access(FILENAME, F_OK) != -1) {
        FILE *file = fopen(FILENAME, "r");
        if (file != NULL) {
            size_t len;
            getline(&hostname, &len, file);
            hostname[strlen(hostname) - 1] = '\0';
            fclose(file);
        }
    }

    if (hostname == NULL) {
        hostname = (char *)malloc(1 * sizeof(char));
        hostname[0] = '\0';
    }

    printf("%s@%s\n", username, hostname);
    printf("%s@%s\n", username, hostname);

    if (username != NULL)
        free(username);

    if (hostname != NULL)
        free(hostname);
}
