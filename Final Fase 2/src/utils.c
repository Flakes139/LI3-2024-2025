#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <ctype.h>

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
void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

char* format_output_string(const char* command, char* output) {
    if (!command || !output) return strdup("");
    
    char first_char = command[0];
    
    int has_s_format = 0;
    if (first_char >= '1' && first_char <= '9') {
        int i = 1;
        while (command[i] == ' ') i++; 
        has_s_format = (command[i] == 'S');
    }
    
    if (!has_s_format) return strdup(output);
    
    char* result = strdup(output);
    char* ptr = result;
    while ((ptr = strchr(ptr, ';')) != NULL) {
        *ptr = '=';
    }
    
    return result;
}

int count_constituents(char* list) {
    int count = 0;
    char* copy = strdup(list);
    char* str = copy;
    
    // Remove colchetes
    str[strlen(str)-1] = '\0';
    str++;
    
    // Conta vírgulas + 1 para obter número de elementos
    char* token = strtok(str, ",");
    while (token != NULL) {
        count++;
        token = strtok(NULL, ",");
    }
    
    free(copy);
    return count;
}