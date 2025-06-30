# Utils Module Documentation

## Overview
The utils module provides utility functions that support various aspects of the Cub3D game. These functions handle memory management, player direction calculations, cleanup operations, and other helper functionalities.

## Files Structure
- `u_cleanup.c` - Memory cleanup and resource deallocation
- `u_dir_player.c` - Player direction and angle calculations
- `u_minimap.c` - Minimap utility functions (if implemented)

## Core Concepts

### Utility Functions Purpose
Utility functions serve to:
1. **Reduce code duplication** - Common operations in reusable functions
2. **Improve maintainability** - Centralized logic for specific tasks
3. **Handle edge cases** - Robust error handling and validation
4. **Provide abstractions** - Simplify complex operations

### Memory Management Philosophy
- **RAII principle** - Resource Acquisition Is Initialization
- **Clean exit** - Always free allocated resources
- **Error safety** - Handle allocation failures gracefully
- **Leak prevention** - Track and free all dynamic memory

## Functions Analysis

### Memory Cleanup

#### `free_map_data(t_map_data *data)`
**Purpose**: Free all dynamically allocated memory in map data structure
**Process**:
1. Free texture path strings (NO, SO, WE, EA)
2. Free color strings (floor, ceiling)
3. Free 2D map array
4. Set pointers to NULL to prevent double-free

**Implementation Pattern**:
```c
void free_map_data(t_map_data *data)
{
    if (data->textures.no)
        free(data->textures.no);
    if (data->textures.so)
        free(data->textures.so);
    // ... continue for all allocated fields
    
    if (data->map)
    {
        int i = 0;
        while (data->map[i])
            free(data->map[i++]);
        free(data->map);
    }
}
```

### Player Direction Management

#### `assign_direction(t_player *player)`
**Purpose**: Convert player direction character to angle in radians
**Process**:
1. Check player direction character (N, S, E, W)
2. Assign corresponding angle in radians
3. Set player angle for raycasting calculations

**Direction to Angle Mapping**:
- **North (N)**: 3π/2 radians (270°)
- **South (S)**: π/2 radians (90°)
- **East (E)**: 0 radians (0°)
- **West (W)**: π radians (180°)

```c
void assign_direction(t_player *player)
{
    if (player->direction == 'N')
        player->angle = 3 * M_PI / 2;
    else if (player->direction == 'S')
        player->angle = M_PI / 2;
    else if (player->direction == 'E')
        player->angle = 0;
    else if (player->direction == 'W')
        player->angle = M_PI;
}
```

### Minimap Utilities (if implemented)

#### Minimap Helper Functions
**Purpose**: Support minimap rendering and calculations
**Common Functions**:
- `scale_coordinates()` - Convert world to minimap coordinates
- `draw_player_dot()` - Draw player position on minimap
- `draw_map_walls()` - Render walls on minimap
- `calculate_minimap_bounds()` - Determine minimap display area

## Mathematical Utilities

### Angle Normalization
Keep angles within valid range (0 to 2π):
```c
double normalize_angle(double angle)
{
    while (angle < 0)
        angle += 2 * M_PI;
    while (angle >= 2 * M_PI)
        angle -= 2 * M_PI;
    return (angle);
}
```

### Distance Calculation
Calculate distance between two points:
```c
double calculate_distance(double x1, double y1, double x2, double y2)
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
```

### Coordinate Conversion
Convert between different coordinate systems:
```c
// Grid to world coordinates
double grid_to_world_x(int grid_x)
{
    return ((double)grid_x + 0.5);
}

// World to grid coordinates
int world_to_grid_x(double world_x)
{
    return ((int)world_x);
}
```

## Error Handling Utilities

### Safe Memory Allocation
```c
void *safe_malloc(size_t size)
{
    void *ptr = malloc(size);
    if (!ptr)
    {
        write(2, "Error: Memory allocation failed\n", 32);
        exit(1);
    }
    return (ptr);
}
```

### Safe String Duplication
```c
char *safe_strdup(const char *src)
{
    char *dst;
    
    if (!src)
        return (NULL);
    dst = malloc(strlen(src) + 1);
    if (!dst)
        return (NULL);
    strcpy(dst, src);
    return (dst);
}
```

## Validation Utilities

### Boundary Checking
```c
int is_valid_position(double x, double y, char **map)
{
    int grid_x = (int)x;
    int grid_y = (int)y;
    
    if (grid_x < 0 || grid_y < 0)
        return (0);
    if (!map[grid_y] || !map[grid_y][grid_x])
        return (0);
    return (map[grid_y][grid_x] != '1');
}
```

### Range Validation
```c
int is_in_range(double value, double min, double max)
{
    return (value >= min && value <= max);
}
```

## Performance Utilities

### Fast Integer Operations
```c
// Fast absolute value for integers
int fast_abs(int x)
{
    return (x < 0 ? -x : x);
}

// Fast minimum/maximum
int fast_min(int a, int b)
{
    return (a < b ? a : b);
}

int fast_max(int a, int b)
{
    return (a > b ? a : b);
}
```

## Debug Utilities

### Debug Printing (for development)
```c
void debug_print_player(t_player *player)
{
    printf("Player: x=%.2f, y=%.2f, angle=%.2f, dir=%c\n",
        player->x, player->y, player->angle, player->direction);
}

void debug_print_map_info(char **map)
{
    int height = 0;
    while (map[height])
        height++;
    printf("Map height: %d\n", height);
}
```

---

# Documentation du Module Utils

## Vue d'ensemble
Le module utils fournit des fonctions utilitaires qui supportent divers aspects du jeu Cub3D. Ces fonctions gèrent la gestion mémoire, les calculs de direction du joueur, les opérations de nettoyage, et d'autres fonctionnalités d'aide.

## Structure des Fichiers
- `u_cleanup.c` - Nettoyage mémoire et désallocation de ressources
- `u_dir_player.c` - Calculs de direction et d'angle du joueur
- `u_minimap.c` - Fonctions utilitaires de minimap (si implémentée)

## Concepts Fondamentaux

### Objectif des Fonctions Utilitaires
Les fonctions utilitaires servent à :
1. **Réduire la duplication de code** - Opérations communes dans des fonctions réutilisables
2. **Améliorer la maintenabilité** - Logique centralisée pour des tâches spécifiques
3. **Gérer les cas limites** - Gestion d'erreur robuste et validation
4. **Fournir des abstractions** - Simplifier les opérations complexes

### Philosophie de Gestion Mémoire
- **Principe RAII** - Resource Acquisition Is Initialization
- **Sortie propre** - Toujours libérer les ressources allouées
- **Sécurité d'erreur** - Gérer les échecs d'allocation gracieusement
- **Prévention de fuites** - Suivre et libérer toute mémoire dynamique

## Analyse des Fonctions

### Nettoyage Mémoire

#### `free_map_data(t_map_data *data)`
**Objectif** : Libérer toute mémoire allouée dynamiquement dans la structure de données de carte
**Processus** :
1. Libérer les chaînes de chemin de texture (NO, SO, WE, EA)
2. Libérer les chaînes de couleur (sol, plafond)
3. Libérer le tableau 2D de carte
4. Définir les pointeurs à NULL pour prévenir la double libération

**Modèle d'Implémentation** :
```c
void free_map_data(t_map_data *data)
{
    if (data->textures.no)
        free(data->textures.no);
    if (data->textures.so)
        free(data->textures.so);
    // ... continuer pour tous les champs alloués
    
    if (data->map)
    {
        int i = 0;
        while (data->map[i])
            free(data->map[i++]);
        free(data->map);
    }
}
```

### Gestion de Direction du Joueur

#### `assign_direction(t_player *player)`
**Objectif** : Convertir le caractère de direction du joueur en angle en radians
**Processus** :
1. Vérifier le caractère de direction du joueur (N, S, E, W)
2. Assigner l'angle correspondant en radians
3. Définir l'angle du joueur pour les calculs de raycasting

**Mapping Direction vers Angle** :
- **Nord (N)** : 3π/2 radians (270°)
- **Sud (S)** : π/2 radians (90°)
- **Est (E)** : 0 radians (0°)
- **Ouest (W)** : π radians (180°)

```c
void assign_direction(t_player *player)
{
    if (player->direction == 'N')
        player->angle = 3 * M_PI / 2;
    else if (player->direction == 'S')
        player->angle = M_PI / 2;
    else if (player->direction == 'E')
        player->angle = 0;
    else if (player->direction == 'W')
        player->angle = M_PI;
}
```

### Utilitaires Minimap (si implémentée)

#### Fonctions d'Aide Minimap
**Objectif** : Supporter le rendu de minimap et les calculs
**Fonctions Communes** :
- `scale_coordinates()` - Convertir coordonnées monde vers minimap
- `draw_player_dot()` - Dessiner position joueur sur minimap
- `draw_map_walls()` - Rendre les murs sur minimap
- `calculate_minimap_bounds()` - Déterminer zone d'affichage minimap

## Utilitaires Mathématiques

### Normalisation d'Angle
Maintenir les angles dans une plage valide (0 à 2π) :
```c
double normalize_angle(double angle)
{
    while (angle < 0)
        angle += 2 * M_PI;
    while (angle >= 2 * M_PI)
        angle -= 2 * M_PI;
    return (angle);
}
```

### Calcul de Distance
Calculer la distance entre deux points :
```c
double calculate_distance(double x1, double y1, double x2, double y2)
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
```

### Conversion de Coordonnées
Convertir entre différents systèmes de coordonnées :
```c
// Coordonnées grille vers monde
double grid_to_world_x(int grid_x)
{
    return ((double)grid_x + 0.5);
}

// Coordonnées monde vers grille
int world_to_grid_x(double world_x)
{
    return ((int)world_x);
}
```

## Utilitaires de Gestion d'Erreurs

### Allocation Mémoire Sécurisée
```c
void *safe_malloc(size_t size)
{
    void *ptr = malloc(size);
    if (!ptr)
    {
        write(2, "Error: Memory allocation failed\n", 32);
        exit(1);
    }
    return (ptr);
}
```

### Duplication de Chaîne Sécurisée
```c
char *safe_strdup(const char *src)
{
    char *dst;
    
    if (!src)
        return (NULL);
    dst = malloc(strlen(src) + 1);
    if (!dst)
        return (NULL);
    strcpy(dst, src);
    return (dst);
}
```

## Utilitaires de Validation

### Vérification de Limites
```c
int is_valid_position(double x, double y, char **map)
{
    int grid_x = (int)x;
    int grid_y = (int)y;
    
    if (grid_x < 0 || grid_y < 0)
        return (0);
    if (!map[grid_y] || !map[grid_y][grid_x])
        return (0);
    return (map[grid_y][grid_x] != '1');
}
```

### Validation de Plage
```c
int is_in_range(double value, double min, double max)
{
    return (value >= min && value <= max);
}
```

## Utilitaires de Performance

### Opérations Entières Rapides
```c
// Valeur absolue rapide pour entiers
int fast_abs(int x)
{
    return (x < 0 ? -x : x);
}

// Minimum/maximum rapide
int fast_min(int a, int b)
{
    return (a < b ? a : b);
}

int fast_max(int a, int b)
{
    return (a > b ? a : b);
}
```

## Utilitaires de Debug

### Impression Debug (pour développement)
```c
void debug_print_player(t_player *player)
{
    printf("Player: x=%.2f, y=%.2f, angle=%.2f, dir=%c\n",
        player->x, player->y, player->angle, player->direction);
}

void debug_print_map_info(char **map)
{
    int height = 0;
    while (map[height])
        height++;
    printf("Map height: %d\n", height);
}
```