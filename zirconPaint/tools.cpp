#include "masterInclude.h"
#include "tools.h"

bool debugMode = false;
sf::Vector2u drawingArea = (sf::Vector2u(1080, 720));
sf::Vector2f drawingOrigin = (sf::Vector2f(100, 100));

ellipseTool::ellipseTool()
{
	//resize texture to drawing area size and set tool type
	bool resizeSuccessful;
	resizeSuccessful = texture.resize(drawingArea);
	
	toolType = _ellipse;
}

ellipseTool::~ellipseTool() {}


void ellipseTool::setEllipseColour(sf::Color newColour)
{ //change ellipse tool colour
	ellipseColour = newColour;
}

void ellipseTool::setEllipseSize(sf::Vector2f newDimensions)
{ // change the ellipse tool's size
	ellipseDimensions.x = newDimensions.x / 2;
	ellipseDimensions.y = newDimensions.y / 2;
}

void ellipseTool::setEllipseLocation(sf::Vector2f location)
{ // set the origin location for the ellipse
	ellipseLocation = location;
}

sf::Sprite ellipseTool::renderEllipse()
{
	//renbdering ellipse code, clearing the texture type and drawing a sprite to it with the allocated parameters.
	texture.clear(sf::Color::Transparent);
	sf::Sprite sprite(texture.getTexture());
	ellipseShape ellipse;
	ellipse.setFillColor(ellipseColour);
	ellipse.setRadius(ellipseDimensions);
	ellipse.setPosition(ellipseLocation);
	texture.draw(ellipse);
	texture.display();
	sprite.setTexture(texture.getTexture());
	return sf::Sprite(sprite);
}

sf::Sprite ellipseTool::render()
{
	//re-rendering the sprite from the texture saved in memory on the draw frame
	sf::Sprite sprite(texture.getTexture());
	return sf::Sprite(sprite);
}

rectangleTool::rectangleTool()
{
	//resize texture to drawing area size and set tool type
	bool resizeSuccessful;
	resizeSuccessful = texture.resize(drawingArea);
	toolType = _rectangle;
}

rectangleTool::~rectangleTool() {}

void rectangleTool::setRectangleColour(sf::Color newColour)
{	//set the rectangle colour
	rectangleColour = newColour;
}


void rectangleTool::setRectangleSize(sf::Vector2f newDimensions)
{
	//draw the rectangle to a specific set of dimensions
	rectangleDimensions = newDimensions;
}

void rectangleTool::setRectangleLocation(sf::Vector2f location)
{
	//set the origin point of the rectangle
	rectangleLocation = location;
}

sf::Sprite rectangleTool::renderRectangle()
{
	//render the rectangle through similar means to the previous
	texture.clear(sf::Color::Transparent);
	sf::Sprite sprite(texture.getTexture());
	sf::RectangleShape rectangle;
	rectangle.setFillColor(rectangleColour);
	rectangle.setSize(rectangleDimensions);
	rectangle.setPosition(rectangleLocation);
	texture.draw(rectangle);
	texture.display();
	sprite.setTexture(texture.getTexture());
	return sf::Sprite(sprite);
}

sf::Sprite rectangleTool::render() {
	//re-rendering the sprite from the texture saved in memory on the draw frame
	sf::Sprite sprite(texture.getTexture());
	return sf::Sprite(sprite);
}

lineTool::lineTool()
{
	//resize texture to drawing area size and set tool type
	bool resizeSuccessful;
	resizeSuccessful = texture.resize(drawingArea);
	lineThickness = 0;
	toolType = _line;
}

lineTool::~lineTool()
{
}

void lineTool::setLineColour(sf::Color newColour)
{
	//change the line colour
	lineColour = newColour;
}

void lineTool::setLineThickness(float newThickness)
{
	//change the line thickness
	lineThickness = newThickness;
}

void lineTool::setLineOrigin(sf::Vector2f location)
{
	//set the starting point to draw a line from
	lineOrigin = location;
}

void lineTool::setLineLocation(sf::Vector2f location)
{
	//set the ending point to draw a line to
	lineDraw = location;
}

sf::RectangleShape lineTool::drawLine()
{
	//drawline function used to allow the freehand tool to return just a shape rather than a sprite
	sf::RectangleShape line;
	line.setFillColor(lineColour);
	line.setPosition(lineOrigin);
	line.setOrigin(sf::Vector2f(0, lineThickness / 2));
	//since a line should be drawn with an angled rectangle. Do math to determine the dimensions of the rectangle
	float mathsPythagValueX, mathsPythagValueY, mathsSquaredValueX, mathsSquaredValueY, mathsHypotValue, lineLengthValue, lineAngleValue;
	mathsPythagValueX = lineDraw.x;
	mathsPythagValueY = lineDraw.y;
	mathsSquaredValueX = mathsPythagValueX * mathsPythagValueX;
	mathsSquaredValueY = mathsPythagValueY * mathsPythagValueY;
	mathsHypotValue = mathsSquaredValueX + mathsSquaredValueY;
	lineLengthValue = sqrt(mathsHypotValue);
	lineAngleValue = acos(mathsPythagValueX / lineLengthValue);
	lineAngleValue *= (180 / 3.1416);
	if (mathsPythagValueY < 0) {
		lineAngleValue *= -1;
	}
	//set parameters of output line
	line.setSize(sf::Vector2f(lineLengthValue, lineThickness));
	line.rotate(sf::degrees(lineAngleValue));
	return sf::RectangleShape(line);
}

sf::Sprite lineTool::renderLine()
{
	//initialise sprite and texture
	texture.clear(sf::Color::Transparent);
	sf::Sprite sprite(texture.getTexture());
	texture.draw(drawLine());
	texture.display();
	//add rounded edges
	sf::CircleShape roundedEdges;
	roundedEdges.setFillColor(lineColour);
	roundedEdges.setRadius(lineThickness / 2);
	roundedEdges.setPosition(lineOrigin - sf::Vector2f(lineThickness / 2, lineThickness / 2));
	texture.draw(roundedEdges);
	roundedEdges.setPosition((lineDraw + lineOrigin) - sf::Vector2f(lineThickness / 2, lineThickness / 2));
	texture.draw(roundedEdges);
	sprite.setTexture(texture.getTexture());
	return sf::Sprite(sprite);
}



sf::Sprite lineTool::render()
{
	//re-rendering the sprite from the texture saved in memory on the draw frame
	sf::Sprite sprite(texture.getTexture());
	return sf::Sprite(sprite);
}


freehandTool::freehandTool()
{

	//resize texture to drawing area size and set tool type
	bool resizeSuccessful;
	resizeSuccessful = texture.resize(drawingArea);
	size = 0;
	toolType = _freehand;
	bugfix = true; 
}

freehandTool::~freehandTool()
{
}

void freehandTool::setFreehandSize(float newSize)
{
	//set the width of the line to draw
	size = newSize;
}

void freehandTool::setFreehandColour(sf::Color newColour)
{
	//set the colour of a freehand line to draw
	freehandColour = newColour;
}

sf::Sprite freehandTool::freehandDraw(sf::Vector2f location)
{
	//place a circle at the cursor this frame
	//TODO interpolate the line tool if the mouse has moved too far since the last frame.
	pointPosition = location;
	pointPosition.x -= size;
	pointPosition.y -= size;
	sf::CircleShape circle;
	sf::Sprite sprite(texture.getTexture());
	if (previousPosition.x != NULL && previousPosition.y != NULL) {
		if (abs(previousPosition.x - pointPosition.x) > (size) || abs(previousPosition.y - pointPosition.y) > (size)) {
			//initialise stats for corresponding line tool
			sf::Vector2f interpolationLineOrigin, interpolationLineDraw;

			interpolationLineOrigin.x = previousPosition.x + size;
			interpolationLineOrigin.y = previousPosition.y + size;
			interpolationLineDraw = location - interpolationLineOrigin;
			interpolationLine.setLineColour(freehandColour);
			interpolationLine.setLineThickness(size * 2);
			interpolationLine.setLineOrigin(interpolationLineOrigin);
			interpolationLine.setLineLocation(interpolationLineDraw);
			//draw a line in between the two circles that are too far away
			texture.draw(interpolationLine.drawLine());
			//place a circle at the start of the line
			circle.setFillColor(freehandColour);
			circle.setRadius(size);
			circle.setPosition(previousPosition);
			texture.draw(circle);
		}
	}
	//place a circle at the cursor
	circle.setFillColor(freehandColour);
	circle.setRadius(size);
	circle.setPosition(pointPosition);
	texture.draw(circle);
	texture.display();
	previousPosition = pointPosition;
	return sf::Sprite(sprite);
}

sf::Sprite freehandTool::render() {
	//re-rendering the sprite from the texture saved in memory on the draw frame
	sf::Sprite sprite(texture.getTexture());
	return sf::Sprite(sprite);
}

customShapeTool::customShapeTool()
{
	bool resizeSuccessful;
	resizeSuccessful = texture.resize(drawingArea);
	interpolationLine.setLineColour(customShapeColour);
	interpolationLine.setLineThickness(size);
}

customShapeTool::~customShapeTool()
{
}

void customShapeTool::setColour(sf::Color inputColour)
{
	customShapeColour = inputColour;
}

void customShapeTool::placeLine(sf::Vector2f location)
{
	if (linesPlaced == 0) {
		originPosition = location;
		interpolationLine.setLineOrigin(location);
	}
	else {
		interpolationLine.setLineOrigin(previousPosition);
	}
	interpolationLine.setLineLocation(location);
	linePlacements.push_back(location);
	linesPlaced++;
}



sf::Sprite customShapeTool::renderLines(sf::Vector2f location)
{
	for (int i = 1; i < linesPlaced; i++) {
		interpolationLine.setLineOrigin(linePlacements.at(i));
		if (linesPlaced > 1) {
			interpolationLine.setLineLocation(linePlacements.at(i - 1));
		}
		else { interpolationLine.setLineLocation(linePlacements.at( i )); }
		texture.draw(interpolationLine.drawLine());
		sf::Vector2f debugValue;
		debugValue = linePlacements.at(i);
		std::cout << debugValue.x << " " << debugValue.y << std::endl;

	}
	std::cout << std::endl;
	interpolationLine.setLineOrigin(previousPosition);
	interpolationLine.setLineLocation(location);
	

	currentPosition = location;
	if (previousPosition.x != NULL && previousPosition.y != NULL) {
		if (abs(previousPosition.x - currentPosition.x) < (size * 2) || abs(previousPosition.y - currentPosition.y) < (size * 2)) {
			sf::ConvexShape custom;
			custom.setPointCount(linesPlaced);
			int i = 0;
			for (sf::Vector2f thisPoint : linePlacements) {
				custom.setPoint(i, { thisPoint });
				i++;
			}
			texture.draw(custom);
			shapeCreated = true;
		}
	}
	texture.draw(interpolationLine.render());
	sf::Sprite sprite(texture.getTexture());
	return sf::Sprite(sprite);
}

sf::Sprite customShapeTool::render() {

	sf::ConvexShape custom;
	custom.setPointCount(linesPlaced);
	int i = 0;
	for (sf::Vector2f thisPoint : linePlacements) {
		custom.setPoint(i, { thisPoint });
		i++;
	}
	texture.draw(custom);
	sf::Sprite sprite(texture.getTexture());
	return sf::Sprite(sprite);
}

stampTool::stampTool()
{
	stampToolValid = false;
}

stampTool::~stampTool()
{
}

bool stampTool::stampLocation(sf::Vector2f location)
{
	if (stampToolValid == false) {
		incorrectFileTypeDialogueBox2();
		return false;
	}
	else {
		imageLocation = location;
		return true;
	}

}

bool stampTool::setImage(std::string inputFilePath)
{
	imageFilePath = returnFilePath();
	stampToolValid = imageTexture.loadFromFile(imageFilePath);
	//imageTexture.resize(imageTexture.getSize());
	return stampToolValid;
}

sf::Sprite stampTool::stampRender()
{
	fileDimensions = imageTexture.getSize();

	
	sf::Sprite sprite(imageTexture);
	

	sprite.setPosition(sf::Vector2f(imageLocation.x - fileDimensions.x/2, imageLocation.y - fileDimensions.y / 2));
	return sf::Sprite(sprite);
}

sf::Sprite stampTool::render() {
	sf::Sprite sprite(imageTexture);
	sprite.setPosition(sf::Vector2f(imageLocation.x - fileDimensions.x / 2, imageLocation.y - fileDimensions.y / 2));

	return sf::Sprite(sprite);
}