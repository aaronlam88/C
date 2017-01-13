/*
 * Author: Aaron Lam
 * SID: 92329177
 * Program: ICS53-HW3
 * Discription: implement linux command ls -lR, not file sorting, print sub dir with 4 space indent
 * main use for test my_ls.h my_ls.c
 */

#include "my_ls.h"

int main(int argc, char const *argv[])
{
    if (argc == 2)
        return do_ls(argv[1]);
    else 
        return do_ls(".");
    return 0;
}
