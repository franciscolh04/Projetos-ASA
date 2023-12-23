from pulp import *

prob = LpProblem("Base", LpMaximize)

# Recolhe informações iniciais
toys, bundles, var_toys, var_bundles = [], [], [], []
t, p, m = [int(i) for i in input().split()]

# Recolhe brinquedos e respetiva capacidade
for i in range(t):
    toys.append([int(i) for i in input().split()])

# Recolhe pacotes especiais
for i in range(p):
    bundles.append([int(i) for i in input().split()])

# Cria variáveis de decisão: brinquedos e pacotes
for i in range(t):
    temp = LpVariable("x" + str(i + 1), 0, None, cat=LpInteger)
    var_toys.append(temp)
for i in range(p):
    temp = LpVariable("y" + str(i + 1), 0, None, cat=LpInteger)
    var_bundles.append(temp)

# Função Objetivo
prob += lpSum(var_toys[i] * toys[i][0] for i in range(t)) + lpSum(var_bundles[i] * bundles[i][-1] for i in range(p))

# Restrição dos brinquedos e pacotes
for i in range(t):
    exp = var_toys[i]
    for j in range(p):
        if (i + 1) in bundles[j]:
            exp += var_bundles[j]
    prob += exp <= toys[i][1]

# Restrição do número máximo de peças
prob += lpSum(var_toys[i] for i in range(t)) + lpSum(3 * var_bundles[i] for i in range(p)) <= m

prob.solve()
print(int(value(prob.objective)))