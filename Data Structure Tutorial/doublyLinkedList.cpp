#include <stdio.h>
#include <stdlib.h>

struct node{
    int value;
    struct node *next;
}*head = 0, *tail = 0;

struct node *newNode(int value){
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp->value = value;
    temp->next = 0;
    return temp;
}

void insertHead(int value){
    struct node *temp = newNode(value);
    // IF INSERT 1ST DATA
    if (head == NULL){
        head = tail = temp;
    }
    // IF INSERT >= 2 DATA
    else {
        temp->next = head;
        head = temp;
    }
}

void insertTail(int value){
    struct node *temp = newNode(value);
    // IF INSERT THE 1ST DATA
    if (tail == NULL){
        head = tail = temp;
    }
    // if insert >= 2 data
    else {
        tail->next = temp;
        tail = temp;
    }
}

void insertMiddleDescending(int value){
    struct node *temp = newNode(value);
    struct node *curr = head;

    while (curr->next->value > value){
        curr = curr->next;
    }
    temp->next = curr->next;
    curr->next = temp;
}

void insertMiddleAscending(int value){
    struct node *temp = newNode(value);
    struct node *curr = head;

    while (curr->next->value < value){
        curr = curr->next;
    }
    temp->next = curr->next;
    curr->next = temp;
}

void displayAll(){
    struct node *curr = head;
    while (curr != 0){
        printf("%d -> ", curr->value);
        curr = curr->next;
    }
}

void insertDataAsc(int value){
    // if LL is empty
    if (head == NULL){
        // choose either insert head or insert tail
        insertHead(value);
        // insertTail(value);
    }
    // if new value is lower than head value
    else if (value < head->value){
        insertHead(value);
    }
    // if new value is higher than tail value
    else if (value > tail->value){
        insertTail(value);
    }
    // if new value is somewhere in the middle
    else {
        insertMiddleAscending(value);
    }
}

void insertDataDesc(int value){
    // if LL is empty
    if (head == NULL){
        // choose either insert head or insert tail
        insertHead(value);
        // insertTail(value);
    }
    // if new value is lower than head value
    else if (value > head->value){
        insertHead(value);
    }
    // if new value is higher than tail value
    else if (value < tail->value){
        insertTail(value);
    }
    // if new value is somewhere in the middle
    else {
        insertMiddleDescending(value);
    }
}

int main(){
     
    insertTail(50);
    insertTail(40);
    insertTail(30);
    insertTail(20);

    insertMiddleDescending(45);
    insertMiddleDescending(25);
    insertMiddleDescending(33);
    insertMiddleDescending(22);

    // insertDataDesc(40);
    // insertDataDesc(10);
    // insertDataDesc(29);
    // insertDataDesc(50);
    // insertDataDesc(1);
    // insertDataDesc(24);

    displayAll();

}