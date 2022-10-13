#include <iostream>
#include <list>
#include <sstream>
#include <memory>
#include <aux.hpp>

class Kid {
private:
    int age;
    std::string name;
public:
    Kid(std::string name, int age) {
        this->age = age;
        this->name = name;
    }
    int getAge() {
        return age;
    }
    std::string getName() {
        return name;
    }
    std::string str() {
        return name + ":" + std::to_string(age);
    }
};

using PtrKid = std::shared_ptr<Kid>;

std::ostream& operator<<(std::ostream& os,  PtrKid kid) {
    return (os << kid->str());
}

class Trampoline {
    std::list<PtrKid> waiting;
    std::list<PtrKid> playing;
    
    PtrKid removeFromList(std::string name, std::list<PtrKid>& lista) {
        for(auto it = lista.begin(); it != lista.end(); it++) {
            if( (*it)->getName() == name) {
                auto aux = (*it);
                lista.remove(*it);
                return aux;
            }
            
        }
        return nullptr;
        
    }

public:
    Trampoline() {
    }
    
    void arrive(PtrKid kid) {
         waiting.push_front(kid); 
         return;
    }

    void enter() {
        if(this->waiting.size() == 0){
            std::cout << "[]\n";
            return;
        }
        this->playing.push_front( waiting.back() );
        this->waiting.pop_back();
        return;
    }

    void leave() {
        if(this->playing.size() != 0) {
            this->waiting.push_front( playing.back() );
            this->playing.pop_back();
            return;
        }
    }

    PtrKid removeKid(std::string name) { 
        removeFromList(name, this->waiting);
        removeFromList(name, this->playing);
        return nullptr;
    }
    std::string str() {
        return (waiting | aux::FMT()) + " => " + (playing | aux::FMT());
    }
};

int main() {
    aux::Chain chain;
    aux::Param param;
    Trampoline tr;
    chain["arrive"] = [&]() { tr.arrive(std::make_shared<Kid>(param[1], aux::to<int>(param[2]))); };
    chain["enter"]  = [&]() { tr.enter(); };
    chain["leave"]  = [&]() { tr.leave(); };
    chain["remove"] = [&]() { tr.removeKid(param[1]); };
    chain["show"]   = [&]() { std::cout << tr.str() << std::endl; };

    aux::execute(chain, param);
}