#include "main.h"

void day1_2024(void) {
    char *buffer = (char *)get_file_content("assets/day1_2024.txt");
    int left_list[1000], right_list[1000];
    for(int i = 0; i < 1000; i++) {
        sscanf(&buffer[i * 15], "%5d   %5d\r\n", &left_list[i], &right_list[i]);
    }
    free(buffer);

    quickSort(left_list, 0, arr_len(left_list) - 1);
    quickSort(right_list, 0, arr_len(right_list) - 1);

    int list_diff = 0;
    for(int i = 0; i < 1000; i++) {
        if(left_list[i] < right_list[i]) {
            list_diff += right_list[i] - left_list[i];
        } else {
            list_diff += left_list[i] - right_list[i];
        }
    }

    int list_diff_p2 = 0;
    for(int i = 0; i < 1000; i++) {
        int needle = left_list[i];
        int count = 0;
        for(int j = 0; j < 1000; j++) {
            if(right_list[j] == needle) {
                count++;
            }
        }
        list_diff_p2 += needle * count;
    }

    printf("AOC 2024 - Day 1, part 1: answer: %d\n", list_diff);
    printf("AOC 2024 - Day 1, part 2: answer: %d\n", list_diff_p2);
}