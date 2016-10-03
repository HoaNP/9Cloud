all: hello-cpp-world hello-c-world main demo

%: %.cc
	g++ -std=c++11 $< -o $@

%: %.c
	gcc $< -o $@

