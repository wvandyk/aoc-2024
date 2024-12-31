#include "main.h"

struct Position {
    int x;
    int y;
};

void day3_2015(void) {
    HashNode_t root = {NULL};
    int visits_p1 = 0;
    int visits_p2 = 0;
    Position santa = {0};
    char *buffer = (char *)get_file_content("assets/day3_2015.txt");

    for(int i = 0; i < strlen(buffer); i++) {
        char key_str[10] = {0};
        sprintf(key_str, "%04d:%04d", santa.x, santa.y);

        uint32_t key = gen_hash(key_str);
        HashNode_t *node = find_node(&root, key);
        if(!node) {
            insert_node(&root, key, 0);
            node = find_node(&root, key);
            visits_p1++;
        }

        switch(buffer[i]) {
            case '^':
                node->val++;
                santa.y--;
            break;
            case '>':
                node->val++;
                santa.x++;
            break;
            case 'v':
                node->val++;
                santa.y++;
            break;
            case '<':
                node->val++;
                santa.x--;
            break;
        }
    }
    free_hash(&root);

    Position robot = {0};
    santa = {0};

    for(int i = 0; i < strlen(buffer); i++) {
        char key_str[10] = {0};
        char rkey_str[10] = {0};
        sprintf(key_str, "%04d:%04d", santa.x, santa.y);
        sprintf(rkey_str, "%04d:%04d", robot.x, robot.y);

        uint32_t key = gen_hash(key_str);
        uint32_t rkey = gen_hash(rkey_str);

        HashNode_t *node = NULL;
        Position *current = (i % 2 != 0) ? &robot : &santa;
        if(i % 2 != 0) {
            node = find_node(&root, rkey);
            if(!node) {
                insert_node(&root, rkey, 0);
                node = find_node(&root, rkey);
                visits_p2++;
            }
        } else {
            node = find_node(&root, key);
            if(!node) {
                insert_node(&root, key, 0);
                node = find_node(&root, key);
                visits_p2++;
            }
        }

        switch(buffer[i]) {
            case '^':
                node->val++;
                current->y--;
            break;
            case '>':
                node->val++;
                current->x++;
            break;
            case 'v':
                node->val++;
                current->y++;
            break;
            case '<':
                node->val++;
                current->x--;
            break;
        }
    }
    free_hash(&root);
    free(buffer);

    printf("AOC 2015 - Day 3, part 1: %d\n", visits_p1);
    printf("AOC 2015 - Day 3, part 2: %d\n", visits_p2);
}