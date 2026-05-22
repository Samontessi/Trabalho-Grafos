#pragma once

#include "No.h"
#include <vector>

using namespace std;

class Grafo {
    private:
        bool digrafo;
        int numVertices;
        int numArestas;
        vector<No> vertices;

        bool indiceValido(int v) const; // true se v é um índice de vértice existente

    public:
        Grafo(bool digrafo);
        int insereVertice(); // coloca o id do vértice automaticamente, somando 1 ao tamanho do vetor
        void insereVertice(int id); // insere o vértice com um id específico
        void insereAresta(int v1, int v2, double peso); // insere uma aresta entre v1 e v2 com peso
        void removeVertice(int v); // remove o vértice da posicao v e todas as suas arestas
        void removeAresta(int v1, int v2); // remove a aresta entre v1 e v2 (e vice-versa se não for digrafo)
        bool verificaAresta(int v1, int v2); // verifica se existe uma aresta entre v1 e v2
        void alteraPesoAresta(int v1, int v2, double peso); // altera o peso da aresta entre v1 e v2 (e vice-versa se não for digrafo)
        void imprime(); // imprime o grafo
};
