CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
LIBS = -lole32 -luuid
TARGET = main.exe

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	del /Q $(TARGET) $(OBJ) 2>NUL

.PHONY: all run clean
