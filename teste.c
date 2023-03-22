#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {
    for (int i = 0; envp[i] != NULL; i++) {
        printf("%s\n", envp[i]);
    }
    return 0;
}
// The envp array is terminated by a NULL pointer, so we can iterate over it until we find a NULL pointer to know when to stop.
