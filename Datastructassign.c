#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node {
    char title[100];  
    char author[100];
    int year;         
    struct Node* next; 
} Node;
void insert(Node** head, char title[], char author[], int year);
void delete(Node** head, char title[]);
Node* find(Node* head, char title[]);
void findAndReplace(Node* head, char title[], char newTitle[], char newAuthor[], int newYear);
int count(Node* head);
void sort(Node* head);
void reverse(Node** head);
void printList(Node* head);
int main() {
    Node* head = NULL;  
    int choice, year;
    char title[100], author[100], newTitle[100], newAuthor[100];
    while(1) {
        printf("\nMenu:\n");
        printf("1. Insert Book\n");
        printf("2. Delete Book\n");
        printf("3. Find Book by Title\n");
        printf("4. Find and Replace Book\n");
        printf("5. Count Books\n");
        printf("6. Sort Books by Title\n");
        printf("7. Reverse List\n");
        printf("8. Display List\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 
        switch(choice) {
            case 1:
                printf("Enter book title: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0'; 
                printf("Enter book author: ");
                fgets(author, sizeof(author), stdin);
                author[strcspn(author, "\n")] = '\0'; 
                printf("Enter year of publication: ");
                scanf("%d", &year);
                insert(&head, title, author, year);
                break;
            case 2:
                printf("Enter book title to delete: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0'; 
                delete(&head, title);
                break;
            case 3:
                printf("Enter book title to find: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0';  
                if (find(head, title)) {
                    printf("Book with title \"%s\" found.\n", title);
                } else {
                    printf("Book not found.\n");
                }
                break;
            case 4:
                printf("Enter book title to find: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0'; 
                printf("Enter new title: ");
                fgets(newTitle, sizeof(newTitle), stdin);
                newTitle[strcspn(newTitle, "\n")] = '\0';  
                printf("Enter new author: ");
                fgets(newAuthor, sizeof(newAuthor), stdin);
                newAuthor[strcspn(newAuthor, "\n")] = '\0'; 
                printf("Enter new year: ");
                scanf("%d", &year);
                findAndReplace(head, title, newTitle, newAuthor, year);
                break;
            case 5:
                printf("Total number of books: %d\n", count(head));
                break;
            case 6:
                sort(head);
                printf("Books sorted by title.\n");
                break;
            case 7:
                reverse(&head);
                printf("List reversed.\n");
                break;
            case 8:
                printList(head);
                break;
            case 9:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
void insert(Node** head, char title[], char author[], int year) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->title, title);
    strcpy(newNode->author, author);
    newNode->year = year;
    newNode->next = NULL;
    if (*head == NULL) {
        *head = newNode;  
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;  
    }
}
void delete(Node** head, char title[]) {
    Node *temp = *head, *prev = NULL;
    if (temp != NULL && strcmp(temp->title, title) == 0) {
        *head = temp->next;
        free(temp);
        printf("Book with title \"%s\" deleted.\n", title);
        return;
    }
    while (temp != NULL && strcmp(temp->title, title) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Book with title \"%s\" not found.\n", title);
        return;
    }
    prev->next = temp->next;
    free(temp);
    printf("Book with title \"%s\" deleted.\n", title);
}
Node* find(Node* head, char title[]) {
    Node* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->title, title) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
void findAndReplace(Node* head, char title[], char newTitle[], char newAuthor[], int newYear) {
    Node* temp = find(head, title);
    if (temp != NULL) {
        strcpy(temp->title, newTitle);
        strcpy(temp->author, newAuthor);
        temp->year = newYear;
        printf("Book details updated.\n");
    } else {
        printf("Book with title \"%s\" not found.\n", title);
    }
}
int count(Node* head) {
    int count = 0;
    Node* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}
void sort(Node* head) {
    if (head == NULL) return;
    
    Node *i, *j;
    char tempTitle[100], tempAuthor[100];
    int tempYear;
    
    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (strcmp(i->title, j->title) > 0) {
                // Swap titles, authors, and years
                strcpy(tempTitle, i->title);
                strcpy(i->title, j->title);
                strcpy(j->title, tempTitle);
                
                strcpy(tempAuthor, i->author);
                strcpy(i->author, j->author);
                strcpy(j->author, tempAuthor);
                
                tempYear = i->year;
                i->year = j->year;
                j->year = tempYear;
            }
        }
    }
}
void reverse(Node** head) {
    Node *prev = NULL, *current = *head, *next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}
void printList(Node* head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }
    Node* temp = head;
    while (temp != NULL) {
        printf("Title: %s, Author: %s, Year: %d\n", temp->title, temp->author, temp->year);
        temp = temp->next;
    }
}
