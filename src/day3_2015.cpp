#define HASH_TABLE_SIZE 5000
#include "main.h"

struct Position {
    int x;
    int y;
};

typedef KeyVal<int32_t, HASH_TABLE_SIZE> HashTable;

void day3_2015(void) {
    HashTable hashtable[HASH_TABLE_SIZE] = {};
    int visits_p1 = 0;
    int visits_p2 = 0;
    Position santa = {0};
    char *buffer = (char *)get_file_content("assets/day3_2015.txt");

    for(int i = 0; i < strlen(buffer); i++) {
        char key_str[10] = {0};
        sprintf(key_str, "%04d:%04d", santa.x, santa.y);
        HashTable *hash_node = hash_find(hashtable, key_str);
        if(!hash_node) {
            hash_insert(hashtable, key_str, 0);
            hash_node = hash_find(hashtable, key_str);
            visits_p1++;
        }

        switch(buffer[i]) {
            case '^':
                hash_node->val++;
                santa.y--;
            break;
            case '>':
                hash_node->val++;
                santa.x++;
            break;
            case 'v':
                hash_node->val++;
                santa.y++;
            break;
            case '<':
                hash_node->val++;
                santa.x--;
            break;
        }
    }


    Position robot = {0};
    santa = {0};
    memset(&hashtable, 0, HASH_TABLE_SIZE * sizeof(HashTable));

    for(int i = 0; i < strlen(buffer); i++) {
        char key_str[10] = {0};
        char rkey_str[10] = {0};
        sprintf(key_str, "%04d:%04d", santa.x, santa.y);
        sprintf(rkey_str, "%04d:%04d", robot.x, robot.y);

        HashTable *node = NULL;
        Position *current = (i % 2 != 0) ? &robot : &santa;
        if(i % 2 != 0) {
            node = hash_find(hashtable, rkey_str);
            if(!node) {
                hash_insert(hashtable, rkey_str, 0);
                node = hash_find(hashtable, rkey_str);
                visits_p2++;
            }
        } else {
            node = hash_find(hashtable, key_str);
            if(!node) {
                hash_insert(hashtable, key_str, 0);
                node = hash_find(hashtable, key_str);
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

    free(buffer);

    printf("AOC 2015 - Day 3, part 1: answer: %d\n", visits_p1);
    printf("AOC 2015 - Day 3, part 2: answer: %d\n", visits_p2);
}