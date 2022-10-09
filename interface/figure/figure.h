#include <SFML/Graphics.hpp>
#include "../../geometry/superEllipse/superEllipse.h"

#ifndef FIGURE_H

#define FIGURE_H

class Figure
{
protected:
	int width = 0;
	int height = 0;
	int outlineWidth = 1;
	sf::Vector2f* coords = new sf::Vector2f();
	sf::Color* fillColor = new sf::Color();
	sf::Color* outlineColor = new sf::Color();
public:
	virtual ~Figure();
	virtual void setWidth(int width);
	virtual void setHeight(int height);
	virtual void setOutlineWidth(int width);
	virtual int getWidth();
	virtual int getHeight();
	virtual int getOutlineWidth();
	virtual void draw(sf::RenderWindow& window);
	virtual void setFillColor(sf::Color color);
	virtual void setFillColor(sf::Color* color);
	virtual sf::Color* getFillColor();
	virtual void setOutlineColor(sf::Color color);
	virtual void setOutlineColor(sf::Color* color);
	virtual sf::Color* getOutlineColor();
	virtual void setX(float x);
	virtual void setY(float y);
	virtual void setCoords(float x, float y);
	virtual void setCoords(sf::Vector2f coords);
	virtual void setCoords(float* coords);
	virtual float getX();
	virtual float getY();
	virtual sf::Vector2f* getCoords();
};

#endif // !FIGURE_H


