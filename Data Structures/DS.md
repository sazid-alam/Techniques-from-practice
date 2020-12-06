## Data Structures

<details>
<summary>  
    Binary Indexed Tree / Fenwick Tree 
</summary>

**Problem:** [CSES Range Sum Queries II](https://cses.fi/problemset/task/1648)

**Code:**

```cpp
ll n, q;
ll old[MX];
ll Tree[MX]; // 1 - indexed.

ll Update(ll idx, ll value){
    while(idx <= n){
        Tree[idx] += value;
        idx += (idx & -idx);
    }
}

ll Sum(ll idx){
    ll sum = 0;
    while(idx){
        sum += Tree[idx];
        idx -= (idx & -idx);
    }
    return sum;
}

ll Query(ll L, ll R){
    return Sum(R) - Sum(L - 1);
}

int main(){

    setIO();

    cin >> n >> q;

    FOR(i, 1, n + 1){
        cin >> old[i];
        Update(i, old[i]);
    }

    F0R(i, q){

        ll operation_type;
        cin >> operation_type;

        if(operation_type == 1){
            ll change_index, new_value;
            cin >> change_index >> new_value;
            Update(change_index, new_value - old[change_index]);
            old[change_index] = new_value;
        }
        else{
            ll L, R;
            cin >> L >> R;
            cout << Query(L, R) << "\n";
        }
    }
}
```
</details>

<details>
<summary>  
    Binary Indexed Tree / Fenwick Tree Template
</summary>

<details>
<summary>  
    1. Point Update and Range Query
</summary>

```cpp
struct BIT {      // 1D and 1 - indexed.
    int n; vll a; // Point Update and Range Query.
    void init(int s){ n = s; a = vll(n + 1, 0LL); }
    void add(int pos, ll delta){ while(pos <= n){ a[pos] += delta; pos += (pos & -pos); }}
    ll sum(int pos){ ll s = 0LL; while(pos > 0){ s += a[pos]; pos -= (pos & -pos); } return s; }
    ll query(int l, int r){ return sum(r) - sum(l - 1);}
};
```
</details>

</details>
