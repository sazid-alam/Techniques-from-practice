/* longest prefix of a string which is also a suffix of that string */

/*
    everything 0-indexed
    pi[i] = 0 -> empty string matched
    pi[i] = j -> prefix s[0..(j)] matched
*/
int prefixFunction(const string& s){

    int n = sz(s);

    vector<int> pi(n);

    FOR(i, 1, n){

        int j = pi[i - 1];

        /*
            while there is some matching left before it
            if Characters at the positions are equal : break
            else : go to next smaller matching.

            more explanation: https://codeforces.com/blog/entry/84359?#comment-718894.
        */
        while(j > 0 && s[j] != s[i]) j = pi[j - 1];

        if(s[j] == s[i]) j++;
        pi[i] = j;
    }
    return pi[n - 1];
}
