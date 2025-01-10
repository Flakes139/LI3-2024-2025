/** \file utils.h
 *  \brief Funções utilitárias para o sistema.
 *
 * Este arquivo contém funções auxiliares e macros usadas em várias partes do sistema.
 */

#ifndef UTILS_H
#define UTILS_H

#include <glib.h>

/** \def CURRENT_DATE
 *  Data atual usada para cálculos relacionados ao tempo.
 */
#define CURRENT_DATE "2024/09/09" 

/** \brief Calcula a diferença de anos entre duas datas.
 *  \param date1 String da primeira data no formato YYYY/MM/DD.
 *  \param date2 String da segunda data no formato YYYY/MM/DD.
 *  \return Diferença em anos entre as duas datas.
 */
int years_between(char* date1, char* date2);

/** \brief Converte uma duração de uma música no formato HH:MM:SS para segundos.
 *  \param duration String da duração no formato HH:MM:SS.
 *  \return Duração em segundos.
 */
int track_duration_to_int(char* duration);

/** \brief Converte uma duração de uma música em segundos para o formato HH:MM:SS.
 *  \param duration Duração em segundos.
 *  \return String da duração no formato HH:MM:SS.
 */
char *int_to_track_duration(int duration);

/** \brief Liberta memória de uma chave-valor numa hash table.
 *  \param key Ponteiro para a chave.
 *  \param value Ponteiro para o valor.
 *  \param user_data Dados adicionais (não usados aqui).
 *  \return Retorna sempre 0.
 */
int free_key_value_pair(gpointer key, gpointer value, gpointer user_data);

/** \brief Converte uma string para letras minúsculas.
 *  \param str String a ser convertida.
 */
void to_lowercase(char *str);

/** \brief Formata o output de uma query.
 *  \param command Comando original da query.
 *  \param output Resultado da query.
 *  \return String formatada para exibição ou gravação.
 */
char* format_output_string(const char* command, char* output);

/** \brief Conta o número de elementos numa lista formatada.
 *  \param list Lista de strings.
 *  \return Número de elementos.
 */
int count_constituents(char* list);

#endif