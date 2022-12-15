#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include <sstream>
#include <aux.hpp>

struct Cliente{
    std::string id;
    std::string fone;

    Cliente(std::string id = "", std::string fone = "") {
        this->id = id;
        this->fone = fone;
    }

    std::string getFone() {
        return fone;
    }
    std::string getId() {
        return id;
    }
    void setId(std::string id) {
        this->id = id;
    }
    void setFone(std::string fone) {
        this->fone = fone;
    }
    std::string str() {
        std::stringstream ss;
        ss << this->id << ":" << this->fone;
        return ss.str();
    }
};

std::ostream& operator<<(std::ostream& os, Cliente c) {
    return os << c.str();
}

class Sala{
    std::vector<std::shared_ptr<Cliente>> cadeiras;
    int procurar(std::string nome) {
        for(auto i = 0; i < (int) cadeiras.size(); i++) {
            if (cadeiras[i] != nullptr && cadeiras[i]->getId() == nome ) {
                return i;
            }
        }
        return -1;
    }
    bool verificarIndice(int indice) {
        if(indice < 0 || indice > (int) this->cadeiras.size() - 1) {
            return false;
        }
        return true;
    }

public:
    Sala(int qtd = 0):cadeiras(qtd, nullptr){ }
    void reservar(std::string id, std::string fone, int ind) {   

        if (verificarIndice(ind) == false) {
            std::cout << "fail: cadeira nao existe\n";
            return;
        }    
        if (procurar(id) != -1) {
            std::cout << "fail: cliente ja esta no cinema\n";
            return;
        }
        if (cadeiras[ind] != nullptr ) {
            std::cout << "fail: cadeira ja esta ocupada\n";
            return;
        }
        if ( verificarIndice(ind) == true) {
            for (int i = 0; i < (int) cadeiras.size(); i++) {
                if (i == ind) {
                    cadeiras[i] = std::make_shared<Cliente>(id, fone);
                    return;
                }
            }
        }             
    }

    void cancelar(std::string id) {
        if (procurar(id) != -1) {
            cadeiras[(int)procurar(id)] = nullptr;  
            return;
        }
        if (procurar(id) == -1) {
            std::cout << "fail: cliente nao esta no cinema\n";
            return;
        } 
       
    }

    std::string str() {
        std::stringstream ss;
        ss << "[";
        for (auto i = 0; i < (int) cadeiras.size(); i++) {
            if (cadeiras[i] == nullptr) {
                ss << (i == 0   ? "-" : " -") ;

            }else 
                ss << (i == 0 ? "" : " ") <<  cadeiras[i]->str();
        }
        ss << "]";
        return ss.str();

    }
};
int main() {
    aux::Chain chain;
    aux::Param param;
    Sala sala;
    chain["init"]     = [&]() { sala = Sala(aux::to<int>(param[1])); };
    chain["reservar"] = [&]() { sala.reservar(param[1], param[2], aux::to<int>(param[3])); };
    chain["cancelar"] = [&]() { sala.cancelar(param[1]); };
    chain["show"]     = [&]() { std::cout << sala.str() << std::endl; };
    aux::execute(chain, param);
};
