CXXFLAGS = -std=c++11 -g
LIBS = -lGL -lglut -lGLU
krushkal: ../src/graph-graphics.cpp krushkal.cpp
	$(CXX) $(CXXFLAGS) krushkal.cpp ../src/graph-graphics.cpp -I. -o $@ $(LIBS)