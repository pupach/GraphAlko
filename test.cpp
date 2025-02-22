//
// Created by catboy on 2/19/2025.
//
#include <fstream>
#include <cassert>

#include "test.hpp"
#include "FlowVisitors.hpp"
#include "LCAVisitors.hpp"
#include "ShortestPathVisitors.hpp"

void MakeTestGraph_TopEdges(const std::string &filename) {
  std::string line;
  int amount_vetrex, amount_edges, answer, begin, end;

  int vert_1, vert_2;
  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<GraphStorageTopsEdges<Edges_TopsEdges<bool>>>;
      graph_type graph(amount_vetrex);
      for (std::size_t i = 0; i < amount_edges; i++) {
        myfile >> vert_1 >> vert_2;
        graph.AddEdge(vert_1, vert_2);
      }
      myfile >> begin >> end;
      graph.PrintGraph();
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

  int vert_1, vert_2;
  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<GraphStorageMatrixNear<EdgesWeight_MatrixNear<bool>>>;
      graph_type graph(amount_vetrex);
      for (std::size_t i = 0; i < amount_edges; i++) {
        myfile >> vert_1 >> vert_2;
        graph.AddEdge(vert_1, vert_2);
      }
      myfile >> begin >> end;
      graph.PrintGraph();
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

  int vert_1, vert_2, weight;
  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<GraphStorageTopsEdges<EdgesWeight_TopsEdges<int>>>;
      graph_type graph(amount_vetrex);
      for (std::size_t i = 0; i < amount_edges; i++) {
        myfile >> vert_1 >> vert_2 >> weight;
        graph.AddEdge(vert_1, vert_2, weight);
      }
      myfile >> begin >> end;
      graph.PrintGraph();
      DejkstraVisitor<graph_type> visitor(begin);
      graph.Dejkstra<DejkstraVisitor<graph_type>>(begin, visitor);
      assert((answer == graph.GetDeep(end)));
    }
    myfile.close();
  }
  std::cerr << "Tst Dejkstra done" << "\n";
}

void TestLCAUpDouble_TopEdges(const std::string &filename) {
  std::string line;
  int amount_vetrex, amount_edges, answer, begin, end;

  int vert_1, vert_2;
  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<GraphStorageTopsEdges<Edges_TopsEdges<bool>>>;
      graph_type graph(amount_vetrex);
      for (std::size_t i = 0; i < amount_edges; i++) {
        myfile >> vert_1 >> vert_2;
        graph.AddEdge(vert_1, vert_2);
      }
      myfile >> begin >> end;
      graph.PrintGraph();

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

  int vert_1, vert_2;
  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<GraphStorageTopsEdges<Edges_TopsEdges<bool>>>;
      graph_type graph(amount_vetrex);
      for (std::size_t i = 0; i < amount_edges; i++) {
        myfile >> vert_1 >> vert_2;
        graph.AddEdge(vert_1, vert_2);
      }
      myfile >> begin >> end;
      graph.PrintGraph();

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

  int vert_1, vert_2, cap;
  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<FlowNetworkStorageTopsEdges<EdgesFlow_TopsEdges<int>>>;
      graph_type graph(amount_vetrex, true);
      for (std::size_t i = 0; i < amount_edges; i++) {
        myfile >> vert_1 >> vert_2 >> cap;
        graph.AddEdge(vert_1, vert_2, cap);
      }
      myfile >> begin >> end;
      graph.PrintGraph();

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

  int vert_1, vert_2, cap;
  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<FlowNetworkStorageMatrixNear<EdgesFlow_MatrixNear<int>>>;
      graph_type graph(amount_vetrex, true);
      for (std::size_t i = 0; i < amount_edges; i++) {
        myfile >> vert_1 >> vert_2 >> cap;
        graph.AddEdge(vert_1, vert_2, cap);
      }
      myfile >> begin >> end;
      graph.PrintGraph();

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

  int vert_1, vert_2, weight;
  std::ifstream myfile(filename);

  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<GraphStorageMatrixNear<EdgesWeight_MatrixNear<int>>>;
      graph_type graph(amount_vetrex);
      for (std::size_t i = 0; i < amount_edges; i++) {
        myfile >> vert_1 >> vert_2 >> weight;
        graph.AddEdge(vert_1, vert_2, weight);
      }
      myfile >> begin >> end;
      graph.PrintGraph();
      DejkstraVisitor<graph_type> visitor(begin);
      graph.Dejkstra<DejkstraVisitor<graph_type>>(begin, visitor);
      assert((answer == graph.GetDeep(end)));
    }
    myfile.close();
  }
  std::cerr << "Tst Dejkstra done" << "\n";
}

void TestLCA_MatrixNear(const std::string &filename) {
  std::string line;
  int amount_vetrex, amount_edges, answer, begin, end;

  int vert_1, vert_2;
  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<GraphStorageTopsEdges<Edges_TopsEdges<bool>>>;
      graph_type graph(amount_vetrex);
      for (std::size_t i = 0; i < amount_edges; i++) {
        myfile >> vert_1 >> vert_2;
        graph.AddEdge(vert_1, vert_2);
      }
      myfile >> begin >> end;
      graph.PrintGraph();

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

  int vert_1, vert_2, weight;
  std::ifstream myfile(filename);

  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<GraphStorageTopsEdges<EdgesWeight_TopsEdges<int>>>;
      graph_type graph(amount_vetrex);
      for (std::size_t i = 0; i < amount_edges; i++) {
        myfile >> vert_1 >> vert_2 >> weight;
        graph.AddEdge(vert_1, vert_2, weight);
      }
      graph.PrintGraph();
      FloydWarshallVisitor<graph_type> visitor(amount_vetrex);
      visitor.FloydWarshell(graph);
      myfile >> begin >> end;
      do {
        assert((answer == visitor.GetDist(begin, end)));
        myfile >> begin >> end;
      } while (begin != -1);
    }
    myfile.close();
  }

  std::cerr << "Tst TestLoydWarshell_TopEdges done" << "\n";
}

void TestFordFUlkerson_TopEdges(const std::string &filename) {
  std::string line;
  int amount_vetrex, amount_edges, answer, begin, end;

  int vert_1, vert_2, cap;
  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<FlowNetworkStorageTopsEdges<EdgesFlow_TopsEdges<int>>>;
      graph_type graph(amount_vetrex, true);
      for (std::size_t i = 0; i < amount_edges; i++) {
        myfile >> vert_1 >> vert_2 >> cap;
        graph.AddEdge(vert_1, vert_2, cap);
      }
      myfile >> begin >> end;
      graph.PrintGraph();

      int root = 0;
      DFSFordFulkerson<graph_type> visitor(begin, end, amount_vetrex);
      int ans = visitor.FordFUlkerson(begin, end, graph);

      std::cerr << "answer = " << answer << " ans = " << ans << "\n";
      assert((answer == ans));
    }
    myfile.close();
  }
}

void TestFordFUlkerson_MatrixNear(const std::string &filename) {
  std::string line;
  int amount_vetrex, amount_edges, answer, begin, end;

  int vert_1, vert_2, cap;
  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<FlowNetworkStorageMatrixNear<EdgesFlow_MatrixNear<int>>>;
      graph_type graph(amount_vetrex, true);
      for (std::size_t i = 0; i < amount_edges; i++) {
        myfile >> vert_1 >> vert_2 >> cap;
        graph.AddEdge(vert_1, vert_2, cap);
      }
      myfile >> begin >> end;
      graph.PrintGraph();

      int root = 0;
      DFSFordFulkerson<graph_type> visitor(begin, end, amount_vetrex);
      int ans = visitor.FordFUlkerson(begin, end, graph);

      assert((answer == ans));
    }
    myfile.close();
  }
}

void TestAdmondKarp_TopEdges(const std::string &filename) {
  std::string line;
  int amount_vetrex, amount_edges, answer, begin, end;

  int vert_1, vert_2, cap;
  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<FlowNetworkStorageTopsEdges<EdgesFlow_TopsEdges<int>>>;
      graph_type graph(amount_vetrex, true);
      for (std::size_t i = 0; i < amount_edges; i++) {
        myfile >> vert_1 >> vert_2 >> cap;
        graph.AddEdge(vert_1, vert_2, cap);
      }
      myfile >> begin >> end;
      graph.PrintGraph();

      int root = 0;
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

  int vert_1, vert_2, cap;
  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<FlowNetworkStorageMatrixNear<EdgesFlow_MatrixNear<int>>>;
      graph_type graph(amount_vetrex, true);
      for (std::size_t i = 0; i < amount_edges; i++) {
        myfile >> vert_1 >> vert_2 >> cap;
        graph.AddEdge(vert_1, vert_2, cap);
      }
      myfile >> begin >> end;
      graph.PrintGraph();

      int root = 0;
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

  int vert_1, vert_2, weight;
  std::ifstream myfile(filename);

  if (myfile.is_open()) {
    while (!myfile.eof()) {
      myfile >> amount_vetrex >> amount_edges >> answer;
      std::cerr << "\n" << "amount_vetrex = " << amount_vetrex << " amount_edges = " << amount_edges << " answer = "
                << answer << "\n";
      using graph_type = Graph<GraphStorageMatrixNear<EdgesFlow_MatrixNear<int>>>;
      graph_type graph(amount_vetrex);
      for (std::size_t i = 0; i < amount_edges; i++) {
        myfile >> vert_1 >> vert_2 >> weight;
        graph.AddEdge(vert_1, vert_2, weight);
      }
      graph.PrintGraph();
      FloydWarshallVisitor<graph_type> visitor(amount_vetrex);
      visitor.FloydWarshell(graph);
      myfile >> begin >> end;
      do {
        assert((answer == visitor.GetDist(begin, end)));
        myfile >> begin >> end;
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