#include "user.h"
#include "users.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "validation.h"

struct user 
{
    char* username;
    char* email;
    char* first_name;
    char* last_name;
    char* birth_date;
    char* country;
    SubscriptionType subscription_type;
    char* liked_songs_ids;
};

int create_and_store_user(char **user_data, void *user_catalog){
    if (!validate_user(user_data, 8)) {
        return 1;
    }
    

    User* user = (User*)malloc(sizeof(User));

    set_username(user, user_data[0]);
    set_email(user, user_data[1]);
    set_first_name(user, user_data[2]);
    set_last_name(user, user_data[3]);
    set_birth_date(user, user_data[4]);
    set_country(user, user_data[5]);
    
    if(strcmp(user_data[6], "regular") == 0) {
        user->subscription_type = REGULAR;
    }
    else {
        user->subscription_type = PREMIUM;
    }

    set_liked_songs_ids(user, user_data[7]);

    insert_user((CatalogUser*)user_catalog, user);

    return 0;
}

void free_user(void *user_void){
    User* user = (User*)user_void;
    free(user->username);
    free(user->email);
    free(user->first_name);
    free(user->last_name);
    free(user->birth_date);
    free(user->country);
    free(user->liked_songs_ids);
    free(user);
}

char* get_username(User* user)
{
    return strdup(user->username);
}

void set_username(User* user, char* username)
{
    user->username = strdup(username);
}

char* get_email(User* user)
{
    return strdup(user->email);
}

void set_email(User* user, char* email)
{
    user->email = strdup(email);
}

char* get_first_name(User* user)
{
    return strdup(user->first_name);
}

void set_first_name(User* user, char* first_name)
{
    user->first_name = strdup(first_name);
}

char* get_last_name(User* user)
{
    return strdup(user->last_name);
}

void set_last_name(User* user, char* last_name)
{
    user->last_name = strdup(last_name);
}

char* get_birth_date(User* user)
{
    return strdup(user->birth_date);
}

void set_birth_date(User* user, char* birth_date)
{
    user->birth_date = strdup(birth_date);
}

char* get_country(User* user)
{
    return strdup(user->country);
}

void set_country(User* user, char* country)
{
    user->country = strdup(country);
}

SubscriptionType get_subscription_type(User* user)
{
    return user->subscription_type;
}

void set_subscription_type(User* user, SubscriptionType subscription_type)
{
    user->subscription_type = subscription_type;
}

char* get_liked_songs_ids(User* user)
{
    return strdup(user->liked_songs_ids);
}

void set_liked_songs_ids(User* user, char* liked_songs_ids)
{
    user->liked_songs_ids = strdup(liked_songs_ids);
}