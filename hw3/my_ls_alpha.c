/**
 * Program: my_ls
 * Description: a C program that do what Linux ls do
 * Author: Aaron Lam
 * ID: 92329177
 * Class: ICS53
**/
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>

int do_ls(const char *dirName)
{
    DIR *dirp;
    struct dirent *direntp;
    if (!(dirp  = opendir(dirName)))
    {
        fprintf(stderr, "Error(%d) opening %s\n", errno, dirName);
        return errno;
    }
    while ((direntp = readdir(dirp)))
        printf("%s\n", direntp->d_name);  /* use stat here to find attributes of file */
    closedir(dirp);
}

// char *getUserName(uid_t uid) /* how to convert a user ID to a user name */
// {
//     struct passwd *pw = getpwuid(uid);
//     return pw->pw_name ? pw->pw_name : "";
// }

int main(int argc, char const *argv[])
{
    do_ls(argv[1]);
    // DIR *dir;
    // struct dirent *ent;
    // if ((dir = opendir (argv[1])) != NULL) {
    // /* print all the files and directories within directory */
    //     while ((ent = readdir (dir)) != NULL) {
    //         printf ("%s\n", ent->d_name);
    //     }
    //     closedir (dir);
    // } else {
    //     /* could not open directory */
    //     perror ("");
    //     exit(EXIT_FAILURE);
    // }
    return 0;
}