//
// Created by catboy on 2/21/2025.
//

#ifndef GRAPHALKO_EDGES_HPP
#define GRAPHALKO_EDGES_HPP
#include<iostream>
#include<vector>
#include<iterator>
#include<deque>
const int INT_MAXIMUS = 2147483646;
const int POISON_VAL_ID_VERT = -1;

template<typename T>
struct Edges {
 public:
  using value_type = T;

  Edges() = default;
};

template<typename T>
struct Edges_TopsEdges : public Edges<T> {
 public:
  int where = POISON_VAL_ID_VERT;

  Edges_TopsEdges() = default;

  explicit Edges_TopsEdges(int m) : where(m) {};
};

template<typename T>
struct EdgesWeight_TopsEdges : public Edges_TopsEdges<T> {
 public:
  EdgesWeight_TopsEdges() = default;
  EdgesWeight_TopsEdges(int vert, T m) : Edges_TopsEdges<T>(vert), weight(m) {};

  template<typename... Args>
  explicit EdgesWeight_TopsEdges(int vert, Args... construct_args)
      : Edges_TopsEdges<T>(vert), weight(construct_args...) {};

  T weight;
};

template<typename T>
struct EdgesFlow_TopsEdges : public EdgesWeight_TopsEdges<T> {
 public:
  EdgesFlow_TopsEdges() = default;
  EdgesFlow_TopsEdges(int vert, T m) : EdgesWeight_TopsEdges<T>(vert, m) {};

  template<typename... Args>
  explicit EdgesFlow_TopsEdges(int vert, Args... construct_args) : EdgesWeight_TopsEdges<T>(vert, construct_args...) {};

  template<typename... Args>
  EdgesFlow_TopsEdges(int rev, int vert, Args... construct_args)
      : rev(rev), EdgesWeight_TopsEdges<T>(vert, construct_args...) {};

  T flow;
  int rev = POISON_VAL_ID_VERT;
};

template<typename T>
struct EdgesWeight_MatrixNear : public Edges<T> {
 public:
  EdgesWeight_MatrixNear() = default;
  explicit EdgesWeight_MatrixNear(int vert, T m) : where(vert), weight(m) {
    std::cerr << "constuct EdgesWeight_MatrixNear(int vert, T m) : where(vert), weight(m)\n";
  };

  template<typename... Args>
  explicit EdgesWeight_MatrixNear(int vert, Args... construct_args) : where(vert), weight(construct_args...) {};

  T weight;
  int where = POISON_VAL_ID_VERT;
};

template<typename T>
struct EdgesFlow_MatrixNear : public EdgesWeight_MatrixNear<T> {
 public:

  T flow;
  int rev = POISON_VAL_ID_VERT;

  EdgesFlow_MatrixNear() = default;
  explicit EdgesFlow_MatrixNear(T m) : EdgesWeight_MatrixNear<T>(m) {};

  explicit EdgesFlow_MatrixNear(int vert, T m) : EdgesWeight_MatrixNear<T>(vert, m) {}

  EdgesFlow_MatrixNear(const EdgesFlow_MatrixNear<T> &matr) {
    this->weight = matr.weight;
    this->where = matr.where;
    this->flow = matr.flow;
    this->rev = matr.rev;
  };

  EdgesFlow_MatrixNear(EdgesFlow_MatrixNear<T> &&matr) {
    this->weight = matr.weight;
    this->where = matr.where;
    this->flow = matr.flow;
    this->rev = matr.rev;
  };

  EdgesFlow_MatrixNear &operator=(const EdgesFlow_MatrixNear<T> &matr) {
    this->weight = matr.weight;
    this->where = matr.where;
    this->flow = matr.flow;
    this->rev = matr.rev;
    return *this;
  }

  EdgesFlow_MatrixNear &operator=(EdgesFlow_MatrixNear<T> &&matr) {
    this->weight = matr.weight;
    this->where = matr.where;
    this->flow = matr.flow;
    this->rev = matr.rev;
    return *this;
  }

  template<typename... Args>
  explicit EdgesFlow_MatrixNear(Args... construct_args) : EdgesWeight_MatrixNear<T>(construct_args...) {};

  template<typename... Args>
  explicit EdgesFlow_MatrixNear(int vert, Args... construct_args) : EdgesWeight_MatrixNear<T>(vert,
                                                                                              construct_args...) {};

};

#endif //GRAPHALKO_EDGES_HPP
