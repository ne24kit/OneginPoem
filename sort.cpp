#include <stdio.h>

#define ANSI_COLOR_RED       "\x1b[31m"
#define ANSI_COLOR_BLUE      "\x1b[38;5;27m"
#define ANSI_COLOR_YELLOW    "\x1b[33m"
#define ANSI_COLOR_CYAN      "\x1b[36m"
#define ANSI_COLOR_LIGHT_RED "\x1b[38;5;198m"	
#define ANSI_COLOR_MAGENTA   "\x1b[35m"
#define ANSI_COLOR_GREEN     "\x1b[32m"
#define ANSI_COLOR_RESET     "\x1b[0m"

void Sort(int data[], size_t left, size_t right);
size_t Partition(int data[], size_t left, size_t right);

void debug_print(int data[], size_t left, size_t right);

void swap(int *elem1, int *elem2);

void print_array(int data[]);

size_t size_array = 0;

void swap(int *elem1, int *elem2)
{
    int temp = *elem1;
    *elem1 = *elem2;
    *elem2 = temp;
}

size_t Partition(int data[], size_t left, size_t right)
{
    int mid_elem = data[(left + right) / 2];
       
    debug_print(data, left, right);
    while(true){
        
        while(data[left] < mid_elem){
            left++;
            debug_print(data, left, right);
        }

        while(data[right] > mid_elem){
            right--;
            debug_print(data, left, right);
        }

        if (left >= right)
            return right;

        debug_print(data, left, right);
        swap(data + left, data + right);
        left++;
        right--;
        debug_print(data, left, right);
    }

}

void Sort(int data[], size_t left, size_t right)
{

    if (left + 1 == right){
        if (data[left] > data[right]){
            swap(data + left, data + right);
            debug_print(data, left, right);
        }
        return;
    }

    if (left < right){
        size_t mid = Partition(data, left, right);
        Sort(data, left, mid);
        Sort(data, mid + 1, right);
    }
}

void print_array(int data[])
{
  for(size_t i = 0; i < size_array; i++)
    printf("%d ", data[i]);
  printf("\n");
}

void debug_print(int data[], size_t left, size_t right)
{
    for(size_t i = 0; i < size_array; i++)
        if (i < left)
            printf(ANSI_COLOR_BLUE "%2d " ANSI_COLOR_RESET, data[i]);
        else if (i == left)
            printf(ANSI_COLOR_CYAN "%2d " ANSI_COLOR_RESET, data[i]);
        else if (left < i && i < right)
            printf(ANSI_COLOR_GREEN "%2d " ANSI_COLOR_RESET, data[i]);
        else if (i == right)
            printf(ANSI_COLOR_LIGHT_RED "%2d " ANSI_COLOR_RESET, data[i]);
        else if (i > right)
            printf(ANSI_COLOR_RED "%2d " ANSI_COLOR_RESET, data[i]);
    
    printf("\n");
}

int main()
{
    int data[] = {32, 92, 5, 5, 5, 5, 34, 16, 57, 14, 70, 3, 17, 98, 9, 17, 86, 77, 61, 83, 9, 36, 16, 88, 4, 38, 5, 1, 92, 19, 75, 15, 56, 44, 26, 21, 72, 45, 85, 75, 41, 74, 62, 41, 15, 35, 92, 89, 45, 82};
    size_array = sizeof(data)/sizeof(data[0]);
    
    print_array(data);

    Sort(data, 0, sizeof(data)/sizeof(data[0]) - 1);

    print_array(data);
}