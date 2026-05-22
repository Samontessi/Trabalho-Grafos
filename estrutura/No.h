#pragma once

#include <vector>
#include <utility>

using namespace std;

class No {
public:
    int id; // id do vértice (mantém o invariante id == índice no vetor de vértices)
    vector<pair<int, double>> vizinhos; // <índice do vizinho, peso da aresta>

    No(int id){
        this->id = id;
    }
};
