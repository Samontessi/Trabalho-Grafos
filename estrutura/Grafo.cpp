#include "Grafo.h"
#include <iostream>

Grafo::Grafo(bool digrafo){
    this->digrafo = digrafo;
    this->numVertices = 0;
    this->numArestas = 0;
}

int Grafo::insereVertice(){
    No novoNo(this->numVertices);
    this->vertices.push_back(novoNo);
    this->numVertices++;   
    return this->numVertices - 1; 
}

void Grafo::insereVertice(int id){
    No novoNo(id);
    this->vertices.push_back(novoNo);
    this->numVertices++;
}

void Grafo::insereAresta(int v1, int v2, int peso){
    this->vertices[v1].vizinhos.push_back({v2, peso});
    if(!digrafo){
        this->vertices[v2].vizinhos.push_back({v1, peso});
    }
}

void Grafo::removeVertice(int v){
    this->vertices.erase(this->vertices.begin() + v);
    this->numVertices--;
    for(No &no : this->vertices) {
        for(int i = 0; i < (int)no.vizinhos.size(); i++) {
            if(no.vizinhos[i].first == v){
                no.vizinhos.erase(no.vizinhos.begin() + i);
                i--;
            }
        }
    }
}

void Grafo::removeAresta(int v1, int v2){
    for(int i = 0; i < (int)this->vertices[v1].vizinhos.size(); i++) {
        if(this->vertices[v1].vizinhos[i].first == v2){
            this->vertices[v1].vizinhos.erase(this->vertices[v1].vizinhos.begin() + i);
            break;
        }
    }
    if(!digrafo){
        for(int i = 0; i < (int)this->vertices[v2].vizinhos.size(); i++) {
            if(this->vertices[v2].vizinhos[i].first == v1){
                this->vertices[v2].vizinhos.erase(this->vertices[v2].vizinhos.begin() + i);
                break;
            }
        }
    }
    this->numArestas--;
}

bool Grafo::verificaAresta(int v1, int v2){
    for(int i = 0; i < (int)this->vertices[v1].vizinhos.size(); i++) {
        if(this->vertices[v1].vizinhos[i].first == v2){
            return true;
        }
    }
    return false;
}

void Grafo::alteraPesoAresta(int v1, int v2, int peso){
    for(int i = 0; i < (int)this->vertices[v1].vizinhos.size(); i++) {
        if(this->vertices[v1].vizinhos[i].first == v2){
            this->vertices[v1].vizinhos[i].second = peso;
            break;
        }
    }
    if(!digrafo){
        for(int i = 0; i < (int)this->vertices[v2].vizinhos.size(); i++) {
            if(this->vertices[v2].vizinhos[i].first == v1){
                this->vertices[v2].vizinhos[i].second = peso;
                break;
            }
        }
    }
}

void Grafo::imprime(){
    for(No no : this->vertices) {
        cout << "Vertice " << no.id << ": ";
        for(pair<int, int> vizinho : no.vizinhos) {
            cout << "(" << vizinho.first << ", " << vizinho.second << ") ";
        }
        cout << endl;
    }
}
