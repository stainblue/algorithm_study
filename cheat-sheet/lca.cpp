#include <vector>
#include <algorithm>

#define endl "\n"
using namespace std;

const int MAXN = 1e5 + 5;
int N, M, par[MAXN][20], dep[MAXN];
vector<int> adj[MAXN];

void dfs(int u, int p, int d)
{
    par[u][0] = p;
    dep[u] = d;
    for (auto v : adj[u])
    {
        if (v == p)
            continue;
        dfs(v, u, d + 1);
    }
}

void init()
{
    dfs(1, 0, 0);

    for (int k = 1; k < 20; k++)
        for (int i = 1; i <= N; i++)
            par[i][k] = par[par[i][k - 1]][k - 1];
}

int lca(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);

    for (int k = 19; k >= 0; k--)
    {
        if (1 << k <= dep[u] - dep[v])
            u = par[u][k];
    }

    if (u == v)
        return u;

    for (int k = 19; k >= 0; k--)
    {
        if (par[u][k] != par[v][k])
        {
            u = par[u][k];
            v = par[v][k];
        }
    }

    return par[u][0];
}
