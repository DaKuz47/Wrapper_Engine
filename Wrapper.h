#pragma once
#include <map>
#include <string>
#include <vector>
#include <cassert>
#include <functional>

class Wrapper{

public:
    template<typename Object, typename ...Args>
    Wrapper(Object* object, int (Object::*fptr)(Args...), std::vector<std::pair<std::string, int>>const& arguments) {
        //checking correction of data
        assert(object != nullptr && fptr != nullptr && "Unexpected nullptr");
        assert(sizeof...(Args) == arguments.size() && "Wrong number of arguments");
        for(auto argument: arguments){
            _arguments.insert(argument);
        }
        assert(arguments.size() == _arguments.size() && "Perhabs certain arguments has the same name");
        //wrapper over function
        wrapped_function = [this, object, fptr](std::vector<int>const& arguments){
            return (function_executer(object, fptr, arguments, std::make_index_sequence<sizeof...(Args)>{}));
        };
    }

    Wrapper() = delete;
    Wrapper(const Wrapper& wrapper) = delete;
    Wrapper& operator=(Wrapper const& wrapper) = delete;
    Wrapper(Wrapper&&) = default;
    Wrapper& operator=(Wrapper&&) = default;
    ~Wrapper() = default;

    //wrapped function execution
    int function_execute(std::vector<std::pair<std::string, int>> arguments){
        assert(arguments.size() == _arguments.size() && "Wrong number of arguments");

        std::map<std::string, int> checking_arguments;
        for(auto argument: arguments){
            checking_arguments.insert(argument);
        }
        assert(arguments.size() == checking_arguments.size() && "Perhabs certain arguments has the same name");

        auto it_end = checking_arguments.end();
        std::vector<int> arguments_value;
        for(auto argument: _arguments){
            assert(checking_arguments.find(argument.first) != it_end && "Wrong name of argument");
            arguments_value.push_back(checking_arguments[argument.first]);
        }

        return wrapped_function(arguments_value);
    }
    
private:
    std::map<std::string, int> _arguments{};
    std::function<int(const std::vector<int>&)> wrapped_function;

    //present elements of vector as parameters of function
    template<typename Object, typename ...Args, size_t...Idx>
    int function_executer(Object* object, int(Object::*fptr)(Args...), std::vector<int>const& args, std::index_sequence<Idx...>){
        return (object->*fptr)(args[Idx]...);
    }
    
};