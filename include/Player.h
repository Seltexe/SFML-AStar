#pragma once
#include "tools.h"
#include "Node.h"
#include "Window.h"

class Player
{
private:
    std::vector<Node*> path;
    Node* currentNode;
    size_t pathIndex;

    float m_speed = 100.0f;
    sf::Vector2f m_playerPosition;
    sf::CircleShape playerShape;

public:
    Player(Node* startNode) : currentNode(startNode), pathIndex(0) {
        playerShape.setRadius(16.0f);
        playerShape.setFillColor(sf::Color::Blue);
    }

    void setPath(const std::vector<Node*>& newPath) {
        path = newPath;
        pathIndex = 0;
        if (!path.empty()) {
            m_playerPosition = sf::Vector2f(path[0]->m_position.x * 32, path[0]->m_position.y * 32);
        }
    }

    void update() {
        if (pathIndex < path.size() - 1) {
            Node* nextNode = path[pathIndex + 1];
            sf::Vector2f targetPosition(nextNode->m_position.x * 32, nextNode->m_position.y * 32);

            sf::Vector2f direction = targetPosition - m_playerPosition;
            float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

            if (distance > 1.0f) {
                sf::Vector2f normalizedDirection = direction / distance;
                float moveStep = m_speed * getDeltaTime();

                if (moveStep < distance) {
                    m_playerPosition += normalizedDirection * moveStep;
                }
                else {
                    m_playerPosition = targetPosition;
                    pathIndex++;
                }
            }
            else {
                m_playerPosition = targetPosition;
                pathIndex++;
            }
        }
    }

    void drawPath(Window& window) {
        sf::VertexArray line(sf::LinesStrip);
        for (auto node : path) {
            line.append(sf::Vertex(sf::Vector2f(node->m_position.x * 32 + 16, node->m_position.y * 32 + 16), sf::Color::Red));
        }
        window.draw(line);
    }


    void draw(Window& window) {
        playerShape.setPosition(m_playerPosition);
        window.draw(playerShape);

        ImGui::Begin("Player");

        ImGui::SliderFloat("Player Speed", &m_speed, 0.f, 1000.f);

        ImGui::End();
    }
};

