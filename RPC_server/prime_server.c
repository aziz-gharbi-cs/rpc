#include <stdio.h>
#include "PrimeNb.h"


void *
calnull_1_svc(void *argp, struct svc_req *rqstp)
{
    static char result;

    printf("Message from procedure 0: RPC client connected successfully!\n");

    result = 0;
    return (void *)&result;
}

Boolean *
isprime_1_svc(long *n, struct svc_req *rqstp)
{
    static Boolean result;

    result = 1;

    if (*n < 2) {
        result = 0;
        return &result;
    }

    for (long i = 2; i * i <= *n; i++) {
        if (*n % i == 0) {
            result = 0;
            return &result;
        }
    }

    return &result;
}

PrimeList *
rangeprime_1_svc(PrimeRange *range, struct svc_req *rqstp)
{
    static PrimeList result;
    static long primes[100];

    result.count = 0;
    result.primes.primes_val = primes;
    result.primes.primes_len = 0;

    for (long n = range->min;
         n <= range->max && result.count < 100;
         n++) {

        int prime = 1;

        if (n < 2) {
            prime = 0;
        }

        for (long i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                prime = 0;
                break;
            }
        }

        if (prime) {
            result.primes.primes_val[result.count] = n;
            result.count++;
            result.primes.primes_len = result.count;
        }
    }

    return &result;
}

PrimeList *
firstprime_1_svc(long *n, struct svc_req *rqstp)
{
    static PrimeList result;
    static long primes[100];

    result.count = 0;
    result.primes.primes_val = primes;
    result.primes.primes_len = 0;

    long candidate = 2;

    while (result.count < *n && result.count < 100) {

        int prime = 1;

        for (long i = 2; i * i <= candidate; i++) {
            if (candidate % i == 0) {
                prime = 0;
                break;
            }
        }

        if (prime) {
            result.primes.primes_val[result.count] = candidate;
            result.count++;
            result.primes.primes_len = result.count;
        }

        candidate++;
    }

    return &result;
}
