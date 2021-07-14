`Author(s)`: Billy Bertrand

`Project Description`: 

A simple 2D ray caster. Light rays are emitted from a single light source, in every direction. I was inspired by the Coding train's thumbnail on the matter. So I decided to build my own version. I also wanted to understand what a game loop is, and undergo the research process to build one.

`Why this project?`:

I was inspired by a video from the Coding Train's YouTube chanel. So, I decided to build my own version. I also wanted to understand what a game loop is, and undergo the research process to implement one :)

`Technologies, Tools, or Frameworks used`: 

CMake and SDL

`Complications`:

- I got an `undefinied reference` for calling `SDL_Init()` function. The error occured because the linker did not know where to find the actual definition (or implemention) of the function, and "link" it.

- The `SDL` window, once generated, immedialtely closed. The fix to that was to implement a game loop that would maintain the windown open until some event occured to close it.

- For my first run, I set the frame rate at `30 FPS`. The light source's position was lagging bhid the mouse cursor's position. The reason what that the `update()` function had to wait for "too long" before updating the position of the light source on the screen. So, by increasing the frame rate, I decreased the time `update` had to wait before doing its job. This resulted in *much* more responsive result.

`Result`:

This is to what the ray caster looks like:

![2D Ray Caster GIF](https://github.com/billy-bertrand/2d-raycaster/blob/master/rayCasterDemo.gif)

`Potential Improvements`:

- Lines are aliased. An anti-aliased drawing algorithm would lead to a "smoother" result.

- The overall code organization of the project can be improved. Separating code in `source` and `header` files would be an interesting move.

`Useful Resources`:

- https://computergraphics.stackexchange.com/questions/8916/sdl2-compiler-throws-undefined-reference

- https://stackoverflow.com/questions/10409032/why-am-i-getting-undefined-reference-to-sqrt-error-even-though-i-include-math

- https://stackoverflow.com/questions/9809213/what-are-a-and-so-files

- https://www.udemy.com/course/game-loop-c-sdl/

- https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect