#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include <utility>
#include <aux.hpp>

class Pass{
    std::string id;
    int idade;
public:
    Pass(std::string id = "", int idade = 0  ){
        this->id = id;
        this->idade = idade;
    }
     void setId(std::string id) {
        this->id = id;
    }

    void setIdade(int idade) {
        this->idade = idade;
    }
    bool isPref() {
        return idade >= 65 ? true : false;
    }
    std::string getId() {
        return id;
    }
    int getIdade() {
        return idade;
    }
    std::string str() {
        std::stringstream ss;
        ss << id << ":" << idade;
        return ss.str();
    }
};

std::ostream& operator<<(std::ostream& os, Pass p) {
    return os << p.str();
}
class Topic{
    std::vector<std::shared_ptr<Pass>> preferenciais;
    std::vector<std::shared_ptr<Pass>> normais;
    int qtdPref;

    static int procurarPorNome(std::string id, std::vector<std::shared_ptr<Pass>> &cadeiras) {
        for (int i = 0; i < (int) cadeiras.size(); i++){
            if (cadeiras[i] != nullptr && cadeiras[i]->getId() == id )
            return i;
        }
        return -1;
    }
    static int procurarVaga(std::vector<std::shared_ptr<Pass>> &cadeiras) {
        for (int i = 0; i < (int) cadeiras.size(); i++){
            if (cadeiras[i] == nullptr) {
                return i;
            }
        }

        return -1;
    }
    static int sentar(std::shared_ptr<Pass> pass, std::vector<std::shared_ptr<Pass>> &cadeiras) {

        auto cadeiradisponivel = procurarVaga(cadeiras);
        cadeiras[cadeiradisponivel] = std::make_shared<Pass>(pass->getId(), pass->getIdade());
        return cadeiradisponivel;
    }
    static std::shared_ptr<Pass> descer(std::string id, std::vector<std::shared_ptr<Pass>> &cadeiras) {

        auto descerPassageiro = procurarPorNome(id, cadeiras);
        auto remover = cadeiras[descerPassageiro];
        cadeiras[descerPassageiro] = nullptr;

        return remover;

    }

public:

    Topic(int lotacao = 0, int qtdPref = 0): preferenciais(qtdPref), normais((lotacao - qtdPref), nullptr){
    }

    bool subir(std::shared_ptr<Pass> pass) {
        if (procurarPorNome(pass->getId(), preferenciais ) != -1 || procurarPorNome(pass->getId(), normais ) != -1) {
        std::cout << "fail: " << pass->getId() << " ja esta na topic\n";
        return false;
        }
        if (pass->isPref() == false) {
            for (int i = 0; i < (int)normais.size(); i++) {
                if (normais[i] == nullptr){
                    sentar(pass, normais);
                    return true;
                }
            }
            for (int i = 0; i < (int)preferenciais.size(); i++) {
                if (preferenciais[i] == nullptr) {
                    sentar(pass, preferenciais);
                    return true;
                }
            }
            
        }
        else{
            for (int i = 0; i < (int) preferenciais.size(); i++) {
            if (preferenciais[i] == nullptr){
                sentar(pass, preferenciais);
                return true;
                }
            }
            for (int i = 0; i < (int)normais.size(); i++) {
                if (normais[i] == nullptr) {
                    sentar(pass, normais);
                    return true;
                }
            }
        }

        std::cout << "fail: topic lotada\n";
        return false;
    }



    std::shared_ptr<Pass> descer(std::string id) {
            if (procurarPorNome(id, preferenciais) != -1) {
                return descer(id, preferenciais);
            }
            if (procurarPorNome(id, normais) != -1) {
                return descer(id, normais);
            }
            std::cout << "fail: " << id << " nao esta na topic\n";
            return {};
    };

    std::string str() const {
    std::stringstream ss;

        ss << "[";
        for (int i = 0; i < (int)preferenciais.size(); i++) {
            int tamanhoPref = preferenciais.size() - 1;

            if (preferenciais[i] == nullptr)
                ss << "@ ";
            else if (preferenciais[i] != nullptr && i == tamanhoPref)
                ss << "@" << preferenciais[i]->str() << " ";
            else
                ss << "@" << preferenciais[i]->str() << " ";
        }
        for (int i = 0; i < (int)normais.size(); i++) {
            int tamanhoNormais = normais.size() - 1;

            if (normais[i] == nullptr && i == tamanhoNormais)
                ss << "=";
            else if (normais[i] == nullptr)
                ss << "= ";
            else if (normais[i] != nullptr && i == tamanhoNormais)
                ss << "=" << normais[i]->str();
            else
                ss << "=" << normais[i]->str() << " ";
        }
        ss << "]";
        return ss.str();
    };
};


int main(){
    aux::Chain chain;
    aux::Param param;
    Topic topic;

    chain["init"] = [&](){
        topic = Topic(aux::to<int>(param[1]), aux::to<int>(param[2]));
    };
    chain["show"] = [&](){
        std::cout << topic.str() << std::endl;
    };
    chain["in"] = [&](){
        topic.subir(std::make_shared<Pass>(param[1], aux::to<int>(param[2])));
    };
    chain["out"] = [&](){
        topic.descer(param[1]);
    };
    aux::execute(chain, param);
}