/**
 * @file GraphStorage.hpp
 * @brief Способы хранения графов
 *
 * Этот файл содержит определения шаблонных классов для хранения графов в виде списка (TopsEdges) и в виде матрицы (MatrixNear).
 * Также представлены специализированные классы для потоковых сетей.
 */

#ifndef GRAPHALKO_GRAPHSTORAGE_HPP
#define GRAPHALKO_GRAPHSTORAGE_HPP

#include <iostream>
#include <vector>
#include <iterator>
#include <deque>
#include "Edges.hpp"
#include "iterators.hpp"

/**
 * @brief Базовый класс для хранения данных графа. Его прямое создание может привести к неопределенным результатам
 *
 * Шаблонный класс GraphStorage предоставляет базовые структуры для хранения цвета вершин, глубины и предков.
 *
 * @tparam CurEdges Тип ребра, используемый в графе.
 */
template<typename CurEdges>
class GraphStorage {
 protected:
  /// Цвета вершин
  std::vector<int> color;
  /// Глубина вершин
  std::vector<int> depth;
  /// Предки для восстановления пути обхода
  std::vector<int> predecessor;

 public:
  /// Тип веса ребра
  using weight_type = typename CurEdges::value_type;
  /// Итераторы для обхода
  using const_iterator = int *;
  using iterator = int *;
  using const_reverse_iterator = std::reverse_iterator<int *>;
  using reverse_iterator = std::reverse_iterator<int *>;

  /// Флаг ориентации графа
  bool orientation = false;

  /**
   * @brief Конструктор с указанием числа вершин и ориентации графа(должен вызываться только из наследников).
   *
   * @param n Число вершин графа.
   * @param orientation Флаг ориентации графа
   */
  explicit GraphStorage(std::size_t n, bool orientation = false) : orientation(orientation) {};

  /**
   * @brief Возвращает количество вершин в графе.
   *
   * Определена для использования в качестве интерфейса. Разрешен вызов только ее перегрузок в наследниках
   *
   * @return Количество вершин.
   * @throws std::out_of_range Так как ее вызов запрещен
   */
  [[nodiscard]] virtual std::size_t size() const {
    std::cerr << "THROWS!!\n";
    throw std::out_of_range(nullptr);
  }

  /**
   * @brief Возвращает цвет вершины по её идентификатору (константная версия).
   *
   * @param id Идентификатор вершины.
   * @return Цвет вершины.
   */
  [[nodiscard]] int GetColor(int id) const {
    return color[id];
  }

  /**
   * @brief Возвращает ссылку на цвет вершины по её идентификатору(для возможности изменения).
   *
   * @param id Идентификатор вершины.
   * @return Ссылка на цвет вершины.
   */
  int &GetColor(int id) {
    return color[id];
  }

  /**
   * @brief Очищает массив цветов, чтобы использовалось меньшее количество памяти
   */
  void DestructColor() {
    color.clear();
  }

  /**
   * @brief Заполняет массив цветов значениями по умолчанию.
   *
   * @param default_color Значение по умолчанию (по умолчанию 0).
   */
  void FillColor(int default_color = 0) {
    while (color.size() != this->size()) {
      color.push_back(default_color);
    }
  }

  /**
   * @brief Конструирует в случае надобности вектор цветов, заполняя его значениями по умолчанию.
   *
   * @param default_color Значение по умолчанию (по умолчанию 0).
   */
  void ConstructColor(int default_color = 0) {
    if (color.size() != this->size()) {
      DestructColor();
      FillColor(default_color);
    } else {
      for (int &i : color) {
        i = default_color;
      }
    }
  }

  /**
   * @brief Возвращает глубину вершины по её идентификатору (константная версия).
   *
   * @param id Идентификатор вершины.
   * @return Глубина вершины.
   */
  [[nodiscard]] int GetDepth(int id) const {
    return depth[id];
  }

  /**
   * @brief Возвращает ссылку на глубину вершины по её идентификатору(для возможности изменения).
   *
   * @param id Идентификатор вершины.
   * @return Ссылка на глубину вершины.
   */
  int &GetDepth(int id) {
    return depth[id];
  }

  /**
   * @brief Очищает массив цветов, чтобы использовалось меньшее количество памяти
   */
  void DestructDepth() {
    depth.clear();
  }
  /**
   * @brief Заполняет массив глубин значениями по умолчанию.
   *
   * @param default_depth Значение по умолчанию (по умолчанию 0).
   */
  void FillDepth(int default_depth = INT_MAXIMUS) {
    while (depth.size() != this->size()) {
      depth.push_back(default_depth);
    }
  }

  /**
   * @brief Конструирует вектор глубин, заполняя его значениями по умолчанию.
   *
   * @param default_depth Значение по умолчанию (по умолчанию INT_MAXIMUS).
   */
  void ConstructDepth(int default_depth = INT_MAXIMUS) {
    if (depth.size() != this->size()) {
      DestructDepth();
      FillDepth(default_depth);
    } else {
      for (int &i : depth) {
        i = default_depth;
      }
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

  void FillPredecessor(int default_value = 0) {
    while (predecessor.size() != this->size()) {
      predecessor.push_back(default_value);
    }
  }

  void ConstructPredecessor(int default_color = 0) {
    if (predecessor.size() != this->size()) {
      DestructPredecessor();
      FillPredecessor(default_color);
    }
  }

  /**
   * @brief Возвращает итератор на начало списка ребер по идентификатору вершины.
   *
   * @param id Идентификатор вершины.
   * @return Итератор на начало списка ребер.
   */
  iterator BeginEdges(int id);

  /**
   * @brief Возвращает итератор на конец списка ребер по идентификатору вершины.
   *
   * @param id Идентификатор вершины.
   * @return Итератор на конец списка ребер.
   */
  iterator EndEdges(int id);

  /**
   * @brief Возвращает индекс вершины в которую идет ребро, на которое указывает итератор.
   *
   * @param iter Итератор по списку ребер.
   * @return Индекс вершины.
   */
  int GetIndexVertex(iterator iter);

  /**
   * @brief Возвращает вес ребра по заданному итератору.
   *
   * @param iter Итератор по списку ребер.
   * @return Вес ребра.
   */
  weight_type GetWeightFromIter(iterator iter);

  /**
   * @brief Возвращает поток ребра по итератору (константная версия).
   *
   * @param iter Итератор по списку ребер.
   * @return Поток ребра.
   */
  weight_type GetFlow(iterator iter) const;

  /**
   * @brief Возвращает ссылку на поток ребра по итератору.
   *
   * @param iter Итератор по списку ребер.
   * @return Ссылка на поток ребра(для возможности изменения).
   */
  weight_type &GetFlow(iterator iter);

  /**
   * @brief Добавляет ребро в граф.
   *
   * Обьявлена только для использования этого класса в качестве единого интерфейса(реализации в этом классе у ФУНКЦИИ НЕ БУДЕТ  )
   *
   * @tparam Args Параметры для конструктора ребра.
   * @param f_top Исходная вершина.
   * @param s_top Конечная вершина.
   * @param construct_args Аргументы для конструктора ребра.
   */
  template<typename... Args>
  void AddEdge(int f_top, int s_top, Args &&... construct_args);
};


/**
 * @brief Хранение графа с помощью списка ребер для каждой вершины.
 *
 * Класс GraphStorageTopsEdges наследуется от GraphStorage. Требует, чтобы тип ребра был наследником
 * Edges_TopsEdges.
 *
 * @tparam CurEdges Тип ребра.
 */
template<typename CurEdges>
class GraphStorageTopsEdges : public GraphStorage<CurEdges> {
  static_assert(std::is_base_of_v<Edges_TopsEdges<typename CurEdges::value_type>, CurEdges>);
 protected:
  using edges = std::vector<CurEdges>;
  /// Вектор Векторов списков ребер для каждой вершины
  std::vector<edges> edges_of_tops;
 public:
  /// Тип ребер
  using edges_type = CurEdges;
  /// Тип веса ребра
  using weight_type = typename edges_type::value_type;
  /// Итератор для обхода ребер вершины
  using const_iterator = NearTopIterator_TopEdges<CurEdges, true>;
  using iterator = NearTopIterator_TopEdges<CurEdges, false>;
  using const_reverse_iterator = std::reverse_iterator<NearTopIterator_TopEdges<CurEdges, true>>;
  using reverse_iterator = std::reverse_iterator<NearTopIterator_TopEdges<CurEdges, false>>;
  using GraphStorage<CurEdges>::GetColor;
  using GraphStorage<CurEdges>::GetPredecessor;
  using GraphStorage<CurEdges>::GetDepth;

  /**
   * @brief Конструктор с числом вершин и флагом ориентации.
   *
   * @param n Число вершин.
   * @param orientation Флаг ориентации (по умолчанию false).
   */
  explicit GraphStorageTopsEdges(std::size_t n, bool orientation = false)
      : GraphStorage<CurEdges>(n, orientation), edges_of_tops(n) { std::cout << 1; };

  /**
   * @brief описание метода см в классе родителе @
   */
  template<typename... Args>
  std::size_t AddTop(Args &&... construct_args) {
    edges_of_tops.push_back(edges(construct_args...));
    return edges_of_tops.size() - 1;
  }

  template<typename... Args>
  void SetEdge(std::size_t f_top, Args &&... construct_args) {
    edges_of_tops[f_top] = edges(construct_args...);
  }

  /**
   * @brief описание метода см в классе выше
   */
  template<typename... Args>
  void AddEdge(int f_top, int s_top, Args &&... construct_args) {
    edges_of_tops[f_top].push_back(CurEdges(s_top, construct_args...));
    if (!this->orientation)
      edges_of_tops[s_top].push_back(CurEdges(f_top, construct_args...));
  }

  /**
   * @brief описание метода см в классе выше.
   */
  iterator BeginEdges(int id) {
    return iterator(edges_of_tops[id].begin());
  }

  /**
   * @brief описание метода см в классе выше
   */
  iterator EndEdges(int id) {
    return iterator(edges_of_tops[id].end());
  }

  /**
   * @brief Возвращает матрицу смежности, представляющую граф.
   *
   * Конвертирует метод хранения в виде списка смежных ребер в матрицу смежности
   *
   * @return Матрица смежности, где элемент [i][j] равен весу ребра между вершинами i и j.
   */
  std::vector<std::vector<weight_type>> GetMatrixNear() {
    std::vector<std::vector<weight_type>> to_ret(edges_of_tops.size(), std::vector<weight_type>(edges_of_tops.size(), 0));
    for (std::size_t i = 0; i < edges_of_tops.size(); i++) {
      for (std::size_t j = 0; j < edges_of_tops[i].size(); j++) {
        to_ret[i][edges_of_tops[i][j].where] = GetWeightFromIter(iterator(edges_of_tops[i].begin() + j));
      }
    }
    return to_ret;
  }

  /**
   * @brief описание метода см в классе выше
   */
  [[nodiscard]] virtual std::size_t size() const {
    return edges_of_tops.size();
  }

  /**
   * @brief описание метода см в классе выше
   */
  int GetIndexVertex(iterator iter) {
    return (*iter).where;
  }
  /**
   * @brief описание метода см в классе выше
   * Если тип веса - bool то вес ребра равен одному(тк ребро существует) иначе  возвращает его вес
   */
  weight_type GetWeightFromIter(iterator iter) {
    if constexpr (std::is_base_of_v<EdgesWeight_TopsEdges<weight_type>, edges_type>)
      return (*iter).weight;
    else
      return 1;
  }

  /**
   * @brief Возвращает вес ребра между двумя вершинами.
   *
   *Если тип веса - bool то вес ребра равен одному(тк ребро существует) иначе  возвращает его вес
   *
   * @param from Индекс исходной вершины.
   * @param to Индекс конечной вершины.
   * @return Вес ребра.
   */
  weight_type GetWeight(int from, int to) {
    if constexpr (std::is_base_of_v<EdgesWeight_TopsEdges<weight_type>, edges_type>) {
      for (std::size_t i = 0; i < this->edges_of_tops[from].size(); i++) {
        if (this->edges_of_tops[from][i].where == to)
          return this->edges_of_tops[from][i].weight;
      }
      return weight_type();
    } else {
      for (std::size_t i = 0; i < this->edges_of_tops[from].size(); i++) {
        if (this->edges_of_tops[from][i].where == to)
          return 1;
      }
      return 1;
    }
  }

  /**
   * @brief Возвращает ссылку на цвет вершины в которую идет ребро.
   *
   * @param iter Итератор по ребрам.
   * @return Ссылка на цвет вершины.
   */
  int &GetColor(iterator iter) {
    return this->color[GetIndexVertex(iter)];
  }

  int &GetPredecessor(iterator iter) {
    return this->predecessor[GetIndexVertex(iter)];
  }

  /**
   * @brief Возвращает ссылку на глубину вершины, в которую идет ребро.
   *
   * @param iter Итератор по ребрам.
   * @return Ссылка на глубину вершины.
   */
  int &GetDepth(iterator iter) {
    return this->depth[GetIndexVertex(iter)];
  }

  /**
   * @brief Выводит содержимое хранилища графа в std::cerr.
   */
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


/**
 * @brief Хранение графа для потоковых графов через список смежных ребер для каждой вершины.
 *
 * Класс FlowNetworkStorageTopsEdges расширяет GraphStorageTopsEdges, дополнительно поддерживая работу с потоками.
 *
 * @tparam CurEdges Тип ребра.
 */
template<typename CurEdges>
class FlowNetworkStorageTopsEdges : public GraphStorageTopsEdges<CurEdges> {
 public:
  using base = GraphStorageTopsEdges<CurEdges>;
  using base::GraphStorageTopsEdges;

  /**
   * @brief Возвращает поток ребра по итератору.
   *
   * @param iter Итератор по ребрам.
   * @return Поток ребра.
   */
  base::weight_type GetFlow(base::iterator iter) const {
    return iter->flow;
  }

  /**
   * @brief Возвращает ссылку на поток ребра по итератору.
   *
   * @param iter Итератор по ребрам.
   * @return Ссылка на поток ребра.
   */
  base::weight_type &GetFlow(base::iterator iter) {
    return iter->flow;
  }

  /**
   * @brief Возвращает ссылку на поток ребра между двумя вершинами.
   *
   * @param from Индекс исходной вершины.
   * @param to Индекс конечной вершины.
   * @return Ссылка на поток ребра.
   * @throws std::out_of_range Если ребро не найдено.
   */
  base::weight_type &GetFlow(int from, int to) {
    std::cerr << "GetFlow from = " << from << " to = " << to << "\n";
    for (std::size_t i = 0; i < this->edges_of_tops[from].size(); i++) {
      if (this->edges_of_tops[from][i].where == to)
        return this->edges_of_tops[from][i].flow;
    }
    throw(std::out_of_range(nullptr));
  }

/**
 * @brief описание метода см в классе выше
   */


  void AddEdge(int f_top, int s_top, base::weight_type weight) {
    this->edges_of_tops[f_top].push_back(CurEdges(s_top, weight));
    if (!this->orientation) {
      this->edges_of_tops[s_top].push_back(CurEdges(f_top, weight));
    } else {
      this->edges_of_tops[s_top].push_back(CurEdges(f_top, typename base::weight_type()));
    }
  }

  /**
   * @brief описание метода см в классе выше
   */
  void PrintStorage() {
    for (int i = 0; i < this->edges_of_tops.size(); i++) {
      std::cerr << i << " : ";
      for (int j = 0; j < this->edges_of_tops[i].size(); j++) {
        std::cerr << this->edges_of_tops[i][j].where << "-" << this->edges_of_tops[i][j].weight
                  << " / " << this->edges_of_tops[i][j].flow << "\n";
      }
      std::cerr << "\n";
    }
  }
};

/**
 * @brief Хранение графа ввиде матрицы смежности.
 *
 * Класс GraphStorageMatrixNear хранит граф в виде матрицы, где для каждой пары вершин хранится или действительное ребро или "пустое"
 * Требует, чтобы тип ребра был наследником EdgesWeight_MatrixNear.
 *
 * @tparam CurEdges Тип ребра.
 */
template<typename CurEdges>
class GraphStorageMatrixNear : public GraphStorage<CurEdges> {
  static_assert(std::is_base_of_v<EdgesWeight_MatrixNear<typename CurEdges::value_type>, CurEdges>);
 protected:
  /// матрица смежности
  using edges = std::vector<CurEdges>;
  std::vector<edges> edges_of_tops;

 public:
  /// Тип ребер
  using edges_type = CurEdges;
  /// Тип веса ребра
  using weight_type = typename edges_type::value_type;
  /// Константный итератор для обхода ребер вершины
  using const_iterator = NearTopIterator_NearMatrix<CurEdges, true>;
  /// Итератор для обхода ребер вершины
  using iterator = NearTopIterator_NearMatrix<CurEdges, false>;
  using const_reverse_iterator = std::reverse_iterator<NearTopIterator_NearMatrix<CurEdges, true>>;
  using reverse_iterator = std::reverse_iterator<NearTopIterator_NearMatrix<CurEdges, false>>;
  using GraphStorage<CurEdges>::GetColor;
  using GraphStorage<CurEdges>::GetPredecessor;
  using GraphStorage<CurEdges>::GetDepth;

  /**
   * @brief Конструктор, создающий матрицу смежности графа.
   *
   * В конец каждой строки кладем INT_MAXIMUS, чтобы у итераторов по существующим ребрам всегд существовал end()
   *
   * А в случае если ребра не существует то инициализирует ребро с помощью глобальной константы POISON_VAL_ID_VERT
   *
   * @param n Число вершин.
   * @param orientation Флаг ориентации графа (по умолчанию false).
   */
  explicit GraphStorageMatrixNear(std::size_t n, bool orientation = false)
      : GraphStorage<CurEdges>(n, orientation),
        edges_of_tops(n, edges(n + 1, edges_type(POISON_VAL_ID_VERT, weight_type()))) {
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

/**
 * @brief описание метода см в классе выше
   */
  void AddEdge(int f_top, int s_top, weight_type weight = weight_type(1)) {
    edges_of_tops[f_top][s_top] = edges_type(s_top, weight);
    if (!this->orientation) {
      edges_of_tops[s_top][f_top] = edges_type(f_top, weight);
    }
  }

  /**
   * @brief описание метода см в классе выше
   */
  template<typename... Args>
  void AddEdge(int f_top, int s_top, Args &&... construct_args) {
    edges_of_tops[f_top][s_top] = edges_type(s_top, construct_args...);
    if (!this->orientation) {
      edges_of_tops[s_top][f_top] = edges_type(f_top, construct_args...);
    }
  }

  /**
   * @brief Возвращает итератор на начало списка ребер для вершины.
   *
   * Пропускает элементы с POISON_VAL_ID_VERT.(это означает что такого ребра в графе нет)
   *
   * @param id Индекс вершины.
   * @return Итератор на начало списка ребер.
   */
  iterator BeginEdges(int id) {
    auto i = edges_of_tops[id].begin();
    while (i->where == POISON_VAL_ID_VERT)
      i++; // Пропускаем некорректные элементы
    return iterator(i);
  }

  /**
   * @brief описание метода см в классе выше
   */
  int GetIndexVertex(iterator iter) {
//    std::cerr << "GetIndexVertex = " << (*iter).where << "\n";
    return (*iter).where;
  }

  /**
   * @brief описание метода см в классе выше
   */
  weight_type GetWeightFromIter(iterator iter) {
    return (*iter).weight;
  }

  /**
   * @brief описание метода см в классе выше
   */
  weight_type GetWeight(int from, int to) {
    return this->edges_of_tops[from][to].weight;
  }

  /**
   * @brief Возвращает итератор на конец списка вершин для вершины.
   *
   * @param id Индекс вершины.
   * @return Итератор на конец списка вершин.
   */
  iterator EndEdges(int id) {
    auto i = edges_of_tops[id].end() - 1;
    return iterator(i);
  }

  /**
   * @brief Возвращает матрицу смежности, представляющую граф.
   *
   * @return Матрица смежности, где каждый элемент содержит вес соответствующего ребра.
   */
  std::vector<std::vector<weight_type>> GetMatrixNear() {
    std::vector<std::vector<weight_type>> to_ret(edges_of_tops.size(), std::vector<weight_type>(edges_of_tops.size(), 0));
    for (std::size_t i = 0; i < edges_of_tops.size(); i++) {
      for (std::size_t j = 0; j < edges_of_tops.size(); j++) {
        to_ret[i][j] = GetWeightFromIter(iterator(edges_of_tops[i].begin() + j));
      }
    }
    return to_ret;
  }

  /**
   * @brief описание метода см в классе выше
   */
  virtual std::size_t size() const {
    return edges_of_tops.size();
  }

  /**
   * @brief описание метода см в классе выше
   */
  int &GetColor(iterator iter) {
    return this->color[GetIndexVertex(iter)];
  }
  int &GetPredecessor(iterator iter) {
    return this->predecessor[GetIndexVertex(iter)];
  }

  /**
   * @brief описание метода см в классе выше
   */
  int &GetDepth(iterator iter) {
    return this->depth[GetIndexVertex(iter)];
  }
  /**
   * @brief описание метода см в классе выше
   */
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

/**
 * @brief Хранение графа потоковой сети с помощью матрицы смежности.
 *
 * Класс FlowNetworkStorageTopsEdges расширяет GraphStorageTopsEdges, дополнительно поддерживая работу с потоками.
 *
 * @tparam CurEdges Тип ребра.
 */
template<typename CurEdges>
class FlowNetworkStorageMatrixNear : public GraphStorageMatrixNear<CurEdges> {
 public:
  using base = GraphStorageMatrixNear<CurEdges>;
  using base::GraphStorageMatrixNear;

  /**
   * @brief описание метода см в классе выше
   */
  base::weight_type GetFlow(base::iterator iter) const {
    return iter->flow;
  }

  /**
   * @brief описание метода см в классе выше
   */
  base::weight_type &GetFlow(base::iterator iter) {
    return iter->flow;
  }

  /**
   * @brief Возвращает ссылку на поток ребра между двумя вершинами.
   *
   * @param from Индекс исходной вершины.
   * @param to Индекс конечной вершины.
   * @return Ссылка на поток ребра.
   */
  base::weight_type &GetFlow(int from, int to) {
    return this->edges_of_tops[from][to].flow;
  }

  /**
   * @brief Добавляет ребро в потоковую сеть представленную в виде матрицы смежности.
   *
   * Если граф неориентированный, добавляется обратное ребро. Для ориентированного графа обратное ребро
   * добавляется с весом 0.(Так как в алгоритмах с потоками используются обратные ребра)
   *
   * @param f_top Индекс исходной вершины.
   * @param s_top Индекс конечной вершины.
   * @param weight Вес ребра (по умолчанию 1).
   */
  void AddEdge(int f_top, int s_top, base::weight_type weight = base::weight_type(1)) {
    this->edges_of_tops[f_top][s_top] = typename base::edges_type(s_top, weight);
    if (!this->orientation) {
      this->edges_of_tops[s_top][f_top] = typename base::edges_type(f_top, weight);
    } else {
      this->edges_of_tops[s_top][f_top] = CurEdges(f_top, typename base::weight_type(0));
    }
  }

  /**
   * @brief описание метода см выше
   */
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

#endif // GRAPHALKO_GRAPHSTORAGE_HPP