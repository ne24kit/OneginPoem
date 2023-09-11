#include <stdio.h>
#include <stdlib.h>

FILE *init_file(int argc, char *argv[]);
void  close_file(FILE * fp, char * filename);

void read_to_buffer(char *buffer, size_t *size_file, FILE *fp);
void set_lines_to_text(char **text, char* buffer, size_t size_file);

size_t get_size_file(FILE * fp);
size_t get_num_lines(char * buffer, size_t size_file);

void clear_text(char **text, char * buffer);
void print_text(char **text, size_t num_lines);

FILE *init_file(int argc, char *argv[])
{
    FILE *fp;
    
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

void read_to_buffer(char *buffer, size_t *size_file, FILE *fp)
{
    fread(buffer, sizeof(char), *size_file, fp);

    buffer[*size_file] = '\n';
    (*size_file)++;
}

void set_lines_to_text(char **text, char* buffer, size_t size_file)
{
    text[0] = buffer;
    
    for(size_t i = 0, j = 1; i < size_file - 1; i++){
        if (buffer[i] == '\0'){
            text[j] = &buffer[i + 1];
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
size_t get_num_lines(char * buffer, size_t size_file)
{
    size_t count = 0;
    
    for(size_t i = 0; i < size_file; i++){
        if (buffer[i] == '\n'){
            buffer[i] = '\0';
            count++;
        }
    }

    return count;
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

int main(int argc, char *argv[])
{
    FILE * fp = init_file(argc, argv);
    size_t size_file = get_size_file(fp);

    char *buffer = (char *)calloc(size_file + 1, sizeof(char));
    read_to_buffer(buffer, &size_file, fp);
    
    size_t num_lines = get_num_lines(buffer, size_file);
    
    char **text = (char **)calloc(num_lines, sizeof(char *));
    set_lines_to_text(text, buffer, size_file);

    print_text(text, num_lines);
    
    clear_text(text, buffer);
    close_file(fp, argv[1]);
}