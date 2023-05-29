#include <stdio.h>
#include <stdlib.h>

struct node{
    int value;
    struct node *next;
    struct node *prev;
}*head = 0, *tail = 0;

struct node *newNode(int value){
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp->value = value;
    temp->next = temp->prev = 0;
    return temp;
}

void insert(int value){
    struct node *temp = newNode(value);

    if (head == 0){
        head = tail = temp;
    } else {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
}

void display(){
    struct node *curr = head;
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
    insert(50);

    display();

}