#include "s21_graph_algorithms.h"

namespace s21 {
class Tester {
 public:
  Tester() : gA(), graphTest() {}
  ~Tester() = default;
  bool testLoad() {
    graphTest.loadGraphFromFile("graph_10.txt");
    bool result(graphTest.size() == 10);
    graphTest.loadGraphFromFile("graph_0.txt");
    return graphTest.size() == 0 && result;
  }

  bool testExport() {
    graphTest.loadGraphFromFile("graph_10.txt");
    bool result(true);
    try {
      graphTest.exportGraphToDot("graph_export.dot");
    } catch (const std::exception&) {
      result = false;
    }
    return result;
  }

  bool testDepth() {
    graphTest.loadGraphFromFile("graph_10.txt");
    Stack<int> main1(gA.depthFirstSearch(graphTest, 0));
    Stack<int> correct1({1, 2, 5, 3, 4, 6, 7, 8, 9, 10});
    Stack<int> main2(gA.depthFirstSearch(graphTest, 5));
    Stack<int> correct2({6, 1, 2, 5, 3, 4, 7, 8, 9, 10});
    return (main1 == correct1 && main2 == correct2);
  }

  bool testBreadth() {
    graphTest.loadGraphFromFile("graph_10.txt");
    Queue<int> main1(gA.breadthFirstSearch(graphTest, 0));
    Queue<int> correct1({1, 2, 3, 4, 5, 6, 8, 9, 10, 7});
    Queue<int> main2(gA.breadthFirstSearch(graphTest, 5));
    Queue<int> correct2({6, 1, 4, 5, 7, 8, 9, 10, 2, 3});
    return (main1 == correct1 && main2 == correct2);
  }

  bool testShortesPath() {
    graphTest.loadGraphFromFile("graph_10.txt");
    int main(gA.getShortestPathBetweenVertices(graphTest, 0, 9));
    bool result(main == 32);
    main = gA.getShortestPathBetweenVertices(graphTest, 4, 8);
    return result && main == 20;
  }

  bool testShortesPathAll() {
    graphTest.loadGraphFromFile("graph_10.txt");
    Matrix main = gA.getShortestPathsBetweenAllVertices(graphTest);
    Matrix correct(
        10, 10,
        {0,   29,  20, 20, 16, 31, 101, 12, 4,   32, 29, 0,   42, 32, 28,
         44,  111, 21, 33, 41, 20, 42,  0,  15,  14, 27, 81,  23, 23, 27,
         20,  32,  15, 0,  4,  12, 92,  12, 24,  13, 16, 28,  14, 4,  0,
         16,  95,  9,  20, 16, 31, 44,  27, 12,  16, 0,  95,  24, 35, 3,
         101, 111, 81, 92, 95, 95, 0,   90, 104, 98, 12, 21,  23, 12, 9,
         24,  90,  0,  15, 25, 4,  33,  23, 24,  20, 35, 104, 15, 0,  36,
         32,  41,  27, 13, 16, 3,  98,  25, 36,  0});
    return main == correct;
  }

  bool testListSpaningTree() {
    graphTest.loadGraphFromFile("graph_10.txt");
    Matrix main = gA.getLeastSpanningTree(graphTest);
    Matrix correct(
        10, 10,
        {0, 0, 0,  0, 0,  0, 0,  12, 4, 0, 0,  0,  0, 0,  0, 0,  0, 21, 0, 0,
         0, 0, 0,  0, 14, 0, 81, 0,  0, 0, 0,  0,  0, 0,  4, 12, 0, 0,  0, 0,
         0, 0, 14, 4, 0,  0, 0,  9,  0, 0, 0,  0,  0, 12, 0, 0,  0, 0,  0, 3,
         0, 0, 81, 0, 0,  0, 0,  0,  0, 0, 12, 21, 0, 0,  9, 0,  0, 0,  0, 0,
         4, 0, 0,  0, 0,  0, 0,  0,  0, 0, 0,  0,  0, 0,  0, 3,  0, 0,  0, 0});
    return main == correct;
  }

  bool testSalesman() {
    graphTest.loadGraphFromFile("graph_10.txt");
    std::pair<bool, TsmResult> res =
        gA.solveTravelingSalesmanProblem(graphTest);
    return res.second.distance == 282;
  }

 private:
  GraphAlgorithms gA;
  Graph graphTest;
};
};  // namespace s21
