#include <iostream>
#include <vector>



int count(std::vector<int> vet, int x) {
     int cont = 0;
    for(auto elem:vet)
        if(elem == x)
            cont++;
    return cont;
}

int sum(std::vector<int> vet) {
    double soma = 0;
    for(int i = 0; i < (int)vet.size(); i++){
        soma = soma + vet[i];
    }
}

double average(const std::vector<int>& vet) {
    double soma = 0;
    for(int i = 0; i < (int)vet.size(); i++){
        soma = soma + abs(vet[i]);
    } 
    return soma/(int) vet.size();
    
}

std::string more_men(const std::vector<int>& vet) {
    int cont_h = 0;
    int cont_m = 0;
    for(auto elem:vet){
        if(elem > 0)
          cont_h++;
          
        if(elem < 0)
          cont_m++;
    }        
    if (cont_h < cont_m)
      return "women";
    if (cont_h > cont_m)
      return "men";
    else
      return "draw";
}

std::string half_compare(const std::vector<int>& vet) {
   double mediaP = 0, mediaS = 0;
    double somaP = 0, somaS = 0;
    int metade_size = vet.size()/2;
    int n_metade_size = metade_size;
    
    if((int) vet.size() %2 != 0 && metade_size %2 != 0)
      n_metade_size = n_metade_size + 1;
      
    for(int i = 0; i < metade_size; i++)
         somaP = somaP + abs(vet[i]);
         mediaP = somaP/ metade_size;
        
      
    for(int i  = n_metade_size; i < (int)vet.size(); i++)
         somaS = somaS + abs(vet[i]);
         mediaS = somaS/ metade_size;
         
    if(mediaP > mediaS)
      return "first";
    if(mediaP<mediaS)
      return "second";
    else
      return "draw";
  
}

std::string sex_battle(const std::vector<int>& vet) {
     int stress_h = 0;
    int stress_m = 0;

    for(int i = 0; i < (int)vet.size(); i++){
        if(vet[i] > 0 )
            stress_h = abs(stress_h) + vet[i];
        if(vet[i] < 0 )
            stress_m = stress_m + vet[i];
    }

    if ((stress_m *-1)  > stress_h){
        return "women";
    }if (stress_h > (stress_m *-1)){
      return "men";
      
    }else{
      return "draw";
    }
}
/*
#include <aux.hpp>
using namespace aux;

//loop principal
int main(){
    Chain chain;
    Param ui;

    auto float2str= LAMBDA(x, x | aux::STR("%.2f"));                            //converte de float para string com 2 casas
    auto INT      = LAMBDA(x, x | aux::STR2<int>());                            //converte de string para int
    auto VET      = LAMBDA(x, x | COPY(1, -1) | SPLIT(',') | MAP(STR2<int>())); //converte de string para vetor de int

    chain["count"]        = [&] {        count(VET(ui[1]), INT(ui[2])) | PRINT(); };
    chain["sum"]          = [&] {          sum(VET(ui[1])            ) | PRINT(); };
    chain["average"]      = [&] {      average(VET(ui[1])            ) | PIPE(float2str) | PRINT(); };
    chain["more_men"]     = [&] {     more_men(VET(ui[1])            ) | PRINT(); };
    chain["half_compare"] = [&] { half_compare(VET(ui[1])            ) | PRINT(); };
    chain["sex_battle"]   = [&] {   sex_battle(VET(ui[1])            ) | PRINT(); };

    execute(chain, ui);
}
*/