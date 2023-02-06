#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const char FILE_NAME[] = "contacts.txt";

struct Contact {
    char surname[100];
    char name[100];
    int age;
    char phoneNumber[20];
    char gender;
    struct Contact* next;
    struct Contact* prev;
};

struct List {
    struct Contact* head;
    struct Contact* tail;
};
void addContact(struct List* list, char surname[], char name[], int age, char phoneNumber[], char gender) {
    struct Contact* newContact = (struct Contact*)malloc(sizeof(struct Contact));
    strcpy(newContact->surname, surname);
    strcpy(newContact->name, name);
    newContact->age = age;
    strcpy(newContact->phoneNumber, phoneNumber);
    newContact->gender = gender;
    newContact->next = NULL;
    newContact->prev = list->tail;
    if (list->tail) {
        list->tail->next = newContact;
    }
    if (!list->head) {
        list->head = newContact;
    }
    list->tail = newContact;
}
void deleteContact(struct List* list, char surname[]) {
    struct Contact* contact = list->head;
    while (contact) {
        if (strcmp(contact->surname, surname) == 0) {
            if (contact->prev) {
                contact->prev->next = contact->next;
            }
            if (contact->next) {
                contact->next->prev = contact->prev;
            }
            if (contact == list->head) {
                list->head = contact->next;
            }
            if (contact == list->tail) {
                list->tail = contact->prev;
            }
            free(contact);
            return;
        }
        contact = contact->next;
    }
}
void getContacts(struct List* list) {
    struct Contact* contacts = list->head;
    printf("\n+------------------------------------------------------------------------------------+");
    printf("\n| Surname               | Name                  | Age | Phone Number        | Gender |");
    printf("\n+------------------------------------------------------------------------------------+");
    while (contacts) {
        printf("\n| %-22s| %-22s| %-4d| %-20s| %-7c|", contacts->surname, contacts->name, contacts->age, contacts->phoneNumber, contacts->gender);
        contacts = contacts->next;
    }
    printf("\n+------------------------------------------------------------------------------------+");
}

void saveFile(struct List* list) {
    FILE* pFile = fopen(FILE_NAME, "w");
    if (!pFile) {
        printf("Error when opening a file\n");
        return;
    }
    struct Contact* contact = list->head;
    while (contact) {
        fprintf(pFile, "%s\n", contact->surname);
        fprintf(pFile, "%s\n", contact->name);
        fprintf(pFile, "%d\n", contact->age);
        fprintf(pFile, "%20s\n", contact->phoneNumber);
        fprintf(pFile, "%c\n", contact->gender);
        contact = contact->next;
    }
    fclose(pFile);
}
void getFromFile(struct List* list) {
    FILE* pFile = fopen(FILE_NAME, "r");
    if (!pFile) {
        printf("Error when opening a file\n");
        return;
    }
    char surname[100];
    char name[100];
    int age;
    char phoneNumber[20];
    char gender;

    while (fscanf(pFile, "%s\n%s\n%d\n%s\n%c\n", surname, name, &age, phoneNumber, &gender) == 5) {
        addContact(list, surname, name, age, phoneNumber, gender);
    }
    fclose(pFile);
}

void updateContact(struct Contact** list, char* surname) {
    struct Contact* tmp = *list;
    while (tmp != NULL) {
        if (strcmp(tmp->surname, surname) == 0) {
            printf("New contact surname: ");
            scanf("%s", tmp->surname);
            printf("New contact name: ");
            scanf("%s", tmp->name);
            printf("Age: ");
            scanf("%d", &tmp->age);
            printf("New contact phone number: ");
            scanf("%s", tmp->phoneNumber);
            printf("New gender (M/K): ");
            scanf(" %c", &tmp->gender);
            break;
        }
        tmp = tmp->next;
    }
    if (tmp == NULL) {
        printf("Contact does not exist \n");
    }
}

int main() {
    struct List list;
    list.head = NULL;
    list.tail = NULL;

    char surname[100];
    char name[100];
    int age;
    char phoneNumber[20];
    char gender;

    char option;
    getFromFile(&list);

    while (1) {
        system("clear");
        printf("\nC. Add contact\n");
        printf("D. Delete contact\n");
        printf("R. Read contacts\n");
        printf("U. Update contact\n");
        printf("E. Exit\n");
        printf("Choice option: ");
        option = getchar();
        if (option == 10) {
            continue;
        }
        else {
            switch (option) {
            case 99:
                system("clear");
                printf("Nazwisko: ");
                scanf("%s", surname);
                printf("Imię: ");
                scanf("%s", name);
                printf("Wiek: ");
                scanf("%d", &age);
                printf("Numer komórkowy: ");
                scanf("%s", phoneNumber);
                printf("Płeć (M/K): ");
                scanf(" %c", &gender);
                addContact(&list, surname, name, age, phoneNumber, gender);
                saveFile(&list);
                break;
            case 100:
                system("clear");
                getContacts(&list);
                printf("\nSurname: ");
                scanf("%s", surname);
                deleteContact(&list, surname);
                saveFile(&list);
                break;
            case 114:
                system("clear");
                getContacts(&list);
                printf("\nPress any key to return to the main menu");
                getchar();
                getchar();
                break;
            case 117:
                system("clear");
                getContacts(&list);
                printf("\nSurname: ");
                scanf("%s", surname);
                updateContact(&list, surname);
                saveFile(&list);
                break;
            case 101:
                return 0;
            default:
                printf("Error\n");
                break;
            }
        }
    }
    return 0;
}