#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

struct Piece {
    int length;
    int width;
    int price;

    Piece(int a, int b, int p): length(a), width(b), price(p) {}
};

int _X, _Y, _n;
vector<Piece> *_marblePieces;

void readInput() {
    // Recolhe as informações iniciais
    cin >> _X >> _Y >> _n;
    _marblePieces = new vector<Piece>[_n];

    for(int i = 0; i < _n; i++) {
        int a, b, price;
        // Recolhe informações da peça
        cin >> a >> b >> price;

        // Cria e insere nova peça no vetor de peças
        _marblePieces->emplace_back(a, b, price);
    }

}

int knapsack(int X, int Y, vector<Piece> &pieces) {
    vector< vector<int> > k(X + 1, vector<int>(Y + 1, 0));

    for(int x = 1; x <= X; x++) {
        for(int y = 1; y <= Y; y++) {
            k[x][y] = max(k[x - 1][y], k[x][y - 1]);
            for (int i = 0; i < _n; ++i) {
                // Se a peça já tiver o tamanho certo, associamos o seu valor
                if ((pieces[i].length == x && pieces[i].width == y) ||
                    (pieces[i].width == x && pieces[i].length == y)) {
                    k[x][y] = pieces[i].price;
                }
                else {
                    int value1 = 0, value2 = 0;

                    if((pieces[i].length <= x && pieces[i].width <= y)) { // Sem rotação
                        value1 = max(k[x][pieces[i].width] + k[x][y - pieces[i].width], k[pieces[i].length][y] + k[x - pieces[i].length][y]);
                    }
                    if((pieces[i].width <= x && pieces[i].length <= y)) { // Com rotação
                        value2 = max(k[x][pieces[i].length] + k[x][y - pieces[i].length], k[pieces[i].width][y] + k[x - pieces[i].width][y]);
                    }
                    k[x][y] = max(k[x][y], max(value1, value2));
                }
            }
        }
    }
    
    return k[X][Y];
}

int main() {
    readInput();
    auto start = chrono::high_resolution_clock::now();

    int result = knapsack(_X, _Y, *_marblePieces);
    cout << result << endl;

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Runtime: " << duration.count() << " milliseconds" << endl;

    return 0;
}