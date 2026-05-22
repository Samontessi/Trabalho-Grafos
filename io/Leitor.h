#pragma once

#include <string>
#include "../estrutura/Grafo.h"

// classe para ler o arquivo exportado do CSAcademy e preencher a estrutura de Grafo
class Leitor
{
public:
    static bool lerArquivo(const std::string& caminho, Grafo& grafo); // lê o arquivo e preenche o grafo, retornando true se bem-sucedido, false caso contrário
};