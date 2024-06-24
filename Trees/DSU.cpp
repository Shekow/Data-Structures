#include <iostream>
#include <vector>
using namespace std;

class DSU
{
    vector<size_t> par, rank, nxt;
    size_t sz, comps;
    public:
    DSU(size_t n) : sz(n)
    {
        par = rank = nxt = vector<size_t>(sz + 1);
        for (size_t i{1}; i <= sz; i++)
            par[i] = nxt[i] = i;
        comps = n;
    }
    size_t get(size_t a)
    {
        return par[a] = (par[a] == a ? a : get(par[a]));
    }
    bool unite(size_t a, size_t b)
    {
        a = get(a), b = get(b);
        if (a == b)
            return false;
        if (rank[a] == rank[b]) 
            rank[a]++;
        if (rank[a] < rank[b]) 
            swap(a, b);
        par[b] = a;
        comps--;
        return true;
    }
    size_t get_r(size_t a)
    {
        return nxt[a] = (nxt[a] == a ? a : get_r(nxt[a]));
    }
    void unite_r(size_t a, size_t b)
    {
        for (size_t d{get_r(a)}; d < b; d = get_r(d + 1))
        {
            unite(d, b);
            nxt[d] = b;
        }
    }
};