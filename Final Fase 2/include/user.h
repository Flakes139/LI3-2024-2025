/** \file user.h
 *  \brief Funções e estrutura para manipular usuários.
 *
 * Este arquivo contém funções e definições para gerenciar usuários no sistema.
 */

#ifndef USER_H
#define USER_H

/** \struct user
 *  \brief Representa um usuário com as suas informações.
 */
typedef struct user User;

/** \enum SubscriptionType
 *  \brief Tipos de subscrição disponíveis (REGULAR ou PREMIUM).
 */
typedef enum {
    REGULAR = 0,
    PREMIUM = 1,
} SubscriptionType;

/** \brief Liberta a memória de um usuário.
 *  \param user_ptr Ponteiro para o usuário a ser libertado.
 */
void free_user(void *user_ptr);

/** \brief Cria uma cópia de um usuário.
 *  \param user Ponteiro para o usuário a ser copiado.
 *  \return Ponteiro para a cópia criada.
 */
User *copy_user (User *user);

/** \brief Aloca memória para um novo usuário.
 *  \return Ponteiro para o usuário criado.
 */
User *allocate_user();

/** \brief Obtém o username de um usuário.
 *  \param user Ponteiro para o usuário.
 *  \return String com o username do usuário.
 */
char* get_username(User* user);

/** \brief Define o username de um usuário.
 *  \param user Ponteiro para o usuário.
 *  \param username String com o novo username.
 */
void set_username(User* user, char* username);

/** \brief Obtém o email de um usuário.
 *  \param user Ponteiro para o usuário.
 *  \return String com o email do usuário.
 */
char* get_email(User* user);

/** \brief Define o email de um usuário.
 *  \param user Ponteiro para o usuário.
 *  \param email String com o novo email.
 */
void set_email(User* user, char* email);

/** \brief Obtém o primeiro nome de um usuário.
 *  \param user Ponteiro para o usuário.
 *  \return String com o primeiro nome do usuário.
 */
char* get_first_name(User* user);

/** \brief Define o primeiro nome de um usuário.
 *  \param user Ponteiro para o usuário.
 *  \param first_name String com o novo primeiro nome.
 */
void set_first_name(User* user, char* first_name);

/** \brief Obtém o último nome de um usuário.
 *  \param user Ponteiro para o usuário.
 *  \return String com o último nome do usuário.
 */
char* get_last_name(User* user);

/** \brief Define o último nome de um usuário.
 *  \param user Ponteiro para o usuário.
 *  \param last_name String com o novo último nome.
 */
void set_last_name(User* user, char* last_name);

/** \brief Obtém a data de nascimento de um usuário.
 *  \param user Ponteiro para o usuário.
 *  \return String com a data de nascimento do usuário.
 */
char* get_birth_date(User* user);

/** \brief Define a data de nascimento de um usuário.
 *  \param user Ponteiro para o usuário.
 *  \param birth_date String com a nova data de nascimento.
 */
void set_birth_date(User* user, char* birth_date);

/** \brief Obtém o país de um usuário.
 *  \param user Ponteiro para o usuário.
 *  \return String com o país do usuário.
 */
char* get_country(User* user);

/** \brief Define o país de um usuário.
 *  \param user Ponteiro para o usuário.
 *  \param country String com o novo país.
 */
void set_country(User* user, char* country);

/** \brief Obtém o tipo de subscrição de um usuário.
 *  \param user Ponteiro para o usuário.
 *  \return Tipo de subscrição do usuário (REGULAR ou PREMIUM).
 */
SubscriptionType get_subscription_type(User* user);

/** \brief Define o tipo de subscrição de um usuário.
 *  \param user Ponteiro para o usuário.
 *  \param subscription_type Novo tipo de subscrição do usuário.
 */
void set_subscription_type(User* user, SubscriptionType subscription_type);

/** \brief Obtém os IDs das músicas gostadas por um usuário.
 *  \param user Ponteiro para o usuário.
 *  \return String com os IDs das músicas gostadas pelo usuário.
 */
char* get_liked_songs_ids(User* user);

/** \brief Define os IDs das músicas gostadas por um usuário.
 *  \param user Ponteiro para o usuário.
 *  \param liked_songs_ids String com os IDs das músicas gostadas pelo usuário.
 */
void set_liked_songs_ids(User* user, char* liked_songs_ids);

#endif