#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char station[50];
    struct Node *prev, *next;
};

struct Node *head = NULL, *tail = NULL;

/* Function Declarations */
void addStationEnd();
void addStationAtPosition();
void deleteStation();
void displayForward();
void displayBackward();
void searchStation();

int main() {
    int choice;

    while (1) {
        printf("\n=== BUS ROUTE MANAGEMENT SYSTEM ===\n");
        printf("1. Add Bus Station (End)\n");
        printf("2. Add Bus Station (At Position)\n");
        printf("3. Delete Bus Station\n");
        printf("4. Display Route (Forward)\n");
        printf("5. Display Route (Backward)\n");
        printf("6. Search Station\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStationEnd(); break;
            case 2: addStationAtPosition(); break;
            case 3: deleteStation(); break;
            case 4: displayForward(); break;
            case 5: displayBackward(); break;
            case 6: searchStation(); break;
            case 7: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }
}

/* =============== INSERT AT END =============== */
void addStationEnd() {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    printf("Enter station name: ");
    scanf("%s", newNode->station);

    printf("\n{Creating new node '%s'}\n", newNode->station);

    newNode->prev = newNode->next = NULL;

    if (head == NULL) {
        printf("{List empty ? newNode becomes head and tail}\n");
        head = tail = newNode;
    } else {
        printf("{Attaching new node at end}\n");
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    printf("\nUpdated Route:\n");
    displayForward();
}


/* =============== INSERT AT SPECIFIC POSITION =============== */
void addStationAtPosition() {
    int pos, i = 1;
    printf("Enter position to insert: ");
    scanf("%d", &pos);

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    printf("Enter station name: ");
    scanf("%s", newNode->station);

    printf("\n{Creating new node '%s' for position %d}\n", newNode->station, pos);

    newNode->prev = newNode->next = NULL;

    if (pos <= 1 || head == NULL) {
        printf("{Inserting at head position}\n");

        if (head == NULL) {
            printf("{List empty ? newNode becomes head and tail}\n");
            head = tail = newNode;
        } else {
            printf("{Shifting old head forward}\n");
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    else {
        struct Node *temp = head;

        while (temp != NULL && i < pos - 1) {
            temp = temp->next;
            i++;
        }

        if (temp == tail) {
            printf("{Position is at/after tail ? inserting at end}\n");
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        } else {
            printf("{Inserting between two nodes}\n");

            newNode->next = temp->next;
            newNode->prev = temp;

            temp->next->prev = newNode;
            temp->next = newNode;
        }
    }

    printf("\nUpdated Route:\n");
    displayForward();
}


/* =============== DELETE STATION =============== */
void deleteStation() {
    if (head == NULL) {
        printf("No stations available.\n");
        return;
    }

    char name[50];
    printf("Enter station to delete: ");
    scanf("%s", name);

    struct Node *temp = head;

    printf("\n{Searching for '%s'}\n", name);

    while (temp != NULL) {
        if (strcmp(temp->station, name) == 0) {
            printf("{Station found ? '%s'}\n", name);

            if (temp == head && temp == tail) {
                printf("{Only node ? deleting}\n");
                head = tail = NULL;
            }
            else if (temp == head) {
                printf("{Deleting head ? shifting head forward}\n");
                head = head->next;
                head->prev = NULL;
            }
            else if (temp == tail) {
                printf("{Deleting tail ? shifting tail back}\n");
                tail = tail->prev;
                tail->next = NULL;
            }
            else {
                printf("{Deleting middle node}\n");
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }

            free(temp);
            printf("\nUpdated Route:\n");
            displayForward();
            return;
        }

        temp = temp->next;
    }

    printf("Station not found.\n");
}


/* =============== DISPLAY FORWARD =============== */
void displayForward() {
    struct Node *temp = head;

    if (temp == NULL) {
        printf("Route is empty.\n");
        return;
    }

    while (temp != NULL) {
        printf("%s -> ", temp->station);
        temp = temp->next;
    }
    printf("END\n");
}


/* =============== DISPLAY BACKWARD =============== */
void displayBackward() {
    struct Node *temp = tail;

    if (temp == NULL) {
        printf("Route is empty.\n");
        return;
    }

    while (temp != NULL) {
        printf("%s -> ", temp->station);
        temp = temp->prev;
    }
    printf("START\n");
}


/* =============== SEARCH =============== */
void searchStation() {
    char name[50];
    printf("Enter station to search: ");
    scanf("%s", name);

    struct Node *temp = head;
    int pos = 1;

    while (temp != NULL) {
        if (strcmp(temp->station, name) == 0) {
            printf("Station '%s' found at position %d.\n", name, pos);
            return;
        }
        temp = temp->next;
        pos++;
    }

    printf("Station not found.\n");
}
