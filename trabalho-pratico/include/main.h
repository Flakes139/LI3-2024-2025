/** \file main.h
 *  \brief Definições e função para executar o programa principal.
 *
 * Este ficheiro contém a função para a execução do programa.
 */

#ifndef MAIN_H
#define MAIN_H

#include "catalogUser.h"
#include "catalogMusic.h"
#include "catalogArtist.h"
#include "program.h"
#include "queries.h"


#define OUTPUT_NAME "resultados"
#define OUTPUT_FILE_NAME "command%d_output.txt"
#define BUFFER_SIZE 200


/** \brief Executa o programa principal.
 *  \param program Ponteiro para a estrutura principal do programa.
 *  \param arguments Array de strings com os argumentos do programa.
 */
void run_program(Program *program, char **arguments);

#endif