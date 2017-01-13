#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    char *path = getenv("PATH");
    char  pathenv[strlen(path) + sizeof("PATH=")];
    sprintf(pathenv, "PATH=%s", path);
    char *envp[] = {pathenv, NULL};
    char *tests[] = {"ls", "-lR", NULL};
    execvpe(tests[0], tests, envp);
    fprintf(stderr, "failed to execute \"%s\"\n", tests[0]);
    return 1;
}