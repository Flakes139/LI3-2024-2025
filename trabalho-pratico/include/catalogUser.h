/** \file catalogUser.h
 *  \brief Funções para gerir o catálogo de usuários.
 *
 * Este ficheiro contém funções para manipular e gerir um catálogo de usuários.
 */

#ifndef CATALOGUSER_H
#define CATALOGUSER_H

#include "user.h"
#include "catalogUser.h"
#include <glib.h>

/** \struct catalogUser
 *  \brief Representa um catálogo de usuários.
 */
typedef struct catalogUser CatalogUser;

/** \brief Inicializa o catálogo de usuários.
 *  \return Ponteiro para o catálogo inicializado.
 */
CatalogUser *initialize_users_catalog();

/** \brief Liberta a memória do catálogo de usuários.
 *  \param catalog Ponteiro para o catálogo a ser libertado.
 */
void free_users_catalog(CatalogUser *catalog);

/** \brief Insere um usuário no catálogo.
 *  \param catalog Ponteiro para o catálogo.
 *  \param user Ponteiro para o usuário a ser inserido.
 */
void insert_user(CatalogUser *catalog, User *user);

/** \brief Retorna um usuário pelo nome de usuário.
 *  \param catalog Ponteiro para o catálogo de usuários.
 *  \param username Nome de usuário a procurar.
 *  \return Ponteiro para o usuário encontrado ou NULL se não existir.
 */
User *catalog_get_user_by_username(CatalogUser *catalog, char *username);

/** \brief Verifica se um usuário existe no catálogo.
 *  \param username Nome de usuário a ser verificado.
 *  \param catalog Ponteiro para o catálogo.
 *  \return 1 se o usuário existir, 0 caso contrário.
 */
int exists_user(char *username, CatalogUser *catalog);

/** \brief Obtém os usuários dentro de um intervalo de idades.
 *  \param catalog Ponteiro para o catálogo de usuários.
 *  \param min_age Idade mínima.
 *  \param max_age Idade máxima.
 *  \return Ponteiro para um array de usuários dentro da faixa etária.
 */
GPtrArray* get_users_by_age_range(CatalogUser *catalog, int min_age, int max_age);

/** \brief Obtém as músicas gostadas pelos usuários.
 *  \param users Array de usuários.
 *  \return Ponteiro para um array de músicas gostadas.
 */
GPtrArray* get_liked_songs_from_users(GPtrArray *users);

#endif