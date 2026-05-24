#include "Grafo.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <queue>
Grafo::Grafo(bool digrafo)
{
    this->digrafo = digrafo;
    this->numVertices = 0;
    this->numArestas = 0;
}

// Valida se v é um índice de vértice existente, evitando acessos fora dos limites
bool Grafo::indiceValido(int v) const
{
    return v >= 0 && v < this->numVertices;
}

int Grafo::insereVertice()
{
    No novoNo(this->numVertices);
    this->vertices.push_back(novoNo);
    this->numVertices++;
    return this->numVertices - 1;
}

void Grafo::insereVertice(int id)
{
    No novoNo(id);
    this->vertices.push_back(novoNo);
    this->numVertices++;
}

void Grafo::insereAresta(int v1, int v2, double peso)
{
    if (!indiceValido(v1) || !indiceValido(v2))
        return;

    this->vertices[v1].vizinhos.push_back({v2, peso});
    if (!digrafo)
    {
        this->vertices[v2].vizinhos.push_back({v1, peso});
    }
    this->numArestas++; // conta a aresta lógica uma única vez (orientada ou não)
}

void Grafo::removeVertice(int v)
{
    if (!indiceValido(v))
        return;

    // Atualiza o contador de arestas com base nas arestas incidentes a v
    if (this->digrafo)
    {
        this->numArestas -= (int)this->vertices[v].vizinhos.size(); // arcos de saída
        for (int i = 0; i < this->numVertices; i++)
        { // arcos de entrada
            if (i == v)
                continue;
            for (const pair<int, double> &viz : this->vertices[i].vizinhos)
                if (viz.first == v)
                    this->numArestas--;
        }
    }
    else
    {
        // cada aresta não orientada incidente aparece exatamente uma vez na lista de v
        this->numArestas -= (int)this->vertices[v].vizinhos.size();
    }

    // Remove o vértice do vetor
    this->vertices.erase(this->vertices.begin() + v);
    this->numVertices--;

    // Remove referências a v e reindexa as referências > v, pois os índices
    // dos vértices seguintes deslocaram uma posição para trás
    for (No &no : this->vertices)
    {
        for (int i = 0; i < (int)no.vizinhos.size();)
        {
            if (no.vizinhos[i].first == v)
            {
                no.vizinhos.erase(no.vizinhos.begin() + i);
            }
            else
            {
                if (no.vizinhos[i].first > v)
                    no.vizinhos[i].first--;
                i++;
            }
        }
    }

    // Mantém o invariante id == índice após o deslocamento
    for (int i = 0; i < this->numVertices; i++)
        this->vertices[i].id = i;
}

void Grafo::removeAresta(int v1, int v2)
{
    if (!indiceValido(v1) || !indiceValido(v2))
        return;

    bool removeu = false;
    for (int i = 0; i < (int)this->vertices[v1].vizinhos.size(); i++)
    {
        if (this->vertices[v1].vizinhos[i].first == v2)
        {
            this->vertices[v1].vizinhos.erase(this->vertices[v1].vizinhos.begin() + i);
            removeu = true;
            break;
        }
    }
    if (!digrafo)
    {
        for (int i = 0; i < (int)this->vertices[v2].vizinhos.size(); i++)
        {
            if (this->vertices[v2].vizinhos[i].first == v1)
            {
                this->vertices[v2].vizinhos.erase(this->vertices[v2].vizinhos.begin() + i);
                break;
            }
        }
    }
    if (removeu)
        this->numArestas--; // só decrementa se a aresta realmente existia
}

bool Grafo::verificaAresta(int v1, int v2) const
{
    if (!indiceValido(v1) || !indiceValido(v2))
        return false;

    for (int i = 0; i < (int)this->vertices[v1].vizinhos.size(); i++)
    {
        if (this->vertices[v1].vizinhos[i].first == v2)
        {
            return true;
        }
    }
    return false;
}

void Grafo::alteraPesoAresta(int v1, int v2, double peso)
{
    if (!indiceValido(v1) || !indiceValido(v2))
        return;

    for (int i = 0; i < (int)this->vertices[v1].vizinhos.size(); i++)
    {
        if (this->vertices[v1].vizinhos[i].first == v2)
        {
            this->vertices[v1].vizinhos[i].second = peso;
            break;
        }
    }
    if (!digrafo)
    {
        for (int i = 0; i < (int)this->vertices[v2].vizinhos.size(); i++)
        {
            if (this->vertices[v2].vizinhos[i].first == v1)
            {
                this->vertices[v2].vizinhos[i].second = peso;
                break;
            }
        }
    }
}

void Grafo::imprime()
{
    for (No no : this->vertices)
    {
        cout << "Vertice " << no.id << ": ";
        for (pair<int, double> vizinho : no.vizinhos)
        {
            cout << "(" << vizinho.first << ", " << vizinho.second << ") ";
        }
        cout << endl;
    }
}

int Grafo::grauVertice(int v) const
{
    if (!indiceValido(v))
        return 0;

    // Em grafos orientados, considera o grau de saída,
    // pois a lista de adjacência guarda os arcos que saem do vértice.
    return vertices[v].vizinhos.size();
}

vector<int> Grafo::listarVizinhos(int v) const
{
    vector<int> vizinhos;

    if (!indiceValido(v))
        return vizinhos;

    // Retorna somente os identificadores dos vizinhos,
    // ignorando os pesos armazenados junto às arestas.
    for (const pair<int, double> &vizinho : vertices[v].vizinhos)
        vizinhos.push_back(vizinho.first);

    return vizinhos;
}

bool Grafo::saoAdjacentes(int u, int v) const
{
    // Adjacência é equivalente à existência de aresta de u para v.
    // Em grafo não orientado, a aresta inversa já é inserida na estrutura.
    return verificaAresta(u, v);
}

int Grafo::getNumVertices() const
{
    return this->numVertices;
}

int Grafo::getNumArestas() const
{
    return this->numArestas;
}

void Grafo::limpar()
{
    vertices.clear();

    numVertices = 0;
    numArestas = 0;
}

// Algoritmo de Kahn (BFS).
// Retorna a ordenação topológica dos vértices (por índice).
// Se o grafo contiver um ciclo, ou não for um dígrafo, retorna vetor vazio.
vector<int> Grafo::ordenacaoTopologica() const
{
    // Ordenação topológica só faz sentido em dígrafos.
    if (!digrafo){
        cout << "Não é um dígrafo." << endl;
        return {};
    }
    // 1. Calcula o grau de entrada de cada vértice.
    vector<int> grauEntrada(numVertices, 0);
    for (int i = 0; i < numVertices; i++)
        for (const pair<int, double> &viz : vertices[i].vizinhos)
            grauEntrada[viz.first]++;

    // 2. Enfileira todos os vértices com grau de entrada 0.
    queue<int> fila;
    for (int i = 0; i < numVertices; i++)
        if (grauEntrada[i] == 0)
            fila.push(i);

    // 3. Processa a fila, removendo arestas virtualmente.
    vector<int> ordem;
    ordem.reserve(numVertices);

    while (!fila.empty())
    {
        int i = fila.front();
        fila.pop();
        ordem.push_back(i);

        for (const pair<int, double> &viz : vertices[i].vizinhos)
        {
            int v = viz.first;
            grauEntrada[v]--;
            if (grauEntrada[v] == 0)
                fila.push(v);
        }
    }

    // 4. Se nem todos os vértices foram processados, há um ciclo.
    if ((int)ordem.size() != numVertices){
        cout << "O grafo é cíclico." << endl;
        return {};
    }
    return ordem;
}