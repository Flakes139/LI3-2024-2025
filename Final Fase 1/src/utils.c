#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

// Calcula a diferença de anos entre duas datas
int years_between(char* date1, char* date2) {
    int year1, month1, day1;
    int year2, month2, day2;

    sscanf(date1, "%d/%d/%d", &year1, &month1, &day1);

    sscanf(date2, "%d/%d/%d", &year2, &month2, &day2);

    int year_diff = year2 - year1;

    if (month2 < month1 || (month2 == month1 && day2 < day1)) {
        year_diff--;
    }

    return year_diff;
}

int track_duration_to_int(char* duration) {
    int hours, minutes, seconds;
    sscanf(duration, "%d:%d:%d", &hours, &minutes, &seconds);
    return hours * 3600 + minutes * 60 + seconds;
}


char *int_to_track_duration(int duration) {
    int hours = duration / 3600;
    int minutes = (duration % 3600) / 60;
    int seconds = duration % 60;

    char *track_duration = (char *)malloc(16 * sizeof(char));
    if (track_duration == NULL) {
        return NULL;
    }

    snprintf(track_duration, 16, "%02d:%02d:%02d", hours, minutes, seconds);

    return track_duration;
}

int free_key_value_pair(gpointer key, gpointer value, gpointer user_data) {
    free(key);
    free(value);

    return 0;
}

