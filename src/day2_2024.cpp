#include "main.h"

bool is_line_safe_p1(int *levels, int level_count) {
    int level_diffs[7] = {-20, -20, -20, -20, -20, -20, -20};
    for(int j = 0; j < level_count - 1; j++) {
        if(levels[j + 1] == 0) { continue; }
        level_diffs[j] = levels[j + 1] - levels[j];
    }

    int prev_diff = -20;
    bool safe_string = true;
    for(int j = 0; j < level_count - 1; j++) {
        int diff = level_diffs[j];

        if((abs(diff) < 1) || (abs(diff) > 3)) {
            safe_string = false;
        }

        if((prev_diff != -20) && ((diff < 0 && prev_diff > 0) || (diff > 0 && prev_diff < 0))) {
            safe_string = false;
        }

        prev_diff = diff;
    }
    return safe_string;
}

bool is_line_safe_p2(int *levels, int level_count) {
    if(!is_line_safe_p1(levels, level_count)) {
        int permutation[8] = {};
        for(int current_p = 0; current_p < level_count; current_p++) {
            int j = 0;
            for(int i = 0; i < level_count; i++) {
                if(i == current_p) {
                    continue;
                } else {
                    permutation[j++] = levels[i];
                }
            }
            if(is_line_safe_p1(permutation, level_count - 1)) {
                return true;
            };
        }
    }
    return false;
}

void day2_2024(void) {
    int safe_reports = 0;
    int safe_reports_p2 = 0;
    char line[255];

    FILE *f = fopen("assets/day2_2024.txt", "rb");
    if(f == NULL) {
        perror("Could not open input file!\n");
        exit(EXIT_FAILURE);
    }

    while(fgets(line, 255, f)) {
        line[strcspn(line, "\n")] = 0;
        line[strcspn(line, "\r")] = 0;

        char *token = strtok(line, " ");
        int i = 0;
        int levels[8] = {};
        int lc = 0;
        
        levels[i++] = atoi(token);
        lc++;
        while(token != NULL) {
            token = strtok(NULL, " ");
            if(token != NULL) {
                levels[i++] = atoi(token);
                lc++;
            } else {
                i = 0;
            }
        }

        if(is_line_safe_p1(levels, lc) == true) { 
            safe_reports++;
            safe_reports_p2++;
        } else if(is_line_safe_p2(levels, lc) == true) {
            safe_reports_p2++;
        }
    }

    fclose(f);
    printf("AOC 2024 - Day 2, part 1: safe reports: %d\n", safe_reports);
    printf("AOC 2024 - Day 2, part 2: safe reports: %d\n", safe_reports_p2);
}