#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count = 1;
int found = 0;
int chain = 0;

struct Player
{
    char username[100];
    int score;
    char job[100];
    double match;
    double win;
    int lose;
    int draw;
    double winrate;

    int height;
    Player *left, *right, *next;
} *root = NULL;

int getMax(int a, int b)
{
    return (a >= b) ? a : b;
}

int calculateHeight(Player *curr)
{
    return (!curr) ? 0 : 1 + getMax(calculateHeight(curr->left), calculateHeight(curr->right));
}

int getBalance(Player *curr)
{
    return (!curr) ? 0 : (calculateHeight(curr->left) - calculateHeight(curr->right));
}


Player *rightRotate(Player *curr)
{
    Player *newParent = curr->left;
    curr->left = newParent->right;
    newParent->right = curr;

    curr->height = calculateHeight(curr);
    newParent->height = calculateHeight(newParent);

    return newParent;
}

Player *leftRotate(Player *curr)
{
    Player *newParent = curr->right;
    curr->right = newParent->left;
    newParent->left = curr;

    curr->height = calculateHeight(curr);
    newParent->height = calculateHeight(newParent);

    return newParent;
}

Player *createPlayer(const char username[], const char job[], int score, double match, double win, int lose, int draw)
{
    Player *newPlayer = (Player *)malloc(sizeof(Player));
    strcpy(newPlayer->username, username);
    newPlayer->score = score;
    strcpy(newPlayer->job, job);
    newPlayer->match = match;
    newPlayer->win = win;
    newPlayer->lose = lose;
    newPlayer->draw = draw;
    newPlayer->winrate = (win / match) * 100;
    newPlayer->left = newPlayer->right = newPlayer->next = NULL;
    newPlayer->height = 1;

    return newPlayer;
}

Player *collision(Player *curr, Player *newPlayer)
{
    Player *temp = curr;
    if (newPlayer->winrate > curr->winrate)
    {
        newPlayer->left = curr->left;
        newPlayer->right = curr->right;
        newPlayer->next = temp;
        curr = newPlayer;
        return curr;
    }

    while (temp->next != NULL && newPlayer->winrate <= temp->next->winrate)
    {
        if (temp->next == NULL)
        {
            break;
        }
        temp = temp->next;
    }
    newPlayer->next = temp->next;
    temp->next = newPlayer;
    return curr;
}

Player *insertPlayer(Player *curr, Player *newPlayer)
{
    if (curr == NULL)
    {
        return newPlayer;
    }
    else if (newPlayer->score < curr->score)
    {
        curr->left = insertPlayer(curr->left, newPlayer);
    }
    else if (newPlayer->score > curr->score)
    {
        curr->right = insertPlayer(curr->right, newPlayer);
    }
    else
    {
        curr = collision(curr, newPlayer);
    }

    curr->height = calculateHeight(curr);
    int balance = getBalance(curr);

    if (balance > 1)
    {
        if (getBalance(curr->left) < 0)
        {
            curr->left = leftRotate(curr->left);
        }

        return rightRotate(curr);
    }
    else if (balance < -1)
    {
        if (getBalance(curr->right) > 0)
        {
            curr->right = rightRotate(curr->right);
        }

        return leftRotate(curr);
    }

    return curr;
}

Player *deletePlayer(Player *curr, int score)
{
    if (curr == NULL)
    {
        return curr;
    }
    else if (score < curr->score)
    {
        curr->left = deletePlayer(curr->left, score);
    }
    else if (score > curr->score)
    {
        curr->right = deletePlayer(curr->right, score);
    }
    else
    {
        if (curr->next != NULL)
        {
            if (chain == 1)
            {
                curr->next = NULL;
                free(curr);
                curr = NULL;
            }
            else
            {
                Player *del = curr;
                curr = curr->next;
                curr->left = del->left;
                curr->right = del->right;
                free(del);
            }
        }
        else
        {
            if (curr->left == NULL && curr->right == NULL)
            {
                free(curr);
                curr = NULL;
            }
            else if (curr->left == NULL)
            {
                Player *del = curr;
                curr = curr->right;
                free(del);
                del = NULL;
            }
            else if (curr->right == NULL)
            {
                Player *del = curr;
                curr = curr->left;
                free(del);
                del = NULL;
            }
            else
            {
                chain = 1;
                Player *temp = curr->right;
                while (temp->left != NULL)
                {
                    temp = temp->left;
                }

                strcpy(curr->username, temp->username);
                curr->score = temp->score;
                strcpy(curr->job, temp->job);
                curr->match = temp->match;
                curr->win = temp->win;
                curr->lose = temp->lose;
                curr->draw = temp->draw;
                curr->winrate = temp->winrate;
                curr->next = temp->next;

                curr->right = deletePlayer(curr->right, temp->score);
            }
        }
    }

    if (curr == NULL)
    {
        return curr;
    }

    curr->height = calculateHeight(curr);
    int balance = getBalance(curr);

    if (balance > 1)
    {
        if (getBalance(curr->left) < 0)
        {
            curr->left = leftRotate(curr->left);
        }

        return rightRotate(curr);
    }
    else if (balance < -1)
    {
        if (getBalance(curr->right) > 0)
        {
            curr->right = rightRotate(curr->right);
        }

        return leftRotate(curr);
    }

    return curr;
}

void inOrderTree(Player *curr)
{
    if (curr == NULL)
    {
        return;
    }
    inOrderTree(curr->left);
    Player *temp = curr;
    printf("score %d\n", curr->score);
    count = 1;
    while (temp != NULL)
    {
        printf("%d. %s [%s] (%.0f%%)\n", count++, temp->username, temp->job, temp->winrate);
        temp = temp->next;
    }
    printf("\n");
    inOrderTree(curr->right);
}

void findPlayer(Player *curr, int score)
{
    if (curr == NULL)
    {
        return;
    }
    findPlayer(curr->left, score);
    if (curr->score == score)
    {
        found = 1;
        Player *temp = curr;
        printf("Score %d\n", curr->score);
        count = 1;
        while (temp != NULL)
        {
            printf("%d. %s [%s] (%.0f%)\n", count++, temp->username, temp->job, temp->winrate);
            temp = temp->next;
        }
    }
    printf("\n");
    findPlayer(curr->right, score);
}

int main()
{
    root = insertPlayer(root, createPlayer("Gregor", "Sniper", 113, 10, 9, 1, 0));
    root = insertPlayer(root, createPlayer("Heimdall", "Druid", 300, 100, 50, 50, 0));
    root = insertPlayer(root, createPlayer("Travy", "Warrior", 300, 200, 100, 100, 0));
    root = insertPlayer(root, createPlayer("Tetron", "Novice", 300, 50, 25, 25, 0));
    root = insertPlayer(root, createPlayer("Homer", "Druid", 113, 10, 8, 2, 0));
    root = insertPlayer(root, createPlayer("Garen", "Warrior", 113, 100, 70, 30, 0));

    int cmd_count = 0;
    char cmd[30] = {};
    int insert_count = 0;
    char username[100];
    int jobType;
    char job[20];
    int score;
    int match;
    int win;
    int lose;
    int draw;

    scanf("%d", &cmd_count);
    getchar();

    for (int i = 0; i < cmd_count; i++)
    {
        scanf("%s", cmd);
        getchar();

        if (strcmpi(cmd, "INSERT") == 0)
        {
            scanf("%d", &insert_count);
            getchar();

            for (int j = 0; j < insert_count; j++)
            {
                scanf("%[^#]#%d#%d#%d#%d#%d#%d", username, &jobType, &score, &match, &win, &lose, &draw);
                if (jobType == 0)
                {
                    strcpy(job, "Novice");
                }
                else if (jobType == 1)
                {
                    strcpy(job, "Warrior");
                }
                else if (jobType == 2)
                {
                    strcpy(job, "Sniper");
                }
                else if (jobType == 3)
                {
                    strcpy(job, "Wizard");
                }
                else if (jobType == 4)
                {
                    strcpy(job, "Druid");
                }
                else if (jobType == 5)
                {
                    strcpy(job, "Assassin");
                }
                getchar();

                root = insertPlayer(root, createPlayer(username, job, score, match, win, lose, draw));
            }
        }
        else if (strcmpi(cmd, "FIND") == 0)
        {
            found = 0;
            int findScore = 0;
            scanf("%d", &findScore);
            getchar();

            findPlayer(root, findScore);
            if (found == 0)
            {
                printf("Score %d\n", findScore);
                printf("No data found for %d\n", findScore);
            }
        }
        else if (strcmpi(cmd, "DELETE") == 0)
        {
            chain = 0;
            int delScore = 0;
            scanf("%d", &delScore);
            getchar();

            root = deletePlayer(root, delScore);
        }
        else if (strcmpi(cmd, "SHOWALL") == 0)
        {
            inOrderTree(root);
            printf("\n");
    	}
	}
}
