#include<stdio.h>
#include<string.h>

struct courses{
	char courseName[50];
	int sks;
};

struct student{
	char nim[50];
	char name[50];
	float ipk;
	struct courses c;
}s1,s2[10];

int main(){

//	struct student s1;
	
	s1.ipk = 3.5;
	strcpy(s1.name, "Jason");
	strcpy(s1.nim, "2602190450");
	strcpy(s1.c.courseName, "Data Structures");
	s1.c.sks = 4;
	
	printf("IPK: %.2f\n", s1.ipk);
	printf("Name: %s\n",s1.name);
	printf("NIM: %s\n",s1.nim);
	printf("Course Name: %s\n",s1.c.courseName);
	printf("SKS is: %d\n",s1.c.sks);
	printf("\n");
	
//	struct student s2;
	s2[0].ipk = 4.0;
	strcpy(s2[0].name, "Bintang");
	strcpy(s2[0].nim, "2602189847");
	strcpy(s2[0].c.courseName, "Data Sturctures");
	s2[0].c.sks = 4;
	
	printf("IPK: %.2f\n",s2[0].ipk);
	printf("Name: %s\n",s2[0].name);
	printf("NIM: %s\n",s2[0].nim); 
	printf("Course Name: %s\n",s2[0].c.courseName);
	printf("SKS is: %d\n",s2[0].c.sks);
	
}