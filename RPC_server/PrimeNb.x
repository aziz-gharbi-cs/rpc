typedef bool Boolean;

struct PrimeRange {
    long min;
    long max;
};

struct PrimeList {
    int count;
    long primes<100>;
};

program PRIME_PROG {
    version PRIME_VERS_ONE {
        void CALNULL(void) = 0;
        Boolean ISPRIME(long) = 1;
        PrimeList RANGEPRIME(PrimeRange) = 2;
        PrimeList FIRSTPRIME(long) = 3;
    } = 1;
} = 0x20000001;
