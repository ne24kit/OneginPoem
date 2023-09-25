#include "text.h"

int main(int argc, char *argv[])
{
    Text text;
    
    FILE *fp_read = init_read_file(argc, argv);
    FILE *fp_write = init_write_file("sorted_text.txt");

    init_Text_from_file(&text, fp_read);
    close_file(fp_read);

    sort(text.poem, 0, text.num_lines - 1, sizeof(char **), left_comp);
    write_sorted(fp_write, &text);
    
    sort(text.poem, 0, text.num_lines - 1, sizeof(char **), right_comp);
    write_sorted(fp_write, &text);
    
    write_source(fp_write, &text);
    
    close_file(fp_write);
    
    print_text(text.poem, text.num_lines);
    
    clear_Text_struct(&text);
}