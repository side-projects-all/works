#include "Shortest_path.h"

int Shortest_path::find_smallest_reacheable(std::vector<std::vector<int>>& shortest_paths, int& distanceThreshold) {
  int ans = -1;
  int n = shortest_paths.size();
  int fewest = n;

  for (int i = 0; i < n; ++i) {
    int reach_cnt = 0;

    for (int j = 0; j < n; ++j) {
      if (i == j) {
        continue;
      }

      if (shortest_paths[i][j] <= distanceThreshold) {
        ++reach_cnt;
      }
    }

    if (reach_cnt <= fewest) {
      ans = i;
      fewest = reach_cnt;
    }
  }

  return ans;
}
int Shortest_path::by_Dijkstra_alg(int n, std::vector<std::vector<int>>& edges, int& distanceThreshold) {

  std::vector<std::vector<std::pair<int, int>>> adj(n, std::vector<std::pair<int, int>>());
  for (const auto& e : edges) {
    adj[e[0]].push_back({e[1], e[2]});
    adj[e[1]].push_back({e[0], e[2]});
  }

  std::vector<std::vector<int>> shortest_paths(n, std::vector<int>(n, INT_MAX));
  std::priority_queue<std::pair<int, int>, 
                      std::vector<std::pair<int, int>>, 
                      std::greater<std::pair<int, int>>> pq;

  for (int i = 0; i < n; ++i) {
    pq.push({0, i});

    while (!pq.empty()) {
      auto [curr_summed_dis, curr] = pq.top();
      pq.pop();

      if (curr_summed_dis > shortest_paths[i][curr]) {
        continue;
      }

      for (const auto& [nei, dis] : adj[curr]) {
                    
          if (shortest_paths[i][nei] > dis + curr_summed_dis) {
              shortest_paths[i][nei] = dis + curr_summed_dis;
              pq.push({dis + curr_summed_dis, nei});
          }
      }
    }
  }

  return find_smallest_reacheable(shortest_paths, distanceThreshold);
}
int Shortest_path::by_Bellman_ford_alg(int n, std::vector<std::vector<int>>& edges, int& distanceThreshold) {
  std::vector<std::vector<int>> shortest_paths(n, std::vector<int>(n, INT_MAX));

  //starting from every city 
  for (int i = 0; i < n; ++i) {
    shortest_paths[i][i] = 0;
    //using the idea of n nodes n-1 edges
    for (int e = 1; e < n; ++e) {
      for (const auto& edge : edges) {
        int from = edge[0];
        int to = edge[1];
        int weight = edge[2];

        if (shortest_paths[i][from] != INT_MAX && shortest_paths[i][from] + weight < shortest_paths[i][to]) {
          shortest_paths[i][to] = shortest_paths[i][from] + weight;
        }

        //undirected graph, do both directions
        if (shortest_paths[i][to] != INT_MAX && shortest_paths[i][to] + weight < shortest_paths[i][from]) {
            shortest_paths[i][from] = shortest_paths[i][to] + weight;
        }
      }
    }
  }

  return find_smallest_reacheable(shortest_paths, distanceThreshold);
}
int Shortest_path::by_Floyd_warshall_alg(int n, std::vector<std::vector<int>>& edges, int& distanceThreshold) {
  std::vector<std::vector<int>> shortest_paths(n, std::vector<int>(n, INT_MAX));

  for (int i = 0; i < n; ++i) {
    shortest_paths[i][i] = 0;
  }

  for (const auto& e : edges) {
    shortest_paths[e[0]][e[1]] = e[2];
    shortest_paths[e[1]][e[0]] = e[2];
  }

  for (int mid = 0; mid < n; ++mid) {
    for (int from = 0; from < n; ++from) {
      for (int to = 0; to < n; ++to) {

        int by_mid = (shortest_paths[from][mid] == INT_MAX || 
                        shortest_paths[mid][to] == INT_MAX) ? INT_MAX : 
                            shortest_paths[from][mid] + shortest_paths[mid][to];

        shortest_paths[from][to] = std::min(shortest_paths[from][to], by_mid);
      }
    }
  }
  
  return find_smallest_reacheable(shortest_paths, distanceThreshold);
}
int Shortest_path::findTheCity() {
  int n = 4;
  std::vector<std::vector<int>> edges{ {0,1,3}, {1,2,1}, {1,3,4}, {2,3,1} };
  int distanceThreshold = 4;

  //return by_Dijkstra_alg(n, edges, distanceThreshold);
  //return by_Bellman_ford_alg(n, edges, distanceThreshold);
  return by_Floyd_warshall_alg(n, edges, distanceThreshold);
}