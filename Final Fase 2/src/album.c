#include "catalogAlbum.h"
#include "album.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "validation.h"

struct album 
{
    char* id;
    char* title;
    char* artist_id;
    int year;
    char* producers;
};

void free_album(void *album_void) {
    Album* album = (Album*)album_void;
    
    free(album->id);
    free(album->title);
    free(album->artist_id);
    free(album->producers);
    free(album);
}

Album *allocate_album() {
    Album *album = (Album *)malloc(sizeof(Album));
    album->id = NULL;
    album->title = NULL;
    album->artist_id = NULL;
    album->year = 0;
    album->producers = NULL;
    return album;
}

char* get_album_id(Album* album) {
    return strdup(album->id);
}

void set_album_id(Album* album, char* id) {
    album->id = strdup(id);
}

char* get_album_title(Album* album) {
    return strdup(album->title);
}

void set_album_title(Album* album, char* title) {
    album->title = strdup(title);
}

char* get_album_artist_id(Album* album) {
    return strdup(album->artist_id);
}

void set_album_artist_id(Album* album, char* artist_id) {
    album->artist_id = strdup(artist_id);
}

int get_album_year(Album* album) {
    return album->year;
}

void set_album_year(Album* album, int year) {
    album->year = year;
}

char* get_album_producers(Album* album) {
    return strdup(album->producers);
}

void set_album_producers(Album* album, char* producers) {
    album->producers = strdup(producers);
}
