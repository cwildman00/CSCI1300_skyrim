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
____________________________________________________________________________________
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
	
	





























