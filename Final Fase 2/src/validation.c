#include <string.h>
#include <stdlib.h>
#include "validation.h"
#include "utils.h"
#include <stdio.h>

int validate_user(char **fields, int field_count)
{
    if (field_count < 8)
        return 0;
    if (!validate_date(fields[4]))
        return 0;
    if (!validate_email(fields[1]))
        return 0;
    if (!validate_subscription_type(fields[6]))
        return 0;
    if (!validate_list_format(fields[7]))
        return 0;
    return 1;
}

int validate_music(char **fields, int field_count)
{
    int duration = validate_duration(fields[4]);
    int list = validate_list_format(fields[2]);

    return field_count == 8 && duration && list;
}

int validate_artist(char **fields, int field_count)
{
    int list = validate_list_format(fields[4]);
    int artist = validate_artist_type(fields[6], fields[4]);

    return field_count == 7 && list && artist;
}
int validate_album(char **fields, int field_count)
{   
    int list = validate_list_format(fields[2]);
    int list2 = validate_list_format(fields[4]);

    return field_count == 5 && list && list2;
}
int validate_history(char **fields, int field_count)
{
    if (field_count < 5)
        return 0;
    if (!validate_timestamp(fields[3]))
        return 0;
    if (!validate_platform(fields[5]))
        return 0;
    return 1;
}

int validate_date(const char *date)
{
    const int current_year = 2024;
    if (strlen(date) != 10 || date[4] != '/' || date[7] != '/')
    {
        return 0;
    }

    int month = atoi(date + 5);
    int day = atoi(date + 8);
    int year = atoi(date);

    if (month < 1 || month > 12)
        return 0;
    if (day < 1 || day > 31)
        return 0;
    if (year < 1900 || year > current_year)
        return 0;

    return 1;
}

int validate_duration(const char *duration)
{

    if (strlen(duration) != 8 || duration[2] != ':' || duration[5] != ':')
    {
        return 0;
    }

    int hours = atoi(duration);
    int minutes = atoi(duration + 3);
    int seconds = atoi(duration + 6);

    if (hours < 0 || hours > 99)
        return 0;
    if (minutes < 0 || minutes >= 60)
        return 0;
    if (seconds < 0 || seconds >= 60)
        return 0;

    if (hours == 0 && minutes == 0 && seconds == 0)
        return 0;

    return 1;
}

int validate_email(const char *email)
{

    const char *at = strchr(email, '@');
    if (!at)
        return 0;

    const char *dot = strchr(at + 1, '.');
    if (!dot || dot == at + 1)
        return 0;

    if (strlen(dot + 1) < 2 || strlen(dot + 1) > 3)
        return 0;

    for (const char *p = email; p < at; p++)
    {

        if (!((*p >= 'a' && *p <= 'z') || (*p >= '0' && *p <= '9')))
        {
            return 0;
        }
    }

    for (const char *p = at + 1; p < dot; p++)
    {
        if (!((*p >= 'a' && *p <= 'z') || (*p >= '0' && *p <= '9')))
        {
            return 0;
        }
    }

    return 1;
}

int validate_subscription_type(const char *subscription)
{
    if (strcmp(subscription, "normal") == 0 || strcmp(subscription, "premium") == 0)
    {
        return 1;
    }
    return 0;
}

int validate_list_format(const char *list)
{
    size_t len = strlen(list);
    if (len > 1 && list[0] == '[' && list[len - 1] == ']')
    {
        return 1;
    }
    return 0;
}

int validate_timestamp(const char *timestamp)
{
    if (strlen(timestamp) != 19 || timestamp[4] != '/' || timestamp[7] != '/' || timestamp[10] != ' ' || timestamp[13] != ':' || timestamp[16] != ':')
        return 0;

    int year = atoi(timestamp);
    int month = atoi(timestamp + 5);
    int day = atoi(timestamp + 8);
    int hour = atoi(timestamp + 11);
    int minute = atoi(timestamp + 14);
    int second = atoi(timestamp + 17);

    if (year < 0)
        return 0;
    if (month < 1 || month > 12)
        return 0;
    if (day < 1 || day > 31)
        return 0;
    if (hour < 0 || hour > 23)
        return 0;
    if (minute < 0 || minute > 59)
        return 0;
    if (second < 0 || second > 59)
        return 0;

    return 1;
}

int validate_platform(const char *platform)
{
    char temp[20];
    strncpy(temp, platform, sizeof(temp) - 1);
    temp[sizeof(temp) - 1] = '\0';

    to_lowercase(temp);

    if (strcmp(temp, "mobile") == 0 || strcmp(temp, "desktop") == 0)
    {
        return 1;
    }
    return 0;
}

int validate_artist_type(const char *artist_type, const char *id_constituent)
{
    char temp[20];
    strncpy(temp, artist_type, sizeof(temp) - 1);
    temp[sizeof(temp) - 1] = '\0';

    to_lowercase(temp);

    if ((strcmp(temp, "individual") == 0 && strcmp(id_constituent, "[]") == 0) || (strcmp(temp, "group") == 0 && strcmp(id_constituent, "[]") != 0))
    {
        return 1;
    }
    return 0;
}