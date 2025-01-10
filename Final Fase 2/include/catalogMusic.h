/** \file catalogMusic.h
 *  \brief Funções para gerir o catálogo de músicas.
 *
 * Este ficheiro contém funções para manipular e gerir um catálogo de músicas.
 */

#ifndef CATALOGMUSIC_H
#define CATALOGMUSIC_H

#include "music.h"
#include "catalogMusic.h"
#include <glib.h>

/** \struct catalogMusic
 *  \brief Representa um catálogo de músicas.
 */
typedef struct catalogMusic CatalogMusic;

/** \struct genreLikes
 *  \brief Armazena informações de géneros e número de likes.
 */
typedef struct genreLikes GenreLikes;

/** \brief Cria uma nova estrutura GenreLikes.
 *  \param genre Género da música.
 *  \param likes Número de likes.
 *  \return Ponteiro para a nova estrutura.
 */
GenreLikes* create_genre_likes(char* genre, int likes);

/** \brief Obtém o género a partir da estrutura de likes.
 *  \param gl Ponteiro para a estrutura de género.
 *  \return Género da música.
 */
char* get_genre_from_likes(GenreLikes* gl);

/** \brief Obtém o número de likes de um género.
 *  \param gl Ponteiro para a estrutura de género.
 *  \return Número de likes.
 */
int get_likes_count(GenreLikes* gl);

/** \brief Liberta a memória de uma estrutura GenreLikes.
 *  \param gl_void Ponteiro para a estrutura a ser libertada.
 */
void free_genre_likes(void* gl_void);

/** \brief Compara duas estruturas GenreLikes.
 *  \param a Ponteiro para a primeira estrutura.
 *  \param b Ponteiro para a segunda estrutura.
 *  \return Resultado da comparação para ordenação.
 */
int compare_genre_likes(gconstpointer a, gconstpointer b);


/** \brief Inicializa o catálogo de músicas.
 *  \return Ponteiro para o catálogo inicializado.
 */
CatalogMusic *initialize_musics_catalog();

/** \brief Liberta a memória do catálogo de músicas.
 *  \param catalog Ponteiro para o catálogo a ser libertado.
 */
void free_musics_catalog(CatalogMusic *catalog);

/** \brief Insere uma música no catálogo.
 *  \param catalog Ponteiro para o catálogo.
 *  \param music Ponteiro para a música a ser inserida.
 */
void insert_music(CatalogMusic *catalog, Music *music);

/** \brief Verifica se uma música existe no catálogo.
 *  \param music_id ID da música a ser verificada.
 *  \param catalog Ponteiro para o catálogo.
 *  \return 1 se a música existir, 0 caso contrário.
 */
int exists_music(char *music_id, CatalogMusic *catalog);

/** \brief Retorna uma tabela com a duração total da discografia de cada artista.
 *  \param catalog Ponteiro para o catálogo de músicas.
 *  \return Ponteiro para a tabela de duração.
 */
GHashTable *get_discography_duration_by_artist_table(void *catalog);

/** \brief Estrutura para armazenar informações de gênero e likes
 */
GPtrArray* get_genre_likes_from_users(CatalogMusic *catalog, GPtrArray *liked_songs);

/** \brief Obtém as músicas de um artista específico.
 *  \param catalog Ponteiro para o catálogo de músicas.
 *  \param artist_id ID do artista.
 *  \return Ponteiro para um array com as músicas do artista.
 */
GPtrArray* get_artist_musics(CatalogMusic *catalog, char* artist_id);

#endif
