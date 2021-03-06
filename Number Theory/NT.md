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
