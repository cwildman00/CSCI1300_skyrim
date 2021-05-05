//CSCI1300 Fall 2020
//Author: Cassie Wildman
//Recitation: 514 - Chris Gavin
//Project 3 - Item Class

/*/Purpose:
    -Create new items
    -Manage items
/*/

#include <string>
#include <vector>
using namespace std;

class item
{
    private:
        string name;
        string type;
        int rating;
        int weight;
        int value;
        bool equipped;

    public:
        item();
        item(string newName, string newType, int newRating, int newWeight, int newValue);

        string getName();
        void setName(string Name);

        string getType();
        void setType(string Type);

        int getRating();
        void setRating(int Rating);

        int getWeight();
        void setWeight(int Weight);

        int getValue();
        void setValue(int Value);

        bool getEquipped();
        void setEquipped(bool status);
    
};

