#include <stdio.h>
#include <stdlib.h>

struct data{
    int value;
    struct data *next;
    struct data *prev;
}*head = 0, *tail = 0;

struct data *newNode(int value){
    struct data *temp = (struct data*)malloc(sizeof(struct data));
    temp->value = value;
    temp->next = temp->prev = NULL;
    return temp;
}

void insert(int value){
    struct data *temp = newNode(value);
    if (head == NULL){
        head = tail = temp;
    } else {
        temp->prev = tail;
        tail->next = temp;
        tail = temp;
    }
}

void deleteNode(int value){
    struct data *curr = head;
    if (head->value == value){
        head = head->next;
        free(head->prev);
        head->prev = 0;
    } else if (tail->value == value){
        tail = tail->prev;
        free(tail->next);
        tail->next = 0;
    } else {
        while (curr->next != NULL && curr->next->value != value){
            curr == curr->next;
        }
        if (curr->next != NULL){
            struct data *del = curr->next;
            curr->next = del->next;
            del->next->prev = curr;
            free(del);
        }
    }
}

void display(){
    struct data *curr = head;
    while (curr != NULL){
        printf("%d -> ",curr->value);
        curr = curr->next;
    }
}

int main(){

    insert(10);
    insert(20);
    insert(30);
    insert(40);
    insert(50);
    display();

}