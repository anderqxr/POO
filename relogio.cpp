#include <iostream>
#include <sstream>
#include <aux.hpp>

class Time {
private:
    int hour {0};
    int minute {0};
    int second {0};

public:
    Time (int hour, int minute, int second) {
        this->setHour(hour);
        this->setMinute(minute);
        this->setSecond(second);
    }

    void setHour (int hour) {
        if(hour >= 0 && hour <= 23){
            this->hour =  hour;
            return;
        }else {
            std::cout << "fail: hora invalida\n";
        }
    }
    
    void setMinute (int minute) {
        if(minute >=0 && minute <= 59) {
            this->minute = minute;
            return;
        }else {
        std::cout << "fail: minuto invalido\n";
        }
    }

    void setSecond (int second) {
        if(second >=0 && second <= 59) {
            this->second = second;
            return;
        }else {
            std::cout << "fail: segundo invalido\n";
        }
    }

    int getHour () {
        return hour; // todo

    }
    
    int getMinute () {
        return minute; // todo
    }
    
    int getSecond () {
        return second; // todo
    }
    
    void nextSecond() {
        if(getMinute() == 59 && getSecond() == 59) {
            setHour(getHour() + 1);
            setMinute(getMinute() == 0);
            setSecond(getSecond() == 0);
        }else if(getSecond() == 59 && getMinute() < 59) {
            setMinute(getMinute() + 1);
            setSecond(getSecond() == 0);
        }
    }

    std::string str() {
        std::stringstream ss;
        auto sw = std::setw(2);
        ss  << std::setfill('0') << sw << this->hour << ":" << sw << this->minute << ":" << sw << this->second;
        return ss.str();
    }
};

int main() {
    aux::Chain chain;
    aux::Param ui;
    Time time(0, 0, 0);

    chain["set"] = [&] () {
        time.setHour(aux::to<int>(ui[1]));
        time.setMinute(aux::to<int>(ui[2]));
        time.setSecond(aux::to<int>(ui[3]));
    };
    chain["show"] = [&] () { std::cout << time.str() << std::endl; };
    chain["next"] = [&] () { time.nextSecond(); };

    aux::execute(chain, ui);
};