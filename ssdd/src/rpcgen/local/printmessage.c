/* Simplified version of: http://docs.oracle.com/cd/E19683-01/816-1435/rpcgenpguide-21470/index.html*/

#include <stdio.h>
#include <stdlib.h>

int printmessage(char *msg) {
    printf("%s\n", msg);
    return 1;
}

int main(int argc, char *argv[]) {
    char *message = argv[1];

    if (!printmessage(message)) {
        fprintf(stderr, "%s: couldn't print your message\n", argv[0]);
        return 1;
    }

    printf("Message Delivered!\n");
    return 0;
}
