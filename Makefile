CXX      = g++
CXXFLAGS = -std=c++17 -Wall
BINDIR   = output

$(BINDIR):
	mkdir -p $(BINDIR)

# --- Alvos principais ---

all: $(BINDIR)/main $(BINDIR)/testall

$(BINDIR)/main: main.cpp estrutura/Grafo.cpp estrutura/Grafo.h estrutura/No.h io/Leitor.cpp io/Leitor.h | $(BINDIR)
	$(CXX) $(CXXFLAGS) -Iestrutura -Iio main.cpp estrutura/Grafo.cpp io/Leitor.cpp -o $@

$(BINDIR)/testall: testall.cpp estrutura/Grafo.cpp estrutura/Grafo.h estrutura/No.h io/Leitor.cpp io/Leitor.h | $(BINDIR)
	$(CXX) $(CXXFLAGS) -Iestrutura -Iio testall.cpp io/Leitor.cpp -o $@

# --- Atalhos de execução ---

run: $(BINDIR)/main
	./$(BINDIR)/main

test: $(BINDIR)/testall
	./$(BINDIR)/testall

# --- Limpeza ---

clean:
	rm -f $(BINDIR)/main $(BINDIR)/testall

.PHONY: all run test clean
