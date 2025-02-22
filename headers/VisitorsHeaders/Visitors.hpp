/**
 * @file Visitors.hpp
 * @brief Определения классов Visitor для обхода графа.
 *
 * Данный файл содержит определения классов DFSVisitor, BFSVisitor и DejkstraVisitor,
 * для DFS, BFD and Dejkstra влгоритмов соответсвенно.
 * Они представляют из себя набор методов, которые вызываются в определенные моменты программы
 */

#ifndef GRAPHALKO_VISITORS_HPP
#define GRAPHALKO_VISITORS_HPP

#include "GraphStorage.hpp"
#include "Graph.hpp"

/**
 * @brief Visitor для обхода графа в глубину (DFS).
 *
 * Шаблонный класс DFSVisitor определяет интерфейс методов, вызываемых при обходе графа в глубину.
 * Пользователь может переопределить данные методы для реализации производных методов
 *
 * @tparam CurGraph Тип графа, который обрабатывается Visitor
 */
template<typename CurGraph>
class DFSVisitor {
 protected:
  /// Тип графа
  using graph_type = CurGraph;
  /// Тип дескриптора вершины
  using vert_desc = int;
  /// Тип итератора по ребрам
  using edge_desc_iter = typename graph_type::graph_storage::iterator;
  /// Пара, описывающая ребро (начальная и конечная вершина)
  using edge_desc = std::pair<vert_desc, vert_desc>;

 public:
  /**
   * @brief Вызывается для каждой вершины перед началом DFS.
   *
   * @param top Индекс вершины.
   * @param graph Ссылка на граф.
   */
  void initialize_vertex_DFS(vert_desc top, graph_type &graph) {}

  /**
   * @brief Вызывается, когда вершина впервые обнаружена.
   *
   * @param top Индекс вершины.
   * @param graph Ссылка на граф.
   * @return Если возвращено true, обход текущий вершины прерывается.
   */
  bool discover_vertex_DFS(vert_desc top, graph_type &graph) { return false; }

  /**
   * @brief Обработка Вызывается когда вершина обрабатывается
   *
   * @param top Индекс вершины.
   * @param graph Ссылка на граф.
   */
  void examine_vertex_DFS(vert_desc top, graph_type &graph) {}

  /**
   * @brief Вызывается при старте обхода в начальной вершине
   *
   * @param top Индекс начальной вершины.
   * @param graph Ссылка на граф.
   */
  void start_vertex(vert_desc top, graph_type &graph) {}

  /**
   * @brief Вызывается для каждого ребра из обнаруженной вершины.
   *
   * @param edge Пара вершин, определяющая ребро.
   * @param iter Итератор, указывающий на текущее ребро.
   * @param graph Ссылка на граф.
   */
  void examine_edge_DFS(edge_desc edge, edge_desc_iter iter, graph_type &graph) {}

  /**
   * @brief Вызывается для прямого ребра в дереве обхода(оставном)
   *
   * @param edge Пара вершин, определяющая ребро.
   * @param iter Итератор, указывающий на текущее ребро.
   * @param graph Ссылка на граф.
   */
  bool tree_edge_DFS(edge_desc edge, edge_desc_iter iter, graph_type &graph) { return false; }


  /**
   * @brief Вызывается для обратных ребер, в дереве обхода
   *
   * @param edge Пара вершин, определяющая ребро.
   * @param iter Итератор, указывающий на текущее ребро.
   * @param graph Ссылка на граф.
   */
  void back_edge(edge_desc edge, edge_desc_iter iter, graph_type &graph) {}

  /**
   * @brief Вызывается, когда ребро является "поперечным" в дереве обхода
   *
   * @param top Индекс вершины.
   * @param graph Ссылка на граф.
   */
  void forward_or_cross_edge(edge_desc edge, edge_desc_iter iter, graph_type &graph) {}

  /**
   * @brief Вызывается когда все исходящие ребра уже обработаны, перед выходом из текущей вершины
   *
   * @param top Индекс вершины.
   * @param graph Ссылка на граф.
   */
  void finish_vertex_DFS(vert_desc top, graph_type &graph) {}


  void DFSVisitFinishVertex(vert_desc top, graph_type &graph) {}

  /**
   * @brief Вызывается при завершении обработки ребра(перед обратным проходом по нему)
   *
   * @param edge Пара вершин, определяющая ребро.
   * @param iter Итератор, указывающий на текущее ребро.
   * @param graph Ссылка на граф.
   * @return Если возвращено true, обработка ребра считается успешной.
   */
  bool finish_edge(edge_desc edge, edge_desc_iter iter, graph_type &graph) {
    return false;
  }
};

/**
 * @brief Visitor для обхода графа в ширину (BFS).
 *
 * Шаблонный класс BFSVisitor определяет интерфейс методов, вызываемых при обходе графа в глубину.
 * Пользователь может переопределить данные методы для реализации производных методов
 *
 * @tparam CurGraph Тип графа, с которым работает посетитель.
 */
template<typename CurGraph>
class BFSVisitor {
 protected:
  /// Тип графа
  using graph_type = CurGraph;
  /// Тип дескриптора вершины
  using vert_desc = int;
  /// Тип итератора по ребрам графа
  using edge_desc_iter = typename graph_type::graph_storage::iterator;
  /// Пара, описывающая ребро (начальная и конечная вершина)
  using edge_desc = std::pair<vert_desc, vert_desc>;

 public:
  /**
   * @brief Вызывается для каждой вершины перед началом DBFS.
   *
   * @param top Индекс вершины.
   * @param graph Ссылка на граф.
   */
  void initialize_vertex_BFS(vert_desc top, graph_type &graph) {}

  /**
   * @brief Вызывается, когда вершина впервые обнаружена.
   *
   * @param top Индекс вершины.
   * @param graph Ссылка на граф.
   * @return Если возвращено true, обход текущий вершины прерывается.
   */
  bool discover_vertex_BFS(vert_desc top, graph_type &graph) { return false; }

  /**
   * @brief Обработка Вызывается когда вершина обрабатывается
   *
   * @param top Индекс вершины.
   * @param graph Ссылка на граф.
   */
  void examine_vertex_BFS(vert_desc top, graph_type &graph) {}

  /**
   * @brief Вызывается для каждого ребра из обнаруженной вершины.
   *
   * @param edge Пара вершин, определяющая ребро.
   * @param iter Итератор, указывающий на текущее ребро.
   * @param graph Ссылка на граф.
   */
  void examine_edge_BFS(edge_desc edge, edge_desc_iter iter, graph_type &graph) {}

  /**
   * @brief Обработка "деревянного" ребра.
   *
   * Вызывается, когда ребро является частью дерева обхода.
   *
   * @param edge Пара вершин, определяющая ребро.
   * @param iter Итератор, указывающий на текущее ребро.
   * @param graph Ссылка на граф.
   * @return Если возвращено true, дальнейшая обработка ребра прерывается.
   */
  void tree_edge_BFS(edge_desc edge, edge_desc_iter iter, graph_type &graph) {}

  /**
   * @brief Вызывается, когда ребро не является частью дерева обхода.
   *
   * @param edge Пара вершин, определяющая ребро.
   * @param iter Итератор, указывающий на текущее ребро.
   * @param graph Ссылка на граф.
   * @return Если возвращено true, дальнейшая обработка ребра прерывается.
   */
  void non_tree_edge(edge_desc edge, edge_desc_iter iter, graph_type &graph) {}

  /**
   * @brief Вызывается, когда вершина в которую ведет ребро окрашено в серый
   *
   * @param edge Пара вершин, определяющая ребро.
   * @param iter Итератор, указывающий на текущее ребро.
   * @param graph Ссылка на граф.
   * @return Если возвращено true, дальнейшая обработка ребра прерывается.
   */
  void gray_target(vert_desc top, graph_type &graph) {}

  /**
   * @brief Вызывается, когда вершина в которую ведет ребро окрашено в черный
   *
   * @param edge Пара вершин, определяющая ребро.
   * @param iter Итератор, указывающий на текущее ребро.
   * @param graph Ссылка на граф.
   * @return Если возвращено true, дальнейшая обработка ребра прерывается.
   */
  void black_target(vert_desc top, graph_type &graph) {}

  /**
   * @brief Вызывается когда все исходящие ребра уже обработаны, перед выходом из текущей вершины
   *
   * @param top Индекс вершины.
   * @param graph Ссылка на граф.
   */
  void finish_vertex_BFS(vert_desc top, graph_type &graph) {}
};

/**
 * @brief Visitor для алгоритма Dejkstra.
 *
 * Шаблонный класс DejkstraVisitor определяет интерфейс методов, вызываемых при обходе графа в глубину.
 * Пользователь может переопределить данные методы для реализации производных методов
 *
 * @tparam CurGraph Тип графа.
 */
template<typename CurGraph>
class DejkstraVisitor {
 protected:
  /// Тип графа
  using graph_type = CurGraph;
  /// Тип дескриптора вершины
  using vert_desc = int;
  /// Тип итератора по ребрам графа
  using edge_desc_iter = typename graph_type::graph_storage::iterator;
  /// Пара, описывающая ребро (начальная и конечная вершина)
  using edge_desc = std::pair<vert_desc, vert_desc>;

  /// Индекс начальной вершины для алгоритма Дейкстры
  int begin;

 public:
  DejkstraVisitor() = default;

  DejkstraVisitor(int begin) : begin(begin) {};

  /**
   * @brief Вызывается для каждой вершины перед началом Dejkstra.
   *
   * @param top Индекс вершины.
   * @param graph Ссылка на граф.
   */
  void initialize_vertex_Dejkstra(vert_desc top, graph_type &graph) {}

  /**
   * @brief Обнаружение вершины во время алгоритма Дейкстры.
   *
   * @param top Индекс вершины.
   * @param graph Ссылка на граф.
   * @return Если возвращено true, дальнейшая обработка прерывается.
   */
  bool discover_vertex_Dejkstra(vert_desc top, graph_type &graph) { return false; }

  /**
   * @brief Обработка Вызывается когда вершина обрабатывается
   *
   * @param top Индекс вершины.
   * @param graph Ссылка на граф.
   */
  void examine_vertex_Dejkstra(vert_desc top, graph_type &graph) {}

  /**
   * @brief Вызывается для каждого ребра из обнаруженной вершины.
   *
   * @param edge Пара вершин, определяющая ребро.
   * @param iter Итератор, указывающий на текущее ребро.
   * @param graph Ссылка на граф.
   */
  void examine_edge_Dejkstra(edge_desc edge, edge_desc_iter iter, graph_type &graph) {}

  /**
   * @brief Вызывается для ребра, для которого удалось улучшить кратчайший путь.
   *
   *
   * @param edge Пара вершин, определяющая ребро.
   * @param iter Итератор, указывающий на текущее ребро.
   * @param graph Ссылка на граф.
   */
  void edge_relaxed(edge_desc edge, edge_desc_iter iter, graph_type &graph) {}

  /**
   * @brief Вызывается для ребра, для которого не удалось улучшить кратчайший путь.
   *
   * @param edge Пара вершин, определяющая ребро.
   * @param iter Итератор, указывающий на текущее ребро.
   * @param graph Ссылка на граф.
   */
  void edge_not_relaxed(edge_desc edge, edge_desc_iter iter, graph_type &graph) {}

  /**
   * @brief Вызывается когда все исходящие ребра уже обработаны, перед выходом из текущей вершины
   *
   * @param top Индекс вершины.
   * @param graph Ссылка на граф.
   */
  void finish_vertex_Dejkstra(vert_desc top, graph_type &graph) {}

  /**
   * @brief Запускает алгоритма Дейкстры.
   *
   * Метод запускает выполнение алгоритма поиска кратчайших путей из заданной начальной вершины.
   *
   * @param begin_top Индекс начальной вершины.
   * @param graph Ссылка на граф.
   */
  void Dejkstra(int begin_top, CurGraph &graph);
};

#endif //GRAPHALKO_VISITORS_HPP