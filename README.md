# 🏹 Jogos Vorazes: Labirinto
> **Trabalho Prático - Estrutura de Dados I**

![C](https://img.shields.io/badge/C-Standard-00599C?style=for-the-badge&logo=c&logoColor=white)
![Makefile](https://img.shields.io/badge/Build-Makefile-green?style=for-the-badge)
![UFES](https://img.shields.io/badge/UFES-DCE-red?style=for-the-badge)

## 📖 Sobre o Projeto

Este projeto foi desenvolvido para a disciplina de **Estrutura de Dados I** da Universidade Federal do Espírito Santo (UFES). O objetivo é resolver o problema proposto pelo cenário fictício dos "Jogos Vorazes".

O programa simula um labirinto onde um **Tributo** (o jogador) deve encontrar uma saída segura sem ser capturado pelos **Bestantes** (monstros). Para isso, o sistema calcula as distâncias mínimas de perigo e traça o melhor caminho utilizando algoritmos de busca em grafos.

### 🎯 O Desafio
O software deve ler a configuração de um labirinto e determinar se existe um caminho para a saída, considerando que o Tributo não pode passar por locais onde seria interceptado pelos Bestantes antes de chegar ao destino.

---

## ⚙️ Estruturas de Dados e Algoritmos

O projeto implementa estruturas fundamentais "do zero" (sem uso de bibliotecas de contêineres prontas), focando na eficiência e gerenciamento de memória.

### 1. Fila Dinâmica (`labirinto.c`)
Uma implementação de fila (`Queue`) utilizando lista encadeada para gerenciar a ordem de visitação dos nós do labirinto. Essencial para o funcionamento da BFS.

### 2. Busca em Largura (BFS)
O algoritmo principal utilizado em duas etapas:
1.  **Mapeamento de Perigo:** Uma BFS multi-origem (ou iterativa) é executada a partir de todos os Bestantes para preencher uma matriz de distâncias (`distanciaBestantes`). Isso cria um "mapa de calor" do perigo.
2.  **Caminho do Tributo:** Uma segunda BFS é executada a partir da posição do Tributo ('A') para encontrar a saída, respeitando as restrições de distância calculadas na etapa anterior.

---

## 📂 Estrutura dos Arquivos

| Arquivo | Descrição |
| :--- | :--- |
| `main.c` | Ponto de entrada. Lê as dimensões e o mapa do labirinto, aloca as matrizes e chama as funções de resolução. |
| `labirinto.c` | Implementação da lógica: funções de Fila (Enfileirar/Desenfileirar) e algoritmos de busca (BFS). |
| `labirinto.h` | Arquivo de cabeçalho com as definições de structs (`Node`, `Fila`) e protótipos de funções. |
| `makefile` | Script de automação para compilação e limpeza dos arquivos binários. |

---

## 🚀 Como Compilar e Executar

O projeto conta com um `makefile` para facilitar a compilação.

### Pré-requisitos
* Compilador GCC instalado.
* Ambiente Linux ou Windows (com MinGW/Make).

### 1. Compilação
No terminal, dentro da pasta do projeto, execute:

```bash
make
```
Isso irá gerar um executável chamado `teste`.

### 2. Execução

Para rodar o programa, você deve fornecer os dados do labirinto via entrada padrão (teclado) ou redirecionar um arquivo de entrada.

Linux:
```bash
./teste < entrada.txt
```
Windows:
```DOS
teste.exe < entrada.txt
```

### 3. Limpeza

Para remover os arquivos objetos (.o) e o executável gerado:

```bash
make clean
```

## 📝 Formato de Entrada

O programa espera a seguinte entrada:
  * Dois inteiros N e M (linhas e colunas, máx 1000).
  * A matriz de caracteres representando o labirinto:
    - "." : Caminho livre
    - "#" : Parede
    - "A" : Posição inicial do Tributo
    - "B" : Posição de um Bestante
    - "S" : Saída (se houver representação específica)

Exemplo:

```bash
5 5
A...#
.#.#.
.....
#.B.#
.....
```

## 📜 Licença

Este projeto está sob a licença MIT. Consulte o arquivo LICENSE para mais detalhes.

Desenvolvido por Felipe Amaral.
