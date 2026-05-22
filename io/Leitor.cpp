#include "Leitor.h"

#include <fstream>
#include <regex>
#include <sstream>
#include <vector>

using namespace std;

namespace
{
    string lerConteudoArquivo(const string& caminho)
    {
        ifstream arquivo(caminho);

        if (!arquivo.is_open())
            return "";

        stringstream buffer;
        buffer << arquivo.rdbuf();

        return buffer.str();
    }

    // Conta o número de vértices no conteúdo do arquivo, procurando por padrões que indiquem a presença de vértices.
    int contarVertices(const string& conteudo)
    {
        // O arquivo exportado pode ter metadados aninhados dentro de cada nó.
        static const regex padraoNode(R"(label\s*:\s*\d+)");

        return distance(
            sregex_iterator(conteudo.begin(), conteudo.end(), padraoNode),
            sregex_iterator()
        );
    }

    // Extrai as arestas do conteúdo do arquivo, preenchendo o vetor de arestas.
    // Se alguma aresta referenciar um vértice fora do intervalo encontrado, retorna false para indicar falha.
    bool extrairArestas(
        const string& conteudo,
        int quantidadeVertices,
        vector<pair<int, int>>& arestas
    )
    {
        static const regex padraoAresta(
            R"(\{\s*source\s*:\s*(\d+)\s*,\s*target\s*:\s*(\d+)\s*\})"
        ); // Supondo que o padrao do CSAcademy seja {source: <número>, target: <número>}, com possíveis espaços em branco. O número é capturado em grupos para origem e destino.

        for (sregex_iterator it(conteudo.begin(), conteudo.end(), padraoAresta), fim;
             it != fim;
             ++it)
        {
            int origem = stoi((*it)[1]); // O primeiro grupo captura a origem (source) da aresta.
            int destino = stoi((*it)[2]); // O segundo grupo captura o destino (target) da aresta.

            // Evita arestas que referenciem vértices fora do intervalo encontrado.
            if (origem >= quantidadeVertices || destino >= quantidadeVertices)
                return false;

            arestas.push_back({origem, destino});
        }

        return true;
    }
}


bool Leitor::lerArquivo(const string& caminho, Grafo& grafo)
{
    string conteudo = lerConteudoArquivo(caminho);

    if (conteudo.empty())
        return false;

    int quantidadeVertices = contarVertices(conteudo);

    if (quantidadeVertices == 0)
        return false;

    vector<pair<int, int>> arestas;
    arestas.reserve(quantidadeVertices); // Assume que o número de arestas não deve exceder o número de vértices (caso contrário, o arquivo pode estar mal formatado).

    if (!extrairArestas(conteudo, quantidadeVertices, arestas))
        return false;

    // Limpa o grafo antes de carregar os dados do arquivo, para evitar que dados anteriores interfiram.
    grafo.limpar();

    for (int i = 0; i < quantidadeVertices; i++)
        grafo.insereVertice(i);

    // Aparentemente, o arquivo exportado pelo CSAcademy não inclui pesos nas arestas. Usamos um peso padrão de 1.0.
    for (const pair<int, int>& aresta : arestas)
        grafo.insereAresta(aresta.first, aresta.second, 1.0);

    return true;
}