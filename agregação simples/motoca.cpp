#include <iostream>
#include <sstream>
#include <memory>
#include <aux.hpp>

class Person {
    
public:
    std::string name; //atributo
    int age;
    Person(std::string name, int age): name(name), age(age) {
        
    }

    // Person(int age) { //todo Person("", age) {
    
    // }

    int getAge() {
        return age;    
    }
    
    std::string getName() {
        return name;
    }
    std::string str() {
        std::ostringstream oss;
        oss << name << ":" << age;
        return oss.str();
    }
};

std::ostream& operator<<(std::ostream& os, Person& p) {
    return os << p.str();
}

class Motorcycle {
    std::shared_ptr<Person> person {nullptr}; //agregação
    int age {0};
    int time {0};
    int power {1};
    

public:
    Motorcycle(int power = 1) { //todo power {power} {
    this->power = power;
    person = nullptr;
    age = 0;
    }


    bool insertPerson(std::shared_ptr<Person> p) {
        if(person == nullptr) {
            this->person = p;
            return true;
        }
        std::cout << "fail: busy motorcycle\n";
        return false;
    }

    std::string honk() {
        return "P" + std::string(power, 'e') + "m";
    }

    std::shared_ptr<Person> removePerson() {
        if(person != nullptr) {
            auto aux = this->person;
            person = nullptr;
            return aux;
        }
        std::cout << "fail: empty motorcycle\n";
        return nullptr;
    }

    void buyTime(int time) {
         this->time += time;
    }
    
    

    void drive(int andar) {
        if(person.get()->getAge() < 10) {
            if(this->time == 0 ) {
                std::cout << "fail: buy time first\n";
                return;
            }if (andar > time) {
                std::cout << "fail: time finished after " << time << " minutes\n";
                time = 0;
                return;
            }if(person != nullptr) {
                this->time -= andar;
                return;
            }
            return;
        }if(person.get()->getAge() > 10) {
            std::cout << "fail: too old to drive\n";
            return;
        }
      
    }



    std::string str() const{
        std::ostringstream os;
        os << "power:" << power << ", time:" << time;
        os << ", person:(" << (person == nullptr ? "empty" : person->str()) << ")";
        return os.str();
    }
};

std::ostream& operator<<(std::ostream& os, const Motorcycle& m) {
    return os << m.str();
}


int main() {
    aux::Chain chain;
    aux::Param par;

    Motorcycle m(1);


    auto toint = aux::to<int>;

    chain["show"]  = [&]() { aux::show << m; };
    chain["leave"] = [&]() { 
        auto person = m.removePerson(); 
        if (person != nullptr) {
            aux::show << *person;
        }
    };
    chain["honk"]  = [&]() { aux::show << m.honk(); };
    chain["init"]  = [&]() { m = Motorcycle(toint(par[1]));};
    chain["enter"] = [&]() { m.insertPerson(std::make_shared<Person>(par[1], toint(par[2]))); };
    chain["buy"]   = [&]() { m.buyTime(toint(par[1])); };
    chain["drive"] = [&]() { m.drive  (toint(par[1])); };

    aux::execute(chain, par);
}
