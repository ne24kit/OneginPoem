#pragma once

#include "sort.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct {
    char *buffer = NULL;
    size_t size_buffer = 0;
    char **poem = NULL;
    size_t num_lines = 0;
}Text;

FILE *init_read_file(int argc, char *argv[]);
FILE *init_write_file(const char * filename);
void  close_file(FILE * fp);

void write_sorted(FILE * fp, Text *text);
void write_source(FILE * fp, Text *text);

void init_Text_from_file(Text *text, FILE *fp);

void read_to_buffer(Text *text, FILE *fp);
void set_lines_to_text(Text *text);

size_t get_size_file(FILE * fp);
void set_num_lines(Text *text);

void print_text(char **text, size_t num_lines);

void clear_Text_struct(Text *text);

const char * skip_punctuation(const char *str, int shift);
int left_comp(const void *a, const void *b);
int right_comp(const void *a, const void *b);
