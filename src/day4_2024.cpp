#include "main.h"
#define WIDTH 140
#define HEIGHT 141

int find_xmasses(char *grid) {
    int total = 0;
    for(int y = 0; y < HEIGHT; y++) {
        for(int x = 0; x < WIDTH; x++) {
            char word[5] = {};

            if(grid[x + y * WIDTH] == 'X') {
                word[0] = grid[x + y * WIDTH];
                // check forward
                if(x <= WIDTH - 3) {
                    word[1] = grid[(x + 1) + y * WIDTH];
                    word[2] = grid[(x + 2) + y * WIDTH];
                    word[3] = grid[(x + 3) + y * WIDTH];
                    if(strncmp(word, "XMAS", 4) == 0) {
                        total++;
                    }
                }

                // check backwards
                if(x >= 3) {
                    word[1] = grid[(x - 1) + y * WIDTH];
                    word[2] = grid[(x - 2) + y * WIDTH];
                    word[3] = grid[(x - 3) + y * WIDTH];
                    if(strncmp(word, "XMAS", 4) == 0) {
                        total++;
                    }
                }

                // check up
                if(y >= 3) {
                    word[1] = grid[x + (y - 1) * WIDTH];
                    word[2] = grid[x + (y - 2) * WIDTH];
                    word[3] = grid[x + (y - 3) * WIDTH];
                    if(strncmp(word, "XMAS", 4) == 0) {
                        total++;
                    }
                }

                // check down
                if(y <= HEIGHT - 3) {
                    word[1] = grid[x + (y + 1) * WIDTH];
                    word[2] = grid[x + (y + 2) * WIDTH];
                    word[3] = grid[x + (y + 3) * WIDTH];
                    if(strncmp(word, "XMAS", 4) == 0) {
                        total++;
                    }
                }

                //check diag down + fwd
                if((y <= HEIGHT - 3) && (x <= WIDTH - 3)) {
                    word[1] = grid[(x + 1) + (y + 1) * WIDTH];
                    word[2] = grid[(x + 2) + (y + 2) * WIDTH];
                    word[3] = grid[(x + 3) + (y + 3) * WIDTH];
                    if(strncmp(word, "XMAS", 4) == 0) {
                        total++;
                    }
                }

                // check diag down + back
                if((y <= HEIGHT - 3) && (x >= 3)) {
                    word[1] = grid[(x - 1) + (y + 1) * WIDTH];
                    word[2] = grid[(x - 2) + (y + 2) * WIDTH];
                    word[3] = grid[(x - 3) + (y + 3) * WIDTH];
                    if(strncmp(word, "XMAS", 4) == 0) {
                        total++;
                    }
                }

                // check diag up + back
                if((y >= 3) && (x >= 3)) {
                    word[1] = grid[(x - 1) + (y - 1) * WIDTH];
                    word[2] = grid[(x - 2) + (y - 2) * WIDTH];
                    word[3] = grid[(x - 3) + (y - 3) * WIDTH];
                    if(strncmp(word, "XMAS", 4) == 0) {
                        total++;
                    }
                }

                // check diag up + fwd
                if((y >= 3) && (x <= WIDTH - 3)) {
                    word[1] = grid[(x + 1) + (y - 1) * WIDTH];
                    word[2] = grid[(x + 2) + (y - 2) * WIDTH];
                    word[3] = grid[(x + 3) + (y - 3) * WIDTH];
                    if(strncmp(word, "XMAS", 4) == 0) {
                        total++;
                    }
                }
            }
        }
    }

    return total;
}

int find_crossed_masses(char *grid) {
    int total = 0;
    for(int y = 1; y < HEIGHT - 1; y++) {
        for(int x = 1; x < WIDTH - 1; x++) {
            char diag_mas1[3] = {};
            char diag_mas2[3] = {};
            if(grid[x + y * WIDTH] == 'A') {
                diag_mas1[1] = grid[x + y * WIDTH];
                diag_mas2[1] = grid[x + y * WIDTH];

                diag_mas1[0] = grid[(x - 1) + (y - 1) * WIDTH];
                diag_mas1[2] = grid[(x + 1) + (y + 1) * WIDTH];

                diag_mas2[0] = grid[(x - 1) + (y + 1) * WIDTH];
                diag_mas2[2] = grid[(x + 1) + (y - 1) * WIDTH];

                if((((diag_mas1[0] == 'M') && (diag_mas1[2] == 'S')) ||
                   ((diag_mas1[0] == 'S') && (diag_mas1[2] == 'M'))) &&
                   (((diag_mas2[0] == 'M') && (diag_mas2[2] == 'S')) ||
                   ((diag_mas2[0] == 'S') && (diag_mas2[2] == 'M')))) {
                    total++;
                }
            }
        }
    }
    return total;
}

void day4_2024(void) {
    int day4_p1_total = 0;
    int day4_p2_total = 0;

    char *buffer = (char *)get_file_content("assets/day4_2024.txt");
    char grid[WIDTH * HEIGHT] = {};

    int j = 0;
    for(int i = 0; i < strlen(buffer); i++) {
        if(!((buffer[i] == '\n') || (buffer[i] == '\r'))) {
            grid[j++] = buffer[i];
        }
    }
    free(buffer);

    day4_p1_total = find_xmasses(grid);
    day4_p2_total = find_crossed_masses(grid);

    printf("AOC 2024 - Day 4, part 1: XMAS occurences: %d\n", day4_p1_total);
    printf("AOC 2024 - Day 4, part 2: X-MAS occurences: %d\n", day4_p2_total);
}