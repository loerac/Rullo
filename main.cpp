#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

// Linked list
// Allows to insert and delete easily
struct node {
	int data;
	struct node* next;
};
struct node* head = NULL;

// Functions
void insert(int data);
void deleteLast();
void display();
void print();
int sum();
int length();

int main(int argc, char** argv) {
	// Checking if there are arguements given
	if(argc < 3) {
		printf("\nError: no arguements given: %s [result] [single row/column]\n\n", argv[0]);
		return 2;
	}

	int volatile i = 0, data = 0;
	int index = 0;		// Increments up the list[]
	int pred = -1;		// The last successful predecessor that will increment
	int rullo = atoi(argv[1]);
	int size = 0; 
	int const SIZE = (argc - 2);
	int list[SIZE];

	for(i = 0; i < (argc - 2); i++) {
		if(atoi(argv[i + 2]) <= rullo) {
			list[index] = atoi(argv[i + 2]);
			index++;
			size++;
		}
	}
	
	printf("Result given: %d\n", rullo);
	printf("Row/Column given: [");
	for(i = 0; i < index; i++) { printf(" %d", list[i]); }
	printf(" ]\n=====================================\n\n");
	
	index = 0;
	for(i = 0; i < SIZE; i++) {
		while(pred != size && pred != SIZE) {
			//printf(">> %d\n", list[index]);
			insert(list[index]);
			//print();
			index++;
			if(sum() == rullo) { 
				display();
				deleteLast();
			}
			else if(sum() > rullo) { deleteLast(); }
			else { pred++; }
		
			printf("--> %d %d\n", index, pred);
			if(index >= size) {
				deleteLast();
				index = (length() == 1 ? pred : (pred + 1));
			}
		}
		for(int j = 0; j < length(); j++) { deleteLast(); }
		size--;
		pred = (i + 1);
		index = pred;
		printf("----> %d %d\n", index, pred);
		//printf("%d %d %d\n", size, pred, index);
	}
	return 0;
}

// Insert data to the list
void insert(int data) {
	struct node* link = (struct node*) malloc(sizeof(struct node));
	link->data = data;
	link->next = head;
	head = link;
}


// Delete the last node entered to the list
void deleteLast() { head = head->next; }

// Displaying the found combination
void display() {
	struct node* temp = head;

	printf("Found Combination: [ ");
	while(temp != NULL) {
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("]\n");
}

void print() {
	struct node* temp = head;

	printf("--> ");
	while(temp != NULL) {
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

// Finding the sum of the list
int sum() {
	int sum = 0;
	struct node* temp;

	for(temp = head; temp != NULL; temp = temp->next) { sum += temp->data; }
	return sum;
}

// Getting the length of the list
int length() {
	int length = 0;
	struct node* temp;
	
	for(temp = head; temp != NULL; temp = temp->next) { length++; }
	return length;
}
