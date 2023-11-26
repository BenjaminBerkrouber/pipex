# Pipex Project

## Description
Le projet Pipex simule le comportement de la commande shell `pipe` (`|`) en C. Il est conçu pour exécuter deux commandes en les passant à travers un pipe, de la même manière que le shell Unix le fait avec `cmd1 | cmd2`.

## Architecture
Le projet est structuré autour de plusieurs fonctions clés :

- `ft_get_path` : Trouve le chemin complet d'une commande donnée.
- `ft_exec` : Exécute une commande en utilisant `execve`.
- `ft_child` : Gère le processus enfant dans Pipex.
- `ft_parent` : Gère le processus parent dans Pipex.
- `ft_pipex` : Fonction principale qui initialise le pipe et les processus.

## Fonctionnement
```
+-----------+        +------------+        +------------+
| ft_pipex  |  fork  | ft_child   |  pipe  | ft_parent  |
+-----------+        +------------+        +------------+
   |                       |                   |
   |                       |                   |
   +---> Vérifie argc,     |                   |
         crée pipe,        |                   |
         appelle fork ---->+                   |
                            |                   |
                            +---> Exécute cmd1 -+
                                  via ft_exec   |
                                                |
                                                +---> Exécute cmd2
                                                      via ft_exec
```

## Utilisation
Pour utiliser Pipex, compilez le programme avec `make` et exécutez-le avec la syntaxe suivante :
Cela équivaut à `< file1 cmd1 | cmd2 > file2` dans le shell.

## Implémentation

### `ft_get_path`
Cette fonction trouve le chemin d'accès complet d'une commande en parcourant les répertoires spécifiés dans la variable d'environnement `PATH`.

### `ft_exec`
Exécute la commande spécifiée. Elle divise la commande en arguments, trouve le chemin de l'exécutable et exécute la commande en utilisant `execve`.

### `ft_child`
Gère le processus enfant dans Pipex. Il redirige l'entrée standard depuis le fichier d'entrée, connecte la sortie standard au pipe et exécute la première commande spécifiée.

### `ft_parent`
Gère le processus parent dans Pipex. Il redirige la sortie standard vers le fichier de sortie, lit l'entrée du pipe et exécute la seconde commande spécifiée.

### `ft_pipex`
Fonction principale de Pipex. Elle valide les arguments, configure le pipe et crée les processus enfant et parent.

## Dépendances
- La bibliothèque Libft est utilisée pour diverses fonctions utilitaires.

## Compilation
Compilez le projet avec la commande `make`. Cela générera l'exécutable `pipex`.

./pipex file1 cmd1 cmd2 file2


Cela équivaut à `< file1 cmd1 | cmd2 > file2` dans le shell.

## Implémentation

### `ft_get_path`
Cette fonction trouve le chemin d'accès complet d'une commande en parcourant les répertoires spécifiés dans la variable d'environnement `PATH`.

### `ft_exec`
Exécute la commande spécifiée. Elle divise la commande en arguments, trouve le chemin de l'exécutable et exécute la commande en utilisant `execve`.

### `ft_child`
Gère le processus enfant dans Pipex. Il redirige l'entrée standard depuis le fichier d'entrée, connecte la sortie standard au pipe et exécute la première commande spécifiée.

### `ft_parent`
Gère le processus parent dans Pipex. Il redirige la sortie standard vers le fichier de sortie, lit l'entrée du pipe et exécute la seconde commande spécifiée.

### `ft_pipex`
Fonction principale de Pipex. Elle valide les arguments, configure le pipe et crée les processus enfant et parent.

## Dépendances
- La bibliothèque Libft est utilisée pour diverses fonctions utilitaires.

## Compilation
Compilez le projet avec la commande `make`. Cela générera l'exécutable `pipex`.# pipex
