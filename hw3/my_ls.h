/*
 * Author: Aaron Lam
 * SID: 92329177
 * Program: ICS53-HW3
 * Discription: implement linux command ls -lR, not file sorting, print sub dir with 4 space indent
 */

#ifndef MY_LS_H
#define MY_LS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>

struct dirent  *dp;
struct stat     statbuf;
struct passwd  *pwd;
struct group   *grp;
struct tm      *tm;
char            date_time[24];

/*
 * int do_ls(const char *str_name):
 * input: const char *str_name --> a string the represent a file name or directory
 * do_ls will get stat of the the file, return error if can't get stat
 * do_ls will pass file stat to ls_int() to do decision making base of file is reg or dir
 */
int do_ls(const char *str_name);

/*
 * int ls_int(const char *str_name):
 * input: const char *str_name --> a string the represent a file name or directory
 * ls_int will check stat of the file and will call ls_reg() or ls_dir()
 * str_name is to be passed to print_info
 */
int ls_int(const char *str_name);

/*
 * int ls_reg(const char *reg_name):
 * input: const char *reg_name --> a string the represent a regular file name
 */
int ls_reg(const char *reg_name);

/*
 * int ls_dir(const char *reg_name):
 * input: const char *dir_name --> a string the represent a directory name
 */
int ls_dir(const char *dir_name);

/*
 * char *_new_dir(char *new_dir, const char *cur_dir, const char *sub_dir):
 * create new directory (new_dir) from current direct (cur_dir) and sub directory (sub_dir)
 */
char *_new_dir(char *new_dir, const char *cur_dir, const char *sub_dir);

/*
 * void print_space(int numb):
 * print space for indentation of sub directory
 */
void print_space(int numb);

/* 
 * void print_inf(const char *f_name):
 * input: const char *f_name -->file name which info need to be printed
 * print_inf call functions print_per(), print_uid(), print_gid(), print_siz(), print_tim(f_name) 
 * print_inf print out file name f_name file information
 * 
 */
void print_inf(const char *f_name);

/* 
 * void print_per():
 * input : none
 * print_per call codeline saving functions: _print_isdir(), _print_u_per(), _print_g_per()
 *                                           _print_o_per(), _print_n_lik
 * print_per print file is_directory, user, group, and other permission, and numb_link
 * print_per will not print new line at the end of the out put string
 */
void print_per();

/*
 * void print_uid():
 * print file user id
 */
void print_uid();

/*
 * void print_gid():
 * print group id
 */
void print_gid();

/*
 * void print_siz():
 * print file size in byte
 */
void print_siz();

/*
 * void print_tim(const char *f_name):
 * print last access time of the file
 */
void print_tim(const char *f_name);

/*
 * Functions for saving code line count
 */
int _print_err();
int _safe_open(DIR **dirp, const char *dir_name);
void _print_isdir();
void _print_u_per();
void _print_g_per();
void _print_o_per();
void _print_n_lik();
void _loop(const char *new_file);

#endif