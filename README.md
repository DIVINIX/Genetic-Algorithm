# Algorithme génétique

Dans le cadre du module `Résolution de problèmes complexes` au sein de ma formation à l'EPSI, nous avions à réaliser un algorithme génétique s'appuyant au problème du voyageur de commerce. 

## Qu'est ce qu'un algorithme génétique

Les algorithmes génétiques appartiennent à la famille des algorithmes évolutionnistes. Ce sont des algorithmes utilités lorsqu'on ne connait pas les paramètres optimums ou que par exemple il et impossible de tester toutes les possibilités de résolution (explosion combinatoire). On préfère trouver une solution acceptable rapidement plutôt que la solution optimum en un temps indéfini. Les algorithmes génétiques sont une analogie avec le paradigme darwinien de l'évolution des espèces.

Cette méthode suit donc le principe de l'évolution sur une population donnée. On retrouve les notions suivante :
* Sélection : on ne conserve que les individus les plus adaptés d'une population
* Gène : définition caractéristique de l'individu
* Chromosome : un chromosome est un ensemble de gènes
* Croisement : deux individus échangent une partie de leur ADN
* Mutation : modification aléatoire d'un gène

## Principe d'un algorithme génétique

Comme expliqué ci-dessus, ces algorithmes s'appuient sur un principe de sélection des individus d'une population qui présentent des caractéristiques se rapprochant au mieux de ce que l'on recherche tout en faisant évoluer cette population selon des critères d'évolution génétique que l'on a choisit.

Pour fonctionner, un algorithme génétique doit disposer d'une population de départ générée aléatoirement. Cette population est composée de chromosomes qui sont eux-mêmes composés de gènes. On teste cette population de départ grâce à une fonction dite de "fitting", qui permet d'effectuer la sélection. Par la suite on procède aux croisements et aux mutations pour générer une nouvelle population, c'est l'évolution. Enfin on teste cette nouvelle population et on recommence. La conditoin d'arrêt de l'lgorithme est un score de fitting suffisant ou alors un nombre prédéfini d'it"rations.
