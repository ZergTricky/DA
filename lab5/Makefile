CXXFLAGS+=-std=c++14 -w -O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic -lm
CXX=g++

all: out out/main.o

run: out out/main.o
	./out/main.o

gen: src/gen.cpp
	$(CXX) $^ $(CXXFLAGS) -o out/gen

slow: src/slow.cpp
	$(CXX) $^ $(CXXFLAGS) -o out/slow


out/main.o: src/main.cpp src/SuffixTree.h src/Types.h
	$(CXX) $^ $(CXXFLAGS) -o out/main.o

pack:
	zip solution.zip -r Makefile src

out:
	mkdir -p out

clean:
	rm -rf out