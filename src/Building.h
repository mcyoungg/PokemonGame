/* 
* This class is the base class for all building type objects in the game. 
* is responsible for tracking the total number of Pokemon Trainers that
* enter or leave a building.
*/
#ifndef BUILDING_H
#define BUILDING_H

#include "GameObject.h"

class Building: public GameObject{
    private:
    unsigned int trainer_count;

    public:
    Building();
    Building(char in_code, int in_Id, Point2D in_loc);
    ~Building();
    
    void AddOneTrainer();
    void RemoveOneTrainer();
    void ShowStatus();
    bool ShouldBeVisible();
    //implemented a getter function to return the number of trainers in a building
    unsigned int GetNumTrainers();

};

#endif
