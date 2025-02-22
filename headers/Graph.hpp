//
// Created by catboy on 2/17/2025.
//

#ifndef GRAPHALKO_GRAPH_HPP
#define GRAPHALKO_GRAPH_HPP

#include<iostream>
#include<vector>
#include<iterator>
#include<deque>
#include<queue>
#include<cmath>

#include "GraphStorage.hpp"
/*
template<typename CurGraphStorage, std::enable_if_t<std::is_base_of_v<GraphStorage<typename CurGraphStorage::edges_type>, CurGraphStorage>, bool> = true>
class Graph;
*/
#include "Visitors.hpp"

template<typename CurGraphStorage>
class Graph {
 protected:
  using edge = std::pair<int, int>;
  std::deque<edge> bfs_deq;
  CurGraphStorage storage;

  //GraphStorage storage;

 public:
  using graph_storage = CurGraphStorage;
  using edges_type = typename graph_storage::edges_type;
  using weight_type = typename graph_storage::weight_type;
  using iterator = typename graph_storage::iterator;;

  Graph() : storage(0) {
    std::cout << 1;
  }

  explicit Graph<CurGraphStorage>(std::size_t amount_top, bool orientation = false) : storage(amount_top,
                                                                                              orientation) {}

  void PushQeueuBFS(const edge &elem) {
    bfs_deq.push_back(elem);
  }

  weight_type GetWeightFromIter(iterator iter) {
    return storage.GetWeightFromIter(iter);
  }

  int GetDeep(int id) {
    return storage.GetDeep(id);
  }

  int &GetColor(int id) {
    return storage.GetColor(id);
  }

  int &GetFlow(int from, int to) {
    return storage.GetFlow(from, to);
  }

  std::vector<std::vector<int>> GetMatrixNear() {
    return storage.GetMatrixNear();
  }

  void SetWeight(int from, int to, weight_type weight) {
    return storage.GetWeight(from, to) = weight;
  }

  weight_type GetWeight(int from, int to) {
    return storage.GetWeight(from, to);
  }

  void ConstructPredecessor(int default_color = 0) {
    storage.ConstructPredecessor(default_color);
  }

  void ConstructColor(int default_color = 0) {
    storage.ConstructColor(default_color);
  }

  void ConstructDeep(int default_color = INT_MAXIMUS) {
    storage.ConstructDeep(default_color);
  }

  int &GetPredecessor(int id) {
    return storage.GetPredecessor();
  }

  std::size_t size() {
    return storage.size();
  }

  void PrintGraph() {
    std::cerr << "PrintGraph begin\n";
    storage.PrintStorage();
    std::cerr << "PrintGraph end\n";
  }

  void foo();
  template<typename... Args>
  void AddEdge(int f, int s, Args &&... construct_args);

  template<typename CurDFSVisitor>
  void DFS(int begin_top, CurDFSVisitor &visitor);

  template<typename CurDFSVisitor>
  void DFSRecr(int begin_top, CurDFSVisitor &visitor);

  template<typename CurBFSVisitor>
  void BFS(int begin_top, CurBFSVisitor &visitor);

  template<typename CurBFSVisitor>
  void BFSRecr(int begin_top, CurBFSVisitor &visitor);

  template<typename CurBFSVisitor>
  void Dejkstra(int begin_top, CurBFSVisitor &graph);
};

#include "../tpp/Graph.cpp"
#endif //GRAPHALKO_GRAPH_HPP
