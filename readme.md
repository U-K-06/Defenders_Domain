# Defender's Domain

## Overview
**Defender's Domain** is a **command-line interface** (CLI) game where players defend their **domain** from incoming enemies displayed as **ASCII characters**. The game is developed in **C++** and leverages the **Windows API** for audio playback. Players **strategically** place various types of towers on a grid to destroy **enemies** before they reach the door. Each tower has **unique** properties and can be upgraded over time to enhance gameplay. The game features simple **ASCII-based graphics** and offers a challenging and engaging experience.

## Project Structure

The project contains the following files and directories:

- `audio/` - This directory contains audio files used in the game.
- `constants.h` - Header file that defines all constants used throughout the project.
- `draw.cpp` - Source file that contains the logic for rendering the game graphics.
- `draw.h` - Header file that declares the functions in `draw.cpp`.
- `game.cpp` - Source file that contains the main game logic.
- `game.h` - Header file that declares the functions in `game.cpp`.
- `main.cpp` - The entry point of the application where execution begins.
- `PTD.exe` - The compiled executable for Windows.
- `screenshots/` - This directory contains screenshots of the game.
- `LICENSE` - The license file for the project.

## Features
- The game features simple **ASCII-based graphics**.
- Players can place **mines** on the battlefield to destroy **enemies.**
- Choose from **different types of mines** to enhance gameplay.
- Various types of mines with **unique properties** for **increased strategic** and **versatile gameplay.**
<h1>How to Play</h1>

<p>Welcome to the <strong>Defender's Domain</strong>! Your goal is to strategically place different types of bombs to defeat enemies and reach the door.</p>

<hr>

<h2>Controls & Key Bindings</h2>

<table border="1" cellpadding="5" cellspacing="0" style="border-collapse: collapse;">
  <thead>
    <tr>
      <th>Key</th>
      <th>Action Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><strong>Arrow Keys</strong></td>
      <td>Move your cursor around the grid to select where to place bombs or interact with objects.</td>
    </tr>
    <tr>
      <td><strong>Enter</strong></td>
      <td>Confirm selection or place a bomb on the currently selected grid cell.</td>
    </tr>
    <tr>
      <td><strong>Number keys (1-7)</strong></td>
      <td>Switch between different types of bombs to select which one you want to place. Each bomb type has unique abilities and effects.</td>
    </tr>
    <tr>
      <td><strong>Spacebar</strong></td>
      <td>Activate or toggle the bomb placement mode. When active, you can place bombs on the grid.</td>
    </tr>
    <tr>
      <td><strong>Escape</strong></td>
      <td>Pause the game or open the menu (if implemented).</td>
    </tr>
  </tbody>
</table>

<hr>

<h2>Game Elements</h2>
<ul>
  <li><strong>Grid Cells</strong>: The game board where you move and place bombs.</li>
  <li><strong>Bomb Types</strong>: Different elemental bombs such as Electro, Fire, Poison, Water, Ice, Wind, and Shadow.</li>
  <li><strong>Enemies</strong>: Various colored characters on the grid that you need to defeat with your bombs.</li>
  <li><strong>Timer & Score</strong>: Track your time and points earned by defeating enemies.</li>
</ul>

<hr>

<h2>Gameplay Tips</h2>
<ul>
  <li>Use <strong>number keys</strong> to cycle through bombs with different levels and effects.</li>
  <li>Move your cursor using <strong>arrow keys</strong> and press <strong>Enter</strong> to plant the selected bomb.</li>
  <li>Toggle bomb placement mode using the <strong>Spacebar</strong>.</li>
  <li>Watch bomb stats (level, explosion time, blast range) displayed next to the grid.</li>
  <li>Defeat enemies by strategically placing bombs.</li>
</ul>

<hr>

<h2>Visual Cues in the Game</h2>
<ul>
  <li><span style="color:red; font-weight:bold;">Red Highlight</span>: Shows the active cell ready for bomb placement.</li>
  <li><strong>Colored Letters</strong>: Represent different enemy types on the grid.</li>
  <li><strong>Bomb Symbols</strong>: Indicate bombs placed on grid cells, showing type and level.</li>
</ul>
<p>Good luck and have fun!</p>

## Screenshots
Some screenshots of the game are shown below:

### Screenshot 1:
![Initial Grid](./screenshots/Game_ss_1.png)

### Screenshot 2:
![Gameplay](./screenshots/Game_ss_2.png)

To compile the program, you need to have a C++ compiler installed on your system. Below are the commands for compiling the project on different operating systems and compilers:

## Requirements
- C++ Compiler
- Windows API

# Compiling the Program
### Windows
Open your command prompt and run the following command:
### GCC
```
g++ main.cpp game.cpp draw.cpp -o DD.exe -lwinmm
```

### MSVC
``` 
cl main.cpp Game.cpp draw.cpp /FeDD.exe /link winmm.lib
```
## End
If you liked this project you are free to fork it for your own use as well!.

<footer>Project Co-Developed by @JayanshDevgan(Jayansh Devgan) and @U-K-06(Utkarsh Khajuria)</footer>
