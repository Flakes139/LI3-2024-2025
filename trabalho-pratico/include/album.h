/** \file album.h
 *  \brief Definições para lidar com álbuns.
 *
 * Este ficheiro contém funções e estrutura para manipular álbuns no sistema.
 */

#ifndef ALBUM_H
#define ALBUM_H

/** \struct album
 *  \brief Representa um álbum com dados básicos.
 */
typedef struct album Album;

/** \brief Liberta a memória de um álbum.
 *  \param album_void Ponteiro para o álbum a ser liberado.
 */
void free_album(void *album_void);

/** \brief Aloca memória para um novo álbum.
 *  \return Ponteiro para o album criado.
 */
Album *allocate_album();

/** \brief Retorna o ID do álbum.
 *  \param album Ponteiro para o álbum.
 *  \return String com o ID.
 */
char* get_album_id(Album* album);

/** \brief Define o ID do álbum.
 *  \param album Ponteiro para o álbum.
 *  \param id String com o novo ID.
 */
void set_album_id(Album* album, char* id);

/** \brief Retorna o título do álbum.
 *  \param album Ponteiro para o álbum.
 *  \return String com o título.
 */
char* get_album_title(Album* album);

/** \brief Define o título do álbum.
 *  \param album Ponteiro para o álbum.
 *  \param title String com o novo título.
 */
void set_album_title(Album* album, char* title);

/** \brief Retorna o ID do artista do álbum.
 *  \param album Ponteiro para o álbum.
 *  \return String com o ID do artista.
 */
char* get_album_artist_id(Album* album);

/** \brief Define o ID do artista do álbum.
 *  \param album Ponteiro para o álbum.
 *  \param artist_id String com o novo ID do artista.
 */
void set_album_artist_id(Album* album, char* artist_id);

/** \brief Retorna o ano do álbum.
 *  \param album Ponteiro para o álbum.
 *  \return Ano do álbum.
 */
int get_album_year(Album* album);

/** \brief Define o ano do álbum.
 *  \param album Ponteiro para o álbum.
 *  \param year Novo ano do álbum.
 */
void set_album_year(Album* album, int year);

/** \brief Retorna os produtores do álbum.
 *  \param album Ponteiro para o álbum.
 *  \return String com os produtores.
 */
char* get_album_producers(Album* album);

/** \brief Define os produtores do álbum.
 *  \param album Ponteiro para o álbum.
 *  \param producers String com os novos produtores.
 */
void set_album_producers(Album* album, char* producers);

#endif
