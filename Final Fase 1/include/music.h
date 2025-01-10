#ifndef MUSIC_H
#define MUSIC_H

typedef struct music Music;

int create_and_store_music(char **user_data, void *music_catalog);
void free_music(void *music_void);

char* get_id(Music* music);
void set_id(Music* music, char* id);
char* get_title(Music* music);
void set_title(Music* music, char* title);
char* get_music_artist_id(Music* music);
void set_music_artist_id(Music* music, char* artist_id);
int get_duration(Music* music);
void set_duration(Music* music, int duration);
char* get_genre(Music* music);
void set_genre(Music* music, char* genre);
int get_year(Music* music);
void set_year(Music* music, int year);
char* get_lyrics(Music* music);
void set_lyrics(Music* music, char* lyrics);

#endif