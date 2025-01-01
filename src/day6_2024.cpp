#include "main.h"
#define DAY6_WIDTH 130
#define DAY6_HEIGHT 130

struct Guard {
    int x, y;
    int heading; // 0 - up, 1 - right, 2 - down, 3 - left
};

void day6_2024(void) {
    int day6_p1_total = 0;
    int day6_p2_total = 0;
    Guard g = {};


    char grid[DAY6_WIDTH * DAY6_HEIGHT] = {};
    char directions[4] = { '^', '>', 'v', '<' };

    char *buffer = (char *)get_file_content("assets/day6_2024.txt");
    int j = 0;
    for(int i = 0; i < strlen(buffer); i++) {
        if((buffer[i] != '\r') && (buffer[i] != '\n')) {
            grid[j++] = buffer[i];
        }
    }
    free(buffer);

    // Find guard's starting position
    for(int y = 0; y < DAY6_HEIGHT; y++) {
        for(int x = 0; x < DAY6_WIDTH; x++) {
            if(grid[x + y * DAY6_WIDTH] == '^') {
                g.x = x;
                g.y = y;
                g.heading = 0;
            }
        }
    }

    while(g.x < DAY6_WIDTH && g.x >= 0 && g.y < DAY6_HEIGHT && g.y >= 0) {
        char next_position = '.';
        
        switch(g.heading) {
            case 0: // ^
                grid[g.x + g.y * DAY6_WIDTH] = directions[g.heading];
                next_position = grid[g.x + (g.y - 1) * DAY6_WIDTH];
                if(next_position == '#') {
                    g.heading = (g.heading + 1) % 4;
                } else {
                    if(next_position == '>') {
                        day6_p2_total++;
                    } else {
                        bool found_row = false;
                        for(int c = g.x; c < DAY6_WIDTH; c++) {
                            char scan_char = grid[c + (g.y - 1) * DAY6_WIDTH];
                            if(scan_char == '>') {
                                found_row = true;
                            }
                            if((scan_char == '#') && (found_row == false)) {
                                break;
                            }
                        }
                        if(found_row) {
                            day6_p2_total++;
                        }
                    }
                    g.y--;
                }
            break;
            case 1: // >
                grid[g.x + g.y * DAY6_WIDTH] = directions[g.heading];
                next_position = grid[(g.x + 1) + g.y * DAY6_WIDTH];
                if(next_position == '#') {
                    g.heading = (g.heading + 1) % 4;
                } else {
                    if(next_position == 'v') {
                        day6_p2_total++;
                    } else {
                        bool found_row = false;
                        for(int c = g.y; c < DAY6_WIDTH; c++) {
                            char scan_char = grid[(g.x + 1) + c * DAY6_WIDTH];
                            if(scan_char == 'v') {
                                found_row = true;
                            }
                            if((scan_char == '#') && (found_row == false)) {
                                break;
                            }
                        }
                        if(found_row) {
                            day6_p2_total++;
                        }
                    }
                    g.x++;
                }
            break;
            case 2: // v
                grid[g.x + g.y * DAY6_WIDTH] = directions[g.heading];
                next_position = grid[g.x + (g.y + 1) * DAY6_WIDTH];
                if(next_position == '#') {
                    g.heading = (g.heading + 1) % 4;
                } else {
                    if(next_position == '<') {
                        day6_p2_total++;
                    }else {
                        bool found_row = false;
                        for(int c = g.x; c > 0; c--) {
                            char scan_char = grid[c + (g.y + 1) * DAY6_WIDTH];
                            if(scan_char == '<') {
                                found_row = true;
                            }
                            if((scan_char == '#') && (found_row == false)) {
                                break;
                            }
                        }
                        if(found_row) {
                            day6_p2_total++;
                        }
                    }
                    g.y++;
                }
            break;
            case 3: // <
                grid[g.x + g.y * DAY6_WIDTH] = directions[g.heading];
                next_position = grid[(g.x - 1) + g.y * DAY6_WIDTH];
                if(next_position == '#') {
                    g.heading = (g.heading + 1) % 4;
                } else {
                    if(next_position == '^') {
                        day6_p2_total++;
                    } else {
                        bool found_row = false;
                        for(int c = g.y; c > 0; c--) {
                            char scan_char = grid[(g.x - 1) + c * DAY6_WIDTH];
                            if(scan_char == '^') {
                                found_row = true;
                            }
                            if((scan_char == '#') && (found_row == false)) {
                                break;
                            }
                        }
                        if(found_row) {
                            day6_p2_total++;
                        }
                    }
                    g.x--;
                }
            break;
        }
    }

    for(int y = 0; y < DAY6_HEIGHT; y++) {
        for(int x = 0; x < DAY6_WIDTH; x++) {
            for(int d = 0; d < 4; d++) {
                if(grid[x + y * DAY6_WIDTH] == directions[d]) {
                    day6_p1_total++;
                }
            }
        }
    }

    printf("AOC 2024 - Day 6, part 1: answer: %d\n", day6_p1_total);
    printf("AOC 2024 - Day 6, part 2: answer: %d\n", day6_p2_total);
}