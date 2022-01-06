# SDL2-sandpile
A multi-threaded [Abelian sandpile](https://en.wikipedia.org/wiki/Abelian_sandpile_model) simulation written in C++, using SDL2.

### Dependancies
- A c++20 compiler (for barrier)
- SDL2

### Building

``` bash
mkdir build
cd build
cmake ..
make
```


### Getting Started

Look at the main.cpp file in the src folder. It does boilerplate SDL initialization and creates the sandpile for you easily. Simply change the global variables to set window and sandpile dimensions. 

Initialize the sandpile by placing sand wherever you please. This example places 10000 pieces of sand in the middle of the simulation. Each cell initializes to 0 pieces of sand. You can also use 'world.set_sand(x, y, value)' to set instead of add sand.

``` c++
world.add_sand(world.width() / 2, world.height() / 2, 10000);
```

If you want to change the default colors, then use:
``` c++
world.set_colors(
  {.r = 255, .g = 255, .b = 255}, // 0 grains
  {.r = 0,   .g = 255, .b = 0},   // 1 grains
  {.r = 128, .g = 0,   .b = 128}, // 2 grains
  {.r = 255, .g = 215, .b = 0},   // 3 grains
  {.r = 255, .g = 255, .b = 255}  // > 3 grains
);
```

When you are ready to run the simulation simply call:

``` c++
  world.start(6);
  world.join();
```

This will run the simulation with 6 threads. The function 'join' will be called when the window is closed and performs some cleanup. 

### Controls

#### Normal Mode

##### The sandpile will render and simulation will run.

| Syntax                         | Description                                        |
| ------------------------------ | -------------------------------------------------- |
| **scroll wheel**               | zoom in/out                                        |
| **click + drag**               | pan                                                |
| **p**                          | pause renderer                                     |
| **s**                          | save sandpile (saved in current working directory) |
| **e**                          | enter edit mode                                    |
  

#### Edit Mode

##### The rendering and simulation will pause and clicking on a cell in the simulation will add 1000 sand.

| Syntax                       | Description                                        |
| ---------------------------- | -------------------------------------------------- |
| **scroll wheel**             | zoom in/out                                        |
| **left ctrl + click + drag** | pan                                                |
| **s**                        | save sandpile (saved in current working directory) |
| **e**                        | enter normal mode                                  |

#### Links
- [Abelian sandpile](https://en.wikipedia.org/wiki/Abelian_sandpile_model) 
- [Sandpiles - Numberphile](https://www.youtube.com/watch?v=1MtEUErz7Gg&ab_channel=Numberphile)