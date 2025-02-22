//
// Created by catboy on 2/19/2025.
//
#include <fstream>
#include <cassert>

#include "test.hpp"
#include "FlowVisitors.hpp"
#include "LCAVisitors.hpp"
#include "ShortestPathVisitors.hpp"

template<typename CurGraph>
void CreateGraphfromIfStream(int amount_edges, std::ifstream& read_stream, CurGraph& graph) {
if constexpr (((std::is_base_of_v<EdgesWeight_MatrixNear<typename CurGraph::weight_type>, typename CurGraph::edges_type> && !std::is_same_v<typename CurGraph::weight_type, bool> ) || std::is_base_of_v<EdgesWeight_TopsEdges<typename CurGraph::weight_type>, typename CurGraph::edges_type>)) {
  int vert_1, vert_2, weight;
  for (std::size_t i = 0; i < amount_edges; i++) {
    read_stream >> vert_1 >> vert_2 >> weight;
    graph.AddEdge(vert_1, vert_2, weight);
    std::cerr << "sadfsdasadf\n";
  }
}
else{
  int vert_1, vert_2;
  for (std::size_t i = 0; i < amount_edges; i++) {
    read_stream >> vert_1 >> vert_2;
    graph.AddEdge(vert_1, vert_2);
  }
}
  graph.PrintGraph();
}


void MakeTestGraph_TopEdges(const std::string &filename) {
  std::string line;
  int amount_vetrex, amount_edges, answer, begin, end;

  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<GraphStorageTopsEdges<Edges_TopsEdges<bool>>>;
      graph_type graph(amount_vetrex);
      CreateGraphfromIfStream<graph_type>(amount_edges, myfile, graph);
      myfile >> begin >> end;
      BFSShortestPathBetweenPair<graph_type> visitor(begin, end, amount_vetrex);
      graph.BFS<BFSShortestPathBetweenPair<graph_type>>(begin, visitor);
      assert((answer == visitor.deep[end]));
    }
    myfile.close();
  }
}

void MakeTestGraph_MatrixNear(const std::string &filename) {
  std::string line;
  std::size_t amount_vetrex, amount_edges;
  int answer, begin, end;

  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<GraphStorageMatrixNear<EdgesWeight_MatrixNear<bool>>>;
      graph_type graph(amount_vetrex);
      CreateGraphfromIfStream<graph_type>(amount_edges, myfile, graph);
      myfile >> begin >> end;
      BFSShortestPathBetweenPair<graph_type> visitor(begin, end, amount_vetrex);
      graph.BFS<BFSShortestPathBetweenPair<graph_type>>(begin, visitor);
      assert((answer == visitor.deep[end]));
    }
    myfile.close();
  }
}

void TestDejkstra_TopEdges(const std::string &filename) {
  std::string line;
  int amount_vetrex, amount_edges, answer, begin, end;

  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<GraphStorageTopsEdges<EdgesWeight_TopsEdges<int>>>;
      graph_type graph(amount_vetrex);
      CreateGraphfromIfStream<graph_type>(amount_edges, myfile, graph);
      myfile >> begin >> end;
      DejkstraVisitor<graph_type> visitor(begin);
      graph.Dejkstra<DejkstraVisitor<graph_type>>(begin, visitor);

      int algo_ans = graph.GetDepth(end);
      if(algo_ans == INT_MAXIMUS) {
        algo_ans = -1;
      }

      std::cerr << "answer = " << answer << " ans = " << algo_ans << "\n";
      assert((answer == algo_ans));
    }
    myfile.close();
  }
  std::cerr << "Tst Dejkstra done" << "\n";
}

void TestLCAUpDouble_TopEdges(const std::string &filename) {
  std::string line;
  int amount_vetrex, amount_edges, answer, begin, end;

  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<GraphStorageTopsEdges<Edges_TopsEdges<bool>>>;
      graph_type graph(amount_vetrex);
      CreateGraphfromIfStream<graph_type>(amount_edges, myfile, graph);
      myfile >> begin >> end;

      int root = 0;
      DFSLCADoubleUp<graph_type> visitor(root, amount_vetrex);
      visitor.BeReadyForLCA(graph);
      int ans = visitor.LSA_with_distance(begin, end, graph);
      assert((answer == ans));
    }
    myfile.close();
  }
}

void TestLCAFrakBender_TopEdges(const std::string &filename) {
  std::string line;
  int amount_vetrex, amount_edges, answer, begin, end;

  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<GraphStorageTopsEdges<Edges_TopsEdges<bool>>>;
      graph_type graph(amount_vetrex);
      CreateGraphfromIfStream<graph_type>(amount_edges, myfile, graph);
      myfile >> begin >> end;

      int root = 0;
      DFSLCAFrakBender<graph_type> visitor(root, amount_vetrex);
      visitor.PreprocessForLCAFrakBender(graph);
      int ans = visitor.GetLCA(begin, end, graph);
      assert((answer == ans));
    }
    myfile.close();
  }
}

void TestDinic_TopEdges(const std::string &filename) {
  std::string line;
  int amount_vetrex, amount_edges, answer, begin, end;

  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<FlowNetworkStorageTopsEdges<EdgesFlow_TopsEdges<long long int>>>;
      graph_type graph(amount_vetrex, true);
      CreateGraphfromIfStream<graph_type>(amount_edges, myfile, graph);
      myfile >> begin >> end;

      int root = 0;
      DFS_BFS_Dinic<graph_type> visitor(begin, end, amount_vetrex);
      int ans = visitor.Dinic(begin, end, graph);

      assert((answer == ans));
    }
    myfile.close();
  }
}

void TestDinic_MatrixNear(const std::string &filename) {
  std::string line;
  int amount_vetrex, amount_edges, answer, begin, end;

  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<FlowNetworkStorageMatrixNear<EdgesFlow_MatrixNear<int>>>;
      graph_type graph(amount_vetrex, true);
      CreateGraphfromIfStream<graph_type>(amount_edges, myfile, graph);
      myfile >> begin >> end;

      int root = 0;
      DFS_BFS_Dinic<graph_type> visitor(begin, end, amount_vetrex);
      int ans = visitor.Dinic(begin, end, graph);

      assert((answer == ans));
    }
    myfile.close();
  }
}

void TestDejkstra_MatrixNear(const std::string &filename) {
  std::string line;
  int amount_vetrex, amount_edges, answer, begin, end;

  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<GraphStorageMatrixNear<EdgesWeight_MatrixNear<int>>>;
      graph_type graph(amount_vetrex);
      CreateGraphfromIfStream<graph_type>(amount_edges, myfile, graph);
      myfile >> begin >> end;
      DejkstraVisitor<graph_type> visitor(begin);
      graph.Dejkstra<DejkstraVisitor<graph_type>>(begin, visitor);
      int algo_ans = graph.GetDepth(end);
      if(algo_ans == INT_MAXIMUS) {
        algo_ans = -1;
      }

      assert((answer == algo_ans));
    }
    myfile.close();
  }
  std::cerr << "Tst Dejkstra done" << "\n";
}

void TestLCA_MatrixNear(const std::string &filename) {
  std::string line;
  int amount_vetrex, amount_edges, answer, begin, end;

  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<GraphStorageTopsEdges<Edges_TopsEdges<bool>>>;
      graph_type graph(amount_vetrex);
      CreateGraphfromIfStream<graph_type>(amount_edges, myfile, graph);
      myfile >> begin >> end;

      int root = 0;
      DFSLCADoubleUp<graph_type> visitor(root, amount_vetrex);
      visitor.BeReadyForLCA(graph);
      int ans = visitor.LSA_with_distance(begin, end, graph);
      assert((answer == ans));
    }
    myfile.close();
  }
}

void TestLoydWarshell_TopEdges(const std::string &filename) {
  std::string line;
  int amount_vetrex, amount_edges, answer, begin, end;
  std::ifstream myfile(filename);

  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << "\n";
      using graph_type = Graph<GraphStorageTopsEdges<EdgesWeight_TopsEdges<int>>>;
      graph_type graph(amount_vetrex);
      CreateGraphfromIfStream<graph_type>(amount_edges, myfile, graph);
      FloydWarshallVisitor<graph_type> visitor(amount_vetrex);
      visitor.FloydWarshell(graph);
      myfile >> begin >> end >> answer;
      do {
        int algo_ans = visitor.GetDist(begin, end);
        if(algo_ans == INT_MAXIMUS) {
          algo_ans = -1;
        }
        std::cerr << answer << "    " << algo_ans << "\n";

        assert((answer == algo_ans));
        myfile >> begin >> end >> answer;
      } while (begin != -1);
    }
    myfile.close();
  }

  std::cerr << "Tst TestLoydWarshell_TopEdges done" << "\n";
}

void TestFordFUlkerson_TopEdges(const std::string &filename) {
  std::string line;
  int amount_vetrex, amount_edges, begin, end;
  double answer;

  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<FlowNetworkStorageTopsEdges<EdgesFlow_TopsEdges<double>>>;
      graph_type graph(amount_vetrex, true);
      CreateGraphfromIfStream<graph_type>(amount_edges, myfile, graph);
      myfile >> begin >> end;

      int root = 0;
      DFSFordFulkerson<graph_type> visitor(begin, end, amount_vetrex);
      double ans = visitor.FordFUlkerson(begin, end, graph);

      std::cerr << "answer = " << answer << " ans = " << ans << "\n";
      assert((answer == ans));
    }
    myfile.close();
  }
}

void TestFordFUlkerson_MatrixNear(const std::string &filename) {
  std::string line;
  int amount_vetrex, amount_edges, answer, begin, end;

  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<FlowNetworkStorageMatrixNear<EdgesFlow_MatrixNear<double>>>;
      graph_type graph(amount_vetrex, true);
      CreateGraphfromIfStream<graph_type>(amount_edges, myfile, graph);
      myfile >> begin >> end;

      int root = 0;
      DFSFordFulkerson<graph_type> visitor(begin, end, amount_vetrex);
      int ans = visitor.FordFUlkerson(begin, end, graph);

      std::cerr << "answer = " << answer << " ans = " << ans << "\n";
      assert((answer == ans));
    }
    myfile.close();
  }
}

void TestAdmondKarp_TopEdges(const std::string &filename) {
  std::string line;
  int amount_vetrex, amount_edges, answer, begin, end;

  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<FlowNetworkStorageTopsEdges<EdgesFlow_TopsEdges<int>>>;
      graph_type graph(amount_vetrex, true);
      CreateGraphfromIfStream<graph_type>(amount_edges, myfile, graph);
      myfile >> begin >> end;

      BFSAdmondKarp<graph_type> visitor(begin, end, amount_vetrex);
      int ans = visitor.AdmondKarp(begin, end, graph);

      std::cerr << "answer = " << answer << " ans = " << ans << "\n";
      assert((answer == ans));
    }
    myfile.close();
  }
}

void TestAdmondKarp_MatrixNear(const std::string &filename) {
  std::string line;
  int amount_vetrex, amount_edges, answer, begin, end;

  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<FlowNetworkStorageMatrixNear<EdgesFlow_MatrixNear<int>>>;
      graph_type graph(amount_vetrex, true);
      CreateGraphfromIfStream<graph_type>(amount_edges, myfile, graph);
      myfile >> begin >> end;

      BFSAdmondKarp<graph_type> visitor(begin, end, amount_vetrex);
      int ans = visitor.AdmondKarp(begin, end, graph);

      assert((answer == ans));
    }
    myfile.close();
  }
}

void TestLoydWarshell_MatrixNear(const std::string &filename) {
  std::string line;
  int amount_vetrex, amount_edges, answer, begin, end;

  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << "\n";
      using graph_type = Graph<GraphStorageMatrixNear<EdgesFlow_MatrixNear<int>>>;
      graph_type graph(amount_vetrex);
      CreateGraphfromIfStream<graph_type>(amount_edges, myfile, graph);
      FloydWarshallVisitor<graph_type> visitor(amount_vetrex);
      visitor.FloydWarshell(graph);
      myfile >> begin >> end  >> answer;
      do {
        assert((answer == visitor.GetDist(begin, end)));
        myfile >> begin >> end  >> answer;
      } while (begin != -1);
    }
    myfile.close();
  }

  std::cerr << "Tst TestLoydWarshell_TopEdges done" << "\n";
}

int main() {
  MakeTestGraph_TopEdges("./tests/ForShortestPath/simple_test.txt");
  MakeTestGraph_MatrixNear("./tests/ForShortestPath/simple_test.txt");

  TestLCAUpDouble_TopEdges("./tests/ForLCA/LCAWitDistance_test.txt");
  TestLCAFrakBender_TopEdges("./tests/ForLCA/LCA_test.txt");

  TestLCA_MatrixNear("./tests/ForLCA/LCAWitDistance_test.txt");

  TestDejkstra_TopEdges("./tests/ForShortestPath/Dejkstra_test.txt");
  TestDejkstra_MatrixNear("./tests/ForShortestPath/Dejkstra_test.txt");

  TestLoydWarshell_TopEdges("./tests/ForShortestPath/LoydWarshell_test.txt");
  TestLoydWarshell_MatrixNear("./tests/ForShortestPath/LoydWarshell_test.txt");

  TestDinic_TopEdges("./tests/ForFlowNetwork/FlowNetwork_test.txt");
  TestDinic_MatrixNear("./tests/ForFlowNetwork/FlowNetwork_test.txt");
  TestFordFUlkerson_TopEdges("./tests/ForFlowNetwork/FlowNetwork_test.txt");
  TestFordFUlkerson_MatrixNear("./tests/ForFlowNetwork/FlowNetwork_test.txt");
  TestAdmondKarp_TopEdges("./tests/ForFlowNetwork/FlowNetwork_test.txt");
  TestAdmondKarp_MatrixNear("./tests/ForFlowNetwork/FlowNetwork_test.txt");

  TestDinic_TopEdges("./tests/ForFlowNetwork/Dinic_test.txt");
  TestDinic_MatrixNear("./tests/ForFlowNetwork/Dinic_test.txt");

  TestFordFUlkerson_TopEdges("./tests/ForFlowNetwork/FordFUlkerson_test.txt");
  TestFordFUlkerson_MatrixNear("./tests/ForFlowNetwork/FordFUlkerson_test.txt");

  TestAdmondKarp_TopEdges("./tests/ForFlowNetwork/AdmondKarp_test.txt");
  TestAdmondKarp_MatrixNear("./tests/ForFlowNetwork/AdmondKarp_test.txt");
}