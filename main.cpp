#include <iostream>

#include "estrutura/Grafo.h"
#include "Leitor.h"

using namespace std;

int main(int argc, char *argv[])
{

     if (argc < 2)
     {
          cerr << "Uso: " << argv[0] << " <arquivo> [--orientado]\n";
          return 1;
     }

     string caminho = argv[1];
     string opcaoOrientacao = (argc >= 3) ? argv[2] : "";
     bool orientado = (opcaoOrientacao == "--orientado");
     Grafo grafo(orientado);

     if (!Leitor::lerArquivo(caminho, grafo))
     {
          cerr << "Falha ao carregar arquivo.\n";
          return 1;
     }

     cout << "Grafo carregado com sucesso.\n\n";

     grafo.imprime();

     cout << "\nTeste de operacoes:\n";

     for (int i = 0; i < grafo.getNumVertices(); i++)
     {
          cout << "Grau do vertice " << i
               << ": "
               << grafo.grauVertice(i)
               << endl;
     }
     return 0;
}