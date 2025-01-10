#include "main.h"
#include "catalogUser.h"
#include "catalogArtist.h"  
#include "catalogMusic.h"
#include "catalogAlbum.h" 
#include "catalogHistory.h"
#include <stdlib.h>
#include <stdio.h>
#include "queries.h"
#include "utils.h"
#include <glib.h>

void run_query(Program *program, int query_number, char *arguments, int command_number, char* original_command) {
    switch (query_number)
    {
    case 1:
        query_list_user_data_by_username(program, arguments, command_number, original_command);
        break;
    case 2:
        query_list_top_n_artists_by_discography(program, arguments, command_number, original_command);
        break;
    case 3:
        query_list_most_popular_genres_by_age(program, arguments, command_number, original_command);
        break;
    default:
        printf("Query %d não implementada.\n", query_number);
        break;
    }
}

void query_list_user_data_by_username(Program *program, char *arguments, int command_number, char* original_command) {
    // Avançar no arguments se tiver o 'S'
    char *id = arguments;
    while (*id == 'S' || *id == ' ') {
        id++;
    }

    // Verificar o primeiro caractere do ID
    if (id[0] == 'U') {
        handle_user_query(program, id, command_number, original_command);
    }
    else if (id[0] == 'A') {
        handle_artist_query(program, id, command_number, original_command);
    }
    else {
        save_output(command_number, "", original_command);
    }
}
void handle_user_query(Program *program, char *arguments, int command_number, char* original_command) {
    CatalogUser *users_catalog = get_users_catalog(program);
    User *user = catalog_get_user_by_username(users_catalog, arguments);
    
    if (user == NULL)
    {
        save_output(command_number, "", original_command);
        return;
    }

    char* email = get_email(user);
    char* first_name = get_first_name(user);
    char* last_name = get_last_name(user);
    char* birth_date = get_birth_date(user);
    char* country = get_country(user);

    int age = years_between(birth_date, CURRENT_DATE);

    char *output = g_strdup_printf("%s;%s;%s;%d;%s\n", email, first_name, last_name, age, country);

    save_output(command_number, output, original_command);

    free(email);
    free(first_name);
    free(last_name);
    free(birth_date);
    free(country);
    free(output);
}

void handle_artist_query(Program *program, char *arguments, int command_number, char* original_command) {
    Artist *artist = get_artist_by_id(get_artists_catalog(program), arguments);
    if (!artist) {
        save_output(command_number, "", original_command);
        return;
    }

    char *name = get_artist_name(artist);
    char *country = get_artist_country(artist);
    Type artist_type = get_artist_type(artist);
    float recipe_per_stream = get_artist_recipe_per_stream(artist);
    int num_albums = count_individual_albums(get_albums_catalog(program), arguments);
    
    float total_recipe = 0.0;
    
    // Calcular receita das músicas próprias
    GPtrArray *artist_musics = get_artist_musics(get_musics_catalog(program), arguments);
    for (guint i = 0; i < artist_musics->len; i++) {
        Music *music = g_ptr_array_index(artist_musics, i);
        char *music_id = get_id(music);
        int *reproductions = g_hash_table_lookup(get_music_reproductions_cache(program), music_id);
        if (reproductions) {
            total_recipe += (*reproductions) * recipe_per_stream;
        }
        free(music_id);
    }

    // Para artistas individuais, adicionar receita da participação em grupos
    if (artist_type == INDIVIDUAL) {
        GPtrArray *groups = g_hash_table_lookup(get_artist_groups_cache(program), arguments);
        if (groups) {
            for (guint i = 0; i < groups->len; i++) {
                char *group_id = g_ptr_array_index(groups, i);
                Artist *group = get_artist_by_id(get_artists_catalog(program), group_id);
                if (!group) continue;

                float group_rate = get_artist_recipe_per_stream(group);
                char *constituents = get_artist_id_constituent(group);
                int num_constituents = count_constituents(constituents);
                free(constituents);
                
                if (num_constituents == 0) continue;

                GPtrArray *group_musics = get_artist_musics(get_musics_catalog(program), group_id);
                for (guint j = 0; j < group_musics->len; j++) {
                    Music *music = g_ptr_array_index(group_musics, j);
                    char *music_id = get_id(music);
                    int *reproductions = g_hash_table_lookup(get_music_reproductions_cache(program), music_id);
                    if (reproductions) {
                        total_recipe += ((*reproductions) * group_rate) / num_constituents;
                    }
                    free(music_id);
                }
                g_ptr_array_free(group_musics, FALSE);
            }
        }
    }

    char *output = g_strdup_printf("%s;%s;%s;%d;%.2f\n", 
        name, 
        artist_type == INDIVIDUAL ? "individual" : "group", 
        country, 
        num_albums,
        total_recipe);

    save_output(command_number, output, original_command);

    free(name);
    free(country);
    free(output);
    g_ptr_array_free(artist_musics, FALSE);
}

void query_list_top_n_artists_by_discography(Program *program, char *arguments, int command_number, char* original_command) {
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

    save_output(command_number, output, original_command);
    free(output);
}

void save_output(int command_number, char *output, char* original_command){
    char *output_file = g_strdup_printf(OUTPUT_NAME "/" OUTPUT_FILE_NAME, command_number + 1);
    FILE *file = fopen(output_file, "w");

    if (file == NULL) {
        perror("Erro ao abrir ficheiro.");
        return;
    }

    char* formatted_output = format_output_string(original_command, output);

    if (formatted_output == NULL || formatted_output[0] == '\0') {
        fprintf(file, "\n");
    } else {
        fprintf(file, "%s", formatted_output);
    }

    free(formatted_output);
    fclose(file);
    g_free(output_file);
}

void query_list_most_popular_genres_by_age(Program *program, char *arguments, int command_number, char* original_command) {
    int min_age, max_age;
    if (sscanf(arguments, "%d %d", &min_age, &max_age) != 2) {
        save_output(command_number, "", original_command);
        return;
    }

    CatalogUser *users_catalog = get_users_catalog(program);
    CatalogMusic *musics_catalog = get_musics_catalog(program);

    // Obter usuários na faixa etária
    GPtrArray *users_in_range = get_users_by_age_range(users_catalog, min_age, max_age);
    
    // Obter músicas curtidas desses usuários
    GPtrArray *liked_songs = get_liked_songs_from_users(users_in_range);
    
    // Processar contagem de gêneros
    GPtrArray *sorted_genres = get_genre_likes_from_users(musics_catalog, liked_songs);


    GString *output = g_string_new("");
    for (guint i = 0; i < sorted_genres->len; i++) {
        GenreLikes *gl = g_ptr_array_index(sorted_genres, i);
        char* genre = get_genre_from_likes(gl);
        int likes = get_likes_count(gl);
        g_string_append_printf(output, "%s;%d\n", genre, likes);
        free(genre);
    }

    save_output(command_number, output->str, original_command);

    g_ptr_array_free(sorted_genres, TRUE);
    g_ptr_array_free(liked_songs, TRUE);
    g_ptr_array_free(users_in_range, TRUE);
    g_string_free(output, TRUE);
}