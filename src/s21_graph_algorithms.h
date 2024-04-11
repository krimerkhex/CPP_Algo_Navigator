#ifndef S21_GRAPH_ALGORITHMS_H
#define S21_GRAPH_ALGORITHMS_H

#include <list>
#include <vector>

#include "containers/s21_queue.h"
#include "containers/s21_stack.h"
#include "s21_graph.h"

namespace s21 {

struct TsmResult {
  Matrix vertices;
  int distance = 0;
};

class GraphAlgorithms {
 public:
  GraphAlgorithms() = default;
  ~GraphAlgorithms() = default;

  Stack<int> depthFirstSearch(const Graph& graph, const int start_vertex);
  Queue<int> breadthFirstSearch(const Graph& graph, const int start_vertex);
  int getShortestPathBetweenVertices(const Graph& graph, const int vertex1,
                                     const int vertex2);
  Matrix getShortestPathsBetweenAllVertices(const Graph& graph);
  Matrix getLeastSpanningTree(const Graph& graph);
  std::pair<bool, TsmResult> solveTravelingSalesmanProblem(const Graph& graph);

 private:
  void algorithmDijkstra(const Graph& graph, Matrix& valueNodes,
                         const int thisNode);
  int sumMatrix(const Matrix& ma);
  class AntColony;
};

class GraphAlgorithms::AntColony {
 public:
  struct Ant {
    Ant() = default;
    Ant(const int currentPlace);
    Ant(const Ant& queen);
    TsmResult path;
    bool death = false;

    void nextVertices(const int nextPlace, const int distance);
  };
  AntColony(const Graph& Graph, const int startPlace, const int currentPlace,
            const int backPlace, Ant queen, Matrix* mapVertices = nullptr,
            std::vector<TsmResult>* pathDeadlock = nullptr);
  ~AntColony() = default;

  TsmResult makePatch();

 private:
  int currentPlace_;
  int startPlace_;
  int backPlace_;
  const Graph& graph_;
  int sizeGraph_;
  Stack<Ant> ants_;
  Ant queen_;
  std::list<int> vertices_;
  Matrix* mapVertices_;
  std::vector<TsmResult>* pathDeadlock_;

  void antCrusade();
  void exitDeadlock();
  int numberEdges(const int n);
  void sumTsm(TsmResult& thise, const TsmResult other);
  bool checkIsFullPath(const Matrix& path);
  void colonyNotDead(TsmResult& result);
  void colonyDead(TsmResult& result);
};

};  // namespace s21

#endif  // S21_GRAPH_ALGORITHMS_H