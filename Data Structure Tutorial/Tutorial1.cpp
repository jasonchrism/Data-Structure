#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct PC{
    char motherboard[30];
    char processor[30];
    char vga[30];
    int RAM; //GB
    float price; //Rupiah
}data[30];

int pcCount = 0;

void inserData(char motherboard[30], char processor[30], char vga[30], int RAM, float price){
    strcpy(data[pcCount].motherboard, motherboard);
    strcpy(data[pcCount].processor, processor);
    strcpy(data[pcCount].vga, vga);
    data[pcCount].RAM = RAM;
    data[pcCount].price = price;
    pcCount++;
}

void view(){
    if (pcCount == 0){
        printf("There is no data to display!\n");
    } else {
        printf("==============================================================================================================================\n");
        printf("| No. | Motherboard\t\t       | Processor\t\t\t| VGA\t\t\t\t | RAM\t| Price      |\n");
        printf("==============================================================================================================================\n");
        for (int i = 0; i < pcCount; i++){
            printf("| %d.  | %-30s | %-30s | %-30s | %-4d | %-10.0f |\n", i + 1, data[i].motherboard, data[i].processor, data[i].vga, data[i].RAM, data[i].price);
        }
        printf("==============================================================================================================================\n");
        printf("Press enter to continue..."); getchar();
    }
}

void modify(){
    if (pcCount == 0){
        printf("There is no data to modify!.."); getchar();
    } else {
        int num;
        view();

        do {
            printf("Enter number of data to modify : ");
            scanf("%d", &num); getchar();
        } while (num < 1 || num > pcCount);
        num = num - 1;

        char motherboard[30];
        char processor[30];
        char vga[30];
        int RAM; //GB
        float price; //Rupiah
        do {
            printf("Enter New Motherboard : "); 
            scanf("%[^\n]", motherboard); getchar();
        } while (strlen(motherboard) < 1);

        do {
            printf("Enter New Processor : "); 
            scanf("%[^\n]", processor); getchar();
        } while (strlen(processor) < 1);

        do {
            printf("Enter New VGA : "); 
            scanf("%[^\n]", vga); getchar();
        } while (strlen(vga) < 1);

        do {
            printf("Enter New RAM Size : "); 
            scanf("%d", &RAM); getchar();
        } while (RAM < 1);

        do {
            printf("Enter PC Price : "); 
            scanf("%f", &price); getchar();
        } while (price < 1);

        strcpy(data[num].motherboard, motherboard);
        strcpy(data[num].processor, processor);
        strcpy(data[num].vga, vga);
        data[num].RAM = RAM;
        data[num].price = price;
        printf("Data successfully modified!\n");
        printf("Press enter to continue..."); getchar();
    }
}

void insert(){
    char motherboard[30];
    char processor[30];
    char vga[30];
    int RAM; //GB
    float price; //Rupiah
    do {
        printf("Enter Motherboard : "); 
        scanf("%[^\n]", motherboard); getchar();
    } while (strlen(motherboard) < 1);

    do {
        printf("Enter Processor : "); 
        scanf("%[^\n]", processor); getchar();
    } while (strlen(processor) < 1);

    do {
        printf("Enter VGA : "); 
        scanf("%[^\n]", vga); getchar();
    } while (strlen(vga) < 1);

    do {
        printf("Enter RAM Size : "); 
        scanf("%d", &RAM); getchar();
    } while (RAM < 1);

    do {
        printf("Enter PC Price : "); 
        scanf("%f", &price); getchar();
    } while (price < 1);

    strcpy(data[pcCount].motherboard, motherboard);
    strcpy(data[pcCount].processor, processor);
    strcpy(data[pcCount].vga, vga);
    data[pcCount].RAM = RAM;
    data[pcCount].price = price;
    pcCount++;
}

void deleteData(){
    if (pcCount == 0){
        printf("There is no data to delete!..."); getchar();
    } else {
        int num;
        view();

        do {
            printf("Choose number of data to delete : ");
            scanf("%d", &num); getchar();
        } while (num < 1 || num > pcCount);
        num = num - 1;

        for (int i = num; i < pcCount; i++){
            strcpy(data[i].motherboard, data[i+1].motherboard);
            strcpy(data[i].processor, data[i+1].processor);
            strcpy(data[i].vga, data[i+1].vga);
            data[i].RAM = data[i+1].RAM;
            data[i].price = data[i+1].price;
        }
        pcCount--;
    }
    printf("Data successfully deleted!\n");
    printf("Press enter to continue..."); getchar();
}

int main(){
    int input;
    
    inserData("ASUS TUF", "i5", "RTX 1050", 8, 15000000);
    inserData("ASUS TUF", "i7", "RTX 1050", 16, 2000000);
    inserData("ASUS TUF", "i6", "RTX 1050", 8, 8000000);


    do {
        system("cls");
        puts("1. Display PC Data");
        puts("2. Insert PC Data");
        puts("3. Modify PC Data");
        puts("4. Delete PC Data");
        puts("5. Exit");
        printf("Choose : "); scanf("%d", &input); getchar();

        switch (input){
            case 1:
                view();
                break;
            case 2:
                insert();
                break;
            case 3:
                modify();
                break;
            case 4:
                deleteData();
                break;
        }

    } while (input != 5);
}