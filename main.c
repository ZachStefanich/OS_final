#//include <pthread.h>
//#include "semaphore.h" 
#include <stdio.h>
#include <stdlib.h>

// Defines the structure of the node type
typedef struct Node{
    //data field, this is the value in the node
    //doesn't have to be a node
    int data;
    //pointer to the next node
    struct Node *next;
}Node;

//function needed to create a new node, and return a pointer to the current node
Node *createNode(int data){
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
int main() {
    Node *first = createNode(10);
    first->next = createNode(20);
    first->next->next = createNode(30);
   
    printf("Linked List: ");

    Node *temp = first;
    while(temp)
    {
        printf("%d", temp->data);
        printf(" ");
        temp = temp->next;
    }

    return 0;
}