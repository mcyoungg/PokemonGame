
#include <iostream>
#include <string>
#include <vector>
#include "GameCommand.h"

using namespace std;

int main(){

    string game_command;
    Model m;
    View v;

    vector <char> char_commands;
    vector <int> game_parameters;
    
    m.ShowStatus();
    v.Clear();
    m.Display(v);
    v.Draw();

    while(true){
        cout << "Enter a Game Command: " << endl;
        getline(cin, game_command);

        LineSplit(game_command, char_commands, game_parameters);

        if(ValidCommand(m, char_commands, game_parameters)){
            ExecuteCommand(m, v, char_commands, game_parameters);
        }
        char_commands.clear();
        game_parameters.clear();
    
    }
    return 0;
}