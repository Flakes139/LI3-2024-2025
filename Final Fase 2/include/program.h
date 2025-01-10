/** \file program.h
 *  \brief Funções principais para gerir o programa.
 *
 * Este ficheiro contém o parser: funções e definições para 
 * inicializar e gerir o programa e os seus catálogos. 
 */

#ifndef PROGRAM_H
#define PROGRAM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "validation.h"
#include "catalogMusic.h" 
#include "catalogAlbum.h"
#include "catalogUser.h"
#include "catalogMusic.h"
#include "catalogArtist.h"
#include "catalogHistory.h"

/** \struct program
 *  \brief Representa a estrutura principal do programa.
 */
typedef struct program Program;

/** \brief Inicializa o programa.
 *  \param arguments Array de strings com os argumentos do programa.
 *  \return Ponteiro para a estrutura principal do programa.
 */
Program* initialize_program(char **arguments);

/** \brief Liberta a memória usada pelo programa.
 *  \param program Ponteiro para a estrutura principal do programa.
 */
void free_program(Program *program);

/** \brief Retorna o catálogo de usuários do programa.
 *  \param program Ponteiro para a estrutura principal do programa.
 *  \return Ponteiro para o catálogo de usuários.
 */
CatalogUser *get_users_catalog(Program *program);

/** \brief Retorna o catálogo de músicas do programa.
 *  \param program Ponteiro para a estrutura principal do programa.
 *  \return Ponteiro para o catálogo de músicas.
 */
CatalogMusic *get_musics_catalog(Program *program);

/** \brief Retorna o catálogo de artistas do programa.
 *  \param program Ponteiro para a estrutura principal do programa.
 *  \return Ponteiro para o catálogo de artistas.
 */
CatalogArtist *get_artists_catalog(Program *program);

/** \brief Retorna o catálogo de álbuns do programa.
 *  \param program Ponteiro para a estrutura principal do programa.
 *  \return Ponteiro para o catálogo de álbuns.
 */
CatalogAlbum *get_albums_catalog(Program *program);

/** \brief Retorna o catálogo de históricos do programa.
 *  \param program Ponteiro para a estrutura principal do programa.
 *  \return Ponteiro para o catálogo de históricos.
 */
CatalogHistory *get_history_catalog(Program *program);


/** \brief Cria e armazena um álbum no programa.
 *  \param album_data Array de strings com os dados do álbum.
 *  \param num_fields Número de campos nos dados do álbum.
 *  \param program Ponteiro para a estrutura principal do programa.
 *  \return 0 em caso de sucesso, 1 caso contrário.
 */
int create_and_store_album(char **album_data, int num_fields, void *program);

/** \brief Cria e armazena um artista no programa.
 *  \param artist_data Array de strings com os dados do artista.
 *  \param num_fields Número de campos nos dados do artista.
 *  \param program Ponteiro para a estrutura principal do programa.
 *  \return 0 em caso de sucesso, 1 caso contrário.
 */
int create_and_store_artist(char **artist_data, int num_fields, void *program);

/** \brief Cria e armazena uma música no programa.
 *  \param music_data Array de strings com os dados da música.
 *  \param num_fields Número de campos nos dados da música.
 *  \param program Ponteiro para a estrutura principal do programa.
 *  \return 0 em caso de sucesso, 1 caso contrário.
 */
int create_and_store_music(char **user_data, int num_fields, void *program);

/** \brief Cria e armazena um histórico no programa.
 *  \param history_data Array de strings com os dados do histórico.
 *  \param num_fields Número de campos nos dados do histórico.
 *  \param program Ponteiro para a estrutura principal do programa.
 *  \return 0 em caso de sucesso, 1 caso contrário.
 */
int create_and_store_history(char **history_data, int num_fields, void *program);

/** \brief Cria e armazena um usuário no programa.
 *  \param user_data Array de strings com os dados do usuário.
 *  \param num_fields Número de campos nos dados do usuário.
 *  \param program Ponteiro para a estrutura principal do programa.
 *  \return 0 em caso de sucesso, 1 caso contrário.
 */
int create_and_store_user(char **user_data, int num_fields, void *program);


/** \brief Define o formato da função de armazenamento de dados. 
 * 
*/
typedef int(StoreData)(char**, int, void*);


/** \brief Lê um ficheiro CSV e armazena os dados no programa.
 *  \param csv Ponteiro para o ficheiro CSV.
 *  \param store_data Função para armazenar os dados lidos.
 *  \param data_catalog Ponteiro para o catálogo de dados armazenados.
 *  \param csv_name Nome do ficheiro CSV.
 *  \return 0 em caso de sucesso, 1 caso contrário.
 */
int parse_csv_and_store_data(FILE* csv, StoreData* store_data, void* data_catalog, const char *csv_name);

/** \brief Remove as aspas de uma string.
 *  \param field String a ser processada.
 *  \return Ponteiro para a string processada.
 */
char* remove_quotes(char* field);

/** \brief Regista uma entrada inválida num ficheiro de logs/erros.
 *  \param fields Array de strings com os campos inválidos.
 *  \param field_count Número de campos inválidos.
 *  \param csv_name Nome do ficheiro CSV.
 *  \param header Cabeçalho do ficheiro CSV.
 *  \param header_written Flag que indica se o cabeçalho já foi escrito.
 */
void log_invalid_entry(char **fields, int field_count, const char *csv_name, const char *header,int header_written);

/** \brief Obtém a cache de reproduções de músicas.
 *  \param program Ponteiro para a estrutura principal do programa.
 *  \return Hash table que contém as reproduções de músicas.
 */
GHashTable *get_music_reproductions_cache(Program *program);

/** \brief Obtém a cache de grupos de artistas.
 *  \param program Ponteiro para a estrutura principal do programa.
 *  \return Hash table que contém os grupos de artistas.
 */
GHashTable *get_artist_groups_cache(Program *program);


#endif