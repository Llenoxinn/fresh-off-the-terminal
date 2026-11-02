#include "bank.h"
#include <stdio.h>

//this is where you will implement the "bank simulation"
//in this MP, we implement our very own "library"
//the declarations of the structures needed and operations/functions are found in the header file (bank.h file)
//the implementation of the operations/functions are found in the implementation file (bank.c)
//implement all the needed operations in the bank.c file
//to include user-defined header files, they are enclosed in double quotes instead of the angle brackets

int main(){
    int testcases;
    scanf("%i", &testcases);
    list l;
    initList(&l);
    for(int i = 0; i<testcases; i++) {
        int n;
        scanf("%i", &n);
    
        account acc;
        int acc_num;
        switch(n) {
            case 1:
                scanf("%s %s %s", acc.fname, acc.mname, acc.lname);
                scanf("%i", (int*)&acc.type);
                scanf("%lf", &acc.balance);
                openAccount(&l, acc);
                // acc.number=acc_num++;
                display(l);
                break;
            case 2:
                // search the account; else display no such account exists.
                scanf("%i",&acc_num);
                boolean it_went_through_1 = closeAccount(&l,acc_num);
                if(!it_went_through_1) printf("No such account exists.\n");
                display(l);
                break;
            case 3:
                // deposit
                double deposits;
                scanf("%i %lf", &acc_num, &deposits);
                boolean it_went_through_2 = deposit(&l,acc_num,deposits);
                if(!it_went_through_2) printf("No such account exists.\n");
                display(l);
                break;
            case 4:
                // withdraw
                double withdraw_mon;
                scanf("%i %lf", &acc_num, &withdraw_mon);
                int nd = search(&l, acc_num);
                if(nd==-1) printf("No such account exists.\n");
                else {
                    boolean it_went_through_3 = withdraw(&l,acc_num,withdraw_mon);
                    if(!it_went_through_3) printf("No sufficient funds.\n");
                }
                display(l);
                break;
        }
    }
    return 0;
}