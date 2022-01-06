# SDL2-sandpile
A multi-threaded [Abelian sandpile](https://en.wikipedia.org/wiki/Abelian_sandpile_model){:target="_blank"} simulation written in C++, using SDL2.

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