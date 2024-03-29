/// <summary>
/// @author: Eric O' Toole, John O' Meara
/// date: 17/10/2017
/// </summary>

#ifndef CHARACTER
#define CHARACTER

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

struct Battery {
	float m_remaining = 1;
	sf::RectangleShape m_outline;
	sf::RectangleShape m_filling;
	sf::Color m_fillColour;
	sf::Color m_outlineColour;
};

class Character
{
public:
	sf::RectangleShape m_TESTPOINTER;
	sf::RectangleShape m_TESTLEFT, m_TESTRIGHT;

	Character();
	Character(string name);
	
	virtual string getName();
	virtual float getRadius();

	virtual void render(sf::RenderTarget &targ);
	virtual void renderMiniMap(sf::RenderTarget & target);
	virtual void update();
	virtual void init();

	virtual void applyForce(sf::Vector2f direction);
	virtual void move();
	void setPosition(sf::Vector2f pos);

	sf::Vector2f getPosition(){
		return m_position;
	}
	float getRotation() {
		return m_rotation;
	}

protected:
	Battery m_battery;

	string m_name;
	sf::RectangleShape m_rect;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::CircleShape m_minimapIcon;

	float m_rotation;
	float m_spinSpeed;

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;

	sf::Vector2f m_direction; // direction to move towards, seperate to rotation

	bool m_moving;
	float m_acceleration;
	float m_moveSpeed;
	float m_maxSpeed;

	float m_collisionRadius;
};

#endif !CHARACTER