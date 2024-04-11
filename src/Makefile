WWW = -Wall -Werror -Wextra -lstdc++ -std=c++17
LIBS = -lgtest

all: s21_console_menu.a
	g++ $(WWW) main.cc s21_console_menu.a -o main.out
	./main.out

s21_graph.a:
	gcc -c containers/s21_matrix.cc s21_graph.cc
	ar rcs s21_graph.a s21_matrix.o s21_graph.o
	ranlib s21_graph.a
	rm -rf *.o

s21_graph_algorithms.a:
	gcc -c containers/s21_matrix.cc s21_graph.cc s21_graph_algorithms.cc
	ar rcs s21_graph_algorithms.a s21_matrix.o s21_graph.o s21_graph_algorithms.o
	ranlib s21_graph_algorithms.a
	rm -rf *.o

s21_console_menu.a:
	gcc -c s21_console_menu.cc s21_graph.cc s21_graph_algorithms.cc containers/s21_matrix.cc
	ar rcs s21_console_menu.a s21_console_menu.o s21_graph.o s21_graph_algorithms.o s21_matrix.o
	ranlib s21_console_menu.a
	rm -rf *.o

test: s21_graph_algorithms.a
	gcc $(WWW) graph_test.cc s21_graph_algorithms.a -o test $(LIBS)
	./test

clean:
	rm -rf *.a
	rm -rf *.o
	rm -rf *.gcno
	rm -rf *.out