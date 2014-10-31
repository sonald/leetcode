srcs=$(wildcard *.cc)
objs=$(patsubst %.cc,%,$(wildcard *.cc))
CXX=clang++
CXXFLAGS=-std=c++11

all: $(objs)
	

