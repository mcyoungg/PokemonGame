#ifndef INPUT_HANDLING_H
#define INPUT_HANDLING_H

#include <string>
class Invalid_Input{

    public:
        Invalid_Input(std::string in_ptr): msg_ptr (in_ptr), param (0), command (0) { }
        Invalid_Input(int in_param): param (in_param), command (0) { }
        Invalid_Input(char in_command): command (in_command), param (0) { }
        const std::string msg_ptr;
        const int param;
        const char command;
    
    private:
        Invalid_Input ();
    //no default construction
};

#endif