#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Variáveis globais
int _n, _m;
vector<vector<int> > _graph;        // Grafo normal
vector<vector<int> > _graphT;       // Grafo invertido

void readInput() {
    // Recolhe as informações iniciais
    scanf("%d %d", &_n, &_m);

    // Inicialização dos grafos
    _graph.resize(_n + 1);
    _graphT.resize(_n + 1);

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
                // Empilhe vizinhos não visitados e marque-os como visitados
                s.push(neighbor);
                visited[neighbor] = true;
                hasUnvisitedNeighbor = true;
                break;
            }
        }

        if (!hasUnvisitedNeighbor) {
            s.pop();
            st.push(currentNode);  // Empilhe o nó após visitar todos os vizinhos
        }
    }
}

// Realiza procura em profundidade primeiro no grafo transposto
int dfsT(int startNode, vector<bool>& visited, vector<int>& scc) {
    stack<int> s = stack<int>();
    s.push(startNode);
    int jump = 0;
    visited[startNode] = true;

    while (!s.empty()) {
        int currentNode = s.top();
        bool hasUnvisitedNeighbor = false;

        for (int neighbor : _graphT[currentNode]) {
            if (!visited[neighbor]) {
                // Empilhe vizinhos não visitados e marque-os como visitados
                s.push(neighbor);
                visited[neighbor] = true;
                hasUnvisitedNeighbor = true;
                break;
            }
        }

        if (!hasUnvisitedNeighbor) {
            s.pop();
            scc.push_back(currentNode);  // Empilhe o nó após visitar todos os vizinhos
        }
    }

    return jump;
}

// Descobre os SCC do grafo utilizando o Algoritmo de Kosaraju
vector<int> kosaraju() {
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
    // Processa os vértices na ordem da pilha
    while (!st.empty()) {
        int node = st.top();
        st.pop();

        if (!visited[node]) {
            vector<int> scc;
            maxJump = max(maxJump, dfsT(node, visited, scc));
            sccs.push_back(scc);
        }
    }

    printf("Max Jump: %d\n", maxJump);

    // Cria um vetor que indica a SCC a que cada vértice pertence
    vector<int> sccNumber(_n + 1, 0);

    for (int i = 0; i < ((int) sccs.size()); i++) {
        for (int vertex : sccs[i]) {
            sccNumber[vertex] = i + 1;
        }
    }

    return sccNumber;
}

int dfsMaxPath(int node, const vector<int>& sccNumber, vector<bool>& visited) {
    visited[node] = true;
    int maxPath = 0;
    int pathLength;
    
    for (int neighbor : _graph[node]) {
        if (!visited[neighbor]) {
            int neighborSCC = sccNumber[neighbor];

            pathLength = dfsMaxPath(neighbor, sccNumber, visited);

            // Verifica se o vizinho está em uma SCC diferente
            if (sccNumber[node] != neighborSCC) {
                pathLength++;
            }

            maxPath = max(maxPath, pathLength);
        }
    }

    visited[node] = false; // Resetar a marcação após a DFS do vértice
    return maxPath;
}

int covid(const vector<int>& sccNumber) {
    vector<bool> visited(_n + 1, false);
    int maxArcs = 0;

    // Executa a DFS em cada vértice do grafo original
    for (int i = 0; i < _n; i++) {
        if (!visited[i]) {
            int currentArcs = dfsMaxPath(i, sccNumber, visited);
            maxArcs = max(maxArcs, currentArcs);
        }
    }

    return maxArcs;
}

int main() {
    readInput();

    vector<int> sccs = kosaraju();

    int result = covid(sccs);
    printf("%d\n", result);

    return 0;
}