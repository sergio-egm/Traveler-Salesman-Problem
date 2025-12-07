import numpy as np
import matplotlib.pyplot as plt

import networkx as nx

cities = np.loadtxt("dat/cities.dat")
paths  = np.loadtxt("dat/paths.dat" , dtype = int)

def plot(G , labels = True):
    draw_options = {
        "font_size": 20,
        "node_size": 1000,
        "node_color": "white",
        "edgecolors": "black",
        "linewidths": 5,
        "width": 5,
        "with_labels" : True ,
        "pos" : cities
    }

    nx.draw(G , **draw_options)

    # Calcola e disegna etichette con le distanze (solo i parametri corretti)
    edge_labels = {}
    if labels:
        for (u, v) in G.edges():
            dist = np.linalg.norm(cities[u] - cities[v])
            edge_labels[(u, v)] = f"{dist:.2f}"

    # Solo questi parametri sono ammessi qui:
    nx.draw_networkx_edge_labels(G, pos=cities, edge_labels=edge_labels, font_size=10)

    plt.xlim(0, 1)
    plt.ylim(-0.1, 1)
    plt.tight_layout()

plt.title("Fully Connected Graph" , fontsize = 20)
G = nx.Graph()
G.add_nodes_from([i for i in range(len(cities))])

bf = paths[0]
mst = paths[1]

cost1 , cost2 = (0,0)

for n1 in G.nodes:
    for n2 in G.nodes:
        if n1 == n2:
            continue

        G.add_edge(n1,n2)

plot(G , False)

G.clear_edges()

plt.figure()

plt.title("Brute Force" , fontsize = 20)

for i in range(len(bf)):
    G.add_edge(bf[i],bf[i-1])
    cost1 += np.sqrt(np.sum((cities[bf[i]]-cities[bf[i-1]])**2))

print(f"Exact Result = {cost1:.2f}")

plot(G)


G.clear_edges()
plt.figure()
plt.title("MST Approximation" , fontsize = 20)

for i in range(len(mst)):
    G.add_edge(mst[i],mst[i-1])
    cost2 += np.sqrt(np.sum((cities[mst[i]]-cities[mst[i-1]])**2))

print(f"Approximation = {cost2:4.2f}")

plot(G)

G.clear_edges()
plt.figure()
plt.title("MST - Prim's Algorithm" , fontsize = 20)

for e in np.loadtxt("dat/edges.dat" , dtype = int):
    G.add_edge(e[0],e[1])

plot(G)

print(f"Deviation = {(cost2/cost1-1)*100:4.2f} %")

print()

plt.show()
