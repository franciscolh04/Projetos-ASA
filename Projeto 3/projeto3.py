toys, bundles = [], []
t, p, max = [int(i) for i in input().split()]

for i in range(t):
    toys.append([int(i) for i in input().split()])

for i in range(p):
    bundles.append([int(i) for i in input().split()])
    
print(toys)
print(bundles)