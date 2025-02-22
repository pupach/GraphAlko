//
// Created by catboy on 2/22/2025.
//

#ifndef GRAPHALKO_HEADERS_VISITORSHEADERS_LCAVISITORS_HPP_
#define GRAPHALKO_HEADERS_VISITORSHEADERS_LCAVISITORS_HPP_

#include"Visitors.hpp"

template<typename CurGraph>
class DFSLCADoubleUp : public DFSVisitor<CurGraph> {
 public:
  using flow_type = std::conditional<std::is_same_v<typename CurGraph::weight_type, bool>,
                                     int,
                                     typename CurGraph::weight_type>::type;
  using my_type = DFSLCADoubleUp<CurGraph>;
  using dp_type = std::vector<std::vector<int>>;

 protected:
  int time = 0;
  int deep = 0;
  int root;
  int amount_vertex;
  std::vector<flow_type> arr_deep;
  std::vector<int> parent;
  std::vector<int> arr_in;
  std::vector<int> arr_out;
  std::vector<flow_type> history_of_deep;
  dp_type dp;

 public:

  DFSLCADoubleUp(int root, int amount_vertex)
      : amount_vertex(amount_vertex),
        root(root),
        parent(amount_vertex, root),
        arr_deep(amount_vertex, 0),
        arr_in(amount_vertex, -1),
        arr_out(amount_vertex, -1) {

  }

  bool tree_edge_DFS(DFSVisitor<CurGraph>::edge_desc edge,
                     DFSVisitor<CurGraph>::edge_desc_iter iter,
                     DFSVisitor<CurGraph>::graph_type &graph) {
    parent[edge.second] = edge.first;
    std::cerr << edge.first << " parent " << edge.second << "\n";
    history_of_deep.push_back(graph.GetWeightFromIter(iter));
    deep += graph.GetWeightFromIter(iter);
    return false;
  }

  bool discover_vertex_DFS(DFSVisitor<CurGraph>::vert_desc top, DFSVisitor<CurGraph>::graph_type &graph) {
    arr_in[top] = time++;
    arr_deep[top] = deep;

    return false;
  }

  bool finish_edge(DFSVisitor<CurGraph>::edge_desc edge,
                   DFSVisitor<CurGraph>::edge_desc_iter iter,
                   DFSVisitor<CurGraph>::graph_type &graph) {
    deep -= history_of_deep.back();
    history_of_deep.pop_back();

    return false;
  }

  void finish_vertex_DFS(DFSVisitor<CurGraph>::vert_desc top, DFSVisitor<CurGraph>::graph_type &graph) {
    arr_out[top] = time++;
  }

  bool IsLeader(int x, int y) {
    if ((arr_in[x] <= arr_in[y]) && (arr_out[x] >= arr_out[y])) return true;

    return false;
  }

  void FillDpForLCA(CurGraph &graph);

  void BeReadyForLCA(CurGraph &graph);

  flow_type LSA_with_distance(int x, int y, CurGraph &graph);

  template<typename... Args>
  void ConstructDp(Args &&... construct_args) {
    dp = dp_type(construct_args...);
  }

  void DeleteDp() {
    dp.clear();
  }

};
template<typename CurGraph>
void DFSLCADoubleUp<CurGraph>::FillDpForLCA(CurGraph &graph) {
  for (int i = 0; i < 21; i++) {
    for (int j = 0; j < amount_vertex; j++) {
      //std::cout << i << " " << j << "\n";
      if (i == 0) {
        dp[j][i] = parent[j];
      } else {
        dp[j][i] = dp[dp[j][i - 1]][i - 1];
      }
      // std::cout << "dp[j][i] = " << dp[j][i] << "\n";
    }
  }
}

template<typename CurGraph>
void DFSLCADoubleUp<CurGraph>::BeReadyForLCA(CurGraph &graph) {
  graph.template DFS<my_type>(root, *this);
  this->ConstructDp(amount_vertex, std::vector(21, root));  //TODO: 21
  this->FillDpForLCA(graph);
}

template<typename CurGraph>
DFSLCADoubleUp<CurGraph>::flow_type DFSLCADoubleUp<CurGraph>::LSA_with_distance(int x, int y, CurGraph &graph) {
  if (IsLeader(x, y)) return arr_deep[y] - arr_deep[x];
  if (IsLeader(y, x)) return arr_deep[x] - arr_deep[y];

  int cur_top = x;
  for (int i = 19; i > -1; i--) {
    if ((!IsLeader(dp[cur_top][i], y)) && (IsLeader(dp[cur_top][i + 1], y))) {
      cur_top = dp[cur_top][i];
    }
  }
  return arr_deep[x] + arr_deep[y] - 2 * arr_deep[parent[cur_top]];
}

template<typename CurGraph>
class DFSLCAFrakBender : public DFSVisitor<CurGraph> {
 public:
  using my_type = DFSLCAFrakBender<CurGraph>;

 protected:
  int deep = 0;
  int root;
  std::vector<int> first;
  std::vector<int> arr_deep;
  std::vector<int> euler;
  std::vector<std::vector<int>> dp;

 public:
  DFSLCAFrakBender(int root, int amount_vertex) : root(root), first(amount_vertex, -1) {

  }
  bool discover_vertex_DFS(DFSVisitor<CurGraph>::vert_desc top, DFSVisitor<CurGraph>::graph_type &graph) {
    deep++;
    arr_deep.push_back(deep);
    euler.push_back(top);
    first[top] = euler.size() - 1;

    return false;
  }

  bool finish_edge(DFSVisitor<CurGraph>::edge_desc edge,
                   DFSVisitor<CurGraph>::edge_desc_iter iter,
                   DFSVisitor<CurGraph>::graph_type &graph) {
    euler.push_back(edge.first);
    arr_deep.push_back(deep);
    return false;
  }

  void finish_vertex_DFS(DFSVisitor<CurGraph>::vert_desc top, DFSVisitor<CurGraph>::graph_type &graph) {
    deep--;
  }

  template<typename... Args>
  void ConstructDp(Args &&... construct_args) {
    dp = dp_type(construct_args...);
  }

  void DeleteDp() {
    dp.clear();
  }

  void BuildSparseTable(CurGraph &visitor);

  int RMQ(int l, int r, CurGraph &graph);

  void PreprocessForLCAFrakBender(CurGraph &graph);

  int GetLCA(int u, int v, CurGraph &graph);
};

template<typename CurGraph>
void DFSLCAFrakBender<CurGraph>::BuildSparseTable(CurGraph &graph) {

  int m = euler.size();
  int log = (int) std::log2(m) + 1;
  dp.assign(m, std::vector<int>(log, -1));

  for (int i = 0; i < m; i++) {
    dp[i][0] = i;
  }

  for (int j = 1; j < log; j++) {
    for (int i = 0; i + (1 << j) <= m; i++) {
      if (arr_deep[dp[i][j - 1]] < arr_deep[dp[i + (1 << (j - 1))][j - 1]]) {
        dp[i][j] = dp[i][j - 1];
      } else {
        dp[i][j] = dp[i + (1 << (j - 1))][j - 1];
      }
    }
  }
}

template<typename CurGraph>
int DFSLCAFrakBender<CurGraph>::RMQ(int l, int r, CurGraph &graph) {

  std::cerr << "RMQ begin l =" << l << " r = " << r << "\n";
  if (l > r) {
    std::cerr << "EEERRRRRRRRROOOOOOORRRRRRR\n";
    return -1;
  }
  int log = (int) std::log2(r - l + 1);
  if (arr_deep[dp[l][log]] < arr_deep[dp[r - (1 << log) + 1][log]]) {
    return dp[l][log];
  } else {
    return dp[r - (1 << log) + 1][log];
  }
}

template<typename CurGraph>
void DFSLCAFrakBender<CurGraph>::PreprocessForLCAFrakBender(CurGraph &graph) {

  graph.template DFS<my_type>(root, *this);
  BuildSparseTable(graph);
}

template<typename CurGraph>
int DFSLCAFrakBender<CurGraph>::GetLCA(int u, int v, CurGraph &graph) {

  int left = first[u];
  int right = first[v];
  int ind = RMQ(left, right, graph);
  return euler[ind];
}

#endif //GRAPHALKO_HEADERS_VISITORSHEADERS_LCAVISITORS_HPP_
