#include <iostream>
#include <sstream>



class Car {
public:
    int pass{0};
    int passMax{2};
    int gas{0};
    int gasMax{100};
    int km;

    Car(){
        
    }
    
    Car(int passMax, int gasmax) {
        this->passMax = passMax;
        this->gasMax = gasMax;
    };



    void enter() { 
        if(pass == passMax){
            std::cout << "fail: limite de pessoas atingido\n";
        }else{
            pass +=1;
        }
    }

    void leave() { 
        if(pass == 0){
            std::cout << "fail: nao ha ninguem no carro\n";
        }else{
            pass -=1;
        }
    }

    void fuel(int gas) {
        this->gas = gas;
        if(gas >= gasMax){
            this->gas = gasMax;
        }else{
            gas+=1;
        }
    }

    void drive(int km) { 
        if(pass == 0) {
        std::cout << "fail: nao ha ninguem no carro\n";
        return;
      }else if(pass > 0 && gas >= km) {
        gas -= km;
        this->km += km;\
        return;
      }if(gas == 0 && km > gas) {
        std:: cout << "fail: tanque vazio\n";
        return;
      }else if(km > gas && pass > 0){
        std::cout << "fail: tanque vazio apos andar " << gas <<" km\n";
        this->km += gas;
        gas = 0;
        return;
      }


        
    }

    std::string str() { // todo 
       std::stringstream ss;
       ss << "pass: " << pass << ", gas: " << gas << ", km: " << km << "";
        return ss.str();
    }
};
int main() {
    Car car;
    

    car.fuel(60);
    std::cout << car.str() << '\n';
    car.drive(10);
    car.enter();
    car.drive(10);
    std::cout << car.str() << '\n';  
    car.drive(70);
    car.drive(10);
    std::cout << car.str() << '\n';


    
}