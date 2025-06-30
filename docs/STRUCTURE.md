# Structure Professionnelle - Cube3D

```
cube3d/
├── Makefile
├── includes/
│   └── cube3d.h
├── src/
│   ├── main.c
│   ├── init/
│   │   ├── init_game.c
│   │   ├── init_player.c
│   │   └── init_mlx.c
│   ├── parsing/
│   │   ├── parse_file.c
│   │   ├── parse_textures.c
│   │   ├── parse_colors.c
│   │   ├── parse_map.c
│   │   └── validate_map.c
│   ├── raycasting/
│   │   ├── raycast.c
│   │   ├── dda.c
│   │   ├── wall_calc.c
│   │   └── texture_calc.c
│   ├── render/
│   │   ├── render.c
│   │   ├── draw_wall.c
│   │   ├── draw_floor.c
│   │   └── draw_ceiling.c
│   ├── events/
│   │   ├── key_events.c
│   │   ├── mouse_events.c
│   │   └── window_events.c
│   ├── movement/
│   │   ├── move_player.c
│   │   ├── rotate_player.c
│   │   └── collision.c
│   └── utils/
│       ├── cleanup.c
│       ├── error.c
│       ├── math_utils.c
│       └── string_utils.c
|
|
├── maps/            
│   ├── simple.cub
│   ├── complex.cub
│   ├── test.cub
│   └── bonus.cub
├── textures/          
│   ├── wall_north.xpm
│   ├── wall_south.xpm
│   ├── wall_east.xpm
│   └── wall_west.xpm
├── libft/
└── mlx/
```