from pulp import *

prob = LpProblem("Base", LpMaximize)

# Recolhe informações iniciais
toys, bundles, packs_index, var_toys, var_bundles = [], [], [], [], []
t, p, m = [int(i) for i in input().split()]

# Recolhe brinquedos e respetiva capacidade e cria variáveis de decisão
for i in range(t):
    toys.append([int(i) for i in input().split()])
    packs_index.append([])
    var_toys.append(LpVariable("x" + str(i + 1), 0, None, cat=LpInteger))

# Recolhe pacotes especiais e cria variáveis de decisão
for i in range(p):
    bundles.append([int(i) for i in input().split()])
    [packs_index[bundles[i][j] - 1].append(i) for j in range(3)]
    var_bundles.append(LpVariable("y" + str(i + 1), 0, None, cat=LpInteger))

# Função Objetivo
prob += lpSum(var_toys[i] * toys[i][0] for i in range(t)) + lpSum(var_bundles[i] * bundles[i][-1] for i in range(p))

# Restrição dos brinquedos e pacotes
for i in range(t):
    exp = var_toys[i]
    for j in range(len(packs_index[i])):
        exp += var_bundles[packs_index[i][j]]
    prob += exp <= toys[i][1]

# Restrição do número máximo de peças
prob += lpSum(var_toys[i] for i in range(t)) + lpSum(3 * var_bundles[i] for i in range(p)) <= m

prob.solve(PULP_CBC_CMD(msg=False))
print(int(value(prob.objective)))