#include "tools.h" 

sf::Time m_time;
sf::Clock m_clock;


void initTools()
{
	srand(time(0));
}

void restartClock()
{
	m_time = m_clock.restart();
}

sf::Time getRestartClock()
{
	return m_time;
}

float getDeltaTime()
{
	return m_time.asSeconds();
}

int randInt(int const& min, int const& max)
{
	return (rand() % (max - min + 1)) + min;
}

sf::Vector2f createVectorWithVector(sf::Vector2f const& _v1, sf::Vector2f const& _v2)
{
	return sf::Vector2f(_v2.x - _v1.x, _v2.y - _v1.y);
}

float getSqrMagnitude(sf::Vector2f const& _a)
{
	return (_a.x * _a.x) + (_a.y * _a.y);
}

float getSqrMagnitudeBetween2Vectors(sf::Vector2f const& _a, sf::Vector2f const& _b)
{
	return getSqrMagnitude(createVectorWithVector(_a, _b));
}

float getMagnitude(sf::Vector2f const& _a)
{
	return sqrtf(getSqrMagnitude(_a));
}

float getMagnitudeBetween2Vectors(sf::Vector2f const& _a, sf::Vector2f const& _b)
{
	return sqrtf(getSqrMagnitudeBetween2Vectors(_a, _b));
}

sf::Vector2f normalizef(sf::Vector2f const& _a)
{
	float magnitude = getMagnitude(_a);
	if (magnitude < EPSILON) {
		return _a;
	}
	return sf::Vector2f(_a.x / magnitude, _a.y / magnitude);
}

sf::Vector2f getNormBetween2Vectorsf(sf::Vector2f const& _a, sf::Vector2f const& _b)
{
	return normalizef(createVectorWithVector(_a, _b));
}

sf::Vector2f polarCoord(sf::Vector2f const& _a, float const& _r, float const& _teta)
{
	return sf::Vector2f(_a.x + (_r * cosf(_teta)), _a.y + (_r * sinf(_teta)));
}

float getAngleBetweenVectors(sf::Vector2f const& _a, sf::Vector2f const& _b)
{
	return atan2f(_b.y, _b.x) - atan2f(_a.y, _a.x);;
}

int randomInt(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

float randomFloat(float min, float max)
{
	return (float)randomInt(min, max);
}

sf::Color randColor(int a)
{
	return sf::Color::Color(randomInt(0, 255), randomInt(0, 255), randomInt(0, 255), a);
}

float lerp(float v0, float v1, float t)
{
	return (1 - t) * v0 + t * v1;
}

float lerp_smooth(float v0, float v1, float t)
{
	return v0 + (v1 - v0) * (t * t * (3.f - 2.f * t));
}

sf::Vector2f vec2_lerp(sf::Vector2f v0, sf::Vector2f v1, float t)
{
	sf::Vector2f tmp;
	tmp.x = (1 - t) * v0.x + t * v1.x;
	tmp.y = (1 - t) * v0.y + t * v1.y;
	return tmp;
}

sf::Vector2f vec2_lerp_smooth(sf::Vector2f v0, sf::Vector2f v1, float t)
{
	sf::Vector2f tmp;
	t = fmaxf(0.0f, fminf(1.0f, t));
	tmp.x = v0.x + (v1.x - v0.x) * (t * t * (3.f - 2.f * t));
	tmp.y = v0.y + (v1.y - v0.y) * (t * t * (3.f - 2.f * t));
	return tmp;
}

sf::Color color_lerp(sf::Color v0, sf::Color v1, float t)
{
	sf::Color tmp;
	tmp.r = (1 - t) * v0.r + t * v1.r;
	tmp.g = (1 - t) * v0.g + t * v1.g;
	tmp.b = (1 - t) * v0.b + t * v1.b;
	tmp.a = (1 - t) * v0.a + t * v1.a;
	return tmp;
}

sf::Color color_lerp_smooth(sf::Color v0, sf::Color v1, float t)
{
	sf::Color tmp;
	tmp.r = v0.r + (v1.r - v0.r) * (t * t * (3.f - 2.f * t));
	tmp.g = v0.g + (v1.g - v0.g) * (t * t * (3.f - 2.f * t));
	tmp.b = v0.b + (v1.b - v0.b) * (t * t * (3.f - 2.f * t));
	tmp.a = v0.a + (v1.a - v0.a) * (t * t * (3.f - 2.f * t));
	return tmp;
}

void AddForce(sf::Vector2f const& _force, sf::Vector2f& _velocity, float const& _mass)
{
	_velocity = _velocity + _force * (1.f / _mass);
}