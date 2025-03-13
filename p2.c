#include <stdio.h>
#include "awk_sem.h"

int main() {
    int i = 0 ;

    // *** please insert proper semaphore initialization here
    int sem2 = get_sem(".", 'B');
    int sem3 = get_sem(".", 'C');

    do {
        // *** this is where you should place semaphore
       P(sem2);

       printf("P222222222 is here\n"); i++ ;

       // *** this is where you should place semaphore
       V(sem3);
       V(sem3);

    }  while (i < 100);
    return 0;
}
