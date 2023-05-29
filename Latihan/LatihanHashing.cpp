#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const int maxArrSize = 20;

struct data{
	char name[20];
};

struct data *dataArr[maxArrSize];

int hashFunc(char name[]){
	char first = name[0];
	char second = name[1];
	char firstLast = name[strlen(name)-1];
	char secondLast = name[strlen(name)-2];
	
	int result = ((first * second) / (firstLast + secondLast)) % maxArrSize;
	
	return result;
}

void insert(char name[]){
	struct data *temp = (struct data*)malloc(sizeof(struct data));
	strcpy(temp->name, name);
	
	//	get hash / value from hash function
	int idx = hashFunc(name);
	printf("%s %d\n", temp->name, idx);
	// if current index is NULL
	if (dataArr[idx] == 0){
		dataArr[idx] = temp;
	}
	// if current index is NOT NULL
	else {
		int currIdx = idx + 1;
		// loop until found empty spot
		while (dataArr[currIdx] != NULL) {
			currIdx++;
			if (currIdx >= maxArrSize) currIdx = 0;
			if (currIdx == idx) break;
		}
		// if array is full
		if (currIdx == idx) printf("Array is full!\n");
		//if found empty spot
		else {
			dataArr[currIdx] = temp;
		}
	}
}

void display(){
	for (int i = 0; i < maxArrSize; i++){
		if (dataArr[i] != NULL){
			printf("%s \n", dataArr[i]->name);	
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
