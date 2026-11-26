#include "zaidimas.h"

// Bandome įkelti nuotraukas iš assets/ aplanko.
// Jei failo nėra, programa neužlūžta, o naudoja spalvotus kvadratus.
void ikeltiPaveikslus(Paveikslai& pav) {
    pav.galvaYra = pav.galva.loadFromFile("assets/xavier.png");
    pav.masinaYra = pav.masina.loadFromFile("assets/masina.png");
}

// Nustato pradinę gyvatės padėtį: galva + 2 mašinos, juda į dešinę.
void paruostiZaidima(Busena& busena) {
    busena.gyvate.clear();
    busena.gyvate.push_back(sf::Vector2i(5, 5)); // galva
    busena.gyvate.push_back(sf::Vector2i(4, 5)); // mašina
    busena.gyvate.push_back(sf::Vector2i(3, 5)); // mašina
    busena.kryptis = DESINE;
    busena.tikslinisIlgis = 3;
}

// Skaito rodykles ir keičia kryptį (negalima apsisukti 180 laipsnių).
void apdorotiIvesti(Busena& busena) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && busena.kryptis != ZEMYN)
        busena.kryptis = VIRSUN;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && busena.kryptis != VIRSUN)
        busena.kryptis = ZEMYN;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && busena.kryptis != DESINE)
        busena.kryptis = KAIRE;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && busena.kryptis != KAIRE)
        busena.kryptis = DESINE;
}

// Vienas žaidimo žingsnis: pastumia gyvatę per vieną langelį.
void atnaujinti(Busena& busena) {
    sf::Vector2i nauja = busena.gyvate[0];

    if (busena.kryptis == VIRSUN) nauja.y--;
    if (busena.kryptis == ZEMYN)  nauja.y++;
    if (busena.kryptis == KAIRE)  nauja.x--;
    if (busena.kryptis == DESINE) nauja.x++;

    // Atsimušė į sieną, pradedame iš naujo (vėliau čia bus "Game over")
    if (nauja.x < 0 || nauja.x >= STULPELIAI || nauja.y < 0 || nauja.y >= EILUTES) {
        paruostiZaidima(busena);
        return;
    }

    busena.gyvate.insert(busena.gyvate.begin(), nauja); // nauja galva priekyje
    while ((int)busena.gyvate.size() > busena.tikslinisIlgis)
        busena.gyvate.pop_back();                       // nupjauname uodegą
}

// Nupiešia visą žaidimą į langą.
void pieisti(sf::RenderWindow& langas, const Busena& busena, const Paveikslai& pav) {
    langas.clear(sf::Color(30, 30, 30));

    for (size_t i = 0; i < busena.gyvate.size(); i++) {
        float x = (float)busena.gyvate[i].x * LANGELIS;
        float y = (float)busena.gyvate[i].y * LANGELIS;
        bool galva = (i == 0);

        const sf::Texture& tekstura = galva ? pav.galva : pav.masina;
        bool turiTeksturos = galva ? pav.galvaYra : pav.masinaYra;

        if (turiTeksturos) {
            sf::Sprite spritas(tekstura);
            sf::Vector2u dydis = tekstura.getSize();
            spritas.setScale((float)LANGELIS / dydis.x, (float)LANGELIS / dydis.y);
            spritas.setPosition(x, y);
            langas.draw(spritas);
        }
        else {
            sf::RectangleShape kvadratas(sf::Vector2f(LANGELIS - 2, LANGELIS - 2));
            kvadratas.setPosition(x + 1, y + 1);
            kvadratas.setFillColor(galva ? sf::Color::Yellow : sf::Color::Red);
            langas.draw(kvadratas);
        }
    }

    langas.display();
}