#include <string.h>
#include <stdlib.h>
#include "validation.h"


int validate_user(char **fields, int field_count){
    if (field_count < 8) return 0; 
    if (!validate_date(fields[4])) return 0;  
    if (!validate_email(fields[1])) return 0;  
    if (!validate_subscription_type(fields[6])) return 0;  
    if (!validate_list_format(fields[7])) return 0;  
    return 1;
}


int validate_music(char **fields, int field_count) {
    if (field_count < 4) return 0;  
    if (!validate_duration(fields[3])) return 0;  
    if (!validate_list_format(fields[2])) return 0; 
    return 1;
}

int validate_artist(char **fields, int field_count){
    if (field_count < 6) return 0; 
    if (!validate_list_format(fields[4])) return 0; 
    if (strcmp(fields[6], "individual") == 0 && strlen(fields[4]) > 2) return 0;
    return 1;
}

int validate_date(const char *date){
    if (strlen(date) != 10 || date[4] != '/' || date[7] != '/') {
        return 0;  
    }
    
    int month = atoi(date + 5);
    int day = atoi(date + 8);

    
    if (month < 1 || month > 12) return 0;
    if (day < 1 || day > 31) return 0;

    return 1;
}

int validate_duration(const char *duration) {
    if (strlen(duration) != 8 || duration[2] != ':' || duration[5] != ':') {
        return 0; 
    }

    int hours = atoi(duration);
    int minutes = atoi(duration + 3);
    int seconds = atoi(duration + 6);

    
    if (hours < 0 || hours > 99) return 0;
    if (minutes < 0 || minutes >= 60) return 0;
    if (seconds < 0 || seconds >= 60) return 0;

    if (hours == 0 && minutes == 0 && seconds == 0) return 0;

    return 1;
}

int validate_email(const char *email) {
    const char *at = strchr(email, '@');
    if (!at) return 0;  

    const char *dot = strchr(at + 1, '.');
    if (!dot || dot == at + 1) return 0; 

    
    if (strlen(dot + 1) < 2 || strlen(dot + 1) > 3) return 0;

    for (const char *p = email; p < at; p++) {
        if (!((*p >= 'a' && *p <= 'z') || (*p >= '0' && *p <= '9'))){
            return 0;
        }
    }

    for (const char *p = at + 1; p < dot; p++) {
        if (!((*p >= 'a' && *p <= 'z') || (*p >= '0' && *p <= '9'))){
            return 0;
        }
    }

    return 1;
}

int validate_subscription_type(const char *subscription){
    if (strcmp(subscription, "normal") == 0 || strcmp(subscription, "premium") == 0){
        return 1;
    }
    return 0;
}

int validate_list_format(const char *list){
    size_t len = strlen(list);
    if (len > 1 && list[0] == '[' && list[len - 1] == ']'){
        return 1;
    }
    return 0;
}