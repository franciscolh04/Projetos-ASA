#include <iostream>
#include <vector>

using namespace std;

// Variáveis globais
int _X, _Y, _n;
vector<vector<int> > _values;

void readInput() {
    // Recolhe as informações iniciais e cria matriz de dimensões (X+1, Y+1)
    scanf("%d %d %d", &_X, &_Y, &_n);
    _values = vector< vector<int> > (_X + 1, vector<int>(_Y + 1, 0));

    for (int i = 0; i < _n; i++) {
        int a, b, price;
        // Recolhe informações da peça
        scanf("%d %d %d", &a, &b, &price);

        // Insere o valor da peça na entrada específica da matriz
        if (a <= _X && b <= _Y) {
            _values[a][b] = max(_values[a][b], price);
            if (a <= _Y && b <= _X) { // Verifica se dá para rodar peça
                _values[b][a] = max(_values[b][a], price);
            }
        }
    }
}

int calculateMaxValue() {
    // Percorre cada célula da matriz e calcula o valor máximo
    for(int x = 1; x <= _X; x++) {
        for(int y = 1; y <= _Y; y++) {
            int value1 = 0, value2 = 0;

            // Corta horizontalmente
            for(int j = 1; j <= y; j++) {
                value1 = max(value1, _values[x][j] + _values[x][y - j]);
            }

            // Corta verticalmente
            for(int i = 1; i <= x; i++) {
                value2 = max(value2, _values[i][y] + _values[x - i][y]);
            }

            // Existe uma peça com estas dimensões
            _values[x][y] = max(_values[x][y], max(value1, value2));
        }
    }
    return _values[_X][_Y];
}

int main() {
    readInput();

    int result = calculateMaxValue();
    printf("%d\n", result);

    return 0;
}