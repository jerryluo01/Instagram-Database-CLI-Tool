#include "database.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Programmer   : Louis Renard
// Created      : 2025/04/09
// Purpose      : Initialize data base

Database db_create(){
        Database db;
        db.size         = 0;
        db.capacity     = 4;

        db.records      = malloc(4 * sizeof(Record));

        // Check malloc was successfull
        if (db.records == NULL) {
                fprintf(stderr, "Failed to allocate memory\n");
                exit(1);
        }
        return db;
}

// Programmer   : Louis Renard
// Created      : 2025/04/09
// Purpose      : Add element to the database

void db_append(Database * db, Record const * item){
        if (db->size == db->capacity){

                Record *records_copy = malloc(2 * db->capacity * sizeof(Record));

                // Check is malloc successful
                if (records_copy == NULL) {
                fprintf(stderr, "Failed to allocate memory\n");
                exit(1);
                }

                // Copy old array
                for (int i = 0; i < db->capacity; i++){
                        records_copy[i] = db->records[i];
                }

                // Free space
                free(db->records);

                // Adjust fields
                db->records = records_copy;
                db->capacity *= 2;
        }
        db->records[db->size] = *item;
        db->size++;


}

// Programmer   : Louis Renard
// Created      : 2025/04/09
// Purpose      : Return object at index

Record *db_index(Database * db, int index){

        // Bound check
        if (index >= 0 && index < db->size){
                return &db->records[index];
        } else {
                return NULL;
        }

}

// Programmer   : louis Renard
// Created      : 2025/04/09
// Purpose      : Find a record given handle

Record *db_lookup(Database * db, char const * handle){

        // Traverese and compare handles
        for (int i = 0; i < db->size; i++){
                if (strcmp(db->records[i].handle, handle) == 0){
                        return &db->records[i];
                }
        }
        return NULL;
}

// Programmer   : Louis Renard
// Created      : 2025/04/09
// Purpose      : Delete a database

void db_free(Database * db){
        free(db->records);
        db->records = NULL;
}



// Programmer   : Jerry Luo
// Created      : 2025/04/08
// Purpose      : Parses a line of CSV data into one Record

Record parse_record(char const *line) {
        Record item;

        // Duplicating line to not modify original
        char *temp = strdup(line);

        // If no line found, quit function
        if (!temp) {
                puts("No line to strdup");
                exit(1);
        }

        // Assign a pointer to first token
        char *token = strtok(temp, ",");

        // If token exists, copy into handle of respective record
        if (token) {

                // Leaving space for null-terminator character
                strncpy(item.handle, token, sizeof(item.handle) - 1);

                // Appending null-terminator to string
                item.handle[sizeof(item.handle) - 1] = '\0';
        }

        token = strtok(NULL, ",");
        if (token) {

                // Converting string to long integer and assigning
                // to followers in respective record
                item.follower_count= strtol(token, NULL, 10);
        }

        token = strtok(NULL, ",");
        if (token) {
                strncpy(item.comment, token, sizeof(item.comment) - 1);
                item.comment[sizeof(item.comment) - 1] = '\0';
        }

        token = strtok(NULL, ",");
        if (token) {
                item.date_modified = strtol(token, NULL, 10);
        }

        // Free memory allocated for temp
        free(temp);
        return item;
}

// Programmer   : Jerry Luo
// Created      : 2025/04/08
// Purpose      : Appends record from file to path to db


void db_load_csv(Database * db, char const * path) {
        // Open the file
        FILE *doc = fopen(path, "rt");

        // If no file found
        if (doc == NULL) {
                puts("Could not open file");
                return;
        }

        // Initialise parameters for getline()
        char *line      = NULL;
        size_t length   = 0;

        // Read line until none are left
        while(getline(&line, &length, doc) != -1) {
                size_t line_length = strlen(line);

                // Remove newline
                if (line_length > 0 && line[line_length - 1] == '\n') {
                        line[line_length - 1] = '\0';
                }

                // Parsing the line into a Record-like format
                Record item = parse_record(line);

                // Addint formatted line to database
                db_append(db, &item);
        }

        // Free the memory allocated for line
        free(line);

        // Close file
        fclose(doc);
}

// Programmer   : Jerry Luo
// Created      : 2025/04/08
// Purpose      : Overwrites the file at path with db contents, in CSV format

void db_write_csv(Database * db, char const * path) {
        FILE *doc = fopen(path, "wt");

        if (doc == NULL) {
                puts("Could not open file");
                return;
        }

        // Iterate through the database
        for (int i = 0; i < db->size; i++) {

                // Assigning pointer to specific record
                Record *item = &db->records[i];                 // Might need to change variable records

                // Writing in file in CSV format
                fprintf(doc, "%s,%lu,%s,%lu\n", item->handle, item->follower_count, item->comment, item->date_modified);
        }
        fclose(doc);

}
