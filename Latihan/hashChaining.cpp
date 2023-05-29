#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxSize = 20;

struct data{
    char name[100];
    int age;
    struct data *next;
};

struct data *dataArr[maxSize];

int hashFunc(const char name[]){
    int first = name[0];
    int last = name[strlen(name) - 1];
    int res = (first + last) % maxSize;
    return res;
}

void insert(const char name[], int age){
    struct data *temp = (struct data*)malloc(sizeof(data));
    strcpy(temp->name, name);
    temp->age = age;
    temp->next = NULL;

    int idx = hashFunc(name);
    if (dataArr[idx] == 0){
        dataArr[idx] = temp;
    } else {
        struct data *curr = dataArr[idx];
        while (curr->next != NULL){
            curr = curr->next;
        }
        curr->next = temp;
    }
}

void display(){
    for (int i  = 0; i < maxSize; i++){
        if (dataArr[i] != NULL){
            struct data *curr = dataArr[i];
            while (curr){
                printf("%s - %d --> ", curr->name, curr->age);
                curr = curr->next;
            }
            printf("\n");
        }
    }
}

int main(){

	insert("axe", 1);
	insert("invoker", 1);
	insert("sven", 1);
	insert("axe", 1);
	insert("sven", 1);
	insert("magnus", 1);	
	insert("juggernaut", 1);
	insert("sniper", 1);
	insert("andre", 1);
	insert("junt", 1);
    display();

}