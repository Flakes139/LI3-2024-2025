#ifndef UTILS_H
#define UTILS_H

int years_between(char* date1, char* date2);
int track_duration_to_int(char* duration);

int track_duration_to_int(char* duration);

char *int_to_track_duration(int duration);

int free_key_value_pair(gpointer key, gpointer value, gpointer user_data);

#endif