typedef enum{
    TRUE = 1,
    FALSE = 0
}boolean;

typedef enum{
    SAVINGS_ACCOUNT,
    CHECKING_ACCOUNT
}accountType;

typedef struct{
    int number;
    accountType type;
    char fname[30],mname[30],lname[30],PIN[7];
    double balance;
    
}account;

typedef struct{
    account accounts[100];
    int size;
}list;

void display(list);
void initList(list*);
boolean openAccount(list*,account);
boolean closeAccount(list*,int);
int search(list*,int);
boolean deposit(list*,int,double);
boolean withdraw(list*,int,double);