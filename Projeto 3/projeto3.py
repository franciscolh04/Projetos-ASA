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

# Cria variáveis de decisão
for i in range(t):
    temp = LpVariable("x" + str(i + 1), 0, toys[i][1], cat=LpInteger)
    var_toys.append(temp)

# Cria pacotes
for i in range(p):
    temp = LpVariable("y" + str(i + 1), 0, bundles[i][-1], cat=LpInteger)
    var_bundles.append(temp)

# Função Objetivo
prob += lpSum(var_toys[i] * toys[i][0] for i in range(t)) + lpSum(var_bundles[i] * bundles[i][-1] for i in range(p))

# Restrições das variáveis de decisão
for i in range(t):
    prob += var_toys[i] <= toys[i][1]

'''
print(toys)
print(bundles)
print(var_toys)
print(var_bundles)
'''

# Restrição dos pacotes
for i in range(p):
    prob += var_toys[bundles[i][0] - 1] + var_bundles[i] <= toys[bundles[i][0] - 1][1]
    prob += var_toys[bundles[i][1] - 1] + var_bundles[i] <= toys[bundles[i][1] - 1][1]
    prob += var_toys[bundles[i][2] - 1] + var_bundles[i] <= toys[bundles[i][2] - 1][1]
    prob += var_bundles[i] <= var_toys[bundles[i][0] - 1]
    prob += var_bundles[i] <= var_toys[bundles[i][1] - 1]
    prob += var_bundles[i] <= var_toys[bundles[i][2] - 1]

# Restrição do número máximo de peças
prob += lpSum(var_toys[i] for i in range(t)) + 3 * lpSum( var_bundles[i] for i in range(p)) <= m

prob.solve()

print(int(value(prob.objective)))

