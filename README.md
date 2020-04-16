# Algorithme génétique

Dans le cadre du module `Résolution de problèmes complexes` au sein de ma formation à l'EPSI, j'ai réalisé un algorithme génétique s'appuyant au problème du voyageur de commerce. C'est un problème d'optimisation qui en fonction d'une liste de villes et des distances entre-elles, détermine le plus court chemin qui visite chaque ville en une seule fois en déterminant la ville de départ.

## Qu'est ce qu'un algorithme génétique

Les algorithmes génétiques appartiennent à la famille des algorithmes évolutionnistes. Ce sont des algorithmes utilisés lorsqu'on ne connait pas les paramètres optimums ou que par exemple il est impossible de tester toutes les possibilités de résolution (explosion combinatoire). On préfère trouver une solution acceptable rapidement plutôt que la solution optimum en un temps indéfini.
Cette méthode suit donc le principe de l'évolution sur une population donnée. On retrouve les notions suivantes :
* Sélection : on ne conserve que les individus les plus adaptés d'une population
* Gène : définition caractéristique de l'individu
* Chromosome : un chromosome est un ensemble de gènes
* Croisement : deux individus échangent une partie de leur ADN
* Mutation : modification aléatoire d'un gène

## Principe d'un algorithme génétique

Pour fonctionner, un algorithme génétique doit disposer d'une population de départ générée aléatoirement. Cette population est composée de chromosomes qui sont eux-mêmes composés de gènes. On teste cette population de départ grâce à une fonction dite de "fitting", qui permet d'effectuer la sélection. Par la suite on procède aux croisements et aux mutations pour générer une nouvelle population, c'est l'évolution. Enfin on teste cette nouvelle population et on recommence. La condition d'arrêt de l'algorithme est un score de fitting suffisant ou alors un nombre prédéfini d'itérations.
* Calcul de la distance entre deux gènes c’est-à-dire entre deux villes en fonction des coordonnées GPS.
* Calcul de la distance total d'un chromosome  c’est-à-dire d'un chemin soit la distance total entre toutes les villes.
* Fonction pour récupérer le meilleur chromosome donc le meilleur chemin.
* Fonction de génération : génération d'une population aléatoire d'une taille donnée. Une population est composée de chromosomes eux-mêmes composés de gènes.
* Fonction d'évaluation de la population : sert à évaluer la population existante pour sélectionner les meilleurs chromosomes pour servir à la fonction d'évolution.
* Fonction de mutation : Cette fonction permet une mutation sur un chromosome, on prend un chromosome et on intervertit deux gènes.
* Fonction de croisement : Cette fonction permet de croiser deux chromosomes, c’est-à-dire de créer un chromosome enfant à partir de deux chromosomes parents.
* Fonction d'évolution : Cette fonction permet d'évoluer une population, c’est-à-dire qu'à partir d'une population on en créer une nouvelle. Cette nouvelle population contient la population source et tous les enfants créés suite à la fonction de croisement.

## Environnement :

C++, Visual Studio

