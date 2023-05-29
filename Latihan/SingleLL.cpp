#include <stdio.h>
#include <stdlib.h>

struct node{
    int value;
    struct node *next;
}*head = NULL;

struct node *newNode(int value){
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp->value = value;
    temp->next = NULL;
    return temp;
}

void insert(int value){
    struct node *temp = newNode(value);
    if (head == NULL){
        head = temp;
    } else {
        temp->next = head;
        head = temp;
    }

}

void deleteNode(int value){
    struct node *curr = head;
    if (head->value == value){
        head = curr->next;
        free(curr);
    } else {
        while (curr->next != NULL && curr->next->value != value){
            curr = curr->next;
        }

        if (curr->next != NULL){
            struct node *del = curr->next;
            curr->next = del->next;
            free(del);
        }
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

    deleteNode(30);

    display();
}