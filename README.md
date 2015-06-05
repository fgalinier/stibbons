# Stibbons

![Logo Stibbons](https://gitlab.info-ufr.univ-montp2.fr/florian.galinier/stibbons/raw/master/data/images/stibbons-full.png)

Ceci est le projet Stibbons en version 1.1 développé dans le cadre du Master Architecture et
InGénierie du Logiciel et du wEb à la Faculté des Sciences à l'Université Montpellier.

Ce projet vise à la création d’un langage de programmation multi-agents pour programmeurs
débutants et avancés : le Stibbons. Nous l’avons réalisé en C++ et ses applications utilisent
le framework Qt. Deux applications sont proposées pour répondre à deux cas d’utilisation dif-
férents : une application graphique permettant de développer des programmes Stibbons et de
les voir s’exécuter directement, et une application en ligne de commande simplifiant l’exécution
d’un programme et permettant un export régulier de données du modèle exécuté. Ce rapport
expose le fonctionnement du langage Stibbons et de ses applications, ainsi que l’organisation
que nous avons eu tout au long de la réalisation de ce projet.

## Dépendances des exécutables

- C++11
- Qt 5.0
- Flex
- Bison
- Json Spirit 4.0.4 (requiert Boost)
- CppUnit

## Compilation

### Tout

`make` ou `make all`

### Nettoyage

`make clean`

### Applications

#### Application graphique

`make stibbons`

#### Application en ligne de commande

`make stibbons-cli`

#### Tests unitaires

`make test`

### Documentation

`make doc`

#### Rapport

`make report`

#### Rapport de gestion de projet

`make project`

#### Présentation

`make keynote`

