
all: dirs bin/ut_all

bin/ut_all: test/ut_all.cpp test/node_test.h src/node.h src/file.h src/folder.h
	g++ -std=c++11 test/ut_all.cpp -o bin/ut_all -lgtest -lpthread

clean:
	rm -rf bin obj

dirs:
	mkdir -p bin obj