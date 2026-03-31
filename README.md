This is the README file.

Project:
- src folder:   main.c, headers
- bin:          compiled code

build using:
``` bash
gcc $(sdl2-config --cflags) src/main.c src/engine.c src/maths.c src/rasterizer.c -o bin/p $(sdl2-config --libs) -lm
```
