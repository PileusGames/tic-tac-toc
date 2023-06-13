# TIC TAC TOC
> Moteur du jeu de morpion pour Pileus

![tic-tac-toc_robot_gif](https://media.giphy.com/media/3oriNKQe0D6uQVjcIM/giphy.gif)

## Démarer
### Construire

```shell
cmake ./CMakeLists.txt 
make all
```

### Tester
```shell
make test
```
> NB: Avoir fait [Construire](#construire) avant de lancer les tests.

### Lancer
```shell
bin/tic_tac_toc
```
> NB: Avoir fait [Construire](#construire) avant de lancer le projet.

## Entrés / Sorties
> Communique avec l'entrée et la sortie standard **stdin/stdout**.
### Initialisation
Pour démarrer le jeu, saisir dans stdin :
```json
{"init": {"players" : 2}}
```
En cas d'erreur ... ?

La réponse sera :
```json
?
```