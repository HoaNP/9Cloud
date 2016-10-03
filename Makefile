OBJECTS = main
all: main

%: %.cc
	g++ -std=c++11 $< -o $@

%: %.c
	gcc $< -o $@

clean:
	rm -f $(OBJECTS)

