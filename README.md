# Kings And Pigs (2D Platformer, written in C++, rendering with SFML)
# About 
This is a game I've started writing as my final project for a C++ course I've taken, I couldn't finish it in time due to poor architectural design,
therefore I quickly got lost in the spaghetti code with multiple God-classes and an inability to develop new features.
So, I decided to start basically from scratch using a more structured approach and discovered Entity-Component-System which was much easier to handle and build upon.
I've taken an already existing implementaion for such system - [Entt](https://github.com/skypjack/entt/). Now, this ECS-based version on Kings-And-Pigs with be a full on 
game developing project I will do my best to develop and in the same time use as a playground to implement and learn best programming practices.
## Branches
- `main`  - Purely referencial, the moment I got stuck using OOP. **(CURRENTLY DOESN'T BUILD)**.
- `feature` - the ACTUAL main branch I am constantly pushing to, this is the Data Driven version of the game I am developing with the help of Entt.

## Dependencies 
- [Entt](https://github.com/skypjack/entt/) - ECS library I build upon.
- [SFML](https://www.sfml-dev.org/) - A c++ rendering library.
- [TmxParser](https://github.com/sainteos/tmxparser/) - The .tmx parser used to parse Tile Map Editor maps.
- [Googletest](https://github.com/google/googletest/) - Unit testing for the engine.
- [CMake](https://github.com/google/googletest/) - Cross-Platform build automation system.

# Task List (updated 14.12.2021)
- [x] Get a grasp of ECS, particularly Entt. 
- [x] Build a quick demo project using CMake.
- [X] Build an SFML example using CMake.
- [X] Re-write an example with ECS approach.
- [X] Create a wrapper Entity class for easier component managment.
- [X] Create a base Scene class for the game scenes(gameplay, menu, options ...)
- [X] Create a TextureLoader class to manage game resources.
- [X] Draw the main character with a Sprite Component and a corresponding system.
- [X] Animate the Sprite;
- [X] Create an animation pool component to switch between animations.
- [X] Create a DebugRenderer class to render sprite outlines and origins for easier collision debugging in the future
- [X] Create a map in Tile Map Editor.
- [X] Parse the tilemap and render it with SFML.
- [X] Basic input handling.
- [X] Get some basic player movement going.
- [X] Implement absolutely awful physics :heavy_check_mark: :heavy_check_mark: :heavy_check_mark: (gonna work on it)
- [X] Add support for unit testing.
- [ ] Cover existing systems with unit tests. 
- [ ] Linux build support.
- [ ] Implement a better state managing system
- [ ] Map object parsing.
- [ ] Multi-thread textures and maps loading.
- [ ] AABB Collision.
- [ ] Enemies.
- [ ] Enemy AI.
- [ ] Interraction with the enemies.
- [ ] TBD...
# Build
As I mentioned I am using CMake to generate build files for my project, it will not build on Linux in the moment but i am planning on changing it in the few days.
## IMPORTANT!!! 
SFML requires specific compliers and versions for a specific library release. The libs I am using require MinGW GCC 7.3.0 x64 which can be found [here](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/7.3.0/threads-posix/seh/x86_64-7.3.0-release-posix-seh-rt_v5-rev0.7z/download).
## Build process 

```
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
```
