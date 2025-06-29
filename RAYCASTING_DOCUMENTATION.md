# Raycasting Documentation - Cube3D

## Overview

The raycasting system in this Cube3D implementation is based on the Digital Differential Analyzer (DDA) algorithm, which efficiently traces rays from the player's position to find wall intersections. This creates a pseudo-3D environment by casting rays across the field of view and calculating wall distances.

## Core Concepts

### 1. Raycasting Basics
- **Ray**: A line cast from the player's position in a specific direction
- **Field of View (FOV)**: The angle range visible to the player (60° = π/3 radians)
- **Ray Angle**: The direction of each individual ray within the FOV
- **Wall Hit**: The point where a ray intersects with a wall

### 2. Coordinate System
- **Player Position**: Stored as floating-point coordinates (x, y)
- **Map Coordinates**: Integer grid coordinates for wall detection
- **World Coordinates**: Floating-point coordinates for precise positioning

## Data Structures

### t_ray_pos
```c
typedef struct s_ray_pos
{
    double  pos_x;      // Player's X position in world coordinates
    double  pos_y;      // Player's Y position in world coordinates
    int     map_x;      // Current map grid X coordinate
    int     map_y;      // Current map grid Y coordinate
} t_ray_pos;
```

### t_ray_dir
```c
typedef struct s_ray_dir
{
    double  ray_dir_x;      // Ray direction vector X component
    double  ray_dir_y;      // Ray direction vector Y component
    double  delta_dist_x;   // Distance to next X grid line
    double  delta_dist_y;   // Distance to next Y grid line
    double  side_dist_x;    // Distance to next X grid line from current position
    double  side_dist_y;    // Distance to next Y grid line from current position
    int     step_x;         // Step direction in X (-1 or 1)
    int     step_y;         // Step direction in Y (-1 or 1)
} t_ray_dir;
```

### t_ray_hit
```c
typedef struct s_ray_hit
{
    double  distance;   // Perpendicular distance to wall
    int     map_x;      // Wall map X coordinate
    int     map_y;      // Wall map Y coordinate
    int     side;       // Wall side (0 = X-axis, 1 = Y-axis)
    double  wall_x;     // Exact wall hit position (0.0 to 1.0)
} t_ray_hit;
```

## Algorithm Flow

### 1. Ray Initialization (`init_ray_vars`)
```c
static void init_ray_vars(t_game *game, double ray_angle, 
                         t_ray_pos *pos, t_ray_dir *dir)
```

**Purpose**: Sets up the initial ray parameters for DDA algorithm.

**Steps**:
1. **Player Position**: Convert player grid position to world coordinates
2. **Ray Direction**: Calculate ray direction vector using trigonometry
3. **Delta Distances**: Calculate distance to next grid lines
4. **Step and Side Distances**: Determine initial step direction and distances

**Mathematical Formulas**:
- `ray_dir_x = cos(ray_angle)`
- `ray_dir_y = sin(ray_angle)`
- `delta_dist_x = |1 / ray_dir_x|` (avoid division by zero)
- `delta_dist_y = |1 / ray_dir_y|` (avoid division by zero)

### 2. DDA Algorithm (`perform_dda`)
```c
static int perform_dda(t_game *game, t_ray_pos *pos, 
                      t_ray_dir *dir, int *side)
```

**Purpose**: Performs the Digital Differential Analyzer algorithm to find wall intersections.

**Algorithm**:
1. **Compare Distances**: Choose the shorter distance to next grid line
2. **Step Forward**: Move one grid unit in the chosen direction
3. **Update Distances**: Add delta distance to the chosen axis
4. **Check for Wall**: Test if new position contains a wall
5. **Repeat**: Continue until wall is hit

**Key Insight**: DDA ensures we always step to the nearest grid line, making the algorithm efficient and accurate.

### 3. Distance Calculation
```c
// For X-axis walls (side = 0)
hit.distance = (pos.map_x - pos.pos_x + (1 - dir.step_x) / 2) / dir.ray_dir_x;

// For Y-axis walls (side = 1)
hit.distance = (pos.map_y - pos.pos_y + (1 - dir.step_y) / 2) / dir.ray_dir_y;
```

**Purpose**: Calculate the perpendicular distance to the wall to avoid fisheye distortion.

**Formula Explanation**:
- `(1 - step) / 2`: Adjusts for grid cell boundaries
- Division by ray direction: Converts to perpendicular distance

### 4. Wall Hit Position (`wall_x`)
```c
// For X-axis walls
hit.wall_x = pos.pos_y + hit.distance * dir.ray_dir_y;

// For Y-axis walls
hit.wall_x = pos.pos_x + hit.distance * dir.ray_dir_x;

hit.wall_x -= floor(hit.wall_x);  // Keep value between 0.0 and 1.0
```

**Purpose**: Calculate the exact position where the ray hit the wall for texture mapping.

## Rendering Loop

### Main Rendering Process (`render_loop`)
```c
int render_loop(void *param)
```

**Process**:
1. **Calculate FOV Range**: `start_angle = player_angle - FOV/2`
2. **Cast Rays**: For each screen column (0 to win_w)
3. **Ray Angle**: `ray_angle = start_angle + (x / win_w) * FOV`
4. **Cast Ray**: `hit = cast_ray(game, ray_angle)`
5. **Draw Wall Slice**: `draw_wall_slice(game, x, &hit, ray_angle)`

**Ray Distribution**:
- Screen width: 640 pixels
- FOV: 60° (π/3 radians)
- Ray angle increment: `FOV / win_w` radians per pixel

## Performance Optimizations

### 1. Efficient Wall Detection
- Uses integer map coordinates for wall checking
- Avoids floating-point comparisons in collision detection

### 2. DDA Algorithm Benefits
- Always steps to the nearest grid line
- No need to check every pixel along the ray
- Logarithmic complexity: O(log n) where n is map size

### 3. Distance Calculation
- Perpendicular distance prevents fisheye effect
- Single calculation per ray, no additional trigonometry

## Visual Effects

### 1. Wall Height Calculation
```c
line_height = (int)(win_h / hit.distance)
```

**Principle**: Closer walls appear taller due to perspective projection.

### 2. Texture Mapping
- `wall_x` determines which texture column to use
- `tex_x = (int)(hit.wall_x * texture_width)`
- Vertical scaling based on wall distance

### 3. Side Detection
- Different textures for X-axis vs Y-axis walls
- Enables directional wall rendering

## Common Issues and Solutions

### 1. Fisheye Distortion
**Problem**: Walls appear curved when using direct distance.
**Solution**: Use perpendicular distance calculation.

### 2. Texture Stretching
**Problem**: Textures appear stretched on walls.
**Solution**: Proper texture coordinate calculation and clamping.

### 3. Collision Detection
**Problem**: Player can pass through walls.
**Solution**: Integer-based map coordinate checking.

## Mathematical Foundation

### Trigonometry
- **Ray Direction**: `(cos(angle), sin(angle))`
- **Distance**: Euclidean distance with perpendicular correction
- **Texture Mapping**: Linear interpolation based on wall hit position

### Coordinate Systems
- **World Space**: Continuous floating-point coordinates
- **Map Space**: Discrete integer grid coordinates
- **Screen Space**: Pixel coordinates for rendering

## File Structure

```
src/raycasting/
├── r_cast.c          # Main raycasting algorithm
└── r_loop.c          # Rendering loop and ray distribution

includes/
└── cube3d.h          # Data structures and constants
```

## Constants

```c
#define FOV (M_PI / 3)    // 60 degrees in radians
#define WIN_W 640         // Screen width
#define WIN_H 480         // Screen height
```

## Usage Example

```c
// Cast a single ray
double ray_angle = player_angle + 0.1;  // Slightly to the right
t_ray_hit hit = cast_ray(game, ray_angle);

// Use the hit information
printf("Wall distance: %f\n", hit.distance);
printf("Wall side: %s\n", hit.side == 0 ? "X-axis" : "Y-axis");
printf("Wall position: %f\n", hit.wall_x);
```

This raycasting system provides the foundation for creating immersive 3D environments with efficient wall detection and realistic perspective rendering. 