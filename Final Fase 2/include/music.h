/** \file music.h
 *  \brief Funções e estrutura para manipular músicas.
 *
 * Este ficheiro contém funções e definições para gerir músicas no sistema.
 */

#ifndef MUSIC_H
#define MUSIC_H

/** \struct music
 *  \brief Representa uma música com dados básicos.
 */
typedef struct music Music;

/** \brief Liberta a memória de uma música.
 *  \param music_void Ponteiro para a música a ser libertada.
 */
void free_music(void *music_void);

/** \brief Aloca memória para uma nova música.
 *  \return Ponteiro para a música criada.
 */
Music *allocate_music();


/** \brief Retorna o ID da música.
 *  \param music Ponteiro para a música.
 *  \return String com o ID.
 */
char* get_id(Music* music);

/** \brief Define o ID da música.
 *  \param music Ponteiro para a música.
 *  \param id String com o novo ID da música.
 */
void set_id(Music* music, char* id);

/** \brief Retorna o título da música.
 *  \param music Ponteiro para a música.
 *  \return String com o título da música.
 */
char* get_title(Music* music);

/** \brief Define o título da música.
 *  \param music Ponteiro para a música.
 *  \param title String com o novo título da música.
 */
void set_title(Music* music, char* title);

/** \brief Retorna o ID do artista da música.
 *  \param music Ponteiro para a música.
 *  \return String com o ID do artista.
 */
char* get_music_artist_id(Music* music);

/** \brief Define o ID do artista da música.
 *  \param music Ponteiro para a música.
 *  \param artist_id String com o novo ID do artista.
 */
void set_music_artist_id(Music* music, char* artist_id);

/** \brief Retorna a duração da música.
 *  \param music Ponteiro para a música.
 *  \return Duração da música em segundos.
 */
int get_duration(Music* music);

/** \brief Define a duração da música.
 *  \param music Ponteiro para a música.
 *  \param duration Nova duração da música em segundos.
 */
void set_duration(Music* music, int duration);

/** \brief Retorna o género da música.
 *  \param music Ponteiro para a música.
 *  \return String com o género da música.
 */
char* get_genre(Music* music);

/** \brief Define o género da música.
 *  \param music Ponteiro para a música.
 *  \param genre String com o novo género da música.
 */
void set_genre(Music* music, char* genre);

/** \brief Retorna o ano de lançamento da música.
 *  \param music Ponteiro para a música.
 *  \return Ano de lançamento da música.
 */
int get_year(Music* music);

/** \brief Define o ano de lançamento da música.
 *  \param music Ponteiro para a música.
 *  \param year Novo ano de lançamento da música.
 */
void set_year(Music* music, int year);

#endif