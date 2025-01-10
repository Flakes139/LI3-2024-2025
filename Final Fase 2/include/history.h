/** \file history.h
 *  \brief Funções para lidar com históricos de reprodução.
 *
 * Este ficheiro contém funções e estrutura para manipular históricos de reprodução no sistema.
 */

#ifndef HISTORY_H
#define HISTORY_H

#include "utils.h"

/** \struct history
 *  \brief Representa um histórico de reprodução.
 */
typedef struct history History;

/** \struct timestamp
 *  \brief Representa um registro de data e hora.
 */
typedef struct timestamp {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
} Timestamp;  

/** \enum Platform
 *  \brief Plataforma utilizada na reprodução.
 */
typedef enum {
    MOBILE = 0,
    DESKTOP = 1,
} Platform;

/** \brief Liberta a memória de um histórico.
 *  \param history_void Ponteiro para o histórico a ser libertado.
 */
void free_history(void *history_void);

/** \brief Aloca memória para um novo histórico.
 *  \return Ponteiro para o histórico criado.
 */
History *allocate_history();


/** \brief Retorna o ID do histórico.
 *  \param history Ponteiro para o histórico.
 *  \return String com o ID do histórico.
 */
char* get_history_id(History* history);

/** \brief Define o ID do histórico.
 *  \param history Ponteiro para o histórico.
 *  \param id String com o novo ID do histórico.
 */
void set_history_id(History* history, char* id);

/** \brief Retorna o ID do usuário associado ao histórico.
 *  \param history Ponteiro para o histórico.
 *  \return String com o ID do usuário.
 */
char* get_history_user_id(History* history);

/** \brief Define o ID do usuário associado ao histórico.
 *  \param history Ponteiro para o histórico.
 *  \param user_id String com o novo ID do usuário.
 */
void set_history_user_id(History* history, char* user_id);

/** \brief Retorna o ID da música associada ao histórico.
 *  \param history Ponteiro para o histórico.
 *  \return String com o ID da música.
 */
char* get_history_music_id(History* history);

/** \brief Define o ID da música associada ao histórico.
 *  \param history Ponteiro para o histórico.
 *  \param music_id String com o novo ID da música.
 */
void set_history_music_id(History* history, char* music_id);

/** \brief Retorna o timestamp do histórico.
 *  \param history Ponteiro para o histórico.
 *  \return Ponteiro para o timestamp do histórico.
 */
Timestamp* get_history_timestamp(History* history);

/** \brief Define o timestamp do histórico.
 *  \param history Ponteiro para o histórico.
 *  \param timestamp_str Ponteiro para uma string no formato YYYY/MM/DD HH:MM:SS.
 */
void set_history_timestamp(History* history, char* timestamp_str);

/** \brief Retorna a duração da reprodução associada ao histórico.
 *  \param history Ponteiro para o histórico.
 *  \return Duração da reprodução em segundos.
 */
int get_history_duration(History* history);

/** \brief Define a duração da reprodução associada ao histórico.
 *  \param history Ponteiro para o histórico.
 *  \param duration Duração da reprodução em segundos.
 */
void set_history_duration(History* history, int duration);

/** \brief Retorna a plataforma utilizada na reprodução associada ao histórico.
 *  \param history Ponteiro para o histórico.
 *  \return Plataforma utilizada (MOBILE ou DESKTOP).
 */
Platform get_history_platform(History* history);

/** \brief Define a plataforma utilizada na reprodução associada ao histórico.
 *  \param history Ponteiro para o histórico.
 *  \param platform Nova plataforma (MOBILE ou DESKTOP).
 */
void set_history_platform(History* history, Platform platform);
#endif
