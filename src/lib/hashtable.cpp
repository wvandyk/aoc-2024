#define min(a, b) ((a) < (b)) ? (a) : (b)
#define HASH_STR_LEN 16
#define HASH_ALGO djb2_hash

template <typename T, size_t table_size>
struct KeyVal {
    uint64_t full_hash;
    uint64_t hash;
    T val;
};

uint64_t fnv1a_hash(const char *str, size_t length) {
    uint64_t hash = 0xcbf29ce484222325;
    uint64_t prime = 0x00000100000001b3;

    for(int i = 0; i < length; i++) {
        hash = (hash ^ str[i]) * prime;
    }
    return hash;
}

uint64_t djb2_hash(const char *str, size_t length) {
    uint64_t hash = 5381;

    for(int i = 0; i < length; i++) {
        hash = ((hash << 5) + hash) + str[i];
    }
    return hash;
}

template <typename T, size_t table_size>
bool hash_insert(KeyVal<T, table_size> table[], char *key_str, T val) {
    uint64_t full_hash = HASH_ALGO(key_str, min(HASH_STR_LEN, strlen(key_str)));
    uint64_t original_hash = full_hash % table_size;
    uint64_t hash = original_hash;
    KeyVal<T, table_size> *node = &table[hash];

    if(node && table[hash].full_hash != 0) {
        do {
            hash = (hash + 1) % table_size;
            node = &table[hash];
        } while((node && table[hash].full_hash != 0) && (hash != original_hash));
        if(hash == original_hash) {
            return false;
        }
    }

    node->hash = original_hash;
    node->full_hash = full_hash;
    node->val = val;
    return true;
}

template <typename T, size_t table_size>
KeyVal<T, table_size> *hash_find(KeyVal<T, table_size> table[], char *key_str) {
    uint64_t full_hash = HASH_ALGO(key_str, min(HASH_STR_LEN, strlen(key_str)));
    uint64_t original_hash = full_hash % table_size;
    uint64_t hash = original_hash;
    KeyVal<T, table_size> *node = &table[hash];

    if(node && table[hash].full_hash != full_hash) {
        do {
            hash = (hash + 1) % table_size;
            node = &table[hash];
        } while((hash != original_hash) && (node && table[hash].full_hash != full_hash));
        if(hash == original_hash) {
            return NULL;
        }
    }

    return node;
}