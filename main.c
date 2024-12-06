// C program to to implement binary tree
#include "semaphore.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// Define a structure for tree nodes
sem_t sem1, sem2;
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;


// Function to create a new node
Node* createNode(int data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function for inserting a node in a binary tree
void insert(Node** root, int data)
{
    Node* newNode = createNode(data);
    if (*root == NULL) {
        *root = newNode;
        return;
    }

    // Level order traversal to find the appropriate place
    // for insertion
    Node* temp;
    Node* queue[100];
    int front = -1, rear = -1;
    queue[++rear] = *root;

    while (front != rear) {
        temp = queue[++front];

        //  Insert new node as the left child
        if (temp->left == NULL) {
            temp->left = newNode;
            return;
        }
        // if left child is not missing push it to the queue
        else {
            queue[++rear] = temp->left;
        }
        // Insert new node as the right child
        if (temp->right == NULL) {
            temp->right = newNode;
            return;
        }
        // if right child is not missing push it to the
        // queue
        else {
            queue[++rear] = temp->right;
        }
    }
}

// Function to perform level order traversal to find the
// deepest rightmost node
Node* getDeepestRightmostNode(Node* root)
{
    Node* temp;
    Node* queue[100];
    int front = -1, rear = -1;
    queue[++rear] = root;

    while (front != rear) {
        temp = queue[++front];

        if (temp->left != NULL) {
            queue[++rear] = temp->left;
        }

        if (temp->right != NULL) {
            queue[++rear] = temp->right;
        }
    }
    return temp;
}

// Function for deleting deepest rightmost node in a binary
// tree
void deleteDeepestRightmostNode(Node* root, Node* dNode)
{
    Node* temp;
    Node* queue[100];
    int front = -1, rear = -1;
    queue[++rear] = root;

    while (front != rear) {
        temp = queue[++front];

        if (temp == dNode) {
            temp = NULL;
            free(dNode);
            return;
        }

        if (temp->right != NULL) {
            if (temp->right == dNode) {
                temp->right = NULL;
                free(dNode);
                return;
            }
            else {
                queue[++rear] = temp->right;
            }
        }

        if (temp->left != NULL) {
            if (temp->left == dNode) {
                temp->left = NULL;
                free(dNode);
                return;
            }
            else {
                queue[++rear] = temp->left;
            }
        }
    }
}

// Function to delete a node in the binary tree
void delete (Node** root, int data)
{
    if (*root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    if ((*root)->left == NULL && (*root)->right == NULL) {
        if ((*root)->data == data) {
            free(*root);
            *root = NULL;
            return;
        }
        else {
            printf("Node not found.\n");
            return;
        }
    }

    Node* temp;
    Node* queue[100];
    int front = -1, rear = -1;
    queue[++rear] = *root;
    Node* keyNode = NULL;

    while (front != rear) {
        temp = queue[++front];

        if (temp->data == data) {
            keyNode = temp;
        }

        if (temp->left != NULL) {
            queue[++rear] = temp->left;
        }

        if (temp->right != NULL) {
            queue[++rear] = temp->right;
        }
    }

    if (keyNode != NULL) {
        Node* deepestNode = getDeepestRightmostNode(*root);
        keyNode->data = deepestNode->data;
        deleteDeepestRightmostNode(*root, deepestNode);
    }
    else {
        printf("Node not found.\n");
    }
}

// Function to search for a node in the binary tree
Node* search(Node* root, int data)
{
    if (root == NULL) {
        return NULL;
    }

    Node* temp;
    Node* queue[100];
    int front = -1, rear = -1;
    queue[++rear] = root;

    while (front != rear) {
        temp = queue[++front];

        if (temp->data == data) {
            return temp;
        }

        if (temp->left != NULL) {
            queue[++rear] = temp->left;
        }

        if (temp->right != NULL) {
            queue[++rear] = temp->right;
        }
    }
    return NULL;
}

// function to perform inorder traversal in a binary tree
void inorderTraversal(Node* root)
{
    if (root == NULL) {
        return;
    }

    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}
void* threadA(void* arg) {
    Node** root = (Node**)arg;

    printf("Thread A: Before rendezvous\n");
    insert(root, 20);
    insert(root, 30);
    insert(root, 40);

    sem_post(&sem1);  // Signal Thread B's semaphore
    sem_wait(&sem2);  // Wait for Thread B's signal

    printf("Thread A: After rendezvous\n");
    return NULL;
}

// Thread B function
void* threadB(void* arg) {
    Node** root = (Node**)arg;

    printf("Thread B: Before rendezvous\n");
    insert(root, 50);
    insert(root, 60);
    insert(root, 70);

    sem_post(&sem2);  // Signal Thread A's semaphore
    sem_wait(&sem1);  // Wait for Thread A's signal

    printf("Thread B: After rendezvous\n");
    return NULL;
}

int main() {
    Node* root = NULL;

    // Initialize semaphores
    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 0);

    // Create threads
    pthread_t t1, t2;
    pthread_create(&t1, NULL, threadA, &root);
    pthread_create(&t2, NULL, threadB, &root);

    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Print the tree after thread operations
    printf("Inorder traversal of the binary tree: ");
    inorderTraversal(root);
    printf("\n");

    // Destroy semaphores
    sem_destroy(&sem1);
    sem_destroy(&sem2);

    return 0;
}