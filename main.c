#include <stdio.h>
#include <unistd.h>
#include "repl.h"

int main(int argc, char **argv) {
    
    char *username = getlogin();
    if (username == NULL) {
        printf("Problem with username has occured!");
    }

    if (argc == 1) {
        printf("Hello %s! Feel free to type in commands\n", username);
        startRepl();
    }


    return 0;
}
