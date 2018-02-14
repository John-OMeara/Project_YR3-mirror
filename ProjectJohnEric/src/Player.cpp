#include "Player.h"

/// <summary>
/// Default player constructor
/// </summary>
Player::Player()
	: Character()
{
}

/// <summary>
/// Player constructor that sets a name
/// </summary>
/// <param name="name">Name of the character for testing</param>
Player::Player(string name)
	: Character(name),
	m_visionRange(100),
	m_fieldOfVision(45)
{
	m_TESTPOINTER.setSize(sf::Vector2f(0.5, m_visionRange));
	m_TESTPOINTER.setOrigin(1, 0);

	m_TESTLEFT.setSize(sf::Vector2f(0.5, m_visionRange));
	m_TESTLEFT.setOrigin(1, 0);
	m_TESTRIGHT.setSize(sf::Vector2f(0.5, m_visionRange));
	m_TESTRIGHT.setOrigin(1, 0);
}

void Player::init(LightEngine & engine)
{
	m_light = new Light();
	m_light->position = m_position;
	m_light->radius = m_visionRange;
	m_light->angleSpread = m_fieldOfVision;
	m_light->angle = m_rotation;
	m_light->color = sf::Color(240, 230, 120, 128);
	m_light->endColor = sf::Color(240, 230, 120, 255);
	engine.Lights.push_back(m_light);
}

void Player::update(sf::RenderWindow &window, Xbox360Controller & controller)
{
	controller.update();

	if (KeyboardHandler::GetInstance()->KeyPressed(sf::Keyboard::Space))
	{
		if (m_usingMouse)
		{
			m_usingMouse = false;
			m_rect.setFillColor(sf::Color::Red);
		}
		else
		{
			m_usingMouse = true;
			m_rect.setFillColor(sf::Color::Green);
		}
	}

	if ((KeyboardHandler::GetInstance()->KeyDown(sf::Keyboard::LShift))
		|| controller.m_currentState.thumbstickRightClick)
	{
		m_viewForward = true;
	}
	else
	{
		m_viewForward = false;
	}


#pragma region MOVEMENT_LOGIC
	m_direction = sf::Vector2f(0, 0);

	// The moving bool won't work 100%. If two opposite keys (eg, up and down) are
	// being held at the same time, the player won't move but his speed will be
	// accelerating. Worth fixing?
	m_moving = false;

	// @TODO: Fix the analogue movement so that it's not just 8-directional
	if (KeyboardHandler::GetInstance()->KeyDown(sf::Keyboard::A))
	{
		m_direction.x += -1;
		m_moving = true;
	}
	if (KeyboardHandler::GetInstance()->KeyDown(sf::Keyboard::D))
	{
		m_direction.x += 1;
		m_moving = true;
	}
	if (KeyboardHandler::GetInstance()->KeyDown(sf::Keyboard::W))
	{
		m_direction.y += -1;
		m_moving = true;
	}
	if (KeyboardHandler::GetInstance()->KeyDown(sf::Keyboard::S))
	{
		m_direction.y += 1;
		m_moving = true;
	}

	if (controller.m_currentState.thumbstickLeft.x >= 20) {
		m_direction.x -= -1;
		m_moving = true;
	}
	else if (controller.m_currentState.thumbstickLeft.x <= -20) {
		m_direction.x += -1;
		m_moving = true;
	}

	if (controller.m_currentState.thumbstickLeft.y >= 20) {

		m_direction.y -= -1;
		m_moving = true;
	}
	else if (controller.m_currentState.thumbstickLeft.y <= -20) {
		m_direction.y += -1;
		m_moving = true;
	}

	move();

#pragma endregion

#pragma region ROTATION_LOGIC

	if (m_usingMouse)
	{
		sf::Vector2f mouse = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

		sf::Vector2f d = mouse - m_position;
		m_rotation = (atan2(d.y, d.x) * (180 / acos(-1)));
	}

	else
	{
		if (KeyboardHandler::GetInstance()->KeyDown(sf::Keyboard::Left))
		{
			m_rotation += m_spinSpeed;
			if (m_rotation >= 360)
				m_rotation -= 360;
		}
		if (KeyboardHandler::GetInstance()->KeyDown(sf::Keyboard::Right))
		{
			m_rotation -= m_spinSpeed;
			if (m_rotation < 0)
				m_rotation += 360;
		}

		m_rotation = controller.m_currentState.rightAngleDEG;
	}


#pragma endregion

#pragma region
	m_light->position = m_position;
	m_light->angle = m_rotation;

#pragma region UPDATE_DEBUG
	m_TESTPOINTER.setRotation(m_rotation - 90);
	m_TESTPOINTER.setPosition(m_position);
	m_TESTLEFT.setRotation(m_rotation - m_fieldOfVision/2 -90);
	m_TESTLEFT.setPosition(m_position);
	m_TESTRIGHT.setRotation(m_rotation + m_fieldOfVision / 2 - 90);
	m_TESTRIGHT.setPosition(m_position);
#pragma endregion

}
