#include <stdio.h>
// forgot to add stdio huhu
#include "bank.h"
#include <string.h>

void initList(list* l){
    l->size = 0;
}

boolean openAccount(list* l,account acc){
    if(l->size>=100) return FALSE;
    // INSTEAD OF SIZE+1 WHENEVER IN ACCNUMBER, I WILL TRY TO ADD LIKE A VARIABLE TO STORE THE HIGHEST??
    // instead of putting it sa main, i prefer here nalang
    int generate_last=0;
    for(int i = 0; i<l->size;i++){
        if(l->accounts[i].number > generate_last)
            generate_last = l->accounts[i].number;
    }
    acc.number = generate_last + 1;
    l->accounts[l->size] = acc;
    l->size++;
    return TRUE; // should be the base return eme eme
}

boolean closeAccount(list* l,int num){
    // search the accccc firsttt
    int nd = search(l,num);
    if(nd==-1) return FALSE;
    for(int i=nd; i<l->size-1;i++) {
        l->accounts[i] = l->accounts[i+1];
        // l->accounts[i].number=i+1;
    }
    l->size--;
    return TRUE; // successful
}

int search(list* l,int num){
    for(int i=0;i<l->size;i++) {
        if(l->accounts[i].number == num) {
            return i;
        }
    }
    return -1; // changed to -1 because i feel like 0 is still valid??
    //return 0; // could also be -1. i dont know the difference sa both.// not found;
}

boolean deposit(list* l,int num, double d_amt){
    // search the account first
    // you add money = deposit
    int nd = search(l, num);
    if(nd==-1) return FALSE; // NO ACCOUNT!
    // DEPOSIT NEOOWW!
    l->accounts[nd].balance += d_amt;
    return TRUE;
}

boolean withdraw(list*l,int num,double w_amt){
    // search the account first
    // you get some cash if SUFFICIENT
    // i SHOULD check if naa bay saktong kwarta hahhaah
    int nd = search(l,num);
    if(nd==-1) return FALSE; // account did not even exist atp
    // check if you have ENOUGH!!
    if(l->accounts[nd].balance < w_amt) return FALSE;
    l->accounts[nd].balance -= w_amt;
    return TRUE;
}

void display(list l){
    for(int i=0; i<l.size; i++) {
        printf("Account Number: %i\n",l.accounts[i].number);
        printf("Name: %s %s %s\n", l.accounts[i].fname, l.accounts[i].mname, l.accounts[i].lname);
        printf("Account Type: %s\n", l.accounts[i].type == SAVINGS_ACCOUNT ? "Savings Account" : "Checking Account");
        printf("Balance: %.2lf\n", l.accounts[i].balance);
    }
    printf("------------------------------------\n");
}