#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    char *username = "test";

    struct passwd *pwd = calloc(1, sizeof(struct passwd));
    if(pwd == NULL)
    {
        fprintf(stderr, "Failed to allocate struct passwd for getpwnam_r.\n");
        exit(1);
    }
    size_t buffer_len = sysconf(_SC_GETPW_R_SIZE_MAX) * sizeof(char);
    char *buffer = malloc(buffer_len);
    if(buffer == NULL)
    {
        fprintf(stderr, "Failed to allocate buffer for getpwnam_r.\n");
        exit(2);
    }
    getpwnam_r(username, pwd, buffer, buffer_len, &pwd);
    if(pwd == NULL)
    {
        fprintf(stderr, "getpwnam_r failed to find requested entry.\n");
        exit(3);
    }
    printf("uid: %d\n", pwd->pw_uid);
    printf("gid: %d\n", pwd->pw_gid);

    free(pwd);
    free(buffer);

    return 0;
}