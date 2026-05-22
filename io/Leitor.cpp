#include "Leitor.h"

#include <fstream>
#include <regex>
#include <sstream>
#include <vector>

using namespace std;

namespace
{
    struct ArestaLida
    {
        int origem;
        int destino;
        double peso;
    };

    string lerConteudoArquivo(const string& caminho)
    {
        ifstream arquivo(caminho);

        if (!arquivo.is_open())
            return "";

        stringstream buffer;
        buffer << arquivo.rdbuf();

        return buffer.str();
    }

    int contarVertices(const string& conteudo)
    {
        /*
            O arquivo pode ter labels nos nós e também nas arestas.
            Por isso a contagem precisa ficar restrita ao bloco nodes.
        */
        static const regex blocoNodes(R"REGEX(nodes\s*=\s*\{\[([\s\S]*?)\]\})REGEX");
        static const regex padraoNode(R"REGEX(label\s*:)REGEX");

        smatch matchBloco;

        if (!regex_search(conteudo, matchBloco, blocoNodes))
            return 0;

        string conteudoNodes = matchBloco[1];

        return distance(
            sregex_iterator(conteudoNodes.begin(), conteudoNodes.end(), padraoNode),
            sregex_iterator()
        );
    }

    bool tentarLerPeso(const string& texto, double& peso)
    {
        try
        {
            size_t processados = 0;
            double valor = stod(texto, &processados);

            if (processados != texto.size())
                return false;

            peso = valor;
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    bool extrairArestas(
        const string& conteudo,
        int quantidadeVertices,
        vector<ArestaLida>& arestas
    )
    {
        /*
            Arestas podem vir com campos extras, como label visual.
            Por isso o leitor primeiro isola cada objeto e só depois busca
            source, target e label dentro dele.
        */
        static const regex blocoArestas(R"REGEX(edges\s*=\s*\{\[([\s\S]*?)\]\})REGEX");
        static const regex objetoAresta(R"(\{([^{}]*)\})");

        static const regex campoSource(R"(source\s*:\s*(\d+))");
        static const regex campoTarget(R"(target\s*:\s*(\d+))");
        static const regex campoLabel(R"REGEX(label\s*:\s*"([^"]+)")REGEX");

        smatch matchBloco;

        if (!regex_search(conteudo, matchBloco, blocoArestas))
            return true;

        string conteudoArestas = matchBloco[1];

        for (sregex_iterator it(conteudoArestas.begin(), conteudoArestas.end(), objetoAresta), fim;
             it != fim;
             ++it)
        {
            string objeto = (*it)[1];

            smatch matchSource;
            smatch matchTarget;
            smatch matchLabel;

            if (!regex_search(objeto, matchSource, campoSource) ||
                !regex_search(objeto, matchTarget, campoTarget))
            {
                return false;
            }

            int origem = stoi(matchSource[1]);
            int destino = stoi(matchTarget[1]);

            /*
                source/target fora do intervalo indicam arquivo incompatível
                com a lista de nós encontrada.
            */
            if (origem >= quantidadeVertices || destino >= quantidadeVertices)
                return false;

            double peso = 1.0;

            /*
                O label da aresta é tratado como peso apenas quando for numérico.
                Labels textuais continuam sendo ignorados.
            */
            if (regex_search(objeto, matchLabel, campoLabel))
            {
                double pesoLido;

                if (tentarLerPeso(matchLabel[1], pesoLido))
                    peso = pesoLido;
            }

            arestas.push_back({origem, destino, peso});
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

    vector<ArestaLida> arestas;

    if (!extrairArestas(conteudo, quantidadeVertices, arestas))
        return false;

    /*
        A estrutura só é substituída depois que a leitura termina sem erro.
        Assim, um arquivo inválido não deixa o grafo em estado intermediário.
    */
    grafo.limpar();

    for (int i = 0; i < quantidadeVertices; i++)
        grafo.insereVertice(i);

    for (const ArestaLida& aresta : arestas)
        grafo.insereAresta(aresta.origem, aresta.destino, aresta.peso);

    return true;
}