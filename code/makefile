CXX = g++
CXXFLAGS = -std=c++11
LIBS = -lbenchmark -lpthread

# Lista de tus programas
PROGRAMS = singleThread directSharing falseSharing noSharingLocal padding

all: $(PROGRAMS)

# Reglas para compilar y ejecutar cada programa
singleThread: single_thread.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)

directSharing: direct_sharing.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)

falseSharing: false_sharing.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)

noSharingLocal: no_sharing.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)

padding: padding.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)

# Limpieza de archivos binarios
clean:
	rm -f $(PROGRAMS)
