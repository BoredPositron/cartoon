#include <stdio.h>
#include <stdlib.h>

// Node structure for B-tree
typedef struct BTreeNode {
    int n; // Number of keys in the node
    int keys[3]; // Array to store keys
    struct BTreeNode* children[4]; // Pointers to child nodes
    int leaf; // 1 if node is a leaf, 0 otherwise
} BTreeNode;

// Function to create a new B-tree node
BTreeNode* createNode(int leaf) {
    BTreeNode* newNode = (BTreeNode*)malloc(sizeof(BTreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    newNode->n = 0;
    for (int i = 0; i < 4; i++) {
        newNode->children[i] = NULL;
    }
    newNode->leaf = leaf;

    return newNode;
}

// Function to insert a key into a non-full B-tree node
void insertNonFull(BTreeNode* x, int key);

// Function to split a child node of a B-tree node
void splitChild(BTreeNode* x, int i) {
    BTreeNode* y = x->children[i];
    BTreeNode* z = createNode(y->leaf);
    x->children[i + 1] = z;
    x->keys[i] = y->keys[1];
    z->n = 1;

    for (int j = 0; j < 2; j++) {
        z->keys[j] = y->keys[j + 2];
    }

    y->n = 1;
}

// Function to insert a key into a B-tree
void insert(BTreeNode** root, int key) {
    BTreeNode* r = *root;
    if (r->n == 3) {
        BTreeNode* s = createNode(0);
        *root = s;
        s->children[0] = r;
        splitChild(s, 0);
        insertNonFull(s, key);
    } else {
        insertNonFull(r, key);
    }
}

// Function to insert a key into a non-full B-tree node
void insertNonFull(BTreeNode* x, int key) {
    int i = x->n - 1;
    if (x->leaf) {
        while (i >= 0 && key < x->keys[i]) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = key;
        x->n++;
    } else {
        while (i >= 0 && key < x->keys[i]) {
            i--;
        }
        i++;

        if (x->children[i]->n == 3) {
            splitChild(x, i);

            if (key > x->keys[i]) {
                i++;
            }
        }
        insertNonFull(x->children[i], key);
    }
}

// Function to delete a key from a B-tree
void deleteKey(BTreeNode* x, int key) {
    // Implement deletion logic here
}

// Function to search for a key in a B-tree
BTreeNode* search(BTreeNode* x, int key) {
    int i = 0;
    while (i < x->n && key > x->keys[i]) {
        i++;
    }

    if (i < x->n && key == x->keys[i]) {
        return x;
    }

    if (x->leaf) {
        return NULL;
    }

    return search(x->children[i], key);
}

// Function to print the keys in a B-tree in-order
void printInOrder(BTreeNode* x) {
    int i;
    for (i = 0; i < x->n; i++) {
        if (!x->leaf) {
            printInOrder(x->children[i]);
        }
        printf("%d ", x->keys[i]);
    }

    if (!x->leaf) {
        printInOrder(x->children[i]);
    }
}

int main() {
    BTreeNode* root = createNode(1); // Create a B-tree node with leaf = 1

    // Insert keys into the B-tree
    int keys[] = {90, 27, 7, 9, 18, 21, 3, 4, 16, 11, 23, 72};
    int numKeys = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < numKeys; i++) {
        insert(&root, keys[i]);
    }

    // Print the B-tree in-order
    printf("B-tree after insertion: ");
    printInOrder(root);
    printf("\n");

    // Delete keys from the B-tree
    int keysToDelete[] = {7, 16, 72};
    int numKeysToDelete = sizeof(keysToDelete) / sizeof(keysToDelete[0]);

    for (int i = 0; i < numKeysToDelete; i++) {
        deleteKey(root, keysToDelete[i]);
        printf("B-tree after deleting %d: ", keysToDelete[i]);
        printInOrder(root);
        printf("\n");
    }

    return 0;
}
