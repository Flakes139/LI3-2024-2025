#ifndef USER_H
#define USER_H

typedef struct user User;

typedef enum {
    REGULAR = 0,
    PREMIUM = 1,
} SubscriptionType;

int create_and_store_user(char **user_data, void *user_catalog);

void free_user(void *user_ptr);

char* get_username(User* user);

void set_username(User* user, char* username);

char* get_email(User* user);

void set_email(User* user, char* email);

char* get_first_name(User* user);

void set_first_name(User* user, char* first_name);

char* get_last_name(User* user);

void set_last_name(User* user, char* last_name);

char* get_birth_date(User* user);

void set_birth_date(User* user, char* birth_date);

char* get_country(User* user);

void set_country(User* user, char* country);

SubscriptionType get_subscription_type(User* user);

void set_subscription_type(User* user, SubscriptionType subscription_type);

char* get_liked_songs_ids(User* user);

void set_liked_songs_ids(User* user, char* liked_songs_ids);

#endif