# 🏹 Jogos Vorazes: Labirinto

> **Trabalho Prático — Estrutura de Dados I | UFES**

<p align="center">
  <img src="https://img.shields.io/badge/C-Standard-00599C?style=for-the-badge&logo=c&logoColor=white" />
  <img src="https://img.shields.io/badge/Build-Makefile-6D8E3C?style=for-the-badge&logo=gnu&logoColor=white" />
  <img src="https://img.shields.io/badge/Algoritmo-BFS-8A2BE2?style=for-the-badge" />
  <img src="https://img.shields.io/badge/UFES-DCE-003087?style=for-the-badge" />
</p>

---

## 📖 Sobre o Projeto

Este projeto foi desenvolvido para a disciplina de **Estrutura de Dados I** da Universidade Federal do Espírito Santo (UFES). O problema proposto simula o cenário fictício dos **Jogos Vorazes**: um tributo preso em um labirinto junto a um ou mais bestantes deve encontrar uma rota de fuga segura até qualquer borda do labirinto.

O grande desafio está na restrição de movimento: a cada passo do tributo, os bestantes também se movem. A solução deve funcionar **mesmo que os bestantes conheçam o caminho escolhido com antecedência** — ou seja, o tributo só pode ocupar uma célula se chegar lá estritamente antes de qualquer bestante.

---

## 🎯 O Problema

Dado um labirinto de `N × M` células, determinar se existe um caminho para o tributo escapar, e caso exista, imprimir esse caminho. O caminho deve ter no máximo `N × M` passos.

### Legenda do Labirinto

| Caractere | Significado |
|:---:|:---|
| `.` | Célula de chão livre (caminhável) |
| `#` | Parede (intransponível) |
| `A` | Posição inicial do Tributo |
| `M` | Posição inicial de um Bestante |

> A **saída** não é marcada com um caractere específico: qualquer célula na **borda** do labirinto (`linha 0`, `linha N-1`, `coluna 0` ou `coluna M-1`) constitui uma saída válida.

---

## ⚙️ Estruturas de Dados e Algoritmos

Todas as estruturas foram implementadas do zero em C, sem uso de bibliotecas de contêineres prontas, com atenção ao gerenciamento manual de memória.

### 🔗 Fila com Lista Encadeada

A fila (`Fila`) é implementada com nós encadeados (`Node`), onde cada nó armazena:

- Coordenadas `(x, y)` da célula
- String `path` com o caminho percorrido até aquela célula
- Ponteiro `next` para o próximo nó

```c
typedef struct Node {
    int x, y;
    char *path;
    struct Node *next;
} Node;

typedef struct {
    Node *ini, *fim;
} Fila;
```

Operações implementadas: `criaFila`, `enfileirar`, `desenfileirar` e `eVazio`.

---

### 🔍 Busca em Largura (BFS) — Duas Etapas

A solução aplica BFS em duas etapas distintas e complementares:

#### Etapa 1 — Mapeamento de Perigo (`calcularDistanciaMinimaBestantes`)

Uma **BFS multi-origem** é executada simultaneamente a partir de todos os bestantes (`M`). Isso preenche uma matriz `distanciaBestantes[i][j]` com o número mínimo de passos que qualquer bestante precisa para chegar à célula `(i, j)`.

```
Resultado: um "mapa de calor" que representa o perigo de cada célula.
```

#### Etapa 2 — Fuga do Tributo (`encontrarCaminhoTributo`)

Uma segunda BFS é executada a partir da posição do tributo (`A`). Para cada célula vizinha `(nx, ny)` considerada, o movimento só é permitido se:

```c
distanciaBestantes[nx][ny] > strlen(caminho) + 1
// ou seja: o tributo chega antes de qualquer bestante
```

Se uma célula na borda for atingida, o caminho é impresso e o programa encerra com `YES`. Caso a fila se esgote sem encontrar saída, imprime `NO`.

---

## 📂 Estrutura dos Arquivos

```
📦 Data-Structure-I/
├── 📄 main.c            # Ponto de entrada: leitura, alocação e chamada das funções
├── 📄 labirinto.c       # Implementação da Fila e dos algoritmos BFS
├── 📄 labirinto.h       # Definições de structs, constantes e protótipos
├── 📄 makefile          # Automação de compilação e limpeza
├── 📄 ENUNCIADO_ED1.pdf # Enunciado original do trabalho
└── 📄 LICENSE           # Licença MIT
```

### Descrição dos Arquivos

`main.c` — Lê `N` e `M`, aloca o labirinto e a matriz de distâncias, localiza a posição inicial do tributo e chama as duas funções principais.

`labirinto.h` — Define a constante `VOID (-1)` usada para células não visitadas, as structs `Node` e `Fila`, e os protótipos documentados de todas as funções.

`labirinto.c` — Contém toda a lógica: operações de fila, BFS de bestantes e BFS de fuga do tributo.

`makefile` — Compila o projeto com GCC e gera o executável `teste`.

---

## 🚀 Como Compilar e Executar

### Pré-requisitos

- Compilador **GCC** instalado
- **Make** instalado
- Linux, macOS ou Windows com MinGW

### 1. Clone o repositório

```bash
git clone https://github.com/Am4raIl/Data-Structure-I.git
cd Data-Structure-I
```

### 2. Compile

```bash
make
```

Será gerado o executável `teste`.

### 3. Execute

Forneça o labirinto via redirecionamento de arquivo:

```bash
# Linux / macOS
./teste < entrada.txt

# Windows
teste.exe < entrada.txt
```

Ou digite diretamente no terminal:

```bash
./teste
```

### 4. Limpe os arquivos gerados

```bash
make clean
```

---

## 📝 Formato de Entrada e Saída

### Entrada

```
N M
<linha_0>
<linha_1>
...
<linha_N-1>
```

- `N` e `M`: altura e largura do labirinto (1 ≤ N, M ≤ 1000)
- Exatamente um `A` no mapa
- Um ou mais `M` no mapa

### Saída

Se existir caminho:
```
YES
<comprimento_do_caminho>
<sequência_de_direções>
```

Se não existir:
```
NO
```

### Direções

| Caractere | Movimento |
|:---:|:---|
| `D` | Down (baixo) |
| `U` | Up (cima) |
| `L` | Left (esquerda) |
| `R` | Right (direita) |

---

## 💡 Exemplo

### Entrada

```
5 8
########
#M..A..#
#.#.M#.#
#M#..#..
#.######
```

### Saída

```
YES
5
RRDDR
```

### Visualização

```
########
#M..A..#   ← Tributo em (1,4), Bestantes em (1,1) e (3,1)
#.#.M#.#   ← Bestante em (2,4)
#M#..#..   ← Tributo escapa pela borda direita
#.######
```

O tributo se move `R → R → D → D → R`, saindo pela borda direita na linha 3, chegando antes de qualquer bestante em cada célula do trajeto.

---

## 📜 Licença

Este projeto está sob a licença MIT. Consulte o arquivo [LICENSE](LICENSE) para mais detalhes.

---



## 👥 Autores

| Nome | GitHub |
|:---|:---|
| **Marcelo Ferraz de Araújo Costa Filho** | [@MarceloFerraz](https://github.com/marcelfz) |
| **Felipe Kitamoto Amaral** | [@Am4raIl](https://github.com/Am4raIl) |
| **Gustavo Cunha Gonçalves** | [@gustavoCunhaG](https://github.com/gustavoCunhaG) |

<p align="center">Desenvolvido para a disciplina de <strong>Estrutura de Dados I</strong> — UFES 2024</p>
