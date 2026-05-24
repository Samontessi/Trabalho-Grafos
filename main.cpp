#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>

#include "estrutura/Grafo.h"
#include "Leitor.h"

using namespace std;

// Pergunta uma resposta sim/nao ao usuário.
static bool perguntarSimNao(const string &pergunta)
{
    cout << pergunta << " (s/n): ";
    char resposta;
    cin >> resposta;
    return resposta == 's' || resposta == 'S';
}

// Preenche o grafo lendo os dados do teclado, usando apenas os métodos
// da estrutura (insereVertice / insereAresta).
// O usuário digita apenas as arestas (uma por linha) no formato:
//     origem destino peso
// O peso é opcional (padrão 1.0). A quantidade de vértices é inferida a partir
// do maior id que aparecer nas arestas, então não é preciso informá-la.
static void inserirManualmente(Grafo &grafo)
{
    struct ArestaManual
    {
        int origem;
        int destino;
        double peso;
    };

    cout << "Digite as arestas, uma por linha, no formato: origem destino [peso]\n";
    cout << "(o peso e opcional; padrao 1.0)\n";
    cout << "Encerre com uma linha vazia (ou EOF).\n";
    cout << "Exemplo:\n  0 1 2.5\n  1 2\n\n";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<ArestaManual> arestas;
    int maiorId = -1;

    string linha;
    while (true)
    {
        cout << "> ";
        if (!getline(cin, linha)) // EOF
            break;
        if (linha.empty()) // linha vazia encerra a entrada
            break;

        istringstream iss(linha);
        int origem, destino;
        double peso = 1.0;

        if (!(iss >> origem >> destino))
        {
            cout << "  (entrada invalida, ignorada)\n";
            continue;
        }
        iss >> peso;

        arestas.push_back({origem, destino, peso});
        if (origem > maiorId)
            maiorId = origem;
        if (destino > maiorId)
            maiorId = destino;
    }

    for (int i = 0; i <= maiorId; i++)
        grafo.insereVertice(i);

    // Insere as arestas coletadas
    for (const ArestaManual &a : arestas)
        grafo.insereAresta(a.origem, a.destino, a.peso);
}

static void exibirResumo(Grafo &grafo)
{
    cout << "\nGrafo resultante:\n";
    grafo.imprime();

    cout << "\nResumo:\n";
    cout << "  Vertices: " << grafo.getNumVertices() << "\n";
    cout << "  Arestas:  " << grafo.getNumArestas() << "\n";
    for (int i = 0; i < grafo.getNumVertices(); i++)
        cout << "  Grau do vertice " << i << ": " << grafo.grauVertice(i) << "\n";
    cout << "Ordenacao topologica: \n";
    vector<int> ordem = grafo.ordenacaoTopologica();
    for (int v : ordem)
        cout << v << " ";
    cout << "\n";
}

int main(int argc, char *argv[])
{
    string caminhoArquivo;
    bool orientado = false;
    for (int i = 1; i < argc; i++)
    {
        string arg = argv[i];
        if (arg == "--orientado")
            orientado = true;
        else
            caminhoArquivo = arg;
    }

    // arquivo inserido no run
    if (!caminhoArquivo.empty())
    {
        Grafo grafo(orientado);
        if (!Leitor::lerArquivo(caminhoArquivo, grafo))
        {
            cerr << "Falha ao carregar arquivo.\n";
            return 1;
        }
        cout << "Grafo carregado do arquivo com sucesso.\n";
        exibirResumo(grafo);
        return 0;
    }

    // menu caso não informado
    cout << "=== Trabalho de Grafos ===\n";
    orientado = perguntarSimNao("O grafo eh orientado?");
    Grafo grafo(orientado);

    cout << "\nComo deseja carregar o grafo?\n";
    cout << "  1 - Carregar de arquivo (formato CS Academy)\n";
    cout << "  2 - Inserir manualmente\n";
    cout << "Opcao: ";
    int opcao;
    cin >> opcao;

    if (opcao == 1)
    {
        cout << "Caminho do arquivo: ";
        string caminho;
        cin >> caminho;
        if (!Leitor::lerArquivo(caminho, grafo))
        {
            cerr << "Falha ao carregar arquivo.\n";
            return 1;
        }
        cout << "Grafo carregado do arquivo com sucesso.\n";
    }
    else if (opcao == 2)
    {
        inserirManualmente(grafo);
        cout << "Grafo inserido manualmente com sucesso.\n";
    }
    else
    {
        cerr << "Opcao invalida.\n";
        return 1;
    }

    exibirResumo(grafo);
    return 0;
}
