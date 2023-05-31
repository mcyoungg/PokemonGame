/* GameCommand Functions */
#include <vector>
#include <sstream>
#include <string>
#include "Model.h"
#include "Trainer.h"
#include "Input_Handling.h"

using namespace std;
//#include "View.h"
void DoMoveCommand(Model &model, int trainer_id, Point2D p1);

void DoMoveToCenterCommand(Model &model, int trainer_id, int center_id);

void DoMoveToGymCommand(Model &model, int trainer_id, int gym_id);

void DoStopCommand(Model &model, int trainer_id);

void DoBattleCommand(Model &model, int trainer_id, unsigned int battles);

void DoRecoverInCenterCommand(Model &model, int trainer_id, unsigned potions_needed);

void DoAdvanceCommand(Model &model, View &view);

void DoRunCommand(Model &model, View &view);

bool ValidCommand(Model &model, vector<char>& commands, vector<int>& parameters);

void ExecuteCommand(Model &model, View &view, vector<char>& commands, vector<int>& parameters);

void LineSplit(string line, vector<char>& commands, vector<int>& parameters);