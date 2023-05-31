
#include "Building.h"

Building::Building() : GameObject('B'){
    trainer_count = 0;
    cout << "Building default constructed" << endl;
}

Building::Building(char in_code, int in_id, Point2D in_loc) : GameObject(in_loc, in_id, in_code){
    trainer_count = 0;
    cout << "Building constructed" << endl;
}
Building::~Building(){
    cout << "Building destructed" << endl;
}

void Building::AddOneTrainer(){
    trainer_count += 1;
}
void Building::RemoveOneTrainer(){
    trainer_count -= 1;
}
void Building::ShowStatus(){
    GameObject::ShowStatus();
    string plurality;
    if(trainer_count != 1){
        plurality = " trainers are";
    }
    else{
        plurality = " trainer is";
    }
    cout << trainer_count << plurality << " in this building" << endl;
}
bool Building::ShouldBeVisible(){
    return true;
}
//implemented a getter function to return the number of trainers in a building
unsigned int Building::GetNumTrainers(){
    return trainer_count;
}
