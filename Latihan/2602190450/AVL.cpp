#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int i = 1;
int count = 0;

struct User{
	char username[100];
	char job[100];
	int score;
	int matchCount;
	int winCount;
	int loseCount;
	int drawCount;
	double rate;
	
	int height;
	User *left, *right, *next;
};

User *createUser(const char username[], const char job[], int score, double matchCount, double winCount, int loseCount, int drawCount){
	User *newUser = (User*)malloc(sizeof(User));
	strcpy(newUser->username, username);
	strcpy(newUser->job, job);
	newUser->score = score;
	newUser->matchCount = matchCount;
	newUser->winCount = winCount;
	newUser->loseCount = loseCount;
	newUser->drawCount = drawCount;
	newUser->rate = (winCount / matchCount) * 100;
	newUser->height = 1;
	newUser->left = newUser->right = newUser->next = NULL;
	
	return newUser;
}

int getMax(int a, int b){
	return (a >= b) ? a : b;
}

int calculateHeight(User *node){
	return (!node) ? 0 : 1 + getMax(calculateHeight(node->left), calculateHeight(node->right)); 
}

int getBalance(User *node){
	return (!node) ? 0 : (calculateHeight(node->left) - calculateHeight(node->right));
}

void push(User* root, User* newParent){
	User* temp = root;
	while(temp->next != NULL && temp->next->rate >= newParent->rate){
		if(temp->next == NULL){
			break;
		}
		temp = temp->next;
	}
	newParent->next = temp->next;
	temp->next = newParent; 
}

User *rightRotate(User *node){
	User *newParent = node->left;
	node->left = newParent->right;
	newParent->right = node;
	
	node->height = calculateHeight(node);
	newParent->height = calculateHeight(newParent); 
	
	return newParent;
}

User *leftRotate(User *node){
	User *newParent = node->right;
	node->right = newParent->left;
	newParent->left = node;
	
	node->height = calculateHeight(node);
	newParent->height = calculateHeight(newParent);
	
	return newParent;
}

User *insertUser(User *root, const char username[], const char job[], int score, double matchCount, double winCount, int loseCount, int drawCount){
	int winRate = (winCount / matchCount) * 100;
	if (!root){
		return createUser(username, job, score, matchCount, winCount, loseCount, drawCount);
	} else if (score == root->score){
		if (winRate < root->rate){
			root->left = insertUser(root->left, username, job, score, matchCount, winCount, loseCount, drawCount);
		} else {
			root->right = insertUser(root->right, username, job, score, matchCount, winCount, loseCount, drawCount);
		}
	} else if (score < root->score){
		root->left = insertUser(root->left, username, job, score, matchCount, winCount, loseCount, drawCount);
	} else if (score > root->score){
		root->right = insertUser(root->right, username, job, score, matchCount, winCount, loseCount, drawCount);
	} else{ 
		push(root, createUser(username, job, score, matchCount, winCount, loseCount, drawCount));
	}
	
	root->height =  calculateHeight(root);
	int balance = getBalance(root);
	
	if (balance > 1){
		if (score > root->score){
			root->left = leftRotate(root->left);
		}
		return rightRotate(root);
	} else if (balance < -1){
		if (score < root->score){
			root->right = rightRotate(root->right);
		}
		return leftRotate(root);
	}
	return root;
}

User *deleteUser(User *curr, int score){
	if (!curr){
		return curr;
	} else if (score < curr->score){
		curr->left = deleteUser(curr->left, score);
	} else if (score > curr->score){
		curr->right = deleteUser(curr->right, score);
	} else {
		if (!curr->right && !curr->left){
			free(curr);
			curr = NULL;
			return curr;
		} else if (!curr->left){
			User *temp = curr->left;
			free(curr);
			return temp;
		} else if (!curr->right){
			User *temp = curr->right;
			free(curr);
			return temp;
		} else {
			User *temp = curr->left;
			while (temp->right){
				temp = temp->right;
			}
			strcpy(curr->username, temp->username);
			strcpy(curr->job, temp->job);
			curr->winCount = temp->winCount;
			curr->matchCount = temp->matchCount;
			curr->loseCount = temp->loseCount;
			curr->rate = temp->rate;
			curr->score = temp->score;
			curr->left = deleteUser(curr->left, temp->score);
		}
	}
	
	curr->height =  calculateHeight(curr);
	int balance = getBalance(curr);
	
	if (balance > 1){
		if (score > curr->score){
			curr->left = leftRotate(curr->left);
		}
		return rightRotate(curr);
	} else if (balance < -1){
		if (score < curr->score){
			curr->right = rightRotate(curr->right);
		}
		return leftRotate(curr);
	}
	return curr;
}

void findUser(User *root, int score){
	if (!root){
		return;
	}
	findUser(root->left, score);
	if (root->score == score){
		printf("%d. %s [%s] (%.f%)\n", i, root->username, root->job, root->rate);
		count--;
		i++;
	}
	findUser(root->right, score);
	return;
}

void display(User *curr){
	int count = 0;
	if(curr == 0){
		return;
	}
	display(curr->left);
	User* temp = curr;
	printf("Score %d\n",temp->score);
	while(temp){
		count++;
		printf("%d. %s [%s](%.f%%)\n", count, temp->username, temp->job, temp->rate);
		temp = temp->next;
	}
	printf("\n");
	display(curr->right);
}

int main(){
	
	char cmd[100];
	int input, countToInsert, countToFind, scoreToDelete;
	char username[100];
	char job[100];
	int jobChoose, score, loseCount, drawCount;
	double matchCount, winCount;
	
	User *root = insertUser(NULL, "Gregor", "Sniper", 113, 10, 9, 1, 0);
	root = insertUser(root, "Heimdall", "Druid", 300, 100, 50, 50, 0);
	root = insertUser(root, "Travy", "Warrior", 300, 200, 100, 100, 0);
	root = insertUser(root, "Tetron", "Novice", 300, 50, 25, 25, 0);
	root = insertUser(root, "Homer", "Druid", 113, 10, 8, 2, 0);
	root = insertUser(root, "Garen", "Warrior", 113, 100, 70, 30, 0);
	
	scanf("%d", &input); getchar();
	for (int loop = 0; loop < input; loop++){
		scanf("%s", cmd); getchar();
		if (strcmp("INSERT", cmd) == 0){
			scanf("%d", &countToInsert); getchar();
			for (int j = 0; j < countToInsert; j++){
				scanf("%[^#]#%d#%d#%d#%d#%d#%d", username, &jobChoose, &score, &matchCount, &winCount, &loseCount, &drawCount); getchar();
				if (jobChoose == 0){
					strcpy(job, "Novice");
				} else if (jobChoose == 1){
					strcpy(job, "Warrior");
				} else if (jobChoose == 2){
					strcpy(job, "Sniper");
				} else if (jobChoose == 3){
					strcpy(job, "Wizard");
				} else if (jobChoose == 4){
					strcpy(job, "Druid");
				} else if (jobChoose == 5){
					strcpy(job, "Assassin");
				}
			root = insertUser(root, username, job, score, matchCount, winCount, loseCount, drawCount);
			}
		} else if (strcmp("FIND", cmd) == 0){
			count = 0;
			i = 1;
			scanf("%d", &countToFind); getchar();
			findUser(root, countToFind);
			if (count == 0){
				printf("No data found for %d\n", countToFind);
			}
		} else if (strcmp("DELETE", cmd) == 0){
			scanf("%d", &scoreToDelete); getchar();
			root = deleteUser(root, scoreToDelete);
		} else if (strcmp("SHOWALL", cmd) == 0){
			display(root);
		}
	}
}
