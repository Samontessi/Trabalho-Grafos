#include <iostream>
#include "estrutura/Grafo.cpp"// h" Bugue do vscode/antigravity

using namespace std;

int main() {
    Grafo grafo(false);
    grafo.insereVertice();
    grafo.insereVertice();
    grafo.insereVertice();
    grafo.insereAresta(0, 1, 10);
    grafo.insereAresta(0, 2, 20);
    grafo.insereAresta(1, 2, 30);
    grafo.imprime();
    return 0;
}