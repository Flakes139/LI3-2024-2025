/** \file artist.h
 *  \brief Definições para lidar com artistas.
 *
 * Este ficheiro contém funções e estrutura para manipular artistas no sistema.
 */

#ifndef ARTIST_H
#define ARTIST_H

/** \struct artist
 *  \brief Representa um artista com dados básicos.
 */
typedef struct artist Artist;

/** \enum Type
 *  \brief Tipo do artista: individual ou grupo.
 */
typedef enum {
    INDIVIDUAL = 0,
    GROUP = 1,
} Type;

/** \brief Liberta a memória de um artista.
 *  \param artist_void Ponteiro para o artista a ser libertado.
 */
void free_artist(void *artist_void);

/** \brief Cria um novo artista.
 *  \return Ponteiro para o artista criado.
 */
Artist *allocate_artist();

/** \brief Retorna o ID do artista.
 *  \param artist Ponteiro para o artista.
 *  \return String com o ID.
 */
char* get_artist_id(Artist* artist);

/** \brief Define o ID do artista.
 *  \param artist Ponteiro para o artista.
 *  \param id String com o novo ID.
 */
void set_artist_id(Artist* artist, char* id);

/** \brief Retorna o nome do artista.
 *  \param artist Ponteiro para o artista.
 *  \return String com o nome.
 */
char* get_artist_name(Artist* artist);

/** \brief Define o nome do artista.
 *  \param artist Ponteiro para o artista.
 *  \param name String com o novo nome.
 */
void set_artist_name(Artist* artist, char* name);

/** \brief Retorna a descrição do artista.
 *  \param artist Ponteiro para o artista.
 *  \return String com a descrição.
 */
char* get_artist_description(Artist* artist);

/** \brief Define a descrição do artista.
 *  \param artist Ponteiro para o artista.
 *  \param description String com a nova descrição.
 */
void set_artist_description(Artist* artist, char* description);

/** \brief Retorna a receita por reprodução do artista.
 *  \param artist Ponteiro para o artista.
 *  \return Receita por reprodução.
 */
float get_artist_recipe_per_stream(Artist* artist);

/** \brief Define a receita por reprodução do artista.
 *  \param artist Ponteiro para o artista.
 *  \param recipe_per_stream Novo valor da receita por reprodução.
 */
void set_artist_recipe_per_stream(Artist* artist, float recipe_per_stream);

/** \brief Retorna o ID dos constituintes do artista.
 *  \param artist Ponteiro para o artista.
 *  \return String com o ID dos constituintes.
 */
char* get_artist_id_constituent(Artist* artist);

/** \brief Define o ID dos constituintes do artista.
 *  \param artist Ponteiro para o artista.
 *  \param id_constituent String com o novo ID dos constituintes.
 */
void set_artist_id_constituent(Artist* artist, char* id_constituent);

/** \brief Retorna o país do artista.
 *  \param artist Ponteiro para o artista.
 *  \return String com o país.
 */
char* get_artist_country(Artist* artist);

/** \brief Define o país do artista.
 *  \param artist Ponteiro para o artista.
 *  \param country String com o novo país.
 */
void set_artist_country(Artist* artist, char* country);

/** \brief Retorna o tipo do artista.
 *  \param artist Ponteiro para o artista.
 *  \return Tipo do artista (individual ou grupo).
 */
Type get_artist_type(Artist* artist);

/** \brief Define o tipo do artista.
 *  \param artist Ponteiro para o artista.
 *  \param type Novo tipo do artista.
 */
void set_artist_type(Artist* artist, Type type);

/** \brief Retorna a duração da discografia do artista.
 *  \param artist Ponteiro para o artista.
 *  \return Duração da discografia.
 */
int get_artist_discography_duration(Artist* artist);

/** \brief Define a duração da discografia do artista.
 *  \param artist Ponteiro para o artista.
 *  \param discography_duration Nova duração da discografia.
 */
void set_artist_discography_duration(Artist* artist, int discography_duration);

#endif