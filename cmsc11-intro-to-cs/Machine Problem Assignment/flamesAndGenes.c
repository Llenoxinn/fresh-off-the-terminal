// HONOR CODE:
// I  declare, upon my honor, that I did this machine problem assignment by 
// myself using online resources from the following: 
// https://www.geeksforgeeks.org/c/strcpy-in-c/
// https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
// Further, my solution is not a copy from the aforementioned sources.
// NOTE THAT THIS IS A NEW CODE AND THE PAST IS IN THE PAST?? LET IT GOOOO??

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    int t, Dashin;
    
    scanf("%d", &t);
    getchar();
    
    for(int u = 0; u < t; u++) {

        scanf("%d", &Dashin);
        getchar();
        
        
        if(Dashin == 1) { 
            // EXECUTE FLAMES BABY
            char ftir_a[200], ftir_b[200];
            char ft_a[200], ft_b[200];
            
            fgets(ftir_a, sizeof(ftir_a), stdin);
            fgets(ftir_b, sizeof(ftir_b), stdin);
            
            // buffer[strcspn(buffer, "\n")] = 0;
            ftir_a[strcspn(ftir_a, "\n")] = 0;
            ftir_b[strcspn(ftir_b, "\n")] = 0;
            
            // maybe have a carbon copy of it
            strcpy(ft_a, ftir_a);
            strcpy(ft_b, ftir_b);
            
            // input is done but what's next?
            
            // DECLARE AND INITIALIZE VARIABLES ----
            // use int as datatype for total
            int i = 0;
            int j = 0;
            int l = 0;
            int honor_1 = 0, honor_2 = 0;
            // use char as datatype for storing lowercases!
            char lowerplease_1, lowerplease_2;
            
            for(int i = 0; ftir_a[i] != '\0'; i++){
                lowerplease_1 = tolower(ftir_a[i]);
                if(lowerplease_1 != ' ' && lowerplease_1 != '\n') {
                    honor_1++;
                }
            }
            for(int i = 0; ftir_b[i] != '\0'; i++) {
                lowerplease_2 = tolower(ftir_b[i]);
                if(lowerplease_2 != ' ' && lowerplease_2 != '\n') {
                    honor_2++;
                }
            }
            
            for(int i = 0; ftir_a[i] != '\0'; i++) {
                lowerplease_1 = tolower(ftir_a[i]);
                if(lowerplease_1 == ' ' || lowerplease_1 == '\n') continue;
                
                if(ftir_a[i] == '&') continue;
                
                int foundyah = 0;
                
                for(int j=0; ftir_b[j] != '\0'; j++) {
                    lowerplease_2 = tolower(ftir_b[j]);
                    if(lowerplease_2 == ' ' || lowerplease_2 == '\n') continue;
                    if (lowerplease_1 == lowerplease_2) {
                        foundyah=1;
                        break;
                    }
                }
                
                if(foundyah) {
                    for(int l = 0; ftir_a[l] != '\0'; l++) {
                        char peekk = tolower(ftir_a[l]);
                        if(peekk == lowerplease_1) {
                            ftir_a[l] = '&';
                        }
                    }
                    for(int l = 0; ftir_b[l] != '\0'; l++) {
                        char peekk = tolower(ftir_b[l]);
                        if(peekk == lowerplease_1) {
                            ftir_b[l] = '&';
                        }
                    }
                }
            }
            int crushed_1 = 0, crushed_2 = 0;
            
            for(int i = 0; ftir_a[i] != '\0'; i++) {
                if(ftir_a[i] == '&')
                    crushed_1++;
            }
            for(int j = 0; ftir_b[j] != '\0'; j++) {
                if(ftir_b[j] == '&')
                    crushed_2++;
            }
            
            int total_crushed = crushed_1 + crushed_2;
                
                // if 0, then NEVER! chariz;..
            if(total_crushed == 0) {
                printf("%s does not want to have anything to do with %s.\n", ft_a, ft_b);
                printf("%s does not want to have anything to do with %s.\n", ft_b, ft_a);
                printf("They are not a thing. They will never be.\n");
                continue;
            }
            
            int out_it_out = 0;
            // get the remainder
            int len = 6;
            out_it_out = crushed_1 % len;
            
            // however what if the out is 0? then it should be the previous [SWEETHEARTS]!
            if(out_it_out == 0) out_it_out = 6;
            
            printf("%s wants to be ", ft_a);
            switch (out_it_out) {
                case 1: printf("FRIENDS"); 
                    break;
                case 2: printf("LOVERS"); 
                    break;
                case 3: printf("ACCEPT their fate"); 
                    break;
                case 4: printf("MARRIED"); 
                    break;
                case 5: printf("ENGAGED"); 
                    break;
                case 6: printf("SWEETHEARTS"); 
                    break;
            }
            printf(" with %s.                               \n", ft_b);
            
            out_it_out = crushed_2 % len;
            if(out_it_out == 0) out_it_out = 6;

            printf("%s wants to be ", ft_b);
            switch (out_it_out) {
                case 1: printf("FRIENDS"); 
                    break;
                case 2: printf("LOVERS"); 
                    break;
                case 3: printf("ACCEPT their fate"); 
                    break;
                case 4: printf("MARRIED"); 
                    break;
                case 5: printf("ENGAGED"); 
                    break;
                case 6: printf("SWEETHEARTS"); 
                    break;
            }
            // ADDED SPACES BECAUSE SAM MILBY IS INCORRECt???
            printf(" with %s.                           \n", ft_a);
            //
            //
            out_it_out = total_crushed % len;    
            if(out_it_out == 0) out_it_out = 6;
            
            if(out_it_out == 1){
                printf("They will end up as FRIENDS.\n");}
            else if(out_it_out == 2){
                printf("They will end up as LOVERS.\n");}
            else if(out_it_out == 3){
                printf("They will ACCEPT their fate, whatever it is.\n");}
            else if(out_it_out == 4){
                printf("They will end up as a MARRIED couple.\n");}
            else if(out_it_out == 5){
                printf("They will be ENGAGED.\n");}
            else if (out_it_out == 6){
                printf("They will end up as SWEETHEARTS.\n");
            }
    }
        else if (Dashin == 2) {
            char gene_1[500], gene_2[500];
            
            int burn=0, index[500];
            int akopaba=1;
            
            fgets(gene_1, sizeof(gene_1), stdin);
            fgets(gene_2, sizeof(gene_2), stdin);

            gene_1[strcspn(gene_1, "\n")] = 0;
            gene_2[strcspn(gene_2, "\n")] = 0;
            
            int len1 = strlen(gene_1);
            int len2 = strlen(gene_2);
                for (int i = 0; i <= len1 - len2; i++) {
                
                    akopaba = 1;
                
                    for (int j = 0; j < len2; j++) {
                        if (gene_1[i+j] != gene_2[j]) {
                            akopaba = 0;
                            break;
                        }
                    }
                    if (akopaba) {
                        index[burn] = i;   
                        burn++;
                    }
                }
                if (burn > 0) {
                    printf("YES\n%d\n", burn);
                    for (int k = 0; k < burn; k++) {
                        printf("%d ", index[k]);
                    }
                    printf("\n");
                } else {
                    printf("NO\n");
                }
         
                }
            }
            // scanf("%s", gene_1);
            // scanf("%s", gene_2);
            return 0;
        }
