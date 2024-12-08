struct s {
    char raw[20];
};

bool contains_3_vowels(s str) {
    int vowels = 0;
 
    for(int i = 0; i < 20; i++) {
        switch(str.raw[i]) {
            case 'a': vowels++; break;
            case 'e': vowels++; break;
            case 'i': vowels++; break;
            case 'o': vowels++; break;
            case 'u': vowels++; break;
        }
    }
    if(vowels >= 3) {
        return true;
    }
    return false;
}

bool contains_duplicate_letter(s str) {
    char prev_letter = NULL;
    char cur_letter = NULL;
    for(int i = 0; i < 16; i++) {
        cur_letter = str.raw[i];
        if(cur_letter == prev_letter) {
            return true;
        }
        prev_letter = cur_letter;
    }
    return false;
}

bool contains_no_bad_strings(s str) {
    char *bad_strings[4] = {"ab", "cd", "pq", "xy"};
    for(int i = 0; i < 16; i++) {
        char *s = &(str.raw[i]);
        if(strncmp(s, bad_strings[0], 2) == 0) { return false; };
        if(strncmp(s, bad_strings[1], 2) == 0) { return false; };
        if(strncmp(s, bad_strings[2], 2) == 0) { return false; };
        if(strncmp(s, bad_strings[3], 2) == 0) { return false; };
    }
    return true;
}

bool contains_non_overlapping_repeats(s str) {
    for(int i = 0; i < strlen(str.raw); i++) {
        char *p = &(str.raw[i]);
        for(int j = 0; j < strlen(str.raw); j++) {
            if(((j < i - 1) || (j > i + 1)) && (strncmp(p, &(str.raw[j]), 2) == 0)) { return true; }
        }
    }
    return false;
}

bool contains_repeat_with_middle_spacer(s str) {
    for(int i = 0; i < strlen(str.raw) - 2; i++) {
        char p = str.raw[i];
        char q = str.raw[i + 2];
        if(p == q) { return true; }
    }
    return false;
}

void day5_part1(void) {
    uint8_t *buffer = get_file_content("assets/input5.txt");
    s strs[1000] = {};
    for(int i = 0; i < 1000; i++) {
        sscanf((char *)(buffer + i * 18), "%16s\n\r", strs[i].raw);
    }

    free(buffer);
    buffer = NULL;
    int nice_strings = 0;
    int nice_strings_p2 = 0;

    for(int i = 0; i < 1000; i++) {
        if(contains_3_vowels(strs[i]) && contains_duplicate_letter(strs[i]) && contains_no_bad_strings(strs[i])) {
            nice_strings++;
        }
        if (contains_non_overlapping_repeats(strs[i]) && contains_repeat_with_middle_spacer(strs[i])) {
            nice_strings_p2++;
        }
    }

    printf("AOC 2015 - Day 5, part 1: Nice strings: %d\n", nice_strings);
    printf("AOC 2015 - Day 5, part 2: Nice strings: %d\n", nice_strings_p2);

#ifdef AOC_TEST
    s test = { .raw = "aaa" };
    char *result = "PASSED";
    if (contains_non_overlapping_repeats(test)) {
        result = "FAILED";
    }
    printf("Test aaa should be naughty: %s\n", result);

    test = { .raw = "xyxy" };
    result = "FAILED";
    if (contains_non_overlapping_repeats(test)) {
        result = "PASSED";
    }
    printf("Test xyxy should be nice: %s\n", result);

    test = { .raw = "aabcdefgaa" };
    result = "FAILED";
    if (contains_non_overlapping_repeats(test)) {
        result = "PASSED";
    }
    printf("Test aabcdefgaa should be nice: %s\n", result);

    test = { .raw = "qjhvhtzxzqqjkmpb" };
    result = "FAILED";
    if (contains_non_overlapping_repeats(test) && contains_repeat_with_middle_spacer(test)) {
        result = "PASSED";
    }
    printf("Test qjhvhtzxzqqjkmpb should be nice: %s\n", result);

    test = { .raw = "uurcxstgmygtbstg" };
    result = "PASSED";
    if (contains_non_overlapping_repeats(test) && contains_repeat_with_middle_spacer(test)) {
        result = "FAILED";
    }
    printf("Test uurcxstgmygtbstg should be naughty: %s\n", result);
#endif

}
