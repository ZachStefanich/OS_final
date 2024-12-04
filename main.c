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
Node *createNode(int data, Node *head) {
    Node *newNode = (Node *)malloc(sizeof(Node)); // Allocate memory for the new node
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL) {
        // If the list is empty, the new node becomes the head
        return newNode;
    }

    Node *temp = head;
    // Traverse to the end of the list
    while (temp->next != NULL) {
        temp = temp->next;
    }

    // Append the new node at the end
    temp->next = newNode;

    // Return the head of the list
    return head;
}
Node *deleteNode(int del, Node *head) {
    if (head == NULL) {
        // Empty list, nothing to delete
        return NULL;
    }

    if (head->data == del) {
        // If the first node contains the data to delete
        Node *temp = head->next; // Save the pointer to the next node
        
        free(head);              // Free the current head
        
        return temp;             // Return the new head
    }
    Node *temp = head;
    while(temp->next->data!=del){
        temp = temp->next;
    }
    temp->next = temp->next->next;
    return head;
    
}
Node printList(struct Node *head){
    printf("Linked List: ");

    Node *temp = head;
    while(temp)
    {
        printf("\n");
        printf("%d", temp->data);
        
        temp = temp->next;
    }
}

int main() {
    Node *first = NULL;
    first = createNode(10,first);
    first = createNode(20,first);
    first = createNode(30,first);
    
    printList(first);
    first = deleteNode(20,first);
    printList(first);
    return 0;
}
