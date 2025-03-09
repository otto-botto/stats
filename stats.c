#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "stats.h"

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

void write_stats(char* result) {
    FILE* fileptr;
    char filepath[100];
    // specify full path
    sprintf(filepath, "/home/lora/Microservices/stats.txt");
    // open file for writing
    fileptr = fopen(filepath, "w");
    if(fileptr == NULL) {
        fprintf(stderr, "Failed to write to file.");
        exit(EXIT_FAILURE);
    }

    // write to the file
    fprintf(fileptr, result);

    // close the file
    fclose(fileptr);
}

void stats(Server server, Request request) {
    char* message = parse(request.content);
    printf("%s\n", message);
    write_stats(message);
    // respond(&server, &request, 200, message);
    free(message);
}