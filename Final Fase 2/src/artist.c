#include "catalogArtist.h"
#include "artist.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "validation.h"
#include "utils.h"

struct artist 
{
    char* id;
    char* name;
    char* description;
    float recipe_per_stream;
    char* id_constituent;
    char* country;
    Type type;
    int discography_duration;
};


void free_artist(void *artist_void) {
    Artist* artist = (Artist*)artist_void;
    
    free(artist->id);
    free(artist->name);
    free(artist->description);
    free(artist->id_constituent);
    free(artist->country);
    free(artist);
}

Artist *allocate_artist() {
    Artist *artist = (Artist *)malloc(sizeof(Artist));
    artist->id = NULL;
    artist->name = NULL;
    artist->description = NULL;
    artist->recipe_per_stream = 0;
    artist->id_constituent = NULL;
    artist->country = NULL;
    artist->type = INDIVIDUAL;
    artist->discography_duration = 0;
    return artist;
}


char* get_artist_id(Artist* artist) {
    return strdup(artist->id);
}

void set_artist_id(Artist* artist, char* id) {
    artist->id = strdup(id);
}

char* get_artist_name(Artist* artist) {
    return strdup(artist->name);
}

void set_artist_name(Artist* artist, char* name) {
    artist->name = strdup(name);
}

char* get_artist_description(Artist* artist) {
    return strdup(artist->description);
}

void set_artist_description(Artist* artist, char* description) {
    artist->description = strdup(description);
}

float get_artist_recipe_per_stream(Artist* artist) {
    return artist->recipe_per_stream;
}

void set_artist_recipe_per_stream(Artist* artist, float recipe_per_stream) {
    artist->recipe_per_stream = recipe_per_stream;
}

char* get_artist_id_constituent(Artist* artist) {
    return strdup(artist->id_constituent);
}

void set_artist_id_constituent(Artist* artist, char* id_constituent) {
    artist->id_constituent = strdup(id_constituent);
}

char* get_artist_country(Artist* artist) {
    return strdup(artist->country);
}

void set_artist_country(Artist* artist, char* country) {
    artist->country = strdup(country);
}

Type get_artist_type(Artist* artist) {
    return artist->type;
}

void set_artist_type(Artist* artist, Type type) {
    artist->type = type;
}

int get_artist_discography_duration(Artist* artist) {
    return artist->discography_duration;
}

void set_artist_discography_duration(Artist* artist, int discography_duration) {
    artist->discography_duration = discography_duration;
}