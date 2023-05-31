#include "View.h"


View::View(){
size = 11;
scale = 2.0;
origin = Point2D();
}
bool View::GetSubscripts(int &out_x, int &out_y, Point2D location){
    out_x = int((location.x - origin.x)/scale);
    out_y = int((location.y - origin.y)/scale);

    if(out_x < size && out_y < size){
        return true;
    }
    cout << "An object is outside the display" << endl;
    return false;
}
void View::Clear(){
    for(int i = 0; i < size + 1 ; i++){
        for(int j = 0; j < size + 1; j++){
            grid[i][j][0] = '.';
            grid[i][j][1] = ' ';

        }
    }

}


void View::Plot(GameObject *ptr){
    int x_coord, y_coord;
    if(View::GetSubscripts(x_coord, y_coord, ptr -> GetLocation())){
        if(grid[x_coord][y_coord][0] == '.'){
            char *validLocation = &(grid[x_coord][y_coord][0]);
            ptr -> DrawSelf(validLocation);
        }
        else{
            grid[x_coord][y_coord][0] = '*';
            grid[x_coord][y_coord][1] = ' ';
        }
    }

}
void View::Draw(){
    for(int j = size - 1; j >= -1; j--){
        for(int i = -1; i <= size - 1; i++){
            //grid axis
            if(i == -1 && j%2 == 0){
                cout << j * 2;
                if(j/5 == 0){
                    cout << " ";
                }
            }
            else if(i == -1 && j%2 != 0){
                cout << "  ";
            }
            else if(j == -1 && i%2 == 0){
                cout << i * 2;
                if(i/5 == 0){
                    cout << " ";
                }
            }
            else if(j == -1 && i%2 != 0){
                cout << "  ";
            }
            //draw objects
            if(i >= 0 && j >= 0){
                cout << grid[i][j][0] << grid[i][j][1];
            }
        }
        cout << endl;
    }

}