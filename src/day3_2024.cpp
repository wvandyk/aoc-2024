#include "main.h"

void day3_2024(void) {
    int day3_p1_total = 0;
    int day3_p2_total = 0;

    char *buffer = (char *)get_file_content("assets/day3_2024.txt");
    int left = 0;
    int right = 0;
    int length = strlen(buffer);
    bool enable_mul = true;

    for(int i = 0; i < length; i++) {
        int n = 0;

        if(strncmp(&buffer[i], "do()", 4) == 0) {
            enable_mul = true;
        }
        if(strncmp(&buffer[i], "don't()", 7) == 0) {
            enable_mul = false;
        }

        int res = sscanf(&buffer[i], "mul(%3d,%3d)%n", &left, &right, &n);
        if((res == 2) && (n != 0)) {
            day3_p1_total += left * right;
            if(enable_mul == true) {
                day3_p2_total += left * right;
            }
        }
    }
    free(buffer);

    printf("AOC 2024 - Day 3, part 1: answer: %d\n", day3_p1_total);
    printf("AOC 2024 - Day 3, part 2: answer: %d\n", day3_p2_total);
}