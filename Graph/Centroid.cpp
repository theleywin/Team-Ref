//
// Created by Pablo Gómez Vidal on 21/09/24.
//
#include<bits/stdc++.h>
const int maxn = 2e5;
struct Centroid
{

    set<int> tree[maxn];
    map<int, int> dist[maxn];
    int subtreesz[maxn], par[maxn], ans[maxn];

    void init(int n)
    {
        for(int i=1; i<=n; i++)
        {
            tree[i].clear();
            dist[i].clear();
            ans[i] = maxn;
        }
    }

    void addEdge(int u, int v)
    {
        tree[u].insert(v);
        tree[v].insert(u);
    }

    int findSubtreeSize(int u, int p)
    {
        subtreesz[u] = 1;
        for(auto v : tree[u])
        {
            if(v==p)continue;
            subtreesz[u] += findSubtreeSize(v, u);
        }
        return subtreesz[u];
    }

    int findCentroid(int u, int p, int n)
    {
        for(auto v : tree[u])
        {
            if(v==p)continue;
            if(subtreesz[v]>n/2)
                return findCentroid(v, u, n);
        }
        return u;
    }

    void findDist(int u, int p, int c, int d)   // build distance
    {
        dist[c][u] = d;
        for(auto v : tree[u])
        {
            if(v==p)continue;
            findDist(v, u, c, d + 1);
        }
    }

    void buildCentroidTree(int u, int p)
    {
        int n = findSubtreeSize(u, p);
        int c = findCentroid(u, p, n);
        if(p == -1) p = c;
        par[c] = p;
        findDist(c, p, c, 0);

        vector<int> tmp(tree[c].begin(), tree[c].end());
        for(auto v : tmp)
        {
            tree[c].erase(v);
            tree[v].erase(c);
            buildCentroidTree(v, c);
        }
    }

};