#ifndef S21_CONSOLE_MENU_H
#define S21_CONSOLE_MENU_H

#include "s21_graph_algorithms.h"
#include "s21_test.h"

namespace s21 {
class ConsoleMenu {
 public:
  ConsoleMenu() = default;
  ~ConsoleMenu() = default;

  void start();

 private:
  Graph graph_;
  GraphAlgorithms* algorithms_;

  void mainMenu();
  bool choiseMenu();
  void loadGraph();
  void breadthFirstSearch();
  void depthFirstSearch();
  void getShortestPathBetweenVertices();
  void getShortestPathsBetweenAllVertices();
  void getLeastSpanningTree();
  void solveTravelingSalesmanProblem();
  void printGraph();
  void test();
  void errorChoise();
};
};  // namespace s21

#endif  // S21_CONSOLE_MENU_H