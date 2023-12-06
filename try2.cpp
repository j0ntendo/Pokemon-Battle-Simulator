#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
using namespace std;


// CLASS FOR SKILLS 
// ===================================================================================================

class Skill {
private:
    string skillName;
    string skillType;
    int damage;
    int maxTry;
    int currentTry;

public:
    // default constructor
    Skill() : skillName(""), skillType(""), damage(0), maxTry(0), currentTry(0) {}
    // constructor
    Skill(const string& name, const string& st, int d, int mt) 
    : skillName(name), skillType(st), damage(d), maxTry(mt), currentTry(mt) {}

    // Getters
    string getName() const { return skillName; }
    string getSkillType() const { return skillType; }
    int getDamage() const { return damage; }
    int getMaxTry() const { return maxTry; }
    int getCurrentTry() const { return currentTry; }

    // functions to calculate damage depending on defender pokemon and attack type
    int calculateDamage(const string &defenderType, string &effectiveness) {
        int calculateDamage = damage;  //make internal variable

        // Check for super effective attacks
        if ((skillType == "Water" && defenderType == "Fire") ||
            (skillType == "Water" && defenderType == "Ground") ||
            (skillType == "Electric" && defenderType == "Water") ||
            (skillType == "Fire" && defenderType == "Glass") ||
            (skillType == "Ground" && defenderType == "Electric") ||
            (skillType == "Ground" && defenderType == "Fire") ||
            (skillType == "Glass" && defenderType == "Water"))
        {
            calculateDamage += 5;  // change damage
            effectiveness = "super effective"; // var for output use
        }
        // Check for not very effective attacks
        else if ((skillType == "Electric" && defenderType == "Ground") ||
                (skillType == "Electric" && defenderType == "Electric") ||
                (skillType == "Electric" && defenderType == "Glass") ||
                (skillType == "Water" && defenderType == "Glass") ||
                (skillType == "Water" && defenderType == "Water") ||
                (skillType == "Fire" && defenderType == "Water") ||
                (skillType == "Fire" && defenderType == "Fire") ||
                (skillType == "Ground" && defenderType == "Glass") ||
                (skillType == "Glass" && defenderType == "Ground") ||
                (skillType == "Glass" && defenderType == "Glass") ||
                (skillType == "Glass" && defenderType == "Fire"))
        {
            calculateDamage -= 3;  // change damage
            effectiveness = "not very effective"; // var for output use
        }
        else
        {
            effectiveness = "effective";  // var for output use
        }
        // No change for normal attacks
        return calculateDamage;
    }

    // function to decrease skill count when used
    bool useSkill() {
        if (currentTry > 0) {
            currentTry--;
            return true;
        }
        return false;
    }

};
// ===================================================================================================
// PARENT CLASS OF POKEMON 
class Pokemon {

private:  
    string name;
    string type;
    int HP;
    Skill skills[4]; 
    bool isTurn;

public:
    // Constructor
    Pokemon(const string& n, const string& t, int h)
        : name(n), type(t), HP(h), isTurn(false) {}

    // Setter function for skills (four skills)
    void setSkill(int index, const Skill& skill) {
        if (index >= 0 && index < 4) {
            skills[index] = skill;
        }
    }

    // Getter methods 
    string getName() const { return name; }
    string getType() const { return type; }
    int getHP() const { return HP; }
    // getter for skill
    Skill& getSkill(int index) {
    return skills[index];
    }
    // function to decrease HP when attacked where it cannot be negative
    void receiveDamage(int damage) {
        HP = std::max(0, HP - damage);
    }
    // function to set turn
    void setTurn(bool turn) {
        isTurn = turn;
    }
    // function to check if it is current turn
    bool isCurrentTurn() const {
        return isTurn;
    }
};


// ===================================================================================================
//  CHILD CLASSES OF SPECIFIC POKEMON's SKILLS
class Pikachu : public Pokemon {
    public:
    // constructor
    Pikachu () : Pokemon("Pikachu", "Electric", 35){
        setSkill(0, Skill("Tackle", "Normal", 4, 5));
        setSkill(1, Skill("Glass Knot", "Glass", 8, 5));
        setSkill(2, Skill("Thunderbolt", "Electric", 10, 5));
        setSkill(3, Skill("Megabolt", "Electric", 15, 3));
    }

};

class Dratini : public Pokemon {
public:
    // constructor
    Dratini() : Pokemon("Dratini", "Water", 41) {
        // Set skills
        setSkill(0, Skill("Wrap", "Normal", 4, 10));
        setSkill(1,Skill("Aqua Tail", "Water", 3, 5));
        setSkill(2, Skill("Water Pulse", "Water", 13, 2));
        setSkill(3, Skill("Hyper Beam", "Normal", 20, 1));
    }
};

class Eevee : public Pokemon {
public:
    // constructor
    Eevee() : Pokemon("Eevee", "Normal", 55) {
        // Set skills
        setSkill(0, Skill("Tackle", "Normal", 4, 5));
        setSkill(1, Skill("Sand Attack", "Ground", 8, 3));
        setSkill(2, Skill("Bite", "Normal", 12, 3));
        setSkill(3, Skill("Rain Dance", "Water", 15, 1));
    }
};

class Charmander : public Pokemon {
public:
    // constructor
    Charmander() : Pokemon("Charmander", "Fire", 39) {
        // Set skills
        setSkill(0, Skill("Tackle", "Normal", 4, 5));
        setSkill(1, Skill("Flamethrower", "Fire", 11, 5));
        setSkill(2, Skill("Dig", "Ground", 7, 5));
        setSkill(3, Skill("Heat Wave", "Fire", 14, 5));
    }
};

class Palkia : public Pokemon {
public:
    // constructor
    Palkia() : Pokemon("Palkia", "Water", 90) {
        // Set skills
        setSkill(0, Skill("Hydro Pump", "Water", 12, 10));
        setSkill(1, Skill("Earth Power", "Ground", 15, 10));
        setSkill(2, Skill("Surf", "Water", 13, 10));
        setSkill(3, Skill("Spatial Rend", "Normal", 30, 10));
    }
};




// ===================================================================================================
// BATTLE CLASS
class Battle
{
public:
    // function to initialize battle
    void initializeBattle(Pokemon& p1, Pokemon& p2) {
    // init battle settings
    p1.setTurn(true);  // player1 starts automatically
    p2.setTurn(false);
    }

    // function to display current state of battle 
    void displayCurrent(Pokemon& p1, Pokemon& p2) {
    const int columnWidth = 29; // width of each column
    const int skillColumnWidth = 29;   // width of each skill column

    // Display student information
    cout << "+-------------------------------------------------------------+" << endl;
    cout << "| 2023148017 Ujin Jonathan Kang Computer Science              |" << endl;
    cout << "+------------------------------+------------------------------+" << endl;

    // Display Pokemon names and turns with (*) depending on current turn
    string p1TurnIndicator = p1.isCurrentTurn() ? " (*) " : "     ";
    string p2TurnIndicator = p2.isCurrentTurn() ? " (*) " : "     ";
    cout << "| " << p1.getName() << p1TurnIndicator
         << string(columnWidth - p1.getName().length() - p1TurnIndicator.length(), ' ')
         << "| " << p2.getName() << p2TurnIndicator
         << string(columnWidth - p2.getName().length() - p2TurnIndicator.length(), ' ')
         << "|" << endl;

    // Display Pokemon types and HP
    cout << "| Type: " << p1.getType()
         << string(columnWidth - 6 - p1.getType().length(), ' ')
         << "| Type: " << p2.getType()
         << string(columnWidth - 6 - p2.getType().length(), ' ')
         << "|" << endl;
    cout << "| HP: " << p1.getHP()
         << string(columnWidth - 4 - to_string(p1.getHP()).length(), ' ')
         << "| HP: " << p2.getHP()
         << string(columnWidth - 4 - to_string(p2.getHP()).length(), ' ')
         << "|" << endl;
    cout << "+------------------------------+------------------------------+" << endl;

    // Display skills
    for (int i = 0; i < 4; i++) {
        Skill m1 = p1.getSkill(i);
        Skill m2 = p2.getSkill(i);

        cout << "| (" << i << ") " << m1.getName()
             << string(skillColumnWidth - m1.getName().length() - 4, ' ')
             << "| (" << i << ") " << m2.getName()
             << string(skillColumnWidth - m2.getName().length() - 4, ' ')
             << "|" << endl;

        cout << "|     - Type: " << m1.getSkillType()
             << string(skillColumnWidth - m1.getSkillType().length() - 12, ' ')
             << "|     - Type: " << m2.getSkillType()
             << string(skillColumnWidth - m2.getSkillType().length() - 12, ' ')
             << "|" << endl;

        cout << "|     - Damage: " << m1.getDamage()
             << string(skillColumnWidth - to_string(m1.getDamage()).length() - 14, ' ')
             << "|     - Damage: " << m2.getDamage()
             << string(skillColumnWidth - to_string(m2.getDamage()).length() - 14, ' ')
             << "|" << endl;

        cout << "|     - Count: " << m1.getCurrentTry() << "(" << m1.getMaxTry() << ")"
             << string(skillColumnWidth - to_string(m1.getCurrentTry()).length() - to_string(m1.getMaxTry()).length() - 15, ' ')
             << "|     - Count: " << m2.getCurrentTry() << "(" << m2.getMaxTry() << ")"
             << string(skillColumnWidth - to_string(m2.getCurrentTry()).length() - to_string(m2.getMaxTry()).length() - 15, ' ')
             << "|" << endl;
    }

    cout << "+------------------------------+------------------------------+" << endl;
}

    // function to perform next turn
    void nextTurn(Pokemon& p1, Pokemon& p2) {
    int skillIndex;  // var for skill index
    cout << "Choose a skill (0~3): ";  // ask for input
    cin >> skillIndex;

    Pokemon *attacker, *defender;  // var for attacker and defender

    // determine the attacker and defender
    if (p1.isCurrentTurn()) {
        attacker = &p1;
        defender = &p2;
    } else {
        attacker = &p2;
        defender = &p1;
    }

    // perform attack
    performAttack(*attacker, *defender, skillIndex);

    // toggle turn
    p1.setTurn(!p1.isCurrentTurn());
    p2.setTurn(!p2.isCurrentTurn());

}

    // function to perform attack
    void performAttack(Pokemon& attacker, Pokemon& defender, int skillIndex) {
    Skill& chosenSkill = attacker.getSkill(skillIndex); // determine the skill to be used
    string effectiveness;  // var for effectiveness

    // Check if the skill can be used
    if (!chosenSkill.useSkill()) {
        cout << attacker.getName() << " failed to perform " << chosenSkill.getName() << "." << endl;  //output message
        cout << "\n";
        return; // skip turn if the skill cannot be used

    }

    // Calculate damage if the skill is available
    int damage = chosenSkill.calculateDamage(defender.getType(), effectiveness);  // calculate damage
    cout << attacker.getName() << " used " << chosenSkill.getName() << "." << endl;  // output message

    // Output message depending on the effectiveness
    if (effectiveness == "super effective") {
        cout << "The attack was super effective." << endl;
    } else if (effectiveness == "not very effective") {
        cout << "The attack was not very effective." << endl;
    } else {
        cout << "The attack was effective." << endl;
    }

    defender.receiveDamage(damage);  // decrease HP of defender
    cout << "\n";
}

};

// ===================================================================================================
// GAME CLASS
class Game {
private:
    static const int MAX_POKEMON = 5;  // set number of pokemons
    Pokemon* availablePokemon[MAX_POKEMON];  // Array of available Pokémon
    Battle currentBattle;  
    Pokemon *p1, *p2;

public:
    // Constructor
    Game() {
        // Initialize Pokémon 
        availablePokemon[0] = new Pikachu();
        availablePokemon[1] = new Dratini();
        availablePokemon[2] = new Eevee();
        availablePokemon[3] = new Charmander();
        availablePokemon[4] = new Palkia();
    }
    // Destructor
    ~Game() {
        // Delete all Pokémon
        for (int i = 0; i < MAX_POKEMON; i++) {
            delete availablePokemon[i];
        }
    }

    // function to choose pokemon
    void choosePokemon() {
        int choice1, choice2;  // var for pokemon 
        cout << "Choose a Pokemon(0~4): ";  // ask for input
        cin >> choice1;
        p1 = availablePokemon[choice1];  // set pokemon1

        cout << "Choose another Pokemon(0~4): ";  // ask for second input
        cin >> choice2;

        // condition if same Pokemon is chosen
        if (choice1 == choice2) {
            cout << "You have to choose Pokemons different from each other." << endl;
            exit(0); // Terminate the program
        }

        p2 = availablePokemon[choice2];  // set pokemon2

        currentBattle.initializeBattle(*p1, *p2);  // initialize battle
    }

    // function to start battle
    void startBattle() {
        bool continueBattle = true;  // flag for battle

        // while loop for battle
        while (continueBattle) {
            // display the current state at the beginning of each turn
            currentBattle.displayCurrent(*p1, *p2);

            // perform next turn
            currentBattle.nextTurn(*p1, *p2);

            // keep checking if either Pokémon has been defeated
            if (p1->getHP() <= 0 || p2->getHP() <= 0) {
                continueBattle = false; // Stop the battle and set flag to false
            }
        }

        // Determine the winner
        string winner, loser;  // var for winner and loser
        if (p1->getHP() <= 0) {
            // p2 wins
            winner = p2->getName();
            loser = p1->getName();
        } else {
            // p1 wins
            winner = p1->getName();
            loser = p2->getName();
        }

        // Display the result message
        cout << "===============================================================" << endl;
        cout << "Match Result: " << winner << " defeats " << loser << endl;
    }


};


int main() {
    // Create a game object and start the game
    Game game;
    // Choose Pokémon
    game.choosePokemon();
    // Start the battle
    game.startBattle();

    return 0;
}
