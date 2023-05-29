#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data{
    char name[50];
    char NIM[20];
    float GPA;

    struct data *next;
}*head = 0, *tail = 0;

void push(const char name[], const char NIM[], float GPA){
    struct data *temp = (struct data*)malloc(sizeof(struct data));
    strcpy(temp->name, name);
    strcpy(temp->NIM, NIM);
    temp->GPA = GPA;
    temp->next = NULL;

    if (head == NULL){
        head = tail = temp;
    } else if (strcmp(NIM, head->NIM) >= 0){
        temp->next = head;
        head = temp;
    } else if (strcmp(NIM, tail->NIM) <= 0){
        tail->next = temp;
        tail = temp;
    } else {
        struct data *curr = head;
        while (strcmp(curr->next->NIM, NIM) >= 0){
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
    printf("=============================\n");
    printf("| Name \t     | NIM   | \tGPA |\n");
    printf("=============================\n");
    while (curr != NULL){
        printf("| %-10s | %5s | %.2f |\n", curr->name, curr->NIM, curr->GPA);
        curr = curr->next;
    }
    printf("=============================");
}

int main(){

    push("Jason", "1002", 3.0);
    push("Justin", "6969", 2.0);
    push("Aryo", "1004", 3.6);
    push("Stephen", "1000", 3.5);
    push("Abdhy", "1001", 2.5);

    pop();

    display();

}