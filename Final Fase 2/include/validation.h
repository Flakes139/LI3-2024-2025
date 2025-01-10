/** \file validation.h
 *  \brief Funções para validar dados de entrada no sistema.
 *
 * Este arquivo contém funções para verificar a validade de diversos tipos de dados usados no sistema.
 */

#ifndef VALIDATION_H
#define VALIDATION_H

/** \brief Valida os campos de um usuário.
 *  \param fields Array de strings que contém os campos do usuário.
 *  \param field_count Número de campos fornecidos.
 *  \return 1 se os campos forem válidos, 0 caso contrário.
 */
int validate_user(char **fields, int field_count);

/** \brief Valida os campos de uma música.
 *  \param fields Array de strings que contém os campos da música.
 *  \param field_count Número de campos fornecidos.
 *  \return 1 se os campos forem válidos, 0 caso contrário.
 */
int validate_music(char **fields, int field_count);

/** \brief Valida os campos de um artista.
 *  \param fields Array de strings que contém os campos do artista.
 *  \param field_count Número de campos fornecidos.
 *  \return 1 se os campos forem válidos, 0 caso contrário.
 */
int validate_artist(char **fields, int field_count);

/** \brief Valida os campos de um álbum.
 *  \param fields Array de strings que contém os campos do álbum.
 *  \param field_count Número de campos fornecidos.
 *  \return 1 se os campos forem válidos, 0 caso contrário.
 */
int validate_album(char **fields, int field_count);

/** \brief Valida os campos de um histórico.
 *  \param fields Array de strings que contém os campos do histórico.
 *  \param field_count Número de campos fornecidos.
 *  \return 1 se os campos forem válidos, 0 caso contrário.
 */
int validate_history(char **fields, int field_count);

/** \brief Valida uma data no formato YYYY/MM/DD.
 *  \param date String com a data a ser validada.
 *  \return 1 se a data for válida, 0 caso contrário.
 */
int validate_date(const char *date);

/** \brief Valida a duração de uma música no formato HH:MM:SS.
 *  \param duration String com a duração a ser validada.
 *  \return 1 se a duração for válida, 0 caso contrário.
 */
int validate_duration(const char *duration);

/** \brief Valida um email.
 *  \param email String com o email a ser validado.
 *  \return 1 se o email for válido, 0 caso contrário.
 */
int validate_email(const char *email);

/** \brief Valida o tipo de subscrição de um usuário.
 *  \param subscription String com o tipo de subscrição.
 *  \return 1 se o tipo for válido, 0 caso contrário.
 */
int validate_subscription_type(const char *subscription);

/** \brief Valida uma lista de strings no formato [a, b, c].
 *  \param list String com a lista a ser validada.
 *  \return 1 se a lista for válida, 0 caso contrário.
 */
int validate_list_format(const char *list);

/** \brief Valida um timestamp no formato YYYY/MM/DD HH:MM:SS.
 *  \param timestamp String com o timestamp a ser validado.
 *  \return 1 se o timestamp for válido, 0 caso contrário.
 */
int validate_timestamp(const char *timestamp);

/** \brief Converte uma string para letras minúsculas.
 *  \param str String a ser convertida.
 */
void to_lowercase(char *str);

/** \brief Valida uma plataforma de streaming.
 *  \param platform String com a plataforma a ser validada.
 *  \return 1 se a plataforma for válida, 0 caso contrário.
 */
int validate_platform(const char *platform);

/** \brief Valida o tipo de artista.
 *  \param artist_type String com o tipo de artista.
 *  \param id_constituent ID do constituinte do artista.
 *  \return 1 se o tipo for válido, 0 caso contrário.
 */
int validate_artist_type(const char *artist_type, const char *id_constituent);

#endif
