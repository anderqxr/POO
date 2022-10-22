#include <iostream>
#include <sstream>
#include <memory>  //sharedptr
#include <iomanip> //setprecision
#include <utility> //exchange
#include <aux.hpp>


class Lead {
    float thickness;  // espessura
    std::string hardness; // dureza
    int size; // tamanho

public:
    Lead(float thickness, std::string hardness, int size) {
        this->hardness = hardness;
        this->thickness = thickness;
        this->size = size;
    
    
    }

    int usagePerSheet() const {
        if(hardness ==  "HB") {
            return 1;
        }
        if(hardness ==  "2B") {
            return 2;
        }
        if(hardness ==  "4B") {
            return 4;
        }
        if(hardness ==  "6B") {
            return 6;
        }
        return 0;
    }

    float getThickness() const {
        return thickness;
    }

    std::string getHardness() const {
        return hardness;
    }

    int getSize() const {
        return size;
    }

    void setSize(int size) {
        this->size = size;
        return;
    }

    std::string str() const {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) 
        << thickness << ":" << hardness << ":" << size;
        return ss.str();
    }
};

std::ostream& operator<<(std::ostream& ss, Lead gr) {
    return ss << gr.str();
}

struct Pencil {
    float thickness {0.f};
    std::shared_ptr<Lead> tip {nullptr};

    Pencil(float thickness = 0.0) { //todo thickness{thickness} {
        this->thickness = thickness;
        tip = nullptr;
        
    }

    bool hasGrafite() {
        if(tip == nullptr) {
            return false;
        }
        return true; 
    }

    bool insert(std::shared_ptr<Lead> grafite) {

        if(hasGrafite()) {
            std::cout << "fail: ja existe grafite\n";
            return false;
        }
        if(grafite->getThickness() == thickness) {
            tip = grafite;
            return true;
        }
        if(grafite->getThickness() != thickness){
            std::cout << "fail: calibre incompativel\n";
            return false;
        }
        return false;
    }

    std::shared_ptr<Lead> remove() {

        if(hasGrafite()) {
            tip = nullptr; 
        }
        else {
            std::cout << "Fail: nao tem grafite\n";
        }
        std::shared_ptr<Lead> aux = this->tip;
        this->tip = nullptr;
        return aux; 
    }

    void writePage() {
        if(!hasGrafite()) {
            std::cout << "fail: nao existe grafite\n";
            return;
        }if(tip->getSize() <= 10) {
            std::cout <<"fail: tamanho insuficiente\n";
            return;
        }if(hasGrafite() && (tip->getSize() - tip->usagePerSheet() ) < 10) {
            tip->setSize(10);
            std::cout << "fail: folha incompleta\n";
            return;
        }
        tip->setSize(tip->getSize() - tip->usagePerSheet());
        return;   
    }

    std::string str() {
        std::stringstream ss;
        ss << "calibre: " << thickness << ", grafite: ";
        if (tip != nullptr)
            ss << "[" << *tip << "]";
        else
            ss << "null";
        return ss.str();
    }
};

std::ostream& operator<<(std::ostream& os, Pencil l) {
    return os << l.str();
}

int main() {
    aux::Chain chain;
    aux::Param ui;

    Pencil pencil;

    auto tofloat = aux::to<float>;
    auto toint   = aux::to<int>;

    chain["show"]   = [&]() { std::cout << pencil << std::endl; };
    chain["init"]   = [&]() { pencil = Pencil(tofloat(ui[1])); };
    chain["insert"] = [&]() { pencil.insert(std::make_shared<Lead>(tofloat(ui[1]), ui[2], toint(ui[3]))); };
    chain["remove"] = [&]() { pencil.remove(); };
    chain["write"]  = [&]() { pencil.writePage(); };

    aux::execute(chain, ui);
}


