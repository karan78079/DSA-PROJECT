#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Node {
    char filename[100];
    struct Node *left, *right;
};


struct Node* createNode(char *filename) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->filename, filename);
    newNode->left = newNode->right = NULL;
    return newNode;
}


struct Node* insert(struct Node* root, char *filename) {
    if (root == NULL) return createNode(filename);

    if (strcmp(filename, root->filename) < 0)
        root->left = insert(root->left, filename);
    else if (strcmp(filename, root->filename) > 0)
        root->right = insert(root->right, filename);

    return root;
}


void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%s\n", root->filename);
        inorder(root->right);
    }
}


struct Node* search(struct Node* root, char *filename) {
    if (root == NULL || strcmp(root->filename, filename) == 0)
        return root;
    if (strcmp(filename, root->filename) < 0)
        return search(root->left, filename);
    return search(root->right, filename);
}


struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}


struct Node* deleteNode(struct Node* root, char *filename) {
    if (root == NULL) return root;

    if (strcmp(filename, root->filename) < 0)
        root->left = deleteNode(root->left, filename);
    else if (strcmp(filename, root->filename) > 0)
        root->right = deleteNode(root->right, filename);
    else {
       
        if (remove(filename) == 0)
            printf("??? File '%s' deleted from system.\n", filename);
        else
            printf("?? Could not delete '%s' (file not found).\n", filename);

        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* temp = minValueNode(root->right);
        strcpy(root->filename, temp->filename);
        root->right = deleteNode(root->right, temp->filename);
    }
    return root;
}


struct Node* createAndInsertFile(struct Node* root, char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("? Error creating file '%s'\n", filename);
        return root;
    }
    fprintf(fp, "This is a new file named %s\n", filename);
    fclose(fp);
    printf("? File '%s' created successfully.\n", filename);
    return insert(root, filename);
}


void openFile(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("? File '%s' not found.\n", filename);
        return;
    }
    fclose(fp);

#ifdef _WIN32
    char command[200];
    sprintf(command, "notepad %s", filename);
    system(command);
#else
    char command[200];
    sprintf(command, "xdg-open %s", filename);
    system(command);
#endif
}

int main() {
    struct Node* root = NULL;
    int choice;
    char filename[100];

    // Create some default files
    root = createAndInsertFile(root, "data.txt");
    root = createAndInsertFile(root, "notes.txt");
    root = createAndInsertFile(root, "project.txt");

    while (1) {
        printf("\n====== FILE INDEXER MENU ======\n");
        printf("1. Display all files (sorted)\n");
        printf("2. Create & Insert new file\n");
        printf("3. Search for a file\n");
        printf("4. Delete a file\n");
        printf("5. Open a file\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                printf("\n?? Files in BST (sorted order):\n");
                inorder(root);
                break;
            case 2:
                printf("Enter new filename (with .txt): ");
                gets(filename);
                root = createAndInsertFile(root, filename);
                break;
            case 3:
                printf("Enter filename to search: ");
                gets(filename);
                if (search(root, filename))
                    printf("? File '%s' FOUND in BST.\n", filename);
                else
                    printf("? File '%s' NOT found.\n", filename);
                break;
            case 4:
                printf("Enter filename to delete: ");
                gets(filename);
                root = deleteNode(root, filename);
                break;
            case 5:
                printf("Enter filename to open: ");
                gets(filename);
                openFile(filename);
                break;
            case 6:
                printf("?? Exiting program...\n");
                return 0;
            default:
                printf("?? Invalid choice! Try again.\n");
        }
    }
}
