#include <iostream>
#include "Wrapper.h"
#include "Engine.h"

class Subject{
public:
    int f3(int arg1, int arg2){
        return arg1 + arg2;
    }
};

int main(){
    Subject subj{};

    Wrapper wrapper(&subj, &Subject::f3, {{"arg1", 0}, {"arg2", 0}});

    Engine engine;
    engine.register_command(&wrapper, "command1");
    std::cout << engine.execute("command1", {{"arg1", 4}, {"arg2", 10}}) << std::endl;
    return 0;
}
