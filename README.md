# Conway's Game of life made in cpp using SDL2

Conway's Game of Life is a cellular automaton devised by the British mathematician John Horton Conway in 1970. It is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input from a human player. The game takes place on an infinite two-dimensional grid of cells, where each cell can be in one of two possible states: alive or dead.
Libs and include files are only complatable with minGW compiler.

## Getting started

### Prerequisites

- MinGW compiler
- Makefile

To compile this you need Makefile. Makefile can be installed with [Chocolatey](https://chocolatey.org/install#individual) package manager for Windows (while you are installing choco make sure you follow instruction in section "individual")

### Installation
1. **Install makefile**
    ```bash
    choco install make
    ```

2. **Clone repository**
    ```bash
    git clone https://github.com/boce1/game-of-life.git
    ```

3. **Compile**
    ```bash
    make
    ```

4. **Run the simulation**
    ```bash
    ./main
    ```

    or

    ```bash
    main.exe
    ```

    or just open it from file explorer


**To delete object file and main.exe run**
```bash
make clean
```

### Instruction
With left mouse click user can make cell alive or dead.

With right mouse click user can start/stop simulation.

With scrool user can scale the scene. Note: every alive cell will be deleted.

By pressing keys "1", "2", "3", "4" user can change speed of simulation. (1 is the slowest, 4 is the fastest)