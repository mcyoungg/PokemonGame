/* GameCommand Functions */
#include "GameCommand.h"


//#include "View.h"
void DoMoveCommand(Model &model, int trainer_id, Point2D p1){
    Trainer * trainer = model.GetTrainerPtr(trainer_id);
    cout << "Moving " << trainer -> GetName() << " to " << p1 << endl;
     trainer -> StartMoving(p1);
}

void DoMoveToCenterCommand(Model &model, int trainer_id, int center_id){
    Trainer * trainer = model.GetTrainerPtr(trainer_id);
    PokemonCenter *center = model.GetPokemonCenterPtr(center_id);
    cout << "Moving " << trainer -> GetName() << " to Pokemon Center " << center_id << endl;
    trainer -> StartMovingToCenter(center);
}

void DoMoveToGymCommand(Model &model, int trainer_id, int gym_id){
    Trainer * trainer = model.GetTrainerPtr(trainer_id);
    PokemonGym *gym = model.GetPokemonGymPtr(gym_id);
    cout << "Moving " << trainer -> GetName() << " to Pokemon Gym " << gym_id << endl;
    trainer -> StartMovingToGym(gym);
}

void DoStopCommand(Model &model, int trainer_id){
    Trainer * trainer = model.GetTrainerPtr(trainer_id);
    cout << "Stopping " << trainer -> GetName() << endl;
     trainer -> Stop();
}

void DoBattleCommand(Model &model, int trainer_id, unsigned int battles){
    Trainer * trainer = model.GetTrainerPtr(trainer_id);
    cout << trainer -> GetName() << " is attempting to battle" << endl;
    trainer -> StartBattling(battles);
}

void DoRecoverInCenterCommand(Model &model, int trainer_id, unsigned potions_needed){
    Trainer * trainer = model.GetTrainerPtr(trainer_id);
    cout << "Attempting to recover " << trainer -> GetName() << "'s Pokemon's health" << endl;
    trainer -> StartRecoveringHealth(potions_needed);
}

void DoAdvanceCommand(Model &model, View &view){
    cout << "Advancing one tick" << endl;

    model.Update();
    model.ShowStatus();
    view.Clear();
    model.Display(view);
    view.Draw();
    
}

void DoRunCommand(Model &model, View &view){
    cout << "Advancing to next event" << endl;
    int counter = 0;
    while(counter < 5){
        if(model.Update()){
            model.ShowStatus();
            view.Clear();
            model.Display(view);
            view.Draw();
            break;
        }
        model.ShowStatus();
        view.Clear();
        model.Display(view);
        view.Draw();
        counter++;
    }
    counter = 0;
}

void ExecuteCommand(Model &model, View &view, vector<char> &commands, vector<int> &parameters){
 
    switch (commands.at(0)){
        case 'm':
            DoMoveCommand(model, parameters.at(0), Point2D(parameters.at(1), parameters.at(2)));
            break;
        case 'c':
           DoMoveToCenterCommand(model, parameters.at(0), parameters.at(1));
           break;
        case 'g':
           DoMoveToGymCommand(model, parameters.at(0), parameters.at(1));
           break;
        case 's':
           DoStopCommand(model, parameters.at(0));
           break;
        case 'b':
           DoBattleCommand(model, parameters.at(0), parameters.at(1));
           break;
        case 'p':
           DoRecoverInCenterCommand(model, parameters.at(0), parameters.at(1));
           break;
        case 'a':
            DoAdvanceCommand(model, view);
            break;
        case 'r':
            DoRunCommand(model, view);
            break;
        case 'n':
             model.NewCommand(commands.at(1), parameters.at(0), Point2D(parameters.at(1), parameters.at(2)));
             break;
        case 'q':
            cout << "Quitting game" << endl;
            model.~Model();
            exit(0);
    }

}

bool ValidCommand(Model &model, vector<char> &commands, vector<int> &parameters){
    
    string vaild_commands = "mcgspbarqn";
    string valid_type_codes = "cgtw";
    try{
         if (vaild_commands.find(commands.at(0)) == string::npos){
            cout << "Error: Enter a valid command code" << endl;
            throw Invalid_Input(commands.at(0));
        }
        //check if valid movement in display, check if valid placement of new object in display
        switch(commands.at(0)){
            case 'm':
            case 'n':
                if(parameters.at(1) < 0 || parameters.at(1) >= 20){
                    cout << "Error: Enter valid location" << endl;
                    throw Invalid_Input(parameters.at(1));
                }
                if(parameters.at(2) < 0 || parameters.at(2) >= 20){
                    cout << "Error: Enter valid location" << endl;
                    throw Invalid_Input(parameters.at(2));
                }
                break;
        }
        switch(commands.at(0)){
            case 'c':{
                if(!model.GetPokemonCenterPtr(parameters.at(1))){
                    cout << "Error: Invalid id" << endl;
                    throw Invalid_Input(parameters.at(1));
                }
                break;
            }
            case 'g':{
                if(!model.GetPokemonGymPtr(parameters.at(1))){
                    cout << "Error: Invalid id" << endl;
                    throw Invalid_Input(parameters.at(1));
                }
                break;
            }
            case 'm':
            case 'p':
            case 'b':
            case 's':{
                if(!model.GetTrainerPtr(parameters.at(0))){
                    cout << "Error: Invalid id" << endl;
                    throw Invalid_Input(parameters.at(0));
                }
                break;
            }
            case 'n':{
                //error check type
                if (valid_type_codes.find(commands.at(1)) == string::npos){
                    cout << "Error: Invalid type code " << endl;
                    throw Invalid_Input(commands.at(1));
                }
                //error check id
                if(parameters.at(0) > 9 || parameters.at(0) < 0){
                    cout << "Error: Not a valid id range " << endl;
                    throw Invalid_Input(commands.at(0));
                }
                //error check for duplcate ids
                if(model.IsDuplicateId(commands.at(1),parameters.at(0))){
                    cout << "Error: An existing member of this type already has this id! " << endl;
                    throw Invalid_Input(parameters.at(0));
                }
                break;
            }
        }
    }
    catch (Invalid_Input& except){
        cout << "Please enter a valid game command!" << endl;
        cout << "Try Again " << endl;
        return false;
    }
    return true;
}
void LineSplit(string line, vector<char>& commands, vector<int>& parameters){
    string rest; //reads in the line of user input
    char delim = ' ';
    stringstream ss (line); 

    try{
        getline(ss, rest, delim);
        commands.push_back(rest[0]);

        switch(commands.at(0)){
            case 'm':
            case 'c':
            case 'g':
            case 'p':
            case 'b':
            case 's':{
                while(getline(ss, rest, delim)){
                    parameters.push_back(stoi(rest));
                }
                break;
            }
            case 'n':{
                getline(ss, rest, delim);
                commands.push_back(rest[0]);
                while(getline(ss, rest, delim)){
                    parameters.push_back(stoi(rest));
                }
                break;
            }
        }
    }
     catch(invalid_argument){
        cout << "Error: Invalid input" << endl;
        cout << "Please enter valid command!" << endl;
     }
}
