#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node *head;
    pthread_rwlock_t lock; // Reader-writer lock for synchronization
} LinkedList;

typedef struct ThreadData {
    char *name;          // Thread name (e.g., "t1", "t2", "t3")
    LinkedList *list;    // Pointer to the linked list
} ThreadData;

// Initialize linked list
LinkedList *createList() {
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    list->head = NULL;
    pthread_rwlock_init(&list->lock, NULL);
    return list;
}

// Destroy linked list
void destroyList(LinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    pthread_rwlock_destroy(&list->lock);
    free(list);
}

void *reader(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    for (int i = 0; i < 5; i++) {
        pthread_rwlock_rdlock(&data->list->lock); // Acquire read lock
        printf("[%s] Linked List:", data->name);
        Node *temp = data->list->head;
        while (temp != NULL) {
            printf(" %d", temp->data);
            temp = temp->next;
        }
        printf("\n");
        pthread_rwlock_unlock(&data->list->lock); // Release read lock
        usleep(100000); // Simulate some delay
    }
    return NULL;
}

void *writer(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    for (int i = 0; i < 5; i++) {
        pthread_rwlock_wrlock(&data->list->lock); // Acquire write lock
        printf("[%s] Adding node with data: %d\n", data->name, i * 10);

        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = i * 10;
        newNode->next = NULL;

        if (data->list->head == NULL) {
            data->list->head = newNode;
        } else {
            Node *temp = data->list->head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }

        pthread_rwlock_unlock(&data->list->lock); // Release write lock
        usleep(150000); // Simulate some delay
    }
    return NULL;
}

int main() {
    LinkedList *list = createList();

    pthread_t t1, t2, t3;
    ThreadData data1 = {"t1", list};
    ThreadData data2 = {"t2", list};
    ThreadData data3 = {"t3", list};

    // Create threads
    pthread_create(&t1, NULL, writer, (void *)&data1);
    pthread_create(&t2, NULL, reader, (void *)&data2);
    pthread_create(&t3, NULL, reader, (void *)&data3);

    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    // Destroy the list
    destroyList(list);

    return 0;
}
