#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxArrSize = 20;

struct data{
	char name[20];
	
	struct data *next;
};

struct data *dataArr[maxArrSize];

int hashFunc(char name[]){
	char first = name[0];
	char second =  name[1];
	char firstLast = name[strlen(name)-1];
	char secondLast = name[strlen(name)-2];
	
	int res = ((first * second) / (firstLast + secondLast)) % maxArrSize;
	return res;
}

void insert(char name[]){
	struct data *temp = (struct data*)malloc(sizeof(struct data));
	strcpy(temp->name, name);
	temp->next = NULL;
	
//	get hash / value from hash function
	int idx = hashFunc(name);
//	printf("%d\n", idx);
// insert to hash value, apply chaining if needed
// if current idx in hash table is empty
	if (dataArr[idx] == 0){
		dataArr[idx] = temp;
	}
// if current idx in hash table is not empty
	else {
		struct data *curr = dataArr[idx];
		while (curr->	next != NULL) {
			curr = curr->next;
		}
		curr->next = temp;
	}
}

void display(){
	for (int i = 0; i < maxArrSize; i++){
		// if current idx is not empty
		if (dataArr[i] != 0){
			struct data *curr = dataArr[i];
			while (curr){
				printf("%s -> ", curr->name);
				curr = curr->next;
			}
			printf("\n");
		}
	}
}

int main(){
	
	insert("Youtube21");
	insert("noobmaster96");
	insert("xTyranx");
	insert("Revan789");
	insert("Mario");
	insert("RoboFox");	
	insert("SnakeyBoy");	
	insert("Derp");
	insert("Herpina");
	insert("DonChef");		
	
	display();	
}
