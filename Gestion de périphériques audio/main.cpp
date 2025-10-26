#include <iostream>
#include <string>
using namespace std;


class SortieAudio {
public:
    virtual void ouvrir() = 0;
    virtual void jouer(string son) = 0;
    virtual void fermer() = 0;
    virtual ~SortieAudio() {}
};


class HautParleur : public SortieAudio {
public:
    void ouvrir() override { cout << "Haut-parleur ouvert.\n"; }
    void jouer(string son) override { cout << "Haut-parleur joue: " << son << endl; }
    void fermer() override { cout << "Haut-parleur ferm�.\n"; }
};


class CasqueBT : public SortieAudio {
public:
    void ouvrir() override { cout << "Casque Bluetooth connect�.\n"; }
    void jouer(string son) override { cout << "Casque Bluetooth joue: " << son << endl; }
    void fermer() override { cout << "Casque Bluetooth d�connect�.\n"; }
};


class SortieHDMI : public SortieAudio {
public:
    void ouvrir() override { cout << "Sortie HDMI activ�e.\n"; }
    void jouer(string son) override { cout << "Sortie HDMI joue: " << son << endl; }
    void fermer() override { cout << "Sortie HDMI d�sactiv�e.\n"; }
};


void tester(SortieAudio* sa) {
    sa->ouvrir();
    sa->jouer("Do R� Mi Fa Sol");
    sa->fermer();
    cout << "----------------------\n";
}

int main() {
    SortieAudio* tab[3];

    tab[0] = new HautParleur();
    tab[1] = new CasqueBT();
    tab[2] = new SortieHDMI();

    for (int i = 0; i < 3; i++) {
        tester(tab[i]);

    }

    return 0;
}
