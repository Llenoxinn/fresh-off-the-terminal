/*"I declare, upon my honor, that I did this machine problem assignment by myself
using references from the lecture notes and MPs.

Further, my solution is not a copy from the aforementioned sources."*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int coefficient;
    int exponent;
} Poln;

Poln findMeTermie(char str[]) {
    Poln x;
    x.coefficient = 1;
    x.exponent = 0;

    int has_variable = 0;
    int Position_of_X = -1;
    int Caret_saan_ka = -1;
    int strlength = 0;

    while (str[strlength] != '\0') {
        strlength++;
    }

    for (int i = 0; i < strlength; i++) {
        if (str[i] == 'x') {
            has_variable = 1;
            Position_of_X = i;
        }
        if (str[i] == '^') {
            Caret_saan_ka = i;
        }
    }

    if (has_variable == 0) {
        x.coefficient = atoi(str);
        x.exponent = 0;
    } else {
        if (Position_of_X == 0) {
            x.coefficient = 1;
        } else if (Position_of_X == 1 && str[0] == '-') {
            x.coefficient = -1;
        } else {
            char OnlyCoefficient[50] = "";
            for (int i = 0; i < Position_of_X; i++) {
                OnlyCoefficient[i] = str[i];
            }
            OnlyCoefficient[Position_of_X] = '\0';
            x.coefficient = atoi(OnlyCoefficient);
        }

        if (Caret_saan_ka != -1) {
            char OnlyExponent[50] = "";
            int idx = 0;
            for (int i = Caret_saan_ka + 1; i < strlength; i++) {
                OnlyExponent[idx] = str[i];
                idx++;
            }
            OnlyExponent[idx] = '\0';
            x.exponent = atoi(OnlyExponent);
        } else {
            x.exponent = 1;
        }
    }

    return x;
}

Poln multiply(Poln first, Poln second) {
    Poln product;
    product.coefficient = first.coefficient * second.coefficient;
    product.exponent = first.exponent + second.exponent;
    return product;
}

void display(Poln x) {
    int eff = x.coefficient;
    int exp = x.exponent;

    if(eff == 0) printf("0\n");
    else if (exp == 0) {
        printf("%d\n", eff);
    } else if (exp == 1) {
        if (eff == 1) {
            printf("x\n");
        } else if (eff == -1) {
            printf("-x\n");
        } else {
            printf("%dx\n", eff);
        }
    } else {
        if (eff == 1) {
            printf("x^%d\n", exp);
        } else if (eff == -1) {
            printf("-x^%d\n", exp);
        } else {
            printf("%dx^%d\n", eff, exp);
        }
    }
}

int main() {
    int testCases;
    scanf("%d", &testCases);
    getchar();

    for (int i = 0; i < testCases; i++) {
        char rml[100];
        fgets(rml, 100, stdin);

        int strlength = 0;
        while (rml[strlength] != '\0') {
            strlength++;
        }

        if (rml[strlength - 1] == '\n') {
            rml[strlength - 1] = '\0';
        }

        char *firstTermPtr = strtok(rml, " ");
        char *secondTermPtr = strtok(NULL, " ");

        Poln p1 = findMeTermie(firstTermPtr);
        Poln p2 = findMeTermie(secondTermPtr);

        Poln rs = multiply(p1, p2);
        display(rs);
    }

    return 0;
}
