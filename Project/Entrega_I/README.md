# Relatório - Projeto de Concepção e Análise de Algoritmos
## Meat Wagons (Tema 8) - Parte 1
### Turma 3 - Grupo 1
### André Gomes - up201806224@fe.up.pt
### Gonçalo de Batalhão Alves - up201806451@fe.up.pt
### Pedro Jorge Fonseca Seixas - up201806227@fe.up.pt

<div style="page-break-after: always;"></div>

## Descrição do Tema
Um estabelecimento prisional necessita de gerir o transporte dos seus prisioneiros entre diferentes penitenciárias, tribunais, estabelecimentos prisionais ou esquadras policiais, tendo ao seu dispor diferentes veículos e sendo preciso ter em conta: prisioneiros com o mesmo destino, propriedades do destino para escolher o veículo e planeamento de rotas.

O objetivo é desenvolver um programa que calcule, para o dia, as rotas a tomar para cada veículo da frota tendo em conta os destinos do dia para a lista de prisioneiros.

Nesta fase inicial o projeto encontra-se dividido em 3 fases.

### Fase 1 : Um veículo para todos os prisioneiros
Tendo uma lista dos prisioneiros, e sabendo para cada um o seu destino, o objetivo desta primeira parte é ter um autocarro, com capacidade ilimitada, que passe por todos os POI designados para cada prisioneiro, tendo em conta o caminho mais curto que passe em todos os POI e que depois retorne para a origem.
Certas vias podem ser inacessíveis por razões diversas (obras, cortes de estrada, largura de rua não ser suficiente). Assim, durante o processamento do grafo, será necessário desprezar certas arestas.

### Fase 2 : Diferentes Veículos, capacidade ilimitada
Nesta fase cada Vértice do Grafo terá a informação extra sobre a sua Densidade Populacional (Cidade, Periferia ou Campo). Os prisioneiros serão previamente divididos pelos Veículos, tendo em conta o seu destino, e cada veiculo estará especializado para uma Densidade Populacional. Começaremos por ter uma camioneta (Campo e Periferia) e um carro (Cidade), ambos com capacidade ilimitada, para testar a divisão dos prisioneiros e a formulação de rotas.

### Fase 3 : Mais veículos, capacidade limitada
Na fase final, teremos uma frota de veículos com capacidade limitada e um conjunto de prisioneiros com o seu destino. A leitura de dados inicial será para o dia, ou seja, ao executar o programa ficam em memória os prisioneiros, com o seu destino, e a frota disponível. Caso toda a frota esteja ocupada e ainda sobrarem prisioneiros, tendo em conta o seu destino, serão retornados para a origem os veiculos necessários para refazer rotas e os transportarem.

## Possíveis Problemas a Encontrar
- Leitura dos mapas provenientes do Open Street Maps
- Peso das arestas do grafo
- Conversão dos dados de modo a possibilitar a utilização do GraphViewer 
- Cruzamento de ruas com o mesmo nome 
- Acentuação nos nomes das ruas 
- Nos ficheiros de mapas não são disponibilizadas tags referentes a tribunais ou estabelecimentos prisionais
- Distribuição de tag densidade populacional pelos vértices do grafo 

<div style="page-break-after: always;"></div>

## Formalização do Problema
### Dados de Entrada
Pi - Lista de prisioneiros com destinos para o dia, sendo P(i) o i-nésimo elemento, cada um é caracterizado por:
- ID - número identificador de prisioneiro
- Destino - Identificador de Destino

O número identificador de destino terá duas partes: a primeira parte, de 1 dígito, é correspondente ao tipo de destino; a segunda parte, com numero de dígitos variavel, é correspondente ao ID do node de destino. Como exemplo: Um tribunal poderá ter um Destino de 1000001 enquanto que um estabelecimento prisional poderá ter um Destino de 2000001.

Fi - Lista de veiculos da frota, sendo F(i) o i-nésimo elemento, cada um é caracterizado por:
- ID - número identificador do veículo (tal como em Destino, será um número que terá implicito o tipo de veiculo)
- cap - número de assentos destinados a prisioneiros

Gi = (Vi, Ei) - Grafo Dirigido Pesado (Dirigido -> sentido da rua|Pesado -> Distância entre vértices)
- V - vértices representativos de pontos da cidade com:
  - ID do Node - retirado do ficheiro de nós fornecidos pelos mapas
  - tag - Penitenciária, tribunal, esquadra policial ou estabelecimento prisional (cada um terá um ID igual a Destino)(Caso não seja nenhum desses, ID = 0)
  - DP - Informação sobre densidade populacional (Cidade, Periferia ou Campo)
  - Adj ⊆ E ‐ conjunto de arestas que partem do vértice
- E - arestas representativas das vias de comunicação
  - w - peso da aresta (representa a distância entre os dois vértices que a delimitam)
  - ID - identificador único da aresta
  - dest ∈ Vi ‐ vértice de destino
  
S ∈ Vi ‐ vértice inicial (Estabelecimento prisional)

T ⊆ Vi ‐ vértices finais (Destinos)


### Dados de Saída

Gf = (Vf,Ef) grafo dirigido pesado, tendo Vf e Ef os mesmos atributos que Vi e Ei.

Ff‐ Lista ordenada de todos os veículos usados, sendo Ff(i) o seu i‐nésimo elemento.
Cada um tem os seguintes valores:
- cap ‐ número de assentos utilizados
- I - Lista de *Inmates* que o veículo transportará por ordem de paragem. 
- P = {e ∈ Ei | 1 ≤ j ≤ |P|} ‐ sequência ordenada (com repetidos) de arestas a visitar, sendo ej o seu j‐ésimo elemento.


### Restrições
#### Sobre os Dados de entrada
- ∀ i ∈ [1 ; |Fi| ], cap(Fi[i]) > 0, dado que uma capacidade representa os assentos disponiveis.
- ∀ v ∈ Vi, tag ≥ 0;
- ∀ e ∈ Ei, w > 0, dado que o peso de uma aresta representa uma distância entre
pontos de um mapa.
- ∀ e ∈ Ei, e deve ser utilizável pelo elemento da frota. Senão, não é incluída no grafo Gi.

#### Sobre os Dados de Saída
No grafo Gf:
- ∀ vf ∈ Vf, ∃ vi ∈ Vi tal que vi e vf têm os mesmos valores para todos os atributos
- ∀ ef ∈ Ef, ∃ ei ∈ Ei tal que ei e ef têm os mesmos valores para todos os atributos.

#### Funções Objetivo
É possível determinar trÊs funcões objetivo para o nosso projeto, as quais apresentamos por ordem de prioridade:<br> 
Diminuir a distância total percorrida pela frota, que será a soma dos valores das arestas percorridas por cada veículo; Diminuir o tempo de execução do cálculo das rotas; Diminuir o número de veículos da frota usados
1. ∑ dos valores das arestas percorridas pelos elementos da frota
2. ∑ tempos de execução dos algoritmos
3. h = |Ff|

## Perspetiva de solução
### Fase 1
Esta primeira fase terá vários passos referentes à preparação do ambiente de trabalho, começando pela:

#### 1. Preparação dos ficheiros de entrada
Serão utilizados os ficheiros de nodes e edges fornecidos pelos professores. A informação lida dos ficheiros será guardada num grafo G. Será criada uma tag para cada tipo de edifício de interesse (prisões, esquadras e tribunais) de forma a facilitar a identificação dos pontos de interesse.

<div style="page-break-after: always;"></div>

#### 2. Análise da Conectividade do Grafo
Para certificar que haverá um caminho de retorno para qualquer rota calculada o grafo terá de ter uma componente fortemente conexa. Para fazer essa avaliação num grafo dirigido pesado será preciso seguir o método fornecido nas aulas teóricas:

>**Método**
>- Pesquisa em profundidade no grafo G determina floresta de expansão, numerando vértices em pós-ordem (ordem inversa de numeração em pré-ordem)
>- Inverter todas as arestas de G (grafo resultante é Gr)
>- Segunda pesquisa em profundidade, em Gr, começando sempre pelo vértice de numeração mais alta ainda não visitado
>- Cada árvore obtida é um componente fortemente conexo, i.e., a partir de um qualquer dos nós pode chegar-se a todos os outros

Com recurso a uma Pesquisa em Profundidade, é possível verificar se de facto há um caminho de ida entre o ponto de origem e o destino e um caminho de volta para o estabelecimento prisional original.

#### 3. Criação de POI's
Após a leitura dos ficheiros com os nodes e edges, serão lidos os ficheiros das tags de forma a identificar os pontos de interesse, alterando, para esse node, a sua variável *tag*, inicializada a 0, para o seu valor correspondente ao tipo de ponto de interesse.

No ficheiro de tags disponibilizado não existem tags referentes ao nosso tema, tendo isso em mente, será necessário obter os nós referentes a prisões, tribunais e esquadras.
Após alguma pesquisa sobre como obter essa informação, percebemos que a melhor forma seria através da ferramenta disponível no site https://overpass-turbo.eu/. Esta ferramenta permite o acesso à informação do OpenStreetMap em formato json.

Foram utilizadas as seguintes querys para esse acesso:
#### Prisões
```java
[out:json];{{geocodeArea:Portugal}}->.searchArea;
(
  node[amenity=prison](area.searchArea);>;
  way[amenity=prison](area.searchArea);>;
  relation[amenity=prison](area.searchArea);>;
);
out;
```

<div style="page-break-after: always;"></div>

#### Tribunais
```javascript
[out:json];{{geocodeArea:Portugal}}->.searchArea;
(
  node[amenity=courthouse](area.searchArea);>;
  way[amenity=courthouse](area.searchArea);>;
  relation[amenity=courthouse](area.searchArea);>;
);
out;
```
#### Esquadras
```json
[out:json];{{geocodeArea:Portugal}}->.searchArea;
(
  node[amenity=police](area.searchArea);>;
  way[amenity=police](area.searchArea);>;
  relation[amenity=police](area.searchArea);>;
);
out;
```

Após obter os ficheiros json com a informação pretendida, será necessário fazer um script (será feito em python devido à maior facilidade com o tratamento de dados) com o objetivo de filtrar a informação e obter apenas os ID's dos nodes que correspondem aos POI's. O seguinte pseudo-código mostra o procedimento necessário para isso:

```py
1. loadPrisonJSON()
2.
3. for prison in data:
4.   for node in prison['nodes']:
5.     for locationFile in nodeFilesFolder:
6.       for availableNode in locationFile.read():
7.         if node.ID == availableNode.ID:
8.           write node.ID to file (location + 'tags.txt')
9.
10. loadCourtJSON()
12.
13. for court in data:
14.   for node in court['nodes']:
15.     for locationFile in nodeFilesFolder:
16.       for availableNode in locationFile.read():
17.         if node.ID == availableNode.ID:
18.           write node.ID to file (location + 'tags.txt')
19.
20. loadPoliceJSON()
21.
22. for police in data:
23.   for node in police['nodes']:
24.     for locationFile in nodeFilesFolder:
25.       for availableNode in locationFile.read():
26.         if node.ID == availableNode.ID:
27.           write node.ID to file (location + 'tags.txt')
```
No fim deste script o resultado obtido serão um conjunto de ficheiros de tags (um para cada cidade) com o conjunto de nodes correspondesntes a cada uma das tags necessárias para o nosso trabalho. Estes ficheiros permitirão a identificação dos POI's no Grafo. 


#### 4. Identificação de Técnicas de Concepção

Assim que a preparação estiver pronta, é possivel seguir para a implementação de código. Nesta fase será necessário que o programa consiga criar 2 rotas, uma de ida e outra de volta.

Como primeira tentativa decidimos usar para a Rota de ida o algoritmo de Dijkstra:

| DIJKSTRA(G, s): // G=(V,E), s in V  | BIDIRECTIONAL DIJKSTRA(G, s): <br> |
|--------------|-----------------|
|     1. **for** each v **in** V do<br>    2. &emsp;dist(v) <- INF<br>    3. &emsp;path(v) <- nil<br>    4. dist(s) <- 0<br>    5. Q <- 0 // min-priority queue<br>    6. INSERT(Q, (s, 0)) // inserts s with key 0<br>    7. **while** Q != 0 do<br>    8. &emsp;v <- EXTRACT-MIN(Q) <br>    9. &emsp;**for** each w **in** Adj(v) do<br>    10.&emsp;&emsp;**if** dist(w) > dist(v) + weight(v,w) **then**<br>    11.&emsp;&emsp;&emsp;dist(w) <- dist(v)+ weight(v,w)<br>    12.&emsp;&emsp;&emsp;path(w) <- v<br>    13.&emsp;&emsp;&emsp;**if** w not in Q **then** <br>    14.&emsp;&emsp;&emsp;&emsp;INSERT(Q, (w, dist(w)))<br>    15.&emsp;&emsp;&emsp;**else**<br>    16.&emsp;&emsp;&emsp;&emsp;DECREASE-KEY(Q, (w, dist(w))) | 1. Qi.Insert(x1) and mark xi as visited<br> 2. Qg.Insert(xg) and mark xg as visited<br> 3. **while** Qi not empty **and** Qg not empt **do** <br> 4.&emsp;**if** Qi not empty <br> 5.&emsp;&emsp;x <- Qi.GetFirst() <br> 6.&emsp;&emsp;**if** x = xg **or** x ∈ Qg <br> 7.&emsp;&emsp;&emsp;&emsp;**return** SUCCESS <br> 8.&emsp;&emsp;**forall** u ∈ U(x) <br> 9. &emsp; &emsp;&emsp;x' <- f(x,u) <br> 10.&emsp;&emsp;&emsp;**if** x' not visited <br> 11.&emsp;&emsp;&emsp;&emsp;Mark x' as visited <br> 12.&emsp;&emsp;&emsp;&emsp;Qi.Insert(x') <br> 13.&emsp;&emsp;&emsp;**else** <br> 14.&emsp;&emsp;&emsp;&emsp;Resolve duplicate x' <br> 15.&emsp;**if** Qg not empty <br> 16.&emsp;&emsp;x' <- Q.GetFirst() <br> 17.&emsp;&emsp;**if** x' = xi **or** x' ∈ Qi <br> 18.&emsp;&emsp;&emsp;&emsp;**return** SUCCESS <br> 19.&emsp;&emsp;**forall** u^(-1) ∈ U^(-1)(x') <br> 20. &emsp; &emsp;&emsp;x <- f^(-1)(x',u^(-1)) <br> 21.&emsp;&emsp;&emsp;**if** x not visited <br> 22.&emsp;&emsp;&emsp;&emsp;Mark x as visited <br> 23.&emsp;&emsp;&emsp;&emsp;Qg.Insert(x) <br> 24.&emsp;&emsp;&emsp;**else** <br> 25.&emsp;&emsp;&emsp;&emsp;Resolve duplicate x <br> 26. **return** FAILURE                                             |

da seguinte forma: Começando no estabelecimento prisional, onde se encontram os prisioneiros, é usado o algoritmo até encontrar um vértice, que será uma paragem de um dos prisioneiros. Neste ponto é usado outra vez o algoritmo de Dijkstra, mas com o vértice encontrado a ser usado como vértice de início, para encontrar a próxima paragem. Assim que todos os prisioneiros estiverem distribuidos será necessário encontrar o caminho de volta. Para isso, é aplicado o algoritmo de Dijkstra Bi-Direcional, de modo a encontrar o caminho mais curto entre o Vértice final do passo anterior e o estabelecimento prisional inicial.

## ALGORITMO A*
Após alguma reflexão sobre qual seria o melhor algoritmo para o cálculo mais eficiente das rotas percebemos que o algoritmo A* seria melhor, quando comparado com o algoritmo de Dijkstra e o algoritmo Dijkstra Bi-Directional. Este algoritmo funciona de forma semelhante aos dois previamente apresentados mas com uma ligeira diferença. O cálculo dos pesos da aresta segue a função:

*f(v) = h(v) + g(v)*

sendo h(v) a função heurística. 
O algoritmo de Dijkstra é uma variância deste algoritmo em que a função h(v) = 0. Utilizando uma função melhor, é possível optimizar o cálculo do custo de cada vértice e desta forma melhorar significativamente a eficiência do algoritmo.
Optamos então pela implementação deste algoritmo usando como função heurística a distância euclidiana ao destino, isto é, permite que o custo de cada vértice seja calculado tendo em conta, nao só o seu custo, mas também se se aproxima ou não do destino.

```java
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
    cost = g(m) + distance(m,n) // cost of current child
    if n in open_list and cost < g(n) 
      remove n from open_list as new path is better
    if n in closed_list and cost < g(n)  
      remove n from closed_list
    if n not in open_list and n not in closed_list
      add n to open_list
      g(n) = cost
      h(n) = heuristic_function(n,end)
      f(n) = g(n) + h(n)
return failure 
```

| X             | Dijkstra                             | A*                                   |
|:-------------:|:------------------------------------:|:------------------------------------:|
| Normal        | ![](https://i.imgur.com/hk4TYfe.png) | ![](https://i.imgur.com/M0GOBfp.png) |
| BiDirectional | ![](https://i.imgur.com/0qtlaBd.png) | ![](https://i.imgur.com/SOKOEon.png) |

> Imagens obtidas a partir de https://qiao.github.io/PathFinding.js/visual/

Como observações finais para esta fase temos a comparação e decisão dos algoritmos tendo em conta a informação revista: Já ficou provado que será melhor usar o algoritmos A* invés dos algoritmos Dijkstra e Bi-Directional Dijkstra. Restou-nos então a decisão entre A* normal ou A* Bidirectional.
Como, diferente do exemplo, num grafo que representa vias e estradas não haverá uma *parede* que perturbe de forma significativa o algoritmo A*, causando, por exemplo, que este processe demasiados nós à volta do sítio bloqueado pela parede em vez de avançar de forma direta para o nó destino, juntamente com o facto de que o speedup ganho não é tão significativo entre os algoritmos A* como entre os algoritmos de Djikstra, decidimos que usaremos o algoritmo A* normal.

### Fase 2
Na segunda fase teremos em conta o valor de densidade populacional (DP) dos vértices e 2 veículos, cada um especializado para os seus valores de DP. Isso leva-nos a 3 formas de encontrar o caminho mais curto, tendo em conta uma divisão prévia dos prisioneiros:

#### Hipótese 1 - Não tendo em conta o caminho
Como primeira hipótese considera-se apenas a DP dos destinos de cada um dos prisioneiros. Tendo isso em conta é feita uma divisão em dois grupos baseado na DP do destino de cada prisioneiro. Um grupo será levado por um carro (com capacidade infinita) para destinos com DP de *cidade* enquanto que o outro grupo será levado por um autocarro (também com capacidade infinita) para destinos com DP de *periferia* ou *campo*.
Feita a divisão o problema simplifica-se a aplicar o método da fase 1 para cada veículo.

<div style="page-break-after: always;"></div>

#### Hipótese 2 - Tendo em conta o caminho
Nesta hipótese, que parece mais precisa, será feito, no início, o cálculo de uma rota, como na fase 1, para todos os prisioneiros. A partir do processamento da rota, cada prisioneiro ficará com o valor de cada DP dos vértices pela qual passou. Tendo em conta a DP máxima de cada prisioneiro fazem-se as divisões em 2 grupos e segue-se como na hipótese anterior para a divisão nos veiculos e cálculo de rotas.
A contagem das DP para cada prisioneiro terá em conta apenas a rota inicial e não as rotas criadas pelos veiculos aos quais ficaram designados, isto poderá não trazer os melhores resultados quanto à divisão dos prisioneiros entre veículos mas é uma melhoria face à hipótese anterior.

#### Hipótese 3 - Apenas considerando os vértices onde o veículo pode transportar
Nesta hipótese consideram-se diferentes tipos de veículo para transportar em *cidade* ou não. Quando são selecionados veículos que não estão aptos para transportar prisioneiros em cidades, o grafo será filtrado, removendo temporariamente todos os vértices em que a Densidade Populacional corresponde a uma cidade (não seguindo por arestas cujo destino é cidade), de forma a que encontre o caminho mais curto, apenas passando por vértices com DP de *campo* ou *periferia*. Desta forma, será descoberto o caminho mais curto para cada tipo de veículo.

### Fase 3
A diferença principal desta fase para a anterior é o limite em cada veiculo. Com isso em conta, para esta fase, adotamos os mesmos passos da hipótese 2 da fase 2, até à divisão dos prisioneiros pelos veículos, excepto que neste caso teremos que fazer um cálculo do *resto* de prisioneiros, caso não haja transporte para todos. Caso haja transporte para todos, o problema torna-se igual à fase 2. Em caso contrário, faz-se um cálculo dos veículos que terão de retornar ao estabelecimento prisional inicial tendo em conta: a sua capacidade, o número de prisioneiros restantes e o grupo ao qual os prisioneiros restantes estão designados.
Assim que este cálculo for realizado repete-se este método, a partir do ponto em que se calcula o resto dos prisioneiros.

## Casos de utilização
A aplicação utilizará uma interface simples, de texto, de modo a interagir com o utilizador. Para isso, será usado um conjunto de menus com diversas opções.

Inicialmente, o programa apresentará um menu que permita ao utilizador selecionar o distrito que pretende explorar.
Após essa seleção, o utilizador poderá selecionar uma das seguintes opções:

- **Visualização do mapa**, através do GraphViewer;
- **Seleção da origem** (um dos estabelecimentos prisionais desse distrito). É de notar que, após esta seleção, o utilizador terá que criar 	pelo menos um prisioneiro, com informação de ID e Destino;
- **Conectividade da origem**: através dos algoritmos de Pesquisa em Largura/Profundidade, será calculada a quantidade de esquadras, prisões e tribunais que podem ser alcançados a partir da origem selecionada. Estes pontos poderão ser apresentados ao utilizador.
- **Edição da lista de prisioneiros**: caso não haja um caminho possível entre a origem selecionada ou caso o utilizador queira alterar o destino de um prisioneiro, será possível alterar a lista de prisioneiros;
- **Cálculo do caminho ótimo**: esta opção calculará o caminho ótimo através do algoritmo de Dijkstra/Dijkstra Bidireciona/A* e apresentará o 	caminho ótimo sob forma de um grafo;

_Notas_:
_Numa fase posterior, com a implementação de diferentes tipos de veículos serão apresentadas todas as rotas, quando o utilizador selecionar a opção de 'Cálculo do caminho ótimo'.
Numa fase ainda mais avançada, poderá ser dada a opção do utilizador escolher um tipo de veículo, de modo a transportar um prisioneiro específico._


## Conclusão
Temos um plano traçado e bem dividido. Esperamos que na altura da implementação consigamos tratar de forma eficiente de todas as partes, principalmente, do uso da parte gráfica de criação de grafos, visto que será a primeira vez neste curso que faremos uso de algo semelhante.
