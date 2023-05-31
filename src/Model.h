#ifndef MODEL_H
#define MODEL_H

/* stores all GameObjects in memory */
#include <list>
#include "GameObject.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Trainer.h"
#include "View.h"
#include "WildPokemon.h"


class Model{
private:
    int time;

    list<GameObject*> object_ptrs;
    list<GameObject*> active_ptrs;
    list<Trainer*> trainer_ptrs;
    list<PokemonCenter*> center_ptrs;
    list<PokemonGym*> gym_ptrs;
    list<WildPokemon*> wildpokemon_ptrs;

    list<GameObject*>::iterator gameobject_itr;
    list<Trainer*>::iterator trainer_itr;
    list<PokemonCenter*>::iterator center_itr;
    list<PokemonGym*>::iterator gym_itr;
    list<WildPokemon*>::iterator wildpokemon_itr;


public:
    Model();
    ~Model();

    Trainer* GetTrainerPtr(int id);
    PokemonGym* GetPokemonGymPtr(int id);
    PokemonCenter* GetPokemonCenterPtr(int id);
    WildPokemon* GetWildPokemonPtr(int id);
    bool Update();
    void Display(View &view);
    void ShowStatus();
    void IsAtTrainer(WildPokemon* wp);  
    bool IsDuplicateId(char code, int id);
    void NewCommand(char type, int id, Point2D loc);
};
#endif
