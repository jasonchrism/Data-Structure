#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct data{
    char name[50];
    char NIM[10];
    float GPA;

    struct data *next;
}*head = 0, *tail = 0;

void push(const char name[], const char NIM[], float GPA){
    // priority based on gpa descending
    struct data *temp = (struct data*)malloc(sizeof(struct data));
    strcpy(temp->name, name);
    strcpy(temp->NIM, NIM);
    temp->GPA = GPA;
    temp->next = NULL;
    // if LL is NULL / empty
    if (head == NULL){
        head = tail = temp;
    }
    // if new node has higher prio than head
    else if (GPA > head->GPA){
        // insert head
        temp->next = head;
        head = temp;
    }
    // if new node has lower prio than tail
    else if (GPA <= tail->GPA){
        tail->next = temp;
        tail = temp;
    }
    // if new node has prio somewhere in middle
    else {
        struct data *curr = head;
        while (curr->next->GPA >= GPA){
            curr = curr->next;
        }
        temp->next = curr->next;
        curr->next = temp;
    }
}

void pop(){
    if (head == 0){
        printf("LL is empty!\n");
    } else {
        struct data *del = head;
        head = head->next;
        free(del);
    }
}

void display(){
    struct data *curr = head;
    printf("=================================\n");
    while (curr != NULL){
        printf("| %-15s | %4s | %.2f |\n", curr->name, curr->NIM, curr->GPA);
        curr = curr->next;
    }
    printf("=================================");
}

int main(){

    push("Jason", "1122", 3.5);
    push("Chrisbellno", "2233", 3.2);
    push("Mackenzie", "2222", 3.8);
    push("Stefanus", "1111", 3.0);
    push("Justin", "1233", 2.5);
    push("Jcm", "1919", 3.4);

    pop();

    display();

}
