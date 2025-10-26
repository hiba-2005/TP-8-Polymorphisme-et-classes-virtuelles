#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <iomanip>
using namespace std;


struct Vec3 {
    float x, y, z;
};


float distance(const Vec3& a, const Vec3& b) {
    return sqrt((a.x - b.x)*(a.x - b.x)
              + (a.y - b.y)*(a.y - b.y)
              + (a.z - b.z)*(a.z - b.z));
}


class Lumiere {
public:
    virtual float intensite(const Vec3& point) = 0;
    virtual string type() const = 0;
    virtual ~Lumiere() {}
};

class LumiereDirectionnelle : public Lumiere {
public:
    float intensite(const Vec3& point) override {
        (void)point;
        return 1.0f;
    }
    string type() const override {
        return "Lumière directionnelle";
    }
};

class LumierePonctuelle : public Lumiere {
    Vec3 position;
    float puissance;
public:
    LumierePonctuelle(Vec3 pos, float p) : position(pos), puissance(p) {}

    float intensite(const Vec3& point) override {
        float d = distance(point, position);
        float I = puissance / (1 + d * d);
        cout << fixed << setprecision(3);
        cout << "  -> [Ponctuelle] Distance = " << d
             << " | Intensité = " << I << endl;
        return I;
    }

    string type() const override {
        return "Lumière ponctuelle";
    }
};

class LumiereSpot : public Lumiere {
    Vec3 position;
    float puissance;
    float angle;
public:
    LumiereSpot(Vec3 pos, float p, float a)
        : position(pos), puissance(p), angle(a) {}

    float intensite(const Vec3& point) override {
        float d = distance(point, position);
        if (d > angle) {
            cout << "  -> [Spot] Point hors du cône (distance = " << d << " > " << angle << ")\n";
            return 0.0f;
        }
        float I = puissance / (1 + d);
        cout << fixed << setprecision(3);
        cout << "  -> [Spot] Distance = " << d
             << " | Intensité = " << I << endl;
        return I;
    }

    string type() const override {
        return "Lumière spot";
    }
};


float calculerEclairage(const Vec3& point, const vector<unique_ptr<Lumiere>>& lumieres) {
    float total = 0.0f;
    cout << "\n=== Calcul de l'éclairage pour le point ("
         << point.x << "," << point.y << "," << point.z << ") ===\n";
    cout << "----------------------------------------------------\n";

    for (const auto& L : lumieres) {
        cout << "Type : " << L->type() << endl;
        float I = L->intensite(point);
        cout << "  --> Contribution : " << I << endl;
        cout << "----------------------------------------------------\n";
        total += I;
    }

    cout << ">>> Intensité totale au point (" << point.x << "," << point.y << "," << point.z
         << ") = " << total << endl;
    cout << "====================================================\n\n";
    return total;
}


int main() {
    vector<unique_ptr<Lumiere>> lumieres;

    lumieres.push_back(make_unique<LumiereDirectionnelle>());
    lumieres.push_back(make_unique<LumierePonctuelle>(Vec3{0, 0, 5}, 10.0f));
    lumieres.push_back(make_unique<LumiereSpot>(Vec3{0, 0, 2}, 5.0f, 3.0f));

    vector<Vec3> points = {
        {0, 0, 0}
    };

    for (const auto& p : points) {
        calculerEclairage(p, lumieres);
    }

    return 0;
}
