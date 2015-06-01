# Stibbons

Ceci est le projet Stibbons en version 1.1.

## Dépendances des exécutables

- C++11
- Qt 5.0
- Flex
- Bison
- Json Spirit 4.0.4
- CppUnit

## Compilation

Le makefile a été prévu pour compiler également la documentation (non fournie) qui est également compilée par la règle par défaut. Il faut donc compiler en précisant la ou les cibles souhaitées.

### Application graphique

`make stibbons`

### Application en ligne de commande

`make stibbons-cli`

### Tests unitaires

`make test`

### Nettoyage

`make clean`

