#include <bits/stdc++.h>
#include "fibonacci.hpp"
using namespace std;
#define ff first
#define ss second
vector<vector<pair<int, int>>> adj;
int main() {
  int n, m;
  cin >> n >> m;
  adj.resize(n);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    --u, --v;
    adj[u].emplace_back(v, w);
  }
  // BELLMAN-FORD
  int s = adj.size();
  adj.emplace_back();
  for (int i = 0; i < s; ++i) adj[s].emplace_back(i, 0);
  int H[s + 1];
  memset(H, 0x3f, sizeof(H));
  H[s] = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < adj.size(); ++j) {
      for (auto p : adj[j]) H[p.ff] = min(H[p.ff], p.ss + H[j]);
    }
  }
  adj.pop_back();
  for (int i = 0; i < n; ++i) for (auto& p : adj[i]) {
      p.ss += H[i] - H[p.ff];
    }
  // DIJKSTRA
  int cal[n][n];
  for (int i = 0; i < n; ++i) {
    FibonacciHeap<pair<int, int>> h;
    int dist[n];
    memset(dist, 0x3f, sizeof(dist));
    dist[i] = 0;
    vector<node<pair<int, int>>*> index(n, NULL);
    index[i] = h.insert(make_pair(0, i));
    while (!h.isEmpty()) {
      auto u = h.getMinimum().second;
      h.removeMinimum();
      for (auto p : adj[u]) {
        if (index[p.ff] == NULL) {
          dist[p.ff] = dist[u] + p.ss;
          index[p.ff] = h.insert(make_pair(dist[p.ff], p.ff));
        } else {
          if (dist[u] + p.ss < dist[p.ff]) {
            dist[p.ff] = dist[u] + p.ss;
            h.decreaseKey(index[p.ff], make_pair(dist[u] + p.ss, p.ff));
          }
        }
      }
    }
    for (int j = 0; j < n; ++j) cal[i][j] = dist[j] - H[i] + H[j];
  }
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) cout << cal[i][j] << " \n"[j == n - 1];
}
