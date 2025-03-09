#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "stats.h"

#define STATS_FILE_PATH "/home/lora/Microservices/stats.txt"
#define FILE_PATH_BUFFER_SIZE 256

int test_gtest(){
    return 5;
}

char* build_str(int num_books, double size) {
    char* message = (char*)malloc(200*sizeof(char));
    if(message == NULL) {
        fprintf(stderr, "Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    message[0] = '\0';
    strcat(message, "Number of books: ");
    char temp[5];
    sprintf(temp, "%d\n",num_books);
    strcat(message, temp);

    strcat(message, "Library size: ");
    char temp2[10000];
    sprintf(temp2, "%.2lfMB\n",size);
    strcat(message, temp2);


    return message;
}

char* parse(char* body) {

    const cJSON* num_books_json = NULL;
    const cJSON* size_json = NULL;

    cJSON* body_json = cJSON_Parse(body);
    if(body_json == NULL) {
        fprintf(stderr, "Failed to parse request body.");
        exit(EXIT_FAILURE);
    }

    num_books_json = cJSON_GetObjectItemCaseSensitive(body_json, "num_books");
    if(!cJSON_IsNumber(num_books_json)) {
        fprintf(stderr, "Error parsing number of books.");
    }

    size_json = cJSON_GetObjectItemCaseSensitive(body_json, "size");
    if(!cJSON_IsNumber(size_json)) {
        fprintf(stderr, "Error parsing size.");
    }

    int num_books = num_books_json->valueint;
    int size = size_json->valueint;
    double size_mb = size / 125000;

    char* result = build_str(num_books, size_mb);
    return result;
}

int write_stats(char* result) {
    FILE* fileptr;
    char filepath[FILE_PATH_BUFFER_SIZE];
    // specify full path
    sprintf(filepath, "/home/lora/Microservices/stats.txt");
    // open file for writing
    fileptr = fopen(STATS_FILE_PATH, "w");
    if(fileptr == NULL) {
        fprintf(stderr, "Failed to open file '%s': %s\n", STATS_FILE_PATH, strerror(errno));
        return -1; // Indicate failure
    }

    // Check for null result pointer
    if (result == NULL) {
        fprintf(stderr, "Error: result pointer is NULL.\n");
        fclose(fileptr);
        return -1;
    }

    // Write to the file
    if (fprintf(fileptr, "%s\n", result) < 0) { // added newline, check fprintf return value
        fprintf(stderr, "Failed to write to file '%s': %s\n", STATS_FILE_PATH, strerror(errno));
        fclose(fileptr);
        return -1;
    }

    // Close the file
    if (fclose(fileptr) != 0) {
        fprintf(stderr, "Failed to close file '%s': %s\n", STATS_FILE_PATH, strerror(errno));
        return -1;
    }
    // success
    return 0;
}

void stats(Request request) {
    char* message = parse(request.content);
    printf("%s\n", message);
    if(write_stats(message) == 0) {
        printf("Successfully wrote to file.\n");
    }else {
        printf("Failed to write to file.\n");
    }
    // respond(&server, &request, 200, message);
    free(message);
}