#include <stdio.h>
#include <string.h>
#include "main.h"
#include <stdlib.h>
#include <glib.h>
#include "program.h"




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

void run_program(Program *program, char **arguments)
{

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

        run_query(program, query_number, line_buffer + 2, command_number, line_buffer);

        command_number++;
    }

    free(line_buffer);
}