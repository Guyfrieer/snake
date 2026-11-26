#include <SFML/Graphics.hpp>
#include "zaidimas.h"

int main() {
    sf::RenderWindow langas(sf::VideoMode(STULPELIAI * LANGELIS, EILUTES * LANGELIS), "Snake");
    langas.setFramerateLimit(60);

    Busena busena;
    Paveikslai pav;
    ikeltiPaveikslus(pav);
    paruostiZaidima(busena);

    sf::Clock laikrodis;
    const float ZINGSNIO_LAIKAS = 0.15f; // sekundės tarp žingsnių (mažiau = greičiau)

    while (langas.isOpen()) {
        sf::Event ivykis;
        while (langas.pollEvent(ivykis)) {
            if (ivykis.type == sf::Event::Closed)
                langas.close();
        }

        apdorotiIvesti(busena);

        if (laikrodis.getElapsedTime().asSeconds() >= ZINGSNIO_LAIKAS) {
            laikrodis.restart();
            atnaujinti(busena);
        }

        pieisti(langas, busena, pav);
    }
    return 0;
}