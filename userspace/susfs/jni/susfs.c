#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/prctl.h>

#define KERNEL_SU_OPTION 0xDEADBEEF
#define CMD_SUSFS_SHOW_VERSION 0x555e1
#define CMD_SUSFS_SHOW_VARIANT 0x555e3

int main(int argc, char *argv[]) {
    int error = -1;
    char version[16];
    char variant[16];

    // Check for arguments
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <version|support>\n", argv[0]);
        return 1;
    }

    // If 'version' is given, show version
    if (strcmp(argv[1], "support") == 0) {
        prctl(KERNEL_SU_OPTION, CMD_SUSFS_SHOW_VERSION, version, NULL, &error);
        if (!error) {
            if (version[0] == 'v') {
                printf("Supported\n");
            }
        } else {
            printf("Unsupported\n");
        }
        
    } else if (strcmp(argv[1], "version") == 0) {
        prctl(KERNEL_SU_OPTION, CMD_SUSFS_SHOW_VERSION, version, NULL, &error);
        if (!error) {
            printf("%s\n", version);
        } else {
            printf("Invalid\n");
        }
    } else if (strcmp(argv[1], "variant") == 0) {
        prctl(KERNEL_SU_OPTION, CMD_SUSFS_SHOW_VARIANT, variant, NULL, &error);
        if (!error) {
            printf("%s\n", variant);
        } else {
            printf("Invalid\n");
        }
    } else {
        fprintf(stderr, "Invalid argument: %s\n", argv[1]);
        return 1;
    }

    return 0;
}