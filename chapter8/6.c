#include <stdio.h>

int main(int argc, char **argv, char **envp) {
    printf("Command-line arguments:\n");

    int i = 0;
    char *cli_args = argv[i];

    while(cli_args != NULL) {
        printf("argv[%d]: %s\n", i++, cli_args);
        cli_args = argv[i];
    }
    
    printf("Environment variables:\n");
    
    i = 0;
    char *env_vars = envp[i];

    while(env_vars != NULL) {
        printf("envp[%d]: %s\n", i++, env_vars);
        env_vars = envp[i];
    }

    return 0;
}
