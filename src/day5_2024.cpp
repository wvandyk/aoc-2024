#include "main.h"
#define UPDATE_LENGTH 23
#define RULE_COUNT 1176

struct Rule {
    int left;
    int right;
};

bool operator==(Rule &lhs, Rule &rhs) {
    return ((lhs.left == rhs.left) && (lhs.right == rhs.right));
}

void zero_array(int *array, int count) {
    for(int i = 0; i < count; i++) {
        array[i] = 0;
    }
}

int present_in_rule_right(int num, Rule *rules, Rule *found_rules) {
    int j = 0;

    for(int i = 0; i < RULE_COUNT; i++) {
        if(num == rules[i].right) {
            found_rules[j++] = rules[i];
        }
    }
    return j;
}

int present_in_rule_left(int num, Rule *rules, Rule *found_rules) {
    int j = 0;

    for(int i = 0; i < RULE_COUNT; i++) {
        if(num == rules[i].left) {
            found_rules[j++] = rules[i];
        }
    }
    return j;
}

int parse_update_line(char *line, int *l) {
    zero_array(l, UPDATE_LENGTH);
    int offset = 0;
    for(int i = 0; i < UPDATE_LENGTH; i++) {
        int n = 0;
        int res = sscanf(&line[offset], "%2d,%n", &l[i], &n);
        if(res == 1) {
            offset += n;
            if(n == 0) { return i + 1; }
        }
    }
    return 0;
};

bool check_line_p1(int *update_line, int elements, Rule *rules) {
    for(int i = 0; i < elements; i++) {
        if(i < elements - 1) {
            bool fwd_match = false;
            bool bwd_match = false;
            Rule fwd = { .left = update_line[i], .right = update_line[i+1]};

            for(int j = 0; j < RULE_COUNT; j++) {
                if(fwd == rules[j]) {
                    fwd_match = true;
                }
            }
            if(!fwd_match) { return false; }
            if(i > 0) {
                Rule bwd = { .left = update_line[i - 1], .right = update_line[i]};
                for(int j = 0; j < RULE_COUNT; j++) {
                    if(bwd == rules[j]) {
                        bwd_match = true;
                    }
                }
                if(!bwd_match) { return false; }
            }
        }
    }
    return true;
}

void day5_2024(void) {
    int day5_p1_total = 0;
    int day5_p2_total = 0;
    Rule rules[RULE_COUNT] = {};
    int update_line[UPDATE_LENGTH] = {};

    char *buffer = (char *)get_file_content("assets/day5_2024.txt");
    char *line = strtok(buffer, "\r\n");
    int i = 0;

    while(line != NULL) {
        if(i < RULE_COUNT) {
            int n = 0;
            int tmp_left = 0;
            int tmp_right = 0;
            sscanf(line, "%2d|%2d%n", &tmp_left, &tmp_right, &n);
            if(n > 0) {
                rules[i].left = tmp_left;
                rules[i].right = tmp_right;
                i++;
            }
        } else {
            int length = parse_update_line(line, update_line);
            bool result = check_line_p1(update_line, length, rules);
            if(result) {
                int mid_idx = (int)((length / 2.0) + 0.5) - 1;
                day5_p1_total += update_line[mid_idx];
            } else {
                // fix the update by rearanging it
                bool result2 = false;
                while(result2 == false) {
                    for(int x = 0; x < length - 1; x++) {
                        Rule left_rules[RULE_COUNT] = {};
                        Rule right_rules[RULE_COUNT] = {};
                        int left_found_count = present_in_rule_left(update_line[x], rules, left_rules);
                        int right_found_count = present_in_rule_right(update_line[x + 1], left_rules, right_rules);
                        if((left_found_count == 0) || (right_found_count == 0)) {
                            swap(&update_line[x], &update_line[x + 1]);
                        }
                    }
                    result2 = check_line_p1(update_line, length, rules);
                }
                int mid_idx = (int)((length / 2.0) + 0.5) - 1;
                day5_p2_total += update_line[mid_idx];
            }
        }
        line = strtok(NULL, "\r\n");
    }
    free(buffer);

    printf("AOC 2024 - Day 5, part 1: middle number total: %d\n", day5_p1_total);
    printf("AOC 2024 - Day 5, part 2: middle number total: %d\n", day5_p2_total);
}