from pulp import *

prob = LpProblem("Base", LpMaximize)

# Recolhe informações iniciais
toys, exps = [], []
t, p, m = [int(i) for i in input().split()]
lpSum_obj, lpSum_max = 0, 0

# Recolhe brinquedos e respetiva capacidade e cria variáveis de decisão
for i in range(t):
    toys.append([int(i) for i in input().split()])
    var = LpVariable("x" + str(i + 1), 0, toys[i][1], cat=LpInteger)
    exps.append(var)
    lpSum_obj += var * toys[i][0]
    lpSum_max += var

# Recolhe pacotes especiais e cria variáveis de decisão
for i in range(p):
    pack = [int(j) for j in input().split()]
    var = LpVariable("y" + str(i + 1), 0, None, cat=LpInteger)
    for j in range(3):
        exps[pack[j] - 1] += var
    lpSum_obj += var * pack[-1]
    lpSum_max += 3 * var

# Função Objetivo
prob += lpSum_obj

# Restrição dos brinquedos e pacotes
for i in range(t):
    prob += exps[i] <= toys[i][1]

# Restrição do número máximo de peças
prob += lpSum_max <= m

prob.solve(GLPK(msg=0))
print(int(value(prob.objective)))