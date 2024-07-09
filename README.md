# Geometry War

Geometry War is a dynamic and engaging game developed using SFML and C++. This project involves building a game engine from scratch using the Entity-Component-System (ECS) architecture. The game engine can create objects as entity instances, add components to entities, handle user input, pause the game, and load game data from files.



## Demo Video
https://github.com/wasim395/Geometry_Wars/assets/168566160/72337843-c5af-40b6-962a-5010c8d3cfa2

---

## Features

- **Entity-Component-System (ECS) Architecture**: Flexible and scalable design for game object creation and component integration.
- **User Input Handling**: Smooth and responsive control for a better gameplay experience.
- **Pause and Resume**: Ability to pause the game and resume seamlessly.
- **Data Loading**: Load game data from external files to manage game configurations.
- **Special Weapon**: Unique weapon feature to enhance gameplay.
- **Score System**: Track and display player scores to keep the game competitive and fun.

---

## Prerequisites

Before you begin, make sure you have the following installed on your system:

- Microsoft Visual Studio with latest version installed

---

## Getting Started

#### 1. Clone the Repository

- Clone the repository to your local machine using the following command:
sh
   git clone https://github.com/wasim395/Geometry_Wars.git


#### 2. Open the Project in Visual Studio:
- Navigate to the Geometry_Wars directory.
- Open Geometry_Wars.sln in Visual Studio.

#### 3. Configure SFML
- Make sure to configure SFML properly in your Visual Studio project. Set up include directories, library directories, and link dependencies. Refer to the [SFML documentation](https://www.sfml-dev.org/tutorials/2.6/start-vc.php) for detailed instructions.

#### 4. Build the Project
- Build the project within Visual Studio to compile the C++ code and create the executable for the game.

#### 5. Run the Game
- Click the "Start" button in Visual Studio to run the game.

---

## Game Engine Components

### Entity Creation

The game engine allows for the creation of objects as entity instances. Each entity can have multiple components attached to it, enabling diverse functionalities and behaviors.

### Components

Some of the key components include:

- **CTransform**: Handles the position, rotation, and scale of entities.
- **CShape**: Manages the visual representation of entities.
- **CCollision**: Deals with collision detection and response.
- **CScore**: Keeps track of the player's score.
- **CLifespan**: Controls the lifespan of entities.
- **CInput**: Manages user input, allowing entities to respond to player controls.

### Systems

The game engine also includes various systems to manage different aspects of the game:

- **sMovement**: Updates entity positions and handles movement logic.
- **sUserInput**: Processes user input and applies corresponding actions to entities.
- **sLifespan**: Manages the lifespan of entities and removes them when they expire.
- **sRender**: Renders entities and handles all drawing operations.
- **sEnemySpawner**: Spawns enemies based on the defined spawn interval and other parameters.
- **sCollision**: Detects and handles collisions between entities.

### Special Features

- **Special Weapon**: Generated at regular intervals, it adds an exciting dimension to the gameplay, making it more challenging and enjoyable.
- **Death Count**: Tracks the number of times the player has died.
- **Score System**: Keeps players engaged by tracking their performance and displaying scores.

---                                                                                                                                           

## Configuration File

The game settings can be customized by Geometry_Wars/config.txt . Here is an example of the configuration format:

config.txt
Window 1280 720 60 0
Font fonts/verdana.ttf 24 255 255 255
Player 32 32 5 5 5 5 255 0 0 4 8
Enemy 32 32 3 3 255 255 255 2 3 8 30 60
Bullet 10 10 10 255 255 255 255 255 255 0 20 60


### Explanation:

- **Window**: 
  - 1280 720: Window width and height in pixels.
  - 60: Frame rate limit.
  - 0: Additional settings (e.g., fullscreen mode).

- **Font**: 
  - fonts/verdana.ttf: Path to the font file.
  - 24: Font size.
  - 255 255 255: Font color in RGB.

- **Player**: 
  - 32: Shape radius.
  - 32: Collision radius.
  - 5: Speed.
  - 5 5 5: Fill color in RGB.
  - 255 0 0: Outline color in RGB.
  - 4: Outline thickness.
  - 8: Shape vertices.
  - 8: Number of lives.

- **Enemy**: 
  - 32: Shape radius.
  - 32: Collision radius.
  - 3: Minimum speed.
  - 3: Maximum speed.
  - 255 255 255: Outline color in RGB.
  - 2: Outline thickness.
  - 3: Minimum vertices.
  - 8: Maximum vertices.
  - 30: Lifespan of small enemies after the death of an enemy, in seconds.
  - 60: Enemy spawn interval in milliseconds.

- **Bullet**: 
  - 10: Shape radius.
  - 10: Collision radius.
  - 10: Speed.
  - 255 255 255: Fill color in RGB.
  - 255 255 255: Outline color in RGB.
  - 0: Outline thickness.
  - 20: Shape vertices.
  - 60: Lifespan in milliseconds.

To customize the game, edit the configuration file with your preferred settings and restart the game.

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## Acknowledgements

- [SFML](https://www.sfml-dev.org/) for providing the graphics and multimedia library.
