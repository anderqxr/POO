Skip to content
Search or jump to…
Pull requests
Issues
Marketplace
Explore
 
@anderqxr 
bandeiramgn
/
POO_22.2
Public
Code
Issues
Pull requests
Actions
Projects
Security
Insights
POO_22.2/Agregação Simples/Grafite/main.cpp
@bandeiramgn
bandeiramgn completed graffiti activity
Latest commit 33b982e 4 hours ago
 History
 1 contributor
190 lines (163 sloc)  3.69 KB

#include <iostream>
#include <sstream>
#include <memory>  //sharedptr
#include <iomanip> //setprecision
#include <utility> //exchange
#include <aux.hpp>

class Lead
{
    float thickness;
    std::string hardness;
    int size;

public:
    Lead(float thickness, std::string hardness, int size) : thickness(thickness), hardness(hardness), size(size)
    {
    }

    int usagePerSheet() const
    {
        if (getHardness() == "HB") 
        {
            return 1;
        }
        else if (hardness == "2B")
        {
            return 2;
            
        }
        else if (hardness == "4B")
        {
            return 4;
        }
        else if (hardness == "6B")
        {
            return 6;
        }  
        return 0;
    }
        
    float getThickness() const
    {
        return thickness;
    }

    std::string getHardness() const
    {
        return hardness; 
    }

    int getSize() const
    {
        return size;
    }

    void setSize(int size)
    {
        this->size = size;
    }

    std::string str() const
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(1)
            << thickness << ":" << hardness << ":" << size;
        return ss.str();
    }
};

std::ostream &operator<<(std::ostream &ss, Lead gr)
{
    return ss << gr.str();
}

struct Pencil
{
    float thickness{0.f};
    std::shared_ptr<Lead> tip{nullptr};

    Pencil(float thickness = 0.0) : thickness(thickness), tip(nullptr)
    {

    }

    bool hasGrafite()
    {
        if (tip == nullptr)
            return false;

        return true; 
    }

    bool insert(std::shared_ptr<Lead> grafite)
    {
        if (hasGrafite()){
            std::cout << "fail: ja existe grafite\n";
            return false;
        }

        if (grafite->getThickness() == thickness) 
        {
            tip = grafite;
            return true;
        } 
        else 
        {
            std::cout << "fail: calibre incompativel\n";
            return false;
        }

        return false;
    }

    std::shared_ptr<Lead> remove() {
        if (hasGrafite()) 
        {
            tip = nullptr;        
        }
        else 
        {
            std::cout << "fail: não tem grafite\n";
        } 
        return {};
    }

    void writePage()
    {
        if (!hasGrafite())
        {
            std::cout << "fail: nao existe grafite\n";
        }
        else if (tip->getSize() <= 10) 
        {
            std::cout << "fail: tamanho insuficiente\n";
        } 
        else if (hasGrafite())
        {
            int useGrafite = tip->usagePerSheet();   
            if ((tip->getSize() - useGrafite) < 10) 
            { 
                tip->setSize(10);
                std::cout << "fail: folha incompleta\n";
            }
            else 
            {
                tip->setSize(tip->getSize() - useGrafite); 
            }
        }
    }

    std::string str()
    {
        std::stringstream ss;
        ss << "calibre: " << thickness << ", grafite: ";
        if (tip != nullptr)
            ss << "[" << *tip << "]";
        else
            ss << "null";
        return ss.str();
    }
};

std::ostream &operator<<(std::ostream &os, Pencil l)
{
    return os << l.str();
}

int main()
{
    aux::Chain chain;
    aux::Param ui;

    Pencil pencil;

    auto tofloat = aux::to<float>;
    auto toint = aux::to<int>;

    chain["show"] = [&]()
    { std::cout << pencil << std::endl; };
    chain["init"] = [&]()
    { pencil = Pencil(tofloat(ui[1])); };
    chain["insert"] = [&]()
    { pencil.insert(std::make_shared<Lead>(tofloat(ui[1]), ui[2], toint(ui[3]))); };
    chain["remove"] = [&]()
    { pencil.remove(); };
    chain["write"] = [&]()
    { pencil.writePage(); };

    aux::execute(chain, ui);
}
Footer
© 2022 GitHub, Inc.
Footer navigation
Terms
Privacy
Security
Status
Docs
Contact GitHub
Pricing
API
Training
Blog
About
POO_22.2/main.cpp at main · bandeiramgn/POO_22.2