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

static int size = 0;

//Given structure
void read_command(char* option);
void evaluate_command(char option, char* fileName, SONG* library);
void load_MusicLibrary(char* fileName, SONG* library);
void store_MusicLibrary(char* fileName, SONG* library);
void print_MusicLibrary(SONG* library);
void find_index_of_song_with_name(SONG *library);
void remove_song_from_MusicLibrary_by_name();
void add_song_to_MusicLibrary(SONG* library);
void write_song(SONG* song);
void read_song(char* songData, SONG* song);
FILE* open_file(char* fileName, char* mode);


//Add_on helper functions
bool is_valid_command(char* command, char* valid_command); 

int binarysearch(SONG* song, int low, int high, char* key);


bool is_valid_command(char* command, char* valid_command)
{
    *command = tolower(*command);
    if (strlen(command) != 1 || strchr(valid_command, command[0]) == NULL)
        return false;
    return true;
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

void load_MusicLibrary(char* fileName, SONG *library)
{
    char buff[MAX_STRING_SIZE];
    SONG song;
    FILE* input = open_file(fileName, "r");
    
    while (fgets(buff, MAX_STRING_SIZE, input) != NULL)
    {
        read_song(buff, &song);
        songcpy(&library[size++], &song);
    }
    fclose(input);
}

char* getInput(char* promp, char * str)
{
    printf("%s", promp);
    fgets(str, MAX_STRING_SIZE, stdin);
    str[strlen(str)-1] = '\0';
    return str;
}

void getSong(SONG* song)
{   
    char title[40], artist[40], year[5];
    strcpy(song->title, getInput("Title: ", title));
    strcpy(song->artist, getInput("Artist: ", artist));
    strcpy(song->year, getInput("Year Published: ", year));
}

void rightshift(SONG* library, int at_index)
{
    for (int i = size; i > at_index; --i)
    {
        songcpy(&library[i], &library[i-1]);
    }
}

void leftshift(SONG* library, int at_index)
{
    if(size == 1)
        return;
    for(int i = size-1; i > at_index; --i)
    {
        songcpy(&library[i-1], &library[i]);
    }
}

void insertSong(SONG* song, SONG* library, int at_index)
{
    rightshift(library, at_index);
    songcpy(&library[at_index], song);
    ++size;
}

void deleteSong(SONG* library, int at_index)
{
    leftshift(library, at_index);
    --size;
}

void add_song_to_MusicLibrary(SONG* library)
{
    SONG song;
    getSong(&song);
    int index = binarysearch(library, 0, size-1, song.title);

    if(strcmp(library[index].title, song.title) != 0)
        insertSong(&song, library, index);

}
void show_find(SONG* library, char* title, int index)
{
    if((strcmp(library[index].title, title)) == 0)
        write_song(&library[index]);
    else
        printf("Song not found!\n");
}

void find_index_of_song_with_name(SONG *library)
{
    char title[40];
    getInput("Song Title: ", title);
    int index = binarysearch(library, 0, size-1, title);
    show_find(library, title, index);
}

int binarysearch(SONG* library, int low, int high, char* key)
{
    int mid;
    for(mid = (low+high)/2; low <= high; mid = (low+high)/2)
    {
        if(strcmp(library[mid].title, key) == 0)
            return mid;
        strcmp(library[mid].title, key) < 0 ? (low = mid + 1) : (high = mid -1);
    }
    return mid;
}

void remove_song_from_MusicLibrary_by_name(SONG* library)
{
    char title[40];
    getInput("Song Title: ", title);
    int index =binarysearch(library, 0, size-1, title);
    if(strcmp(library[index].title, title) == 0)
        deleteSong(library, index);
}

void print_MusicLibrary(SONG *library)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%d. ", i+1);
        write_song(&library[i]);
    }
}

//read_command read user's input command and eveluate if it's valid or not
//keep asking user input utill get valid command
void read_command(char* option)
{
    for (getInput("command: ", option); !is_valid_command(option, "ipdlq"); getInput("command: ", option))
        printf("\"%s\" is not a valid input!\n", option);
}

void store_MusicLibrary(char* fileName, SONG* library)
{
    FILE* output = open_file(fileName, "w");
    for(int i = 0; i < size; ++i)
        fprintf(output, "%s|%s|%s|\n", library[i].title, library[i].artist, library[i].year);
    fclose(output);
}

//evaluate_command evaluate user's command and call the appropirate function
void evaluate_command(char option, char* fileName, SONG* library)
{
    switch (option)
    {
    case 'i': add_song_to_MusicLibrary(library);
        break;
    case 'p': print_MusicLibrary(library);
        break;
    case 'd': remove_song_from_MusicLibrary_by_name(library);
        break;
    case 'l': find_index_of_song_with_name(library);
        break;
    case 'q':
        break;
    }
}

void read_song(char* songData, SONG* song)
{
    strcpy(song->title, strtok(songData, "|"));
    strcpy(song->artist, strtok(NULL, "|"));
    strcpy(song->year, strtok(NULL, "| \n"));
}

void write_song(SONG* song)
{
    printf("%s|%s|%s|\n", song->title, song->artist, song->year);
}

int main(int argc, char *argv[])
{
    char option[10];
    SONG library[MAX_ARRAY_SIZE];
    char fileName[MAX_STRING_SIZE];
    argc == 1 ? strcpy(fileName, "myMusic.txt") : strcpy(fileName, argv[1]);

    load_MusicLibrary(fileName, library);
    for (read_command(option); option[0] != 'q'; read_command(option))
        evaluate_command(option[0], fileName, library);
    store_MusicLibrary(fileName, library);
    return 0;
}
#endif