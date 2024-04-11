#include "s21_console_menu.h"

void s21::ConsoleMenu::start() {
  while (!choiseMenu())
    ;
}

void s21::ConsoleMenu::mainMenu() {
  std::cout
      << "_____________Algorithms Graph_____________\n"
      << "1. Load graph from file\n"
      << "2. Breadth first traversal of a graph\n"
      << "3. Depth-first graph traversal\n"
      << "4. Finding the shortest path\n"
      << "5. Finding the shortest paths between all\n   pairs of vertices\n"
      << "6. Finding the minimum spanning tree\n"
      << "7. Solving the traveling salesman problem\n"
      << "8. Print graph\n"
      << "0. Exit" << std::endl;
}

bool s21::ConsoleMenu::choiseMenu() {
  bool result = false;
  std::string in;
  mainMenu();
  std::cin >> in;
  if (in.size() == 1) {
    switch (in[0]) {
      case '1':
        loadGraph();
        break;
      case '2':
        breadthFirstSearch();
        break;
      case '3':
        depthFirstSearch();
        break;
      case '4':
        getShortestPathBetweenVertices();
        break;
      case '5':
        getShortestPathsBetweenAllVertices();
        break;
      case '6':
        getLeastSpanningTree();
        break;
      case '7':
        solveTravelingSalesmanProblem();
        break;
      case '8':
        printGraph();
        break;
      case '0':
        result = true;
        break;
      default:
        errorChoise();
        break;
    }
  } else if (in.empty()) {
    result = true;
  } else {
    errorChoise();
  }
  return result;
}

void s21::ConsoleMenu::loadGraph() {
  std::cout << "Enter the path to the file" << std::endl;
  std::string path;
  std::cin >> path;
  graph_.loadGraphFromFile(path);
  if (graph_.empty()) {
    std::cout << "Not correct file or path" << std::endl;
    loadGraph();
  } else {
    std::cout << "Graph loading successful" << std::endl;
  }
}

void s21::ConsoleMenu::breadthFirstSearch() {
  if (graph_.empty()) {
    std::cout << "First download the graph" << std::endl;
  } else {
    std::cout << "Enter a number in the range from 1 to the graph size ("
              << graph_.size() << ")" << std::endl;
    std::string lineIn;
    std::cin >> lineIn;
    int vertex = 0;
    bool error = false;
    try {
      vertex = std::stoi(lineIn);
    } catch (const std::exception& e) {
      error = true;
    }
    error = error || vertex < 0 || vertex >= graph_.size();
    if (error) {
      breadthFirstSearch();
    } else {
      std::cout << "Result of the algorithm:\n"
                << algorithms_->breadthFirstSearch(graph_, vertex - 1)
                << std::endl;
    }
  }
}

void s21::ConsoleMenu::depthFirstSearch() {
  if (graph_.empty()) {
    std::cout << "First download the graph" << std::endl;
  } else {
    std::cout << "Enter a number in the range from 1 to graph size ("
              << graph_.size() << ")" << std::endl;
    std::string lineIn;
    std::cin >> lineIn;
    int vertex = 0;
    bool error = false;
    try {
      vertex = std::stoi(lineIn);
    } catch (const std::exception& e) {
      error = true;
    }
    error = error || vertex < 0 || vertex >= graph_.size();
    if (error) {
      depthFirstSearch();
    } else {
      std::cout << "Result of the algorithm:\n"
                << algorithms_->depthFirstSearch(graph_, vertex - 1)
                << std::endl;
    }
  }
}

void s21::ConsoleMenu::getShortestPathBetweenVertices() {
  if (graph_.empty()) {
    std::cout << "First download the graph" << std::endl;
  } else {
    std::cout << "Enter 2 numbers ranging from 1 to graph size ("
              << graph_.size() << ")" << std::endl;
    std::string lineIn1, lineIn2;
    std::cin >> lineIn1;
    std::cin >> lineIn2;
    int vertex1 = 0, vertex2 = 0;
    bool error = false;
    try {
      vertex1 = std::stoi(lineIn1);
      vertex2 = std::stoi(lineIn2);
    } catch (const std::exception& e) {
      error = true;
    }
    error = error || vertex1 < 0 || vertex1 >= graph_.size() || vertex2 < 0 ||
            vertex2 >= graph_.size();
    if (error) {
      getShortestPathBetweenVertices();
    } else {
      std::cout << "Result of the algorithm:\n"
                << algorithms_->getShortestPathBetweenVertices(
                       graph_, vertex1 - 1, vertex2 - 1)
                << std::endl;
    }
  }
}

void s21::ConsoleMenu::getShortestPathsBetweenAllVertices() {
  if (graph_.empty()) {
    std::cout << "First download the graph" << std::endl;
  } else {
    std::cout << "Result of the algorithm:\n"
              << algorithms_->getShortestPathsBetweenAllVertices(graph_)
              << std::endl;
  }
}

void s21::ConsoleMenu::getLeastSpanningTree() {
  if (graph_.empty()) {
    std::cout << "First download the graph" << std::endl;
  } else {
    std::cout << "Result of the algorithm:\n"
              << algorithms_->getLeastSpanningTree(graph_) << std::endl;
  }
}

void s21::ConsoleMenu::solveTravelingSalesmanProblem() {
  if (graph_.empty()) {
    std::cout << "First download the graph" << std::endl;
  } else {
    std::pair<bool, TsmResult> result(
        algorithms_->solveTravelingSalesmanProblem(graph_));
    if (!result.first) {
      std::cout << "Calculation error" << std::endl;
      mainMenu();
    } else {
      std::cout << "Result of the algorithm:\nAdjacency matrix:\n"
                << result.second.vertices
                << "Distance: " << result.second.distance << std::endl;
    }
  }
}

void s21::ConsoleMenu::printGraph() {
  if (graph_.empty()) {
    std::cout << "The graph is empty" << std::endl;
  } else {
    std::cout << "This graph:\n" << graph_ << std::endl;
  }
}

void s21::ConsoleMenu::errorChoise() {
  std::cout << "Wrong menu item selected" << std::endl;
}