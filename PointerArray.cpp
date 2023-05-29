#include <stdio.h>

int main(){

    int x = 10;
    // int *px = &x;

    // printf("Value of x : %d\n", x);
    // printf("Value of px : %d\n", px);
    // printf("Address of x : %d\n", &x);

    // *px = 20;
    // printf("New value of x : %d\n", x);

    // printf("%d", *(&x));

    int num[5];
    printf("Size of int : %d\n", sizeof x);
    printf("Address of num[0] : %d\n", &num[0]);
    printf("Address of num[1] : %d\n", &num[1]);
    printf("Address of num[2] : %d\n", &num[2]);
}