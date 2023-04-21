#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
# include <readline/readline.h>

static void func(int signal) {
    printf("Señal: %d\n", signal);
}

int main()
{
    char *input = malloc(300);
    signal(SIGINT, func); // Ctrl C //
    signal(SIGQUIT, func);// Ctrl \ //

    while (42) {
        input = readline("> ");
        printf("input: %s\n", input);
        // sleep(5);
    }
}