#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include <utility>
#include <iterator>
#include <aux.hpp>

class Discp;

class Aluno{
    std::string id;
    std::map<std::string, Discp*> m_discp;
public:
    Aluno(std::string nome = ""):id(nome){}
    
    std::string getId();

    std::vector<Discp*> getDiscps();

    void addDisc(Discp * disciplina);

    void rmDiscp(std::string idDiscp) ;

    friend std::ostream& operator<<(std::ostream& os, Aluno& aluno);
    
};

// ok
class Discp{
    std::string id;
    std::map<std::string, Aluno*> m_aluno;
public:
    friend class Aluno;
    Discp(std::string nome = ""):id(nome) {}
    std::string getId() {
        return this->id;
    }
    void addAluno(Aluno * aluno) {
        auto key = m_aluno.find(aluno->getId());
        if (key != m_aluno.end()) {
            return;
        }
        this->m_aluno[aluno->getId()] = aluno;
        aluno->addDisc(this);
    }

    void rmAluno(std::string idAluno) {
        auto key = m_aluno.find(idAluno);
        if (key == m_aluno.end() ) {
            return;
        }
        Aluno * aluno = key->second;
        this->m_aluno.erase(key);
        aluno->rmDiscp(this->id);
        
    }
    std::vector<Aluno*> getAlunos() {
        std::vector<Aluno*> alunos;
        for (auto [key, value] : this->m_aluno){
            alunos.push_back(value);
        }
        return alunos;
        
    }
    friend std::ostream& operator<<(std::ostream& os, Discp& discp);
};

// metodo da classe Aluno "ok"
    std::string Aluno::getId() {
        return this->id;
    }
    void Aluno::addDisc(Discp * disciplina) {
        auto key = m_discp.find(disciplina->getId());
        if (key != m_discp.end()) {
            return;
        }
        this->m_discp[disciplina->getId()] = disciplina;
        disciplina->addAluno(this);
    }

    void Aluno::rmDiscp(std::string idDiscp) {
        auto key = m_discp.find(idDiscp);
        if (key == m_discp.end() ) {
            return;
        }
        Discp * disciplina = key->second;
        this->m_discp.erase(key);
        disciplina->rmAluno(this->id);
    }
    std::vector<Discp*> Aluno::getDiscps() {
        std::vector<Discp*> disciplinas;
        for (auto [key, value] : this->m_discp){
            disciplinas.push_back(value);
        }
        return disciplinas;
        
    }
    

class Sistema {
   std::map<std::string, Discp*> discp;
   std::map<std::string, Aluno*> aluno;
public:
    Sistema() {};

    void addAluno(std::string idAluno) {
        if (aluno.find(idAluno) != aluno.end()) {
            return;
        }
        this->aluno[idAluno] = new Aluno(idAluno);
        
    }
    void addDiscp(std::string idDiscp) {
        if (discp.find(idDiscp) != discp.end()) {
            return;
        }
         this->discp[idDiscp] = new Discp(idDiscp);
    }
    void matricular(std::string idAluno, std::string idDiscp) {
        auto key_A = aluno.find(idAluno);
        auto key_D = discp.find(idDiscp);
        if (key_A == aluno.end() || key_D == discp.end() ) {
            return;
        }
        Aluno* aluno = key_A->second;
        Discp* discp = key_D->second;
        aluno->addDisc(discp);
    }
    void desmatricular(std::string idAluno, std::string idDiscp) {
        auto key_A = aluno.find(idAluno);
        if (aluno.find(idAluno) != aluno.end() || discp.find(idDiscp) != discp.end() ) {
            Aluno* aluno = key_A->second;
            aluno->rmDiscp(idDiscp);
        }
        return;
    }
    void rmAluno(std::string idAluno) {
        auto key_A = aluno.find(idAluno);
        if (key_A == aluno.end()) {
            return;
            }
        Aluno* aluno = key_A->second;
        auto disciplinas = aluno->getDiscps();
        for (auto d : disciplinas) {
            d->rmAluno(idAluno);
            }
        this->aluno.erase(key_A);
    }
    void rmDiscp(std::string idDiscp) {
        auto key_D = discp.find(idDiscp);
        if (key_D == discp.end()) {
            return;
        }
        Discp* discp = key_D->second;
        auto alunos = discp->getAlunos();
        for (auto a : alunos) {
            a->rmDiscp(idDiscp);
        }
        this->discp.erase(key_D);  
    }
    friend std::ostream& operator<<(std::ostream& os, Sistema& sistema);
    
};
    std::ostream& operator<<(std::ostream& os, Discp& discp) {
        os << discp.getId() << " [";
        for (auto it = discp.m_aluno.begin(); it != discp.m_aluno.end(); it++) {
            os << (it == discp.m_aluno.begin() ? "" : ", " ) << it->second->getId();
        }
        os << "]";
        return os;
    }
    std::ostream& operator<<(std::ostream& os, Aluno& aluno) {
        os << aluno.getId() << " [";
        for (auto it = aluno.m_discp.begin(); it != aluno.m_discp.end(); it++) {
            os << (it == aluno.m_discp.begin() ? "" : ", " ) << it->second->getId();
        }
        os << "]";
        return os;
    }
    std::ostream& operator<<(std::ostream& os, Sistema& sistema) {
        os << "- alunos\n";
        for (auto& [key, value]: sistema.aluno)
            os << "    " << *value << "\n";
        os << "- discps\n";
        for (auto& [key, value]: sistema.discp)
            os << "    " << *value << "\n";

        return os;
    }

int main(){
    std::string line, cmd;
    Sistema sistema;
    while(true){
        try{
            getline(std::cin, line);
            std::cout << "$" << line << '\n';
            std::stringstream ss(line);
            //cria um vetor de strings a partir de line
            std::vector<std::string> ui(std::istream_iterator<std::string>{ss}, std::istream_iterator<std::string>());
            std::string cmd = ui[0];
            if(cmd == "end"){
                break;
            }else if(cmd == "nwalu"){
                for(size_t i = 1; i < ui.size(); i++)
                    sistema.addAluno(ui[i]);
            }else if(cmd == "nwdis"){
                for(size_t i = 1; i < ui.size(); i++)
                    sistema.addDiscp(ui[i]);
            }else if(cmd == "show"){
                std::cout << sistema;
            }else if(cmd == "tie"){
                for(size_t i = 2; i < ui.size(); i++)
                    sistema.matricular(ui[1], ui[i]);
            }else if(cmd == "untie"){
                for(size_t i = 2; i < ui.size(); i++)
                    sistema.desmatricular(ui[1], ui[i]);
            }else if(cmd == "rmalu"){
                sistema.rmAluno(ui[1]);
            }else{
                std::cout << "comando invalido " << "[" << cmd << "]\n";
            }
        }catch(std::string e){
            std::cout << e << '\n';
        }
    }
}
