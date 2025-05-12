#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure for each node in the linked list
typedef struct Node {
    int data;
    struct Node* next;
    struct Set* setPtr;
} Node;

// Structure for the set (linked list)
typedef struct Set {
    Node* head;
    Node* tail;
    int size;
} Set;

Node* elements[MAX];  // Array of node pointers

// Function to create a singleton set
void makeSet(int x) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    Set* newSet = (Set*)malloc(sizeof(Set));

    newNode->data = x;
    newNode->next = NULL;
    newNode->setPtr = newSet;

    newSet->head = newNode;
    newSet->tail = newNode;
    newSet->size = 1;

    elements[x] = newNode;
}

// Function to find the representative of the set containing x
int findSet(int x) {
    return elements[x]->setPtr->head->data;
}

// Function to union two sets by size
void unionSets(int x, int y) {
    Node* nodeX = elements[x];
    Node* nodeY = elements[y];

    Set* setX = nodeX->setPtr;
    Set* setY = nodeY->setPtr;

    if (setX == setY) return;  // Already in the same set

    // **Weighted union: always append the smaller list to the larger one**
    if (setX->size < setY->size) {
        // **Traverse setX and update setPtr of each node to point to setY**
        Node* temp = setX->head;
        while (temp != NULL) {
            temp->setPtr = setY;
            temp = temp->next;
        }

        // **Append list X to list Y**
        setY->tail->next = setX->head;
        setY->tail = setX->tail;
        setY->size += setX->size;

        free(setX);  // Free the old set
    } else {
        // **Traverse setY and update setPtr of each node to point to setX**
        Node* temp = setY->head;
        while (temp != NULL) {
            temp->setPtr = setX;
            temp = temp->next;
        }

        // **Append list Y to list X**
        setX->tail->next = setY->head;
        setX->tail = setY->tail;
        setX->size += setY->size;

        free(setY);  // Free the old set
    }
}

// Function to print the set of an element
void printSet(int x) {
    Node* temp = elements[x]->setPtr->head;
    printf("Set containing %d: ", x);
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Example usage
int main() {
    int i;

    // Create singleton sets
    for (i = 1; i <= 6; i++) {
        makeSet(i);
    }

    unionSets(1, 2);
    unionSets(3, 4);
    unionSets(1, 4);
    unionSets(5, 6);
    unionSets(1, 5);

    for (i = 1; i <= 6; i++) {
        printSet(i);
    }

    return 0;
}
