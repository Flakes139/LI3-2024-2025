/** \file catalogAlbum.h
 *  \brief Funções para gerir o catálogo de álbuns.
 *
 * Este ficheiro contém funções para manipular e gerir um catálogo de álbuns.
 */

#ifndef CATALOGALBUM_H
#define CATALOGALBUM_H

#include "album.h"
#include "catalogAlbum.h"
#include <glib.h>

/** \struct catalogAlbum
 *  \brief Representa um catálogo de álbuns.
 */
typedef struct catalogAlbum CatalogAlbum;

/** \brief Inicializa o catálogo de álbuns.
 *  \return Ponteiro para o catálogo inicializado.
 */
CatalogAlbum *initialize_albums_catalog();

/** \brief Liberta a memória do catálogo de álbuns.
 *  \param catalog Ponteiro para o catálogo a ser libertado.
 */
void free_albums_catalog(CatalogAlbum *catalog);

/** \brief Insere um álbum no catálogo.
 *  \param catalog Ponteiro para o catálogo.
 *  \param album Ponteiro para o álbum a ser inserido.
 */
void insert_album(CatalogAlbum *catalog, Album *album);

/** \brief Verifica se um álbum existe no catálogo.
 *  \param album_id ID do álbum a ser verificado.
 *  \param catalog Ponteiro para o catálogo.
 *  \return 1 se o álbum existe, 0 caso contrário.
 */
int exists_album(char *album_id, CatalogAlbum *catalog);

/** \brief Conta o número de álbuns individuais de um artista.
 *  \param catalog Ponteiro para o catálogo de álbuns.
 *  \param artist_id Identificador único do artista.
 *  \return Número de álbuns individuais do artista no catálogo.
 */
int count_individual_albums(CatalogAlbum *catalog, char* artist_id);

#endif