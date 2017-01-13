#ifndef MUSIC_LIBRARY
#define MUSIC_LIBRARY

#define MAX_ARRAY_SIZE 1024
#define MAX_STRING_SIZE 256

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct song
{
    char title[40];
    char artist[40];
    char year[5];
}SONG;

typedef struct
{
    int size;
    SONG songsArray[MAX_ARRAY_SIZE];
}LIBRARY;

//Given structure
void read_command(char* option);
void evaluate_command(char option, char* fileName, LIBRARY* library);
void load_MusicLibrary(char* fileName, LIBRARY* library);
void store_MusicLibrary();
void print_MusicLibrary(LIBRARY* library);
int find_index_of_song_with_name(LIBRARY *library, char* songName);
void remove_song_from_MusicLibrary_by_name();
void add_song_to_MusicLibrary(SONG* song, LIBRARY* library);
char* write_song(SONG* song);//string --> song
void read_song(char* songData, SONG* song);//song --> string
FILE* open_file(char* fileName, char* mode);


//Add_on helper functions
bool is_valid_command(char* command, char* valid_command); // check if the option is valid command
bool is_valid_index(int index);
bool is_valid_insert_index(int index, int curr_array_size);
bool library_is_full(LIBRARY* library);
void shiftleft(LIBRARY* library, int at_index);
void shiftright(LIBRARY* library, int at_index);
void songcpy(SONG* dst, SONG* src);
int binarysearch(SONG* song, int low, int high, char* key, int* index);

//is_valid_command check to see if a command is valid
//input: command is a single character, valid_command is a lowercase string
bool is_valid_command(char* command, char* valid_command)
{
    *command = tolower(*command);
    if (strlen(command) != 1 || strchr(valid_command, command[0]) == NULL)
        return false;
    return true;
}

bool is_valid_index(int index)
{
    return index < MAX_ARRAY_SIZE && index > -1;
}

void shiftright(LIBRARY* library, int at_index)
{
    if(library->size + 1 > MAX_ARRAY_SIZE)
        return;
    for (int i = library->size; i > at_index; --i)
    {
        printf("%d\n", i);
        songcpy(&library->songsArray[i-1], &library->songsArray[i]);
    }
    ++library->size;
}

void shiftleft(LIBRARY* library, int at_index)
{
    for (int i = at_index; i < library->size; ++i)
    {
        songcpy(&library->songsArray[i], &library->songsArray[i + 1]);
    }
    --library->size;
}

void songcpy(SONG* dst, SONG* src)
{
    strcpy(dst->title, src->title);
    strcpy(dst->artist, src->artist);
    strcpy(dst->year, src->year);
}

//functions defintions:
FILE* open_file(char* fileName, char* mode)
{
    FILE* file = fopen(fileName, mode);
    if (file == NULL)
    {
        fprintf(stderr, "Can't open input file \"%s\"!\n", fileName);
        exit(1);
    }
    return file;
}

void load_MusicLibrary(char* fileName, LIBRARY *library)
{
    char buff[MAX_STRING_SIZE];
    SONG song;
    SONG* songsArray = library->songsArray;

    FILE* input = open_file(fileName, "r");
    while (fgets(buff, MAX_STRING_SIZE, input) != NULL)
    {
        read_song(buff, &song);
        add_song_to_MusicLibrary(&song, library);
    }
}

void add_song_to_MusicLibrary(SONG* song, LIBRARY* library)
{
    int index;
    for(;library->size == 0; ++library->size)
        songcpy(&library->songsArray[0], song);
    if(binarysearch(library->songsArray, 0, library->size, song->title, &index))
    {
        shiftright(library, index);
        songcpy(&library->songsArray[index], song);
    }
}

int find_index_of_song_with_name(LIBRARY *library, char* songName)
{
    int index = binarysearch(library->songsArray, 0, library->size, songName, NULL)
    if(index != -1)
        write_song(&library[index])
    else
        printf("%s not found in database\n", songName);
}

int binarysearch(SONG* songsArray, int low, int high, char* key, int* index)
{
    for(int mid = (low+high)/2; low < high; *index = low){
        if(strcmp(songsArray[mid].title, key) == 0)
            return mid;
        strcmp(songsArray[mid].title, key) < 0 ? (low = mid + 1) : (high = mid -1);
    }
}

void print_MusicLibrary(LIBRARY *library)
{
    for (int i = 0; i < library->size; ++i)
    {
        write_song(&library->songsArray[i]);
    }
}

//read_command read user's input command and eveluate if it's valid or not
//keep asking user input utill get valid command
void read_command(char* option)
{
    for (scanf("%s", option); !is_valid_command(option, "ipdlq"); scanf("%s", option))
        printf("\"%s\" is not a valid input!\n", option);
    fflush(stdin);
}

//evaluate_command evaluate user's command and call the appropirate function
void evaluate_command(char option, char* fileName, LIBRARY *library)
{
    switch (option)
    {
    case 'i': //add_song_to_MusicLibrary();
        break;
    case 'p': print_MusicLibrary(library);
        break;
    case 'd': //remove_song_from_MusicLibrary_by_name();
        break;
    case 'l': //find_index_of_song_with_name();
        break;
    case 'q': //store_MusicLibrary();
        break;
    }
}

void read_song(char* songData, SONG* song)
{
    strcpy(song->title, strtok(songData, "|"));
    strcpy(song->artist, strtok(NULL, "|"));
    strcpy(song->year, strtok(NULL, "| \n"));
}

char* write_song(SONG* song)
{
    printf("%s|%s|%s|\n", song->title, song->artist, song->year);
}

int main(int argc, char *argv[])
{
    char option;
    LIBRARY library;
    char fileName[MAX_STRING_SIZE];
    library.size = 0;

    argc == 1 ? strcpy(fileName, "myMusic.txt") : strcpy(fileName, argv[1]);
    load_MusicLibrary(fileName, &library);
    for (read_command(&option); option != 'q'; read_command(&option))
        evaluate_command(option, fileName, &library);

    return 0;
}
#endif