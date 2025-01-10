/** \file queries.h
 *  \brief Definições das funções para execução das queries.
 *
 * Este ficheiro contém as funções responsáveis por processar as queries implementadas no programa.
 */

#ifndef QUERIES_H
#define QUERIES_H

#include "program.h"
#include <glib.h>

/** \brief Executa uma query com base no número fornecido.
 *  \param program Ponteiro para a estrutura principal do programa.
 *  \param query_number Número da query a ser executada.
 *  \param arguments Argumentos da query.
 *  \param command_number Número do comando em execução.
 *  \param original_command Comando original fornecido pelo utilizador.
 */
void run_query(Program *program, int query_number, char *arguments, int command_number, char* original_command);

/** \brief Executa a query 1: Listar os dados de um utilizador ou artista com base no id.
 *  \param program Ponteiro para a estrutura principal do programa.
 *  \param arguments Argumentos da query (id do utilizador ou artista).
 *  \param command_number Número do comando em execução.
 *  \param original_command Comando original fornecido pelo utilizador.
 */
void query_list_user_data_by_username(Program *program, char *arguments, int command_number, char* original_command);

/** \brief Processa a query para listar os dados de um utilizador.
 *  \param program Ponteiro para a estrutura principal do programa.
 *  \param arguments Identificador único do utilizador.
 *  \param command_number Número do comando em execução.
 *  \param original_command Comando original fornecido pelo utilizador.
 */
void handle_user_query(Program *program, char *arguments, int command_number, char* original_command);

/** \brief Processa a query para listar os dados de um artista.
 *  \param program Ponteiro para a estrutura principal do programa.
 *  \param arguments Identificador único do artista.
 *  \param command_number Número do comando em execução.
 *  \param original_command Comando original fornecido pelo utilizador.
 */
void handle_artist_query(Program *program, char *arguments, int command_number, char* original_command);

/** \brief Executa a query 2: Listar os top N artistas com base na duração da discografia.
 *  \param program Ponteiro para a estrutura principal do programa.
 *  \param arguments Argumentos da query (número de artistas a listar e o país (opcional)).
 *  \param command_number Número do comando em execução.
 *  \param original_command Comando original fornecido pelo utilizador.
 */
void query_list_top_n_artists_by_discography(Program *program, char *arguments, int command_number, char* original_command);

/** \brief Guarda o resultado de uma query no ficheiro correspondente.
 *  \param command_number Número do comando em execução.
 *  \param output String com o resultado da query.
 *  \param original_command Comando original fornecido pelo utilizador.
 */
void save_output(int command_number, char *output, char* original_command);

/** \brief Executa a query 3: Listar os géneros mais populares por faixa etária.
 *  \param program Ponteiro para a estrutura principal do programa.
 *  \param arguments Argumentos da query (idade mínima e máxima).
 *  \param command_number Número do comando em execução.
 *  \param original_command Comando original fornecido pelo utilizador.
 */
void query_list_most_popular_genres_by_age(Program *program, char *arguments, int command_number, char* original_command);

#endif