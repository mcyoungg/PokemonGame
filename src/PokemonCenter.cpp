#include "PokemonCenter.h"

PokemonCenter::PokemonCenter() {
    display_code = 'C';
    id_num = 0;
    potion_capacity = 100;
    num_potions_remaining = potion_capacity;
    pokedollar_cost_per_potion = 5;
    location = Point2D();
    state = POTIONS_AVAILABLE;
    cout << "PokemonCenter default constructed" << endl;

}
PokemonCenter::PokemonCenter(int in_id, double potion_cost, unsigned int potion_cap, Point2D in_loc){
    display_code = 'C';
    id_num = in_id;
    location = in_loc;
    pokedollar_cost_per_potion = potion_cost;
    potion_capacity = potion_cap;
    num_potions_remaining = potion_capacity;
    state = POTIONS_AVAILABLE;
    cout << "PokemonCenter constructed" << endl;
}
PokemonCenter::~PokemonCenter(){
    cout << "PokemonCenter destructed" << endl;
}
bool PokemonCenter::HasPotions(){
    if(num_potions_remaining > 0){
        return true;
    }
    return false;
}
unsigned int PokemonCenter::GetNumPotionsRemaining(){
    return num_potions_remaining;
}
bool PokemonCenter::CanAffordPotion(unsigned int potion, double budget){
    if(budget > PokemonCenter::GetPokeDollarCost(potion)){
        return true;
    }
    return false;
}
// does this mean the total amount of money 
double PokemonCenter::GetPokeDollarCost(unsigned int potion){
    return pokedollar_cost_per_potion * potion;
}
unsigned int PokemonCenter::DistributePotion(unsigned int potion_needed){
    unsigned int current_num_potions = num_potions_remaining;
    if(num_potions_remaining >= potion_needed){
        num_potions_remaining -= potion_needed;
        return potion_needed;
    }
    else{
        num_potions_remaining = 0;
        return current_num_potions;
    }
}
bool PokemonCenter::Update(){
    if(!num_potions_remaining && !state){
        state = NO_POTIONS_AVAILABLE;
        display_code = 'c';
        cout << "PokemonCenter " << id_num << " has ran out of potions." << endl;
        return true;
    }
    else{
        return false;
    }
}
void PokemonCenter::PokemonCenter::ShowStatus(){  
    cout << "PokemonCenter Status: " << endl;
    Building::ShowStatus();
    cout << "PokeDollars per potion: " << pokedollar_cost_per_potion << endl;
    cout << "has "<< num_potions_remaining << " potion(s) remaining" << endl;
}