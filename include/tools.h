#pragma once
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <thread>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <cctype>
#include <ctime>
#include <cstdlib>
#include <list>
#include <map>
#include <unordered_map>
#include "imgui.h"
#include "imgui-SFML.h"

#define EPSILON (float)1e-6
#define MAX (a,b) a >= b ? a : b
#define MIN (a,b) a <= b ? a : b
#define DEG2RAD 0.01745329
#define RAD2DEG 57.295779
#define PI 3.141592
#define LERP(a, b, t) (b-a) * t +a
#define SIGN(nbr) nbr >= 0.f ? 1.f : -1.f

void initTools();

void restartClock();

sf::Time getRestartClock();

float getDeltaTime();

int randInt(int const& min, int const& max);

sf::Vector2f createVectorWithVector(sf::Vector2f const& _v1, sf::Vector2f const& _v2);

float getSqrMagnitude(sf::Vector2f const& _a);

float getSqrMagnitudeBetween2Vectors(sf::Vector2f const& _a, sf::Vector2f const& _b);

float getMagnitude(sf::Vector2f const& _a);

float getMagnitudeBetween2Vectors(sf::Vector2f const& _a, sf::Vector2f const& _b);

sf::Vector2f normalizef(sf::Vector2f const& _a);

sf::Vector2f getNormBetween2Vectorsf(sf::Vector2f const& _a, sf::Vector2f const& _b);

sf::Vector2f polarCoord(sf::Vector2f const& a, float const& r, float const& teta);

float getAngleBetweenVectors(sf::Vector2f const& _a, sf::Vector2f const& _b);

int randomInt(int min, int max);

float randomFloat(float min, float max);

sf::Color randColor(int a);

float lerp(float v0, float v1, float t);

float lerp_smooth(float v0, float v1, float t);

sf::Vector2f vec2_lerp(sf::Vector2f v0, sf::Vector2f v1, float t);

sf::Vector2f vec2_lerp_smooth(sf::Vector2f v0, sf::Vector2f v1, float t);

sf::Color color_lerp(sf::Color v0, sf::Color v1, float t);

sf::Color color_lerp_smooth(sf::Color v0, sf::Color v1, float t);

void AddForce(sf::Vector2f const& _force, sf::Vector2f& _velocity, float const& _mass = 1.f);
