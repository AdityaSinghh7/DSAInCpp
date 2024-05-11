#include "dijkstras.h"
using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source,
                                   vector<int>& previous) {
  vector<int> distances(G.size(), INF);
  distances[source] = 0;

  using pii = pair<int, int>;
  priority_queue<pii, vector<pii>, greater<pii>> queue;
  queue.push({0, source});

  previous = vector<int>(G.size(), -1);

  while (!queue.empty()) {
    int distance = queue.top().first;
    int vertex = queue.top().second;
    queue.pop();
    for (auto& e : G[vertex]) {
      if (distances[vertex] + e.weight < distances[e.dst]) {
        distances[e.dst] = distances[vertex] + e.weight;
        queue.push({distances[e.dst], e.dst});
        previous[e.dst] = vertex;
      }
    }
  }

  return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances,
                                  const vector<int>& previous,
                                  int destination) {
  vector<int> path;
  for (int vertex = destination; vertex != -1; vertex = previous[vertex])
    path.push_back(vertex);

  reverse(path.begin(), path.end());

  return path;
}

void print_path(const vector<int>& v, int total) {
  for (int i = 0; i < v.size(); ++i) {
    cout << v[i] << " ";
  }
  cout << "\nTotal cost is " << total << "\n";
}