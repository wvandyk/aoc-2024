typedef struct HashNode {
    struct HashNode *parent;
    struct HashNode *lchild;
    struct HashNode *rchild;

    int val;
    uint32_t key;
} HashNode_t;

uint32_t gen_hash(char *str) {
    int len = strlen(str);
    uint32_t h = 0;
    if(len > 0) {
        for(int i = 0; i < len; i++) {
           h = 31 * h + str[i];
        }
    }
    return h;
}

HashNode_t *find_node(HashNode_t *root, uint32_t hash_key) {
    if(root->key == hash_key) {
        return root;
    } else {
        if((hash_key > root->key) && (root->rchild != NULL)) {
            return find_node(root->rchild, hash_key);
        } else if((hash_key < root->key) && (root->lchild != NULL)) {
            return find_node(root->lchild, hash_key);
        } else {
            return NULL;
        }
    }
}

void insert_node(HashNode_t *root, uint32_t hash_key, int data) {
    if(hash_key < root->key) {
        if(root->lchild == NULL) {
            root->lchild = (HashNode_t *)malloc(sizeof(HashNode_t));
            if(!root->lchild) {
                printf("insert_node: could not allocate memory for lchild node (id: %d)", hash_key);
                return;
            }
            HashNode_t *current_node = root->lchild;
            current_node->key = hash_key;
            current_node->val = data;
            current_node->parent = root;
            current_node->lchild = NULL;
            current_node->rchild = NULL;
        } else {
            insert_node(root->lchild, hash_key, data);
        }
    }

    if(hash_key > root->key) {
        if(root->rchild == NULL) {
            root->rchild = (HashNode_t *)malloc(sizeof(HashNode_t));
            if(!root->rchild) {
                printf("insert_node: could not allocate memory for rchild node (id: %d)", hash_key);
                return;
            }
            HashNode_t *current_node = root->rchild;
            current_node->key = hash_key;
            current_node->val = data;
            current_node->parent = root;
            current_node->lchild = NULL;
            current_node->rchild = NULL;
        } else {
            insert_node(root->rchild, hash_key, data);
        }
    }
}

void free_hash(HashNode_t *root) {
    HashNode_t *parent;
    if((root->lchild == NULL) && (root->rchild == NULL)) {
        parent = root->parent;
        if(parent != NULL) {
            free(root);
            root = NULL;
        }
    } else {
        if(root->lchild != NULL) {
            free_hash(root->lchild);
            root->lchild = NULL;
        }
        if(root->rchild != NULL) {
            free_hash(root->rchild);
            root->rchild = NULL;
        }
        free_hash(root);
    }
}
