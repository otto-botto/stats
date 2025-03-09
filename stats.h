#ifndef SEARCH_H
#define SEARCH_H

#include "server.h"
#include "cJSON.h"

int test_gtest();

char* build_str(int num_books, double size_mb);
char* parse(char* request_body);
int write_stats(char* result);
void stats(Request request);


#endif //SEARCH_H