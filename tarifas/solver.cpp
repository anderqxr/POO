#include<iostream>
#include<vector>
#include<sstream>
#include <aux.hpp>

enum LabelOp {
    EXTRACT,
    WITHDRAW,
    DEPOSIT,
    FEE,
    REVERSE
};

class Label {
    std::string name = "erro";

public:
    Label(LabelOp op = WITHDRAW){
      if (op == EXTRACT) {
        name = "extract";
      }else if (op == WITHDRAW) {
        name = "withdraw"; 
      }else if ( op == DEPOSIT) {
        name = "deposit";
      }else if (op == FEE) {
        name = "fee";
      }else if (op == REVERSE) {
        name = "reverse";
      }
        
    }
    std::string getName() {
        return this->name;
    }
};


class Operation{
    Label label;
    int index;
    int value;
    int balance;
public:
    Operation(int index , Label label , int value, int balance) {
        this->index = index;
        this->label = label;
        this->value = value;
        this->balance = balance;
    }

    
    int getIndex() {
        return index;
    }
    int getValue() {
        return value;
    }
    int getBalance(){
        return balance;
    }
    Label getLabel() {
        return label;
    }
    std::string str() {
        std::stringstream ss;
        ss << index << ":  " << Label(label).getName() << ":  " <<
        balance << ":  " << value;
        return ss.str();
    }
};



class BalanceMeneger {
    int balance{0};
    int nextId{0};
    std::vector<Operation>extract;

public:
    BalanceMeneger(){}

    void addOperation(Label label, int value) {
        nextId +=1;
        extract.push_back( Operation(nextId, label, (balance += value),  value));
        
    }
    
    int getBalance() {
        return balance;
    }
    std::vector<Operation> getExtract() {
        return this->extract;
    }

    std::string fmt() {
        std::stringstream ss;
        for (int i = 0; i < (int) extract.size(); i++) {
            ss << (i == 0 ? "0:  opening:    0:    0 \n" : ":" || i != 0 ? "" : ":")
             << extract[i].str() << '\n';
        }
        return ss.str();
        
    }
};


class Account {
    BalanceMeneger manager;
    int id;
public:
    Account(int id) {
        this->id = id;
    }
    bool deposit(int value) {
        if(value < 0) {
            std::cout << "fail: invalid value\n";
            return false;
        }
        manager.addOperation(LabelOp::DEPOSIT, value);
            return true;   
    }

    bool fee(int value) {
        manager.addOperation(LabelOp::FEE, -value);
        return true;

    }
    // bool reverse(int index) {
    //     for(int i = 0; i < (int) manager..size(); i++) {
    //         if(index != i) {
    //             std::cout << "fail: index " <<  index << "invalid\n";
    //             return false;
    //         }

    //     }

    // }
    bool withdraw(int value) {
        if(manager.getBalance() < value) {
            std::cout << "fail: insuficient balance\n";
            return false;
        }
        manager.addOperation(LabelOp::WITHDRAW, -value);
        return true;


    }
    std::string str() {
        std::stringstream ss;
        ss << "account:" << id << "  balance:" << manager.getBalance() << '\n';
        return ss.str();
        
    }
    std::stringstream os;
        os  << "acount: " << (id | aux::MAP(fn) | aux::JOIN("|")) << "|\n"    
            << "balance: " << (esperando | aux::MAP(FX(*x)) | aux::FMT());
        return os.str();
    
};
int main() {
    aux::Chain chain;
    aux::Param par;
    
    Account conta(0);

    chain["init"]    =  [&]() {   conta = Account(aux::to<int>(par[1])); };
    chain["deposit"] =  [&]() { conta.deposit(aux::to<int>(par[1])); };
    chain["fee"] =      [&]() {  conta.fee(aux::to<int>(par[1])); };
    chain["withdraw"] = [&]() { conta.withdraw(aux::to<int>(par[1])); };
    chain["show"]   =   [&]() { std::cout << conta.str() << '\n';};

    aux::execute(chain, par);    
}





/*
int main () {std::make_shared<Pessoa>(par[1])
    Operation op(0, WITHDRAW, 0, 0);
    BalanceMeneger bm;
std::cout << ">>> case iniciar\n";
    Account conta(100);
    std::cout << conta.str() << '\n';

std::cout << ">>> case depositar\n"; 
    conta.deposit(100);
    conta.deposit(-10);
    std::cout << conta.str() << '\n';

std::cout << ">>> case debito\n";
    conta.withdraw(20);
    conta.fee(10);
    std::cout << conta.str() << '\n';
    conta.withdraw(150);
    conta.withdraw(30);
    conta.fee(5);
    conta.deposit(5);
    conta.fee(1);
    std::cout << conta.str() << '\n';

    bm.addOperation(DEPOSIT, 100);
std::cout << "#__case extrato\n";
  //  std::cout << bm.fmt() << '\n';
    bm.getExtract();

}
*/