#pragma once
#include "Wrapper.h"

class Engine{
public:
    Engine() = default;
    Engine(Engine const& engine) = delete;
    Engine& operator=(Engine const& engine) = delete;
    Engine(Engine&& Engine) = default;
    Engine& operator=(Engine&& engine) = default;
    ~Engine() = default;

    void register_command(Wrapper* wrapper, std::string command){
        assert(commands.find(command) == commands.end() && "Command already exists");
        assert(wrapper != nullptr && "Unexpected nullptr in engine");

        commands[command] = wrapper;
    }

    int execute(std::string command, std::vector<std::pair<std::string, int>>const& arguments){
        assert(commands.find(command) != commands.end() && "Command doesn't exists");
        return(commands[command]->function_execute(arguments));
    }
private:
    std::map<std::string, Wrapper*> commands;
};