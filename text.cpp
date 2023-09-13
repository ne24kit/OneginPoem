#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

//TODO: change void to type of error and error handling
void init_Text_from_file(Text *text, FILE *fp)
{
    text->size_buffer = get_size_file(fp);
    text->buffer = (char *)calloc(text->size_buffer + 1, sizeof(char));

    read_to_buffer(text, fp);
    set_num_lines(text);
    
    text->poem = (char **)calloc(text->num_lines, sizeof(char *));
    set_lines_to_text(text);

}


int main(int argc, char *argv[])
{
    Text text;
    FILE * fp = init_file(argc, argv);
    
    init_Text_from_file(&text, fp);
    close_file(fp, argv[1]);

    print_text(text.poem, text.num_lines);
    
    clear_text(text.poem, text.buffer);
}
//TODO: divide to two functions 
FILE *init_file(int argc, char *argv[])
{
    FILE *fp = NULL;
    
    if (argc != 2){
        fprintf(stderr, "Write ./a.out <filename.txt>\n");
        exit(0);
    }
    
    if ((fp = fopen(argv[1], "r")) == NULL){
        fprintf(stderr, "Сan't open file: <%s>\n", argv[1]);
        exit(0);
    }
    return fp;
}

void close_file(FILE * fp, char * filename)
{
    if (fclose(fp) != 0)
        fprintf(stderr, "File close error: <%s>\n", filename);
}

void read_to_buffer(Text *text, FILE *fp)
{
    fread(text->buffer, sizeof(char), text->size_buffer, fp);

    text->buffer[text->size_buffer] = '\n';
    text->size_buffer++;
}

void set_lines_to_text(Text *text)
{
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
    return total_byte;
}
//rename: and delete '\n'
void set_num_lines(Text *text)
{
    size_t count = 0;
    
    for(size_t i = 0; i < text->size_buffer; i++){
        if (text->buffer[i] == '\n'){
            text->buffer[i] = '\0';
            count++;
        }
    }
    //TODO: maybe without count, use only text->num_lines and set 0 at start???
    text->num_lines = count;
}

void clear_text(char **text, char * buffer)
{
    free(buffer);
    free(text);
}

void print_text(char **text, size_t num_lines)
{
    for(size_t i = 0; i < num_lines; i++)
        printf("%s\n", text[i]);
}

