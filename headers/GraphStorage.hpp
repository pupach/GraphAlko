//
// Created by catboy on 2/5/2025.
//

#ifndef GRAPHALKO_GRAPHSTORAGE_HPP
#define GRAPHALKO_GRAPHSTORAGE_HPP
#include<iostream>
#include<vector>
#include<iterator>
#include<deque>
#include "Edges.hpp"
#include "iterators.hpp"

template<typename CurEdges>
class GraphStorage {
 protected:
  std::vector<int> color;
  std::vector<int> deep;
  std::vector<int> predecessor;

 public:
  using weight_type = CurEdges::value_type;
  using const_iterator = int *;
  using iterator = int *;
  using const_reverse_iterator = std::reverse_iterator<int *>;
  using reverse_iterator = std::reverse_iterator<int *>;

  bool orientation = false;

  explicit GraphStorage(std::size_t n, bool orientation = false) : orientation(orientation) {};

  [[nodiscard]] virtual std::size_t size() const {
    throw std::out_of_range(nullptr);
  }

  [[nodiscard]] int GetColor(int id) const {
    return color[id];
  }
  int &GetColor(int id) {
    return color[id];
  }
  void DestructColor() {
    color.clear();
  }

  void FillColor(int default_color = 0) {
    while (color.size() != this->size()) {
      color.push_back(default_color);
    }
  }

  void ConstructColor(int default_color = 0) {
    if (color.size() != this->size()) {
      DestructColor();
      FillColor(default_color);
    }
    for (int &i : color) {
      i = default_color;
    }
  }

  [[nodiscard]] int GetDeep(int id) const {
    return deep[id];
  }
  int &GetDeep(int id) {
    return deep[id];
  }
  void DestructDeep() {
    deep.clear();
  }

  void FillDeep(int default_color = INT_MAXIMUS) {
    while (deep.size() != this->size()) {
      deep.push_back(default_color);
    }
  }

  void ConstructDeep(int default_color = INT_MAXIMUS) {
    if (deep.size() != this->size()) {
      DestructDeep();
      FillDeep(default_color);
    }
  }

  [[nodiscard]] int GetPredecessor(int id) const {
    return predecessor[id];
  }

  int &GetPredecessor(int id) {
    return predecessor[id];
  }
  void DestructPredecessor() {
    predecessor.clear();
  }

  void FillPredecessor(int default_color = 0) {
    while (predecessor.size() != this->size()) {
      predecessor.push_back(default_color);
    }
  }

  void ConstructPredecessor(int default_color = 0) {
    if (predecessor.size() != this->size()) {
      DestructPredecessor();
      FillPredecessor(default_color);
    }
  }

  iterator BeginEdges(int id);

  iterator EndEdges(int id);

  int GetIndexVertex(iterator iter);

  weight_type GetWeightFromIter(iterator iter);

  int GetFlow(iterator iter) const;
  int &GetFlow(iterator iter);

  template<typename... Args>
  void AddEdge(int &f_top, int &s_top, Args &&... construct_args);
};

template<typename CurEdges>
class GraphStorageTopsEdges : public GraphStorage<CurEdges> {
  static_assert(std::is_base_of_v<Edges_TopsEdges<typename CurEdges::value_type>, CurEdges>);
 protected:
  using edges = std::vector<CurEdges>;
  std::vector<edges> edges_of_tops;

 public:
  using edges_type = CurEdges;
  using weight_type = edges_type::value_type;
  using const_iterator = NearTopIterator_TopEdges<CurEdges, true>;
  using iterator = NearTopIterator_TopEdges<CurEdges, false>;
  using const_reverse_iterator = std::reverse_iterator<NearTopIterator_TopEdges<CurEdges, true>>;
  using reverse_iterator = std::reverse_iterator<NearTopIterator_TopEdges<CurEdges, false>>;
  using GraphStorage<CurEdges>::GetColor;
  using GraphStorage<CurEdges>::GetPredecessor;
  using GraphStorage<CurEdges>::GetDeep;

  explicit GraphStorageTopsEdges(std::size_t n, bool orientation = false) : GraphStorage<CurEdges>(n, orientation),
                                                                            edges_of_tops(n) { std::cout << 1; };

  template<typename... Args>
  std::size_t AddTop(Args &&... construct_args) {
    edges_of_tops.push_back(edges(construct_args...));
    return edges_of_tops.size() - 1;
  }

  template<typename... Args>
  void SetEdge(std::size_t f_top, Args &&... construct_args) {
    edges_of_tops[f_top] = edges(construct_args...);
  }

  template<typename... Args>
  void AddEdge(int f_top, int s_top, Args &&... construct_args) {
    edges_of_tops[f_top].push_back(CurEdges(s_top, construct_args...));
    std::cerr << "AddEdge f_top = " << f_top << "s_top = " << s_top << "\n";
    if (!this->orientation) edges_of_tops[s_top].push_back(CurEdges(f_top, construct_args...));
  }

  iterator BeginEdges(int id) {
    return iterator(edges_of_tops[id].begin());
  }

  iterator EndEdges(int id) {
    return iterator(edges_of_tops[id].end());
  }

  std::vector<std::vector<int>> GetMatrixNear() {
    std::vector<std::vector<int>> to_ret(edges_of_tops.size(), std::vector<int>(edges_of_tops.size(), 0));

    for (std::size_t i = 0; i < edges_of_tops.size(); i++) {
      for (std::size_t j = 0; j < edges_of_tops[i].size(); j++) {
        to_ret[i][edges_of_tops[i][j].where] = GetWeightFromIter(iterator(edges_of_tops[i].begin() + j));
      }
    }

    return to_ret;
  }

  [[nodiscard]] virtual std::size_t size() const {
    return edges_of_tops.size();
  }

  int GetIndexVertex(iterator iter) {
    std::cerr << "GetIndexVertex ret = " << (*iter).where << "\n";
    return (*iter).where;
  }

  weight_type GetWeightFromIter(iterator iter) {
    if constexpr (std::is_base_of_v<EdgesWeight_TopsEdges<weight_type>, edges_type>) {
      return (*iter).weight;
    } else {
      return 1;
    }
  }

  weight_type GetWeight(int from, int to) {
    if constexpr (std::is_base_of_v<EdgesWeight_TopsEdges<weight_type>, edges_type>) {
      for (std::size_t i = 0; i < this->edges_of_tops[from].size(); i++) {
        if (this->edges_of_tops[from][i].where == to) return this->edges_of_tops[from][i].weight;
      }
      return weight_type();
    } else {
      for (std::size_t i = 0; i < this->edges_of_tops[from].size(); i++) {
        if (this->edges_of_tops[from][i].where == to) return 1;
      }
      return 1;
    }
  }

  int &GetColor(iterator iter) {
    return this->color[GetIndexVertex(iter)];
  }

  int &GetPredecessor(iterator iter) {
    return this->predecessor[GetIndexVertex(iter)];
  }

  int &GetDeep(iterator iter) {
    return this->deep[GetIndexVertex(iter)];
  }

  void PrintStorage() {
    for (int i = 0; i < edges_of_tops.size(); i++) {
      std::cerr << i << " : ";
      for (int j = 0; j < edges_of_tops[i].size(); j++) {
        std::cerr << edges_of_tops[i][j].where << " ";
      }
      std::cerr << "\n";
    }
  }
};

//ХУЙНЯ КАКАЯ ТО!!!!!!!!!
template<typename CurEdges>
class FlowNetworkStorageTopsEdges : public GraphStorageTopsEdges<CurEdges> {
 public:
  using base = GraphStorageTopsEdges<CurEdges>;
  using base::GraphStorageTopsEdges;

  int GetFlow(base::iterator iter) const {
    return iter->flow;
  }
  int &GetFlow(base::iterator iter) {
    return iter->flow;
  }

  int &GetFlow(int from, int to) {
    std::cerr << "GetFlow from = " << from << "to = " << to << "\n";
    for (std::size_t i = 0; i < this->edges_of_tops[from].size(); i++) {
      if (this->edges_of_tops[from][i].where == to) return this->edges_of_tops[from][i].flow;
    }
  }

  template<typename... Args>
  void AddEdge(int f_top, int s_top, Args &&... construct_args) {
    this->edges_of_tops[f_top].push_back(CurEdges(s_top, construct_args...));
    std::cerr << "AddEdge f_top = " << f_top << "s_top = " << s_top << "\n";
    if (!this->orientation) {
      this->edges_of_tops[s_top].push_back(CurEdges(f_top, construct_args...));
    } else {
      this->edges_of_tops[s_top].push_back(CurEdges(f_top, 0));
    }
  }

  void PrintStorage() {
    for (int i = 0; i < this->edges_of_tops.size(); i++) {
      std::cerr << i << " : ";
      for (int j = 0; j < this->edges_of_tops[i].size(); j++) {
        std::cerr << this->edges_of_tops[i][j].where << "-" << this->edges_of_tops[i][j].weight << " / "
                  << this->edges_of_tops[i][j].flow << "\n";
      }
      std::cerr << "\n";
    }
  }
};

template<typename CurEdges>
class GraphStorageMatrixNear : public GraphStorage<CurEdges> {
  static_assert(std::is_base_of_v<EdgesWeight_MatrixNear<typename CurEdges::value_type>, CurEdges>);

 protected:
  using edges = std::vector<CurEdges>;
  std::vector<edges> edges_of_tops;

 public:
  using edges_type = CurEdges;
  using weight_type = edges_type::value_type;
  using const_iterator = NearTopIterator_NearMatrix<CurEdges, true>;
  using iterator = NearTopIterator_NearMatrix<CurEdges, false>;
  using const_reverse_iterator = std::reverse_iterator<NearTopIterator_NearMatrix<CurEdges, true>>;
  using reverse_iterator = std::reverse_iterator<NearTopIterator_NearMatrix<CurEdges, false>>;
  using GraphStorage<CurEdges>::GetColor;
  using GraphStorage<CurEdges>::GetPredecessor;
  using GraphStorage<CurEdges>::GetDeep;

  explicit GraphStorageMatrixNear(std::size_t n, bool orientation = false) : GraphStorage<CurEdges>(n, orientation),
                                                                             edges_of_tops(n,
                                                                                           edges(n + 1,
                                                                                                 edges_type(
                                                                                                     POISON_VAL_ID_VERT,
                                                                                                     weight_type()))) {
    for (std::size_t j = 0; j < n; j++) {
      edges_of_tops[j][n] = edges_type(INT_MAXIMUS, weight_type());
    }
  };

  void AddTop(std::vector<edges> &&edg, std::vector<edges> &&obrat = {}) {
    if (!this->orientation) {
      for (auto i = 0; i < edges_of_tops.size(); i++) {
        edges_of_tops[i].pop_back();
        edges_of_tops[i].push_back(edg[i]);
        edges_of_tops[i].push_back(CurEdges(1));
      }
      edg.push_back(1);
      edges_of_tops.push_back(edg);
    } else {
      for (auto i = 0; i < edges_of_tops.size(); i++) {
        edges_of_tops[i].pop_back();
        edges_of_tops[i].push_back(obrat[i]);
        edges_of_tops[i].push_back(1);
      }
      edg.push_back(1);
      edges_of_tops.push_back(edg);
    }
  }

  void AddEdge(int f_top, int s_top, weight_type weight = weight_type(1)) {
    edges_of_tops[f_top][s_top] = edges_type(s_top, weight);
    if (!this->orientation) {
      edges_of_tops[s_top][f_top] = edges_type(f_top, weight);
    }
  }

  template<typename... Args>
  void AddEdge(int f_top, int s_top, Args &&... construct_args) {
    edges_of_tops[f_top][s_top] = edges_type(s_top, construct_args...);
    if (!this->orientation) {
      edges_of_tops[s_top][f_top] = edges_type(f_top, construct_args...);
    }
  }

  iterator BeginEdges(int id) {
    auto i = edges_of_tops[id].begin();
    while (i->where == POISON_VAL_ID_VERT) i++; // ошибка не 0

    return iterator(i);
  }

  int GetIndexVertex(iterator iter) {
    std::cerr << "GetIndexVertex = " << (*iter).where << "\n";
    return (*iter).where;
  }

  weight_type GetWeightFromIter(iterator iter) {
    return (*iter).weight;
  }
  weight_type GetWeight(int from, int to) {
    return this->edges_of_tops[from][to].weight;
  }

  iterator EndEdges(int id) {
    auto i = edges_of_tops[id].end() - 1;

    return iterator(i);
  }

  std::vector<std::vector<int>> GetMatrixNear() {
    std::vector<std::vector<int>> to_ret(edges_of_tops.size(), std::vector<int>(edges_of_tops.size(), 0));

    for (std::size_t i = 0; i < edges_of_tops.size(); i++) {
      for (std::size_t j = 0; j < edges_of_tops.size(); j++) {
        to_ret[i][j] = GetWeightFromIter(iterator(edges_of_tops[i].begin() + j));
      }
    }

    return to_ret;
  }

  virtual std::size_t size() const {
    return edges_of_tops.size();
  }

  int &GetColor(iterator iter) {
    return this->color[GetIndexVertex(iter)];
  }

  int &GetPredecessor(iterator iter) {
    return this->predecessor[GetIndexVertex(iter)];
  }

  int &GetDeep(iterator iter) {
    return this->deep[GetIndexVertex(iter)];
  }

  void PrintStorage() {
    for (int i = 0; i < edges_of_tops.size(); i++) {
      std::cerr << i << " : ";
      for (int j = 0; j < edges_of_tops[i].size(); j++) {
        std::cerr << edges_of_tops[i][j].weight << "/" << edges_of_tops[i][j].where << "  ";
      }
      std::cerr << "\n";
    }
  }
};

//ХУЙНЯ КАКАЯ ТО!!!!!!!!!
template<typename CurEdges>
class FlowNetworkStorageMatrixNear : public GraphStorageMatrixNear<CurEdges> {
 public:
  using base = GraphStorageMatrixNear<CurEdges>;
  using base::GraphStorageMatrixNear;

  int GetFlow(base::iterator iter) const {
    return iter->flow;
  }
  int &GetFlow(base::iterator iter) {
    return iter->flow;
  }

  int &GetFlow(int from, int to) {
    return this->edges_of_tops[from][to].flow;
  }

  void AddEdge(int f_top, int s_top, base::weight_type weight = base::weight_type(1)) {
    this->edges_of_tops[f_top][s_top] = typename base::edges_type(s_top, weight);
    if (!this->orientation) {
      this->edges_of_tops[s_top][f_top] = typename base::edges_type(f_top, weight);
    } else {
      this->edges_of_tops[s_top][f_top] = CurEdges(f_top, typename base::weight_type(0));
    }
  }

  template<typename... Args>
  void AddEdge(int f_top, int s_top, Args &&... construct_args) {
    this->edges_of_tops[f_top][s_top] = typename base::edges_type(s_top, construct_args...);
    if (!this->orientation) {
      this->edges_of_tops[s_top][f_top] = typename base::edges_type(f_top, construct_args...);
    } else {
      this->edges_of_tops[s_top][f_top] = CurEdges(f_top, 0);
    }
  }
};
#endif //GRAPHALKO_GRAPHSTORAGE_HPP
