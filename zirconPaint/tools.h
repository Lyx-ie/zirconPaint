#pragma once
#pragma once
#include "masterInclude.h"
//class for tool and all subclasses.

class Tools {
public:
    toolType toolType = _NULL;
    virtual sf::Sprite render() = 0;
};

class ellipseTool : public Tools {
public:
    sf::Color ellipseColour;
    sf::Vector2f ellipseDimensions;
    sf::Vector2f ellipseLocation;
    sf::RenderTexture texture;
    ellipseTool();
    ~ellipseTool();
    void setEllipseColour(sf::Color newColour);
    void setEllipseSize(sf::Vector2f newDimension);
    void setEllipseLocation(sf::Vector2f location);
    sf::Sprite renderEllipse();
    sf::Sprite render();
};

class rectangleTool : public Tools {
public:
    sf::Color rectangleColour;
    sf::Vector2f rectangleDimensions;
    sf::Vector2f rectangleLocation;
    sf::RenderTexture texture;
    rectangleTool();
    ~rectangleTool();
    void setRectangleColour(sf::Color newColour);
    void setRectangleSize(sf::Vector2f newDimensions);
    void setRectangleLocation(sf::Vector2f location);
    sf::Sprite renderRectangle();
    sf::Sprite render();


};

class lineTool : public Tools {
public:
    sf::Color lineColour;
    sf::Vector2f lineOrigin;
    sf::Vector2f lineDraw;
    float lineThickness;
    sf::RenderTexture texture;
    lineTool();
    ~lineTool();
    void setLineColour(sf::Color newColour);
    void setLineThickness(float newThickness);
    void setLineOrigin(sf::Vector2f location);
    void setLineLocation(sf::Vector2f location);
    sf::RectangleShape drawLine();
    sf::Sprite renderLine();
    sf::Sprite render();
};

class freehandTool : public Tools {
public:
    lineTool interpolationLine;
    sf::Color freehandColour;
    sf::Vector2f pointPosition;
    sf::Vector2f previousPosition;
    sf::RenderTexture texture;
    float size;
    freehandTool();
    ~freehandTool();
    void setFreehandSize(float newSize);
    void setFreehandColour(sf::Color newColour);
    sf::Sprite freehandDraw(sf::Vector2f location);
    sf::Sprite render();
};