/*

HONOR CODE:

I declare, upon my honor, that I did this machine problem assignment by myself
using references from the lecture notes and MPs.

*/


#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int *array;
    int size;
    int capacity;
}Vector;

void initin(Vector *v) {
    v->capacity = 5;
    v->size = 0;
    v->array = (int*)malloc(v->capacity*sizeof(int));
}

int at(Vector*, int);
int set(Vector*, int, int);
int insert(Vector*, int, int);
void push_back(Vector*, int);
void push_front(Vector*, int);
void display(Vector*);
int removeItem(Vector*, int);
int isSorted(Vector*);
int deleteDuplicates(Vector*);

int main() {
    int t, i, n, j, c;
    Vector vec;
    initin(&vec);
    scanf("%i", &t);
    for(i=0; i<t; i++) {
        scanf("%i", &n);
        vec.size=n;

        if(n > vec.capacity) {
            while(vec.capacity < n) vec.capacity += 5;
            vec.array = realloc(vec.array, vec.capacity * sizeof(int));
        }
        for (j=0; j<n; j++) {
            scanf("%i", &vec.array[j]);
        }
        
        scanf("%i", &c);
        switch(c) {
            case 1: {
                int x;
                scanf("%i", &x);
                push_back(&vec, x);
                display(&vec);
                break;
            }
            case 2: {
                int x;
                scanf("%i", &x);
                push_front(&vec, x);
                display(&vec);
                break;
            }
            case 3: {
                int x, p;
                scanf("%i %i", &x, &p);
                if(!insert(&vec, x, p))
                    printf("OPERATION FAILED\n");
                else
                    display(&vec);
                break;
            }
            case 4: {
                int p, removed;
                scanf("%i", &p);
                removed = removeItem(&vec, p);
                if(removed == -1)
                    printf("OPERATION FAILED\n");
                else {
                    printf("%i\n", removed);
                    display(&vec);
                }
                break;
            }
            case 5: {
                int p, val;
                scanf("%i", &p);
                val = at(&vec, p);
                if(val == -1)
                    printf("OPERATION FAILED\n");
                else {
                    printf("%i\n", val);
                    display(&vec);
                }
                break;
            }
            case 6: {
                int x, p, old;
                scanf("%i %i", &x, &p);
                old = set(&vec, x, p);
                if(old == -1)
                    printf("OPERATION FAILED\n");
                else {
                    printf("%i\n", old);
                    display(&vec);
                }
                break;
            }
            case 7: {
                if(isSorted(&vec))
                    printf("SORTED\n");
                else
                    printf("NOT SORTED\n");
                break;
            }
            case 8: {
                deleteDuplicates(&vec);
                display(&vec);
                break;
            }
        }
        
    }
}

int at(Vector *v, int p) {
    if (p<0 || p>=v->size) return -1;
    return v->array[p];
}

int set(Vector *v, int x, int p) {
    int old;
    if (p<0 || p>v->size) return -1;
    old = v->array[p];
    v->array[p] = x;
    return old;
}
int insert(Vector *v, int x, int p) {
    int i;
    if (p<0 || p>v->size+1) return 0;
    if(v->size == v->capacity) {
        v->capacity += 5;
        v->array = realloc(v->array, v->capacity * sizeof(int));
    }
    for(i= v->size; i>p; i--) {
        v->array[i] = v->array[i-1];
    }
    v->array[p]=x;
    v->size++;
    return 1;
}
void push_back(Vector *v, int x) {
    insert(v, x, v->size); 
}
void push_front(Vector *v, int x) {
    insert(v, x, 0);
}
void display(Vector *v) {
    int i;
    for(i= 0; i<v->size; i++) {
        printf("%i ", v->array[i]);
    }
    printf("\n");
}
int removeItem(Vector *v, int p) {
    int removed, i;
    if (p<0 || p>=v->size+1) return -1;
    removed = v->array[p];
    for(i = p; i<v->size-1; i++) {
        v->array[i] = v->array[i+1];
    }
    v->size--;
    return removed;
}
int isSorted(Vector *v) {
    int i;
    for(i = 0; i<v->size-1; i++) {
        if(v->array[i] > v->array[i+1]) return 0;
    }
    return 1;
}
int deleteDuplicates(Vector *v) {
    int i, j;
    for(i = 0; i<v->size;i++) {
        for(j = i+1; j<v->size;j++) {
            if(v->array[i] == v->array[j]) {
                removeItem(v, j);
                j--;
            }
        }
    }
}