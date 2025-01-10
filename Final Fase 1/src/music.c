#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "musics.h"
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
    char *lyrics;
};



int create_and_store_music(char **music_data, void *music_catalog){
    if (!validate_music(music_data, 4)) {
        return 1;
    }

    Music* music = (Music*)malloc(sizeof(Music));

    set_id(music, music_data[0]);
    set_title(music, music_data[1]);
    set_music_artist_id(music, music_data[2]);
    set_duration(music, track_duration_to_int(music_data[3]));
    set_genre(music, music_data[4]);
    set_year(music, atoi(music_data[5]));
    set_lyrics(music, music_data[6]);


    insert_music((CatalogMusic*)music_catalog, music);

    return 0;
}

void free_music(void *music_void){
    Music* music = (Music*)music_void;
    free(music->id);
    free(music->title);
    free(music->artist_id);
    free(music->genre);
    free(music->lyrics);
    free(music);
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

char* get_lyrics(Music* music)
{
    return strdup(music->lyrics);
}

void set_lyrics(Music* music, char* lyrics)
{
    music->lyrics = strdup(lyrics);
}