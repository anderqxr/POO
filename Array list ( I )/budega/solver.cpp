#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include <aux.hpp>


class Pessoa {
    std::string nome;
public:
    Pessoa(std::string nome) { //todo 
        this->nome = nome;
    }
    std::string getNome() const {
        return nome;
    }
    std::string str() const {
        return nome; // todo
    }
};
std::ostream& operator<<(std::ostream& os, const Pessoa& p) {
    return (os << p.str());
}

class Mercantil {
    std::vector<std::shared_ptr<Pessoa>> caixas; //caixas do supermercado
    std::list  <std::shared_ptr<Pessoa>> esperando; //lista de clientes esperando

    bool validarIndice(int indice) {
        if(indice < 0 || indice >= (int) this->caixas.size() ) {
            return false;
        }
        return true;
    }

public:
    Mercantil(int qtd_caixas): caixas(qtd_caixas, nullptr) { //todo
    }
    
    void chegar(const std::shared_ptr<Pessoa>& person) {
        esperando.push_back(person);        
    }

    bool chamarNoCaixa(int indice) {
        if(indice < 0 || indice >= (int) this->caixas.size() ) {
            std::cout << "find: caixa inexistente\n";
            return false;
        }if(this->esperando.size() == 0) {
            std::cout << "fail: sem clientes\n";
            return false;
        }if(caixas[indice] != nullptr) {
            std::cout << "fail: caixa ocupado\n";
            return false;
        }
        this->caixas[indice] = this->esperando.front();
        this->esperando.pop_front();
        return true;

    }
    
    std::shared_ptr<Pessoa> finalizar(int indice) {
        if(indice < 0 || indice >= (int) this->caixas.size() ) {
            std::cout << "fail: caixa inexistente\n";
            return nullptr;
        }
        if(this->caixas[indice] == nullptr) {
            std::cout << "fail: caixa vazio\n";
            return nullptr;
        }
        auto aux = this->caixas[indice];
        this->caixas[indice] = nullptr;
        return aux;
    
    }

    std::string str() const {
        int i = 0;
        auto fn = [&i](auto p) {
            std::stringstream ss; 
            ss << " " << i++ << ":"<< std::setw(5) << (p == nullptr ? "-----" : p->getNome()) << " ";
            return ss.str();
        };
        std::stringstream os;
        os  << "Caixas: |" << (caixas | aux::MAP(fn) | aux::JOIN("|")) << "|\n"    
            << "Espera: " << (esperando | aux::MAP(FX(*x)) | aux::FMT());
        return os.str();
    }
};

std::ostream& operator<<(std::ostream& os, const Mercantil& b) {
    return (os << b.str());
}

int main() {
    aux::Chain chain;
    aux::Param par;
    
    Mercantil bank(0);

    chain["init"]   = [&]() {   bank = Mercantil(aux::to<int>(par[1])); };
    chain["call"]   = [&]() { bank.chamarNoCaixa(aux::to<int>(par[1])); };
    chain["finish"] = [&]() {     bank.finalizar(aux::to<int>(par[1])); };
    chain["arrive"] = [&]() { bank.chegar(std::make_shared<Pessoa>(par[1])); };
    chain["show"]   = [&]() { aux::show << bank; };

    aux::execute(chain, par);    
}


