# Render Module Documentation

## Overview
The render module handles all visual output of the game. It transforms the 3D world data into 2D pixels on screen, managing textures, colors, and the main rendering loop.

## Files Structure
- `r_loop.c` - Main rendering loop and frame management
- `r_background.c` - Floor and ceiling rendering
- `r_wall.c` - Wall rendering and texture mapping
- `r_textures.c` - Texture loading and management
- `r_minimap.c` - Minimap rendering (if implemented)

## Core Concepts

### 3D to 2D Projection
The render module converts 3D world coordinates to 2D screen coordinates using:
1. **Raycasting results** - Distance and wall information
2. **Perspective projection** - Objects farther away appear smaller
3. **Screen mapping** - Convert world coordinates to pixel positions

### Rendering Pipeline
1. **Clear screen** - Prepare for new frame
2. **Render background** - Draw floor and ceiling
3. **Cast rays** - For each screen column
4. **Render walls** - Draw textured wall slices
5. **Present frame** - Display completed image

### Screen Coordinate System
- **Origin (0,0)** at top-left corner
- **X-axis** increases rightward
- **Y-axis** increases downward
- **Screen dimensions** typically 800x600 or 1024x768

## Mathematical Concepts

### Wall Height Calculation
Wall height on screen depends on distance:
```c
line_height = (int)(screen_height / distance);
```

### Texture Mapping
Map wall texture to screen coordinates:
```c
// Calculate texture X coordinate
tex_x = (int)(wall_x * texture_width);
if (side == 0 && ray_dir_x > 0) tex_x = texture_width - tex_x - 1;
if (side == 1 && ray_dir_y < 0) tex_x = texture_width - tex_x - 1;

// Calculate texture Y step
step = 1.0 * texture_height / line_height;
tex_pos = (draw_start - screen_height / 2 + line_height / 2) * step;
```

### Perspective Correction
To avoid fisheye effect, use perpendicular distance:
```c
perp_wall_dist = distance * cos(ray_angle - player_angle);
```

## Functions Analysis

### Main Rendering Loop

#### `render_loop(void *param)`
**Purpose**: Main rendering function called each frame
**Process**:
1. Clear previous frame
2. Render background (floor/ceiling)
3. Cast rays for each screen column
4. Render wall slices with textures
5. Present completed frame
6. Return 0 for MLX compatibility

### Background Rendering

#### `render_background(t_game *game)`
**Purpose**: Draw floor and ceiling colors
**Process**:
1. Calculate screen regions (top half = ceiling, bottom half = floor)
2. Fill pixels with appropriate colors
3. Use efficient pixel manipulation

### Wall Rendering

#### `draw_wall_slice(t_game *game, int x, t_ray_hit *hit, double ray_angle)`
**Purpose**: Draw a single vertical wall slice
**Parameters**:
- `x`: Screen column position
- `hit`: Ray intersection data
- `ray_angle`: Current ray angle

**Process**:
1. Calculate wall height on screen
2. Determine draw start/end positions
3. Select appropriate texture
4. Map texture coordinates
5. Draw textured vertical line

#### `get_wall_texture(t_game *game, t_ray_hit *hit, double ray_angle)`
**Purpose**: Select correct wall texture based on hit side
**Logic**:
- North wall (ray hits from south): Use north texture
- South wall (ray hits from north): Use south texture
- East wall (ray hits from west): Use east texture
- West wall (ray hits from east): Use west texture

### Texture Management

#### `get_texture_color(t_img *texture, int x, int y)`
**Purpose**: Extract color from texture at specific coordinates
**Process**:
1. Calculate pixel position in texture data
2. Extract RGB values from memory
3. Return color in appropriate format

## Data Structures

### `t_img`
Image/texture data structure:
```c
typedef struct s_img {
    void    *img;       // MLX image pointer
    char    *addr;      // Image data address
    int     bpp;        // Bits per pixel
    int     line_len;   // Line length in bytes
    int     endian;     // Endianness
    int     width;      // Image width
    int     height;     // Image height
} t_img;
```

### `t_draw_params`
Drawing parameters for wall rendering:
```c
typedef struct s_draw_params {
    int     x;          // Screen X position
    int     draw_start; // Start Y position
    int     draw_end;   // End Y position
    int     tex_x;      // Texture X coordinate
    int     line_height;// Wall line height
} t_draw_params;
```

## Performance Optimization

### Efficient Pixel Access
Direct memory manipulation for faster rendering:
```c
char *dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
*(unsigned int*)dst = color;
```

### Texture Caching
- Load textures once at initialization
- Keep in memory for fast access
- Use efficient texture coordinate calculation

### Frame Rate Management
- MLX handles frame timing automatically
- Render loop called at display refresh rate
- Optimize for 60 FPS target

## Color Management

### RGB Color Format
Colors stored as 32-bit integers:
```c
color = (red << 16) | (green << 8) | blue;
```

### Texture Color Extraction
Extract RGB from texture data:
```c
int get_texture_color(t_img *texture, int x, int y)
{
    char *pixel = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
    return (*(int *)pixel);
}
```

---

# Documentation du Module Render

## Vue d'ensemble
Le module render gère toute la sortie visuelle du jeu. Il transforme les données du monde 3D en pixels 2D à l'écran, gérant les textures, couleurs, et la boucle de rendu principale.

## Structure des Fichiers
- `r_loop.c` - Boucle de rendu principale et gestion des frames
- `r_background.c` - Rendu du sol et du plafond
- `r_wall.c` - Rendu des murs et mapping de texture
- `r_textures.c` - Chargement et gestion des textures
- `r_minimap.c` - Rendu de la minimap (si implémentée)

## Concepts Fondamentaux

### Projection 3D vers 2D
Le module render convertit les coordonnées du monde 3D en coordonnées écran 2D en utilisant :
1. **Résultats de raycasting** - Distance et informations de mur
2. **Projection perspective** - Les objets plus loin apparaissent plus petits
3. **Mapping écran** - Convertir les coordonnées monde en positions pixel

### Pipeline de Rendu
1. **Effacer l'écran** - Préparer pour la nouvelle frame
2. **Rendre l'arrière-plan** - Dessiner sol et plafond
3. **Lancer les rayons** - Pour chaque colonne d'écran
4. **Rendre les murs** - Dessiner les tranches de mur texturées
5. **Présenter la frame** - Afficher l'image complétée

### Système de Coordonnées Écran
- **Origine (0,0)** au coin supérieur gauche
- **Axe X** augmente vers la droite
- **Axe Y** augmente vers le bas
- **Dimensions écran** typiquement 800x600 ou 1024x768

## Concepts Mathématiques

### Calcul de Hauteur de Mur
La hauteur du mur à l'écran dépend de la distance :
```c
line_height = (int)(screen_height / distance);
```

### Mapping de Texture
Mapper la texture de mur aux coordonnées écran :
```c
// Calculer la coordonnée X de texture
tex_x = (int)(wall_x * texture_width);
if (side == 0 && ray_dir_x > 0) tex_x = texture_width - tex_x - 1;
if (side == 1 && ray_dir_y < 0) tex_x = texture_width - tex_x - 1;

// Calculer le pas Y de texture
step = 1.0 * texture_height / line_height;
tex_pos = (draw_start - screen_height / 2 + line_height / 2) * step;
```

### Correction de Perspective
Pour éviter l'effet fisheye, utiliser la distance perpendiculaire :
```c
perp_wall_dist = distance * cos(ray_angle - player_angle);
```

## Analyse des Fonctions

### Boucle de Rendu Principale

#### `render_loop(void *param)`
**Objectif** : Fonction de rendu principale appelée chaque frame
**Processus** :
1. Effacer la frame précédente
2. Rendre l'arrière-plan (sol/plafond)
3. Lancer les rayons pour chaque colonne d'écran
4. Rendre les tranches de mur avec textures
5. Présenter la frame complétée
6. Retourner 0 pour compatibilité MLX

### Rendu d'Arrière-plan

#### `render_background(t_game *game)`
**Objectif** : Dessiner les couleurs de sol et plafond
**Processus** :
1. Calculer les régions d'écran (moitié haute = plafond, moitié basse = sol)
2. Remplir les pixels avec les couleurs appropriées
3. Utiliser la manipulation de pixels efficace

### Rendu de Mur

#### `draw_wall_slice(t_game *game, int x, t_ray_hit *hit, double ray_angle)`
**Objectif** : Dessiner une seule tranche verticale de mur
**Paramètres** :
- `x` : Position de colonne d'écran
- `hit` : Données d'intersection de rayon
- `ray_angle` : Angle de rayon actuel

**Processus** :
1. Calculer la hauteur du mur à l'écran
2. Déterminer les positions de début/fin de dessin
3. Sélectionner la texture appropriée
4. Mapper les coordonnées de texture
5. Dessiner la ligne verticale texturée

#### `get_wall_texture(t_game *game, t_ray_hit *hit, double ray_angle)`
**Objectif** : Sélectionner la texture de mur correcte basée sur le côté touché
**Logique** :
- Mur nord (rayon touche depuis le sud) : Utiliser texture nord
- Mur sud (rayon touche depuis le nord) : Utiliser texture sud
- Mur est (rayon touche depuis l'ouest) : Utiliser texture est
- Mur ouest (rayon touche depuis l'est) : Utiliser texture ouest

### Gestion de Texture

#### `get_texture_color(t_img *texture, int x, int y)`
**Objectif** : Extraire la couleur de la texture à des coordonnées spécifiques
**Processus** :
1. Calculer la position du pixel dans les données de texture
2. Extraire les valeurs RGB de la mémoire
3. Retourner la couleur au format approprié

## Structures de Données

### `t_img`
Structure de données image/texture :
```c
typedef struct s_img {
    void    *img;       // Pointeur image MLX
    char    *addr;      // Adresse des données image
    int     bpp;        // Bits par pixel
    int     line_len;   // Longueur de ligne en bytes
    int     endian;     // Endianness
    int     width;      // Largeur image
    int     height;     // Hauteur image
} t_img;
```

### `t_draw_params`
Paramètres de dessin pour le rendu de mur :
```c
typedef struct s_draw_params {
    int     x;          // Position X écran
    int     draw_start; // Position Y début
    int     draw_end;   // Position Y fin
    int     tex_x;      // Coordonnée X texture
    int     line_height;// Hauteur ligne mur
} t_draw_params;
```

## Optimisation des Performances

### Accès Pixel Efficace
Manipulation directe de mémoire pour rendu plus rapide :
```c
char *dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
*(unsigned int*)dst = color;
```

### Cache de Texture
- Charger les textures une fois à l'initialisation
- Garder en mémoire pour accès rapide
- Utiliser calcul efficace de coordonnées de texture

### Gestion du Taux de Frame
- MLX gère le timing des frames automatiquement
- Boucle de rendu appelée au taux de rafraîchissement d'affichage
- Optimiser pour cible 60 FPS

## Gestion des Couleurs

### Format Couleur RGB
Couleurs stockées comme entiers 32-bit :
```c
color = (red << 16) | (green << 8) | blue;
```

### Extraction Couleur Texture
Extraire RGB des données de texture :
```c
int get_texture_color(t_img *texture, int x, int y)
{
    char *pixel = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
    return (*(int *)pixel);
}
```