//
// Created by catboy on 2/22/2025.
//

#ifndef GRAPHALKO_HEADERS_VISITORSHEADERS_SHORTESTPATHVISITORS_HPP_
#define GRAPHALKO_HEADERS_VISITORSHEADERS_SHORTESTPATHVISITORS_HPP_
#include"Visitors.hpp"

template<typename CurGraph>
class FloydWarshallVisitor {
 protected:
  using graph_type = CurGraph;
  using vert_desc = int;
  int amount_vertex;
  std::vector<std::vector<int>> dist;

 public:

  FloydWarshallVisitor(int amount_vertex) : amount_vertex(amount_vertex),
                                            dist(amount_vertex, std::vector<int>(amount_vertex, 0)) {};

  void PrintDist() {
    std::cerr << "dist \n";
    for (auto &i : dist) {
      for (std::size_t j = 0; j < dist.size(); j++) {
        std::cerr << " " << i[j];
      }
      std::cerr << "\n";
    }
  }

  int GetDist(int from, int to) {
    return dist[from][to];
  }

  void FloydWarshell(CurGraph &graph);
};

template<typename CurGraph>
void FloydWarshallVisitor<CurGraph>::FloydWarshell(CurGraph &graph) {
  dist = graph.GetMatrixNear();
  PrintDist();
  std::cerr << "storage.size() = " << amount_vertex;

  for (std::size_t i = 0; i < amount_vertex; i++) {
    for (std::size_t j = 0; j < amount_vertex; j++) {
      for (std::size_t k = 0; k < amount_vertex; k++) {
        if ((dist[j][i] != 0) && (dist[i][k] != 0)) {
          if ((dist[j][k] == 0) && (j != k)) {
            dist[j][k] = dist[j][i] + dist[i][k];
          } else {
            dist[j][k] = std::min(dist[j][k], dist[j][i] + dist[i][k]);
          }
        }
      }
    }
  }
  PrintDist();
}

template<typename CurGraph, std::enable_if_t<std::is_base_of_v<Edges<bool>, typename CurGraph::edges_type>,
                                             bool> = true>
class BFSShortestPathBetweenPair : public BFSVisitor<CurGraph> {
 public:
  int begin;
  int end;
  bool EndAlgorim = false;
  std::vector<int> way;
  std::vector<int> deep;

  BFSShortestPathBetweenPair(int begin, int end, int amount_vertex)
      : begin(begin), end(end), way(amount_vertex, -1), deep(amount_vertex, 0) {

  }

  bool discover_vertex_BFS(BFSVisitor<CurGraph>::vert_desc top, BFSVisitor<CurGraph>::graph_type &graph) {
    if (top == end) {
      EndAlgorim = true;
      return true;
    }
    return EndAlgorim;
  }

  void examine_edge_BFS(BFSVisitor<CurGraph>::edge_desc edge,
                        BFSVisitor<CurGraph>::edge_desc_iter iter,
                        BFSVisitor<CurGraph>::graph_type &graph) {
    if (way[edge.second] == -1) {
      way[edge.second] = edge.first;
      deep[edge.second] = deep[edge.first] + 1;
      std::cerr << "deep " << edge.second << " " << deep[edge.second];
    }
  }
};

#endif //GRAPHALKO_HEADERS_VISITORSHEADERS_SHORTESTPATHVISITORS_HPP_
