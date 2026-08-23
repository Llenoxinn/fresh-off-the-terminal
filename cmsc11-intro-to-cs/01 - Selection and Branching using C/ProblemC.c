// HONOR CODE: I declare, upon my honor, that I did this machine problem by myself using online resources from the following 
// https://stackoverflow.com/questions/276706/what-are-bitwise-operators
// https://www.w3schools.com/c/c_bitwise_operators.php
// Further, my solution is not a copy from the aforementioned sources.

// instructions: Ask the user to enter his/her birth month and day (in numerical format, e.g. 8 for August). 
// Based on these inputs, tell him/her his/her zodiac sign and display a fortune. The fortune should come from the 
// following list only (choose any 12 to serve as fortune or horoscope for the day) for the 12 zodiac signs. DO NOT FORGET ABOUT THE HONOR CODE. 

#include <stdio.h>

int main() {
    int birth_month, day;
    int valid = 1; // flag to check if date is valid

    printf("Enter your birth month and day (e.g. 8 23): ");
    scanf("%d %d", &birth_month, &day);

    // Validate month first
    if (birth_month < 1 || birth_month > 12) {
        printf("\nInvalid month! Please enter a value between 1 and 12.\n");
        return 0;
    }

    // Days in each month (allow up to 29 in February)
    int days_in_month[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (day < 1 || day > days_in_month[birth_month]) {
        printf("\nInvalid day for the given month! Please try again.\n");
        return 0;
    }

    printf("\n");

    // Zodiac and Fortune determination
    if ((birth_month == 1 && day >= 20) || (birth_month == 2 && day <= 18)) {
        printf("\t\tAquarius\n");
        printf("\t\tFORTUNE: Be different: conform.\n");
    }
    else if ((birth_month == 2 && day >= 19) || (birth_month == 3 && day <= 20)) {
        printf("\t\tPisces\n");
        printf("\t\tFORTUNE: You are confused; but this is your normal state.\n");
    }
    else if ((birth_month == 3 && day >= 21) || (birth_month == 4 && day <= 19)) {
        printf("\t\tAries\n");
        printf("\t\tFORTUNE: You will be reincarnated as a toad; and you will be much happier.\n");
    }
    else if ((birth_month == 4 && day >= 20) || (birth_month == 5 && day <= 20)) {
        printf("\t\tTaurus\n");
        printf("\t\tFORTUNE: Today is the tomorrow you worried about yesterday.\n");
    }
    else if ((birth_month == 5 && day >= 21) || (birth_month == 6 && day <= 20)) {
        printf("\t\tGemini\n");
        printf("\t\tFORTUNE: You are going to have a new love affair.\n");
    }
    else if ((birth_month == 6 && day >= 21) || (birth_month == 7 && day <= 22)) {
        printf("\t\tCancer\n");
        printf("\t\tFORTUNE: You are sick, twisted and perverted. I like that in a person.\n");
    }
    else if ((birth_month == 7 && day >= 23) || (birth_month == 8 && day <= 22)) {
        printf("\t\tLeo\n");
        printf("\t\tFORTUNE: Your lucky number is 3552664958674928. Watch for it everywhere.\n");
    }
    else if ((birth_month == 8 && day >= 23) || (birth_month == 9 && day <= 22)) {
        printf("\t\tVirgo\n");
        printf("\t\tFORTUNE: Be free and open and breezy! Enjoy! Things won't get any better so get used to it.\n");
    }
    else if ((birth_month == 9 && day >= 23) || (birth_month == 10 && day <= 22)) {
        printf("\t\tLibra\n");
        printf("\t\tFORTUNE: You two ought to be more careful--your love could drag on for years and years.\n");
    }
    else if ((birth_month == 10 && day >= 23) || (birth_month == 11 && day <= 21)) {
        printf("\t\tScorpio\n");
        printf("\t\tFORTUNE: You definitely intend to start living sometime soon.\n");
    }
    else if ((birth_month == 11 && day >= 22) || (birth_month == 12 && day <= 21)) {
        printf("\t\tSagittarius\n");
        printf("\t\tFORTUNE: Don't relax! It's only your tension that's holding you together.\n");
    }
    else if ((birth_month == 12 && day >= 22) || (birth_month == 1 && day <= 19)) {
        printf("\t\tCapricorn\n");
        printf("\t\tFORTUNE: You are number 6! Who is number one?\n");
    }
    else {
        valid = 0; // sheesh check
    }

    if (valid)
        printf("\nThank you for using the Zodiac Fortune Teller!\n");

    printf("\n");
    return 0;
}
