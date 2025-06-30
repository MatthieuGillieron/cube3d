# Raycasting Module Documentation

## Overview
The raycasting module is the core of the 3D rendering engine. It implements the raycasting algorithm to create a pseudo-3D perspective from a 2D map by casting rays from the player's position and calculating wall distances.

## Files Structure
- `r_cast.c` - Main raycasting algorithm implementation

## Core Concepts

### What is Raycasting?
Raycasting is a rendering technique used to create a 3D perspective in real-time. It works by:
1. Casting rays from the player's position
2. Finding intersections with walls
3. Calculating distances to determine wall heights
4. Drawing vertical lines representing walls

### Mathematical Foundation

#### Ray Equation
A ray can be represented as:
```
Ray(t) = Origin + t * Direction
Where:
- Origin = Player position (x, y)
- Direction = (cos(angle), sin(angle))
- t = Distance parameter
```

#### DDA Algorithm (Digital Differential Analyzer)
DDA is used to efficiently traverse the grid and find wall intersections:
1. Calculate ray direction and delta distances
2. Determine step direction (+1 or -1)
3. Calculate initial side distances
4. Step through grid until wall hit

### Field of View (FOV)
The FOV determines how wide the player's view is:
- Standard FOV: 60° (π/3 radians)
- Defined as: `#define FOV 1.0472` (≈ 60°)

## Algorithm Implementation

### Ray Casting Process
```c
t_ray_hit cast_ray(t_game *game, double ray_angle)
{
    // 1. Initialize ray position and direction
    // 2. Calculate delta distances
    // 3. Determine step direction
    // 4. Perform DDA algorithm
    // 5. Calculate wall distance
    // 6. Return hit information
}
```

### Key Calculations

#### Ray Direction
```c
ray_dir_x = cos(ray_angle);
ray_dir_y = sin(ray_angle);
```

#### Delta Distance (distance between grid lines)
```c
delta_dist_x = fabs(1.0 / ray_dir_x);
delta_dist_y = fabs(1.0 / ray_dir_y);
```

#### Side Distance (distance to next grid line)
```c
if (ray_dir_x < 0) {
    step_x = -1;
    side_dist_x = (pos_x - map_x) * delta_dist_x;
} else {
    step_x = 1;
    side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
}
```

### Wall Distance Calculation
To avoid fisheye effect, we use perpendicular distance:
```c
if (side == 0)  // X-side hit
    distance = (map_x - pos_x + (1 - step_x) / 2) / ray_dir_x;
else           // Y-side hit
    distance = (map_y - pos_y + (1 - step_y) / 2) / ray_dir_y;
```

## Data Structures

### `t_ray_hit`
Stores information about ray-wall intersection:
```c
typedef struct s_ray_hit {
    double  distance;    // Distance to wall
    int     map_x;       // Wall X coordinate
    int     map_y;       // Wall Y coordinate
    int     side;        // Which side was hit (0=X, 1=Y)
    double  wall_x;      // Exact hit point on wall
} t_ray_hit;
```

### `t_ray_dir`
Stores ray direction and calculation data:
```c
typedef struct s_ray_dir {
    double  ray_dir_x, ray_dir_y;      // Ray direction
    double  delta_dist_x, delta_dist_y; // Delta distances
    double  side_dist_x, side_dist_y;   // Side distances
    int     step_x, step_y;             // Step direction
} t_ray_dir;
```

## Performance Optimization
- DDA algorithm provides O(n) complexity where n is distance to wall
- Integer arithmetic where possible
- Efficient grid traversal
- Minimal floating-point operations

---

# Documentation du Module Raycasting

## Vue d'ensemble
Le module raycasting est le cœur du moteur de rendu 3D. Il implémente l'algorithme de raycasting pour créer une perspective pseudo-3D à partir d'une carte 2D en lançant des rayons depuis la position du joueur et en calculant les distances aux murs.

## Structure des Fichiers
- `r_cast.c` - Implémentation principale de l'algorithme de raycasting

## Concepts Fondamentaux

### Qu'est-ce que le Raycasting ?
Le raycasting est une technique de rendu utilisée pour créer une perspective 3D en temps réel. Il fonctionne en :
1. Lançant des rayons depuis la position du joueur
2. Trouvant les intersections avec les murs
3. Calculant les distances pour déterminer les hauteurs de murs
4. Dessinant des lignes verticales représentant les murs

### Fondation Mathématique

#### Équation de Rayon
Un rayon peut être représenté comme :
```
Rayon(t) = Origine + t * Direction
Où :
- Origine = Position du joueur (x, y)
- Direction = (cos(angle), sin(angle))
- t = Paramètre de distance
```

#### Algorithme DDA (Digital Differential Analyzer)
DDA est utilisé pour traverser efficacement la grille et trouver les intersections de murs :
1. Calculer la direction du rayon et les distances delta
2. Déterminer la direction du pas (+1 ou -1)
3. Calculer les distances latérales initiales
4. Parcourir la grille jusqu'à toucher un mur

### Champ de Vision (FOV)
Le FOV détermine la largeur de la vue du joueur :
- FOV standard : 60° (π/3 radians)
- Défini comme : `#define FOV 1.0472` (≈ 60°)

## Implémentation de l'Algorithme

### Processus de Lancement de Rayon
```c
t_ray_hit cast_ray(t_game *game, double ray_angle)
{
    // 1. Initialiser position et direction du rayon
    // 2. Calculer les distances delta
    // 3. Déterminer la direction du pas
    // 4. Exécuter l'algorithme DDA
    // 5. Calculer la distance au mur
    // 6. Retourner les informations de collision
}
```

### Calculs Clés

#### Direction du Rayon
```c
ray_dir_x = cos(ray_angle);
ray_dir_y = sin(ray_angle);
```

#### Distance Delta (distance entre les lignes de grille)
```c
delta_dist_x = fabs(1.0 / ray_dir_x);
delta_dist_y = fabs(1.0 / ray_dir_y);
```

#### Distance Latérale (distance à la prochaine ligne de grille)
```c
if (ray_dir_x < 0) {
    step_x = -1;
    side_dist_x = (pos_x - map_x) * delta_dist_x;
} else {
    step_x = 1;
    side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
}
```

### Calcul de Distance au Mur
Pour éviter l'effet fisheye, nous utilisons la distance perpendiculaire :
```c
if (side == 0)  // Collision côté X
    distance = (map_x - pos_x + (1 - step_x) / 2) / ray_dir_x;
else           // Collision côté Y
    distance = (map_y - pos_y + (1 - step_y) / 2) / ray_dir_y;
```

## Structures de Données

### `t_ray_hit`
Stocke les informations sur l'intersection rayon-mur :
```c
typedef struct s_ray_hit {
    double  distance;    // Distance au mur
    int     map_x;       // Coordonnée X du mur
    int     map_y;       // Coordonnée Y du mur
    int     side;        // Quel côté a été touché (0=X, 1=Y)
    double  wall_x;      // Point exact de collision sur le mur
} t_ray_hit;
```

### `t_ray_dir`
Stocke la direction du rayon et les données de calcul :
```c
typedef struct s_ray_dir {
    double  ray_dir_x, ray_dir_y;      // Direction du rayon
    double  delta_dist_x, delta_dist_y; // Distances delta
    double  side_dist_x, side_dist_y;   // Distances latérales
    int     step_x, step_y;             // Direction du pas
} t_ray_dir;
```

## Optimisation des Performances
- L'algorithme DDA fournit une complexité O(n) où n est la distance au mur
- Arithmétique entière quand possible
- Traversée efficace de la grille
- Opérations en virgule flottante minimales