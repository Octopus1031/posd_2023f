
all: dirs foldIterator.o bin/ut_all

bin/ut_all: test/ut_all.cpp test/node_test.h src/node.h src/file.h src/folder.h src/iterator.h obj/iterator.o
	g++ -std=c++11 test/ut_all.cpp obj/iterator.o -o bin/ut_all -lgtest -lpthread

clean:
	rm -rf bin obj

dirs:
	mkdir -p bin obj

foldIterator.o: src/iterator.h src/iterator.cpp
	g++ -std=c++11 -c src/iterator.cpp -o obj/iterator.o