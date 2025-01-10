#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "musics.h" 

#define BUFFER_SIZE 200
#define DELIMITER ";"

int parse_csv_and_store_data(FILE* csv, StoreData* store_data, void* data_catalog, const char *csv_name)
{
    char *line_buffer;
    size_t buffer_size = BUFFER_SIZE;
    int read = 0;
    int header_written = 0;

    line_buffer = (char *)malloc(buffer_size * sizeof(char));

    // Lê a primeira linha (cabeçalho)
    read = getline(&line_buffer, &buffer_size, csv);
    if (read != -1) {
        // Se a primeira linha for lida com sucesso, armazene-a como cabeçalho
        line_buffer[read - 1] = '\0';  // Remove o caractere newline
        log_invalid_entry(NULL, 0, csv_name, line_buffer, header_written);  // Escreve o cabeçalho no arquivo de erros
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
        
        int create_result = store_data(fields, data_catalog);

        if (create_result != 0) {
            log_invalid_entry(fields, field_count, csv_name, NULL, header_written);  // Registra entrada inválida sem sobrescrever cabeçalho
        }

        for (int i = 0; i < field_count; i++) {
            free(fields[i]);
        }
        free(fields);
    }

    free(line_buffer);
    return 0;
}

char* remove_quotes(char* field){
    size_t len = strlen(field);
    if (field[0] == '"' && field[len - 1] == '"') {
        field[len - 1] = '\0';
        return field + 1;  
    }
    return field;
}

void write_field_with_quotes(FILE *file, const char *field){
    fprintf(file, "\"%s\"", field);
}


void log_invalid_entry(char **fields, int field_count, const char *csv_name, const char *header,int header_written){
    const char *output_dir = "resultados/";

    size_t error_file_size = strlen(output_dir) + strlen(csv_name) + 8;  // 8 para "_errors" + \0
    
    char *error_file = (char *)malloc(error_file_size);
    
    strcpy(error_file, output_dir);
    strcat(error_file, csv_name);

    char *dot_position = strrchr(error_file, '.');
    if (dot_position != NULL && strcmp(dot_position, ".csv") == 0){
        strcpy(dot_position, "_errors.csv");
    } else {
        strcat(error_file, "_errors.csv");
    }

    FILE *file = fopen(error_file, "a");
    if (!file) {
        perror("Erro ao abrir o arquivo de erros");
        free(error_file);
        return;
    }


    if (!header_written && header != NULL){
        fprintf(file, "%s\n", header);
        header_written = 1;
    }

    if (fields != NULL){
        for (int i = 0; i < field_count; i++){
            write_field_with_quotes(file, fields[i]);
            if (i < field_count - 1) fprintf(file, ";");
        }
        fprintf(file, "\n");
    }

    fclose(file);
    free(error_file);
}
