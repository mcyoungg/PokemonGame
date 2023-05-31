#include "Trainer.h"

Trainer::Trainer(): GameObject('T'){
    speed = 5;
    state = STOPPED;
    is_at_center = false;
    is_in_gym = false;
    health = 10;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy = 0;
    potions_to_buy = 0;
    //default name if not specified
    name = "Trainer";
    current_center = 0;
    current_gym = 0;
    destination = Point2D();
    delta = Vector2D();
    location = Point2D();
    id_num = 0;

    //keeps track of the number of potions bought,
    potions_bought = 0;
    //keeps track of the number of battles fought,
    num_of_battles_fought = 0;
    //tracks num of wildpokemon following trainer
    num_wildpokemon = 0;

    cout << "Trainer default constructed" << endl;
}
Trainer::Trainer(char in_code): GameObject(in_code){
    speed = 5;
    state = STOPPED;
    display_code = in_code;
    is_at_center = false;
    is_in_gym = false;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy = 0;
    potions_to_buy = 0;
    //default name if not specified
    name = "Trainer_1";
    current_center = 0;
    current_gym = 0;
    destination = Point2D();
    //update with See How Trainer Moves
    delta = Vector2D();

    //keeps track of the number of potions bought,
    potions_bought = 0;
    //keeps track of the number of battles fought,
    num_of_battles_fought = 0;
    //tracks num of wildpokemon following trainer
    num_wildpokemon = 0;


    cout << "Trainer constructed" << endl;
}
Trainer::Trainer(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc): GameObject(in_loc, in_id, in_code){
    name = in_name;
    speed = in_speed;
    id_num = in_id;
    display_code = in_code;
    location = in_loc;
    is_at_center = false;
    is_in_gym = false;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy = 0;
    potions_to_buy = 0;
    current_center = 0;
    current_gym = 0;
    destination = Point2D();
    //update with See How Trainer Moves
    delta = Vector2D();
    state = STOPPED;

    //keeps track of the number of potions bought,
    potions_bought = 0;
    //keeps track of the number of battles fought,
    num_of_battles_fought = 0;
    //tracks num of wildpokemon following trainer
    num_wildpokemon = 0;


    cout << "Trainer constructed" << endl;
}
Trainer::~Trainer(){
    cout << "Trainer destructed" << endl;
}
bool Trainer::UpdateLocation(){
    //check within delta of destination
    float current_x_pos = fabs(destination.x - location.x);
    float current_y_pos = fabs(destination.y - location.y);

    if(current_x_pos <= fabs(delta.x) && current_y_pos <= fabs(delta.y)){
        location = destination;
        cout << display_code << id_num << " I'm there!" << endl;
        return true;
    }
    location = location + delta;

    cout << display_code << id_num << " step ..." << endl;
    return false;
    }
    //saves destination, calculates delta
string Trainer::GetName(){
    return name;
}
void Trainer::SetupDestination(Point2D dest){
    destination = dest;
    if(!STOPPED){
        delta = (destination - location) * (speed/GetDistanceBetween(destination,location));
    }
}
void Trainer::StartMoving(Point2D dest){
    SetupDestination(dest);
    state = MOVING;
    
    if(!(GetDistanceBetween(location, destination))){
        cout << display_code << id_num << ": I'm already there. See?" << endl;
    }
    else if(HasFainted()){
        cout << display_code << id_num << ": My pokemon have fainted. I may move but you cannot see me." << endl;
        state = FAINTED;
    }
    else{
        state = MOVING;
        cout << display_code << id_num << ": On my way." << endl;
    }
}
void Trainer::StartMovingToGym(PokemonGym* gym){
    current_gym = gym;
   
    SetupDestination(current_gym -> GetLocation());

    if(HasFainted()){
        state = FAINTED;
        cout << display_code << id_num << ": My Pokemon have fainted so I can't move to gym..." << endl;
    }
    //condition where the trainer begins at the gym
    else if(!(GetDistanceBetween(location, destination))){
        cout << display_code << id_num << ": I am already at the PokemonGym! " << endl;
        is_in_gym = true;
        state = IN_GYM;
    }
    else{
        state = MOVING_TO_GYM;
        cout << display_code << id_num << ": On my way to the Gym " << current_gym -> GetId() << endl;
    }
    
}
void Trainer::StartMovingToCenter(PokemonCenter* center){
    current_center = center;
    SetupDestination(current_center -> GetLocation());
    
    if(HasFainted()){
        cout << display_code << id_num << ": My Pokemon have fainted so I should have gone to the center..." << endl;
        state = FAINTED;
    }
    else if(!(GetDistanceBetween(location, destination))){
        cout << display_code << id_num << ": I am already at the Pokemon Center! " << endl;
        is_at_center = true;
        state = AT_CENTER;
    }
    else{
        state = MOVING_TO_CENTER;
        cout << display_code << id_num << ": On my way to the Center " << current_center -> GetId() << endl;
    }

}
void Trainer::StartBattling(unsigned int num_battles){
    if(state == IN_GYM){
        is_in_gym = true;
        if(HasFainted()){
            cout << display_code << id_num << ": My Pokemon have fainted so no more battles for me..." << endl;
        }
        else if(current_gym -> GetPokeDollarCost(num_battles) > PokeDollars){
            cout << display_code << id_num << ": Not enough money for battles " << endl;
        }
        else if(!(current_gym -> GetNumBattlesRemaining())){
            cout << display_code << id_num << ": Cannot battle! This PokemonGym has no more trainers to battle! " << endl;
        }
        else{
            //num_battles is the number of battles requested
            state = BATTLING_IN_GYM;
            num_of_battles_fought = current_gym -> TrainPokemon(num_battles)/current_gym -> GetExperiencePerBattle();
            battles_to_buy = min(num_battles, num_of_battles_fought);
            cout << display_code << id_num << " Started to battle at the PokemonGym " << current_gym -> GetId() << " with " << num_battles << " battle(s)" << endl;
        }
    }
    else{
        cout << display_code << id_num << ": I can only battle in a PokemonGym! " << endl;
    }
}

void Trainer::StartRecoveringHealth(unsigned int num_potions){
    if(state == AT_CENTER){
        is_at_center = true;
      
        if(!(current_center -> CanAffordPotion(num_potions, PokeDollars))){
            cout << display_code << id_num << ": Not enough money to recover health" << endl;
        }
        else if (!(current_center -> HasPotions())){
            cout << display_code << id_num << ": Cannot recover! No potion remaining in this Pokemon Center" << endl;
        }
        else{
            state = RECOVERING_HEALTH;
            cout << display_code << id_num << ": Started recovering " << num_potions << " potions at Pokemon Center " << current_center -> GetId() << endl;
            potions_bought = current_center -> DistributePotion(num_potions);
            potions_to_buy = min(current_center -> GetNumPotionsRemaining(), num_potions);
            health += (potions_bought * 5);
        }
    }
    else{
        cout << display_code << id_num << ": I can only recover health at Pokemon Center!" << endl;
    }
}
void Trainer::Stop(){
    state = STOPPED;
    cout << display_code << id_num << ": Stopping..." << endl;
}
bool Trainer::HasFainted(){
    if(!health){
        state = FAINTED;
        return true;
    }
    return false;
}
bool Trainer::ShouldBeVisible(){
    if(!HasFainted()){
        //returns true if not fainted, then it should be visible
        return true;
    }
    return false;
}
void Trainer::TrainerStatus(){
    cout << "Being followed by " << num_wildpokemon << " Wild Pokemon" << endl;
    cout << "Health: " << health << endl;
    cout << "PokeDollars: " << PokeDollars << endl;
    cout << "Experience: " << experience << endl; 
}
void Trainer::ShowStatus(){
    cout << name << " Status: " << endl;
    GameObject::ShowStatus();
    TrainerStatus();
    //print state specific information 
    switch (state){
        case STOPPED:
            cout << "Stopped" << endl;
            break;
        case MOVING:
            if(!HasFainted()){
                cout << "Moving at a speed of " << speed << " to destination " << destination << " at each step of " << delta << endl;
            }
            break;
        case MOVING_TO_GYM:
            if(!HasFainted()){
                cout << "Heading to Pokemon Gym " << current_gym -> GetId() << " at speed of " << speed << " at each step of " << delta << endl;
            }
            break;
        case MOVING_TO_CENTER:
            if(!HasFainted()){
                cout << "Heading to Pokemon Center " << current_center -> GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
            }
            break;
        case IN_GYM:
            cout << "Inside Pokemon Gym " << current_gym -> GetId() << endl;
            break;
        case AT_CENTER:
            cout << "Inside Pokemon Center "<< current_center -> GetId() << endl;
            break;
        case BATTLING_IN_GYM:
            cout << "Battling in PokemonGym " << current_gym -> GetId() << endl; 
            break;
        case RECOVERING_HEALTH:
            cout << "Recovering health in Pokemon Center " << current_center -> GetId() << endl;
    }
}
bool Trainer::Update(){
    if(HasFainted()){
        state = FAINTED;
        cout << name << " is out of health and can't move" << endl;
        //return true;
    }
    switch (state){
        case STOPPED:
            return false;

        case MOVING:
            //decrease health by 1 since they are moving, and increase their dollar amount by some random amount
            health -= 1;
            PokeDollars += GetRandomAmountofPokeDollars();
            if(current_gym != 0 && current_gym -> GetNumTrainers() >= 1){
                current_gym -> RemoveOneTrainer();
            }
            else if (current_center != 0 && current_center -> GetNumTrainers() >= 1){
                current_center -> RemoveOneTrainer();
            }
            if(UpdateLocation()){
                state = STOPPED;
                return true;
            }
            return false;
        case MOVING_TO_GYM:
            health -= 1;
            PokeDollars += GetRandomAmountofPokeDollars();
            if (current_center != 0 && current_center -> GetNumTrainers() >= 1){
                current_center -> RemoveOneTrainer();
            }
            if(UpdateLocation()){
                state = IN_GYM;
                current_gym -> AddOneTrainer();
                return true;
            }
            return false;
        case MOVING_TO_CENTER:
            health -= 1;
            PokeDollars += GetRandomAmountofPokeDollars();
            if(current_gym != 0 && current_gym -> GetNumTrainers() >= 1){
                current_gym -> RemoveOneTrainer();
            }
            if(UpdateLocation()){
                state = AT_CENTER;
                current_center -> AddOneTrainer();
                return true;
            }
            return false;
        case IN_GYM:
            return false;

        case AT_CENTER:
            return false;

        case BATTLING_IN_GYM:
            experience +=  num_of_battles_fought * current_gym -> GetExperiencePerBattle();
            health -= current_gym -> GetHealthCost(num_of_battles_fought);
            PokeDollars -= current_gym -> GetPokeDollarCost(num_of_battles_fought);
            cout << "** " << name << " completed " << num_of_battles_fought << " battle(s)!**" << endl;
            cout << "** " << name << " gained " << experience << " experience!** " << endl;
            state = IN_GYM;
            return true;

        case RECOVERING_HEALTH:
            state = AT_CENTER;
            StartRecoveringHealth(potions_to_buy);
            PokeDollars -= current_center -> GetPokeDollarCost(potions_bought);
            cout << "** " << name << " recovered " << potions_bought * 5 << " health!**" << endl;
            cout << "** " << name << " bought " << potions_bought << " potion(s)!** " << endl;
            return true;  
    }
    return false;
}
void Trainer::Add_WildPokemon(){
    num_wildpokemon += 1;
}
void Trainer:: Remove_WildPokemon(){
    num_wildpokemon -= 1;
}
//returns a random number between 0.0 and 2.0 inclusive
unsigned int Trainer::GetTrainerHealth(){
    return health;
}
void Trainer::SetTrainerHealth(unsigned int in_health){
    health = in_health;
}
unsigned int Trainer::GetNumPotionsBought(){
    return potions_bought;
}
unsigned int Trainer::GetNumBattlesFought(){
    return num_of_battles_fought;
}
double GetRandomAmountofPokeDollars(){
    srand(time(0));
    return (rand() / (double) RAND_MAX) * (2 - 0) + 0;
} 

