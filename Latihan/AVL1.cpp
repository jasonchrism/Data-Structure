#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Food{
	char name[100];
	int price;
	int height;
	Food *left, *right;
};

Food *createFood(const char name[], int price){
	Food *newFood = (Food*)malloc(sizeof(Food));
	strcpy(newFood->name, name);
	newFood->price = price;
	newFood->height = 1;
	newFood->left = newFood->right = NULL;
	
	return newFood;
}

int getMax(int a, int b){
	return (a >= b) ? a : b;
}

int calculateHeight(Food *node){
	return (!node) ? 0 : 1 + getMax(calculateHeight(node->left), calculateHeight(node->right));
}

int getBalance(Food *node){
	return (!node) ? 0 : calculateHeight(node->left) - calculateHeight(node->right);
}

Food *rightRotate(Food *node){
	Food *newParent = node->left;
	node->left = newParent->right;
	newParent->right = node;
	
	node->height = calculateHeight(node);
	newParent->height = calculateHeight(newParent);
	
	return newParent;
}

Food *leftRotate(Food *node){
	Food *newParent = node->right;
	node->right = newParent->left;
	newParent->left = node;
	
	node->height = calculateHeight(node);
	newParent->height = calculateHeight(newParent);
	
	return newParent;
}

Food *insertFood(Food *curr, const char name[], int price){
	if (!curr){
		return createFood(name, price);
	} else if (price < curr->price){
		curr->left = insertFood(curr->left, name, price);
	} else if (price > curr->price){
		curr->right = insertFood(curr->right, name, price);
	} 
	
	curr->height = calculateHeight(curr);
	
	int balanceFactor = getBalance(curr);
	
	if (balanceFactor > 1){
		if (price > curr->price){
			curr->left = leftRotate(curr->left);
		}
		return rightRotate(curr);
	} else if (balanceFactor < -1){
		if (price < curr->price){
			curr->right = rightRotate(curr->right);
		}
		return leftRotate(curr);
	}
	
	return curr;
}

Food *deleteFood(Food *curr, int price){
	if (!curr){
		return curr;
	} else if (price < curr->price){
		curr->left = deleteFood(curr->left, price);
	} else if (price > curr->price){
		curr->right = deleteFood(curr->right, price);
	} else {
		Food *temp;
		if (!curr->left && !curr->right){
			free(curr);
			curr = NULL;
		} else if (!curr->left){
			temp = curr;
			curr = curr->right;
			free(temp);
			temp = NULL;
		} else if (!curr->right){
			temp = curr;
			curr = curr->left;
			free(temp);
			temp = NULL;
		} else {
			temp = curr->left;
			while (temp->right){
				temp = temp->right;
			}
			strcpy(curr->name, temp->name);
			curr->price = temp->price;
			curr->left = deleteFood(curr->left, temp->price);
		}
	}
	
	// curr->height = calculateHeight(curr);
	
	int balanceFactor = getBalance(curr);
	
	if (balanceFactor > 1){
		if (price > curr->price){
			curr->left = leftRotate(curr->left);
		}
		return rightRotate(curr);
	} else if (balanceFactor < -1){
		if (price < curr->price){
			curr->right = rightRotate(curr->right);
		}
		return leftRotate(curr);
	}
	
	return curr;
	
}

Food *updateFood(Food *curr, const char name[], int price){
	if (!curr){
		printf("Data not found!\n");
		return curr;
	} else if (price < curr->price){
		curr->left = updateFood(curr->left, name, price);
	} else if (price > curr->price){
		curr->right = updateFood(curr->right, name, price);
	} else {
		strcpy(curr->name, name);
		printf("Updated!");
	}
	return curr;
}

void inOrder(Food *curr){
	if (!curr){
		return;
	}
	inOrder(curr->left);
	printf("%s - %d\n", curr->name, curr->price);
	inOrder(curr->right);
}

void inOrder(Book *)

int main(){
	Food* root = insertFood(NULL, "Sate Padang", 34000);
	root = insertFood(root, "Sate Kambing", 30000);
	root = insertFood(root, "Sate Ayam", 28000);
	root = insertFood(root, "Sate Kelinci", 26000);
	root = insertFood(root, "Sate Taichan", 24000);
	root = insertFood(root, "Sate Kuda", 22000);
	
	// tampilin data
	inOrder(root);	
	
	root = updateFood(root, "Sate Taichan Pedas", 24000);
	printf("\nAfter Update\n");
	root = deleteFood(root, 22000);
	inOrder(root);

	printf("\n");
	root = updateFood(root, "Sate Taichan Pedas Banget", 40000);
	inOrder(root);

	return 0;
}
