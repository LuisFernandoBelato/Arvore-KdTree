# Implementação da Árvore K-d Tree em C \ 5º Termo - Pesquisa e Ordenação

Este projeto implementa uma K-d Tree para organizar pontos em um espaço de K dimensões e realizar buscas por proximidade (busca por raio). O desenvolvimento segue as especificações do trabalho de Estruturas de Dados II.

## Visão Geral do Projeto

O objetivo principal é construir uma K-d Tree a partir de um conjunto de pontos e, em seguida, utilizar essa árvore para encontrar todos os pontos que estão dentro de um raio específico de uma dada coordenada.

## Funcionalidades

*   **Construção da K-d Tree:**
    *   Suporta K dimensões (definido pela macro `K`).
    *   Os pontos podem ser gerados aleatoriamente ou carregados a partir de um conjunto pré-definido (função `EncheVetorChico` para teste, `EncheVetorRandom` para geração aleatória).
    *   A árvore é construída recursivamente, alternando o eixo de divisão (dimensão) em cada nível.
    *   Em cada etapa, o conjunto de pontos é ordenado pela dimensão atual e o ponto mediano é escolhido para dividir o espaço.
*   **Busca por Raio**
    *   Dada uma coordenada de referência e um raio, a função de busca percorre a K-d Tree para encontrar todos os pontos que estão dentro da distância euclidiana especificada pelo raio.
*   **Exibição da Árvore:**
    *   Uma função para exibir a estrutura da K-d Tree no console em um formato hierárquico (árvore deitada).
*   **Geração de Dados:**
    *   Pontos e a coordenada de busca/raio podem ser gerados aleatoriamente para facilitar os testes.

## Como Funciona

### 1. Estrutura de Dados

*   **`struct KdTree`**: Representa um nó na K-d Tree. Cada nó armazena:
    *   `ponto[K]`: Um array de inteiros contendo as coordenadas do ponto no espaço K-dimensional.
    *   `esq`: Ponteiro para o filho esquerdo (pontos com valor menor na dimensão de corte atual).
    *   `dir`: Ponteiro para o filho direito (pontos com valor maior na dimensão de corte atual).

### 2. Construção da Árvore (`CriaKdTree`)

1.  **Inicialização:**
    *   Um conjunto de pontos é gerado (aleatoriamente ou fixo).
2.  **Processo Recursivo:**
    *   A função `CriaKdTree` recebe o conjunto de pontos atual, o nível atual da árvore (para determinar a dimensão de corte) e os índices de início e fim do subconjunto de pontos a ser processado.
    *   **Seleção da Dimensão de Corte (Discriminante):** A dimensão é determinada pelo `nivel % K` (alternando entre 0, 1, ..., K-1).
    *   **Ordenação:** O subconjunto de pontos é ordenado com base na coordenada da dimensão de corte atual.
    *   **Seleção do Ponto Mediano:** O ponto na posição mediana do subconjunto ordenado é escolhido para ser o nó atual da árvore.
    *   **Criação do Nó:** Um novo nó é criado com o ponto mediano.
    *   **Recursão:** A função é chamada recursivamente para:
        *   O subconjunto à esquerda do mediano (para o filho esquerdo), incrementando o nível.
        *   O subconjunto à direita do mediano (para o filho direito), incrementando o nível.
    *   O processo continua até que os subconjuntos não possam mais ser divididos (início > fim).

### 3. Busca por Raio (`BuscaPontos`)

1.  **Entrada:** Um nó da árvore (inicialmente a raiz), a coordenada de busca e o raio.
2.  **Cálculo da Distância Euclidiana:** Para o ponto no nó atual, a distância euclidiana até a coordenada de busca é calculada:
    `sqrt(sum((ponto_arvore[i] - ponto_busca[i])^2))`
3.  **Verificação:**
    *   Se a distância calculada for menor ou igual ao raio, o ponto do nó atual é considerado "próximo" e é exibido.
4.  **Poda e Recursão (Simplificada na Implementação Atual):**
    *   A implementação fornecida explora o filho direito se o ponto atual estiver dentro do raio e o filho direito existir.
    *   Explora o filho esquerdo independentemente (se existir).
    *   *Nota: Uma busca por raio mais otimizada em K-d Trees geralmente envolve verificar se a hiperesfera de busca intercepta os hiperplanos de divisão para decidir se é necessário explorar as subárvores. A implementação atual é uma busca mais direta.*

### 4. Exibição (`ExibeArvoreKdTree`)

*   Utiliza um percurso em ordem (modificado) para imprimir os nós. A recursão para a direita é feita primeiro, depois o nó atual é impresso com indentação baseada na profundidade, e então a recursão para a esquerda. Isso resulta em uma visualização da árvore "deitada".

---

## Estrutura do Código

*   **Definições Globais:** Constantes para `K` (dimensões), `TAM` (número de pontos a gerar), `MAX` (valor máximo para coordenadas).
*   **Estruturas:** Definição de `struct KdTree`.
*   **Funções Auxiliares:**
    *   `CriaNo`: Aloca e inicializa um novo nó da K-d Tree.
    *   `EncheVetorChico`: Preenche um vetor com pontos pré-definidos para teste.
    *   `Muda_Coordenadas`: Troca as coordenadas de dois pontos.
    *   `ExibeCoordenadasMatriz`: Mostra todos os pontos de uma matriz.
    *   `Ordena`: Ordena um subconjunto de pontos com base em uma dimensão específica (usado na construção da árvore).
    *   `MostraCoordenada`: Exibe um único ponto.
    *   `MostraNaTree`: Exibe o ponto de um nó da árvore.
    *   `GeraCoordenada`: Gera uma coordenada aleatória.
*   **Funções Principais:**
    *   `EncheVetorRandom`: Preenche a matriz de pontos com coordenadas aleatórias.
    *   `CriaKdTree`: Função recursiva para construir a K-d Tree.
    *   `CalculoDistanciaEuclidiana`: Calcula a distância entre um ponto da árvore e a coordenada de busca.
    *   `BuscaPontos`: Realiza a busca por raio.
    *   `ExibeArvoreKdTree`: Exibe a árvore formatada.
*   **`main()`:**
    *   Inicializa o gerador de números aleatórios.
    *   Declara a raiz da K-d Tree e outras variáveis necessárias.
    *   Preenche o vetor de pontos (usando `EncheVetorRandom` ou `EncheVetorChico`).
    *   Exibe os pontos gerados e um exemplo de ordenação.
    *   Chama `CriaKdTree` para construir a árvore.
    *   Exibe a K-d Tree formada.
    *   Gera uma coordenada de busca e um raio aleatórios.
    *   Chama `BuscaPontos` para encontrar e exibir os pontos próximos.
