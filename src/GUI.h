// GUI.h
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <vector>
#include <iostream>
#include "Simulation.h"

namespace Style {
    extern const sf::Color BG;
    extern const sf::Color PANEL;
    extern const sf::Color BORDER;
    extern const sf::Color CYAN;
    extern const sf::Color PURPLE;
    extern const sf::Color GREEN;
    extern const sf::Color ORANGE;
    extern const sf::Color GOLD;
    extern const sf::Color RED;
    extern const sf::Color YELLOW;
    extern const sf::Color WHITE;
    extern const sf::Color DIM;
    extern const sf::Color VERY_DIM;
}

class GUI {
private:
    sf::RenderWindow window;
    sf::Font font;
    Simulation* simRef = NULL;
    sf::Clock animClock;
    sf::CircleShape pauseButton;
    sf::Text pauseText{font};

    void drawGrid(int W, int H);
    void drawGlow(sf::Vector2f center, float r, sf::Color col, int layers = 5);
    void drawLineGlow(float x, float y, float w, float h, sf::Color col);
    void drawPanel(float x, float y, float w, float h, sf::Color border, sf::Color fill = Style::PANEL);
    void txt(const std::string& s, float x, float y, int sz, sf::Color col, bool centerX = false);
    void drawProgressBar(float x, float y, float w, float h, float progress, sf::Color col);
    void drawVSep(float x, float y, float h, sf::Color col = Style::BORDER);
    void drawBadge(const std::string& s, float x, float y, sf::Color col);

public:
    void initializeWindow();
    void connectToSimulation(Simulation* sim);
    void handleEvents();
    void updateGUI();
    void displayTime();
    void displaySimulationStatus(float pulse);
    void drawServers(float pulse);
    void drawQueue();
    void drawGraph();
    void refreshDisplay();
    void closeWindow();
    bool isOpen() const;
};