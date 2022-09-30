#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <aux.hpp>


class Pet{
private:
    int energyMax, hungryMax, cleanMax;
    int energy, hungry, clean;
    int diamonds;
    int age ;
    bool alive ;

    bool testAlive() {
        if (alive)
            return true;
        std::cout << "fail: pet esta morto" << '\n';
        return false;
    }

    void setHungry(int value) {
        if (value <= 0) {
            hungry = 0;
            std::cout << "fail: pet morreu de fome" << '\n';
            alive = false;
            return;
        } else if (value > hungryMax) {
            hungry = hungryMax;
            return;
        } else {
            hungry = value;
            return;
        }
    }
    void setEnergy(int value) { //todo
        if(value <= 0) {
            energy = 0;
            std::cout << "fail: pet morreu de fraqueza" << '\n';
            alive = false;
            return;
        }else if(value > energyMax) {
            energy = energyMax;
            return;
        }else {
            energy = value;
            return;
        }

    }

    void setClean(int value) { //todo
    if(value <= 0) {
        clean = 0;
        std::cout << "fail: pet morreu de sujeira" << '\n';
        alive = false;
        return;
    }else if(value > cleanMax) {
            clean = cleanMax;
            return;
    }else {
        clean = value;
        return;
        }
    }


public:
    Pet(int energy = 0, int hungry = 0, int clean = 0){
    
        this->clean= clean;
        this->hungry = hungry;
        this->energy = energy;
    

        energyMax = this->energy;
        hungryMax = this->hungry;
        cleanMax = this->clean;
    
        
        diamonds = 0;
        age = 0;
        alive = true;
        
    
}

    void play() {
        if (!testAlive())
            return;
        setEnergy(getEnergy() - 2);
        setHungry(getHungry() - 1);
        setClean(getClean() - 3);
        diamonds += 1;
        age += 1;
    }

// >>>>> case tomar banho <<<<<
//  O comando "$clean" alteram em -3 energia, -1 na saciedade, MAX na limpeza, +0 diamantes, +2 na idade.
    void shower() { //todo
        if(!testAlive()) 
        return;

        setEnergy(getEnergy() -3);
        setHungry(getHungry() -1);
        setClean(getCleanMax() );
        diamonds += 0;
        age += 2;


    }

// >>>>> case comer <<<<< 
// O Comando "$eat" altera em -1 a energia, +4 a saciedade, -2 a limpeza, +0 diamantes,  +1 a idade

    void eat() { //todo
    if(!testAlive()) 
        return;

        setEnergy(getEnergy() - 1);
        setHungry(getHungry() + 4);
        setClean(getClean() - 2);
        diamonds += 0;
        age += 1;
    };

// >>>>> case dormir <<<<<
// > O Comando "$sleep" aumenta energia até o máximo e idade aumenta do número de turnos que o pet dormiu.
// > Também perde 1 de saciedade.
// >>>>> case dormir sem sono <<<<<
//  Para dormir, precisa ter perdido pelo menos 5 unidades de energia

    void sleep() { //todo
    if(testAlive()){
        if (this->getEnergy() + 5 <= this->getEnergyMax()) {
        
        age += this->getEnergyMax() - this->getEnergy();
         
        setEnergy(getEnergyMax());
        setHungry(getHungry() - 1);
        return;
        
        } else {
            std::cout << "fail: nao esta com sono\n";
            return;
            }
        }else{
            return;
        }
       
    }


    int getClean() {
        return clean;
    }
    int getHungry() {
        return hungry;
    }
    int getEnergy() {
        return energy;
    }
    int getEnergyMax() {
        return energyMax;
    }
    int getCleanMax() {
        return cleanMax;
    }
    int getHungryMax() {
        return hungryMax;
    }

    std::string toString() {
        std::stringstream ss;
        ss <<  "E:" << energy << "/" << energyMax << ", "
           <<  "S:" << hungry << "/" << hungryMax << ", "
           <<  "L:" << clean << "/" << cleanMax << ", "
           <<  "D:" << diamonds << ", " << "I:"  << age;
        return ss.str();
    }

};


int main() {
    aux::Chain chain;
    aux::Param ui;
    Pet pet;
    auto toint = aux::to<int>;
    chain["show"] = [&]() { std::cout << pet.toString() << '\n'; };
    chain["init"] = [&]() { pet = Pet(toint(ui[1]), toint(ui[2]), toint(ui[3])); };
    chain["play"] = [&]() { pet.play(); };
    chain["eat"]  = [&]() { pet.eat(); };
    chain["clean"] =[&]() { pet.shower(); };
    chain["sleep"] =[&]() { pet.sleep(); };
    
    aux::execute(chain, ui);
};