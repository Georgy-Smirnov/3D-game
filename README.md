# TestRaycast

This project is First-person 3D representation of a maze using <a href="https://ru.wikipedia.org/wiki/Ray_casting">raycasting</a>, similar to Wolfenstein 3D (1992).

In this project use MiniLibX, a simplified version of the Xlib. It can only run in MacOS.

### For start

Using ``make start`` for start with standart ``map.cube``.

### Controls

For move use ``W`` ``A`` ``S`` ``D``. For rotate around use ``←`` and ``→``. For exit, press ``ESC`` or click the red cross.

### Configurations

For change configurations open file ``map.cub`` or create new file with ``.cub``

In file:
+ resolution screen
+ Path ``.xpm`` textures for notrh, south, east, west walls and sprites.
+ Color for floor and ceiling in RGB format
+ Map, where:
  + ``1`` - wall;
  + ``0`` - floor;
  + ``2`` - sprite;
  + ``N`` or ``S`` or ``W`` or ``E`` - start player position;

Use ``make`` to pack project. For start ``./cube3D`` and file ``.cube``. if use ``--save`` programm create first rendering image in ``bmp`` format.
Example: 
```bash
make ; ./cub3D map.cub --save
```

