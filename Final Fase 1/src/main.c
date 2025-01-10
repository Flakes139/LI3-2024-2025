#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "main.h"
#include "users.h"
#include "queries.h"
#include "musics.h"
#include "artists.h"
#include <stdlib.h>
#include <glib.h>

 struct program {
    CatalogUser *users_catalog;
    CatalogMusic *musics_catalog;
    CatalogArtist *artists_catalog;
};

int main(int argc,char** argv)
{
    // Verifica se o número de argumentos é válido
    if (argc != 3)
    {
        printf("Numero de argumentos inválido. Recebe <caminho-dataset> <ficheiro-input>\n");
        return 1;
    }

    // Cria pasta de output caso não exista
    g_mkdir_with_parents(OUTPUT_NAME, 0700);

    Program *program = initialize_program(argv);

    run_program(program, argv);

    free_program(program);

    return 0;
}

Program* initialize_program(char **arguments) {
    Program *program = (Program *)malloc(sizeof(Program));

    // Leitura e inserção dos dados dos users no sistema
    
    char users_file_path[40] = "";
    strcat(users_file_path, arguments[1]);
    strcat(users_file_path, "/users.csv");
    FILE* users_file = fopen(users_file_path, "r");

    if (users_file ==  NULL)
    {
        perror("Erro ao abrir ficheiro.");
        return NULL;
    }

    CatalogUser *users_catalog = initialize_users_catalog();
    program->users_catalog = users_catalog;

    const char *users_file_name = strrchr(users_file_path, '/');
    users_file_name = users_file_name ? users_file_name + 1 : users_file_path;

    parse_csv_and_store_data(users_file, create_and_store_user, users_catalog, users_file_name);
    
    fclose(users_file);

    // Leitura e inserção dos dados das músicas no sistema

    char musics_file_path[40] = "";
    strcat(musics_file_path, arguments[1]);
    strcat(musics_file_path, "/musics.csv");
    FILE* musics_file = fopen(musics_file_path, "r");

    if (musics_file == NULL) 
    {
        perror("Erro ao abrir ficheiro de músicas.");
        return NULL;
    }

    CatalogMusic *musics_catalog = initialize_musics_catalog(); 
    program->musics_catalog = musics_catalog;

    const char *musics_file_name = strrchr(musics_file_path, '/');
    musics_file_name = musics_file_name ? musics_file_name + 1 : musics_file_path;

    parse_csv_and_store_data(musics_file, create_and_store_music, musics_catalog, musics_file_name);

    fclose(musics_file);

    // Leitura e inserção dos dados dos artistas no sistema

    char artists_file_path[40] = "";
    strcat(artists_file_path, arguments[1]);
    strcat(artists_file_path, "/artists.csv");
    FILE* artists_file = fopen(artists_file_path, "r");

    if (artists_file == NULL) 
    {
        perror("Erro ao abrir ficheiro de artistas.");
        return NULL;
    }

    CatalogArtist *artists_catalog = initialize_artists_catalog();
    program->artists_catalog = artists_catalog;

    const char *artists_file_name = strrchr(artists_file_path, '/');
    artists_file_name = artists_file_name ? artists_file_name + 1 : artists_file_path;

    parse_csv_and_store_data(artists_file, create_and_store_artist, artists_catalog, artists_file_name);

    fclose(artists_file);

    sort_artists_by_discography_duration(program->artists_catalog, program->musics_catalog, get_discography_duration_by_artist_table);

    return program;
}

void run_program(Program *program, char **arguments) {

    // Leitura do ficheiro de queries
    FILE *input_file = fopen(arguments[2], "r");

    if (input_file == NULL)
    {
        perror("Erro ao abrir ficheiro.");
        return;
    }

    char *line_buffer;
    size_t buffer_size = BUFFER_SIZE;
    int read = 0;

    line_buffer = (char *)malloc(buffer_size * sizeof(char));

    int command_number = 0;

    // Para cada comando
    while ((read = getline(&line_buffer, &buffer_size, input_file)) != -1) 
    {
        // Ignora newline
        line_buffer[read - 1] = '\0';

        // Obter número da query
        int query_number = line_buffer[0] - '0';

        run_query(program, query_number, line_buffer + 2, command_number);

        command_number++;
    }

    free(line_buffer);
}

void free_program(Program *program) {
    free_users_catalog(program->users_catalog);
    free_musics_catalog(program->musics_catalog);
    free_artists_catalog(program->artists_catalog);

    free(program);
}


CatalogUser *get_users_catalog(Program *program) {
    return program->users_catalog;
}

CatalogMusic *get_musics_catalog(Program *program) {
    return program->musics_catalog;
}

CatalogArtist *get_artists_catalog(Program *program) {
    return program->artists_catalog;
}

