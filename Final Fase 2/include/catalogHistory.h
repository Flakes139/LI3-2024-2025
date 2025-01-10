/** \file catalogHistory.h
 *  \brief Funções para gerir o catálogo de históricos.
 *
 * Este ficheiro contém funções para manipular e gerir um catálogo de históricos.
 */

#ifndef CATALOG_HISTORY_H
#define CATALOG_HISTORY_H

#include <glib.h>
#include "history.h"

/** \struct catalogHistory
 *  \brief Representa um catálogo de históricos.
 */
typedef struct catalogHistory CatalogHistory;

/** \brief Inicializa o catálogo de históricos.
 *  \return Ponteiro para o catálogo inicializado.
 */
CatalogHistory *initialize_history_catalog();

/** \brief Liberta a memória do catálogo de históricos.
 *  \param catalog Ponteiro para o catálogo a ser libertado.
 */
void free_history_catalog(CatalogHistory *catalog);

/** \brief Insere um histórico no catálogo.
 *  \param catalog Ponteiro para o catálogo.
 *  \param history Ponteiro para o histórico a ser inserido.
 */
void insert_history(CatalogHistory *catalog, History *history);

/** \brief Verifica se um histórico existe no catálogo.
 *  \param history_id ID do histórico a ser verificado.
 *  \param catalog Ponteiro para o catálogo.
 *  \return 1 se o histórico existir, 0 caso contrário.
 */
int exists_history(char *history_id, CatalogHistory *catalog);

/** \brief Conta o número de reproduções de uma música no catálogo de históricos.
 *  \param catalog Ponteiro para o catálogo de históricos.
 *  \param music_id Identificador único da música.
 *  \return Número de reproduções da música no catálogo.
 */
int count_music_reproductions(CatalogHistory *catalog, char* music_id);

/** \brief Constrói uma cache com informações de reproduções de músicas.
 *  \param catalog Ponteiro para o catálogo de históricos.
 *  \return Hash table com as reproduções por música.
 */
GHashTable* build_music_reproductions_cache(CatalogHistory *catalog);

#endif // CATALOG_HISTORY_H