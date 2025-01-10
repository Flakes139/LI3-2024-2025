#include "user.h"
#include "catalogUser.h"
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

User *copy_user (User *user){
    User *new_user = allocate_user();
    set_username(new_user, user->username);
    set_email(new_user, user->email);
    set_first_name(new_user, user->first_name);
    set_last_name(new_user, user->last_name);
    set_birth_date(new_user, user->birth_date);
    set_country(new_user, user->country);
    set_subscription_type(new_user, get_subscription_type(user));
    set_liked_songs_ids(new_user, user->liked_songs_ids);
    return new_user;
}

User *allocate_user(){
    User *user = (User *)malloc(sizeof(User));
    user->username = NULL;
    user->email = NULL;
    user->first_name = NULL;
    user->last_name = NULL;
    user->birth_date = NULL;
    user->country = NULL;
    user->subscription_type = REGULAR;
    user->liked_songs_ids = NULL;
    return user;
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