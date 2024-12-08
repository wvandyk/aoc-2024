#include "main.h"

void day6_2015(void) {
    char lights[1000000] = {};
    char *lines[300] = {};
    
    int start_x, start_y, end_x, end_y;
    start_x = start_y = end_x = end_y = 0;

    char *buffer = (char *)get_file_content("assets/input6.txt");
    
    for(int i = 0; i < 300; i++) {
        sscanf(&(buffer[i * 15]), "%5d   %5d\r\n", &(left_list[i]), &(right_list[i]));
    }
    free(buffer);
}