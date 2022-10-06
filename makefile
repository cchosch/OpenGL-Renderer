CXX = g++
files = src/main.cpp src/triangle.cpp src/vector.cpp

all: comp

comp: ${files}
	$(CXX) -o main.o $(files) -lglfw -framework OpenGL && ./main.o

