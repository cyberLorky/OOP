// Да се дефинира класа Employee со следните информации:

// name - име на вработениот(string)

// baseSalary - основна плата на вработениот (float)

// Потребно е да се имплементираат потребните конструктори, деструктор, методи get и set за класата Employee.

// Да се дефинира апстрактна класа Payable со следните чисто виртуелни функции:

// float getBaseSalary() - ја враќа основната плата пред каква било пресметка

// float getNetSalary() - ја враќа конечната (нето) плата по сите пресметки

// void printDetails() - печати детали за објектот

// Да се дефинираат две класи FullTimeEmployee и Contractor кои наследуваат од Employee и Payable.

// За класата FullTimeEmployee, се чуваат следните дополнителни атрибути:

// overtimeHours (float) - бројот на прекувремени работни часови 
// incomeTaxRate (float) - даночната стапка применета на платата, иста е за сите објекти од класата FullTimeEmployee, со иницијална вредност 0.10 
// Да се имплементираат методите getIncomeTaxRate() и setIncomeTaxRate() за incomeTaxRate. 

// Функцијата getNetSalary() ја враќа нето платата. Таа се пресметува така што се започнува од основната плата (baseSalary), а потоа се применуваат следните правила:

// Се додава надомест за прекувремена работа, пресметан како бројот на прекувремени часови (overtimeHours) помножен со 20.
// На крај, на добиената сума ѝ се одзема данокот на доход, кој изнесува incomeTaxRate (иницијално 10%) од таа сума; резултатот е нето платата.
// Функцијата getBaseSalary() ја враќа основната плата без никакви измени. 

// Функцијата printDetails() го печати секој FullTimeEmployee во следниот формат:

// [name] (FullTime) - Overtime: [overtimeHours]h - Base Salary: [baseSalary] - Net Salary: [netSalary]

// За класата Contractor, се чуваат следните дополнителни атрибути:

// completedProjects (int) - бројот на завршени проекти 
// serviceFeeRate (float) - стапката на провизија применета на платата, иста е за сите објекти од класата Contractor, со почетна вредност 0.15

// Да се имплементираат методите getServiceFeeRate() и setServiceFeeRate() за serviceFeeRate. 


// Функцијата getNetSalary() ја враќа нето платата. Таа се пресметува така што се започнува од основната плата (baseSalary), а потоа се применуваат следните правила:

// Се додава бонус за завршените проекти, пресметан како бројот на завршени проекти (completedProjects) помножен со 100.
// На крај, на добиената сума ѝ се одзема провизијата за услугата, која изнесува serviceFeeRate (иницијално 15%) од таа сума; резултатот е нето платата.

// Функцијата getBaseSalary() ја враќа основната плата без никакви измени. 


// Функцијата printDetails() го печати секој Contractor во следниот формат:

// [name] (Contractor) - Projects: [completedProjects] - Base Salary: [baseSalary] - Net Salary: [netSalary] 

// Да се дефинира класа за исклучок NoContractorException, а потоа да се дефинираат следните глобални функции:

// Contractor* findHighestPaidContractor(Payable** employees, int n) 

// Оваа функција прима низа од покажувачи од Payable објекти, ги филтрира само оние од тип Contractor и го враќа најплатениот меѓу нив (оној со највисока нето плата). Доколку повеќе Contractor објекти имаат иста нето плата, се враќа оној со повеќе завршени проекти (completedProjects). Доколку во низата нема ниту еден Contractor, функцијата треба да фрли исклучок од тип NoContractorException.

// void printHighestPaidContractor(Payable** employees, int n) 

// Оваа функција ја повикува findHighestPaidContractor. Доколку е вратен Contractor, ги печати неговите детали. Доколку се фати исклучок од тип NoContractorException, се печати пораката "There are no contractors".

// Искористете #include <iomanip> и cout << fixed << setprecision(2) за заокружување.


#include <iostream>
#include <cmath>
#include <cstring>
#include <cctype>
#include <iomanip>
using namespace std;

class Employee {
protected:
    string name;
    float baseSalary;

public:
    Employee(string name = "", float baseSalary = 0.0) {
        this->name = name;
        this->baseSalary = baseSalary;
    }

    string getName() {
        return name;
    }

    void setName(string name) {
        this->name = name;
    }

    float getBaseSalary() {
        return baseSalary;
    }

    void setBaseSalary(float baseSalary) {
        this->baseSalary = baseSalary;
    }


};

class Payable {
public:
    virtual float getBaseSalary() = 0;
    virtual float getNetSalary() = 0;
    virtual void printDetails() = 0;

};

class FullTimeEmployee : public Payable, public Employee {
private:
    float overtimeHours;
    static float incomeTaxRate;

public:
    FullTimeEmployee(string name = "", float baseSalary = 0.0, float overtimeHours = 0.0) : Employee(name, baseSalary) {
        this->overtimeHours = overtimeHours;
    }

    static float getIncomeTaxRate() {
        return incomeTaxRate;
    }

    static void setIncomeTaxRate(float rate) {
        incomeTaxRate = rate;
    }

    float getNetSalary() {
        return (baseSalary + overtimeHours*20) * (1 - incomeTaxRate);
    }

    float getBaseSalary() {
        return baseSalary;
    }

    void printDetails() {
        cout<<name<<" (FullTime) - Overtime: "<< fixed << setprecision(2)<<overtimeHours<<"h - Base Salary: "<< fixed << setprecision(2)<<getBaseSalary()<<" - Net Salary: "<< fixed << setprecision(2)<<getNetSalary()<<endl;
    }

};

class Contractor : public Payable, public Employee {
private:
    int completedProjects;
    static float serviceFeeRate;

public:
    Contractor(string name = "", float baseSalary = 0.0, int completedProjects = 0) : Employee(name, baseSalary) {
        this->completedProjects = completedProjects;
    }

    static float getServiceFeeRate() {
        return serviceFeeRate;
    }

    static float setServiceFeeRate(float rate) {
        serviceFeeRate = rate;
    }

    float getNetSalary() {
        return (baseSalary + (float)completedProjects*100) * (1 - serviceFeeRate);
    }

    float getBaseSalary() {
        return baseSalary;
    }

    void printDetails() {
        cout<<name<<" (Contractor) - Projects: "<<completedProjects<<" - Base Salary: "<< fixed << setprecision(2)<<getBaseSalary()<<" - Net Salary: "<< fixed << setprecision(2)<<getNetSalary()<<endl;
    }

    int getCompletedProjects() {
        return completedProjects;
    }

};

float FullTimeEmployee :: incomeTaxRate = 0.10;
float Contractor :: serviceFeeRate = 0.15;

class NoContractorException {
private:
    string message;

public:
    NoContractorException(string message) {
        this->message = message;
    }

    void print() {
        cout<<message<<endl;
    }
};

Contractor* findHighestPaidContractor(Payable** employees, int n) {
    Contractor* hp = nullptr;

    for (int i = 0; i < n; i++) {
        Contractor* c = dynamic_cast<Contractor*>(employees[i]);

        if (c == nullptr) {
            continue;
        }

        if (hp == nullptr || c->getNetSalary() > hp->getNetSalary()) {
            hp = c;
        } else if (c->getNetSalary() == hp->getNetSalary() && c->getCompletedProjects() > hp->getCompletedProjects()) {
            hp = c;
        }
    }

    if (hp == nullptr) {
        throw NoContractorException("There are no contractors");
    } else {
        return hp;
    }

}

void printHighestPaidContractor(Payable** employees, int n) {
    try {
        Contractor* c = findHighestPaidContractor(employees, n);
        c->printDetails();
    } catch (NoContractorException& e){
        e.print();
    }
}
