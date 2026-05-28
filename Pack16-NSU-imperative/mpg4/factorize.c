typedef struct Factors
{
    int k;
    int primes[32];
    int powers[32];
} Factors;

void Factorize(int X, Factors *res)
{
    res->k = 0;

    int d = 2;

    while ((long long)d * d <= X)
    {
        if (X % d == 0)
        {
            int count = 0;

            while (X % d == 0)
            {
                X /= d;
                count++;
            }

            res->primes[res->k] = d;
            res->powers[res->k] = count;
            res->k++;
        }

        d++;
    }

    if (X > 1)
    {
        res->primes[res->k] = X;
        res->powers[res->k] = 1;
        res->k++;
    }
}