# 42-minishell

A reproduction of the bash environment with its command interpretation.

# Règles pour Git

Pour gérer au mieux l'organisation de ce projet, voici quelques règles d'utilisation de git pour que notre travail soit le plus organisé possible, afin de ne pas perdre de temps sur les merge conflicts ou autres trucs pénibles.

## 1. Où on travaille

Le mieux reste de travailler sur ce repository et de ne pas passer par des forks pour que ca soit plus facile. On s'ajoute juste en tant que contributeurs.

## 2. Les branches

Voici ce que chaque branche fait et quel but leur sont donné :

### `main`

La branche principale sur laquelle se trouvera la version 100% fonctionnelle. Sans doute la branche la moins avancée, mais c'est celle qui ne contient aucun bug. Également la branche par défaut qui sera mise en avant lors d'un git pull.

### `develop`

La branche active du développement, celle sur laquelle se trouveront toutes les nouvelles features, mais sur laquelle il peut rester encore quelques bugs. Toutes les branches de fonctionnalités partiront de cette branche.

### Branches de fonctionnalité

Lorsque l'un de nous deux développe une fonctionnalité pour le projet, il crée une branche associée, partant de `develop`. Petit exemple ci-dessous :
> Admettons que je veuille créer une nouvelle feature "here_doc" qui implémente le here_doc dans mon projet. Je fais alors ceci :
> ```bash
> # Passage sur la branche develop
> $ git checkout develop
> # Mise à jour de la branche develop pour récuperer les derniers push (donc les dernières fonctionnalités)
> $ git pull origin develop
> # En cas de conflits, TOUJOURS garder la version distante. Si pas de conflit, alors ignorer la prochaine commande. Pour se faire :
> $ git stash && git pull --no-rebase origin develop --force
> 
> # À cette étape de l'opération, on est sur develop, prêt à initialiser l'espace de travail pour la nouvelle feature:
> $ git checkout -b here_doc
> ```
> Évidemment il faut remplacer here_doc par la fonctionnalité que tu développes.

Et voilà ! Pendant le développement de la feature, il est important de push son travail assez souvent pour ne pas prendre le risque de le perdre. De plus, il est fortement recommandé de se mettre à jour sur develop (d'importer les nouveautés de develop) sur la branche courante pour éviter de se taper des conflits lors de la pull request.

Pour se faire :
```bash
# Placement sur la branche courante (celle sur laquelle se trouve la fonctionnalité que tu codes)
$ git checkout ma_fonctionnalite
# Importation des nouveautés de develop
$ git pull origin develop --rebase
```
En cas de conflit, on essaie de les régler à deux, mais si on s'y prend bien ca ne devrait pas arriver souvent. Au pire, on fait preuve de bon sens.
