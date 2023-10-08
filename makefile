
all: bin/ut_all

bin/ut_all: test/ut_all.cpp test/node_test.h
	g++ -std=c++11 -Wfatal-errors -Wall test/ut_all.cpp -o bin/ut -lgtest -lpthread

clean:
	rm -rf bin obj

dirs:
	mkdir -p obj
