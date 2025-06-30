# Movement Module Documentation

## Overview
The movement module handles all player movement mechanics in the 3D space. It uses trigonometry to calculate precise movements and rotations while ensuring collision detection with walls.

## Files Structure
- `m_move_player.c` - Player movement functions (forward, backward, strafe)
- `m_rotate_player.c` - Player rotation function

## Mathematical Concepts

### Trigonometry in 2D Movement
Movement in Cub3D uses trigonometric functions to calculate direction vectors:
- `cos(angle)` = X component of unit vector
- `sin(angle)` = Y component of unit vector
- Angle in radians (0 to 2π)

### Coordinate System
- **X-axis**: Horizontal (left ← → right)
- **Y-axis**: Vertical (up ↑ ↓ down)
- **Angle 0**: East direction (→)
- **Angle π/2**: South direction (↓)
- **Angle π**: West direction (←)
- **Angle 3π/2**: North direction (↑)

### Movement Calculations

#### Forward/Backward Movement
```c
// Move forward in viewing direction
new_x = player.x + cos(player.angle) * speed;
new_y = player.y + sin(player.angle) * speed;

// Move backward (opposite direction)
new_x = player.x - cos(player.angle) * speed;
new_y = player.y - sin(player.angle) * speed;
```

#### Lateral Movement (Strafe)
```c
// Move left (angle - 90°)
new_x = player.x + cos(player.angle - M_PI/2) * speed;
new_y = player.y + sin(player.angle - M_PI/2) * speed;

// Move right (angle + 90°)
new_x = player.x + cos(player.angle + M_PI/2) * speed;
new_y = player.y + sin(player.angle + M_PI/2) * speed;
```

## Functions Analysis

### `move_forward(t_game *game)`
**Purpose**: Move player forward in viewing direction
**Algorithm**:
1. Calculate new position using cos/sin
2. Check collision with walls
3. Update position if valid

### `move_backward(t_game *game)`
**Purpose**: Move player backward
**Difference**: Uses negative sign to reverse direction

### `move_left(t_game *game)` & `move_right(t_game *game)`
**Purpose**: Lateral movement (strafe)
**Principle**: Uses angle ± 90° to move perpendicular to view direction

### `rotate_player(t_game *game, int direction)`
**Purpose**: Rotate player around their position
**Parameters**:
- `direction = 1`: Rotate right
- `direction = -1`: Rotate left

**Wrap-around handling**:
```c
// Keep angle between 0 and 2π
if (angle >= 2 * M_PI) angle -= 2 * M_PI;
if (angle < 0) angle += 2 * M_PI;
```

## Collision Detection

### Principle
Before each movement, system checks if new position is valid:
```c
if (game->map[(int)new_y][(int)new_x] != '1')
```

### Logic
- `(int)new_x` and `(int)new_y`: Convert to grid coordinates
- `!= '1'`: Check it's not a wall
- If valid → movement allowed
- If wall → movement blocked

## Configuration Parameters
- **Movement Speed**: `0.1` units per frame
- **Rotation Speed**: `0.1` radians per frame (≈ 5.7°)

---

# Documentation du Module Movement

## Vue d'ensemble
Le module movement gère toutes les mécaniques de mouvement du joueur dans l'espace 3D. Il utilise la trigonométrie pour calculer des mouvements et rotations précis tout en assurant la détection de collision avec les murs.

## Structure des Fichiers
- `m_move_player.c` - Fonctions de mouvement du joueur (avant, arrière, strafe)
- `m_rotate_player.c` - Fonction de rotation du joueur

## Concepts Mathématiques

### Trigonométrie dans le Mouvement 2D
Le mouvement dans Cub3D utilise les fonctions trigonométriques pour calculer les vecteurs de direction :
- `cos(angle)` = composante X du vecteur unitaire
- `sin(angle)` = composante Y du vecteur unitaire
- Angle en radians (0 à 2π)

### Système de Coordonnées
- **Axe X** : Horizontal (gauche ← → droite)
- **Axe Y** : Vertical (haut ↑ ↓ bas)
- **Angle 0** : Direction Est (→)
- **Angle π/2** : Direction Sud (↓)
- **Angle π** : Direction Ouest (←)
- **Angle 3π/2** : Direction Nord (↑)

### Calculs de Mouvement

#### Mouvement Avant/Arrière
```c
// Avancer dans la direction de vue
new_x = player.x + cos(player.angle) * vitesse;
new_y = player.y + sin(player.angle) * vitesse;

// Reculer (direction opposée)
new_x = player.x - cos(player.angle) * vitesse;
new_y = player.y - sin(player.angle) * vitesse;
```

#### Mouvement Latéral (Strafe)
```c
// Aller à gauche (angle - 90°)
new_x = player.x + cos(player.angle - M_PI/2) * vitesse;
new_y = player.y + sin(player.angle - M_PI/2) * vitesse;

// Aller à droite (angle + 90°)
new_x = player.x + cos(player.angle + M_PI/2) * vitesse;
new_y = player.y + sin(player.angle + M_PI/2) * vitesse;
```

## Analyse des Fonctions

### `move_forward(t_game *game)`
**Objectif** : Faire avancer le joueur dans sa direction de vue
**Algorithme** :
1. Calculer nouvelle position avec cos/sin
2. Vérifier collision avec les murs
3. Mettre à jour position si valide

### `move_backward(t_game *game)`
**Objectif** : Faire reculer le joueur
**Différence** : Utilise le signe négatif pour inverser la direction

### `move_left(t_game *game)` & `move_right(t_game *game)`
**Objectif** : Mouvement latéral (strafe)
**Principe** : Utilise l'angle ± 90° pour se déplacer perpendiculairement à la direction de vue

### `rotate_player(t_game *game, int direction)`
**Objectif** : Faire tourner le joueur autour de sa position
**Paramètres** :
- `direction = 1` : Tourner à droite
- `direction = -1` : Tourner à gauche

**Gestion du wrap-around** :
```c
// Maintenir l'angle entre 0 et 2π
if (angle >= 2 * M_PI) angle -= 2 * M_PI;
if (angle < 0) angle += 2 * M_PI;
```

## Détection de Collision

### Principe
Avant chaque mouvement, le système vérifie si la nouvelle position est valide :
```c
if (game->map[(int)new_y][(int)new_x] != '1')
```

### Logique
- `(int)new_x` et `(int)new_y` : Conversion en coordonnées de grille
- `!= '1'` : Vérifier que ce n'est pas un mur
- Si valide → mouvement autorisé
- Si mur → mouvement bloqué

## Paramètres de Configuration
- **Vitesse de Mouvement** : `0.1` unités par frame
- **Vitesse de Rotation** : `0.1` radians par frame (≈ 5.7°)