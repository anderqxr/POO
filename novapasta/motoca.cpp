#include <iostream>
#include <sstream>
#include <memory>
//#include <aux.hpp>

class Person {
    std::string name; //atributo
    int age;
public:
    Person(std::string name = "", int age = 0) {
        this->name = nullptr;
        this->age = age;
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
    int time {0};
    int power {1};

public:
    Motorcycle(int power = 1) { //todo power {power} {
        this->power = power;
    }


    bool insertPerson(std::shared_ptr<Person> p) {
        
    }

    std::string honk() {
        return {}; // todo
    }

    std::shared_ptr<Person> removePerson() {
        return {}; // todo
    }

    void buyTime(int time) {
    }

    void drive(int time) {
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
    Motorcycle motoca;

   
    
}
