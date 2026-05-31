CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic
TARGET = graph_project
SOURCES = main.cpp graph.cpp node.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(TARGET) component_*.txt
