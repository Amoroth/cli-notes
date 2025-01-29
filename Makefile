CXX := g++
CXXFLAGS := -I includes/
TARGET := cptsk
SOURCES := src/main.cpp src/task.cpp src/task_store.cpp
OBJECTS := $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGET)
