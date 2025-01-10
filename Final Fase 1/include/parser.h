#ifndef PARSER_H
#define PARSER_H

typedef int(StoreData)(char**, void*);

int parse_csv_and_store_data(FILE* csv, StoreData* store_data, void* data_catalog, const char *csv_name);

char* remove_quotes(char* field);

void log_invalid_entry(char **fields, int field_count, const char *csv_name, const char *header,int header_written);

#endif