## Number Theory
<details>
<summary>  
    Calculate a^b mod m, Calculate a^(-b) mod m(m is prime).
</summary>
    
```cpp
ll Pow(ll a, ll b, ll m){
    if(b == 0) return 1;
    ll x = Pow(a, b / 2LL, m);
    x = (x * x) % m;
    return ((b & 1) ? x = (x * a) % m : x);
}

ll Inv(ll a, ll b, ll m){ return Pow(a, b * (m - 2) % (m - 1), m); }
```
</details>

<details>
<summary>  
    Finding all divisors of a^k from prime factorization
</summary>
    
```cpp
vector<pair<ll, ll>> primes;
vll d;
 
vll All_Div(ll n, ll k){
    primes.clear();
    d.clear();
    for(ll p = 2; p * p <= n; p++){
        if(n % p == 0){
            ll cnt = 0;
            while(n % p == 0) cnt++, n /= p;
            primes.push_back({p, cnt * k});
        }
    }
    if(n > 1){
        primes.push_back({n, k});
    }
 
    d.push_back(1);
    for(ll i = 0; i < primes.size(); i++){
        ll Size = d.size();
        ll p_pow = 1;
        for(ll j = 0; j < primes[i].second; j++){
            p_pow *= primes[i].first;
            for(ll i = 0; i < Size; i++){
                d.push_back(d[i] * p_pow);
            }
        }
    }
 
    sort(all(d));
    return d;
}
```
</details>

<details>
<summary>  
    Count number of divisors
</summary>
    
```cpp
long long numberOfDivisors(long long num) {
    long long total = 1;
    for (int i = 2; (long long)i * i <= num; i++) {
        if (num % i == 0) {
            int e = 0;
            do {
                e++;
                num /= i;
            } while (num % i == 0);
            total *= e + 1;
        }
    }
    if (num > 1) {
        total *= 2;
    }
    return total;
}
```
</details>

<details>
<summary>  
    Count sum of divisors
</summary>
    
```cpp
long long SumOfDivisors(long long num) {
    long long total = 1;

    for (int i = 2; (long long)i * i <= num; i++) {
        if (num % i == 0) {
            int e = 0;
            do {
                e++;
                num /= i;
            } while (num % i == 0);

            long long sum = 0, pow = 1;
            do {
                sum += pow;
                pow *= i;
            } while (e-- > 0);
            total *= sum;
        }
    }
    if (num > 1) {
        total *= (1 + num);
    }
    return total;
}
```
</details>


<details>
<summary>  
    Sieve of Eratosthenes
</summary>
    
```cpp
vector<bool> sieveEra(int n){
    vector<bool> is_prime(n+1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }
    return is_prime;
}

vector<int> getPrimes(int n) {
    vector<bool> is = sieveEra(n);
    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if(is[i]) primes.push_back(i);
    }
    return primes;
}
```
</details>


<details>
<summary>  
    Factorization
</summary>
    
```cpp
vector<long long> primes; // primes up to sqrt(n) is enough

vector<long long> factorize(long long n) {
    vector<long long> factorization;
    for (long long d : primes) {
        if (d * d > n)
            break;
        while (n % d == 0) {
            factorization.push_back(d);
            n /= d;
        }
    }
    if (n > 1)
        factorization.push_back(n);
    return factorization;
}
```
</details>

