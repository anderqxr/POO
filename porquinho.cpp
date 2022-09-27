#include <iostream>
#include <vector>
#include <utility>
#include <aux.hpp>

enum Coin {M10, M25, M50, M100};
struct CoinDef {
    float value;
    int volume;
};

CoinDef getDef(Coin coin) {
    switch (coin) {
        case M10: return {0.1, 1};
        case M25: return {0.25, 2};
        case M50: return {0.50, 3};
        case M100: return {1, 4};
    }
    return {0, 0};
}


class Item {
    std::string label;
    int volume;
public:
    Item(std::string label, int volume) { //todo
    this->setLabel(label);
    this->setVolume(volume);
    
    
    }
    int getVolume() const {
        //return {}; // todo
        return this->volume;
    }
    std::string getLabel() const {
       // return {}; // todo
        return this->label;

    }
    void setVolume(int volume) {
        this->volume = volume;
        return;
    }
    void setLabel(std::string label) {
        this->label = label;
        return;
    }
    std::string str() const {
       // return {}; // todo
        
    }
};

std::ostream& operator<<(std::ostream& os, const Item& item) {
    return os << item.str();
}

class Pig {
    std::vector<std::string> itens;
    double value {0};
    int volume {0};
    int volumeMax {0};
    bool broken {false};

public:
    Pig(int volumeMax = 0) { 
        
    this->value = value;
    this->volume = volume;
    this->volumeMax = volumeMax;
    this->broken = false;

    }
    
    bool addCoin(Coin coin) { 
        
        if(broken == false){ 
          if (this->volume + volume < volumeMax ){
            this->value += getDef(coin).value;
            this->volume += getDef(coin).volume;
          }else{
            std::cout << "fail: the pig is full\n";
            return true;
            }
        }else{
            std::cout << "fail: the pig is broken\n";
            return false;
        }
        
    }

    bool addItem(Item item) {
             
      if(broken == false) {
            if(this->volume + item.getVolume() > volumeMax){
                std::cout << "fail: the pig is full\n";
     
            }else { 
                this->volume += item.getVolume();
                itens.push_back(item.getLabel());
                return true;
                }
          
        }else {
            std::cout << "fail: the pig is broken\n";
            return false;
        }
    }

    bool breakPig() {
        
        this->volume = 0;
        return this->broken = true;
    }

    double getCoins() {
        double recivedValue = 0.0;
        if(broken == false) {
            std::cout << "fail: you must break the pig first\n";
            return recivedValue;
        }else{
            recivedValue = value;
            this->value = 0;
            this->volume = 0;
            return recivedValue;
        }
        
    }

    std::string getItens() {
        if(broken == false) {
            
            std::cout << "fail: you must break the pig first\n";
            return "[]";
            
        }else{
            
            std::stringstream ss;
            ss << "[";
            for (int i = 0; i < (int) itens.size(); i++) {
                ss << (i == 0 ? "":", ") << itens[i];
            }
            ss << "]";
            itens.erase(itens.begin(), itens.end());
            
            return ss.str();
            
        }
        
    }

    std::string str() const {
        std::stringstream ss;
        ss << aux::fmt(this->itens) << " : "
           << aux::fmt(value) << "$ : "
           << volume <<  "/" << volumeMax << " : " 
           <<  (broken ? "broken" : "unbroken");
        return ss.str();
    }
};

std::ostream& operator<<(std::ostream& os, const Pig& pig) {
    return os << pig.str();
}

int main() {
    aux::Chain chain;
    aux::Param par;

    Pig pig;
    
    auto toint = aux::to<int>;

    chain["addCoin"] = [&]() { 
        if      (par[1] == "10") pig.addCoin(M10);
        else if (par[1] == "25") pig.addCoin(M25);
        else if (par[1] == "50") pig.addCoin(M50);
        else if (par[1] == "100") pig.addCoin(M100);
    };
    chain["init"]     = [&]() { pig = Pig(toint(par[1])); };
    chain["addItem"]  = [&]() { pig.addItem(Item(par[1], toint(par[2]))); };
    chain["break"]    = [&]() { pig.breakPig(); };
    chain["getCoins"] = [&]() { aux::show << pig.getCoins(); };
    chain["getItens"] = [&]() { aux::show << pig.getItens(); };
    chain["show"]     = [&]() { aux::show << pig.str(); };

    aux::execute(chain, par);
}


