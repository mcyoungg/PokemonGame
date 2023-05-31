
#include "WildPokemon.h"

WildPokemon::WildPokemon() :GameObject('W') {
    attack = 3;
    health = 10;
    variant = 1;
    in_combat = false;
    name = "WillyWonka";
    trainer = 0;
    id_num = 0;
    location = Point2D();
    state = IN_ENVIRONMENT;
    cout << "WildPokemon default constructed" << endl;

}
WildPokemon::WildPokemon(string name, double attack, double health, bool variant, int id, Point2D in_loc): GameObject(in_loc, id, 'W'){
    this -> name = name;
    this -> attack = attack;
    this -> health = health;
    //for extra credit we could make a dervied class of WildPokemon
    this -> variant = variant;
    location = in_loc;
    in_combat = false;
    trainer = 0;
    state = IN_ENVIRONMENT;
    cout << "WildPokemon constructed" << endl;
}

WildPokemon::~WildPokemon(){
    cout << "WildPokemon destructed" << endl;
}

Trainer* WildPokemon::get_trainer(){
    return trainer;
 }
void WildPokemon::set_trainer(Trainer* in_trainer){
    trainer = in_trainer;
 }

bool WildPokemon::get_variant(){
    return variant;
}

double WildPokemon::get_attack(){
    return attack;
}

double WildPokemon::get_health(){
    return health;
}

bool WildPokemon::get_in_combat(){
    return in_combat;
}

bool WildPokemon::Update(){
    //when the WildPokemon's health is 0 or below changes the state to DEAD

   IsAlive();
   if(state == IN_ENVIRONMENT){
        if(FollowingTrainer()){
            trainer -> Add_WildPokemon();
        }
    }
    else if(state == IN_TRAINER){
        FollowingTrainer();
    }
    //when the WildPokemon is following a trainer changes the state to IN_TRAINER
    // will update location so that it matches the trainer location 


    //Update WildPokemon's health based on whether the trainer is moving (decreases by 1)
    //the trainer that the wild pokemon is following gets an additional 1 health decrease as it moves 
    //this can also be used to update health of WP if trainer is at the center recovering, increases by the number of potions bought, 
        //trainer's health decreases by however much the WP's health increased 
    //if the trainer is in the gym battling, the WP's healh decreases by the number of battles fought, trainer's health decreases by 2
    
    if(trainer!= 0){
        unsigned int trainer_current_health =  trainer -> GetTrainerHealth();
        switch(trainer -> GetState()){
            case MOVING:
            case MOVING_TO_CENTER:
            case MOVING_TO_GYM:{
                trainer -> SetTrainerHealth(trainer_current_health - 1);
            //wildpokemon's health 
                health -= 1;
                break;
            }
            case RECOVERING_HEALTH:{
                unsigned int total_health_inc = trainer -> GetNumPotionsBought();
                trainer -> SetTrainerHealth(trainer_current_health - total_health_inc);
                health += total_health_inc;
                break;
            }
            //Addtionally if trainer is battling, WP'S comabt status is shown
            //to demonstrate this InCombatStatus() function is called
            case BATTLING_IN_GYM:{
                unsigned int total_health_dec = trainer -> GetNumBattlesFought();
                trainer -> SetTrainerHealth(trainer_current_health - total_health_dec);
                health -= total_health_dec;
                InCombatStatus();
                break;
            } 
        }
    }
    return false; //not sure when to return false
}

void WildPokemon::ShowStatus(){
    cout << "Wild Pokemon Status: " << endl;
    GameObject::ShowStatus();
    if(!IsAlive()){
        state = DEAD;
    }
    if(state == IN_ENVIRONMENT){
        cout << "Is in the environment" << endl;
    }
    else if(state == IN_TRAINER){
        cout << "Is following trainer: " << trainer -> GetId() << endl;
        cout << "In Combat with trainer: " << trainer -> GetName() << endl;
    }
    else if (state == DEAD){
        cout << "Wild Pokemon "<< display_code << id_num << " has died " << endl;
        cout << "Wild Pokemon "<< display_code << id_num << " has been removed from the trainer's list " << endl;
    }
    cout << "\t Health: " << health << endl;
    cout << "\t Attack: " << attack << endl;
    cout << "\tVariant: " << variant << endl;
}

bool WildPokemon::IsAlive(){
    if(!health){
        //returns false if not alive, so dead
        cout << "Wild Pokemon " << display_code << id_num << " has 0 health remaining" << endl;
        if(FollowingTrainer()){
            trainer -> Remove_WildPokemon();
            trainer = 0;
        }
        return false;
    }
    //if alive
    return true;
}

bool WildPokemon::ShouldBeVisible(){
    //returns true if alive, then it should be visible
     if(IsAlive()){
        return true;
     }
     return false;
}

bool WildPokemon::FollowingTrainer(){
    if(trainer!= 0){
        if(!(trainer -> HasFainted())){
            state = IN_TRAINER;
            in_combat = true;
            location = trainer -> GetLocation();
            return true;
        }
    }
    return false;
}

void WildPokemon::InCombatStatus(){
    //only show combat status of alive pokemon that is following a trainer
    if(IsAlive() && FollowingTrainer()){
        cout << "\t In Combat:" << in_combat << " /t " << "Is Alive: " << IsAlive() << endl;
    }
}


