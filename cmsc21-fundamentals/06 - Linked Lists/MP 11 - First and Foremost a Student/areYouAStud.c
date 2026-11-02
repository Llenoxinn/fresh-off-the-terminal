/*

HONOR CODE:

I declare, upon my honor, that I did this machine problem assignment by myself
using references from the lecture notes and MPs.

^^^^ <<<<<< ???>>>>>>> 0v0 !!
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    int yearLevel;
    char studentNumber[15];
    char firstName[50], middleName[50], lastName[50], program[100];
}Student;

typedef struct Node {
    Student data;
    struct Node* next;
}Node;

typedef struct {
    int size;
    Node *head;
    Node *tail;
}list;

void initList(list *li);
Node *createMyNode(Student *si);
void enrollStudent(list *li, Student *s);
void insertAtPosition(list *li, Student *s, int pos);
void removeStudent(list *li, char *sNumber);
void getInfo(list *li, char *sNumber);
void editInfo(list *li, char *sNumber, int choose);
void displayByProgram(list *li, char *program);
void displayByYearLevel(list *li, int yearLevel);
void displayAll(list *li);
void readStudent(Student *s);
void printStudent(Student *s);

int main() {
    list li;
    initList(&li);
    
    int t;
    scanf("%i", &t);
    
    for(int i = 0; i<t; i++) {
        Student s;
        readStudent(&s);
        enrollStudent(&li,&s);
    }
    
    int operation;
    scanf("%i", &operation);
    
    while(operation--) {
        int opr;
        scanf("%i", &opr);
        switch(opr) {
            case 1: {
                Student s;
                int pos;
                readStudent(&s);
                scanf(" %i", &pos);
                insertAtPosition(&li,&s,pos);
                displayAll(&li);
                break;
            }
            case 2: {
                char sNumber[15];
                scanf(" %[^\n]", sNumber);
                removeStudent(&li, sNumber);
                displayAll(&li);
                break;
            }
            case 3: {
                char sNumber[15];
                scanf(" %[^\n]", sNumber);
                getInfo(&li, sNumber);
                displayAll(&li);
                break;
            }
            case 4: {
                char sNumber[15];
                int choose;
                scanf("%s %d\n", sNumber, &choose);
                editInfo(&li, sNumber, choose);
                displayAll(&li);
                break;
            }
            case 5: {
                char program[100];
                scanf(" %[^\n]", program);
                displayByProgram(&li, program);
                break;
            }
            case 6: {
                int yearLevel;
                scanf(" %i\n", &yearLevel);
                displayByYearLevel(&li, yearLevel);
                break;
            }
        }
    }
    return 0;
}

void initList(list *li) {
    li->size=0;
    li->head=li->tail=NULL;
}

Node *createMyNode(Student *si) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data=*si;
    newNode->next=NULL;
    return newNode;
}
void insertAtPosition(list *li, Student *s, int pos) {
    if(pos<0 || pos>li->size) return;
    Node *newNode=createMyNode(s);
    if(pos==0) {
        newNode->next=li->head;
        li->head=newNode;
        if(li->size==0) {
            li->tail = newNode;
        }
    } else if(pos==li->size) {
        li->tail->next=newNode;
        li->tail=newNode;
    }
    else {
        Node *current=li->head;
        for(int i=0; i<pos-1;i++) {
            current=current->next;
        }
        newNode->next=current->next;
        current->next=newNode;
    }
    li->size++;

}
void enrollStudent(list *li, Student *s) {
    Node *newNode=createMyNode(s);
    if(li->head==NULL) {
        li->head=newNode;
        /*li->tail=newNode;*/
    } else {
        li->tail->next = newNode;
        /*li->tail = newNode;*/
    }
    li->tail=newNode;
    li->size++;
}
void removeStudent(list *li, char *sNumber) {
    Node *current = li->head;
    Node *prev=NULL;
    
    while(current!=NULL) {
        
        if(strcmp(current->data.studentNumber, sNumber)==0) {
            if(prev==NULL) {
                li->head=current->next;
                if(li->head == NULL) {
                    li->tail=NULL;
                }
            } else {
                prev->next=current->next;
                if(current->next == NULL) {
                    li->tail=prev;
                }
            }
            free(current);
            li->size--;
            return;
        }
        prev=current;
        current=current->next;
    }
    printf("Student not enrolled.\n"); 
}
void getInfo(list *li, char *sNumber) {
    Node *current=li->head;
    while(current!=NULL) {
        if(strcmp(current->data.studentNumber, sNumber)==0) {
            printStudent(&current->data);
            return;
        }
        current=current->next;
    }
    printf("Student not enrolled.\n");
}
void editInfo(list *li, char *sNumber, int choose) {
    Node *current = li->head;
    while(current !=NULL) {
        if(strcmp(current->data.studentNumber, sNumber)==0) {
            if(choose==1) {
                scanf(" %[^\n] ", current->data.program);
            } else if (choose==2) {
                scanf(" %i", &current->data.yearLevel);
            }
            return;
        }
        current=current->next;
    }
    printf("Student not enrolled.\n");
}

void printStudent(Student *s) {
    printf("Student Number: %s\n", s->studentNumber);
    printf("Name: %s %s %s\n", s->firstName, s->middleName, s->lastName);
    printf("Program: %s\n", s->program);
    printf("Year Level: %i\n", s->yearLevel);
}

void displayByProgram(list *li, char *program) {
    Node *current = li->head;
    int found=0;
    while(current!=NULL) {
        if(strcmp(current->data.program, program) == 0) {
            printStudent(&current->data);
            found=1;
        }
        current=current->next;
    }
    if(!found) printf("No students enrolled in %s.\n", program);
    printf("------------------------------------\n");
}

void displayByYearLevel(list *li, int yearLevel) {
    Node *current = li->head;
    int found=0;
    while(current!=NULL) {
        if(current->data.yearLevel == yearLevel) {
            printStudent(&current->data);
            found=1;
        }
        current=current->next;
    }
    if(!found) printf("No students with year level %i.\n", yearLevel);
    printf("------------------------------------\n");
}

void displayAll(list *li) {
    Node *current = li->head;
    while(current!=NULL) {
        printStudent(&current->data);
        current=current->next;
    }
    printf("------------------------------------\n");
}

void readStudent(Student *s) {
    scanf("%s", s->studentNumber);
    scanf("%s %s %s\n", s->firstName, s->middleName, s->lastName);
    scanf(" %[^\n]", s->program);
    scanf(" %i", &s->yearLevel);
}