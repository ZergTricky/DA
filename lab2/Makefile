CXXFLAGS+=-std=c++11 -w -O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic -lm
CXX=g++

all: out out/main.o

run: out out/main.o
	./out/main.o

gen: src/gen.cpp
	$(CXX) $^ $(CXXFLAGS) -o gen

stupid: src/stupid.cpp
	$(CXX) $^ $(CXXFLAGS) -o stupid


out/main.o: src/main.cpp src/AVL.h
	$(CXX) $^ $(CXXFLAGS) -o out/main.o

pack:
	zip solution.zip -r Makefile src

out:
	mkdir -p out

clean:
	rm -rf out