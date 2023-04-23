// Inclure les en-têtes nécessaires pour utiliser SFML
#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    // Créer une fenêtre SFML avec une résolution de 1920x1080
    sf::RenderWindow window(sf::VideoMode(2160, 1440), "Julia Set Fractal Generator");
    // Limiter le taux de rafraîchissement à 60 images par seconde
    window.setFramerateLimit(60);

    sf::Shader shader;
    // Charger le shader à partir du fichier "julia_set.glsl"
    if (!shader.loadFromFile("julia_set.glsl", sf::Shader::Fragment))
        return 1;

    // Créer un rectangle pour couvrir toute la fenêtre
    sf::RectangleShape screen(sf::Vector2f(window.getSize()));

    // Définir les paramètres initiaux du shader
    shader.setUniform("resolution", sf::Vector2f(window.getSize()));
    shader.setUniform("zoom", 2.0f);
    shader.setUniform("offset", sf::Vector2f(-1.0f, -1.0f));

    // Créer une horloge pour mesurer le temps écoulé
    sf::Clock clock;

    // Boucle principale de la fenêtre
    while (window.isOpen()) {
        // Gérer les événements de la fenêtre
        sf::Event event;
        while (window.pollEvent(event)) {
            // Fermer la fenêtre si l'événement "Closed" est détecté
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Obtenir le temps écoulé depuis le début du programme
        float elapsedTime = clock.getElapsedTime().asSeconds();
        // Changer l'angle pour modifier l'ensemble de Julia
        float angle = elapsedTime * 0.5f;
        std::cout << 0.8f * cos(angle) << std::endl;
        // Mettre à jour la constante complexe pour l'ensemble de Julia en fonction de l'angle
        shader.setUniform("juliaC", sf::Vector2f(0.8f * cos(angle), 0.8f * sin(angle)));
        // Effacer la fenêtre avec une couleur noire
        window.clear();

        // Dessiner le rectangle couvrant toute la fenêtre en utilisant le shader
        window.draw(screen, &shader);

        // Dessiner par dessus les axes de coordonnées
        sf::RectangleShape xAxis(sf::Vector2f((float) window.getSize().x, 1));
        sf::RectangleShape yAxis(sf::Vector2f(1, (float) window.getSize().y));
        xAxis.setPosition(0, (float) window.getSize().y / 2);
        yAxis.setPosition((float) window.getSize().x / 2, 0);
        window.draw(xAxis);
        window.draw(yAxis);

        sf::CircleShape point(5);
        point.setFillColor(sf::Color::Black);
        point.setPosition((float) window.getSize().x / 2 + 0.8f * cos(angle) * window.getSize().x / 2,
                          (float) window.getSize().y / 2 + 0.8f * sin(angle) * window.getSize().y / 2);
        window.draw(point);

        // Afficher le contenu de la fenêtre à l'écran
        window.display();
    }

// Terminer le programme avec le code de sortie 0 (succès)
    return 0;
}