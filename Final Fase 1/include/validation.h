#ifndef VALIDATION_H
#define VALIDATION_H

int validate_user(char **fields, int field_count);
int validate_music(char **fields, int field_count);
int validate_artist(char **fields, int field_count);

int validate_date(const char *date);
int validate_duration(const char *duration);
int validate_email(const char *email);
int validate_subscription_type(const char *subscription);
int validate_list_format(const char *list);

#endif
