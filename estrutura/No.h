#include <vector>
#include <utility>

using namespace std;

class No {
public:
    int id; // id do vértice
    vector<pair<int, int>> vizinhos; // <índice do vizinho, peso da aresta>

    No(int id){
        this->id = id;
    }
};
