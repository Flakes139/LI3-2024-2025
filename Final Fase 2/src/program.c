#include "program.h"

struct program
{
    CatalogUser *users_catalog;
    CatalogMusic *musics_catalog;
    CatalogArtist *artists_catalog;
    CatalogAlbum *albums_catalog;
    CatalogHistory *history_catalog;
    GHashTable *music_reproductions_cache;
    GHashTable *artist_groups_cache;
};

Program *initialize_program(char **arguments)
{
    Program *program = (Program *)malloc(sizeof(Program));

    // Leitura e inserção dos dados dos artistas no sistema

    char artists_file_path[40] = "";
    strcat(artists_file_path, arguments[1]);
    strcat(artists_file_path, "/artists.csv");
    FILE *artists_file = fopen(artists_file_path, "r");

    if (artists_file == NULL)
    {
        perror("Erro ao abrir ficheiro de artistas.");
        return NULL;
    }

    CatalogArtist *artists_catalog = initialize_artists_catalog();
    program->artists_catalog = artists_catalog;

    const char *artists_file_name = strrchr(artists_file_path, '/');
    artists_file_name = artists_file_name ? artists_file_name + 1 : artists_file_path;

    parse_csv_and_store_data(artists_file, create_and_store_artist, program, artists_file_name);

    fclose(artists_file);

    // Leitura e inserção dos dados do albuns no sistema

    char albums_file_path[40] = "";
    strcat(albums_file_path, arguments[1]);
    strcat(albums_file_path, "/albums.csv");
    FILE *albums_file = fopen(albums_file_path, "r");

    if (albums_file == NULL)
    {
        perror("Erro ao abrir ficheiro de albuns.");
        return NULL;
    }

    CatalogAlbum *albums_catalog = initialize_albums_catalog();
    program->albums_catalog = albums_catalog;

    const char *albums_file_name = strrchr(albums_file_path, '/');
    albums_file_name = albums_file_name ? albums_file_name + 1 : albums_file_path;

    parse_csv_and_store_data(albums_file, create_and_store_album, program, albums_file_name);

    fclose(albums_file);

    // Leitura e inserção dos dados das músicas no sistema

    char musics_file_path[40] = "";
    strcat(musics_file_path, arguments[1]);
    strcat(musics_file_path, "/musics.csv");
    FILE *musics_file = fopen(musics_file_path, "r");

    if (musics_file == NULL)
    {
        perror("Erro ao abrir ficheiro de músicas.");
        return NULL;
    }

    CatalogMusic *musics_catalog = initialize_musics_catalog();
    program->musics_catalog = musics_catalog;

    const char *musics_file_name = strrchr(musics_file_path, '/');
    musics_file_name = musics_file_name ? musics_file_name + 1 : musics_file_path;

    parse_csv_and_store_data(musics_file, create_and_store_music, program, musics_file_name);

    fclose(musics_file);

    // Leitura e inserção dos dados dos users no sistema

    char users_file_path[40] = "";
    strcat(users_file_path, arguments[1]);
    strcat(users_file_path, "/users.csv");
    FILE *users_file = fopen(users_file_path, "r");

    if (users_file == NULL)
    {
        perror("Erro ao abrir ficheiro.");
        return NULL;
    }

    CatalogUser *users_catalog = initialize_users_catalog();
    program->users_catalog = users_catalog;

    const char *users_file_name = strrchr(users_file_path, '/');
    users_file_name = users_file_name ? users_file_name + 1 : users_file_path;

    parse_csv_and_store_data(users_file, create_and_store_user, program, users_file_name);

    fclose(users_file);

    // Leitura e inserção dos dados do histórico no sistema
    char history_file_path[40] = "";
    strcat(history_file_path, arguments[1]);
    strcat(history_file_path, "/history.csv");
    FILE *history_file = fopen(history_file_path, "r");

    if (history_file == NULL)
    {
        perror("Erro ao abrir ficheiro de histórico.");
        return NULL;
    }

    CatalogHistory *history_catalog = initialize_history_catalog();
    program->history_catalog = history_catalog;

    const char *history_file_name = strrchr(history_file_path, '/');
    history_file_name = history_file_name ? history_file_name + 1 : history_file_path;

    parse_csv_and_store_data(history_file, create_and_store_history, program, history_file_name);

    fclose(history_file);

    sort_artists_by_discography_duration(program->artists_catalog, program->musics_catalog, get_discography_duration_by_artist_table);

    program->music_reproductions_cache = build_music_reproductions_cache(program->history_catalog);
    program->artist_groups_cache = build_artist_groups_cache(program->artists_catalog);

    return program;
}

void free_program(Program *program)
{
    free_users_catalog(program->users_catalog);
    free_musics_catalog(program->musics_catalog);
    free_artists_catalog(program->artists_catalog);
    free_history_catalog(program->history_catalog);
    free_albums_catalog(program->albums_catalog);
    if (program->music_reproductions_cache)
        g_hash_table_destroy(program->music_reproductions_cache);
    if (program->artist_groups_cache)
        g_hash_table_destroy(program->artist_groups_cache);

    free(program);
}

CatalogUser *get_users_catalog(Program *program)
{
    return program->users_catalog;
}

CatalogMusic *get_musics_catalog(Program *program)
{
    return program->musics_catalog;
}

CatalogArtist *get_artists_catalog(Program *program)
{
    return program->artists_catalog;
}
CatalogAlbum *get_albums_catalog(Program *program)
{
    return program->albums_catalog;
}

CatalogHistory *get_history_catalog(Program *program)
{
    return program->history_catalog;
}

int create_and_store_album(char **album_data, int num_fields, void *program)
{    
    if (!validate_album(album_data, num_fields))
    {
        printf("Falhou validação do album\n");
        return 1;
    }

    Program *program_struct = (Program *)program;
    CatalogAlbum *album_catalog = get_albums_catalog(program_struct);
    
    if (!album_catalog) {
        printf("Catalog é NULL\n");
        return 1;
    }

    Album *album = allocate_album();
    if (!album) {
        printf("Falhou alocação do album\n");
        return 1;
    }

    set_album_id(album, album_data[0]);
    set_album_title(album, album_data[1]);
    set_album_artist_id(album, album_data[2]);
    set_album_year(album, atoi(album_data[3]));
    set_album_producers(album, album_data[4]);

    insert_album(album_catalog, album);
    return 0;
}

int create_and_store_artist(char **artist_data, int num_fields, void *program)
{

    if (!validate_artist(artist_data, num_fields))
    {
        return 1;
    }

    Program *program_struct = (Program *)program;

    CatalogArtist *artist_catalog = get_artists_catalog(program_struct);

    Artist *artist = allocate_artist();

    set_artist_id(artist, artist_data[0]);
    set_artist_name(artist, artist_data[1]);
    set_artist_description(artist, artist_data[2]);
    set_artist_recipe_per_stream(artist, atof(artist_data[3])); // Conversão para float
    set_artist_id_constituent(artist, artist_data[4]);
    set_artist_country(artist, artist_data[5]);
    set_artist_discography_duration(artist, 0); // Inicialização a 0

    char temp_type[20];
    strncpy(temp_type, artist_data[6], sizeof(temp_type) - 1);
    temp_type[sizeof(temp_type) - 1] = '\0';
    to_lowercase(temp_type);

    set_artist_type(artist, (strcmp(temp_type, "individual") == 0) ? INDIVIDUAL : GROUP);

    insert_artist(artist_catalog, artist);

    return 0;
}

int create_and_store_music(char **music_data, int num_fields, void *program)
{
    Program *program_struct = (Program *)program;

    int artist_exists = 1;

    // parse music_data[2] and verify if every artist exists, format is "['A00000000', 'A00000001', ...]"
    // Remove the brackets and split the string by comma
    char *artists_str = strdup(music_data[2]);
    artists_str[strlen(artists_str) - 1] = '\0'; // Remove the closing bracket
    char *artist_id = strtok(artists_str + 1, ", "); // Remove the opening bracket and split

    while (artist_id != NULL && artist_exists)
    {
        // Remove quotes from artist_id
        if (artist_id[0] == '\'' && artist_id[strlen(artist_id) - 1] == '\'')
        {
            artist_id[strlen(artist_id) - 1] = '\0';
            artist_id++;
        }

        if (!exists_artist(artist_id, get_artists_catalog(program_struct)))
        {
            artist_exists = 0;
        }

        artist_id = strtok(NULL, ", ");
    }

    free(artists_str);

    if (!validate_music(music_data, num_fields) || !artist_exists || !exists_album(music_data[3], get_albums_catalog(program_struct)))
    {
        return 1;
    }

    CatalogMusic *music_catalog = get_musics_catalog(program_struct);

    Music *music = allocate_music();

    set_id(music, music_data[0]);             // id na posição 0
    set_title(music, music_data[1]);          // title na posição 1
    set_music_artist_id(music, music_data[2]); // artist_id na posição 2
    set_duration(music, track_duration_to_int(music_data[4])); // duration na posição 4
    set_genre(music, music_data[5]);          // genre na posição 5
    set_year(music, atoi(music_data[6]));     // year na posição 6

    insert_music(music_catalog, music);

    return 0;
}

int create_and_store_history(char **history_data, int num_fields, void *program)
{
    Program *program_struct = (Program *)program;

    if (!validate_history(history_data, num_fields) || !exists_user(history_data[1], get_users_catalog(program_struct)) || !exists_music(history_data[2], get_musics_catalog(program_struct)))
    {
        return 1;
    }


    CatalogHistory *history_catalog = get_history_catalog(program_struct);

    History *history = allocate_history();

    set_history_id(history, history_data[0]);
    set_history_user_id(history, history_data[1]);
    set_history_music_id(history, history_data[2]);
    set_history_timestamp(history, history_data[3]);
    set_history_duration(history, track_duration_to_int(history_data[4]));

    char temp_platform[20];
    strncpy(temp_platform, history_data[5], sizeof(temp_platform) - 1);
    temp_platform[sizeof(temp_platform) - 1] = '\0'; // Garantir que a string termine em '\0'
    to_lowercase(temp_platform);

    set_history_platform(history, (strcmp(temp_platform, "mobile") == 0) ? MOBILE : DESKTOP);

    insert_history(history_catalog, history);

    return 0;
}

int create_and_store_user(char **user_data, int num_fields, void *program)
{
    Program *program_struct = (Program *)program;

    int songs_exist = 1;

    // parse user_data[7] and verify if every music exists, format is "['S00000000', 'S00000001', ...]"
    char *songs_str = strdup(user_data[7]);
    songs_str[strlen(songs_str) - 1] = '\0'; // Remove the closing bracket
    char *song_id = strtok(songs_str + 1, ", "); // Remove the opening bracket and split

    while (song_id != NULL && songs_exist)
    {
        // Remove quotes from song_id
        if (song_id[0] == '\'' && song_id[strlen(song_id) - 1] == '\'')
        {
            song_id[strlen(song_id) - 1] = '\0';
            song_id++;
        }

        if (!exists_music(song_id, get_musics_catalog(program_struct)))
        {
            songs_exist = 0;
        }

        song_id = strtok(NULL, ", ");
    }

    free(songs_str);

    if (!validate_user(user_data, num_fields) || !songs_exist)
    {
        return 1;
    }

    CatalogUser *user_catalog = get_users_catalog(program_struct);

    User *user = allocate_user();

    set_username(user, user_data[0]);
    set_email(user, user_data[1]);
    set_first_name(user, user_data[2]);
    set_last_name(user, user_data[3]);
    set_birth_date(user, user_data[4]);
    set_country(user, user_data[5]);

    set_subscription_type(user, strcmp(user_data[6], "regular") == 0 ? REGULAR : PREMIUM);

    set_liked_songs_ids(user, user_data[7]);

    insert_user(user_catalog, user);

    return 0;
}

#define BUFFER_SIZE 2 ^ 12
#define DELIMITER ";"

int parse_csv_and_store_data(FILE *csv, StoreData *store_data, void *data_catalog, const char *csv_name)
{
    char *line_buffer;
    size_t buffer_size = BUFFER_SIZE;
    int read = 0;
    int header_written = 0;

    line_buffer = (char *)malloc(buffer_size * sizeof(char));

    // Lê a primeira linha (cabeçalho)
    read = getline(&line_buffer, &buffer_size, csv);
    if (read != -1)
    {
        // Se a primeira linha for lida com sucesso, armazene-a como cabeçalho
        line_buffer[read - 1] = '\0';                                      // Remove o caractere newline
        log_invalid_entry(NULL, 0, csv_name, line_buffer, header_written); // Escreve o cabeçalho no arquivo de erros
        header_written = 1;
    }

    // Lê as linhas subsequentes
    while ((read = getline(&line_buffer, &buffer_size, csv)) != -1)
    {
        // Ignora newline
        line_buffer[read - 1] = '\0';

        // Separa os campos pelo delimitador
        char *token;
        char **fields = NULL;
        int field_count = 0;

        token = strtok(line_buffer, DELIMITER);
        while (token != NULL)
        {
            token = remove_quotes(token);
            fields = (char **)realloc(fields, (field_count + 1) * sizeof(char *));
            fields[field_count] = strdup(token);
            field_count++;
            token = strtok(NULL, DELIMITER);
        }

        int create_result = store_data(fields, field_count, data_catalog);

        if (create_result != 0)
        {
            log_invalid_entry(fields, field_count, csv_name, NULL, header_written); // Registra entrada inválida sem sobrescrever cabeçalho
        }

        for (int i = 0; i < field_count; i++)
        {
            free(fields[i]);
        }
        free(fields);
    }

    free(line_buffer);
    return 0;
}

char *remove_quotes(char *field)
{
    size_t len = strlen(field);
    if (field[0] == '"' && field[len - 1] == '"')
    {
        field[len - 1] = '\0';
        return field + 1;
    }
    return field;
}

void write_field_with_quotes(FILE *file, const char *field)
{
    fprintf(file, "\"%s\"", field);
}

void log_invalid_entry(char **fields, int field_count, const char *csv_name, const char *header, int header_written)
{
    const char *output_dir = "resultados/";

    size_t error_file_size = strlen(output_dir) + strlen(csv_name) + 8; // 8 para "_errors" + \0

    char *error_file = (char *)malloc(error_file_size);

    strcpy(error_file, output_dir);
    strcat(error_file, csv_name);

    char *dot_position = strrchr(error_file, '.');
    if (dot_position != NULL && strcmp(dot_position, ".csv") == 0)
    {
        strcpy(dot_position, "_errors.csv");
    }
    else
    {
        strcat(error_file, "_errors.csv");
    }

    FILE *file = fopen(error_file, (header_written) ? "a" : "w");

    if (!file)
    {
        perror("Erro ao abrir o arquivo de erros");
        free(error_file);
        return;
    }

    if (!header_written && header != NULL)
    {
        fprintf(file, "%s\n", header);
        header_written = 1;
    }

    if (fields != NULL)
    {
        for (int i = 0; i < field_count; i++)
        {
            write_field_with_quotes(file, fields[i]);
            if (i < field_count - 1)
                fprintf(file, ";");
        }
        fprintf(file, "\n");
    }

    fclose(file);
    free(error_file);
}

GHashTable *get_music_reproductions_cache(Program *program) {
    return program->music_reproductions_cache;
}

GHashTable *get_artist_groups_cache(Program *program) {
    return program->artist_groups_cache;
}