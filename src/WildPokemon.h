
#ifndef WILDPOKEMON_H
#define WILDPOKEMON_H
#include "GameObject.h"
#include "Trainer.h"

enum WildPokemonStates{
    IN_ENVIRONMENT = 0,
    DEAD = 1,
    IN_TRAINER = 2
};

class WildPokemon: public GameObject{
    
    protected:
    double attack;
    double health;
    bool variant;
    bool in_combat;
    string name;
    Trainer* trainer;

    public:
    WildPokemon();
    WildPokemon(string name, double attack, double health, bool variant, int id, Point2D in_loc);
    ~WildPokemon();

    Trainer* get_trainer();
    void set_trainer(Trainer* in_trainer);
    bool get_variant();
    double get_attack();
    double get_health();
    bool get_in_combat();
    bool Update();
    void ShowStatus();
    bool IsAlive();
    bool ShouldBeVisible();

    void IsAtTrainer();
    bool FollowingTrainer();
    void InCombatStatus();
};

#endif