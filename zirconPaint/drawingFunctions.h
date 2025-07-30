#pragma once
#include "tools.h"
//has compacted functions for the initialisation of drawing tools and can provide default parameters to them more flexibly than if defined in the classes.
sf::Vector2f createEllipse(sf::Vector2f placementLocation, ellipseTool* currentEllipse, sf::Color colour = sf::Color::Blue);
sf::Vector2f createRectangle(sf::Vector2f placementLocation, rectangleTool* currentRectangle, sf::Color colour = sf::Color::Magenta);
sf::Vector2f createFreehand(sf::Vector2f placementLocation, freehandTool* currentFreehand, sf::Color color = sf::Color::White, float thickness = 5);
sf::Vector2f createLine(sf::Vector2f placementLocation, lineTool * currentLine, sf::Color colour = sf::Color::Red, float thickness = 5); 
