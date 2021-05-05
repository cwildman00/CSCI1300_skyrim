# CSCI1300_skyrim
CSCI 1300 final project: Text-Based Elder Scrolls V: Skyrim - Helgen Sequence
____________________________________________________________________________________
****DISCLAIMER****
I do not claim ownership of any story content of this game. I only own the code 
written. 
All story credit goes to Bethesda Game Studios for their game The Elder Scrolls V:
Skyrim. 
This is an adaptation of the game's prologue; changes have been made to the story 
for clarity and length. 
____________________________________________________________________________________

This is an adaptation of Skyrim's title sequence and first quest: Unbound. Due to 
deadline constraints at the time, it was impossible to recreate the prologue in 
its entirety. As such, modifications had to be made to the story for the sake of 
length. The goal is to return one day and finish the quest in its entirety.

**Project Requirements**
	- 4+ user-defined classes (one can be a driver class)
	- 4+ data members in two of the classes
	- 1 class should have an array of obects from a different created class as a data 
  	  member
	- 6+ if/else statements
	- 2+ nested loops
	- File I/O

**Project Functionality**
	The backbone of the game is file I/O.
	It works by means of feeding in and reading different .txt files that contain 
	various tags. 
	Tags might look like:
		- [ADD]
		- [CONT]
		- [COMBAT]
	If a tag is caught by the read function, then a function corresponding to that
	tag will trigger and enable gameplay. Once the function is complete then reading
	the story will continue until the next tag is found.

**Features Includes**
	Character creation--> includes writing to files
	Combat--> includes reading and writing to files
	Mini game--> includes randomization
	Story--> file reading
__________________________________________________________________________________________________________________
__________________________________________________________________________________________________________________
**CLASSES**

INVENTORY
  Purpose:
    Organize and manage items on large scale

ITEMS
  Purpose:
    Create new items and manage them on the smaller scale
    
PLAYER:
  Purpose:
    Create character
    Manage health
    Manage equipped items
__________________________________________________________________________________________________________________
__________________________________________________________________________________________________________________
***FUNCTIONS***
*Helper Functions*

split 
	int split (string toSplit, char separ, string array[], int arrSize);
	-
	Splits a string by a given char delimiter into the given array.
	Used in:
    - Loading game saves
    - Reading opponent information and loading in opponents for combat
    - Reading item information
  
whileStatic
	void whileStatic (int choice, int lowInt, int highInt);
	-
	Created to reduce number of while loops
	Only for decisions that take one of two answers
	Prevents user error

whileRange
	void whileRange (int choice, int lowInt, int highInt);
	-
	Created to reduce number of while loops
	Only for decisions that take a range of answers
	Prevents user error
	
*Tag Functions*

combat
	void combat (player& hero, player& opponent, inventory& heroInventory, inventory& opponentInventory, bool runOkay);
	-
	Primary combat function, called by [COMBAT]
	Takes in combatants, inventories,and if running from combat is allowed
	Inventories are saved prior to battle in case of death
	Opponent information is predefined and read from .txt file
	Damage calculator in player.h
	Menu:
	* Attack
		- Player gets first move, inflicts random number of hits.
		- Opponent retaliates
	* Defend
		- Player has 1/3 chance of deflecting attack
		- If successful, opponent takes half damage. 
		- If fail, player takes damage as normal
	* Take potion
		- Opens potion inventory if there are any available
		- Player chooses which to take, then will be returned to main menu to choose another option
	* Open inventory
		- Opens a menu to access weapon/armor inventories for equipping
	* Attempt to run
		- 1/3 chance to run IF running is allowed.
		
	
createChar
	player createChar(player character);
	-
	Character creation function, called by [SET UP]
	Takes in a player class arguement --> a blank charcter is passed through, equivallent to the game's default "Prisoner"
	Prompts user for:
		- Gender
		- Race
		- Name
		- Confirmation of the above before moving on
	Details about Skyrim's races are intended to be added in the future.
	Player information is saved to a .txt file to be opened later if needed (acts as save file)
	

cont
	void cont();
	-
	Continues the story, called by [CONT]
	Prompts user to press 'ENTER' to continue
	Intended to break the story into bite sized pieces instead of flooding the terminal
	
	
lockpick
	void lockpick(int numPicks, item reward, inventory playerInventory);
	-
	Lockpicking minigame, called by [LOCKPICK] 
	Creates a random number between 1 and 10
	Asks the user to pick a number in that range
	User has 3 tries to guess the random number correctly
		- This is due to time constraints, the intention was they would be able to loot
		  lockpicks and have as many attempts as they have lockpicks. 
	If the player successfully picks the lock, then they will receive the items hidden behind that 
	   lock, which are specified in the .txt file.	


*Story*

readStory
	void readStory(string fileName);
	-
	Reads the full story from .txt files
	Takes in a .txt file name to initiate the story --> unboundHelgen.txt
	Uses ifstream to read .txt files
	    - When tags are read, the story is paused and the respective functions will be triggered. 
	Uses player decisions to determine additional files to open
	
*Main*

main
	int main ()
	-
	Calls readStory, initiates the game.
__________________________________________________________________________________________________________________

THIS IS A WORK IN PROGRESS THAT WILLL CONTINUE TO DEVELOP AS I HAVE THE PERSONAL TIME.

I DO NOT OWN THE CREATIVE CONTENT, IT BELONGS TO BETHESDA GAME STUDIOS.
















