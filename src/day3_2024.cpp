#include "main.h"

void day3_2024(void) {
    int day3_p1_total = 0;
    int day3_p2_total = 0;

    char *buffer = (char *)get_file_content("assets/day3_2024.txt");
    int left_list[1000] = {};
    int right_list[1000] = {};
    int j = 0;
    int length = strlen(buffer);
    bool enable_mul = true;

    for(int i = 0; i < length; i++) {
        char *b = &buffer[i];
        int n = 0;
        int n2 = 0;

        sscanf(b, "do()%n", &n2);
        if(n2 > 0) {
            enable_mul = true;
        }

        n2 = 0;
        sscanf(b, "don't()%n", &n2);
        if(n2 > 0) {
            enable_mul = false;
        }

        int res = sscanf(b, "mul(%3d,%3d)%n", &left_list[j], &right_list[j], &n);
        if((res == 2) && (n != 0)) {
            day3_p1_total += left_list[j] * right_list[j];
            if(enable_mul == true) {
                day3_p2_total += left_list[j] * right_list[j];
            }
            j++;
        }
    }
    free(buffer);

    printf("AOC 2024 - Day 3, part 1: sum of multiplications: %d\n", day3_p1_total);
    printf("AOC 2024 - Day 3, part 2: sum of multiplications: %d\n", day3_p2_total);
}