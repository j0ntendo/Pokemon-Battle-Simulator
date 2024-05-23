## Object Oriented Programming (CCO1102.01) (C++) FINAL ASSIGNMENT

## Classes Overview

### Skill Class

This class represents a Pokémon's skill.

- **Attributes:**
  - `skillName`: Name of the skill.
  - `skillType`: Type of the skill (e.g., Water, Fire, Electric).
  - `damage`: The damage dealt by the skill.
  - `maxTry`: Maximum number of times the skill can be used.
  - `currentTry`: Current number of times the skill can be used.

- **Methods:**
  - Constructors to initialize skills.
  - Getters for skill attributes.
  - `calculateDamage`: Calculates the damage based on the defender's type.
  - `useSkill`: Decreases the current try count when the skill is used.

### Pokemon Class

This is the parent class for all Pokémon.

- **Attributes:**
  - `name`: Name of the Pokémon.
  - `type`: Type of the Pokémon.
  - `HP`: Health points of the Pokémon.
  - `skills`: Array of skills the Pokémon can use.
  - `isTurn`: Boolean to check if it's the Pokémon's turn.

- **Methods:**
  - Constructor to initialize a Pokémon.
  - Setters and getters for attributes and skills.
  - `receiveDamage`: Decreases the Pokémon's HP when attacked.
  - `setTurn`: Sets the turn of the Pokémon.
  - `isCurrentTurn`: Checks if it's the Pokémon's turn.

### Specific Pokémon Classes

These classes inherit from the `Pokemon` class and represent specific Pokémon with predefined skills.

- **Pikachu**
- **Dratini**
- **Eevee**
- **Charmander**
- **Palkia**

Each class initializes its Pokémon with specific skills.

### Battle Class

This class handles the battle logic between two Pokémon.

- **Methods:**
  - `initializeBattle`: Sets the initial state of the battle.
  - `displayCurrent`: Displays the current state of the battle.
  - `nextTurn`: Handles the logic for each turn.
  - `performAttack`: Executes an attack by the current Pokémon on the opponent.

### Game Class

This class manages the game, including Pokémon selection and the battle loop.

- **Attributes:**
  - `availablePokemon`: Array of available Pokémon to choose from.
  - `currentBattle`: Instance of the `Battle` class to manage the battle.
  - `p1`, `p2`: Pointers to the selected Pokémon for the battle.

- **Methods:**
  - Constructor and destructor to manage Pokémon instances.
  - `choosePokemon`: Allows the player to choose Pokémon for the battle.
  - `startBattle`: Starts and manages the battle until a Pokémon wins.

## How to Run

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/OOP_Final_Assignments.git
   cd OOP_Final_Assignments

2. g++ -o pokemon_battle main.cpp
3. ./pokemon_battle


