#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;


void replaceAll(string& s, const string& from, const string& to) {
    if (from.empty()) return;
    size_t pos = 0;
    while ((pos = s.find(from, pos)) != string::npos) {
        s.replace(pos, from.size(), to);
        pos += to.size();
    }
}


class Plugin {
public:
    virtual ~Plugin() = default;
    virtual string nom() const = 0;
    virtual string traiter(const string& texte) = 0;
    static unique_ptr<Plugin> creerPlugin(const string& type);
};


class CorrecteurOrthographique : public Plugin {
public:
    string nom() const override { return "CorrecteurOrthographique"; }
    string traiter(const string& t) override {
        string s = t;
        replaceAll(s, "bonjouur", "bonjour");
        replaceAll(s, "sava", "ca va");
        replaceAll(s, "cest", "c'est");
        return s;
    }
};

class TraducteurAnglais : public Plugin {
public:
    string nom() const override { return "TraducteurAnglais"; }
    string traiter(const string& t) override {
        string s = t;
        replaceAll(s, "bonjour", "hello");
        replaceAll(s, "monde", "world");
        replaceAll(s, "merci", "thanks");
        replaceAll(s, "ca va", "how are you");
         replaceAll(s, "c'est", "It's");
        return s;
    }
};

class AnalyseurStyle : public Plugin {
public:
    string nom() const override { return "AnalyseurStyle"; }
    string traiter(const string& t) override {

        string s = t;
        if (s.size() > 80) s += "\n[Style] Phrase longue detectee.";
        else s += "\n[Style] OK.";
        return s;
    }
};


unique_ptr<Plugin> Plugin::creerPlugin(const string& type) {
    if (type == "correcteur") return make_unique<CorrecteurOrthographique>();
    if (type == "traducteur") return make_unique<TraducteurAnglais>();
    if (type == "style")      return make_unique<AnalyseurStyle>();
    return nullptr;
}

int main() {

    cout << "Entrez un texte :\n";
    string texte;
    getline(cin, texte);


    vector<string> types = {"correcteur", "traducteur", "style"};


    vector<unique_ptr<Plugin>> plugins;
    for (const auto& t : types) {
        if (auto p = Plugin::creerPlugin(t)) plugins.push_back(move(p));
    }


    for (const auto& p : plugins) {
        texte = p->traiter(texte);
        cout << "\n--- Plugin : " << p->nom() << " ---\n" << texte << "\n";
    }

    cout << "\n[Termine]\n";
    return 0;
}
