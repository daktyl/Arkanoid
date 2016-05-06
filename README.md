# Arkanoid
A basic clone of 2D retro game called "Arkanoid"

# Build instructions
```
$ cmake .
$ make
```
# Configuration
**Use config.ini file to adjust game settings to your needs.**

```
Slowmotion=0  Sets FPS to fixed value of 60.0. The whole game runs at normal speed.

Slowmotion=1  Sets FPS to fixed value of 30.0. The whole game slows down because its speed is linked to FPS.

Difficulty=0  Easiest difficulty. Bouncer speed is not affected by the number of wall-bounces.

Difficulty=1  Medium difficulty. Bouncer speed increases when it hits the wall or the ceiling and decreases
              when it hits the block.

Difficulty=2  Hardest difficulty. The same as medium + base speed of the bouncer is higher.

Debug=1       Prints more debug information to the console.

Width         Sets game resolution (X axis).

Height        Sets game resolution (Y axis).
```

# Too old CMake version?
Try to change the minimum required version in CMakeLists.txt to match the version you have installed. There shouldn't be any issues.
