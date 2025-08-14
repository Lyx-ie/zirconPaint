#pragma once
#include "masterInclude.h"
//class for tool and all subclasses.
//if you think I am making a separate file for every subclass you are CRINGE

class Tools {
public:
    toolType toolType = _NULL;
    virtual sf::Sprite render() = NULL;
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
    bool bugfix;
    freehandTool();
    ~freehandTool();
    void setFreehandSize(float newSize);
    void setFreehandColour(sf::Color newColour);
    sf::Sprite freehandDraw(sf::Vector2f location);
    sf::Sprite render();
};

class customShapeTool : public Tools {
public: 
    sf::RenderTexture texture;
    lineTool interpolationLine;
    sf::Color customShapeColour;
    sf::Vector2f previousPosition;
    sf::Vector2f currentPosition;
    sf::Vector2f originPosition;
    float linesPlaced = 0;
    std::vector <sf::Vector2f> linePlacements;
    float size = 5;
    bool shapeCreated = false;
    customShapeTool();
    ~customShapeTool();
    void setColour(sf::Color inputColour);
    void placeLine(sf::Vector2f location);
    sf::Sprite renderLines(sf::Vector2f location);
    sf::Sprite render();

};

class stampTool : public Tools {
public:
    std::string imageFilePath;
    bool stampToolValid;
    sf::Texture imageTexture;
    sf::Vector2f imageLocation;
    sf::Vector2u fileDimensions;
    stampTool();
    ~stampTool();
    bool stampLocation(sf::Vector2f location);
    bool setImage(std::string inputFilePath);
    sf::Sprite stampRender();
    sf::Sprite render();
};