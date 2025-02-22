//
// Created by catboy on 2/17/2025.
//

#ifndef GRAPHALKO_VISITORS_HPP
#define GRAPHALKO_VISITORS_HPP

#include "GraphStorage.hpp"
#include "Graph.hpp"

template<typename CurGraph>
class DFSVisitor {
 protected:
  using graph_type = CurGraph;
  using vert_desc = int;
  using edge_desc_iter = graph_type::graph_storage::iterator;
  using edge_desc = std::pair<vert_desc, vert_desc>;

 public:
  void initialize_vertex_DFS(vert_desc top, graph_type &graph) {}

  bool discover_vertex_DFS(vert_desc top, graph_type &graph) { return false; }

  void examine_vertex_DFS(vert_desc top, graph_type &graph) {}

  void start_vertex(vert_desc top, graph_type &graph) {}

  void examine_edge_DFS(edge_desc edge, edge_desc_iter iter, graph_type &graph) {}

  bool tree_edge_DFS(edge_desc edge, edge_desc_iter iter, graph_type &graph) { return false; }

  void back_edge(edge_desc edge, edge_desc_iter iter, graph_type &graph) {}

  void forward_or_cross_edge(edge_desc edge, edge_desc_iter iter, graph_type &graph) {}

  void finish_vertex_DFS(vert_desc top, graph_type &graph) {}

  void DFSVisitFinishVertex(vert_desc top, graph_type &graph) {}

  bool finish_edge(edge_desc edge, edge_desc_iter iter, graph_type &graph) {
    return false;
  }

};

template<typename CurGraph>
class BFSVisitor {
 protected:
  using graph_type = CurGraph;
  using vert_desc = int;
  using edge_desc_iter = graph_type::graph_storage::iterator;
  using edge_desc = std::pair<vert_desc, vert_desc>;

 public:
  //using BFS
  void initialize_vertex_BFS(vert_desc top, graph_type &graph) {}

  bool discover_vertex_BFS(vert_desc top, graph_type &graph) { return false; }

  void examine_vertex_BFS(vert_desc top, graph_type &graph) {}

  void examine_edge_BFS(edge_desc edge, edge_desc_iter iter, graph_type &graph) {}

  void tree_edge_BFS(edge_desc edge, edge_desc_iter iter, graph_type &graph) {}

  void non_tree_edge(edge_desc edge, edge_desc_iter iter, graph_type &graph) {}

  void gray_target(vert_desc top, graph_type &graph) {}

  void black_target(vert_desc top, graph_type &graph) {}

  void finish_vertex_BFS(vert_desc top, graph_type &graph) {}
};

template<typename CurGraph>
class DejkstraVisitor {
 protected:
  using graph_type = CurGraph;
  using vert_desc = int;
  using edge_desc_iter = graph_type::graph_storage::iterator;
  using edge_desc = std::pair<vert_desc, vert_desc>;
  int begin;

 public:
  DejkstraVisitor() = default;
  DejkstraVisitor(int begin) : begin(begin) {};

  void initialize_vertex_Dejkstra(vert_desc top, graph_type &graph) {}

  bool discover_vertex_Dejkstra(vert_desc top, graph_type &graph) { return false; }

  void examine_vertex_Dejkstra(vert_desc top, graph_type &graph) {}

  void examine_edge_Dejkstra(edge_desc edge, edge_desc_iter iter, graph_type &graph) {}

  void edge_relaxed(edge_desc edge, edge_desc_iter iter, graph_type &graph) {}

  void edge_not_relaxed(edge_desc edge, edge_desc_iter iter, graph_type &graph) {}

  void finish_vertex_Dejkstra(vert_desc top, graph_type &graph) {}

  void Dejkstra(int begin_top, CurGraph &graph);
};

#endif //GRAPHALKO_VISITORS_HPP
