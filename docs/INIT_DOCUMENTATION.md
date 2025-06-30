# Init Module Documentation

## Overview
The init module handles all initialization processes for the Cub3D game. It sets up the MLX environment, loads textures, initializes game structures, and prepares the system for rendering.

## Files Structure
- `i_game.c` - Main game initialization and MLX setup
- `i_textures.c` - Texture loading and image initialization

## Core Concepts

### Initialization Sequence
1. **MLX Initialization** - Create MLX instance and window
2. **Structure Setup** - Initialize game data structures
3. **Texture Loading** - Load wall textures from XPM files
4. **Event Registration** - Set up keyboard and window event handlers
5. **Validation** - Ensure all components are properly initialized

### MLX Library Basics
MLX (MiniLibX) is a graphics library that provides:
- **Window management** - Create and manage display windows
- **Image handling** - Load, create, and manipulate images
- **Event system** - Handle keyboard, mouse, and window events
- **Pixel manipulation** - Direct access to image pixel data

## Functions Analysis

### Game Initialization

#### `init_game(t_game *game)`
**Purpose**: Initialize the main game structure and MLX environment
**Process**:
1. Initialize MLX instance with `mlx_init()`
2. Create game window with `mlx_new_window()`
3. Set window dimensions (typically 800x600 or 1024x768)
4. Initialize game image buffer
5. Set up event hooks for keyboard and window events
6. Initialize player position and angle from map data
7. Return success/failure status

**Error Handling**:
- Check MLX initialization success
- Validate window creation
- Ensure all pointers are properly set

### Texture Management

#### `load_textures(t_game *game)`
**Purpose**: Load all wall textures from XPM files
**Process**:
1. Load north wall texture from file path
2. Load south wall texture from file path
3. Load west wall texture from file path
4. Load east wall texture from file path
5. Validate each texture loading
6. Store texture data in game structure

**Texture Loading Process**:
```c
// Load XPM file into MLX image
game->textures.north.img = mlx_xpm_file_to_image(game->mlx, 
    game->map_data.textures.no, &width, &height);

// Get image data address for pixel access
game->textures.north.addr = mlx_get_data_addr(
    game->textures.north.img, &bpp, &line_len, &endian);
```

## MLX Integration

### Window Creation
```c
game->mlx = mlx_init();
game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
```

### Image Buffer Setup
```c
game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, 
    &game->img.line_len, &game->img.endian);
```

### Event Hook Registration
```c
mlx_hook(game->win, 2, 1L<<0, key_press, game);        // Key press
mlx_hook(game->win, 17, 1L<<17, close_window, game);   // Window close
mlx_loop_hook(game->mlx, render_loop, game);           // Render loop
```

## Data Structure Initialization

### Player Setup
Initialize player position and orientation from map data:
```c
// Find player start position in map
// Set player coordinates (convert from grid to world coordinates)
// Set initial angle based on player direction character (N/S/E/W)
game->player.x = (double)start_x + 0.5;
game->player.y = (double)start_y + 0.5;
game->player.angle = get_initial_angle(direction_char);
```

### Texture Structure Setup
```c
typedef struct s_textures {
    t_img   north;  // North wall texture
    t_img   south;  // South wall texture
    t_img   east;   // East wall texture
    t_img   west;   // West wall texture
} t_textures;
```

## Error Handling and Validation

### MLX Validation
- Check if `mlx_init()` returns valid pointer
- Verify window creation success
- Validate image creation

### Texture Validation
- Ensure all texture files exist and are readable
- Verify XPM format compatibility
- Check texture dimensions are reasonable
- Validate image data address retrieval

### Memory Management
- Clean up on initialization failure
- Free allocated resources before exit
- Prevent memory leaks during error conditions

## Configuration Parameters

### Window Settings
```c
#define WIN_WIDTH   800     // Window width in pixels
#define WIN_HEIGHT  600     // Window height in pixels
#define WIN_TITLE   "Cub3D" // Window title
```

### Texture Requirements
- **Format**: XPM (X11 Pixmap)
- **Dimensions**: Typically 64x64 or 128x128 pixels
- **Color depth**: 24-bit RGB
- **File extension**: .xpm

## Initialization Flow

1. **Parse configuration** - Read .cub file and validate
2. **Initialize MLX** - Create graphics context
3. **Create window** - Set up display window
4. **Load textures** - Read wall texture files
5. **Setup player** - Initialize player position and angle
6. **Register events** - Set up input handlers
7. **Start main loop** - Begin game execution

---

# Documentation du Module Init

## Vue d'ensemble
Le module init gère tous les processus d'initialisation pour le jeu Cub3D. Il configure l'environnement MLX, charge les textures, initialise les structures de jeu, et prépare le système pour le rendu.

## Structure des Fichiers
- `i_game.c` - Initialisation principale du jeu et configuration MLX
- `i_textures.c` - Chargement des textures et initialisation des images

## Concepts Fondamentaux

### Séquence d'Initialisation
1. **Initialisation MLX** - Créer l'instance MLX et la fenêtre
2. **Configuration des Structures** - Initialiser les structures de données du jeu
3. **Chargement des Textures** - Charger les textures de mur depuis les fichiers XPM
4. **Enregistrement d'Événements** - Configurer les gestionnaires d'événements clavier et fenêtre
5. **Validation** - S'assurer que tous les composants sont correctement initialisés

### Bases de la Bibliothèque MLX
MLX (MiniLibX) est une bibliothèque graphique qui fournit :
- **Gestion de fenêtre** - Créer et gérer les fenêtres d'affichage
- **Manipulation d'image** - Charger, créer, et manipuler les images
- **Système d'événements** - Gérer les événements clavier, souris, et fenêtre
- **Manipulation de pixels** - Accès direct aux données pixel d'image

## Analyse des Fonctions

### Initialisation du Jeu

#### `init_game(t_game *game)`
**Objectif** : Initialiser la structure principale du jeu et l'environnement MLX
**Processus** :
1. Initialiser l'instance MLX avec `mlx_init()`
2. Créer la fenêtre de jeu avec `mlx_new_window()`
3. Définir les dimensions de fenêtre (typiquement 800x600 ou 1024x768)
4. Initialiser le buffer d'image du jeu
5. Configurer les hooks d'événements pour clavier et fenêtre
6. Initialiser la position et l'angle du joueur depuis les données de carte
7. Retourner le statut de succès/échec

**Gestion d'Erreurs** :
- Vérifier le succès de l'initialisation MLX
- Valider la création de fenêtre
- S'assurer que tous les pointeurs sont correctement définis

### Gestion des Textures

#### `load_textures(t_game *game)`
**Objectif** : Charger toutes les textures de mur depuis les fichiers XPM
**Processus** :
1. Charger la texture de mur nord depuis le chemin de fichier
2. Charger la texture de mur sud depuis le chemin de fichier
3. Charger la texture de mur ouest depuis le chemin de fichier
4. Charger la texture de mur est depuis le chemin de fichier
5. Valider chaque chargement de texture
6. Stocker les données de texture dans la structure de jeu

**Processus de Chargement de Texture** :
```c
// Charger fichier XPM en image MLX
game->textures.north.img = mlx_xpm_file_to_image(game->mlx, 
    game->map_data.textures.no, &width, &height);

// Obtenir l'adresse des données d'image pour accès pixel
game->textures.north.addr = mlx_get_data_addr(
    game->textures.north.img, &bpp, &line_len, &endian);
```

## Intégration MLX

### Création de Fenêtre
```c
game->mlx = mlx_init();
game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
```

### Configuration du Buffer d'Image
```c
game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, 
    &game->img.line_len, &game->img.endian);
```

### Enregistrement des Hooks d'Événements
```c
mlx_hook(game->win, 2, 1L<<0, key_press, game);        // Pression touche
mlx_hook(game->win, 17, 1L<<17, close_window, game);   // Fermeture fenêtre
mlx_loop_hook(game->mlx, render_loop, game);           // Boucle de rendu
```

## Initialisation des Structures de Données

### Configuration du Joueur
Initialiser la position et l'orientation du joueur depuis les données de carte :
```c
// Trouver la position de départ du joueur dans la carte
// Définir les coordonnées du joueur (convertir de grille en coordonnées monde)
// Définir l'angle initial basé sur le caractère de direction du joueur (N/S/E/W)
game->player.x = (double)start_x + 0.5;
game->player.y = (double)start_y + 0.5;
game->player.angle = get_initial_angle(direction_char);
```

### Configuration de la Structure de Texture
```c
typedef struct s_textures {
    t_img   north;  // Texture mur nord
    t_img   south;  // Texture mur sud
    t_img   east;   // Texture mur est
    t_img   west;   // Texture mur ouest
} t_textures;
```

## Gestion d'Erreurs et Validation

### Validation MLX
- Vérifier si `mlx_init()` retourne un pointeur valide
- Vérifier le succès de création de fenêtre
- Valider la création d'image

### Validation de Texture
- S'assurer que tous les fichiers de texture existent et sont lisibles
- Vérifier la compatibilité du format XPM
- Vérifier que les dimensions de texture sont raisonnables
- Valider la récupération de l'adresse des données d'image

### Gestion Mémoire
- Nettoyer en cas d'échec d'initialisation
- Libérer les ressources allouées avant sortie
- Prévenir les fuites mémoire lors de conditions d'erreur

## Paramètres de Configuration

### Paramètres de Fenêtre
```c
#define WIN_WIDTH   800     // Largeur fenêtre en pixels
#define WIN_HEIGHT  600     // Hauteur fenêtre en pixels
#define WIN_TITLE   "Cub3D" // Titre fenêtre
```

### Exigences de Texture
- **Format** : XPM (X11 Pixmap)
- **Dimensions** : Typiquement 64x64 ou 128x128 pixels
- **Profondeur couleur** : RGB 24-bit
- **Extension fichier** : .xpm

## Flux d'Initialisation

1. **Parser la configuration** - Lire le fichier .cub et valider
2. **Initialiser MLX** - Créer le contexte graphique
3. **Créer la fenêtre** - Configurer la fenêtre d'affichage
4. **Charger les textures** - Lire les fichiers de texture de mur
5. **Configurer le joueur** - Initialiser position et angle du joueur
6. **Enregistrer les événements** - Configurer les gestionnaires d'entrée
7. **Démarrer la boucle principale** - Commencer l'exécution du jeu