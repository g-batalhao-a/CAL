Notes

- Objetivo : Otimizar percursos dos veiculos.
- Tipos de veiculos :
  - Camioneta - para levar mais prisioneiros de cada vez 
  - Carro - Para usar em zonas de maior densidade populacional
- Nota : 
  - Pode ocorrer obras na via pública, necessário mudar percurso;
  - Usar mapas reais.
- Prisioneiro : Nome, ID, local de origem, local de destino
- Veiculo : Quantidade que consegue levar, apto para zonas urbanas (bool)

Quais são os pontos (vértices) de interesse aka POI?
  - prisões
  - esquadras
  - tribunais

## Iterações/Estados

Estado inicial:
  - Uma Camioneta para todos os serviços

Estado 2:
  - Diferentes veiculos, capacidades diferentes
  - (Ideia: Destino é mais importante, caso destino seja em cidade, usar carro, else usar camioneta)

Estado 3:
  - Obras na via pública


♦ **Estabelecimento prisional** é uma unidade estrutural-funcional instalada em edificação, dirigida por polícia prisional e respetiva cadeia de comando do Estado, onde cidadãos são colocados e mantidos privados de liberdade, seja por força de ordem de prisão preventiva, em fase de pré-julgamento, seja em cumprimento de pena de prisão a que foram condenados por sentença dum tribunal criminal;

♦ **Penitenciária** é um estabelecimento prisional onde cidadãos cumprem penas de prisão a que foram condenados por sentença dum tribunal criminal;

♦ **Cárcere** é uma cela individual ou coletiva dentro dum estabelecimento prisional. 

♦ **Cárcere privado** é a privação dolosa da liberdade de um cidadão por outro fora de estabelecimento prisional por iniciativa privada, além de certo número de horas – constitui crime punível.

♦ **Prisão** é qualquer uma destas coisas.

in Ciberdúvidas da Língua Portuguesa, https://ciberduvidas.iscte-iul.pt/consultorio/perguntas/estabelecimento-prisional-penitenciaria-carcere-e-prisao/34536 [consultado em 19-04-2020]
___

Info sobre Dijkstra e Traveling Salesman Problem : http://www.gitta.info/Accessibiliti/en/html/unit_Dijkstra.html

```
BiDirectional Dijkstra:
1. Qi.Insert(x1) and mark xi as visited
2. Qg.Insert(xg) and mark xg as visited
3. **while** Qi not empty **and** Qg not empty **do**
4.   **if** Qi not empty
5.     x <- Qi.GetFirst()
6.     **if** x = xg **or** x ∈ Qg
```

Info de BiDir Dijkstra http://planning.cs.uiuc.edu/node50.html

| DIJKSTRA(G, s): // G=(V,E), s in V  | BIDIRECTIONAL DIJKSTRA(G, s): <br> |
|--------------|-----------------|
|     1. **for** each v **in** V do<br>    2. &emsp;dist(v) <- INF<br>    3. &emsp;path(v) <- nil<br>    4. dist(s) <- 0<br>    5. Q <- 0 // min-priority queue<br>    6. INSERT(Q, (s, 0)) // inserts s with key 0<br>    7. **while** Q != 0 do<br>    8. &emsp;v <- EXTRACT-MIN(Q) <br>    9. &emsp;**for** each w **in** Adj(v) do<br>    10.&emsp;&emsp;**if** dist(w) > dist(v) + weight(v,w) **then**<br>    11.&emsp;&emsp;&emsp;dist(w) <- dist(v)+ weight(v,w)<br>    12.&emsp;&emsp;&emsp;path(w) <- v<br>    13.&emsp;&emsp;&emsp;**if** w not in Q **then** <br>    14.&emsp;&emsp;&emsp;&emsp;INSERT(Q, (w, dist(w)))<br>    15.&emsp;&emsp;&emsp;**else**<br>    16.&emsp;&emsp;&emsp;&emsp;DECREASE-KEY(Q, (w, dist(w))) | 1. Qi.Insert(x1) and mark xi as visited<br> 2. Qg.Insert(xg) and mark xg as visited<br> 3. **while** Qi not empty **and** Qg not empt **do** <br> 4.&emsp;**if** Qi not empty <br> 5.&emsp;&emsp;x <- Qi.GetFirst() <br> 6.&emsp;&emsp;**if** x = xg **or** x ∈ Qg <br> 7.&emsp;&emsp;&emsp;&emsp;**return** SUCCESS <br> 8.&emsp;&emsp;**forall** u ∈ U(x) <br> 9. &emsp; &emsp;&emsp;x' <- f(x,u) <br> 10.&emsp;&emsp;&emsp;**if** x' not visited <br> 11.&emsp;&emsp;&emsp;&emsp;Mark x' as visited <br> 12.&emsp;&emsp;&emsp;&emsp;Qi.Insert(x') <br> 13.&emsp;&emsp;&emsp;**else** <br> 14.&emsp;&emsp;&emsp;&emsp;Resolve duplicate x' <br> 15.&emsp;**if** Qg not empty <br> 16.&emsp;&emsp;x' <- Q.GetFirst() <br> 17.&emsp;&emsp;**if** x' = xi **or** x' ∈ Qi <br> 18.&emsp;&emsp;&emsp;&emsp;**return** SUCCESS <br> 19.&emsp;&emsp;**forall** u^(-1) ∈ U^(-1)(x') <br> 20. &emsp; &emsp;&emsp;x <- f^(-1)(x',u^(-1)) <br> 21.&emsp;&emsp;&emsp;**if** x not visited <br> 22.&emsp;&emsp;&emsp;&emsp;Mark x as visited <br> 23.&emsp;&emsp;&emsp;&emsp;Qg.Insert(x) <br> 24.&emsp;&emsp;&emsp;**else** <br> 25.&emsp;&emsp;&emsp;&emsp;Resolve duplicate x <br> 26. **return** FAILURE

Pseudocódigo de A*

https://www.researchgate.net/profile/Peter_Hufnagl/publication/232085273/figure/fig8/AS:214001028997142@1428033229986/A-search-algorithm-Pseudocode-of-the-A-search-algorithm-operating-with-open-and-closed.png

```c++
Input: A Graph G(V, E) with source node start and goal node end.
Output: Least cost path from start to end
Initializitation:
  open_list = {start}                       // List of nodes to be traversed
  closed_list = {}                          // List of already traversed nodes
  g(start) = 0                              // Cost from source node to a node
  h(start) = heuristic_function(start,end)  // Estimated cost from node to goal node
  f(start) = g(start) + h(start)            // Total cost from source to goal node

while open_list is not empty
  m = Node on top of open_list with lowest f 
  if m == end                   // if current note is end node the solution was found
    return success
  remove m from open_list       
  add m to closed_list
  for each n in child(m)        // traverse the child nodes
    if n in closed_list
      continue
    cost = g(m) + distance(m,n)
    if n in open_list and cost < g(n)
      remove n from open_list as new path is betetr
    if n in closed_list and cost < g(n)
      remove n from closed_list
    if n not in open_list and n not in closed_list
      add n to open_list
      g(n) = cost
      h(n) = heuristic_function(n,end)
      f(n) = g(n) + h(n)
return failure
```


```c++
function reconstruct_path(cameFrom, current)
    total_path := {current}
    while current in cameFrom.Keys:
        current := cameFrom[current]
        total_path.prepend(current)
    return total_path

// A* finds a path from start to goal.
// h is the heuristic function. h(n) estimates the cost to reach goal from node n.
function A_Star(start, goal, h)
    // The set of discovered nodes that may need to be (re-)expanded.
    // Initially, only the start node is known.
    // This is usually implemented as a min-heap or priority queue rather than a hash-set.
    openSet := {start}

    // For node n, cameFrom[n] is the node immediately preceding it on the cheapest path from start
    // to n currently known.
    cameFrom := an empty map

    // For node n, gScore[n] is the cost of the cheapest path from start to n currently known.
    gScore := map with default value of Infinity
    gScore[start] := 0

    // For node n, fScore[n] := gScore[n] + h(n). fScore[n] represents our current best guess as to
    // how short a path from start to finish can be if it goes through n.
    fScore := map with default value of Infinity
    fScore[start] := h(start)

    while openSet is not empty
        // This operation can occur in O(1) time if openSet is a min-heap or a priority queue
        current := the node in openSet having the lowest fScore[] value
        if current = goal
            return reconstruct_path(cameFrom, current)

        openSet.Remove(current)
        for each neighbor of current
            // d(current,neighbor) is the weight of the edge from current to neighbor
            // tentative_gScore is the distance from start to the neighbor through current
            tentative_gScore := gScore[current] + d(current, neighbor)
            if tentative_gScore < gScore[neighbor]
                // This path to neighbor is better than any previous one. Record it!
                cameFrom[neighbor] := current
                gScore[neighbor] := tentative_gScore
                fScore[neighbor] := gScore[neighbor] + h(neighbor)
                if neighbor not in openSet
                    openSet.add(neighbor)

    // Open set is empty but goal was never reached
    return failure
```

Retirado do relatório das bicicletas:
## 3.5. Preparar os dados para o GraphViewer
De modo a que o grafo gerado pelo nosso programa tome uma forma aproximada à
forma real deste, foi necessário converter as coordenadas geográficas fornecidas de modo
a satisfazer esta caraterística. Para isso e após alguma pesquisa encontrámos a nossa
resposta em:<br>
https://github.com/pedro-c/CAL-FEUP-EasyPilot/blob/master/src/EasyPilot.cpp<br>
Neste ficheiro estão duas funções que convertem cada uma das coordenadas para
coordenadas cartesianas (x e y). Este código não foi desenvolvido por nós e como tal todo o
crédito vai para o seu autor e dono do repositório Pedro Costa.

## 3.7. Conectividade do grafo
Uma das funções do programa, é testar a conectividade do grafo, aplicando o método
DFS (Depth-First-Search). Nos grafos usados no projeto, não se deu o caso de, com os testes
efetuados, terem encontrado localizações de partilha completamente inatingíveis, apesar de
estas serem geradas de forma aleatória. No entanto, tal como explicado acima, determinados
nós podem ser inalcançáveis se a pesquisa começar num determinado local que apenas parte
para sentidos contrários


Análise entre algoritmos 
Dijkstra, BiDIr Dijkstra, A*,  BiDir A*

bidir dijkstra > dikstra -> ganho em speedup, mais área processada
a* > bidir dijkstra -> ganho em speedup e menos área processada
a* > bidir a* -> poupa espaço com mesmo resultado, sem ganho de speedup

| X             | Dijkstra | A* |
|---------------|--------------------------------------|--------------------------------------|
| Normal        | ![](https://i.imgur.com/hk4TYfe.png) | ![](https://i.imgur.com/M0GOBfp.png) |
| BiDirectional | ![](https://i.imgur.com/0qtlaBd.png) | ![](https://i.imgur.com/SOKOEon.png) |