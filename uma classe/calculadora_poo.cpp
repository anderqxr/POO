#include <iostream>
#include <sstream>
#include <iomanip>
struct Calculator {
    int batteryMax;
    int battery{0};
    float display{0};
    
    //Inicia os atributos, battery e display começam com o zero.
    Calculator(int batteryMax) { // todo
        this->batteryMax = batteryMax;
        this->battery = battery;
        this->display = display;
    }

    //Aumenta a bateria, porém não além do máximo.
    void chargeBattery(int value) { // todo 
        if(battery + value > this->batteryMax) {
            this->battery = this->batteryMax;
            return;
        }else{
            this->battery += value;
            return;

        }
    }

    //Se conseguir gastar bateria, armazene a soma no atributo display.
    void sum(int a, int b) { // todo
        if(this->battery == 0){
            this->battery = 0;
            std::cout << "fail: bateria insuficiente\n";
            return;
        }else{
            this->display = a + b;
            this->battery--;
        return;
        }
    }

    //Se conseguir gastar bateria e não for divisão por 0.
    void division(float num, float den) { // todo
        
        if(battery == 0){
            std::cout << "fail: bateria insuficiente\n";
            return;
        }if(den == 0){
            std::cout << "fail: divisao por zero\n"; 
            this->battery--;
            return;
        }else{
            this->display = num/den;
            this->battery--;
            return;
            }
        
    }

    //Retorna o conteúdo do display com duas casas decimais.
    std::string str() { 
        std::stringstream ss;
        ss << "display = " << std::fixed << std::setprecision(2) << this->display;
        ss << ", battery = " << this->battery;
        return ss.str();
    }
};
std::ostream& operator<<(std::ostream& os, Calculator c) {
    return (os << c.str());
}


            // TESTES PARA O CODIGO //
// <<<<<<

int main() {
    Calculator calc(3);
    
    calc.chargeBattery(3);
    calc.division(6, 3);
    
    calc.division(7, 0);
    std::cout << calc.str() << '\n';
    calc.division(7, 2);
    calc.division(10, 2);
    //calc.chargeBattery(1);
     std::cout << calc.str() << '\n';
    // calc.sum(-4, -2);
    // std::cout << calc.str() << '\n';





}
// <<<<<<