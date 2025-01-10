/** \file catalogArtist.h
 *  \brief Funções para gerir o catálogo de artistas.
 *
 * Este ficheiro contém funções para manipular e gerir um catálogo de artistas.
 */

#ifndef CATALOGARTIST_H
#define CATALOGARTIST_H

#include "artist.h"
#include "catalogArtist.h"
#include <glib.h>

/** \struct catalogArtist
 *  \brief Representa um catálogo de artistas.
 */
typedef struct catalogArtist CatalogArtist;

/** \typedef FetchArtistDiscographyDurationCache
 *  \brief Função para buscar a duração da discografia dos artistas.
 */
typedef GHashTable *(FetchArtistDiscographyDurationCache)(void*);

/** \brief Inicializa o catálogo de artistas.
 *  \return Ponteiro para o catálogo inicializado.
 */
CatalogArtist *initialize_artists_catalog();

/** \brief Liberta a memória do catálogo de artistas.
 *  \param catalog Ponteiro para o catálogo a ser libertado.
 */
void free_artists_catalog(CatalogArtist *catalog);

/** \brief Insere um artista no catálogo.
 *  \param catalog Ponteiro para o catálogo.
 *  \param artist Ponteiro para o artista a ser inserido.
 */
void insert_artist(CatalogArtist *catalog, Artist *artist);

/** \brief Ordena os artistas pela duração da discografia.
 *  \param catalog Ponteiro para o catálogo de artistas.
 *  \param musics_catalog Ponteiro para o catálogo de músicas.
 *  \param fetch_artist_discography_duration Função para ir buscar a duração da discografia dos artistas.
 */
void sort_artists_by_discography_duration(CatalogArtist *catalog, void *musics_catalog, FetchArtistDiscographyDurationCache *fetch_artist_discography_duration);

/** \brief Obtém um array com os artistas do catálogo.
 *  \param catalog Ponteiro para o catálogo de artistas.
 *  \return Ponteiro para o array de artistas.
 */
GPtrArray *get_artists_array(CatalogArtist *catalog);

/** \brief Compara dois artistas pela duração da discografia.
 *  \param a1 Ponteiro para o primeiro artista.
 *  \param a2 Ponteiro para o segundo artista.
 *  \return Resultado da comparação.
 */
int compare_artists_by_discography_duration(gconstpointer *a1, gconstpointer *a2);

/** \brief Verifica se um artista existe no catálogo.
 *  \param artist_id ID do artista a ser verificado.
 *  \param catalog Ponteiro para o catálogo.
 *  \return 1 se o artista existir, 0 caso contrário.
 */
int exists_artist(char *artist_id, CatalogArtist *catalog);

/** \brief Obtém um artista pelo seu ID.
 *  \param catalog Ponteiro para o catálogo de artistas.
 *  \param artist_id ID do artista a ser obtido.
 *  \return Ponteiro para o artista encontrado ou NULL se não existir.
 */
Artist* get_artist_by_id(CatalogArtist *catalog, char* artist_id);

/** \brief Obtém os grupos a que um artista pertence.
 *  \param catalog Ponteiro para o catálogo de artistas.
 *  \param artist_id ID do artista.
 *  \return Ponteiro para um array com os grupos do artista.
 */
GPtrArray* get_artist_groups(CatalogArtist *catalog, char* artist_id);

/** \brief Constrói uma cache de grupos de artistas.
 *  \param catalog Ponteiro para o catálogo de artistas.
 *  \return Hash table que contém a cache de grupos.
 */
GHashTable* build_artist_groups_cache(CatalogArtist *catalog);

#endif