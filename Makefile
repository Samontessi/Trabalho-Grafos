CXX      = g++
CXXFLAGS = -std=c++17 -Wall
BINDIR   = output

.PHONY: all main testall run test clean

all: $(BINDIR)/main $(BINDIR)/testall

main: $(BINDIR)/main

testall: $(BINDIR)/testall

$(BINDIR):
	mkdir -p $(BINDIR)

$(BINDIR)/main: main.cpp estrutura/Grafo.cpp estrutura/Grafo.h estrutura/No.h io/Leitor.cpp io/Leitor.h | $(BINDIR)
	$(CXX) $(CXXFLAGS) -Iestrutura -Iio main.cpp estrutura/Grafo.cpp io/Leitor.cpp -o $@

$(BINDIR)/testall: testall.cpp estrutura/Grafo.cpp estrutura/Grafo.h estrutura/No.h io/Leitor.cpp io/Leitor.h | $(BINDIR)
	$(CXX) $(CXXFLAGS) -Iestrutura -Iio testall.cpp estrutura/Grafo.cpp io/Leitor.cpp -o $@

run: $(BINDIR)/main
	./$(BINDIR)/main

test: $(BINDIR)/testall
	./$(BINDIR)/testall

clean:
	rm -f $(BINDIR)/main $(BINDIR)/testall
