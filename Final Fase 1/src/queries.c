#include "main.h"
#include "users.h"
#include "artists.h"  
#include "musics.h" 
#include <stdlib.h>
#include <stdio.h>
#include "queries.h"
#include "utils.h"
#include <glib.h>

void run_query(Program *program, int query_number, char *arguments, int command_number) {
    switch (query_number)
    {
    case 1:
        query_list_user_data_by_username(program, arguments, command_number);
        break;
    case 2:
        query_list_top_n_artists_by_discography(program, arguments, command_number);
        break;
    default:
        printf("Query %d não implementada.\n", query_number);
        break;
    }
}

void query_list_user_data_by_username(Program *program, char *arguments, int command_number) {
    CatalogUser *users_catalog = get_users_catalog(program);
    User *user = catalog_get_user_by_username(users_catalog, arguments);
    
    if (user == NULL)
    {
        save_output(command_number, "");
        return;
    }

    char* email = get_email(user);
    char* first_name = get_first_name(user);
    char* last_name = get_last_name(user);
    char* birth_date = get_birth_date(user);
    char* country = get_country(user);

    int age = years_between(birth_date, CURRENT_DATE);

    char *output = g_strdup_printf("%s;%s;%s;%d;%s\n", email, first_name, last_name, age, country);

    save_output(command_number, output);

    free(email);
    free(first_name);
    free(last_name);
    free(birth_date);
    free(country);
    free(output);
}

void query_list_top_n_artists_by_discography(Program *program, char *arguments, int command_number) {
    CatalogArtist *artists_catalog = get_artists_catalog(program);
    int top = 0;
    char country[100] = "";

    if (sscanf(arguments, "%d \"%[^\"]\"", &top, country) == 2) {
    } else if (sscanf(arguments, "%d", &top) == 1) {
    }

    GPtrArray *artists_array = get_artists_array(artists_catalog);

    char *output = g_strdup("");

    for (int i = 0; i < top && i < (int)artists_array->len; i++)
    {
        Artist *artist = g_ptr_array_index(artists_array, i);
        char *artist_country = get_artist_country(artist);

        if (strcmp(country, "") == 0 || strcmp(country, artist_country) == 0)
        {
            char *artist_name = get_artist_name(artist);
            const char *artist_type = get_artist_type(artist) == INDIVIDUAL ? "individual" : "group";
            char* discography_duration = int_to_track_duration(get_artist_discography_duration(artist));

            char *artist_output = g_strdup_printf("%s;%s;%s;%s\n", artist_name, artist_type, discography_duration, artist_country);

            char *oldput = output;
            output = g_strconcat(output, artist_output, NULL);

            g_free(artist_name);
            g_free(discography_duration);
            g_free(artist_output);
            g_free(oldput);
        } else {
            top++;
        }

        g_free(artist_country);
    }

    save_output(command_number, output);
    free(output);
}

void save_output(int command_number, char *output){
    char *output_file = g_strdup_printf(OUTPUT_NAME "/" OUTPUT_FILE_NAME, command_number + 1);
    FILE *file = fopen(output_file, "w");

    if (file == NULL)
    {
        perror("Erro ao abrir ficheiro.");
        return;
    }

    if (output[0] == '\0')
    {
        fprintf(file, "\n");
    } else {
        fprintf(file, "%s", output);
    }

    fclose(file);

    g_free(output_file);
}