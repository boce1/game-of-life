This is Conway's Game of life made in cpp using SDL2

Libs and include files are only complatable with minGW compiler.

To compile files run

(Makefile can be installed with "choco" package manager for Windows) 
```bash
git clone https://github.com/boce1/game-of-life.git
make
```

To delete object file and main.exe run
```bash
make clean
```

### Instruction
With left mouse click user can make cell alive or dead.

With right mouse click user can start/stop simulation.

With scrool user can scale the scene. Note: every alive cell will be deleted.

