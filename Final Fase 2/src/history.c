#include "catalogHistory.h"
#include "history.h"
#include "utils.h" 
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "validation.h"

struct history 
{
    char* id;
    char* user_id;
    char* music_id;
    Timestamp *timestamp; 
    int duration;
    Platform platform;
};


void free_history(void *history_void) {
    History* history = (History*)history_void;
    
    free(history->id);
    free(history->user_id);
    free(history->music_id);

    if (history->timestamp) {
        free(history->timestamp);  // Libera o Timestamp
    }
    free(history);
}

History *allocate_history() {
    History *history = (History *)malloc(sizeof(History));
    history->id = NULL;
    history->user_id = NULL;
    history->music_id = NULL;
    history->timestamp = NULL;
    history->duration = 0;
    history->platform = MOBILE;
    return history;
}

char* get_history_id(History* history) {
    return strdup(history->id);
}

void set_history_id(History* history, char* id) {
    history->id = strdup(id);
}

char* get_history_user_id(History* history) {
    return strdup(history->user_id);
}

void set_history_user_id(History* history, char* user_id) {
    history->user_id = strdup(user_id);
}

char* get_history_music_id(History* history) {
    return strdup(history->music_id);
}

void set_history_music_id(History* history, char* music_id) {
    history->music_id = strdup(music_id);
}

Timestamp* get_history_timestamp(History* history) {
    if (!history->timestamp) return NULL;

    Timestamp* timestamp_copy = (Timestamp*)malloc(sizeof(Timestamp));
    *timestamp_copy = *(history->timestamp);  // Copia o conteúdo
    return timestamp_copy;
}

void set_history_timestamp(History* history, char* timestamp_str) {
    history->timestamp = (Timestamp*)malloc(sizeof(Timestamp));
    sscanf(timestamp_str, "%d/%d/%d %d:%d:%d",
           &history->timestamp->year, &history->timestamp->month, &history->timestamp->day,
           &history->timestamp->hour, &history->timestamp->minute, &history->timestamp->second);
}

int get_history_duration(History* history) {
    return history->duration;
}

void set_history_duration(History* history, int duration) {
    history->duration = duration;
}
Platform get_history_platform(History* history) {
    return history->platform;
}

void set_history_platform(History* history, Platform platform) {
    history->platform = platform;
}