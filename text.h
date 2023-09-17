#pragma once
#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct{
    char *buffer = NULL;
    size_t size_buffer = -1;
    char **poem = NULL;
    size_t num_lines = -1;
}Text;

FILE *init_file(int argc, char *argv[]);
void  close_file(FILE * fp, char * filename);

void read_to_buffer(Text *text, FILE *fp);
void set_lines_to_text(Text *text);

size_t get_size_file(FILE * fp);
void set_num_lines(Text *text);

void clear_text(char **text, char * buffer);
void print_text(char **text, size_t num_lines);

void init_Text_from_file(Text *text, FILE *fp);
void clear_struct(Text *text);

int comp(const void *a, const void *b);