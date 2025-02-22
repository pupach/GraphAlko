//
// Created by catboy on 2/17/2025.
//


template<typename CurGraphStorage>
void Graph<CurGraphStorage>::foo() {
  std::cout << 5;
}

//template<typename CurGraphStorage, std::enable_if_t<std::is_base_of_v<GraphStorage<typename CurGraphStorage::edges_type>, CurGraphStorage>, bool>>
template<typename CurGraphStorage>
template<typename... Args>
void Graph<CurGraphStorage>::AddEdge(int f, int s, Args &&... construct_args) {
  storage.AddEdge(f, s, construct_args...); //std::forward realize
}

template<typename CurGraphStorage>
template<typename CurDFSVisitor>
void Graph<CurGraphStorage>::DFS(int begin_top, CurDFSVisitor &visitor) {
  static_assert(std::is_base_of_v<DFSVisitor<Graph<CurGraphStorage>>, CurDFSVisitor>);

  storage.ConstructColor();

  for (std::size_t i = 0; i < storage.size(); i++) {
    visitor.initialize_vertex_DFS(i, *this);
  }
  visitor.start_vertex(begin_top, *this);

  DFSRecr<CurDFSVisitor>(begin_top, visitor);
}

template<typename CurGraphStorage>
template<typename CurDFSVisitor>
void Graph<CurGraphStorage>::DFSRecr(int begin_top, CurDFSVisitor &visitor) {
  static_assert(std::is_base_of_v<DFSVisitor<Graph<CurGraphStorage>>, CurDFSVisitor>);

  storage.GetColor(begin_top) = 1;
  if (visitor.discover_vertex_DFS(begin_top, *this)) return;

  auto near_top_iter_begin = storage.BeginEdges(begin_top);
  auto near_top_iter_end = storage.EndEdges(begin_top);

  while ((near_top_iter_begin != near_top_iter_end)) {
    visitor.examine_edge_DFS({begin_top, storage.GetIndexVertex(near_top_iter_begin)}, near_top_iter_begin, *this);
    near_top_iter_begin++;
  }

  near_top_iter_begin = storage.BeginEdges(begin_top);
  near_top_iter_end = storage.EndEdges(begin_top);
  while ((near_top_iter_begin != near_top_iter_end)) {
    //std::cerr << std::distance(near_top_iter_begin, near_top_iter_end) << "\n";
    if (storage.GetColor(near_top_iter_begin) == 0) {
      if (visitor.tree_edge_DFS({begin_top, storage.GetIndexVertex(near_top_iter_begin)}, near_top_iter_begin, *this)) {
        //std::cerr << std::distance(near_top_iter_begin, near_top_iter_end) << "\n";
        near_top_iter_begin++;
        //std::cerr << std::distance(near_top_iter_begin, near_top_iter_end) << "\n";
        continue;
      }
      DFSRecr(storage.GetIndexVertex(near_top_iter_begin), visitor);
      if (visitor.finish_edge({begin_top, storage.GetIndexVertex(near_top_iter_begin)}, near_top_iter_begin, *this)) {
        return;
      }

    } else if (storage.GetColor(near_top_iter_begin) == 1) {
      visitor.back_edge({begin_top, storage.GetIndexVertex(near_top_iter_begin)}, near_top_iter_begin, *this);
    } else {
      visitor.forward_or_cross_edge({begin_top, storage.GetIndexVertex(near_top_iter_begin)},
                                    near_top_iter_begin,
                                    *this);
    }
    near_top_iter_begin++;
  }
  storage.GetColor(begin_top) = 2;
  visitor.finish_vertex_DFS(begin_top, *this);
  visitor.DFSVisitFinishVertex(begin_top, *this);
}

template<typename CurGraphStorage>
template<typename CurBFSVisitor>
void Graph<CurGraphStorage>::BFS(int begin_top, CurBFSVisitor &visitor) {
  static_assert(std::is_base_of_v<BFSVisitor<Graph<CurGraphStorage>>, CurBFSVisitor>);
  this->bfs_deq.clear();

  storage.ConstructColor();
  for (std::size_t i = 0; i < storage.size(); i++) {
    visitor.initialize_vertex_BFS(i, *this);
  }

  BFSRecr<CurBFSVisitor>(begin_top, visitor);
}

template<typename CurGraphStorage>
template<typename CurBFSVisitor>
void Graph<CurGraphStorage>::BFSRecr(int begin_top, CurBFSVisitor &visitor) {
  static_assert(std::is_base_of_v<BFSVisitor<Graph<CurGraphStorage>>, CurBFSVisitor>);

  storage.GetColor(begin_top) = 1;

  auto near_top_iter_begin = storage.BeginEdges(begin_top);
  auto near_top_iter_end = storage.EndEdges(begin_top);
  if (visitor.discover_vertex_BFS(begin_top, *this)) return;
  while ((near_top_iter_begin != near_top_iter_end)) {
    visitor.examine_edge_BFS({begin_top, storage.GetIndexVertex(near_top_iter_begin)}, near_top_iter_begin, *this);
    near_top_iter_begin++;
  }

  near_top_iter_begin = storage.BeginEdges(begin_top);
  near_top_iter_end = storage.EndEdges(begin_top);
  while ((near_top_iter_begin != near_top_iter_end)) {
    if (storage.GetColor(near_top_iter_begin) == 0) {
      visitor.tree_edge_BFS({begin_top, storage.GetIndexVertex(near_top_iter_begin)},
                            near_top_iter_begin,
                            *this); //TODO: делать bool
      if (storage.GetColor(near_top_iter_begin) == 0) {
        storage.GetColor(near_top_iter_begin) = 1;
        bfs_deq.emplace_back(begin_top, storage.GetIndexVertex(near_top_iter_begin));
      }
    } else {
      visitor.non_tree_edge({begin_top, storage.GetIndexVertex(near_top_iter_begin)}, near_top_iter_begin, *this);
      if (storage.GetColor(near_top_iter_begin) == 1) {
        visitor.gray_target(storage.GetIndexVertex(near_top_iter_begin), *this);
      } else {
        visitor.black_target(storage.GetIndexVertex(near_top_iter_begin), *this);
      }
    }
    near_top_iter_begin++;
  }
  if (bfs_deq.empty()) return;

  auto next_top = bfs_deq.front();
  if (next_top.first != begin_top) {
    visitor.finish_vertex_BFS(begin_top, *this);
  }
  storage.GetColor(next_top.second) = 2;
  bfs_deq.pop_front();
  visitor.examine_vertex_BFS(next_top.second, *this);

  BFSRecr(next_top.second, visitor);
}

template<typename CurGraphStorage>
template<typename CurDejkstraVisitor>
void Graph<CurGraphStorage>::Dejkstra(int begin_top, CurDejkstraVisitor &visitor) {
  static_assert(std::is_base_of_v<DejkstraVisitor<Graph<CurGraphStorage>>, CurDejkstraVisitor>);

  storage.ConstructColor();
  storage.ConstructDeep();
  storage.ConstructPredecessor();
  for (std::size_t i = 0; i < storage.size(); i++) {
    visitor.initialize_vertex_Dejkstra(i, *this);
  }
  storage.GetColor(begin_top) = 1;
  storage.GetDeep(begin_top) = 0;
  if (visitor.discover_vertex_Dejkstra(begin_top, *this)) return;
  std::priority_queue<std::pair<int, int>> dist_queue;

  dist_queue.emplace(0, begin_top);

  while (!dist_queue.empty()) {
    auto v_pair = dist_queue.top();
    dist_queue.pop();
    int v_vert = v_pair.second;
    int v_dist = -v_pair.first;
    std::cerr << " vert = " << v_vert << " dist = " << v_dist << "\n";
    if (storage.GetDeep(v_vert) < v_dist) {
      std::cerr << "continue\n";
      continue;
    } else if (storage.GetDeep(v_vert) > v_dist) {
      std::cerr << "EEEEEEEERRRRRRRRRRRRRRRRROOOOOOOOOOOOOOOORRRRRRRRRRR\n";
    }
    visitor.examine_vertex_Dejkstra(v_dist, *this);
    auto near_top_iter_begin = storage.BeginEdges(v_vert);
    auto near_top_iter_end = storage.EndEdges(v_vert);
    while ((near_top_iter_begin != near_top_iter_end)) {
      visitor.examine_edge_Dejkstra({begin_top, storage.GetIndexVertex(near_top_iter_begin)},
                                    near_top_iter_begin,
                                    *this);

      std::cerr << " vert_to = ";
      std::cerr << storage.GetIndexVertex(near_top_iter_begin) << "weight = ";
      std::cerr << (GetWeightFromIter(near_top_iter_begin));
      std::cerr << " deep = " << storage.GetDeep(near_top_iter_begin) << "\n";

      if (GetWeightFromIter(near_top_iter_begin) + v_dist < storage.GetDeep(near_top_iter_begin)) {
        storage.GetDeep(near_top_iter_begin) = GetWeightFromIter(near_top_iter_begin) + v_dist;
        storage.GetPredecessor(near_top_iter_begin) = v_vert;
        visitor.edge_relaxed({begin_top, storage.GetIndexVertex(near_top_iter_begin)}, near_top_iter_begin, *this);
        dist_queue.push({-(v_dist + GetWeightFromIter(near_top_iter_begin)),
                         storage.GetIndexVertex(near_top_iter_begin)});
        if (storage.GetColor(near_top_iter_begin) == 0) {
          storage.GetColor(near_top_iter_begin) = 1;
          visitor.discover_vertex_Dejkstra(storage.GetIndexVertex(near_top_iter_begin), *this);
        }
      } else {
        visitor.edge_not_relaxed({begin_top, storage.GetIndexVertex(near_top_iter_begin)}, near_top_iter_begin, *this);
      }
      near_top_iter_begin++;
    }
    storage.GetColor(begin_top) = 2;
    visitor.finish_vertex_Dejkstra(begin_top, *this);
  }
}