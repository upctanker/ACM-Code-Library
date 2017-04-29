#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <queue>
#include <vector>
using namespace std;

// Dijkstra �㷨���ڽӱ� + �����
// O(E log V) ���·

const int MAXN = 1005; // �ڵ����
const int MAXM = 1000005;   // �ߵĸ���
const int INF = 1234567890;

struct edge{
    int u, v, w; // �� u �� v ȨΪ w
};

struct graph{
    int V, E; // �ڵ�������ߵĸ���
    edge edges[MAXM];
    vector<int> adj[MAXN];
    int d[MAXN]; // s���������
    int p[MAXN]; // ���·����һ����

    void init(){
        E = 0;
    }

    void add_edge(edge e){
        edges[E] = e;
        adj[e.u].push_back(E++);
    }

    bool done[MAXN];
    void dijkstra(int src){
        typedef pair<int,int> pii; // ����, �ڵ���
        priority_queue<pii, vector<pii>, greater<pii> > q;

        fill(d, d + V + 1, INF);
        d[src] = 0;
        fill(done, done + V + 1, 0);
        q.push(make_pair(0, src));
        while (!q.empty()){
            pii x = q.top(); q.pop();
            int u = x.second;
            if (done[u]) continue;
            done[u] = true;
            for (int i = 0; i < adj[u].size(); i++){
                edge& e = edges[adj[u][i]];
                if (d[e.v] > d[u] + e.w){
                    d[e.v] = d[u] + e.w;
                    p[e.v] = adj[u][i];
                    q.push(make_pair(d[e.v], e.v));
                }
            }
        }
    }
} g;

// POJ 2387
int main(){
    int ec;
    scanf("%d%d", &ec, &g.V);
    g.init();
    for (int i=0; i<ec; i++){
        edge e;
        scanf("%d%d%d", &e.u, &e.v, &e.w);
        g.add_edge(e);
        swap(e.u, e.v);
        g.add_edge(e);
    };
    g.dijkstra(1);
    printf("%d", g.d[g.V]);
    return 0;
}
