<TeX>DYF的完整代码，临时应对用，需要看一会儿。</TeX>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

const double mi = 1e+20;
const double eps = 1e-08;
const double pi = 3.14159265358979;
inline int fi (double a)
{
    if (a > eps) return 1;
    else if (a >= -eps) return 0;
    else return -1;
}
const int mvert = 100010;
const int marea = 300010;
const int medge = 1000010;
double tx[mvert], ty[mvert];
int s, e;
struct edge_rec
{
    int in, out; double angle;
    edge_rec (void) {}
    edge_rec (int in0, int out0, double a0) : in(in0), out(out0), angle(a0) {}
    bool operator < (const edge_rec& a) const { return fi(angle - a.angle) == -1; }
};
double capacity[mvert];
vector<edge_rec> vertex[mvert];
inline int edge1 (int x) { return x << 1; }
inline int edge2 (int x) { return (x << 1) | 1; }
int next_rec[medge << 1], belong[medge << 1]; bool sch[medge << 1];
int areamr;
void find_ring (int x, int ori)
{
    if (next_rec[x] != ori) find_ring(next_rec[x], ori);
    belong[x] = areamr, sch[x] = true;
}
struct { int to, next; double len; } graph[medge]; int grapmr, mv;
void ginit (int m)
{
    grapmr = mv = m;
    for (int i = 0; i < m; i++) graph[i].next = -1;
}
void glink (int a, int b, double len)
{
    int p = grapmr++;
    graph[p].to = b, graph[p].len = len, graph[p].next = graph[a].next;
    graph[a].next = p;
}
struct dij_pair
{
    int vertex; double dist;
    dij_pair (void) {}
    dij_pair (int v0, double d0) : vertex(v0), dist(d0) {}
    bool operator < (const dij_pair& a) const
    {
        int tt = fi(dist - a.dist);
        if (tt) return tt == -1;
        else return vertex < a.vertex;
    }
};
set<dij_pair> heap;
double dist[marea]; bool proc[marea];
set<dij_pair>::iterator mh[marea];
double dijkstra (int source, int terminate)
{
    for (int i = 0; i < mv; i++) dist[i] = mi;
    dist[source] = 0;
    heap.clear();
    for (int i = 0; i < mv; i++) mh[i] = heap.insert(dij_pair(i, dist[i])).first, proc[i] = false;
    proc[source] = true;
    while (!heap.empty())
    {
        int cur = heap.begin()->vertex; heap.erase(heap.begin());
        proc[cur] = true;
        if (cur == terminate) break;
        for (int p = graph[cur].next; p != -1; p = graph[p].next)
        {
            int tar = graph[p].to;
            if (!proc[tar] && fi(dist[tar] - (dist[cur] + graph[p].len)) == 1)
            {
                dist[tar] = dist[cur] + graph[p].len;
                heap.erase(mh[tar]);
                mh[tar] = heap.insert(dij_pair(tar, dist[tar])).first;
            }
        }
    } return dist[terminate];
}
int main ()
{
    int n, m; scanf("%d %d", &n, &m);
    s = e = 0;
    for (int i = 0; i < n; i++)
    {
        double x, y; scanf("%lf %lf", &x, &y);
        tx[i] = x, ty[i] = y;
        if (fi(tx[s] - tx[i]) == 1) s = i;
        if (fi(tx[e] - tx[i]) == -1) e = i;
    }
    for (int i = 0; i < m; i++)
    {
        int a, b; double x; scanf("%d %d %lf", &a, &b, &x);
        if (a == b) { --m, --i; continue; }
        int eg1 = edge1(i), eg2 = edge2(i); capacity[i] = x;
        double agab = atan2(ty[b] - ty[a], tx[b] - tx[a]);
        double agba = atan2(ty[a] - ty[b], tx[a] - tx[b]);
        vertex[a].push_back(edge_rec(eg1, eg2, agab));
        vertex[b].push_back(edge_rec(eg2, eg1, agba));
    }
    int adder1 = edge1(m), adder2 = edge2(m);
    vertex[s].push_back(edge_rec(adder1, adder2, -pi));
    vertex[e].push_back(edge_rec(adder2, adder1, 0));
    for (int i = 0; i < n; i++)
    {
        sort(vertex[i].begin(), vertex[i].end());
        int ms = vertex[i].size();
        for (int j = 0; j < ms - 1; j++) next_rec[vertex[i][j].in] = vertex[i][j + 1].out;
        next_rec[vertex[i][ms - 1].in] = vertex[i][0].out;
    }
    areamr = 0; memset(sch, false, sizeof sch);
    for (int i = 0; i <= adder2; i++) if (!sch[i]) find_ring(i, i), ++areamr;
    ginit(areamr);
    for (int i = 0; i < m; i++)
    {
        int eg1 = edge1(i), eg2 = edge2(i);
        glink(belong[eg1], belong[eg2], capacity[i]);
        glink(belong[eg2], belong[eg1], capacity[i]);
    }
    printf("%.4f\n", dijkstra(belong[adder1], belong[adder2]));
    return 0;
} 
