Да се дефинира класа Shipment со следните информации:

senderName (string) - име на испраќачот

baseCost (float) - основна цена на пратката

Потребно е да се имплементираат потребните конструктори, деструктор, методи get и set за класата Shipment.

Да се дефинира апстрактна класа Deliverable со следните чисто виртуелни функции:

float getBaseCost() - ја враќа основната цена на пратката пред каква било пресметка

float getFinalCost() - ја враќа конечната цена што треба да се плати по сите додатоци

void printDetails() - печати детали за објектот

Да се дефинираат две класи ExpressParcel и FreightCargo кои наследуваат од Shipment и Deliverable.

За класата ExpressParcel, се чуваат следните дополнителни атрибути:

distanceKm (float) - растојанието на доставата во километри 
fuelSurchargeRate (float) - стапката на додаток за гориво применета на цената, иста е за сите објекти од класата ExpressParcel, со почетна вредност 0.12 
Да се имплементираат методите getFuelSurchargeRate() и setFuelSurchargeRate() за fuelSurchargeRate. 

Функцијата getFinalCost() ја враќа конечната цена. За класата ЕxpressParcel таа се пресметува така што се започнува од основната цена (baseCost), а потоа се применуваат следните правила:

Се додава надоместок за растојание, пресметан како поминатото растојание (distanceKm) помножено со 0.5.
На крај, на добиената сума ѝ се додава додаток за гориво, кој изнесува fuelSurchargeRate (иницијално 12%) од таа сума; резултатот е конечната цена.
Функцијата getBaseCost() ја враќа основната цена без никакви измени.

printDetails() го печати секој ExpressParcel во следниот формат:

[senderName] (Express) - Distance: [distanceKm]km - Base Cost: [baseCost] - Final Cost: [finalCost]

За класата FreightCargo, се чуваат следните дополнителни атрибути:

volumeM3 (float) - зафатнината на товарот во кубни метри 
customsRate (float) - царинската стапка применета на цената, иста e за сите објекти од класата FreightCargo, со почетна вредност  0.20 

Да се имплементираат методите getCustomsRate() и setCustomsRate() за customsRate. 


Функцијата getFinalCost() ја враќа конечната цена. Таа се пресметува така што се започнува од основната цена (baseCost), а потоа се применуваат следните правила:

Се додава надоместок за зафатнина, пресметан како зафатнината на товарот (volumeM3) помножена со 8.
На крај, на добиената сума ѝ се додава царина, која изнесува customsRate (иницијално 20%) од таа сума; резултатот е конечната цена.

Функцијата getBaseCost() ја враќа основната цена без никакви измени. 


Функцијата printDetails() го печати секој FreightCargo во следниот формат:

[senderName] (Freight) - Volume: [volumeM3]m3 - Base Cost: [baseCost] - Final Cost: [finalCost] 

Да се дефинира класа за исклучок NoExpressParcelException, а потоа да се дефинираат следните глобални функции:

ExpressParcel* findMostExpensiveExpressParcel(Deliverable** shipments, int n) 

Оваа функција прима низа од покажувачи од Deliverable објекти, ги филтрира само оние од тип ExpressParcel и ја враќа најскапата меѓу нив (онаа со највисока конечна цена). Доколку повеќе ExpressParcel објекти имаат иста конечна цена, се враќа онаа со поголемо растојание (distanceKm). Доколку во низата нема ниту еден ExpressParcel, функцијата треба да фрли исклучок од тип NoExpressParcelException.

void printMostExpensiveExpressParcel(Deliverable** shipments, int n) 

Оваа функција ја повикува findMostExpensiveExpressParcel. Доколку е вратен ExpressParcel, ги печати неговите детали. Доколку се фати исклучок од тип NoExpressParcelException, се печати пораката "There are no express parcels".

Искористете #include <iomanip> и cout << fixed << setprecision(2) за заокружување.

#include <iostream>
#include <cmath>
#include <cstring>
#include <cctype>
#include <iomanip>
using namespace std;

class Shipment {
protected:
    string senderName;
    float baseCost;

public:
    Shipment(string senderName = "", float baseCost = 0.0) {
        this->senderName = senderName;
        this->baseCost = baseCost;
    }

    string getSenderName() {
        return this->senderName;
    }

    float getBaseCost() {
        return this->baseCost;
    }

    void setBaseCost(float temp) {
        this->baseCost = temp;
    }

    void setSenderName(string temp) {
        this->senderName = temp;
    }

};

class Deliverable {
public:
    virtual float getBaseCost() = 0;
    virtual float getFinalCost() = 0;
    virtual void printDetails() = 0;
};


class ExpressParcel : public Deliverable, public Shipment {
private:
    float distanceKm;
    static float fuelSurchargeRate;

public:
    ExpressParcel(string senderName = "", float baseCost = 0.0, float distanceKm = 0.0) : Shipment(senderName, baseCost) {
        this->distanceKm = distanceKm;
    }

    static float getFuelSurchargeRate() {
        return fuelSurchargeRate;
    }

    static void setFuelSurchargeRate(float temp) {
        fuelSurchargeRate = temp;
    }

    float getFinalCost() {
        return (baseCost + distanceKm*0.5) * (1+fuelSurchargeRate);
    }

    float getBaseCost() {
        return baseCost;
    }

    void printDetails() {
        cout<<senderName<<" (Express) - Distance: "<< fixed << setprecision(2)<<distanceKm<<"km - Base Cost: "<< fixed << setprecision(2)<<getBaseCost()<<" - Final Cost: "<< fixed << setprecision(2)<<getFinalCost()<<endl;
    }

    float getDistanceKm() {
        return distanceKm;
    }

};

class FreightCargo : public Deliverable, public Shipment {
private:
    float volumeM3;
    static float customsRate;

public:
    FreightCargo(string senderName = "", float baseCost = 0.0, float volumeM3 = 0.0) : Shipment(senderName, baseCost) {
        this->volumeM3 = volumeM3;
    }

    static float getCustomsRate() {
        return customsRate;
    }

    static void setCustomsRate(float temp) {
        customsRate = temp;
    }

    float getFinalCost() {
        return (baseCost + volumeM3*8) * (1+customsRate);
    }

    float getBaseCost() {
        return baseCost;
    }

    void printDetails() {
        cout<<senderName<<" (Freight) - Volume: "<< fixed << setprecision(2)<<volumeM3<<"m3 - Base Cost: "<< fixed << setprecision(2)<<getBaseCost()<<" - Final Cost: "<< fixed << setprecision(2)<<getFinalCost()<<endl;
    }

};

float ExpressParcel::fuelSurchargeRate = 0.12;
float FreightCargo::customsRate = 0.20;

class NoExpressParcelException {
private:
    string message;

public:
    NoExpressParcelException(string message = "") {
        this->message = message;
    }

    void print() {
        cout<<message<<endl;
    }
};

ExpressParcel* findMostExpensiveExpressParcel(Deliverable** shipments, int n) {
    ExpressParcel* temp = nullptr;

    for (int i = 0; i < n; i++) {
        ExpressParcel* pl = dynamic_cast<ExpressParcel*>(shipments[i]);

        if (pl == nullptr) {
            continue;
        }

        if (temp == nullptr || temp->getFinalCost() < pl->getFinalCost()) {
            temp = pl;
        } else if (temp->getFinalCost() == pl->getFinalCost() && temp->getDistanceKm() < pl->getDistanceKm()) {
            temp = pl;
        }
    }

    if (temp == nullptr) {
        throw NoExpressParcelException("There are no express parcels");
    } else {
        return temp;
    }

}

void printMostExpensiveExpressParcel(Deliverable** shipments, int n) {
    try {
        ExpressParcel* ep = findMostExpensiveExpressParcel(shipments, n);
        ep->printDetails();
    } catch (NoExpressParcelException& e) {
        e.print();
    }
}
