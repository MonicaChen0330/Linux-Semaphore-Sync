#include <stdio.h>
#include "awk_sem.h"

int main() {
    int i = 0 ;

    // *** please insert proper semaphore initialization here
    int sem3 = get_sem(".", 'C');
    int sem1 = get_sem(".", 'A');

    do {
        // *** this is where you should place semaphore
       P(sem3);

       printf("P3333333 is here\n"); i++ ;

       // *** this is where you should place semaphore
       V(sem1);

    }  while (i< 200);
    return 0;
}
