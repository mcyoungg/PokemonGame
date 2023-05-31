//number of wildpokemon follwoing trainer lags in update
//delete update messages in each file


#include "Model.h"

Model::Model(){
    time = 0;

    cout << "Model Default Constructed" << endl;
    
    PokemonCenter* center_ptrs0 = new PokemonCenter(1, 1, 100, Point2D(1,20));
    PokemonCenter* center_ptrs1 = new PokemonCenter(2, 2, 200, Point2D(10,20));
    
    Trainer* trainer_ptrs0 = new Trainer("Ash", 1, 'T', 2, Point2D(5,1));
    Trainer* trainer_ptrs1 = new Trainer("Misty", 2, 'T', 2, Point2D(10,1));

    PokemonGym* gym_ptrs0 = new PokemonGym(10, 1, 2, 3, 1, Point2D());
    PokemonGym* gym_ptrs1 = new PokemonGym(20, 5, 7.5, 4, 2, Point2D(5,5));

    //implement a pointer getter for Wild Pokemon Pointer
    WildPokemon* wildpokemon_ptrs0= new WildPokemon("Pikachu", 1, 2, 1, 1, Point2D(10,12));
    WildPokemon* wildpokemon_ptrs1 = new WildPokemon("Pineco",1, 7, 1, 2, Point2D(15,5));

    object_ptrs.push_back(dynamic_cast<GameObject*>((center_ptrs0)));
    object_ptrs.push_back(dynamic_cast<GameObject*>((center_ptrs1)));
    object_ptrs.push_back(dynamic_cast<GameObject*>((trainer_ptrs0)));
    object_ptrs.push_back(dynamic_cast<GameObject*>((trainer_ptrs1)));
    object_ptrs.push_back(dynamic_cast<GameObject*>((gym_ptrs0)));
    object_ptrs.push_back(dynamic_cast<GameObject*>((gym_ptrs1)));
    object_ptrs.push_back(dynamic_cast<GameObject*>((wildpokemon_ptrs0)));
    object_ptrs.push_back(dynamic_cast<GameObject*>((wildpokemon_ptrs1)));
    active_ptrs = object_ptrs;

    trainer_ptrs.push_back(trainer_ptrs0);
    trainer_ptrs.push_back(trainer_ptrs1);

    gym_ptrs.push_back(gym_ptrs0);
    gym_ptrs.push_back(gym_ptrs1);

    center_ptrs.push_back(center_ptrs0);
    center_ptrs.push_back(center_ptrs1);

    wildpokemon_ptrs.push_back(wildpokemon_ptrs0);
    wildpokemon_ptrs.push_back(wildpokemon_ptrs1);

}
Model::~Model(){
    cout << "Model destructed" << endl;
  
    for(gameobject_itr = object_ptrs.begin(); gameobject_itr != object_ptrs.end(); gameobject_itr++){
        delete *(gameobject_itr);
        object_ptrs.erase(gameobject_itr);
    }
}

Trainer* Model::GetTrainerPtr(int id){
    for(trainer_itr = trainer_ptrs.begin(); trainer_itr != trainer_ptrs.end(); trainer_itr++){
       if(id == (*trainer_itr) -> GetId()){
        return *trainer_itr;
       }  
    }
    return 0;   
}

PokemonCenter* Model::GetPokemonCenterPtr(int id){
    for(center_itr = center_ptrs.begin(); center_itr != center_ptrs.end(); center_itr++){
       if(id == (*center_itr) -> GetId()){
        return (*center_itr);
       }  
    }
    return 0; 
}

PokemonGym* Model::GetPokemonGymPtr(int id){
    for(gym_itr = gym_ptrs.begin(); gym_itr != gym_ptrs.end(); gym_itr++){
       if(id == (*gym_itr) -> GetId()){
        return (*gym_itr);
       }  
    }
    return 0; 
}
WildPokemon* Model::GetWildPokemonPtr(int id){
    for(wildpokemon_itr = wildpokemon_ptrs.begin(); wildpokemon_itr != wildpokemon_ptrs.end(); wildpokemon_itr++){
        if(id == (*wildpokemon_itr) -> GetId()){
            return (*wildpokemon_itr);
        }  
    }   
return 0; 
}

bool Model::Update(){
    time += 1;
    int count_gyms_cleared = 0;
    int count_trainers_fainted = 0;
    
    for(gym_itr = gym_ptrs.begin(); gym_itr != gym_ptrs.end(); gym_itr++){
        if(!((*gym_itr) -> GetNumBattlesRemaining())){
            count_gyms_cleared += 1;
        }
    }
    for(trainer_itr = trainer_ptrs.begin(); trainer_itr != trainer_ptrs.end(); trainer_itr++){
         if((*trainer_itr) -> HasFainted()){
                count_trainers_fainted += 1;
        }
    }
        
    if(trainer_ptrs.size() == count_trainers_fainted){
        cout << "GAME OVER: You lose! All of your Trainers' pokemon have fainted!" << endl;
        this -> ~Model();
        exit(0);
    }
    else if(gym_ptrs.size() == count_gyms_cleared){
        cout << "GAME OVER: You win! All battles done!" << endl;
        this -> ~Model();
        exit(0);
    }
    //update active list
    for(gameobject_itr = active_ptrs.begin(); gameobject_itr != active_ptrs.end(); gameobject_itr++){
        if(!(*gameobject_itr) -> ShouldBeVisible()){
            cout << "Dead object removed" << endl;
            active_ptrs.erase(gameobject_itr);
        }
    }
    //active list calls update function
    int count = 0;
    for(gameobject_itr = active_ptrs.begin(); gameobject_itr != active_ptrs.end(); gameobject_itr++){
        if((*gameobject_itr) -> Update()){
            return true;
        }
    }
    //checks whether wildpokemon and trainer are at the same location
    for(wildpokemon_itr = wildpokemon_ptrs.begin(); wildpokemon_itr != wildpokemon_ptrs.end(); wildpokemon_itr++){
        IsAtTrainer((*wildpokemon_itr));  
    }  
    return false;
}

void Model::Display(View &view){
    cout << "Time: " << time << endl;
    for(gameobject_itr = active_ptrs.begin(); gameobject_itr != active_ptrs.end(); gameobject_itr++){
            view.Plot((*gameobject_itr));
    }
}

void Model::ShowStatus(){
    for(gameobject_itr = object_ptrs.begin(); gameobject_itr != object_ptrs.end(); gameobject_itr++){
        (*gameobject_itr) -> ShowStatus();
    }
}

void Model::IsAtTrainer(WildPokemon* wp){
    for(trainer_itr = trainer_ptrs.begin(); trainer_itr != trainer_ptrs.end(); trainer_itr++){
       if((*trainer_itr) -> GetLocation() == wp -> GetLocation()){
        wp -> set_trainer((*trainer_itr));
       }
    }
}

bool Model::IsDuplicateId(char code, int id){
    switch(code){
        case 't':
            if(GetTrainerPtr(id)){
                return true;
            }
            break;
        case 'c':
            if(GetPokemonCenterPtr(id)){
                return true;
            }
            break;
        case 'g':
            if(GetPokemonGymPtr(id)){
                return true;
            }
            break;
        case 'w':
            if(GetWildPokemonPtr(id)){
                return true;
            }
            break;
    }
    return false;
}

void Model::NewCommand(char type, int id, Point2D loc){

    switch(type){
        case 'c':{
            PokemonCenter* user_def_center = new PokemonCenter();
            user_def_center -> SetId(id);
            user_def_center -> SetLocation(loc);
            center_ptrs.push_back(user_def_center);
            object_ptrs.push_back(user_def_center);
            active_ptrs.push_back(user_def_center);
            break;
        }
        case 'g':{
            PokemonGym* user_def_gym = new PokemonGym();
            user_def_gym -> SetId(id);
            user_def_gym -> SetLocation(loc);
            gym_ptrs.push_back(user_def_gym);
            object_ptrs.push_back(user_def_gym);
            active_ptrs.push_back(user_def_gym);
            break;
        }
        case 't':{
            Trainer* user_def_trainer = new Trainer();
            user_def_trainer -> SetId(id);
            user_def_trainer -> SetLocation(loc);
            trainer_ptrs.push_back(user_def_trainer);
            object_ptrs.push_back(user_def_trainer);
            active_ptrs.push_back(user_def_trainer);
            break;
        }
        case 'w':{
            WildPokemon* user_def_wp = new WildPokemon();
            user_def_wp ->SetId(id);
            user_def_wp -> SetLocation(loc);
            wildpokemon_ptrs.push_back(user_def_wp);
            object_ptrs.push_back(user_def_wp);
            active_ptrs.push_back(user_def_wp);
            break;
        }
    }

}