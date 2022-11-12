# TP2: Résolution de mots cachés


## Description

Les mots mystères ou mots mêlés sont un jeu qui consiste à trouver une liste 
de mots dans une grille remplie de lettres. Ce jeu a été inventé par 
Jean-Claude Langlois1. Les mots peuvent être trouvés horizontalement, 
verticalement, en oblique, à l'endroit ou à l'envers. Ils peuvent s'entrecouper 
et une même lettre peut faire partie de plusieurs mots de la grille. À la fin du jeu, 
lorsque tous les mots de la liste ont été trouvés, il demeure des lettres libres 
dans la grille. Ces lettres, remises dans le bon ordre, constituent les mots cachés 
ou le mot mystère. [Wikipedia](https://en.wikipedia.org/wiki/Word_search)

Ce programme résout ce genre de mots cachés. Les cas prix en comptes sont des grille
de 12 lettres par 12 lettres et les mots peuvent être trouvé orizontalement ou 
verticalement, donc pas d'obliques. À la fin du jeu les lettres sont assemblé 
de gauche à droite, de haut en bas, pour former le mot mystère.

Travail accompli dans le contexte du cours 
Construction et maintenance de logiciels (INF3135) donnee par Serge Dogny à
l'UQAM.

Le contenu du projet:

* `README.md`: ce fichier
* `Makefile`: permet d'automatiser la compilation
* `check.bats`: serie de tests
* `sujet.pdf`: sujet du travail
* `motcache.h`: "interface publique" des fonctions du code source
* `motcache.c`: code source, implementation de l'interface
* `.gitignore`: ignorer certains fichiers lors de la gestion des version
* `.gitla-ci.yml`: instructions d'intégration continu avec GitLab CI/CD
* `tests/MANDOLINE.txt`: fichier contenant un exemple de grille pouvant 
être résolu par le programme

[Contraintes du travail](sujet.pdf)

## Auteur

Leonid Glazyrin (GLAL77080105)

## Fonctionnement

Pour faire fonctionner le projet il vous faudra vous assurez d'avoir `git`
installé, ainsi que `make` et  `bats`. Referez vous à la 
section [Dépendances](#dépendances) pour les sites officiels.

Tout d'abord cloner le projet avec la commande :
```sh
git clone https://gitlab.info.uqam.ca/glazyrin.leonid/inf3135-aut2022-tp2.git
```
Si le projet n'est pas publique vous devrez vous authentifier.

Ensuite exécuté les commandes suivantes pour vous déplacer dans le répertoire, 
compiler le programme:
```sh
cd inf3135-aut2022-tp2
make
```

Finalement pour exécuter le programme avec un mot caché contenu dans un fichier :
```sh
./motcache <FICHIER_TEXTE>
```

Par exemple avec le fichier fourni contenant une grille à résoudre :
```sh
./motcache tests/MANDOLINE.txt
```

Les cas d'erreur gérés sont :

1. Fichier non trouvé
2. Mot non trouvé

## Tests

Entrez `make test` pour exécuter la suite de tests automatiques.

Mes résultats:
```sh
ok 1 test0 : Aucun argument
ok 2 test1 : Test fourni
```
Les 2 tests réussissent.

## Dépendances

* [GCC](https://gcc.gnu.org/)
* [Bats](https://github.com/bats-core/bats-core)
* [Make](https://www.gnu.org/software/make/manual/make.html)

## Références

* [GitLab CI/CD](https://docs.gitlab.com/ee/ci/)
* [GitLab Flavored Markdown](https://docs.gitlab.com/ee/user/markdown.html)
* [Mots cachés](https://fr.wikipedia.org/wiki/Mots_cachés)
* [Char to String in C](https://stackoverflow.com/a/28015754)
* [fgets() en C](https://www.digitalocean.com/community/tutorials/fgets-and-gets-in-c-programming)
* [Declarer i pour une boucle for](https://stackoverflow.com/questions/1287863/c-for-loop-int-initial-declaration)
