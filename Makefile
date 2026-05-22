CXX      = g++
CXXFLAGS = -std=c++17 -Wall
BINDIR   = output

# --- Alvos principais ---

all: $(BINDIR)/main $(BINDIR)/testall

$(BINDIR)/main: main.cpp estrutura/Grafo.cpp estrutura/Grafo.h estrutura/No.h
	$(CXX) $(CXXFLAGS) main.cpp -o $@

$(BINDIR)/testall: testall.cpp estrutura/Grafo.cpp estrutura/Grafo.h estrutura/No.h
	$(CXX) $(CXXFLAGS) testall.cpp -o $@

# --- Atalhos de execução ---

run: $(BINDIR)/main
	./$(BINDIR)/main

test: $(BINDIR)/testall
	./$(BINDIR)/testall

# --- Limpeza ---

clean:
	rm -f $(BINDIR)/main $(BINDIR)/testall

.PHONY: all run test clean
