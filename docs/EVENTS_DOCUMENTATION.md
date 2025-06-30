# Events Module Documentation

## Overview
The events module handles all user interactions and window management in the Cub3D project. It manages keyboard inputs, window events, and provides the interface between user actions and game logic.

## Files Structure
- `e_window.c` - Window and keyboard event management

## Core Concepts

### Event-Driven Programming
Event-driven programming is a paradigm where the program flow is determined by events such as user actions (key presses, mouse clicks) or system messages. In Cub3D, we use MLX library's event system.

### MLX Event System
MLX provides hooks to register callback functions that are called when specific events occur:
- `mlx_hook()` - Register event callbacks
- `mlx_key_hook()` - Register key press callbacks
- `mlx_loop()` - Start the event loop

## Functions Analysis

### `close_window(t_game *game)`
**Purpose**: Safely close the game window and exit the program
**Process**:
1. Destroy MLX window using `mlx_destroy_window()`
2. Exit program with `exit(0)`

### `key_press(int keycode, t_game *game)`
**Purpose**: Handle keyboard input and trigger appropriate actions
**Key Mappings** (macOS):
- `53` (ESC) → Close window
- `13` (W) → Move forward
- `1` (S) → Move backward  
- `0` (A) → Move left
- `2` (D) → Move right
- `123` (←) → Rotate left
- `124` (→) → Rotate right

**Process**:
1. Check keycode against known values
2. Call appropriate movement/action function
3. Return 0 (required by MLX)

## Technical Implementation

### Event Registration
```c
mlx_hook(game->win, 2, 1L<<0, key_press, game);
mlx_hook(game->win, 17, 1L<<17, close_window, game);
```

### Key Code Detection
Key codes are platform-specific integers. On macOS:
- Letters: A=0, S=1, D=2, W=13
- Arrows: Left=123, Right=124
- Special: ESC=53

## Error Handling
- Functions return appropriate values for MLX compatibility
- Safe window destruction prevents memory leaks
- Graceful program termination

---

# Documentation du Module Events

## Vue d'ensemble
Le module events gère toutes les interactions utilisateur et la gestion des fenêtres dans le projet Cub3D. Il gère les entrées clavier, les événements de fenêtre, et fournit l'interface entre les actions utilisateur et la logique du jeu.

## Structure des Fichiers
- `e_window.c` - Gestion des événements fenêtre et clavier

## Concepts Fondamentaux

### Programmation Événementielle
La programmation événementielle est un paradigme où le flux du programme est déterminé par des événements tels que les actions utilisateur (pressions de touches, clics souris) ou les messages système. Dans Cub3D, nous utilisons le système d'événements de la bibliothèque MLX.

### Système d'Événements MLX
MLX fournit des hooks pour enregistrer des fonctions de rappel appelées lors d'événements spécifiques :
- `mlx_hook()` - Enregistrer des callbacks d'événements
- `mlx_key_hook()` - Enregistrer des callbacks de pression de touches
- `mlx_loop()` - Démarrer la boucle d'événements

## Analyse des Fonctions

### `close_window(t_game *game)`
**Objectif** : Fermer proprement la fenêtre du jeu et quitter le programme
**Processus** :
1. Détruire la fenêtre MLX avec `mlx_destroy_window()`
2. Quitter le programme avec `exit(0)`

### `key_press(int keycode, t_game *game)`
**Objectif** : Gérer les entrées clavier et déclencher les actions appropriées
**Mapping des Touches** (macOS) :
- `53` (ESC) → Fermer fenêtre
- `13` (W) → Avancer
- `1` (S) → Reculer
- `0` (A) → Aller à gauche
- `2` (D) → Aller à droite
- `123` (←) → Tourner à gauche
- `124` (→) → Tourner à droite

**Processus** :
1. Vérifier le keycode contre les valeurs connues
2. Appeler la fonction de mouvement/action appropriée
3. Retourner 0 (requis par MLX)

## Implémentation Technique

### Enregistrement d'Événements
```c
mlx_hook(game->win, 2, 1L<<0, key_press, game);
mlx_hook(game->win, 17, 1L<<17, close_window, game);
```

### Détection des Codes de Touches
Les codes de touches sont des entiers spécifiques à la plateforme. Sur macOS :
- Lettres : A=0, S=1, D=2, W=13
- Flèches : Gauche=123, Droite=124
- Spéciales : ESC=53

## Gestion d'Erreurs
- Les fonctions retournent des valeurs appropriées pour la compatibilité MLX
- Destruction sécurisée des fenêtres pour éviter les fuites mémoire
- Terminaison gracieuse du programme