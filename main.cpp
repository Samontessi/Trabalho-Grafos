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
    cout << "\nOrdenacao topologica: \n  ";
    vector<int> ordem = grafo.ordenacaoTopologica();
    for (int v : ordem)
        cout << v << " ";
    cout << "\n";
}

// Menu interativo para editar o grafo já carregado, expondo as operações
// obrigatórias da estrutura. Usa apenas métodos públicos da classe Grafo;
// não altera o Leitor nem a estrutura. Roda em laço até o usuário escolher sair.
static void menuEdicao(Grafo &grafo)
{
    int opcao = -1;
    while (opcao != 0)
    {
        cout << "\n=== Menu de edicao do grafo ===\n";
        cout << "  1 - Inserir vertice\n";
        cout << "  2 - Remover vertice\n";
        cout << "  3 - Inserir aresta\n";
        cout << "  4 - Remover aresta\n";
        cout << "  5 - Alterar peso de aresta\n";
        cout << "  6 - Verificar existencia de aresta\n";
        cout << "  7 - Grau de um vertice\n";
        cout << "  8 - Listar vizinhos de um vertice\n";
        cout << "  9 - Verificar se dois vertices sao adjacentes\n";
        cout << " 10 - Exibir grafo\n";
        cout << " 11 - Ordenacao topologica\n";
        cout << "  0 - Sair\n";
        cout << "Opcao: ";

        if (!(cin >> opcao)) // entrada invalida ou EOF encerra o menu
            break;

        switch (opcao)
        {
        case 1:
        {
            int id = grafo.insereVertice(); // id automatico (proximo indice)
            cout << "Vertice " << id << " inserido.\n";
            break;
        }
        case 2:
        {
            int v;
            cout << "Indice do vertice a remover: ";
            cin >> v;
            grafo.removeVertice(v);
            cout << "Operacao concluida (os vertices podem ter sido reindexados).\n";
            break;
        }
        case 3:
        {
            int u, v;
            double peso;
            cout << "origem destino peso: ";
            cin >> u >> v >> peso;
            grafo.insereAresta(u, v, peso);
            cout << "Operacao concluida.\n";
            break;
        }
        case 4:
        {
            int u, v;
            cout << "origem destino: ";
            cin >> u >> v;
            grafo.removeAresta(u, v);
            cout << "Operacao concluida.\n";
            break;
        }
        case 5:
        {
            int u, v;
            double peso;
            cout << "origem destino novo_peso: ";
            cin >> u >> v >> peso;
            grafo.alteraPesoAresta(u, v, peso);
            cout << "Operacao concluida.\n";
            break;
        }
        case 6:
        {
            int u, v;
            cout << "origem destino: ";
            cin >> u >> v;
            cout << (grafo.verificaAresta(u, v) ? "Existe aresta.\n" : "Nao existe aresta.\n");
            break;
        }
        case 7:
        {
            int v;
            cout << "vertice: ";
            cin >> v;
            cout << "Grau: " << grafo.grauVertice(v) << "\n";
            break;
        }
        case 8:
        {
            int v;
            cout << "vertice: ";
            cin >> v;
            vector<int> vizinhos = grafo.listarVizinhos(v);
            cout << "Vizinhos: ";
            for (int x : vizinhos)
                cout << x << " ";
            cout << "\n";
            break;
        }
        case 9:
        {
            int u, v;
            cout << "vertice1 vertice2: ";
            cin >> u >> v;
            cout << (grafo.saoAdjacentes(u, v) ? "Sao adjacentes.\n" : "Nao sao adjacentes.\n");
            break;
        }
        case 10:
            cout << "\nGrafo atual:\n";
            grafo.imprime();
            break;
        case 11:
        {
            vector<int> ordem = grafo.ordenacaoTopologica();
            if (!ordem.empty()) // se vazio, ordenacaoTopologica ja imprimiu o motivo
            {
                cout << "Ordenacao topologica: ";
                for (int v : ordem)
                    cout << v << " ";
                cout << "\n";
            }
            break;
        }
        case 0:
            cout << "Saindo do menu de edicao.\n";
            break;
        default:
            cout << "Opcao invalida.\n";
            break;
        }
    }
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

    // No modo interativo, mostra o grafo carregado e abre o menu de edicao.
    cout << "\nGrafo inicial:\n";
    grafo.imprime();
    menuEdicao(grafo);
    return 0;
}
