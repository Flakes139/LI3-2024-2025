#ifndef QUERIES_H
#define QUERIES_H

#include "main.h"
#include <glib.h>

#define CURRENT_DATE "2024/09/09" 

void run_query(Program *program, int query_number, char *arguments, int command_number);

void query_list_user_data_by_username(Program *program, char *arguments, int command_number);

void query_list_top_n_artists_by_discography(Program *program, char *arguments, int command_number);

void save_output(int command_number, char *output);

#endif