#ifndef TEAM3_RENDERER_H
#define TEAM3_RENDERER_H

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "../graph/Graph.h"
#include "RotationCalculator.h"

class Renderer {
private:
    sf::RenderWindow* window_;
    std::unique_ptr<RotationCalculator> rotationCalculator_;
public:
    Renderer(sf::RenderWindow* window);
    void render(Graph* g);
};


#endif //TEAM3_RENDERER_H