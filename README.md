
# Pacman-C_ncurses

## Welcome
Welcome to Pacman-C_ncurses, a school project developed in December 2023.

## Description
This project is implemented in C and utilizes the ncurses library to create a Text-based User Interface (TUI). It is designed to be compiled and run on Linux systems.

## Project Overview

The goal of the game is to move a character named Pac-Man through a maze to eat all the small yellow pellets present. Within this maze, there are 1 to 4 ghosts that are the enemies of Pac-Man. The user must avoid being caught by any of these ghosts.

## Key Features to Implement

### 1 - Grid Implementation
- Program the grid as a 2D array. Define values for obstacles and cells with pellets.
- Initially, use a modest grid size (e.g., 10x10 or smaller for initial tests).
- Hardcode the grid with a 2D array initialization.

### 2 - Maze Visualization
- Program the functionality to visualize the maze. Initially, use a console interface with the `printf()` function.

### 3 - Ghost Selection
- Program the functionality to allow the user to choose the number of ghosts (1 to 4).

### 4 - Random Ghost Placement
- Program the functionality to place ghosts randomly within the maze, avoiding walls.

### 5 - Pac-Man Movement
- Program the functionality for Pac-Man to move randomly without touching the walls.

### 6 - Score Management
- Implement scoring, such as tracking the number of pellets eaten.

## 7 - Bonus Features (Using ncurses.h)

### 7.1 -  User-Controlled Pac-Man Movement
- Program the functionality to allow the user to move Pac-Man using keyboard inputs.

### 7.2 - Game Save and Load
- Program the functionality to save and load a game in progress.

### 7.3 - Pac-Man Rules
- Implement the rules of Pac-Man, including ghost behavior and power pellets.

## Screenshots

![App Screenshot](https://i.ibb.co/GFM3mbK/image.png)

![App Screenshot](https://i.ibb.co/gwVbD32/image2.png)

![App Screenshot](https://i.ibb.co/x35bt6n/image3.png)

## Installation
(Before proceeding, please install ncurses.h on Linux or via WSL on Windows)

To compile and run this project, follow these steps :
1. Clone the repository using `git clone` or Download ZIP.
2. Navigate to the project directory using `cd Pacman-C_ncurses/src`.
3. Compile the project using :

(First part of the project)
```
gcc random_pacman.c -o random_pacman && ./pacman1
```

(Second part of the project with ncurses.h)
```
gcc pacman.c -o pacman -lncurses && ./pacman
```

## Status Update

I've implemented a system for harvesting fruit that appears on the map, as well as changing the colour of ghosts when Pac-Man eats a power pill.

I didn't have the time to implement Pac-Man so that he could eat the ghosts, nor the ghosts' movements using complex algorithms such as A* or Dijkstra.
