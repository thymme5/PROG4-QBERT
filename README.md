# Q*bert – Custom C++ Game Engine & Game Implementation

## 🕹️ Overview

This project is a faithful recreation of the classic **Q*bert** arcade game, developed using a custom-built C++ game engine. Designed as part of a programming assignment, the engine emphasizes modularity, component-driven architecture, and modern C++ design patterns. It includes full support for audio, input, rendering, and scene transitions, with extensive use of **SDL2** and **nlohmann/json** for asset and level handling and uses mingin as a base.

---

## 🛠️ Engine Highlights

### 🎮 Component-Based Architecture

GameObjects are modular entities composed of reusable components:
- `TransformComponent`, `TextureComponent`, `TextComponent`
- `QbertMoveComponent`, `CoilyComponent`, `EdgeEnemyComponent`
- `TileComponent`, `GameplayManagerComponent`

This design promotes flexibility and isolates responsibilities across behaviors.

### 🖼️ Scene Management

Custom `SceneManager` handles:
- Dynamic scene loading and switching
- Scene lifecycle: `Enter()`, `Exit()`, `Update()`
- Separate scenes for Main Menu, Gameplay, High Score, Game Over, Victory which allows for seamless switching between scenes. This was very easy to work with and I really liked this implementation.
- Added a way to remove scenes by queing them and cleaning it up at the end of the frame. 

### 🎮 Input System

- Built around a **command pattern**, supporting **keyboard and controller** input.
- Fully dynamic **multi-player binding** using input indexing.
- Scene transitions trigger **input rebinding** to avoid dangling references or overlap.

### 🔊 Audio System

- Managed via a **Service Locator pattern** with centralized control through `QbertSoundLibrary`.
- Preloads audio assets mapped to enums (`SoundID`) for efficient access and organization.

---

## 📄 Level & Tile System

### JSON-Driven Level Design

Levels are data-driven using external **JSON files** that define:
- Tile map layout and positions
- Jump behavior: single jump, double jump, toggle jump
- Starting positions for Q*bert, enemies, and disks

The `LevelBuilder` parses these definitions and constructs the level dynamically.

### Tile Logic

Each tile can exhibit one of the following behaviors:
- **1-jump**: default → target
- **2-jump**: default → intermediate → target
- **Toggle mode**: toggles between two states each time it's stepped on

### Tile-State Decoupling

Tile color transitions are **abstracted away** from rendering/game logic. This keeps the system extendable for future variations or game modes.

---

## ⚙️ Design Principles

### Smart Pointer Usage

- All ownership and lifetime management is handled via `std::shared_ptr` or raw pointers with clear lifetimes.
- Manual memory handling is avoided to prevent leaks and dangling references.

### Singleton vs Static

- Singleton pattern is used where global access is justified (e.g., `InputManager`, `HighscoreManager`, `ResourceManager`).
- Stateless classes like `LevelBuilder` use static access patterns to remain lightweight.

### Separation of Concerns

- Core engine systems (rendering, input, audio) are decoupled from game-specific logic.
- Game-specific systems like `QbertSceneBuilder` and `GameMode` classes (e.g., `SinglePlayerMode`, `VersusMode`) are cleanly separated.

### Gameplay Extension

- Engine was built with extensibility in mind:
  - New modes like Co-op and Versus can be added with minimal scene setup tweaks.
  - Tile behaviors and enemy logic can be easily overridden or extended via component logic.
---

## 🚧 Known Limitations

- `InputManager` assumes a fixed update rate (~60 FPS); deltaTime scaling not yet supported.
- Some tight coupling exists between components (e.g., `CoilyComponent` holds direct pointer to Q*bert) which is not ideal and difficult to work with.
- `InputManager` uses polling; could be improved using event queue model.

---


