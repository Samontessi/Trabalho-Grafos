# Trabalho-Grafos

Projeto em C++ desenvolvido para a disciplina de Teoria dos Grafos.

A implementação suporta grafos orientados e não orientados, com pesos nas arestas.

O objetivo é implementar uma estrutura de grafo usando lista de adjacência, com operações básicas como inserção e remoção de vértices e arestas, consulta de adjacência, cálculo de grau, listagem de vizinhos e alteração de peso das arestas. O projeto também inclui um leitor de arquivos exportados pelo CSAcademy para carregar grafos a partir de um arquivo de entrada.

## Requisitos

- g++
- Make
- C++17

## Formato de entrada

Os arquivos de entrada usados neste trabalho seguem o formato exportado pelo CSAcademy. Os exemplos em [samples/](samples) usam esse formato.

Em resumo, o leitor procura:

- os vértices a partir do bloco `nodes`;
- as arestas a partir de `source` e `target` no bloco `edges`.

O leitor também aceita labels textuais nos vértices e trata `label` numérico nas arestas como peso.

## Estrutura do projeto

- `estrutura/`: implementação do grafo e do nó da lista de adjacência.
- `io/`: leitor responsável por carregar o grafo a partir do arquivo.
- `main.cpp`: programa principal que carrega um grafo e exibe informações básicas.
- `testall.cpp`: bateria de testes usada para validar a implementação.
- `samples/`: arquivos de exemplo de entrada, como `nao_orientado.grafo`, `ponderado.grafo` e `custom_labels.grafo`.

## Compilação

Na raiz do projeto, execute:

```bash
make
```

Isso gera os executáveis em `output/`:

- `output/main`
- `output/testall`

Também é possível rodar a bateria de testes diretamente com:

```bash
make test
```

## Execução

O programa principal recebe o caminho do arquivo e um parâmetro opcional para definir se o grafo deve ser orientado:

```bash
./output/main <arquivo> [--orientado]
```

Exemplos:

```bash
./output/main samples/nao_orientado.grafo
./output/main samples/nao_orientado.grafo --orientado
./output/main samples/ponderado.grafo
./output/main samples/custom_labels.grafo
```

Quando `--orientado` é informado, o grafo é carregado como orientado. Caso contrário, ele é tratado como não orientado.

Para executar a bateria de testes:

## Menu

Para ter acesso ao menu de importação e inserção manual de grafos, assim como as opções de edição do grafo carregado, execute com:

```bash
make run
```

## Limpeza

Para remover os executáveis gerados:

```bash
make clean
```