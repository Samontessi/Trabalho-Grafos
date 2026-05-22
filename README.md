# Trabalho-Grafos

Projeto em C++ desenvolvido para a disciplina de Teoria dos Grafos.

O objetivo é implementar uma estrutura de grafo usando lista de adjacência, com operações básicas como inserção e remoção de vértices e arestas, consulta de adjacência, cálculo de grau, listagem de vizinhos e alteração de peso das arestas. O projeto também inclui um leitor de arquivos exportados pelo CSAcademy para carregar grafos a partir de um arquivo de entrada.

## Formato de entrada

Os arquivos de entrada usados neste trabalho seguem o formato exportado pelo CSAcademy. O arquivo [samples/teste.grafo](samples/teste.grafo) é um exemplo desse formato.

Em resumo, o leitor procura:

- a lista de vértices em `nodes`, usando os campos `label`;
- a lista de arestas em `edges`, usando os campos `source` e `target`.

Esse formato é suficiente para carregar o grafo no programa principal e para executar a bateria de testes fornecida.

## Estrutura do projeto

- `estrutura/`: implementação do grafo e do nó da lista de adjacência.
- `io/`: leitor responsável por carregar o grafo a partir do arquivo.
- `main.cpp`: programa principal que carrega um grafo e exibe informações básicas.
- `testall.cpp`: bateria de testes usada para validar a implementação.
- `samples/`: arquivos de exemplo de entrada.

## Compilação

Na raiz do projeto, execute:

```bash
make
```

Isso gera os executáveis em `output/`:

- `output/main`
- `output/testall`

## Execução

O programa principal recebe o caminho do arquivo e um parâmetro opcional para definir se o grafo deve ser orientado:

```bash
./output/main <arquivo> [--orientado]
```

Exemplos:

```bash
./output/main samples/teste.grafo
./output/main samples/teste.grafo --orientado
```

Quando `--orientado` é informado, o grafo é carregado como orientado. Caso contrário, ele é tratado como não orientado.

Para executar a bateria de testes:

```bash
./output/testall
```

## Limpeza

Para remover os executáveis gerados:

```bash
make clean
```