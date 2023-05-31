#ifndef TRAINER_H
#define TRAINER_H

#include "GameObject.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"


enum TrainerStates{
    STOPPED = 0,
    MOVING = 1,
    FAINTED = 2,
    AT_CENTER = 3,
    IN_GYM =4,
    MOVING_TO_CENTER = 5,
    MOVING_TO_GYM = 6,
    BATTLING_IN_GYM = 7,
    RECOVERING_HEALTH = 8
};

class Trainer: public GameObject{
    private: 
    double speed;
    bool is_at_center;
    bool is_in_gym;
    unsigned int health;
    unsigned int experience;
    double PokeDollars;
    unsigned int battles_to_buy;
    unsigned int potions_to_buy;
    string name;
    PokemonCenter* current_center;
    PokemonGym* current_gym;
    Point2D destination;
    Vector2D delta;
    //keeps track of the number of potions bought, calls the DistrubtePotion functions
    unsigned int potions_bought;
    //keeps track of the number of battles fought,
    unsigned int num_of_battles_fought; 
    //keeps track of the number of wildpokemon following the trainer
    unsigned int num_wildpokemon;
    
    protected:
    bool UpdateLocation();
    void SetupDestination(Point2D dest);

    public:
    Trainer();
    Trainer(char in_code);
    Trainer(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc);
    virtual ~Trainer();
    string GetName();
    void StartMoving(Point2D dest);
    void StartMovingToGym(PokemonGym* gym);
    void StartMovingToCenter(PokemonCenter* center);
    void StartBattling(unsigned int num_battles);
    void StartRecoveringHealth(unsigned int num_potions);
    void Stop();
    bool HasFainted();
    bool ShouldBeVisible();
    void ShowStatus();
    bool Update();
    //helper function to print the health, pokedollars, and experience for each trainer in the different states 
    void TrainerStatus();
    //keeps track of the number of pokemon 
    void Add_WildPokemon();
    void Remove_WildPokemon();

    unsigned int GetTrainerHealth();
    void SetTrainerHealth(unsigned int in_health);
    unsigned int GetNumPotionsBought();
    unsigned int GetNumBattlesFought();
    
};

double GetRandomAmountofPokeDollars();

#endif