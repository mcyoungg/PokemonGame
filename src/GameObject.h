/* 
* This class is the base class for all the objects in the game. 
* It is responsible for the member variables and functions that they all have in 
* common
*/
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <string>
#include <cmath>
#include <time.h>
#include <cstdlib>
#include "Point2D.h"


class GameObject{

protected:
Point2D location;
int id_num;
char display_code, state;

public:
GameObject(char in_code);
GameObject(Point2D in_loc, int in_id, char in_code);
virtual ~GameObject();

Point2D GetLocation();
int GetId();
char GetState();
virtual void ShowStatus();

virtual bool Update() = 0;
virtual bool ShouldBeVisible() = 0;

void DrawSelf(char *ptr);

void SetId(int in_id);
void SetLocation(Point2D loc);




};


#endif