#include "drawingFunctions.h"

sf::Vector2f createEllipse(sf::Vector2f placementLocation, ellipseTool* currentEllipse, sf::Color colour) {
	currentEllipse->setEllipseColour(colour);
	currentEllipse->setEllipseLocation(placementLocation);
	return placementLocation;
}

sf::Vector2f createRectangle(sf::Vector2f placementLocation, rectangleTool* currentRectangle, sf::Color colour) {
	currentRectangle->setRectangleColour(colour);
	currentRectangle->setRectangleLocation(placementLocation);
	return placementLocation;
}

sf::Vector2f createFreehand(sf::Vector2f placementLocation, freehandTool* currentFreehand, sf::Color color, float thickness)
{
	currentFreehand->setFreehandColour(color);
	currentFreehand->setFreehandSize(thickness);
	return sf::Vector2f();
}

sf::Vector2f createLine(sf::Vector2f placementLocation, lineTool* currentLine, sf::Color colour, float thickness) {
	currentLine->setLineColour(colour);
	currentLine->setLineOrigin(placementLocation);
	currentLine->setLineThickness(thickness * 2);
	return placementLocation;
}

