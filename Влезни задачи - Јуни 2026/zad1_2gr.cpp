Да се дефинира класа Song за претставување на информации за песна.
Во класата се чуваат следните информации:
- име на песната (string)
- број на слушања (int)
- број на лајкови (int)
- времетраење на песната во секунди (int)

За класата да се имплементираат:
- Потребните конструктори, set и get методи
- Метод void print() const за печатење на информациите за песната во прегледен формат: име, број на слушања, број на лајкови и времетраење.

Да се дефинира класа Playlist за претставување на музичка плејлиста.


Во класата се чуваат следните информации:


- име на плејлистата (string)
- динамички алоцирана низа од песни Song* (не е дозволено користење на std::vector)
- број на песни во плејлистата (int)


За класата да се имплементираат:


- Потребните конструктори
- Метод double playlistEngagement() const кој го пресметува степенот на интеракција на корисниците со плејлистата според формулата:

playlistEngagement = (вкупно слушања + 2 * вкупно лајкови) / вкупно времетраење
Доколку вкупното времетраење на песните во плејлистата е 0, методот враќа 0.

- Метод void print() const кој го печати името на плејлистата, а потоа секоја песна во форматот зададен во Song::print(). Песните се печатат во истиот редослед како што се додадени во низата. На крајот да се испечати степенот на интеракција на корисниците со плејлистата.
- Оператор Playlist& operator+=(const Song& s) кој додава нова песна во плејлистата, односно ја проширува динамичката низа за еден елемент.


Во функцијата main() каде што е означено треба од тастатура да се прочитаат информации за N песни, да се формира плејлиста со тие песни со користење на операторот +=. Потоа  на стандарден излез да се испечатат податоците за плејлистата, вклучувајќи ги и податоците за сите нејзини песни.


#include<iostream>
#include<cstring>
#include<iomanip>


using namespace std;

class Song {
private:
    string ime;
    int slusanja;
    int lajkovi;
    int vremetraenje;
public:
    Song(string ime="", int slusanja = 0, int lajkovi = 0, int vremetraenje = 0) {
        this->ime=ime;
        this->slusanja = slusanja;
        this->lajkovi = lajkovi;
        this->vremetraenje = vremetraenje;
    }
    string getIme() {
        return ime;
    }
    int getSlusanja() {
        return slusanja;
    }
    int getLajkovi() {
        return lajkovi;
    }
    int getVremetraenje() {
        return vremetraenje;
    }

    void print() const{
        cout<<ime<<" - listens: "<<slusanja<<", likes: "<<lajkovi<<", duration: "<<vremetraenje<<endl;
    }
};

class Playlist {
private:
    string ime_pl;
    Song* pesni;
    int br_pesni;
public:
    Playlist() {
        this->ime_pl = "";
        this->pesni = 0;
        this->br_pesni = 0;
    }
    Playlist(string ime_pl) {
        this->ime_pl = ime_pl;
        this->pesni = 0;
        this->br_pesni = 0;
    }
    Playlist(const Playlist& pl) {
        this->ime_pl = pl.ime_pl;
        this->br_pesni = pl.br_pesni;

        this -> pesni = new Song[br_pesni+1];

        for (int i=0; i<br_pesni; i++) {
            this->pesni[i] = pl.pesni[i];
        }
    }
    Playlist& operator=(const Playlist& pl) {
        if (this==&pl) return *this;
        this->ime_pl = pl.ime_pl;
        this->br_pesni = pl.br_pesni;

        this -> pesni = new Song[br_pesni+1];

        for (int i=0; i<pl.br_pesni; i++) {
            this->pesni[i] = pl.pesni[i];
        }
        return *this;
    }

    ~Playlist() {
        delete[] pesni;
    }

    double playlistEngagement() const {
        int vkupnoSlusanje = 0;
        int vkupnoLajkovi = 0;
        int vkupnoVremetraenje = 0;
        for (int i=0; i<br_pesni; i++) {
            vkupnoSlusanje += pesni[i].getSlusanja();
            vkupnoLajkovi += pesni[i].getLajkovi();
            vkupnoVremetraenje += pesni[i].getVremetraenje();
        }
        if (vkupnoVremetraenje == 0) {
            return 0;
        }
        return ((double)vkupnoSlusanje+2*(double)vkupnoLajkovi)/(double)vkupnoVremetraenje;
    }

    void print() const {
        cout<<"Playlist: "<<ime_pl<<endl;
        if (br_pesni == 0) {
            cout<<"No songs in playlist"<<endl;
        }
        else {
            for (int i=0; i<br_pesni; i++) {
                pesni[i].print();
            }
        }
        cout<<"Playlist engagement: "<<fixed<<setprecision(2)<<playlistEngagement()<<endl;
    }

    Playlist& operator+=(const Song& s) {
        Song* temp = new Song[br_pesni+1];

        for (int i=0; i<br_pesni; i++) {
            temp[i] = pesni[i];
        }

        temp[br_pesni] = s;

        delete[] pesni;

        pesni = temp;

        br_pesni++;

        return *this;
    }
};

int main() {
    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        // TODO your code HERE!

        string ime_playlist;
        cin>>ime_playlist;

        int n;
        cin>>n;

        Playlist plejlista(ime_playlist);

        for (int i=0; i<n; i++) {
            string ime;
            int slusanja, lajkovi, vremetraenje;
            cin>>ime>>slusanja>>lajkovi>>vremetraenje;

            Song s(ime,slusanja,lajkovi,vremetraenje);

            plejlista +=s;
        }

        plejlista.print();

    } else if(testCase == 2) {
        Playlist original("Original");
        original += Song("Song A", 500, 100, 180);
        original += Song("Song B", 300, 50, 200);

        {
            Playlist copy(original);
            copy += Song("Song C", 100, 20, 150);

            cout << "=== copy (inside scope) ===" << endl;
            copy.print();
            cout << endl;
        }

        cout << "=== original (after copy destroyed) ===" << endl;
        original.print();
    } else if (testCase == 3) {
        Playlist *p1 = new Playlist("P1");
        *p1 += Song("Alpha", 900, 180, 240);
        *p1 += Song("Beta", 600, 120, 190);

        Playlist *p2 = new Playlist("P2");
        *p2 += Song("Gamma", 200, 40, 160);

        *p2 = *p1;

        delete p1;

        cout << "=== p2 (after p1 deleted, must still be intact) ===" << endl;
        p2->print();
        cout << endl;

        *p2 = *p2;
        cout << "=== p2 after self-assignment ===" << endl;
        p2->print();

        delete p2;

        return 0;
    }
}
