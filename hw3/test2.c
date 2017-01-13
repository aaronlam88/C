#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <fcntl.h> 

struct dirent  *dp;
struct stat     statbuf;
struct passwd  *pwd;
struct group   *grp;
struct tm      *tm;
char            datestring[256];

/* Loop through directory entries. */
int test (const char *dirName){

    DIR *dirp;
    struct dirent *direntp;
    if (!(dirp  = opendir(dirName)))
    {
        fprintf(stderr, "Error(%d) opening %s\n", errno, dirName);
        return errno;
    }
    while ((dp = readdir(dirp)) != NULL) {

        if(dp->d_name[1] == '.')
            continue;

    /* Get entry's information. */
        if(stat(dp->d_name, &statbuf) == -1)
            continue;


    /* Print out type, permissions, and number of links. */
        // printf("%10.10s", sperm (statbuf.st_mode));
        printf( (S_ISDIR(statbuf.st_mode)) ? "d" : "-");
        printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
        printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
        printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
        printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
        printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
        printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
        printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
        printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
        printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");
        printf(" %2d", statbuf.st_nlink);


    /* Print out owner's name if it is found using getpwuid(). */
        if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
            printf(" %s", pwd->pw_name);
        else
            printf(" %d", statbuf.st_uid);


    /* Print out group name if it is found using getgrgid(). */
        if ((grp = getgrgid(statbuf.st_gid)) != NULL)
            printf("  %s", grp->gr_name);
        else
            printf("  %d", statbuf.st_gid);


    /* Print size of file. */
        printf("  %5jd", (intmax_t)statbuf.st_size);


        tm = localtime(&statbuf.st_mtime);


    /* Get localized date string. */
        // strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
        strftime(datestring, sizeof(datestring), "%b %d %H:%M", tm);

        printf(" %s %s\n", datestring, dp->d_name);
    }
    return 0;
}
int main(int argc, char const *argv[])
{
    test(argv[1]);
    return 0;
}