#include "graph.h"
using namespace std;
void error(string msg) { cout << "Error: " << msg << endl; }

DisjointSet::DisjointSet(int numVertices) {
  subsets.resize(numVertices);
  for (int i = 0; i < numVertices; ++i) {
    DisjointSet::makeSet(i);
  }
}

void DisjointSet::makeSet(Vertex x) { subsets[x].parent = x; }

Vertex DisjointSet::findSet(Vertex x) {
  if (x != subsets[x].parent) {
    subsets[x].parent = findSet(subsets[x].parent);
  }
  return subsets[x].parent;
}

void DisjointSet::unionSets(Vertex x, Vertex y) {
  Vertex temp1 = findSet(x);
  Vertex temp2 = findSet(y);
  if (temp1 != temp2) {
    subsets[temp2].parent = temp1;
  }
}

Graph Graph::sort_edges() const {
  Graph temp_graph = *this;
  sort(temp_graph.begin(), temp_graph.end(),
       [](const Edge &a, const Edge &b) { return a.weight < b.weight; });
  return temp_graph;
}

VertexList Graph::edges_from(Vertex vertex) const {
  VertexList ListOfEdges;
  for (const auto &i : *this) {
    if (i.u == vertex) {
      ListOfEdges.push_back(i.v);
    }
  }
  return ListOfEdges;
}

EdgeList Kruskals(const Graph &G) {
  Graph sorted = G.sort_edges();
  DisjointSet disjoint_set(G.numVertices);
  EdgeList minspantree;
  for (const auto &i : sorted) {
    if (disjoint_set.findSet(i.u) != disjoint_set.findSet(i.v)) {
      minspantree.push_back(i);
      disjoint_set.unionSets(i.u, i.v);
    }
  }
  return minspantree;
}

int sum_weights(EdgeList const &L) {
  return accumulate(L.begin(), L.end(), 0, [](int total, const Edge &edge) {
    return total + edge.weight;
  });
}

void file_to_graph(string filename, Graph &G) {
  ifstream file(filename);
  if (!file) {
    error("Failed to open file");
  }
  file >> G;
}

VertexList dfs(const Graph &graph, Vertex startVertex) {
  VertexList result;
  vector<bool> visited(graph.size(), false);
  stack<Vertex> stk;
  visited[startVertex] = true;
  stk.push(startVertex);
  while (!stk.empty()) {
    Vertex vertex = stk.top();
    stk.pop();
    result.push_back(vertex);
    for (Vertex v : graph.edges_from(vertex))
      if (!visited[v]) {
        visited[v] = true;
        stk.push(v);
      }
  }
  return result;
}

VertexList bfs(const Graph &graph, Vertex startVertex) {
  VertexList result;
  vector<bool> visited(graph.size(), false);
  queue<Vertex> queue;
  visited[startVertex] = true;
  queue.push(startVertex);

  while (!queue.empty()) {
    Vertex vertex = queue.front();
    queue.pop();
    result.push_back(vertex);
    for (Vertex v : graph.edges_from(vertex))
      if (!visited[v]) {
        visited[v] = true;
        queue.push(v);
      }
  }
  return result;
}

string get_arg(int argc, char *argv[], string def) {
  return (argc > 1) ? argv[1] : def;
}