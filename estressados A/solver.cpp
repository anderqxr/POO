#include <iostream>
#include <vector>
#include <aux.hpp>  // https://raw.githubusercontent.com/senapk/cppaux/master/aux.hpp
using namespace aux;

bool in(std::vector<int> vet, int x) {
    for(auto elem:vet)
        if(elem == x)
            return true;
    return false;
}

int index_of(std::vector<int> vet, int x) {
    int size = vet.size();
    int i = 0;
    for(i ; i < size; i++)
        if(vet[i] == x)                  
            return i;             
    return -1;   
}

int find_if(const std::vector<int>& vet) {
    int size = vet.size();
    for(int i = 0; i < size; i++)
        if(vet[i] > 0)                
            return i;              
    return -1; 
}

int min_element(const std::vector<int>& vet) {
    if(vet.empty()){
        return -1;
    }
    int menor_pos = 0;
    for(int i = 0; i < (int) vet.size(); i++)
        if(vet[i] < vet[menor_pos])
            menor_pos = i;
            return menor_pos;
    return -1;
}

int find_min_if(const std::vector<int>& vet) {
    int posMan = find_if(vet);
    
    for(int i = 0; i < (int) vet.size(); i++){
        if(vet[i] > 0 && vet[i] < vet[posMan]) {
            posMan = i;
        }
            
    }
    return posMan;
}


/*
using namespace aux;

int main(){
    Chain chain;
    Param ui;

    auto bool2str = LAMBDA(x, x ? "true" : "false"); //converte de bool para string true or false
    auto INT  = LAMBDA(x, x | aux::STR2<int>());                            //converte de string para int
    auto VET  = LAMBDA(x, x | COPY(1, -1) | SPLIT(',') | MAP(STR2<int>())); //converte de string para vetor de int

    chain["in"]           = [&] {          in(VET(ui.at(1)), INT(ui.at(2))) | PIPE(bool2str) | PRINT(); };
    chain["index_of"]     = [&] {    index_of(VET(ui.at(1)), INT(ui.at(2))) | PRINT(); };
    chain["find_if"]      = [&] {     find_if(VET(ui.at(1))               ) | PRINT(); };
    chain["min_element"]  = [&] { min_element(VET(ui.at(1))               ) | PRINT(); };
    chain["find_min_if"]  = [&] { find_min_if(VET(ui.at(1))               ) | PRINT(); };

    execute(chain, ui);
}
*/