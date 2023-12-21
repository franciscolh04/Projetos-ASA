#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Variáveis globais
int _n, _m;
vector<vector<int> > _graph;        // Grafo normal
vector<vector<int> > _graphT;       // Grafo invertido
vector<int> _sccNumberCorrect;      // Vetor das SCCs dos vértices
vector<int> _result;                // Vetor dos resultados

void readInput() {
    // Recolhe as informações iniciais
    scanf("%d %d", &_n, &_m);

    // Inicialização dos grafos
    _graph.resize(_n + 1);
    _graphT.resize(_n + 1);
    _sccNumberCorrect.resize(_n + 1, 0);
    _result.resize(_n + 1, 0);

    for(int i = 0; i < _m; i++) {
        int x, y;
        // Recolhe informações de cada relação
        scanf("%d %d", &x, &y);

        // Adiciona a relação aos grafos
        if (x < _n + 1 && y < _n + 1) {
            _graph[x].push_back(y);
            _graphT[y].push_back(x);
        }
    }
}

// Realiza procura em profundidade primeiro no grafo normal
void dfs(int startNode, vector<bool>& visited, stack<int>& st) {
    stack<int> s = stack<int>();
    s.push(startNode);
    visited[startNode] = true;

    while (!s.empty()) {
        int currentNode = s.top();
        bool hasUnvisitedNeighbor = false;

        for (int neighbor : _graph[currentNode]) {
            if (!visited[neighbor]) {
                s.push(neighbor);
                visited[neighbor] = true;
                hasUnvisitedNeighbor = true;
                break;
            }
        }

        if (!hasUnvisitedNeighbor) {
            s.pop();
            st.push(currentNode);
        }
    }
}

// Realiza procura em profundidade primeiro no grafo transposto e calcula número de saltos
int dfsT(int startNode, vector<bool>& visited, int sccCounter) {
    stack<int> s = stack<int>();
    s.push(startNode);
    int maxResult = 0;
    visited[startNode] = true;
    _sccNumberCorrect[startNode] = sccCounter;
    bool flagStartNode = false;

    while (!s.empty()) {
        int currentNode = s.top();
        bool hasUnvisitedNeighbor = false;

        for (int neighbor : _graphT[currentNode]) {
            if (!visited[neighbor]) {
                s.push(neighbor);
                visited[neighbor] = true;
                hasUnvisitedNeighbor = true;
                break;
            }
        }

        // Achou SCC do vértice atual
        if (!hasUnvisitedNeighbor) {
            // Calcula o número de saltos para o startNode 
            if (!flagStartNode) {
                s.push(startNode);
                flagStartNode = true;
                currentNode = s.top();
            }

            s.pop();
            _sccNumberCorrect[currentNode] = sccCounter;
            // Calcula o número de saltos para os restantes vértices
            if(!s.empty()) {
                for (int neighbor : _graphT[currentNode]) {
                    if (_sccNumberCorrect[currentNode] != _sccNumberCorrect[neighbor] &&
                        _sccNumberCorrect[currentNode] != 0 && _sccNumberCorrect[neighbor] != 0) {
                        _result[currentNode] = max(_result[currentNode],_result[neighbor] + 1);
                    }
                    else {
                        _result[currentNode] = max(_result[neighbor],_result[currentNode]);
                    }
                    maxResult = max(maxResult, _result[currentNode]);
                }
            } 
        }
    }
    return maxResult;
}

// Descobre os SCC do grafo utilizando o Algoritmo de Kosaraju
int kosaraju() {
    vector<bool> visited(_n + 1, false);
    stack<int> st = stack<int>();

    // Executa DFS no grafo original e preenche a pilha
    for (int i = 1; i <= _n; i++) {
        if (!visited[i]) {
            dfs(i, visited, st);
        }
    }

    // Reinicializa vetor de visitados
    fill(visited.begin(), visited.end(), false);

    vector<vector<int> > sccs;
    int maxJump = 0;
    int sccCounter = 0;

    // Processa os vértices na ordem da pilha
    while (!st.empty()) {
        int node = st.top();
        st.pop();

        if (!visited[node]) {
            sccCounter++;
            maxJump = max(maxJump, dfsT(node, visited, sccCounter));
        }
    }

    return maxJump;
}

int main() {
    readInput();

    int result = kosaraju();
    printf("%d\n", result);

    return 0;
}