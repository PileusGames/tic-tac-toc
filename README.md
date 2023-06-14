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
> NB: Avoir fait [Construire](#construire) avant de lancer le jeu.

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
{
  "displays": [
    {
      "width": "300",
      "height": "300",
      "content": [
        {
          "tag": "style",
          "content": "line{stroke:black;stroke-width:4;}"
        },
        {
          "tag": "line",
          "x1": "0",
          "y1": "100",
          "x2": "300",
          "y2": "100"
        },
        {
          "tag": "line",
          "x1": "100",
          "y1": "0",
          "x2": "100",
          "y2": "300"
        },
        {
          "tag": "line",
          "x1": "0",
          "y1": "200",
          "x2": "300",
          "y2": "200"
        },
        {
          "tag": "line",
          "x1": "200",
          "y1": "0",
          "x2": "200",
          "y2": "300"
        }
      ],
      "player": 1
    },
    {
      "width": "300",
      "height": "300",
      "content": [
        {
          "tag": "style",
          "content": "line{stroke:black;stroke-width:4;}"
        },
        {
          "tag": "line",
          "x1": "0",
          "y1": "100",
          "x2": "300",
          "y2": "100"
        },
        {
          "tag": "line",
          "x1": "100",
          "y1": "0",
          "x2": "100",
          "y2": "300"
        },
        {
          "tag": "line",
          "x1": "0",
          "y1": "200",
          "x2": "300",
          "y2": "200"
        },
        {
          "tag": "line",
          "x1": "200",
          "y1": "0",
          "x2": "200",
          "y2": "300"
        }
      ],
      "player": 2
    }
  ],
  "requested_actions": [
    {
      "type": "CLICK",
      "player": 1,
      "zones": [
        {
          "x": 0,
          "y": 0,
          "width": 100,
          "height": 100
        },
        {
          "x": 0,
          "y": 100,
          "width": 100,
          "height": 100
        },
        {
          "x": 0,
          "y": 200,
          "width": 100,
          "height": 100
        },
        {
          "x": 100,
          "y": 0,
          "width": 100,
          "height": 100
        },
        {
          "x": 100,
          "y": 100,
          "width": 100,
          "height": 100
        },
        {
          "x": 100,
          "y": 200,
          "width": 100,
          "height": 100
        },
        {
          "x": 200,
          "y": 0,
          "width": 100,
          "height": 100
        },
        {
          "x": 200,
          "y": 100,
          "width": 100,
          "height": 100
        },
        {
          "x": 200,
          "y": 200,
          "width": 100,
          "height": 100
        }
      ]
    }
  ],
  "game_state": {
    "scores": [
      0,
      0
    ],
    "game_over": false
  }
}
```