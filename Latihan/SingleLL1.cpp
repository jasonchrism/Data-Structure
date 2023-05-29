#include <stdio.h>
#include <stdlib.h>

struct data{
    int value;
    struct data *next;
}*head = NULL;

struct data *newNode(int value){
    struct data *temp = (struct data*)malloc(sizeof(struct data));
    temp->value = value;
    temp->next = NULL;
    return temp;
}

void insert(int value){
    struct data *temp = newNode(value);
    if (!head){
        head = temp;
    } else {
        temp->next = head;
        head = temp;
    }
}

void deleteNode(int value){
    struct data *curr = head;
    if (curr->value == value){
        head = curr->next;
        free(curr);
    } else {
        while (curr->next != NULL && curr->next->value != value){
            curr = curr->next;
        }
        if (curr->next != NULL){
            struct data *del = curr->next;
            curr->next = del->next;
            free(del);
        }
    }
}

void display(){
    struct data *curr = head;
    while (curr != NULL){
        printf("%d -> ", curr->value);
        curr = curr->next;
    }
}

int main(){

    insert(10);
    insert(20);
    insert(30);
    insert(40);
    deleteNode(20);
    display();

}