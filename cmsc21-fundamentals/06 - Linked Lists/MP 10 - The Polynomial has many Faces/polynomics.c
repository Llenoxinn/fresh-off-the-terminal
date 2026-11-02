/*"I declare, upon my honor, that I did this machine problem assignment by myself
using references from the lecture notes and MPs.

Further, my solution is not a copy from the aforementioned sources."*/
#include<stdio.h>
#include<stdlib.h>

typedef struct Term {
    int coeff;
    int exponent;
    struct Term* next;
}Term;

typedef struct {
    Term *head;
    Term *tail;
    int size;
}Poly;


Poly *newP();
Term *newMeNewTerm(int coeff, int exponent);
void append(Poly *p, int coeff, int exponent);
void freeListFree(Poly *p);
Term *itemAt(Poly *p, int idx);
Poly *parsely(char *line);
void simplify(Poly *p);
void sortLikeABubble(Poly *p);
Poly *dropZeroes(Poly *p);
Poly *clean(Poly *p);
Poly *addMyPoly(Poly *poly1, Poly *poly2);
Poly *subMyPoly(Poly *poly1, Poly *poly2);
Poly *multMyPoly(Poly *poly1, Poly *poly2);
void printMyPoly(Poly *p);

/*
Term *newMeNewTerm(int coeff, int exponent);
Term *append(Term *head, int coeff, int exponent);
void freeListFree(Term *head);
Term *parsely(char *line);
void combinePartner(Term *head);
void sortLikeABubble(Term *head);
Term *dropZeroes(Term *head);
Term *clean(Term *head);
Term *addMyPoly(Term *poly1, Term *poly2);
Term *subMyPoly(Term *poly1, Term *poly2);
Term *multMyPoly(Term *poly1, Term *poly2);
void printMyPoly(Term *head);

*/
int main(){
    int t, operation, i;
    char line[50000];

    scanf("%i", &t);
    fgets(line, sizeof(line), stdin);

    for(i=0; i<t; i++) {
        Poly *poly1, *poly2, *result;

        fgets(line, sizeof(line), stdin);
        operation=atoi(line);

        fgets(line,sizeof(line),stdin);
        poly1=parsely(line);
        poly2=NULL;
        if(operation!=1) {
            fgets(line,sizeof(line), stdin);
            poly2=parsely(line);
        }
        result = NULL;
        switch(operation) {
            case 1:
                result=clean(poly1);
                break;
            case 2:
                result=addMyPoly(poly1,poly2);
                break;
            case 3:
                result=subMyPoly(poly1,poly2);
                break;
            case 4:
                result=multMyPoly(poly1,poly2);
                break;
        }

        printMyPoly(result);
        freeListFree(result);
        if(operation!=1&&poly1) freeListFree(poly1);
        if(poly2) freeListFree(poly2);
    }
    return 0;
}

Poly *newP() {
    Poly *p = (Poly*)malloc(sizeof(Poly));
    p->head=p->tail=NULL;
    p->size=0;
    return p;
}

Term *newMeNewTerm(int coeff, int exponent) {
    Term *new=(Term*)malloc(sizeof(Term));
    new->coeff = coeff;
    new->exponent = exponent;
    new->next = NULL;
    return new;
}

void append(Poly *p, int coeff, int exponent) {
    Term *n = newMeNewTerm(coeff, exponent);
    if(!p->head)
        p->head=p->tail=n;
    else {
        p->tail->next=n;
        p->tail=n;
    }
    p->size++;
/*
    Term *n = newMeNewTerm(coeff, exponent);
    Term *cur;
    if(!head) return n;
    cur=head;
    while(cur->next)
        cur=cur->next;
    cur->next=n;
    return head;
*/
}

void freeListFree(Poly *p) {
    Term *tmp;
    while(p->head) {
        tmp=p->head;
        p->head=p->head->next;
        free(tmp);
    }
    free(p);
}

Term *itemAt(Poly *p, int idx) {
    Term *cur=p->head;
    int i;
    for(i=0; i<idx&&cur; i++)
        cur=cur->next;
    return cur;
}

Poly *parsely(char *line) {
    Poly *p = newP();
    int i = 0;
    int sign, coeff, exp, hasCoeff;

    while(line[i] != '\n' && line[i] != '\0') {
        sign = 1;
        coeff = 0;
        exp = 0;
        hasCoeff = 0;

        if(line[i] == '+'){ 
            i++; 
        }
        else if(line[i] == '-') { sign = -1; i++; }

        while(line[i] >= '0' && line[i] <= '9') {
            coeff = coeff * 10 + (line[i] - '0');
            hasCoeff = 1;
            i++;
        }

        if(line[i] == 'x') {
            if(!hasCoeff) coeff = 1;
            exp = 1;
            i++;
            if(line[i] == '^') {
                i++;
                exp = 0;
                while(line[i] >= '0' && line[i] <= '9') {
                    exp = exp * 10 + (line[i] - '0');
                    i++;
                }
            }
        }

        coeff *= sign;
        append(p, coeff, exp);
    }
    return p;
}

void simplify (Poly *p) {
    int i, j, s=p->size;
    Term *a, *b;
    for(i=0;i<s;i++) {
        a=itemAt(p,i);
        if(a->coeff==0) continue;
        for(j=i+1; j<s;j++) {
            b=itemAt(p,j);
            if(b->exponent==a->exponent) {
                a->coeff+=b->coeff;
                b->coeff=0;
            }
        }
    }
}
/*
void combinePartner(Term *head) {
    Term *a, *b;
    for(a = head; a; a=a->next) {
        if(a->coeff==0) continue;
        for(b=a->next; b; b=b->next) {
            if(b->exponent == a->exponent) {
                a->coeff += b->coeff;
                b->coeff=0;
            }
        }
    }
}
*/

void sortLikeABubble(Poly *p) {
    Term *c;
    int swapped, tempc, tempe;
    if(!p->head) return;
    do {
        swapped=0;
        for(c=p->head; c->next; c=c->next) {
            if(c->exponent < c->next->exponent) {
                tempc=c->coeff;
                tempe=c->exponent;
                c->coeff=c->next->coeff;
                c->exponent=c->next->exponent;
                c->next->coeff=tempc;
                c->next->exponent=tempe;
                swapped=1;
            }
        }
    }while(swapped);
}

Poly *dropZeroes(Poly *p) {
    Term *curr, *tmp;
    while(p->head && p->head->coeff==0) {
        tmp=p->head;
        p->head=p->head->next;
        free(tmp);
        p->size--;
    }
    if(!p->head) return NULL;
    curr = p->head;
    while(curr->next) {
        if(curr->next->coeff==0) {
            tmp = curr->next;
            curr->next=tmp->next;
            free(tmp);
        } else {
            curr = curr->next;
        }
    }
    return p;
}

Poly *clean(Poly *p) {
    sortLikeABubble(p);
    simplify(p);
    return dropZeroes(p);
}

Poly *combineLikePoly(Poly *poly1, Poly *poly2, int operation) {
    Poly *result = newP();
    Term *c;
    for(c = poly1->head; c; c=c->next)
        append(result, c->coeff, c->exponent);
    for(c = poly2->head; c; c=c->next)
        append(result, operation*c->coeff, c->exponent);
    return clean(result);
}
/*
add and sub funcs are just similar
Term *addMyPoly(Term *poly1, Term *poly2) {
    Term *result = NULL;
    Term *c;
    for(c = poly1; c; c=c->next)
        result = append(result, c->coeff, c->exponent);
    for(c = poly2; c; c=c->next)
        result = append(result, c->coeff, c->exponent);
    return clean(result);
}
*/

Poly *addMyPoly(Poly *poly1, Poly *poly2) {
    return combineLikePoly(poly1,poly2,+1);
}

Poly *subMyPoly(Poly *poly1, Poly *poly2) {
    return combineLikePoly(poly1,poly2,-1);
}
/*
Term *subMyPoly(Term *poly1, Term *poly2) {
    Term *result = NULL;
    Term *c;
    for(c = poly1; c; c=c->next)
        result = append(result, c->coeff, c->exponent);
    for(c = poly2; c; c=c->next)
        result = append(result, -c->coeff, c->exponent);
    return clean(result);
}
*/
Poly *multMyPoly(Poly *poly1, Poly *poly2) {
    Poly *result = newP();
    Term *g, *h;
    for(g = poly1->head; g; g=g->next)
        for(h = poly2->head; h; h=h->next)
            append(result, g->coeff * h->coeff, g->exponent + h->exponent);
    return clean(result);
}

void printMyPoly(Poly *p) {
    int c, e, first;
    Term *head=p->head;
    if(!p->head) {
        printf("0\n");
        return;
    }
    first = 1;
    while(head) {
        c = head->coeff;
        e = head->exponent;

        if(first) {
            if(c<0) { 
                printf("-"); c=-c;
            }
            first=0;
        } else {
            if(c<0) { 
                printf("-"); 
                c=-c; 
            }
            else { 
                printf("+"); 
            }
        }

        if(e==0) 
            printf("%i", c);
        else if(e==1&&c==1) 
            printf("x");
        else if(e==1) 
            printf("%ix", c);
        else if(c==1) 
            printf("x^%i", e);
        else 
            printf("%ix^%i", c, e);

        head=head->next;
    }
    printf("\n");
}