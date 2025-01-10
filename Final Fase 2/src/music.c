#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "catalogMusic.h"
#include "music.h"
#include "utils.h"
#include "validation.h"

struct music 
{
    char *id;
    char *title;
    char* artist_id;
    int duration;       
    char *genre;
    int year;
};


void free_music(void *music_void){
    Music* music = (Music*)music_void;
    free(music->id);
    free(music->title);
    free(music->artist_id);
    free(music->genre);
    free(music);
}

Music *allocate_music(){
    Music *music = (Music *)malloc(sizeof(Music));
    music->id = NULL;
    music->title = NULL;
    music->artist_id = NULL;
    music->duration = 0;
    music->genre = NULL;
    music->year = 0;
    return music;
}

char* get_id(Music* music)
{
    return strdup(music->id);
}

void set_id(Music* music, char* id)
{
    music->id = strdup(id);
}

char* get_title(Music* music)
{
    return strdup(music->title);
}

void set_title(Music* music, char* title)
{
    music->title = strdup(title);
}

char* get_music_artist_id(Music* music)
{
    return strdup(music->artist_id);
}

void set_music_artist_id(Music* music, char* artist_id)
{
    music->artist_id = strdup(artist_id);
}

int get_duration(Music* music)
{
    return music->duration;
}

void set_duration(Music* music, int duration)
{
    music->duration = duration;
}

char* get_genre(Music* music)
{
    return strdup(music->genre);
}

void set_genre(Music* music, char* genre)
{
    music->genre = strdup(genre);
}

int get_year(Music* music)
{
    return music->year;
}

void set_year(Music* music, int year)
{
    music->year = year;
}
