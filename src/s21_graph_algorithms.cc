#include "s21_graph_algorithms.h"

s21::Stack<int> s21::GraphAlgorithms::depthFirstSearch(const Graph& graph,
                                                       const int start_vertex) {
  Stack<int> result;
  if (!graph.empty()) {
    Matrix nodes(graph.size());
    Stack<int> temp;
    temp.push(start_vertex);
    while (!temp.empty()) {
      int nod = temp.pop();
      if (nodes[nod] == 2) continue;
      nodes[nod] = 2;
      for (int i = graph.size() - 1; i >= 0; --i) {
        if (graph(nod, i) > 0) {
          temp.push(i);
        }
      }
      result.push(nod + 1);
    }
  }
  return result;
}

s21::Queue<int> s21::GraphAlgorithms::breadthFirstSearch(
    const Graph& graph, const int start_vertex) {
  Queue<int> result;
  if (!graph.empty()) {
    Matrix nodes(graph.size());
    Queue<int> temp;
    temp.push(start_vertex);
    nodes[start_vertex] = 1;
    while (!temp.empty()) {
      int nod = temp.pop();
      for (int i = 0; i < graph.size(); ++i) {
        if (graph(nod, i) > 0 && nodes[i] == 0) {
          temp.push(i);
          nodes[i] = 1;
        }
      }
      result.push(nod + 1);
    }
  }
  return result;
}

int s21::GraphAlgorithms::getShortestPathBetweenVertices(const Graph& graph,
                                                         const int vertex1,
                                                         const int vertex2) {
  int result = 0;
  if (!graph.empty() && vertex1 < graph.size() && vertex2 < graph.size() &&
      vertex1 != vertex2) {
    Matrix valueNodes(graph.size());
    Matrix nodes(graph.size());
    valueNodes.setMaxValue();
    valueNodes[vertex1] = 0;
    algorithmDijkstra(graph, valueNodes, vertex1);
    result = valueNodes[vertex2];
    if (result == 0) result = -1;
  } else {
    result = -1;
  }
  return result;
}

void s21::GraphAlgorithms::algorithmDijkstra(const Graph& graph,
                                             Matrix& valueNodes,
                                             const int thisNode) {
  Matrix nodes(graph.size());
  for (int i = 0; i < graph.size(); ++i) {
    if (graph(thisNode, i) != 0) {
      int res = valueNodes[thisNode] + graph(thisNode, i);
      if (res < valueNodes[i]) {
        valueNodes[i] = res;
        nodes[i] = 1;
      }
    }
  }
  for (int i = 0; i < nodes.getSize(); ++i)
    if (nodes[i]) algorithmDijkstra(graph, valueNodes, i);
}

s21::Matrix s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(
    const Graph& graph) {
  Matrix result(graph.size(), graph.size());
  if (!graph.empty()) {
    for (int i = 0; i < graph.size(); ++i) {
      Matrix valueNodes(graph.size());
      valueNodes.setMaxValue();
      valueNodes[i] = 0;
      algorithmDijkstra(graph, valueNodes, i);
      result(i, valueNodes);
    }
  }
  return result;
}

s21::Matrix s21::GraphAlgorithms::getLeastSpanningTree(const Graph& graph) {
  Matrix result(graph.size(), graph.size());
  Matrix map(graph.size());
  while (sumMatrix(map) < map.getSize()) {
    int it = 0, jt = 0, value = INT_MAX;
    for (int i = 0; i < graph.size(); ++i) {
      for (int j = 0; j < graph.size(); ++j) {
        if ((map[i] || !i) && !map[j]) {
          int tmp = graph(i, j);
          if (tmp > 0 && tmp < value) {
            it = i;
            jt = j;
            value = tmp;
          }
        }
      }
    }
    result(it, jt) = result(jt, it) = value;
    map[it] = map[jt] = 1;
  }
  return result;
}

int s21::GraphAlgorithms::sumMatrix(const Matrix& ma) {
  int result = 0;
  for (int i = 0; i < ma.getSize(); ++i) {
    result += ma[i];
  }
  return result;
}

std::pair<bool, s21::TsmResult>
s21::GraphAlgorithms::solveTravelingSalesmanProblem(const Graph& graph) {
  Matrix mapVertices(graph.size());
  std::vector<TsmResult> pathDeadlock(graph.size());
  AntColony colony(graph, 0, 0, 0, AntColony::Ant(), &mapVertices,
                   &pathDeadlock);
  TsmResult result = colony.makePatch();
  if (!result.vertices.empty()) {
    result.vertices.reverseSet();
    result.vertices += 1;
  }
  bool error = !result.vertices.empty();
  return std::make_pair(error, result);
}

s21::GraphAlgorithms::AntColony::AntColony(const Graph& Graph,
                                           const int startPlace,
                                           const int currentPlace,
                                           const int backPlace, Ant queen,
                                           Matrix* mapVertices,
                                           std::vector<TsmResult>* pathDeadlock)
    : graph_(Graph),
      startPlace_(startPlace),
      currentPlace_(currentPlace),
      backPlace_(backPlace),
      queen_(queen),
      sizeGraph_(Graph.size()),
      mapVertices_(mapVertices),
      pathDeadlock_(pathDeadlock) {
  if (queen_.path.vertices.empty()) queen_.death = true;
}

s21::GraphAlgorithms::AntColony::Ant::Ant(const int currentPlace) {
  path.vertices.pushBack(currentPlace);
  path.distance = 0;
}

s21::GraphAlgorithms::AntColony::Ant::Ant(const Ant& queen) {
  path.vertices = queen.path.vertices;
  path.distance = queen.path.distance;
}

void s21::GraphAlgorithms::AntColony::Ant::nextVertices(const int nextPlace,
                                                        const int distance) {
  path.vertices.pushBack(nextPlace);
  path.distance += distance;
}

s21::TsmResult s21::GraphAlgorithms::AntColony::makePatch() {
  TsmResult result;
  result.distance = INT_MAX;
  antCrusade();
  if (!ants_.empty()) {
    colonyNotDead(result);
  } else {
    colonyDead(result);
  }
  return result;
}

void s21::GraphAlgorithms::AntColony::antCrusade() {
  if (numberEdges(currentPlace_) < 2 && currentPlace_ != startPlace_) {
    exitDeadlock();
    currentPlace_ = queen_.path.vertices.back();
  }
  for (int i = 0; i < sizeGraph_; ++i) {
    if (graph_(currentPlace_, i) && (*mapVertices_)[i] >= 0) {
      if (!queen_.death) {
        ants_.push(Ant(queen_));
      } else {
        ants_.push(Ant(currentPlace_));
      }
      if (!ants_.top().path.vertices.contain(i)) {
        if ((*mapVertices_)[i] == 1) {
          sumTsm(ants_.top().path, (*pathDeadlock_)[i]);
        } else {
          ants_.top().nextVertices(i, graph_(currentPlace_, i));
        }
      } else {
        ants_.pop();
      }
    }
  }
}

void s21::GraphAlgorithms::AntColony::exitDeadlock() {
  int i = 3;
  (*mapVertices_)[currentPlace_] = -1;
  int z = queen_.path.vertices[-2];
  int sumD = graph_(currentPlace_, z);
  queen_.nextVertices(z, sumD);
  while (numberEdges(z) < 3 && z != startPlace_) {
    (*mapVertices_)[z] = -1;
    int g = queen_.path.vertices[-i];
    int d = graph_(z, g);
    z = g;
    queen_.nextVertices(g, d);
    i += 2;
    sumD += d;
  }
  sumD *= 2;
  Matrix& tmp = queen_.path.vertices;
  Matrix sliceT = tmp.slice(tmp.getSize() - i);
  if ((*mapVertices_)[z] == 1) {
    (*pathDeadlock_)[z].vertices.pushBack(sliceT);
    (*pathDeadlock_)[z].distance += sumD;
  } else {
    (*mapVertices_)[z] = 1;
    TsmResult t{sliceT, sumD};
    (*pathDeadlock_)[z] = t;
  }
}

int s21::GraphAlgorithms::AntColony::numberEdges(const int n) {
  int result = 0;
  for (int i = 0; i<sizeGraph_; result += graph_(n, i++)> 0) {
  }
  return result;
}

void s21::GraphAlgorithms::AntColony::sumTsm(TsmResult& thise,
                                             const TsmResult other) {
  thise.vertices.pushBack(other.vertices);
  thise.distance += other.distance;
}

bool s21::GraphAlgorithms::AntColony::checkIsFullPath(const Matrix& path) {
  bool result = true;
  for (int i = 0; i < sizeGraph_ && result; ++i) {
    result = path.contain(i);
  }
  return result;
}

void s21::GraphAlgorithms::AntColony::colonyNotDead(TsmResult& result) {
  s21::Stack<Ant>::Nodes* an = ants_.getFirst();
  while (an != nullptr) {
    Ant& at = an->data_;
    if (startPlace_ == at.path.vertices.back()) {
      if (result.distance > at.path.distance &&
          checkIsFullPath(at.path.vertices)) {
        result = at.path;
      }
      at.death = true;
    }
    if (!at.death) {
      TsmResult tmp = AntColony(graph_, startPlace_, at.path.vertices.back(),
                                currentPlace_, at, mapVertices_, pathDeadlock_)
                          .makePatch();
      if (result.distance > tmp.distance) result = tmp;
    }
    if (an != ants_.getLast())
      an = an->next_;
    else
      an = nullptr;
  }
}

void s21::GraphAlgorithms::AntColony::colonyDead(TsmResult& result) {
  if (!queen_.death && graph_(currentPlace_, startPlace_)) {
    queen_.nextVertices(startPlace_, graph_(currentPlace_, startPlace_));
    if (queen_.path.distance < result.distance &&
        checkIsFullPath(queen_.path.vertices)) {
      result = queen_.path;
    }
  }
}