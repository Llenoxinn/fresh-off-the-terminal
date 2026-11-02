/*
I declare, upon my honor, that I did this machine problem assignment by myself
using references from the lecture notes and MPs.
*/

#include <stdio.h>

/* Function Prototypes */
int logBase10(int n);
int iAmOnTheFloor(double n);
int ceilingan(double n);

int isItANumber(char n);
int isItYouSmallAlpha(char n);
int isItYouLargeAlpha(char n);

char makeItUpper(char c);
char makeItLower(char c);

int isitPunctuation(char c);

int stringtoInt(char n[]);
double stringtoDouble(char n[]);
int aFloat(char n[]);

int mayAbs(int n);

void copyMyString(char sour[], char destined[]);
int subStrings(char s1[], char s2[]);
int divaComparisonStrings(char st1[], char st2[]);

void camelCase(char c[]);
void reverseThisString(char c[]);
int reverseThisDigit(int n);

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int item;
        scanf("%d", &item);

        switch (item) {

            case 1: {
                int n;
                scanf("%d", &n);
                printf("%d\n", logBase10(n));
                break;
            }

            case 2: {
                double n;
                scanf("%lf", &n);
                printf("%d\n", iAmOnTheFloor(n));
                break;
            }

            case 3: {
                double n;
                scanf("%lf", &n);
                printf("%d\n", ceilingan(n));
                break;
            }

            case 4: {
                char n;
                scanf(" %c", &n);
                if (isItANumber(n) || isItYouSmallAlpha(n) || isItYouLargeAlpha(n))
                    printf("YES\n");
                else
                    printf("NO\n");
                break;
            }

            case 5: {
                char n;
                scanf(" %c", &n);
                if (isItYouSmallAlpha(n) || isItYouLargeAlpha(n))
                    printf("YES\n");
                else
                    printf("NO\n");
                break;
            }

            case 6: {
                char n;
                scanf(" %c", &n);
                if (isItYouLargeAlpha(n))
                    printf("YES\n");
                else
                    printf("NO\n");
                break;
            }

            case 7: {
                char n;
                scanf(" %c", &n);
                if (isItYouSmallAlpha(n))
                    printf("YES\n");
                else
                    printf("NO\n");
                break;
            }

            case 8: {
                char n;
                scanf(" %c", &n);
                printf("%c\n", makeItUpper(n));
                break;
            }

            case 9: {
                char n;
                scanf(" %c", &n);
                printf("%c\n", makeItLower(n));
                break;
            }

            case 10: {
                char n;
                scanf(" %c", &n);
                if (isitPunctuation(n))
                    printf("YES\n");
                else
                    printf("NO\n");
                break;
            }

            case 11: {
                char n[51];
                scanf("%s", n);
                printf("%d\n", stringtoInt(n));
                break;
            }

            case 12: {
                char n[51];
                scanf("%s", n);
                printf("%.4lf\n", stringtoDouble(n));
                break;
            }

            case 13: {
                char n[51];
                scanf("%s", n);
                if (aFloat(n))
                    printf("YES\n");
                else
                    printf("NO\n");
                break;
            }

            case 14: {
                int n;
                scanf("%d", &n);
                printf("%d\n", mayAbs(n));
                break;
            }

            case 15: {
                char sour[51], destined[51];
                scanf("%s %s", sour, destined);
                copyMyString(sour, destined);
                printf("%s\n", destined);
                break;
            }

            case 16: {
                char s1[51], s2[51];
                scanf("%s %s", s1, s2);
                if (subStrings(s1, s2))
                    printf("YES\n");
                else
                    printf("NO\n");
                break;
            }

            case 17: {
                char st1[51], st2[51];
                scanf("%s %s", st1, st2);
                int res = divaComparisonStrings(st1, st2);
                if (res == 0)
                    printf("YES\n");
                else if (res < 0)
                    printf("BEFORE\n");
                else
                    printf("AFTER\n");
                break;
            }

            case 18: {
                char c[51];
                scanf("%s", c);
                camelCase(c);
                printf("%s\n", c);
                break;
            }

            case 19: {
                char c[51];
                scanf("%s", c);
                reverseThisString(c);
                printf("%s\n", c);
                break;
            }

            case 20: {
                int n;
                scanf("%d", &n);
                printf("%d\n", reverseThisDigit(n));
                break;
            }
        }
    }
    return 0;
}

/*
        FUNCTIONS TIME! ??????>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/

int logBase10(int n) {
    int heybabycountme = 0;
    while (n >= 10) {
        n /= 10;
        heybabycountme++;
    }
    return heybabycountme;
}

int iAmOnTheFloor(double n) {
    int x = (int)n;
    if (n < 0 && n != x)
        return x - 1;
    return x;
}

int ceilingan(double n) {
    int x = (int)n;
    if (n > 0 && n != x)
        return x + 1;
    return x;
}

int isItANumber(char n) {
    return (n >= '0' && n <= '9');
}

int isItYouSmallAlpha(char n) {
    return (n >= 'a' && n <= 'z');
}

int isItYouLargeAlpha(char n) {
    return (n >= 'A' && n <= 'Z');
}

char makeItUpper(char c) {
    if (c >= 'a' && c <= 'z')
        return c - 32;
    return c;
}

char makeItLower(char c) {
    if (c >= 'A' && c <= 'Z')
        return c + 32;
    return c;
}

int isitPunctuation(char c) {
    return (c == '.' || c == '?' || c == '!' ||
            c == ',' || c == ';' || c == ':');
}

int stringtoInt(char n[]) {
    int result = 0;
    int i = 0;
    int sign = 1;
    if(n[0] == '-') {
        sign = -1;
        i = 1;
    }
    for (; n[i] != '\0'; i++)
        result = result * 10 + (n[i] - '0');
    return result * sign;
}

double stringtoDouble(char n[]) {
    double result = 0, decimal = 0.1;
    int i = 0;
    int sign = 1;

    if(n[i] == '-') {
        sign = -1;
        i = 1;
    }
    while (n[i] >= '0' && n[i] <= '9') {
        result = result * 10 + (n[i] - '0');
        i++;
    }

    if (n[i] == '.') {
        i++;
        for (int j = 0; j < 4 && n[i] >= '0' && n[i] <= '9'; j++) {
            result += decimal * (n[i] - '0');
            decimal /= 10;
            i++;
        }
    }
    return result;
}

int aFloat(char n[]) {
    int dot = 0;
    for (int i = 0; n[i] != '\0'; i++) {
        if (i == 0 && n[i] == '-') {
            continue;
        }
        if (n[i] == '.')
            dot++;
        else if (n[i] < '0' || n[i] > '9')
            return 0;
    }
    return dot <= 1;
}

int mayAbs(int n) {
    if (n < 0)
        return -n;
    return n;
}

void copyMyString(char sour[], char destined[]) {
    int i;
    for (i = 0; sour[i] != '\0'; i++)
        destined[i] = sour[i];
    destined[i] = '\0';
}

int subStrings(char s1[], char s2[]) {
    for (int i = 0; s2[i] != '\0'; i++) {
        int j = 0;
        while (s1[j] != '\0' && s2[i + j] == s1[j])
            j++;
        if (s1[j] == '\0')
            return 1;
    }
    return 0;
}

int divaComparisonStrings(char st1[], char st2[]) {
    int i = 0;
    while (st1[i] != '\0' && st2[i] != '\0') {
        if (st1[i] < st2[i]) return -1;
        if (st1[i] > st2[i]) return 1;
        i++;
    }
    if (st1[i] == '\0' && st2[i] == '\0') return 0;
    if (st1[i] == '\0') return -1;
    return 1;
}

void camelCase(char c[]) {
    for (int i = 0; c[i] != '\0'; i++) {
        if (i % 2 == 0)
            c[i] = makeItLower(c[i]);
        else
            c[i] = makeItUpper(c[i]);
    }
}

void reverseThisString(char c[]) {
    int len = 0;
    while (c[len] != '\0') len++;

    for (int i = 0; i < len / 2; i++) {
        char temp = c[i];
        c[i] = c[len - i - 1];
        c[len - i - 1] = temp;
    }
}

int reverseThisDigit(int n) {
    int sign = 1;
    if (n < 0) {
        sign = -1;
        n = -n;
    }

    int rev = 0;
    while (n != 0) {
        rev = rev * 10 + (n % 10);
        n /= 10;
    }
    return rev * sign;
}