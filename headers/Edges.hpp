/**
 * @file Edges.hpp
 * @brief Определения разных типов ребер графа.
 *
 * Данный файл содержит базовые определения структур для представления ребер графа, а также расширенные
 * структуры для работы с весами и потоками, для графов, представленных списком смежности (TopsEdges), и для матричных представлений (MatrixNear).
 */

#ifndef GRAPHALKO_EDGES_HPP
#define GRAPHALKO_EDGES_HPP

#include <iostream>
#include <vector>
#include <iterator>
#include <deque>

/**
 * @brief Максимальное значение которое обозначает вес равный бесконечности(также используется для обозначения конца итератора).
 * см @c GetEnd()
 */
const int INT_MAXIMUS = 1000000;

/**
 * @brief Специальное значение для обозначения недопустимого идентификатора вершины.
 */
const int POISON_VAL_ID_VERT = -1;

/**
 * @brief Базовая структура ребра.
 *
 * Шаблонная структура @c Edges служит базовым классом для всех типов ребер (но не должна напрямую нигде создаваться)
 *
 * @tparam T Тип значения, который может представлять вес или другой параметр ребра.
 */
template<typename T>
struct Edges {
 public:
  /// Тип веса ребра.
  using value_type = T;

  Edges() = default;
};

/**
 * @brief Тип ребра для графов представленных списками смежности ребер(не имеет веса).
 *
 * Шаблонная структура наследуется от @c Edges и предназначена для хранения
 * идентификатора вершины, в которую направлено ребро.
 *
 * @tparam T Тип значения, используемый в базовой структуре.
 */
template<typename T>
struct Edges_TopsEdges : public Edges<T> {
 public:
  /// Идентификатор вершины, в которую направлено ребро.
  int where = POISON_VAL_ID_VERT;

  Edges_TopsEdges() = default;

  /**
   * @brief Конструктор
   *
   * @param[in] m Идентификатор вершины.
   */
  explicit Edges_TopsEdges(int m) : where(m) {};
};

/**
 * @brief Тип ребра с весом для графов представленных списками смежности ребер
 *
 * Шаблонная структура наследуется от @c Edges_TopsEdges и добавляет хранение
 * веса ребра.
 *
 * @tparam T Тип веса ребра
 */
template<typename T>
struct EdgesWeight_TopsEdges : public Edges_TopsEdges<T> {
 public:

  EdgesWeight_TopsEdges() = default;

  /**
   * @brief Конструктор, инициализирующий идентификатор вершины и вес ребра.
   *
   * @param vert Идентификатор вершины.
   * @param m Вес ребра.
   */
  EdgesWeight_TopsEdges(int vert, T m) : Edges_TopsEdges<T>(vert), weight(m) {};

  /**
   * @brief Шаблонный конструктор для создания ребра с весом.
   *
   * @tparam Args Типы параметров для конструктора веса.
   * @param vert Идентификатор вершины.
   * @param construct_args Аргументы для создания значения веса.
   */
  template<typename... Args>
  explicit EdgesWeight_TopsEdges(int vert, Args... construct_args)
      : Edges_TopsEdges<T>(vert), weight(construct_args...) {};

  /// Вес ребра.
  T weight;
};

/**
 * @brief Тип ребра для графов представленных списками смежности ребер добавляющий хранения потока
 *
 * Шаблонная структура наследуется от @c EdgesWeight_TopsEdges и добавляет хранение
 * потока.
 *
 * @tparam T Тип потока ребра.
 */
template<typename T>
struct EdgesFlow_TopsEdges : public EdgesWeight_TopsEdges<T> {
 public:
  EdgesFlow_TopsEdges() = default;

  /**
   * @с EdgesWeight_TopsEdges(int vert, T m)
   */
  EdgesFlow_TopsEdges(int vert, T m) : EdgesWeight_TopsEdges<T>(vert, m) {};

/**
 * @с explicit EdgesWeight_TopsEdges(int vert, Args... construct_args)
   */
  template<typename... Args>
  explicit EdgesFlow_TopsEdges(int vert, Args... construct_args)
      : EdgesWeight_TopsEdges<T>(vert, construct_args...) {};

  template<typename... Args>
  EdgesFlow_TopsEdges(int rev, int vert, Args... construct_args)
      : rev(rev), EdgesWeight_TopsEdges<T>(vert, construct_args...) {};

  /// Поток, проходящий по ребру.
  T flow = 0;

  int rev = POISON_VAL_ID_VERT;
};

/**
 * @brief Тип ребра с весом для представления графа матрицей смежности вершин(сразу имеет вес)
 *
 * Шаблонная структура наследуется от @c Edges и предназначена для хранения ребер
 * в графе, представленных в виде матрицы смежности вершин.
 *
 * @tparam T Тип веса и потока ребра.
 */
template<typename T>
struct EdgesWeight_MatrixNear : public Edges<T> {
 public:

  EdgesWeight_MatrixNear() = default;

  /**
   * @brief Конструктор, инициализирующий идентификатор вершины и вес ребра.
   *
   * @param vert Идентификатор вершины куда направленно ребро.
   * @param m Вес ребра.
   */
  explicit EdgesWeight_MatrixNear(int vert, T m) : where(vert), weight(m) {
    std::cerr << "constuct EdgesWeight_MatrixNear(int vert, T m) : where(vert), weight(m)\n";
  };

  template<typename... Args>
  explicit EdgesWeight_MatrixNear(int vert, Args... construct_args)
      : where(vert), weight(construct_args...) {};

  /// Вес ребра.
  T weight;
  /// Идентификатор вершины, в которую направленно ребро
  int where = POISON_VAL_ID_VERT;
};

/**
 * @brief Тип ребра с потоками для представления графа матрицей смежности вершин
 *
 * Шаблонная структура наследуется от @c EdgesWeight_MatrixNear и добавляет хранение потока(вес становится вместимостью)
 *
 * @tparam T Тип веса и потока ребра.
 */
template<typename T>
struct EdgesFlow_MatrixNear : public EdgesWeight_MatrixNear<T> {
 public:
  /// Поток, проходящий по ребру.
  T flow = 0;
  int rev = POISON_VAL_ID_VERT;

  EdgesFlow_MatrixNear() = default;

  /**
   * @с EdgesFlow_TopsEdges()
   */
  explicit EdgesFlow_MatrixNear(T m) : EdgesWeight_MatrixNear<T>(m) {};

  /**
   * @с EdgesFlow_TopsEdges(int vert, T m)
   */
  explicit EdgesFlow_MatrixNear(int vert, T m) : EdgesWeight_MatrixNear<T>(vert, m) {}

  /**
   * @brief Конструктор копирования.
   */
  EdgesFlow_MatrixNear(const EdgesFlow_MatrixNear<T> &matr) {
    this->weight = matr.weight;
    this->where = matr.where;
    this->flow = matr.flow;
    this->rev = matr.rev;
  };

  /**
   * @brief Конструктор перемещения.
   */
  EdgesFlow_MatrixNear(EdgesFlow_MatrixNear<T> &&matr) {
    this->weight = matr.weight;
    this->where = matr.where;
    this->flow = matr.flow;
    this->rev = matr.rev;
  };
  /**
   * @brief Оператор copy assigment.
   */
  EdgesFlow_MatrixNear &operator=(const EdgesFlow_MatrixNear<T> &matr) {
    this->weight = matr.weight;
    this->where = matr.where;
    this->flow = matr.flow;
    this->rev = matr.rev;
    return *this;
  }

  /**
   * @brief Оператор move assigment.
   */
  EdgesFlow_MatrixNear &operator=(EdgesFlow_MatrixNear<T> &&matr) {
    this->weight = matr.weight;
    this->where = matr.where;
    this->flow = matr.flow;
    this->rev = matr.rev;
    return *this;
  }

  template<typename... Args>
  explicit EdgesFlow_MatrixNear(Args... construct_args)
      : EdgesWeight_MatrixNear<T>(construct_args...) {};


  template<typename... Args>
  explicit EdgesFlow_MatrixNear(int vert, Args... construct_args)
      : EdgesWeight_MatrixNear<T>(vert, construct_args...) {};
};

#endif // GRAPHALKO_EDGES_HPP