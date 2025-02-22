//
// Created by catboy on 2/22/2025.
//

#ifndef GRAPHALKO_HEADERS_VISITORSHEADERS_FLOWVISITORS_H_
#define GRAPHALKO_HEADERS_VISITORSHEADERS_FLOWVISITORS_H_
#include"Visitors.hpp"

template<typename CurGraph>
class DFS_BFS_Dinic : public DFSVisitor<CurGraph>, public BFSVisitor<CurGraph> {
 public:
  using flow_type = typename CurGraph::weight_type;
  using my_type = DFS_BFS_Dinic<CurGraph>;

 protected:
  flow_type flow = 0;
  int end;
  int root;
  std::vector<int> arr_deep;
  std::vector<flow_type> stack_DFS;

 public:
  DFS_BFS_Dinic(int root, int end, int amount_vertex) : end(end), root(root), arr_deep(amount_vertex, -1) {
    arr_deep[root] = 0;
  }

  void initialize_vertex_BFS(DFSVisitor<CurGraph>::vert_desc top, DFSVisitor<CurGraph>::graph_type &graph) {
    graph.GetColor(top) = 1;
    arr_deep[top] = -1;
    if (root == top) arr_deep[top] = 0;
  }

  bool discover_vertex_BFS(DFSVisitor<CurGraph>::vert_desc top, DFSVisitor<CurGraph>::graph_type &graph) {
    if (top == end) {
      return true;
    }
    return false;
  }

  void non_tree_edge(DFSVisitor<CurGraph>::edge_desc edge,
                     DFSVisitor<CurGraph>::edge_desc_iter iter,
                     DFSVisitor<CurGraph>::graph_type &graph) {
    if ((arr_deep[edge.second] == -1) && ((*iter).flow < (*iter).weight) && (arr_deep[edge.first] != -1)) {
      arr_deep[edge.second] = arr_deep[edge.first] + 1;
      graph.PushQeueuBFS({edge.first, edge.second});
    }
  }

  bool IsTargetAvaliable(int target) {
    return arr_deep[target] != -1;
  }

  bool discover_vertex_DFS(DFSVisitor<CurGraph>::vert_desc top, DFSVisitor<CurGraph>::graph_type &graph) {
    std::cerr << "discover_vertex_DFS = " << top << " top == end = " << (top == end) << "\n";
    if (top == end) {
      //exit(-1);
      return true;
    }
    flow = stack_DFS.back();
    return false;
  }

  void start_vertex(DFSVisitor<CurGraph>::vert_desc top, DFSVisitor<CurGraph>::graph_type &graph) {
    flow = flow_type();
    stack_DFS.clear();
    stack_DFS.push_back(flow_type(INT_MAXIMUS));
  }

  void finish_vertex_DFS(DFSVisitor<CurGraph>::vert_desc top, DFSVisitor<CurGraph>::graph_type &graph) {
    stack_DFS.push_back(flow_type());
  }

  bool tree_edge_DFS(DFSVisitor<CurGraph>::edge_desc edge,
                     DFSVisitor<CurGraph>::edge_desc_iter iter,
                     DFSVisitor<CurGraph>::graph_type &graph) {
    std::cerr << "find tree edge from = " << edge.first << " to " << edge.second << "   " << arr_deep[edge.first] << "/"
              << arr_deep[edge.second] << " cur flow = " << (*iter).flow << " cap = " << (*iter).weight << "\n";
    if ((arr_deep[edge.second] == arr_deep[edge.first] + 1) && ((*iter).flow < (*iter).weight)) {
      stack_DFS.push_back(std::min(flow, (*iter).weight - (*iter).flow));
      std::cerr << "stack push " << std::min(flow, (*iter).weight - (*iter).flow) << "\n";
      return false;
    }
    return true;
  }

  bool finish_edge(DFSVisitor<CurGraph>::edge_desc edge,
                   DFSVisitor<CurGraph>::edge_desc_iter iter,
                   DFSVisitor<CurGraph>::graph_type &graph) {
    flow_type delta = stack_DFS.back();
    stack_DFS.pop_back();
    std::cerr << "stack pop " << delta << "\n";
    flow = stack_DFS.back();
    stack_DFS.pop_back();
    std::cerr << "stack pop " << flow << "\n";
    if (delta > 0) {
      (*iter).flow += delta;
      graph.GetFlow(edge.second, edge.first) -= delta;
      stack_DFS.push_back(delta);
      std::cerr << "stack push " << delta << "\n";
      return true;
    }
    stack_DFS.push_back(flow);
    return false;
  }

  flow_type Dinic(int source, int target, CurGraph &graph);
};

template<typename CurGraph>
DFS_BFS_Dinic<CurGraph>::flow_type DFS_BFS_Dinic<CurGraph>::Dinic(int source, int target, CurGraph &graph) {
  static_assert((std::is_base_of_v<EdgesFlow_TopsEdges<typename CurGraph::weight_type>, typename CurGraph::edges_type>
      || std::is_base_of_v<EdgesFlow_MatrixNear<typename CurGraph::weight_type>, typename CurGraph::edges_type>));

  std::cerr << "soutce = " << source << " target = " << target << "\n";
  flow_type max_flow = flow_type(), flow = flow_type();
  while (true) {
    graph.template BFS<my_type>(source, *this);
    std::cerr << "visitor.arr_deep" << "\n";
    for (int i = 0; i < arr_deep.size(); i++) {
      std::cerr << i << " : " << arr_deep[i] << "\n";
    }
    if (!IsTargetAvaliable(target)) break;
    do {
      graph.template DFS<my_type>(source, *this);
      flow = stack_DFS.back();
      if (flow == flow_type(INT_MAXIMUS)) break;
      max_flow += flow;
      stack_DFS.clear();
    } while (flow != flow_type());
  }
  std::cerr << max_flow;
  return max_flow;
}

template<typename CurGraph>
class DFSFordFulkerson : public DFSVisitor<CurGraph> {
 public:
  using flow_type = typename CurGraph::weight_type;
  using my_type = DFSFordFulkerson<CurGraph>;

 protected:
  flow_type flow = flow_type();
  int end;
  bool EndAlgorim = false;
  int root;
  std::vector<int> parent;
  std::vector<flow_type> stack_DFS;

 public:
  DFSFordFulkerson(int root, int end, int amount_vertex) : end(end), root(root), parent(amount_vertex, -1) {
    parent[root] = root;
  }

  bool discover_vertex_DFS(DFSVisitor<CurGraph>::vert_desc top, DFSVisitor<CurGraph>::graph_type &graph) {
    std::cerr << "discover_vertex_DFS = " << top << " top == end = " << (top == end) << "\n";
    if (top == end) {
      EndAlgorim = true;
      return true;
    }
    flow = stack_DFS.back();
    return EndAlgorim;
  }

  void start_vertex(DFSVisitor<CurGraph>::vert_desc top, DFSVisitor<CurGraph>::graph_type &graph) {
    flow = flow_type();
    stack_DFS.clear();
    stack_DFS.push_back(flow_type(INT_MAXIMUS));
    EndAlgorim = false;
  }

  void finish_vertex_DFS(DFSVisitor<CurGraph>::vert_desc top, DFSVisitor<CurGraph>::graph_type &graph) {
    stack_DFS.push_back(flow_type());
  }

  bool tree_edge_DFS(DFSVisitor<CurGraph>::edge_desc edge,
                     DFSVisitor<CurGraph>::edge_desc_iter iter,
                     DFSVisitor<CurGraph>::graph_type &graph) {
    if (EndAlgorim) {
      return true;
    }
    if ((*iter).flow < (*iter).weight) {
      stack_DFS.push_back(std::min(flow, (*iter).weight - (*iter).flow));
      std::cerr << "stack push " << std::min(flow, (*iter).weight - (*iter).flow) << "\n";
      return false;
    }
    return true;
  }

  bool finish_edge(DFSVisitor<CurGraph>::edge_desc edge,
                   DFSVisitor<CurGraph>::edge_desc_iter iter,
                   DFSVisitor<CurGraph>::graph_type &graph) {

    flow_type delta = stack_DFS.back();
    std::cerr << "stack pop " << delta << "\n";
    if (!EndAlgorim) {
      stack_DFS.pop_back();

      flow = stack_DFS.back();
      stack_DFS.pop_back();
      std::cerr << "stack pop " << flow << "\n";
    }
    if (delta > 0) {
      (*iter).flow += delta;
      graph.GetFlow(edge.second, edge.first) -= delta;
      stack_DFS.push_back(delta);
      std::cerr << "stack push " << delta << "\n";
      return true;
    }
    stack_DFS.push_back(flow);
    return false;
  }

  flow_type FordFUlkerson(int source, int target, CurGraph &graph);
};

template<typename CurGraph>
DFSFordFulkerson<CurGraph>::flow_type DFSFordFulkerson<CurGraph>::FordFUlkerson(int source,
                                                                                int target,
                                                                                CurGraph &graph) {
  static_assert((std::is_base_of_v<EdgesFlow_TopsEdges<typename CurGraph::weight_type>, typename CurGraph::edges_type>
      || std::is_base_of_v<EdgesFlow_MatrixNear<typename CurGraph::weight_type>, typename CurGraph::edges_type>));

  std::cerr << "soutce = " << source << " target = " << target << "\n";
  flow_type max_flow = 0, flow = 0;

  do {
    graph.template DFS<my_type>(source, *this);
    flow = stack_DFS.back();
    if (!EndAlgorim) break;
    max_flow += flow;
    stack_DFS.clear();
  } while (true);

  std::cerr << max_flow;
  return max_flow;
}

template<typename CurGraph>
class BFSAdmondKarp : public DFSVisitor<CurGraph>, public BFSVisitor<CurGraph> {
 protected:
  int end;
  int root;
  bool EndAlgorim;
  std::vector<int> parent;

 public:
  using flow_type = typename CurGraph::weight_type;
  using my_type = BFSAdmondKarp<CurGraph>;

  BFSAdmondKarp(int root, int end, int amount_vertex) : end(end), root(root), parent(amount_vertex, -1) {
  }

  void initialize_vertex_BFS(DFSVisitor<CurGraph>::vert_desc top, DFSVisitor<CurGraph>::graph_type &graph) {
    graph.GetColor(top) = 1;
    parent[top] = -1;
  }

  bool discover_vertex_BFS(DFSVisitor<CurGraph>::vert_desc top, DFSVisitor<CurGraph>::graph_type &graph) {
    if (top == end) {
      EndAlgorim = true;
      return true;
    }
    return EndAlgorim;
  }

  void non_tree_edge(DFSVisitor<CurGraph>::edge_desc edge,
                     DFSVisitor<CurGraph>::edge_desc_iter iter,
                     DFSVisitor<CurGraph>::graph_type &graph) {
    if ((parent[edge.second] == -1) && ((*iter).flow < (*iter).weight)) {
      parent[edge.second] = edge.first;
      graph.PushQeueuBFS({edge.first, edge.second});
    }
  }

  bool IsTargetAvaliable(int target) {
    return parent[target] != -1;
  }

  flow_type AdmondKarp(int source, int target, DFSVisitor<CurGraph>::graph_type &graph);
};

template<typename CurGraph>
BFSAdmondKarp<CurGraph>::flow_type BFSAdmondKarp<CurGraph>::AdmondKarp(int source,
                                                                       int target,
                                                                       DFSVisitor<CurGraph>::graph_type &graph) {
  static_assert((std::is_base_of_v<EdgesFlow_TopsEdges<typename CurGraph::weight_type>, typename CurGraph::edges_type>
      || std::is_base_of_v<EdgesFlow_MatrixNear<typename CurGraph::weight_type>, typename CurGraph::edges_type>));

  std::cerr << "soutce = " << source << " target = " << target << "\n";
  flow_type max_flow = 0, flow = INT_MAXIMUS;

  do {
    EndAlgorim = false;
    graph.template BFS<my_type>(source, *this);
    if (!IsTargetAvaliable(target)) break;
    for (int i = target; i != source;) {
      int prev = parent[i];
      flow = std::min(flow, (graph.GetWeight(prev, i) - graph.GetFlow(prev, i)));
      i = prev;
    }
    for (int i = target; i != source;) {
      int prev = parent[i];
      graph.GetFlow(prev, i) += flow;
      graph.GetFlow(i, prev) -= flow;
      i = prev;
    }
    std::cerr << "flow = " << flow << "\n";
    max_flow += flow;
  } while (true);

  std::cerr << max_flow;
  return max_flow;
}

#endif //GRAPHALKO_HEADERS_VISITORSHEADERS_FLOWVISITORS_H_
