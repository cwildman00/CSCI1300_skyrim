/*/
CSCI1300 Fall 2020
Author: Cassie Wildman
Recitation: 514 - Chris Gavin
Project 3 - Main Function

Project 3 - Elder Scrolls V: Skyrimm Adaptation 
________________________________________________________________________________________________

DISCLAIMER
________________________________________________________________________________________________
I do not claim to own any of the story content of this game beyond the code I have written. 
All story credit goes to Bethesda Game Studios for their game The Elder Scrolls V: Skyrim. This 
is an adaptation of the game's prologue - changes to the story have been made for clarity and 
length. 
_________________________________________________________________________________________________

GAME OVERVIEW
_________________________________________________________________________________________________

As previously mentioned, this game is an adaptation of The ELder Scrolls V: Skyrim. For the sake
of time, all that could be adapted was the game's prologue (quest: Unbound). As a result, the 
story is less than I would have liked and couldn't function how I planned, but it still works well.

Game saves are what suffered most from this crunch. Skyrim is one that takes hundred of hours, and
thus requires being able to save and come back. I was not able to adapt it to save on a whim and 
there are few opportunities for saving with how short it is. However, the game does still write 
information to files for the purpose of reading once saving functionality can be added (I intend
to continue working on this project beyond this class). So technically, file IO is covered in
both respects. 

I will reiterate that the story used is a prologue - there is no resolution here. However, if
you have not played Skyrim and this sounds interesting, I highly recommend picking up the official
game. 

Features that have been included are:
    Character creation --> includes writing to files
    Combat --> includes reading and writing to files
    Mini game --> includes randomization
    Story --> uses file reading completely

Enjoy!
___________________________________________________________________________________________________
/*/

#include <iostream>
#include <string>
#include "player.h"
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

//========================== HELPER FUNCTIONS ==========================//

int split(string toSplit, char separ, string array[], int arrSize)
/*/
* Brought over from previous homework
* Used in:
    * Loading game saves
    * Reading opponent information and loading in opponents for combat
    * Reading item information
/*/
{
    int start = 0;
    int arrayPos = 0;

    for (int i = 1; i <= toSplit.length(); i++)
    {
        if ((toSplit[i] == separ) || (i == toSplit.length()))
        {
            array[arrayPos] = toSplit.substr(start, i - start);
            start = i + 1;
            arrayPos++;
            if (arrayPos > arrSize)
            {
                break;
            }
        }
    }
    return arrayPos - 1;
}

void whileStatic(int choice, int lowInt, int highInt)
// Used to reduce number space from while loops.
// Only for decisions that take 1 of 2 answers
// Prevents user error
{
    while (choice != highInt && choice != lowInt)
    {
        cout << "Please enter a valid option." << endl;
        cin >> choice;
        if (choice == highInt && choice == lowInt)
        {
            break;
        }
    }
}

void whileRange(int choice, int lowInt, int highInt)
// Used to reduce number space from while loops.
// Only for decisions that take a range of answers
// Prevents user error
{
    while (choice > highInt && choice < lowInt)
    {
        cout << "Please enter a valid option." << endl;
        cin >> choice;
        if (choice <= highInt && choice >= lowInt)
        {
            break;
        }
    }
}
//========================== TAG FUNCTIONS ==========================//

void combat(player& hero, player& opponent, inventory& heroInventory, inventory& opponentInventory, bool runOkay)
/*/
PRIMARY FUNCTION FOR COMBAT SEQUENCES | Called by [COMBAT] tag in .txt files
____________________________________________________________________________
Overview
____________________________________________________________________________
* Take in combatants, respective inventories, and permission for chance to 
  run as function arguments
    * Pass in by reference so inventories will stay up to date 
* Save player inventory before battle in case of death
* Opponent, opponent inventory, and run permissions are pre-built and read 
  from .txt file 
* If runOkay == true, then there is a random chance that running will 
  fail anyway
* Damage calclulations are made in "player.h"
    * Follows a formula that takes into account armor ratings vs damage 
      ratings from the weapon and gives a random number of hits from 
      1-10.
* Menu includes:
    * Attack
        * Player gets first move, inflicts damage with random # of hits,
          opponent retaliates
    * Defend
        * Player has a 1/3 chance of deflecting an attack. If successful,
          opponent takes half of the damage instead. If not, attack proceeds
          as normal.
    * Take potion
        * Opens a menu of potions that are in the player's inventory
             * If no potions are available, the main menu will return
             * Player will choose which potion they want, then return to 
               main  menu to choose another option.
    * Open inventory
        * Opens a menu to access the weapon and armor inventories for equipping
        * Equip any new items here
        * Once item is selected, player is returned to the main menu for another
          option
    * Attempt to run
        * 1/3 chance of escaping IF it is not specified in the .txt file that 
          you cannot run from the fight. Ordinarily, prologues wouldn't allow
          for running, but the occasional minor battle will allow for running
          for the sake of showing that it does work.
____________________________________________________________________________
/*/
{
    //======== SET UP ========//
    srand(time(NULL)); // Set up for chance  of running 
    
    heroInventory.saveInventory(heroInventory); // FileIO save in case of death

    int choice; // Numerical choice for menus | [1] Attack, [2] Potion, ....
    string choice2; // String choice for equipping | Y/N prompts
    
    bool run = true; // main loop condition

    hero.setHealth(100); // Reset health to 100 | Because health is passed in by reference, if you have 2pts of health at the end of one fight
                         //                       then that's what you start with in the next fight.

    // Simplifying names for sanity //

    string heroName = hero.getPlayerName(); 
    string opponentName = opponent.getPlayerName();
    
      

    //======== START ========//
    cout << "____________________________________________________________________________________________"<< endl;
    cout << opponentName << " wants to fight!" << endl;
    cout << opponentName << ": Never should have come here!" << endl;

    cout << "You have " << hero.getHealth() << " health." << endl; //Initial status check
    cout << "____________________________________________________________________________________________"<< endl;

    while (run == true && opponent.alive() == true && hero.alive() == true) //While you have not ran and both opponents are alive --> run loop
    {
        item weapon1 = hero.getEquippedWeapon();
        item weapon2 = opponent.getEquippedWeapon();

        item armor1 = hero.getEquippedArmor();
        item armor2 = opponent.getEquippedArmor();  
        cout << "[1] Attack, [2] defend, [3] use a potion, [4] open inventory, or [5] attempt to run? | ";
        cin >> choice;
        whileRange(choice,1,5);
        
        //-------- ATTACK --------//
        if (choice == 1)
        {
            cout << "____________________________________________________________________________________________"<< endl;
            cout << "You attack " << opponentName << " with " << weapon1.getName() << " for " << opponent.takeDamage(weapon1, armor2) << " damage." << endl;
      
            if (opponent.alive() == false) //If opponent has lost
            {
                cout << "You have defeated " << opponentName << "!" << endl << endl;

                cout << opponentName << "'s " << weapon2.getName() << " has been added to your inventory!" << endl; //Loot opponent's weapon

                heroInventory.addItem(weapon2);

                cout << "____________________________________________________________________________________________" << endl;        

            }
            else //If opponent is still alive
            {
                cout << opponentName << " has " << opponent.getHealth() << " health remaining." << endl << endl; //Opponent health check
                
                cout << opponentName << " attacks you for " << hero.takeDamage(weapon2, armor1) << " damage." << endl << endl;

                //cout << "__________________________________________________________________" << endl;

                if (hero.alive() == false) //Player defeated
                {
                    cout << "You have died!" << endl;
                }
                else //Player still alive
                {
                    cout << "You have " << hero.getHealth() << " health remaining." << endl; //Player health check
                    cout << "____________________________________________________________________________________________"<< endl;
                }
            }
        }

        //-------- DEFEND --------//        
        else if (choice == 2) 
        {
            int chance = (rand() % 3) + 1; // Generate random number
            if (chance == 1) // If that random number is 1, execute
            {
                cout << opponentName << " attacks you. You successfully block the attack! " << opponentName << " takes half the damage instead." << endl << endl;;

                opponent.takeDamage(weapon2, armor1) / 2; // Halved damage calculation  
                
                cout << opponentName << " has " << opponent.getHealth() << " health remaining." << endl << endl; // Opponent health check
                
                
                if (opponent.alive() == false) // If opponent has lost
                {
                    cout << "You have defeated " << opponentName << "!" << endl << endl;

                    cout << opponentName << "'s " << weapon2.getName() << " has been added to your inventory!" << endl; // Loot opponent's weapon

                    heroInventory.addItem(weapon2);
                }
            }
            else
            {
                cout << "Your block was unsuccessful! " << opponentName << " attacks you for " << hero.takeDamage(weapon2, armor1) << " damage." << endl << endl;

                if (hero.alive() == false) //Player defeated
                {
                    cout << "You have died!" << endl;
                }
                else //Player still alive
                {
                    cout << "You have " << hero.getHealth() << " health remaining." << endl; //Player health check
                    cout << "____________________________________________________________________________________________"<< endl;
                }
            }
        }

        //-------- POTION --------//
        else if (choice == 3)
        {   
            cout << "Here are the potions you are carrying: " << endl << endl;
            
            int potionQuantity = heroInventory.viewItems("potions"); // Display potions and/or get a return value of how many potions there are. If there are none, -2 will be returned
            
            if (potionQuantity == -2)
            {
                cout << "You have no potions left." << endl << endl;
                cout << "You have " << hero.getHealth() << " health remaining." << endl;
                cout << "____________________________________________________________________________________________"<< endl;
            }

            else if (potionQuantity > 0)
            {
                cout << endl << "Which potion will you use?: ";
                cin >> choice;

                whileRange(choice,1,potionQuantity);

                item potion = heroInventory.itemToRemove("potions", choice); // Function and description found in "inventory.h" and "inventory.cpp"
                hero.usePotion(potion); // Use potion
                heroInventory.removeItem(potion); // Remove used potion from inventory
                //cout << "__________________________________________________________________" << endl;
                cout << "You have " << hero.getHealth() << " health remaining." << endl; // Player health check post-potion
                cout << "____________________________________________________________________________________________"<< endl;
            }
        }

        //-------- INVENTORY --------//
        else if (choice == 4)
        {
            do // Do-While allows for equipping multiple items without having to go in and out of the menu multiple times
            {
                cout << "[1] Weapons  |  [2] Armor  |  [3] Back: "; 
                cin >> choice;
            //    cout << endl;
            
                if (choice == 1) // If choice == Weapons
                {
                    do
                    {
                        cout << "____________________________________________________________________________________________"<< endl;
                        heroInventory.viewItems("weapons"); // Displays everything in the given category

                        cout << "Would you like to equip weapons? | [1] Yes  [2] No: " ;
                        cin >> choice;
                        //cout << endl;
                        if (choice == 1)
                        {
                            
                            cout << "Enter the number of the item you'd like to equip: ";
                            cin >> choice;
                            //cout << endl;
                            item oldWeapon = hero.getEquippedWeapon(); // Get the information of the currently equipped item

                            heroInventory.addItem(oldWeapon); // Put the equipped item back into the inventory

                            item newWeapon = heroInventory.itemToRemove("weapons", choice); // Get the information of the new item

                            hero.setEquipedWeapon(newWeapon); // Equip the chosen item

                            heroInventory.removeItem(newWeapon); // Remove the chosen item from the inventory to avoid confusion
                        }
                        else if (choice > 2 || choice < 1)
                        {
                            cout << "Please enter a valid number." << endl;
                        }
                    } while (choice != 2);
                    
                }
                else if (choice == 2) // If choice == Armor
                {
                    do
                    {
                        cout << "____________________________________________________________________________________________"<< endl;
                        heroInventory.viewItems("armor");
                        //cout << "__________________________________________________________________" << endl;
                        cout << "Would you like to equip armor? | [1] Yes [2] No: ";
                        cin >> choice;
                       // cout << endl;
                        if (choice == 1)
                        {
                            cout << "Enter the number of the item you'd like to equip: ";
                            cin >> choice;
                            cout << endl;
                            item oldArmor = hero.getEquippedArmor();

                            heroInventory.addItem(oldArmor);

                            item newArmor = heroInventory.itemToRemove("armor", choice);

                            hero.setEquipedArmor(newArmor);

                            heroInventory.removeItem(newArmor); 
                        }
                        else if (choice > 2 || choice < 1)
                        {
                            cout << "Please enter a valid number." << endl;
                        }
                    } while(choice != 2);
                }
                else if (choice > 3 || choice < 1) // Anything else other than 3
                {
                    cout << "Please choose a valid option." << endl;
                }
            cout << "____________________________________________________________________________________________"<< endl;

            } while(choice != 3);
        }

        //-------- RUN --------//
        else if (choice == 5 && runOkay == true) //Player chooses to run and running is allowed
        {
            int chanceRun = (rand() % 3) + 1; //randomized number between 1 and 3
            if (chanceRun = 2) //If that number == 2, then the escape is successful
            {
                cout << "You sprint away from your opponent and dodge from sight until you hear them muttering." << endl;
                cout << opponentName << ": Oh well. Guess they must have run off." << endl;
                run = false; //Terminate loop
            }
            else //Any other number and your opponent prevents your escape
            {
                cout << opponentName << " blocks your path! You must continue to fight!" << endl;
            }
        }
        else if (choice == 5 && runOkay == false) //Player chooses run and running is not allowed
        {
            cout << "You cannot run from this fight! Pick up your sword and fight with all you can!" << endl;
            cout << "____________________________________________________________________________________________"<< endl;
        }
    }
}

player createChar(player character)
{
/*/
FUNCTION FOR CHARACTER CREATION | Called by [SET UP] tag in .txt files
____________________________________________________________________________
Overview
____________________________________________________________________________
* Prompt user for a choice of gender, character race, and name
* Display all information and confirm with the user before moving on
* To be added on in the future:
    * Menu for learning more about each race (all races are from Skyrim and 
      not my own and there is a lot of background on them)
        * Sparknotes version:
            * Argonians are a lizard species, known for being good thieves
            * Bretons, Imperials, Nords, and Redguards are varieties of humans
              with varying talents in magic. Redguards are always people of 
              color.
            * Elves are elves, they just look very different from humans and
              High Elves have a superiority complex.
            * Khajiit are cat people from the desert, known for being traveling
              merchants.
            * Orcs are your typical orc - berserker-type and they mostly live 
              in strongholds away from the rest of society
* Player information is saved to a .txt file to be opened later if needed  
____________________________________________________________________________
/*/
    //======== SET UP ========//
    string races[10] = {"Argonian", "Breton", "Dark Elf", "High Elf", "Imperial", "Khajiit", "Nord", "Redguard", "Orc", "Wood Elf"}; //Array of races for given numbers to correspond to
    string genders[2] = {"Male", "Female"};
    int choice;
    string name;
    ofstream playerFile;
    

    //======== START ========//

    cout << "__________________________________________________________" << endl << endl;

    do // Open file in the loop and close it before the final decision in case of any character revisions
    {
        playerFile.open("player.txt"); // Open or create+open the file to store player information 

        //-------- GENDER --------//
        cout << "What gender will you be? | [1] Male  [2] Female" << endl;
        cin >> choice;
        whileStatic(choice,1,2);

        character.setPlayerGender(genders[choice-1]); // [gender-1] to accomodate for index offset

        playerFile << character.getPlayerGender() << ","; // Write player gender to .txt file

        //-------- RACE --------//
        cout << "What race will you play? | Enter the respective number." << endl;
        cout << "[1] Argonian  |  [2] Breton  |  [3] Dark Elf  |  [4] High Elf  |  [5] Imperial  |  [6] Khajiit   | [7]  Nord  |  [8] Redguard  |  [9] Orc  | [10]  Wood Elf\n";
        cin >> choice;
        whileRange(choice,1,10);

        character.setPlayerRace(races[choice-1]); // [race-1] to accomodate for index offset
        playerFile << character.getPlayerRace() << ","; // Write player race to .txt file

        //-------- NAME --------//
        cout << "What is your name? " << endl;
        cin >> name; 

        character.setPlayerName(name);
        playerFile << character.getPlayerName() << "\n"; // Write player name to .txt file

        //-------- CONFIRMATION --------//
        cout << "You are a " << character.getPlayerGender() << " " << character.getPlayerRace() << " called " << character.getPlayerName() << endl;
        cout << "Press [0] to continue or [3] to start over: ";
        playerFile.close();
        cin >> choice;

        whileStatic(choice,0,3);
        

        
    }while (choice != 0); // While final confirmation is not yes 

    cout << "__________________________________________________________" << endl;
    
    return character;
}

void cont()
/*/
FUNCTION FOR CONTINUING STORY | Called by [CONT] tag in .txt files
____________________________________________________________________________
Overview
____________________________________________________________________________
* Prompt user to press Enter to continue
* Simply used to progress story in small bites
____________________________________________________________________________
/*/
{
    cout << "Press Enter to continue. ";
    cin.ignore(); //Ignores any input, allowing for pressing enter to advance forward
}

void lockpick(int numPicks, item reward, inventory playerInventory)
/*/
FUNCTION FOR LOCKPICKING MINI ACTIVITY | Called by [LOCKPICK] tag in .txt files
____________________________________________________________________________
Overview
____________________________________________________________________________
* Create a random number betwen 1 and 10
* Ask the user to choose pick a number in that range
* User has as many tries as they have lockpicks
* Due to time constraints, this functions will be locked in at 3 lockpicks
    * Ideally, there would be a Misc inventory section where lockpicks can
      can sorted and however many lockpicks are in the inventory, that's 
      how many chances the player gets. 
* If the player successfully picks the lock, then they will receive the items
  hidden behind that lock, which are specified in the .txt file. 
____________________________________________________________________________
/*/
{
    srand(time(NULL)); // Initialize randomization
    int number = (rand() % 10)+1; // Generate random number between 1 and 10. Add 1 to prevent the number from actually being between 0 and 9.
    int guess;

    do
    {
        cout << "Choose a number between 1 and 10" << endl;
        cin >> guess; 
        whileRange(guess,1,10);
        
        if (guess == number) // If player is successful
        {
            cout << "The lock clicks open!" << endl;
            cout << "You found a " << reward.getName() << "! It has been added to your inventory." << endl;
            playerInventory.addItem(reward);
        }

        else // If player is unsuccessful
        {
            numPicks--; // Lockpick breaks
            cout << "The pick breaks in the lock." ;
            if (numPicks > 0) // If there are still lockpicks left, then more chances can be attempted
            {
                cout << " You have " << numPicks << " remaining.";
            }
            else // If 0 lockpicks remain, no more attempts can be made and the item is forfeight.
            {
                cout << "You are out of lockpicks. Better luck next time!" << endl;
            }
            
        }
    } while (numPicks > 0 && guess != number); // Loop while the number of lockpicks is greater than 0 and the player's guess is not correct
    
}

//========================== STORY FUNCTION ==========================//

void readStory(string fileName)
/*/FUNCTION FOR READING THE FULL STORY 
____________________________________________________________________________
Overview
____________________________________________________________________________
* Takes in the first file name to initiate the story
* Uses ifstream to read .txt files and upon reading specific tags, readStory
  will call the respective functions needed.
    * [COMBAT] tag calls the combat function, [SET UP] creates the player, etc
* Uses player decisions to determine which other files to open
____________________________________________________________________________
/*/
{
    //======== SET UP ========//

    string lineFromFile; // Line read by ifstream via getline
    string unboundAlly; // Name of the secondary file called later, determined by the user
    
    // Initialize the player with defaults 
    player dragonborn;
    inventory dragonbornInv;

    //======== START ========//

    ifstream story(fileName);

    if (story.is_open())
    {
        while (getline(story, lineFromFile)) // Run lines of the file and search for the tags
        {
            if (lineFromFile.find("[SET UP]") != string::npos) //Find and if it's not equal to (no position found), then run function 
            {
                createChar(dragonborn);
            }

            else if (lineFromFile.find("[CONT]") != string::npos) 
            {
                cont();
            }

            else if (lineFromFile.find("[SIDE]") != string::npos) // Determines which secondary .txt file to open
            {
                string choice;
                
                bool pass = false;
                while (pass == false)
                {
                    cout << "Who do you follow?\n[1] Hadvar  |  [2] Ralof" << endl;
                    cin >> choice;
                    
                    if (choice == "1")
                    {
                        unboundAlly = "hadvarUnbound.txt";
                        pass = true;
                    }
                    else if (choice == "2")
                    {
                        unboundAlly = "ralofUnbound.txt";
                        pass = true;
                    }
                    else // User error check
                    {
                        cout << "Please enter a valid option." << endl;
                        pass = false;
                    }
                }

                //======== PART 2 ========//

                story.close(); // On to next file, no need to keep the first open
                
                ifstream ally(unboundAlly); // Open the second file
                    while (getline(ally, lineFromFile)) // Search for tags
                    {
                        if (lineFromFile.find("[CONT]") != string::npos) 
                        {
                            cont();
                        }

                        else if (lineFromFile.find("[ADD") != string::npos) // Adds new items to the inventory. Details are specified in .txt file
                        {
                            string answer;

                            string arr[5];

                            getline(ally,lineFromFile); // Reads the line directly under the tag to get details for the new item

                            split(lineFromFile,',', arr, 5); // Split helper function to separate the item details
                            
                            item newItem(arr[0], arr[1], stoi(arr[2]), stoi(arr[3]), stoi(arr[4])); // Convert the item details into an item object
                            
                            newItem.setEquipped("N"); // By default, the new item is not equipped by the player.

                            dragonbornInv.addItem(newItem); // Officially add the item to the inventory
                        
                            cout << "| " << newItem.getName() << " has been added to your inventory." << endl;
                        }

                        else if (lineFromFile.find("[LOCKPICK") != string::npos)
                        {
                            int numPicks = 3;

                            item potion("Potion of Healing", "Healing Potion", 50, 2, 36); // Reward for successfully lockpicking

                            lockpick(3, potion, dragonbornInv);
                        }

                        else if (lineFromFile.find("[COMBAT]") != string::npos) 
                        {
                            bool runOkay; // Variable for determining if running from combat is allowed
                            
                            // Setting up Opponent
                            inventory oppInv;

                            string arr[14] = {};

                            getline(ally,lineFromFile); // Reading opponent information - includes name, weapon, and armor
                            
                            split(lineFromFile,',', arr, 14);

                            player opponent(arr[0],arr[1],arr[2]); // Details <name> <race> <gender>
                            
                            
                            item weapon(arr[3], arr[4], stoi(arr[5]), stoi(arr[6]), stoi(arr[7])); // Weapon information <name> <type> <rating> <weight> <value>
                            oppInv.addItem(weapon); // Add weapon to opponent's inventory
                            opponent.setEquipedWeapon(weapon); //Equip opponent's weapon
                            
                            
                            item armor(arr[8], arr[9], stoi(arr[10]), stoi(arr[11]), stoi(arr[12])); // Armor information <name> <type> <rating> <weight> <value>
                            oppInv.addItem(armor); // Add armor to opponent's inventory
                            opponent.setEquipedArmor(armor); //Equip opponent's armor

                            if (arr[13] == "yes") // Running permission. Only allowed if "yes" is specified
                            {
                                runOkay = true;
                            }
                            else
                            {
                                runOkay = false;
                            }

                            combat(dragonborn, opponent, dragonbornInv, oppInv, runOkay); // Call combat
                            if (dragonborn.alive() == false) // If player dies, game is over completely.
                            {
                                cout << "Game Over" << endl;
                                
                                break;
                            }
                        }

                        else // If no tags are found, print the line.
                        {
                            cout << lineFromFile << endl;
                        }

                }
               
            
            }

            else // If no tags are found, print the line
            {
                cout << lineFromFile << endl;
            }
        }
    }
    story.close(); // If no [SIDE] tag is found and no other .txt file is opened, close the first file here

}

//========================== MAIN ==========================//
int main ()
{
    readStory("unboundHelgen.txt");
}
