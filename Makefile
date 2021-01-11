CXX = g++
CXXFLAGS += -I /usr/include/boost
CXXFLAGS += -g -std=c++17 -Wall -Wextra -pedantic-errors
SOURCES := $(shell find . -name '*.cpp')
HEADERS := $(shell find . -name '*.h')

OUTPUT := bin/main

$(OUTPUT): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(SOURCES)

clean:
	rm $(OUTPUT)

run:
	make && ./bin/main