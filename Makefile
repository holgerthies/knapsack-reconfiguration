SRC=$(shell find . -name *.cc)

OBJ=$(SRC:%.cc=%.o)

CXX=clang++ -std=c++11 -Wall -Wextra -O3 -Wshadow -fstack-protector

1:

