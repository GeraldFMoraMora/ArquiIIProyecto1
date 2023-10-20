# Compilador de C++ (g++)
CXX = g++

# Banderas de compilación, incluyendo C++11
CXXFLAGS = -std=c++11

# Bibliotecas a enlazar (Google Benchmark y pthread)
LIBS = -lbenchmark -lpthread

# Metricas de rendimiento
PERF_METRICS = cache-misses,L1-dcache-load-misses,LLC-loads,LLC-stores

# Directorio donde se guardarán los resultados
RESULT_DIR = results

# Lista de programas a compilar y ejecutar
PROGRAMS = singleThread directSharing falseSharing noSharingLocal padding

# Compila y ejecuta todos los programas
all: $(PROGRAMS)

# Reglas para compilar y ejecutar los programas
singleThread: single_thread.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)
	mkdir -p $(RESULT_DIR)
	# ./$@ > $(RESULT_DIR)/$@.txt
	perf stat -e $(PERF_METRICS) -o $(RESULT_DIR)/$@_perf.txt ./$@ >> $(RESULT_DIR)/$@.txt

directSharing: direct_sharing.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)
	mkdir -p $(RESULT_DIR)
	# ./$@ > $(RESULT_DIR)/$@.txt
	perf stat -e $(PERF_METRICS) -o $(RESULT_DIR)/$@_perf.txt ./$@ >> $(RESULT_DIR)/$@.txt

falseSharing: false_sharing.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)
	mkdir -p $(RESULT_DIR)
	# ./$@ > $(RESULT_DIR)/$@.txt
	perf stat -e $(PERF_METRICS) -o $(RESULT_DIR)/$@_perf.txt ./$@ >> $(RESULT_DIR)/$@.txt

noSharingLocal: no_sharing.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)
	mkdir -p $(RESULT_DIR)
	# ./$@ > $(RESULT_DIR)/$@.txt
	perf stat -e $(PERF_METRICS) -o $(RESULT_DIR)/$@_perf.txt ./$@ >> $(RESULT_DIR)/$@.txt

padding: padding.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)
	mkdir -p $(RESULT_DIR)
	# ./$@ > $(RESULT_DIR)/$@.txt
	perf stat -e $(PERF_METRICS) -o $(RESULT_DIR)/$@_perf.txt ./$@ >> $(RESULT_DIR)/$@.txt

# Eliminar archivos binarios y carpeta de resultados
clean:
	rm -f $(PROGRAMS)
	rm -rf $(RESULT_DIR)
