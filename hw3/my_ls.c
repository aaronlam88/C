/*
 * Author: Aaron Lam
 * SID: 92329177
 * Program: ICS53-HW3
 * Discription: implement linux command ls -lR, not file sorting, print sub dir with 4 space indent
 */

#include "my_ls.h"

static int space = 0;

int do_ls(const char *str_name)
{
    if(stat(str_name, &statbuf) == -1)
        return _print_err(str_name);
    return ls_int(str_name);
}

int ls_int(const char *str_name)
{
    if(statbuf.st_mode & S_IFREG)
        return ls_reg(str_name);
    else{
        printf("%s:\n", str_name);
        return ls_dir(str_name);
    }
}

int ls_reg(const char *reg_name)
{
    print_inf(reg_name);
    return 0;
}

/*
 * This function is more than 5 lines
 */
int ls_dir(const char *dir_name)
{
    char new_file[256];
    DIR  *dirp; 
    _safe_open(&dirp, dir_name);

    while ((dp = readdir(dirp)) != NULL) 
    {
        if(dp->d_name[0] == '.') continue; //skip "." and ".." directories
        print_space(space);
        _new_dir(new_file, dir_name, dp->d_name);     
        if(stat(new_file, &statbuf) == -1) continue; //skip unknow files
        _loop(new_file);
    }
    space > 3 ? space -=4: space;
    return 0;
}

void _loop(const char *new_file)
{
    print_inf(dp->d_name);
    if(statbuf.st_mode & S_IFDIR)
    {
        print_space(space+=4);          
        do_ls(new_file);            
    }
}

char *_new_dir(char *new_dir, const char *cur_dir, const char *sub_dir)
{
    strcpy(new_dir, cur_dir);
    strcat(new_dir, "/");
    strcat(new_dir, sub_dir);
    return new_dir;
}

int _print_err(const char *str)
{
    fprintf(stderr, "Error(%d) opening %s\n", errno, str);
    return errno;
}

int _safe_open(DIR **dirp, const char *dir_name)
{
    if (!(*dirp  = opendir(dir_name)))
        return _print_err(dir_name);
    return 0;
}

void print_space(int numb)
{
    int i;
    for(i = 0; i < numb; ++i)
        printf(" ");
}

void print_inf(const char *f_name)
{
    print_per();
    print_uid();
    print_gid();
    print_siz();
    print_tim(f_name);
}

void print_per()
{
    _print_isdir();
    _print_u_per();
    _print_g_per();
    _print_o_per();
    _print_n_lik();
}

void _print_isdir()
{
    printf( (S_ISDIR(statbuf.st_mode)) ? "d" : "-");
}

void _print_u_per()
{
    printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
    printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
    printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
}

void _print_g_per()
{
    printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
    printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
    printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
}

void _print_o_per()
{
    printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
    printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
    printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");
}

void _print_n_lik()
{
    printf(" %2jX", statbuf.st_nlink);
}

void print_uid()
{
    if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
        printf(" %s", pwd->pw_name);
    else
        printf(" %d", statbuf.st_uid);
}

void print_gid()
{
    if ((grp = getgrgid(statbuf.st_gid)) != NULL)
        printf("  %s", grp->gr_name);
    else
        printf("  %d", statbuf.st_gid);
}

void print_siz()
{
    printf("  %6jd", (intmax_t)statbuf.st_size);
}

void print_tim(const char *f_name)
{
    tm = localtime(&statbuf.st_mtime);
    strftime(date_time, sizeof(date_time), "%b %d %H:%M", tm);
    printf(" %s %s\n", date_time, f_name);
}