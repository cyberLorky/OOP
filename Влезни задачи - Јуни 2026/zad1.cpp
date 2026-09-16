// Да се дефинира класа Player за претставување информации за фудбалски играч.

// Во класата да се чуваат следните информации:

// - име на играчот (string)

// - број на голови (int)

// - број на асистенции (int)

// - број на одиграни натпревари (int)

// За класата да се имплементираат:

// - Потребните конструктори, set и get методи

// - Метод void print() const за печатење на информациите за играчот во прегледен формат (име, голови, асистенции, натпревари).

// Да се дефинира класа Team за претставување на фудбалски тим.

// Во класата да се чуваат следните информации:

// - име на тимот (string)

// - динамички алоцирана низа од играчи (Player*) (не е дозволено користење на std::vector)

// - број на играчи во тимот (int)

// За класата да се имплементираат:

// - Потребните конструктори, set и get методи

// - Метод double teamEfficiency() const кој ja пресметува ефикасноста на тимот според формулата:

//   teamEfficiency = (вкупно голови + вкупно асистенции) / вкупно одиграни натпревари

//   Доколку тимот нема одиграно ниту еден натпревар, методот враќа 0.

// - Метод void print() const кој го печати името на тимот, а потоа и секој играч во форматот зададен во Player::print(). Играчите се печатат во истиот редослед како што се додадени во низата. На крајот да се испечати ефикасноста на тимот.

// - Оператор Team& operator+=(const Player& p) кој додава нов играч во тимот (ja проширува динамичката низа за еден елемент).

// Во функцијата main() каде што е означено треба од тастатура да се прочитаат информации за N играчи, да се формира тим со тие играчи со користење на операторот +=. Потоа  на стандарден излез да се испечатат податоците за тимот, вклучувајќи ги и податоците за сите негови играчи.



#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Player
{
private:
    string ime;
    int golovi;
    int asistencii;
    int natprevari;

public:
    Player()
    {
        ime = "";
        golovi = 0;
        asistencii = 0;
        natprevari = 0;
    }

    Player(string ime, int golovi, int asistencii, int natprevari)
    {
        this->ime = ime;
        this->golovi = golovi;
        this->asistencii = asistencii;
        this->natprevari = natprevari;
    }

    void setIme(string ime)
    {
        this->ime = ime;
    }

    void setGolovi(int golovi)
    {
        this->golovi = golovi;
    }

    void setAsistencii(int asistencii)
    {
        this->asistencii = asistencii;
    }

    void setNatprevari(int natprevari)
    {
        this->natprevari = natprevari;
    }

    string getIme() const
    {
        return ime;
    }

    int getGolovi() const
    {
        return golovi;
    }

    int getAsistencii() const
    {
        return asistencii;
    }

    int getNatprevari() const
    {
        return natprevari;
    }

    void print() const
    {
        cout << ime << " - goals: " << golovi
             << ", assists: " << asistencii
             << ", matches: " << natprevari << endl;
    }
};

class Team
{
private:
    string ime;
    Player *igraci;
    int brIgraci;

public:
    Team()
    {
        ime = "";
        igraci = 0;
        brIgraci = 0;
    }

    Team(string ime)
    {
        this->ime = ime;
        igraci = 0;
        brIgraci = 0;
    }

    ~Team()
    {
        delete[] igraci;
    }

    Team(const Team &t)
    {
        ime = t.ime;
        brIgraci = t.brIgraci;

        if (brIgraci > 0)
        {
            igraci = new Player[brIgraci];

            for (int i = 0; i < brIgraci; i++)
            {
                igraci[i] = t.igraci[i];
            }
        }
        else
        {
            igraci = 0;
        }
    }

    Team &operator=(const Team &t)
    {
        if (this != &t)
        {
            delete[] igraci;

            ime = t.ime;
            brIgraci = t.brIgraci;

            if (brIgraci > 0)
            {
                igraci = new Player[brIgraci];

                for (int i = 0; i < brIgraci; i++)
                {
                    igraci[i] = t.igraci[i];
                }
            }
            else
            {
                igraci = 0;
            }
        }

        return *this;
    }

    void setIme(string ime)
    {
        this->ime = ime;
    }

    string getIme() const
    {
        return ime;
    }

    int getBrIgraci() const
    {
        return brIgraci;
    }

    Player *getIgraci() const
    {
        return igraci;
    }

    double teamEfficiency() const
    {
        int vkupnoGolovi = 0;
        int vkupnoAsistencii = 0;
        int vkupnoNatprevari = 0;

        for (int i = 0; i < brIgraci; i++)
        {
            vkupnoGolovi += igraci[i].getGolovi();
            vkupnoAsistencii += igraci[i].getAsistencii();
            vkupnoNatprevari += igraci[i].getNatprevari();
        }

        if (vkupnoNatprevari == 0)
        {
            return 0;
        }

        return (double)(vkupnoGolovi + vkupnoAsistencii) /
            vkupnoNatprevari;
    }

    void print() const
    {
        cout << "Team: " << ime << endl;

        if (brIgraci == 0)
        {
            cout << "No players in team" << endl;
        }
        else
        {
            for (int i = 0; i < brIgraci; i++)
            {
                igraci[i].print();
            }
        }

        cout << "Team efficiency: "
             << fixed << setprecision(2)
             << teamEfficiency() << endl;
    }

    Team &operator+=(const Player &p)
    {
        Player *novaNiza = new Player[brIgraci + 1];

        for (int i = 0; i < brIgraci; i++)
        {
            novaNiza[i] = igraci[i];
        }

        novaNiza[brIgraci] = p;

        delete[] igraci;

        igraci = novaNiza;
        brIgraci++;

        return *this;
    }
};

int main()
{
    int testCase;
    cin >> testCase;
    if (testCase == 1)
    {
      // TO DO
        string imeTim;
        int n;

        cin >> imeTim;
        cin >> n;

        Team t(imeTim);

        for (int i = 0; i < n; i++)
        {
            string ime;
            int golovi, asistencii, natprevari;

            cin >> ime >> golovi >> asistencii >> natprevari;

            Player p(ime, golovi, asistencii, natprevari);
            t += p;
        }

        t.print();
    }
    else if (testCase == 2)
    {
        Team original("Real Madrid");
        original += Player("Ronaldo", 40, 10, 38);
        original += Player("Benzema", 20, 12, 35);

        {
            Team copy(original);
            copy += Player("Modric", 5, 18, 36);

            cout << "=== copy (inside scope) ===" << endl;
            copy.print();
            cout << endl;
        }

        cout << "=== original (after copy destroyed) ===" << endl;
        original.print();
    }
    else if (testCase == 3)
    {
        Team t2("Atletico");

        {
            Team t1("Bayern");
            t1 += Player("Muller", 15, 20, 34);
            t1 += Player("Lewandowski", 35, 8, 34);

            t2 = t1;
        }

        cout << "=== t2 (after t1 destroyed) ===" << endl;
        t2.print();
        cout << endl;

        t2 = t2;

        cout << "=== t2 after self-assignment ===" << endl;
        t2.print();
    }

    return 0;
}
