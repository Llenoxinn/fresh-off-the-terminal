// Honor Code!
// I declare, upon my honor, that I did this machine problem assignment by myself
// using online resources from the following:
// merc: https://mathworld.wolfram.com/MersennePrime.html
// perfect number: https://byjus.com/maths/perfect-numbers/
// scanf if: https://www.quora.com/What-if-I-use-scanf-in-the-if-statement-How-does-it-work
// Further, my solution is not a copy from the aforementioned sources.


// revised my code since i was using an array earlier. i apologize, sir HAHA :>

#include <stdio.h>

int main() {
    int n, count = 0;
    // long long num, sum = 0;

    // Input validation
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("INVALID INPUT");
        return 0;
    }
    
    int candidatePrime = 2;
    while(count < n) {
        int isitPrime = 1;
        for(unsigned int i = 2; i*i <= candidatePrime; i++) {
            if(candidatePrime % i == 0) {
                isitPrime = 0;
                break;
            }
        }
        if(isitPrime) {
            long long merc = (1LL << candidatePrime) - 1;
            
            int isitMerc = 1;
            
            for (long long j = 2; j * j <= merc; j++) {
                if(merc % j == 0) {
                    isitMerc = 0;
                    break;
                }
            }
            
            if(isitMerc) {
                long long merc1 = 1LL << (candidatePrime - 1);
                long long perfect = merc * merc1;
                printf("%lld", perfect);
                count++;
                if(count < n) { 
                    printf(" ");
                }
            }
        }
        candidatePrime++;
    }
    return 0;
}
