#ifndef USERS_H
#define USERS_H

#include "user.h"
#include "users.h"

typedef struct catalogUser CatalogUser;

CatalogUser *initialize_users_catalog();

void free_users_catalog(CatalogUser *catalog);

void insert_user(CatalogUser *catalog, User *user);

User *catalog_get_user_by_username(CatalogUser *catalog, char *username);

#endif