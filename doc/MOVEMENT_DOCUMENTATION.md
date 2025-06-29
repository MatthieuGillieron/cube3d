# Documentation du Système de Mouvement - Cub3D

## Vue d'ensemble

Le système de mouvement de Cub3D utilise la **trigonométrie** pour calculer les déplacements du joueur dans un espace 2D. Le joueur peut se déplacer dans 4 directions et tourner sur lui-même.

## Architecture

### Fichiers concernés
- `src/movement/m_move_player.c` : Fonctions de déplacement
- `src/movement/m_rotate_player.c` : Fonction de rotation
- `src/events/e_window.c` : Gestionnaire d'événements clavier

### Structure du joueur
```c
typedef struct s_player
{
    double  x;          // Position X (coordonnées réelles)
    double  y;          // Position Y (coordonnées réelles)
    char    direction;  // Direction initiale (N/S/E/W)
    double  angle;      // Angle de vue en radians (0 à 2π)
} t_player;
```

## Mathématiques des mouvements

### Système de coordonnées
- **X** : Axe horizontal (gauche ← → droite)
- **Y** : Axe vertical (haut ↑ ↓ bas)
- **Angle 0** : Direction Est (→)
- **Angle π/2** : Direction Sud (↓)
- **Angle π** : Direction Ouest (←)
- **Angle 3π/2** : Direction Nord (↑)

### Calculs trigonométriques

#### Mouvement avant/arrière
```c
// Avancer dans la direction du regard
new_x = player.x + cos(player.angle) * vitesse;
new_y = player.y + sin(player.angle) * vitesse;

// Reculer (direction opposée)
new_x = player.x - cos(player.angle) * vitesse;
new_y = player.y - sin(player.angle) * vitesse;
```

#### Mouvement latéral (strafe)
```c
// Aller à gauche (angle - 90°)
new_x = player.x + cos(player.angle - M_PI/2) * vitesse;
new_y = player.y + sin(player.angle - M_PI/2) * vitesse;

// Aller à droite (angle + 90°)
new_x = player.x + cos(player.angle + M_PI/2) * vitesse;
new_y = player.y + sin(player.angle + M_PI/2) * vitesse;
```

## Fonctions détaillées

### 1. `move_forward(t_game *game)`
**Objectif** : Faire avancer le joueur dans sa direction de vue

**Algorithme** :
1. Calculer nouvelle position avec `cos()` et `sin()`
2. Vérifier collision avec les murs
3. Mettre à jour position si valide

**Code** :
```c
void move_forward(t_game *game)
{
    double new_x = game->player.x + cos(game->player.angle) * 0.1;
    double new_y = game->player.y + sin(game->player.angle) * 0.1;
    
    if (game->map[(int)new_y][(int)new_x] != '1')
    {
        game->player.x = new_x;
        game->player.y = new_y;
    }
}
```

### 2. `move_backward(t_game *game)`
**Objectif** : Faire reculer le joueur

**Différence** : Utilise le **signe négatif** pour inverser la direction

### 3. `move_left(t_game *game)` et `move_right(t_game *game)`
**Objectif** : Déplacement latéral (strafe)

**Principe** : Utilise l'angle ± 90° pour se déplacer perpendiculairement à la vue

### 4. `rotate_player(t_game *game, int direction)`
**Objectif** : Faire tourner le joueur sur lui-même

**Paramètres** :
- `direction = 1` : Rotation droite
- `direction = -1` : Rotation gauche

**Gestion du wrap-around** :
```c
// Maintenir l'angle entre 0 et 2π
if (angle >= 2 * M_PI) angle -= 2 * M_PI;
if (angle < 0) angle += 2 * M_PI;
```

## Détection de collision

### Principe
Avant chaque mouvement, le système vérifie si la nouvelle position est valide :

```c
if (game->map[(int)new_y][(int)new_x] != '1')
```

### Logique
- `(int)new_x` et `(int)new_y` : Conversion en coordonnées de grille
- `!= '1'` : Vérification que ce n'est pas un mur
- Si valide → mouvement autorisé
- Si mur → mouvement bloqué

## Contrôles clavier

### Mapping des touches (macOS)
| Touche | Keycode | Fonction | Action |
|--------|---------|----------|--------|
| W | 13 | `move_forward()` | Avancer |
| S | 1 | `move_backward()` | Reculer |
| A | 0 | `move_left()` | Strafe gauche |
| D | 2 | `move_right()` | Strafe droite |
| ← | 123 | `rotate_player(-1)` | Tourner gauche |
| → | 124 | `rotate_player(1)` | Tourner droite |
| ESC | 53 | `close_window()` | Quitter |

### Gestionnaire d'événements
```c
int key_press(int keycode, t_game *game)
{
    if (keycode == 53)
        close_window(game);
    else if (keycode == 13)
        move_forward(game);
    // ... autres touches
    return (0);
}
```

## Paramètres de configuration

### Vitesses
- **Déplacement** : `0.1` unité par frame
- **Rotation** : `0.1` radian par frame (≈ 5.7°)

### Optimisations possibles
```c
#define MOVE_SPEED 0.1
#define ROTATE_SPEED 0.1

// Utilisation dans les fonctions
new_x = player.x + cos(angle) * MOVE_SPEED;
```

## Avantages du système

### ✅ Fluidité
- Coordonnées en `double` pour mouvements précis
- Pas de saccades grâce aux calculs trigonométriques

### ✅ Réalisme
- Mouvement dans la direction du regard
- Strafe perpendiculaire à la vue
- Rotation continue

### ✅ Sécurité
- Détection de collision systématique
- Pas de traversée de murs
- Gestion des angles (wrap-around)

## Débogage

### Problèmes courants
1. **Joueur traverse les murs** → Vérifier la détection de collision
2. **Mouvements saccadés** → Utiliser `double` au lieu d'`int`
3. **Rotation incorrecte** → Vérifier le wrap-around des angles
4. **Strafe inversé** → Vérifier les signes ± dans les calculs

### Tests recommandés
- Tester chaque direction individuellement
- Vérifier les collisions sur tous les bords
- Tester la rotation complète (360°)
- Vérifier les mouvements diagonaux

## Conclusion

Ce système de mouvement offre une expérience fluide et réaliste pour naviguer dans l'environnement 3D de Cub3D, en utilisant des principes mathématiques solides et une détection de collision fiable.