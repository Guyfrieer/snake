#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

// ---- Konstantos ----
const int LANGELIS = 48;     // vieno langelio dydis pikseliais
const int STULPELIAI = 16;
const int EILUTES = 12;

enum Kryptis { VIRSUN, ZEMYN, KAIRE, DESINE };

// ---- Žaidimo būsena ----
struct Busena {
    std::vector<sf::Vector2i> gyvate; // gyvate[0] = galva (Xavier), kiti = mašinos
    Kryptis kryptis;
    int tikslinisIlgis;
};

// ---- Paveikslėliai ----
struct Paveikslai {
    sf::Texture galva;   // xavier.png
    sf::Texture masina;  // masina.png
    bool galvaYra = false;
    bool masinaYra = false;
};

// ---- Funkcijos (jų realizacija yra zaidimas.cpp) ----
void ikeltiPaveikslus(Paveikslai& pav);
void paruostiZaidima(Busena& busena);
void apdorotiIvesti(Busena& busena);
void atnaujinti(Busena& busena);
void pieisti(sf::RenderWindow& langas, const Busena& busena, const Paveikslai& pav);
