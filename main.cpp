#include<stdio.h>
#include<stdlib.h>
 
/* Type marker stick: using bits to indicate what's chosen.  The stick can't
 * handle more than 32 items, but the idea is there; at worst, use array instead */
typedef unsigned long marker;
marker one = 1;

struct node {
    int value;
    struct node *next;
};
struct node *head = NULL;

void comb(int size, int curr, int list[], int rullo, marker chosen, int at);
void insertFirst(int value);
void deleteFirst();
void printList();
int sum();
int length();

int main(int argc, char **argv) {
    if(argc < 3) {
        printf("Error: No arguments given: %s [rullo number] [set of row/column]\n", argv[0]);
        return 2;
    }

    int i = 0;
    int rullo = atoi(argv[1]);

    for(i = 2; i < argc; i++) {
        if(atoi(argv[i]) <= rullo) { insertFirst(atoi(argv[i])); }
    }

    int const SIZE = length();
    int list[SIZE];
    for(i = 0; i < SIZE; i++) {
        list[i] = head->value;
        head = head->next;
    }
    while(length()) { deleteFirst(); }

    printf("Rullo number: %d\n", rullo);
    printf("Accepted set: [ ");
    for(i = 0; i < SIZE; i++) { printf("%d ", list[i]); }
    printf("]\n==========================================\n");
    for(i = 0; i < (SIZE + 1); i++) { comb(SIZE, i, list, rullo, 0, 0); }
    printf("\n");
    return 0;
}

// Implementing the combinatorics code from Rosetta Code
// http://rosettacode.org/wiki/Combinations#C.2B.2B
void comb(int size, int curr, int list[], int rullo, marker chosen, int i) {
    if (size < (curr + i)) { return; } /* not enough bits left */
 
    if (!curr) {
        /* got all we curred; print the thing.  if other actions are
         * desired, we could have passed in a callback function. */
        for(i = 0; i < size; i++) { if (chosen & (one << i)) { insertFirst(list[i]); } }
        if(sum() == rullo) { printList(); }
        while(length()) { deleteFirst(); }
        return;
    }
    /* if we choose the current item, "or" (|) the bit to mark it so. */
    comb(size, curr - 1, list, rullo, chosen | (one << i), i + 1);
    comb(size, curr, list, rullo, chosen, i + 1);  /* or don't choose it, go to next */
}
 
void insertFirst(int value) {
    struct node* temp = (struct node*) malloc(sizeof(struct node));
    temp->value = value;
    temp->next = head;
    head = temp;
}

void deleteFirst() { head = head->next; }

void printList() {
    struct node *temp = head;

    printf("Found combination: [ ");
    while(temp != NULL) {
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("]\n");
}

int sum() {
    int sum = 0;
    struct node *temp;
    for(temp = head; temp != NULL; temp = temp->next) { sum += temp->value; }
    return sum;
}

int length() {
    int length = 0;
    struct node *temp;
    for(temp = head; temp != NULL; temp = temp->next) { length++; }
    return length;
}
