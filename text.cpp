#include "text.h"

#define cat(a, b) a##b

void write_sorted(FILE * fp, Text *text);
void write_source(FILE * fp, Text *text);

int main(int argc, char *argv[])
{
    Text text;
    FILE * fp_read = init_file(argc, argv);
    FILE * fp_write;
    fp_write = fopen("output.txt", "w+");

    init_Text_from_file(&text, fp_read);
    close_file(fp_read);
    //qsort(text.poem, text.num_lines, sizeof(char *), comp);

    sort(text.poem, 0, text.num_lines - 1, sizeof(char **), comp);
    write_sorted(fp_write, &text);
    
    sort(text.poem, 0, text.num_lines - 1, sizeof(char **), right_comp);
    write_sorted(fp_write, &text);
    
    write_source(fp_write, &text);
    
    fclose(fp_write);
    
    print_text(text.poem, text.num_lines);
    
    clear_struct(&text);
}

void write_sorted(FILE * fp, Text *text)
{
    for(size_t i = 0; i < text->num_lines; i++){
        fputs(text->poem[i], fp);
        fputc('\n', fp);
    }
    fputs("-----------------------------------------------\n", fp);
}

void write_source(FILE * fp, Text *text)
{
    char *copy_buff = text->buffer;
    int shift = 0;
    for(size_t i = 0; i < text->num_lines; ++i)
        copy_buff += fprintf(fp, "%s\n", copy_buff);
    fputs("-----------------------------------------------\n", fp);
    
}


//TODO: change void to type of error and error handling
void init_Text_from_file(Text *text, FILE *fp)
{
    MY_ASSERT((fp != NULL), "Pointer to file == NULL\n");
    MY_ASSERT((text != NULL), "Pointer to struct text == NULL\n");

    text->size_buffer = get_size_file(fp);
    text->buffer = (char *)calloc(text->size_buffer + 1 + 1, sizeof(char));
    
    //ставлю '\0', для обратной сортировки
    *text->buffer = '\0';
    //перемещаю указатель
    text->buffer++;
    
    read_to_buffer(text, fp);

    set_num_lines(text);
    
    text->poem = (char **)calloc(text->num_lines, sizeof(char *));
    set_lines_to_text(text);

}

void clear_struct(Text *text)
{
    //перемещаю указатель на '\0', чтобы не забыть отчистить его
    text->buffer--;

    free(text->buffer);
    free(text->poem);

    text->buffer = NULL;
    text->poem = NULL;
    text->size_buffer = -1;
    text->num_lines = -1;
    text = NULL;
}


//TODO: divide to two functions 
FILE *init_file(int argc, char *argv[])
{
    FILE *fp = NULL;

    MY_ASSERT((argc == 2), "Write ./a.out <filename.txt>\n");
    MY_ASSERT(((fp = fopen(argv[1], "r")) != NULL), "Сan't open file\n");

    return fp;
}

void close_file(FILE * fp)
{
    MY_ASSERT((fp != NULL), "Pointer to file == NULL\n");
    MY_ASSERT((fclose(fp) == 0), "File close error\n");
}

void read_to_buffer(Text *text, FILE *fp)
{   
    MY_ASSERT((fp != NULL), "Pointer to file == NULL\n");
    MY_ASSERT((text != NULL), "Pointer to struct text == NULL\n");
    
    fread(text->buffer, sizeof(char), text->size_buffer, fp);

    text->buffer[text->size_buffer] = '\n';
    text->size_buffer++;
}

void set_lines_to_text(Text *text)
{
    MY_ASSERT((text != NULL), "Pointer to struct text == NULL\n");
    MY_ASSERT((text->size_buffer > 0), "Buffer size is not positive\n");
    
    text->poem[0] = text->buffer;
    
    for(size_t i = 0, j = 1; i < text->size_buffer - 1; i++){
        if (text->buffer[i] == '\0'){
            text->poem[j] = &text->buffer[i + 1];
            j++;
        }
    }

}

size_t get_size_file(FILE * fp)
{
    fseek(fp, 0, SEEK_END);
    size_t total_byte = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    MY_ASSERT((total_byte != 0), "Read zero bytes\n");
    
    return total_byte;
}
//rename: and delete '\n'
void set_num_lines(Text *text)
{
    MY_ASSERT((text != NULL), "Pointer to struct text == NULL\n");
    MY_ASSERT((text->size_buffer > 0), "Buffer size is not positive\n");

    text->num_lines = 0;
    
    for(size_t i = 0; i < text->size_buffer; i++){
        if (text->buffer[i] == '\n'){
            text->buffer[i] = '\0';
            text->num_lines++;
        }
    }
    //TODO: maybe without count, use only text->num_lines and set 0 at start???
    
}

void print_text(char **text, size_t num_lines)
{
    MY_ASSERT((text != NULL), "Pointer to struct text == NULL\n");
    for(size_t i = 0; i < num_lines; i++)
        printf("%s\n", text[i]);
}

const char * left_skip_punctuation(const char *str)
{
    while(*str && !isalnum(*str))
        str++;

    return str;
}

const char * right_skip_punctuation(const char *str)
{
    
    while(*str && !isalnum(*str))
        str--;

    return str;
}

int right_comp(const void *a, const void *b)
{   
    const char * str1 = *(const char **)a;
    const char * str2 = *(const char **)b;
    str1 += strlen(str1) - 1;
    str2 += strlen(str2) - 1;
    
    while(*str1 && *str2){
        str1 = right_skip_punctuation(str1);
        str2 = right_skip_punctuation(str2);

        if(*str1 && *str2 && (toupper(*str1) != toupper(*str2)))
            return toupper(*str1) - toupper(*str2);

        if(*str1 && *str2){
            str1--;
            str2--;
        }
    }
    return *str1 - *str2;
}

int comp(const void *a, const void *b)
{   
    const char * str1 = *(const char **)a;
    const char * str2 = *(const char **)b;


    while(*str1 && *str2){
        str1 = left_skip_punctuation(str1);
        str2 = left_skip_punctuation(str2);

        if(*str1 && *str2 && (toupper(*str1) != toupper(*str2)))
            return toupper(*str1) - toupper(*str2);

        if(*str1 && *str2){
            str1++;
            str2++;
        }
    }
    return *str1 - *str2;
}
