#include <stdio.h>
#include <stdlib.h>
#include "PrimeNb.h"

int main(int argc, char *argv[])
{
    CLIENT *clnt;
    char *host;
    int choice;
    long n;
    PrimeRange range;
    Boolean *prime_result;
    PrimeList *result;
    void *null_result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <host>\n", argv[0]);
        return 1;
    }

    host = argv[1];

    clnt = clnt_create(host, PRIME_PROG, PRIME_VERS_ONE, "tcp");

    if (clnt == NULL) {
        clnt_pcreateerror(host);
        return 1;
    }

    printf("\n0. CALNULL\n");
    printf("1. IsPrime\n");
    printf("2. RangePrime\n");
    printf("3. FirstPrime\n");
    printf("Choice: ");
    scanf("%d", &choice);

    switch (choice) {

        case 0:
            null_result = calnull_1(NULL, clnt);

            if (null_result == NULL) {
                clnt_perror(clnt, "CALNULL RPC call failed");
                clnt_destroy(clnt);
                return 1;
            }

            printf("CALNULL called successfully.\n");
            break;

        case 1:
            printf("Enter a number: ");
            scanf("%ld", &n);

            prime_result = isprime_1(&n, clnt);

            if (prime_result == NULL) {
                clnt_perror(clnt, "ISPRIME RPC call failed");
                clnt_destroy(clnt);
                return 1;
            }

            printf("%ld is %s\n",
                   n,
                   (*prime_result) ? "prime" : "not prime");
            break;

        case 2:
            printf("Enter minimum: ");
            scanf("%ld", &range.min);

            printf("Enter maximum: ");
            scanf("%ld", &range.max);

            result = rangeprime_1(&range, clnt);

            if (result == NULL) {
                clnt_perror(clnt, "RANGEPRIME RPC call failed");
                clnt_destroy(clnt);
                return 1;
            }

            printf("Prime numbers between %ld and %ld:\n",
                   range.min, range.max);

            for (u_int i = 0; i < result->primes.primes_len; i++) {
                printf("%ld ", result->primes.primes_val[i]);
            }

            printf("\n");
            break;

        case 3:
            printf("Enter number of primes: ");
            scanf("%ld", &n);

            result = firstprime_1(&n, clnt);

            if (result == NULL) {
                clnt_perror(clnt, "FIRSTPRIME RPC call failed");
                clnt_destroy(clnt);
                return 1;
            }

            printf("First %ld prime numbers:\n", n);

            for (u_int i = 0; i < result->primes.primes_len; i++) {
                printf("%ld ", result->primes.primes_val[i]);
            }

            printf("\n");
            break;

        default:
            printf("Invalid choice.\n");
    }

    clnt_destroy(clnt);

    return 0;
}
