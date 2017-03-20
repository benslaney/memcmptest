#include <stdio.h>
#include <time.h>

int mycmp(const unsigned char *cmp1, const unsigned char *cmp2, unsigned int length);

int main(int argc, const char * argv[]) {
    long i;
    clock_t begin;
    double time_spent;
    
    
    /* Test the native memcmp() speed by running a simple non-matching comparison a billion times */
    begin = clock();
    for(i = 0; i < 1000000000; i++) {
        if(!memcmp("111111","222222",6))
            printf("Found it\n");
    }
    time_spent = (double)(clock() - begin) / CLOCKS_PER_SEC;
    printf("Native memcmp:\t\t%f\n",time_spent);

    
    /* Test the modified memcmp() speed */
    begin = clock();
    for(i = 0; i < 1000000000; i++) {
        if(!mycmp("111111","222222",6))
            printf("Found it\n");
    }
    time_spent = (double)(clock() - begin) / CLOCKS_PER_SEC;
    printf("Modified memcmp:\t%f\n",time_spent);
    
    
    return 0;
}


/*  The modified memcmp. It simply typecasts the values to int's and return the difference if the first
     four bytes are difference and otherwise returns the native memcmp()'s return value */
int mycmp(const unsigned char *cmp1, const unsigned char *cmp2, unsigned int length) {
    if(length >= 4) {
        int difference = *(int *)cmp1 - *(int *)cmp2;
        if(difference)
            return difference;
    }
    
    return memcmp(cmp1,cmp2,length);
}
