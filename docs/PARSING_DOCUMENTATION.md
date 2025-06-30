# Parsing Module Documentation

## Overview
The parsing module handles all file reading, validation, and data extraction from the .cub configuration files. It ensures the map and configuration are valid before game initialization.

## Files Structure
- `p_file.c` - File opening and basic reading operations
- `p_map.c` - Map parsing and validation
- `p_texture.c` - Texture path parsing
- `p_color.c` - Color parsing and RGB conversion
- `p_check_texture.c` - Texture file validation
- `p_valid_map.c` - Map structure validation
- `p_map_ok_u.c` - Additional map validation utilities

## Core Concepts

### .cub File Format
The .cub file contains:
1. **Texture paths**: NO, SO, WE, EA (North, South, West, East)
2. **Colors**: F (floor), C (ceiling) in RGB format
3. **Map**: 2D grid with walls (1), empty spaces (0), and player start (N/S/E/W)

Example:
```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 220,100,0
C 225,30,0

111111
100001
101001
1000N1
111111
```

### Parsing Strategy
1. **Sequential Reading**: Read file line by line
2. **Section Separation**: Distinguish between config and map sections
3. **Validation**: Check each element for correctness
4. **Data Storage**: Store in appropriate structures

## Functions Analysis

### File Operations

#### `open_map(char *map)`
**Purpose**: Open and read the .cub file into memory
**Process**:
1. Open file with error checking
2. Read all lines using get_next_line
3. Store in string array
4. Close file and return data

#### `split_sections(char **lines, t_map_data *data)`
**Purpose**: Parse file content and separate config from map
**Process**:
1. Parse texture and color lines
2. Find map start position
3. Extract and validate map data

### Texture Parsing

#### `assign_texture_or_color(char *line, t_map_data *data, int *found)`
**Purpose**: Parse texture paths and color values
**Process**:
1. Identify line type (NO, SO, WE, EA, F, C)
2. Extract path or RGB values
3. Validate format and store data

### Color Processing

#### `rgb_to_hex(char *rgb_str)`
**Purpose**: Convert RGB string to hexadecimal color
**Process**:
1. Split RGB string by commas
2. Convert each component to integer
3. Validate range (0-255)
4. Combine into hex format: `(R << 16) | (G << 8) | B`

#### `parse_colors(t_map_data *data)`
**Purpose**: Process floor and ceiling color strings
**Process**:
1. Parse RGB strings
2. Convert to hex values
3. Store in game structure

### Map Validation

#### `is_map_enclosed(char **map, t_player *player)`
**Purpose**: Ensure map is properly enclosed by walls
**Algorithm**:
1. Check all border positions are walls
2. Flood-fill algorithm to verify connectivity
3. Ensure player can't reach map edges

#### `is_player(char c)` & `is_playable(char c)`
**Purpose**: Character validation functions
- `is_player()`: Check if character is valid player start (N/S/E/W)
- `is_playable()`: Check if character is valid map element (0/1/N/S/E/W)

### Map Processing

#### `find_map_start(char **lines, int i)`
**Purpose**: Locate where map data begins in file
**Process**:
1. Skip configuration lines
2. Skip empty lines
3. Find first line containing map characters

#### `copy_map(char **lines, t_map_data *data, int start)`
**Purpose**: Extract map data from file lines
**Process**:
1. Count map lines
2. Allocate memory for map array
3. Copy and validate each line

## Data Structures

### `t_texture`
Stores texture file paths:
```c
typedef struct s_texture {
    char    *no;    // North wall texture
    char    *so;    // South wall texture
    char    *we;    // West wall texture
    char    *ea;    // East wall texture
} t_texture;
```

### `t_color`
Stores color information:
```c
typedef struct s_color {
    char    *floor;      // Floor color string
    char    *ceiling;    // Ceiling color string
    int     set_floor;   // Floor color set flag
    int     set_ceiling; // Ceiling color set flag
} t_color;
```

### `t_map_data`
Main parsing data structure:
```c
typedef struct s_map_data {
    t_texture   textures;   // Texture paths
    t_color     colors;     // Color data
    t_player    player;     // Player information
    char        **map;      // 2D map array
} t_map_data;
```

## Validation Rules

### File Validation
- File must exist and be readable
- Must have .cub extension
- Must contain all required elements

### Texture Validation
- All 4 textures must be specified
- Files must exist and be readable
- Must be valid XPM format

### Color Validation
- RGB values must be in range 0-255
- Format: "R,G,B" with no spaces
- Both floor and ceiling must be specified

### Map Validation
- Must be rectangular (filled with spaces if needed)
- Must be enclosed by walls (1)
- Must contain exactly one player start position
- Only valid characters: 0, 1, N, S, E, W, space

## Error Handling
- Comprehensive error messages for each validation failure
- Memory cleanup on parsing errors
- Graceful exit with appropriate error codes

---

# Documentation du Module Parsing

## Vue d'ensemble
Le module parsing gère toute la lecture de fichiers, la validation, et l'extraction de données des fichiers de configuration .cub. Il s'assure que la carte et la configuration sont valides avant l'initialisation du jeu.

## Structure des Fichiers
- `p_file.c` - Ouverture de fichiers et opérations de lecture de base
- `p_map.c` - Parsing et validation de carte
- `p_texture.c` - Parsing des chemins de textures
- `p_color.c` - Parsing des couleurs et conversion RGB
- `p_check_texture.c` - Validation des fichiers de texture
- `p_valid_map.c` - Validation de la structure de carte
- `p_map_ok_u.c` - Utilitaires de validation de carte supplémentaires

## Concepts Fondamentaux

### Format de Fichier .cub
Le fichier .cub contient :
1. **Chemins de textures** : NO, SO, WE, EA (Nord, Sud, Ouest, Est)
2. **Couleurs** : F (sol), C (plafond) au format RGB
3. **Carte** : Grille 2D avec murs (1), espaces vides (0), et départ joueur (N/S/E/W)

Exemple :
```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 220,100,0
C 225,30,0

111111
100001
101001
1000N1
111111
```

### Stratégie de Parsing
1. **Lecture Séquentielle** : Lire le fichier ligne par ligne
2. **Séparation de Sections** : Distinguer entre sections config et carte
3. **Validation** : Vérifier chaque élément pour sa correction
4. **Stockage de Données** : Stocker dans les structures appropriées

## Analyse des Fonctions

### Opérations de Fichier

#### `open_map(char *map)`
**Objectif** : Ouvrir et lire le fichier .cub en mémoire
**Processus** :
1. Ouvrir le fichier avec vérification d'erreur
2. Lire toutes les lignes avec get_next_line
3. Stocker dans un tableau de chaînes
4. Fermer le fichier et retourner les données

#### `split_sections(char **lines, t_map_data *data)`
**Objectif** : Parser le contenu du fichier et séparer config de carte
**Processus** :
1. Parser les lignes de texture et couleur
2. Trouver la position de début de carte
3. Extraire et valider les données de carte

### Parsing de Texture

#### `assign_texture_or_color(char *line, t_map_data *data, int *found)`
**Objectif** : Parser les chemins de texture et valeurs de couleur
**Processus** :
1. Identifier le type de ligne (NO, SO, WE, EA, F, C)
2. Extraire le chemin ou les valeurs RGB
3. Valider le format et stocker les données

### Traitement des Couleurs

#### `rgb_to_hex(char *rgb_str)`
**Objectif** : Convertir une chaîne RGB en couleur hexadécimale
**Processus** :
1. Diviser la chaîne RGB par virgules
2. Convertir chaque composant en entier
3. Valider la plage (0-255)
4. Combiner au format hex : `(R << 16) | (G << 8) | B`

#### `parse_colors(t_map_data *data)`
**Objectif** : Traiter les chaînes de couleur sol et plafond
**Processus** :
1. Parser les chaînes RGB
2. Convertir en valeurs hex
3. Stocker dans la structure de jeu

### Validation de Carte

#### `is_map_enclosed(char **map, t_player *player)`
**Objectif** : S'assurer que la carte est correctement fermée par des murs
**Algorithme** :
1. Vérifier que toutes les positions de bordure sont des murs
2. Algorithme de remplissage pour vérifier la connectivité
3. S'assurer que le joueur ne peut pas atteindre les bords de carte

#### `is_player(char c)` & `is_playable(char c)`
**Objectif** : Fonctions de validation de caractères
- `is_player()` : Vérifier si le caractère est un départ joueur valide (N/S/E/W)
- `is_playable()` : Vérifier si le caractère est un élément de carte valide (0/1/N/S/E/W)

### Traitement de Carte

#### `find_map_start(char **lines, int i)`
**Objectif** : Localiser où commencent les données de carte dans le fichier
**Processus** :
1. Ignorer les lignes de configuration
2. Ignorer les lignes vides
3. Trouver la première ligne contenant des caractères de carte

#### `copy_map(char **lines, t_map_data *data, int start)`
**Objectif** : Extraire les données de carte des lignes de fichier
**Processus** :
1. Compter les lignes de carte
2. Allouer la mémoire pour le tableau de carte
3. Copier et valider chaque ligne

## Structures de Données

### `t_texture`
Stocke les chemins de fichiers de texture :
```c
typedef struct s_texture {
    char    *no;    // Texture mur nord
    char    *so;    // Texture mur sud
    char    *we;    // Texture mur ouest
    char    *ea;    // Texture mur est
} t_texture;
```

### `t_color`
Stocke les informations de couleur :
```c
typedef struct s_color {
    char    *floor;      // Chaîne couleur sol
    char    *ceiling;    // Chaîne couleur plafond
    int     set_floor;   // Flag couleur sol définie
    int     set_ceiling; // Flag couleur plafond définie
} t_color;
```

### `t_map_data`
Structure principale de données de parsing :
```c
typedef struct s_map_data {
    t_texture   textures;   // Chemins de textures
    t_color     colors;     // Données de couleur
    t_player    player;     // Informations joueur
    char        **map;      // Tableau 2D de carte
} t_map_data;
```

## Règles de Validation

### Validation de Fichier
- Le fichier doit exister et être lisible
- Doit avoir l'extension .cub
- Doit contenir tous les éléments requis

### Validation de Texture
- Les 4 textures doivent être spécifiées
- Les fichiers doivent exister et être lisibles
- Doivent être au format XPM valide

### Validation de Couleur
- Les valeurs RGB doivent être dans la plage 0-255
- Format : "R,G,B" sans espaces
- Sol et plafond doivent être spécifiés

### Validation de Carte
- Doit être rectangulaire (remplie d'espaces si nécessaire)
- Doit être fermée par des murs (1)
- Doit contenir exactement une position de départ joueur
- Seuls caractères valides : 0, 1, N, S, E, W, espace

## Gestion d'Erreurs
- Messages d'erreur complets pour chaque échec de validation
- Nettoyage mémoire lors d'erreurs de parsing
- Sortie gracieuse avec codes d'erreur appropriés