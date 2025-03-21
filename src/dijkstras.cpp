#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph &G, int source,
                                   vector<int> &previous) {
  int numVertices = G.size();
  vector<int> distances(numVertices, INF);
  vector<bool> visited(numVertices, false);
  distances[source] = 0;
  previous[source] = -1;
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      minHeap;
  minHeap.push({source, 0});
  while (!minHeap.empty()) {
    int u = minHeap.top().first;
    minHeap.pop();
    if (visited[u] == true)
      continue;
    visited[u] = true;
    for (Edge edge : G[u]) {
      int v = edge.dst;
      int weight = edge.weight;
      if (distances[u] + weight < distances[v]) {
        distances[v] = distances[u] + weight;
        previous[v] = u;
        minHeap.push({v, distances[v]});
      }
    }
  }
  return distances;
}

vector<int> extract_shortest_path(const vector<int> &distances,
                                  const vector<int> &previous,
                                  int destination) {
  vector<int> result;
  result.push_back(destination);
  int source = destination;
  while (previous[source] != -1) {
    result.push_back(previous[source]);
    source = previous[source];
  }
  result = vector<int>(result.rbegin(), result.rend());
  return result;
}

void print_path(const vector<int> &v, int total) {
  for (int weight : v) {
    cout << weight << " ";
  }
  cout << endl;
  cout << "Total cost is " << total << endl;
}
