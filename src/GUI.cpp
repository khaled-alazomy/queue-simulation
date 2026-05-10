// GUI.cpp
#include "GUI.h"

// Style namespace contains all colors used in the GUI
// This makes it easier to change the UI theme from one place
namespace Style {
    const sf::Color BG         (8,   10,  22,  255);  // Main background color
    const sf::Color PANEL      (16,  20,  44,  230);  // Panel background color
    const sf::Color BORDER     (35,  45,  85,  255);  // Panel border color
    const sf::Color CYAN       (0,   215, 255, 255);  // Cyan accent color
    const sf::Color PURPLE     (160, 80,  255, 255);  // Purple accent color
    const sf::Color GREEN      (0,   255, 130, 255);  // Green status color
    const sf::Color ORANGE     (255, 160, 40,  255);  // Orange queue color
    const sf::Color GOLD       (255, 215, 0,   255);  // VIP customer color
    const sf::Color RED        (255, 60,  80,  255);  // Busy / paused color
    const sf::Color YELLOW     (255, 230, 0,   255);  // Progress bar color
    const sf::Color WHITE      (215, 220, 255, 255);  // Main text color
    const sf::Color DIM        (70,  85,  130, 255);  // Secondary text color
    const sf::Color VERY_DIM   (35,  45,  75,  255);  // Very dim text color
}

// GUI class handles all visual elements of the simulation
// It displays servers, queue, statistics, graph, and pause button

// Draws a grid background to give the UI a technical look
void GUI::drawGrid(int W, int H) {
    sf::VertexArray lines(sf::PrimitiveType::Lines);
    sf::Color gc(22, 28, 58, 90);

    // Draw vertical grid lines
    for (int x = 0; x < W; x += 50) {
        lines.append({{(float)x, 0}, gc});
        lines.append({{(float)x, (float)H}, gc});
    }

    // Draw horizontal grid lines
    for (int y = 0; y < H; y += 50) {
        lines.append({{0, (float)y}, gc});
        lines.append({{(float)W, (float)y}, gc});
    }

    window.draw(lines);
}

// Draws a circular glow effect around an object
void GUI::drawGlow(sf::Vector2f center, float r, sf::Color col, int layers) {
    for (int i = layers; i >= 1; i--) {
        sf::CircleShape g(r + i * 5.f);

        g.setOrigin({r + i * 5.f, r + i * 5.f});
        g.setPosition(center);

        sf::Color gc = col;
        gc.a = (uint8_t)(8 + i * 7);

        g.setFillColor(gc);
        window.draw(g);
    }
}

// Draws a glowing horizontal line
// Used mainly for panel top borders and progress bars
void GUI::drawLineGlow(float x, float y, float w, float h, sf::Color col) {
    for (int i = 3; i >= 1; i--) {
        sf::RectangleShape g({w, h + i * 3.f});
        g.setPosition({x, y - i * 1.5f});

        sf::Color gc = col;
        gc.a = (uint8_t)(20 + i * 15);

        g.setFillColor(gc);
        window.draw(g);
    }
}

// Draws a panel with background, border, and glowing top line
void GUI::drawPanel(float x, float y, float w, float h, sf::Color border, sf::Color fill) {
    sf::RectangleShape bg({w, h});
    bg.setPosition({x, y});
    bg.setFillColor(fill);
    bg.setOutlineThickness(1.f);
    bg.setOutlineColor(border);
    window.draw(bg);

    drawLineGlow(x, y, w, 2.f, border);

    sf::RectangleShape top({w, 2.f});
    top.setPosition({x, y});
    top.setFillColor(border);
    window.draw(top);
}

// Draws text on the screen
// centerX can be used to center the text horizontally around x
void GUI::txt(const std::string& s, float x, float y, int sz, sf::Color col, bool centerX) {
    sf::Text t(font);
    t.setString(s);
    t.setCharacterSize((unsigned)sz);
    t.setFillColor(col);

    if (centerX) {
        auto b = t.getLocalBounds();
        t.setOrigin({b.size.x / 2.f, 0});
    }

    t.setPosition({x, y});
    window.draw(t);
}

// Draws a progress bar with a glowing fill
void GUI::drawProgressBar(float x, float y, float w, float h, float progress, sf::Color col) {
    // Draw progress bar background
    sf::RectangleShape bg({w, h});
    bg.setPosition({x, y});
    bg.setFillColor(sf::Color(20, 25, 50));
    bg.setOutlineThickness(1.f);
    bg.setOutlineColor(sf::Color(40, 50, 85));
    window.draw(bg);

    // Calculate filled width
    float fillW = std::max(1.f, w * progress);

    // Draw glowing fill effect
    drawLineGlow(x, y, fillW, h, col);

    // Draw actual fill rectangle
    sf::RectangleShape fill({fillW, h});
    fill.setPosition({x, y});
    fill.setFillColor(col);
    window.draw(fill);

    // Draw small white tip at the end of the progress bar
    sf::RectangleShape tip({3.f, h + 4.f});
    tip.setPosition({x + fillW - 2.f, y - 2.f});
    tip.setFillColor(sf::Color(255, 255, 255, 200));
    window.draw(tip);
}

// Draws a vertical separator line
void GUI::drawVSep(float x, float y, float h, sf::Color col) {
    sf::RectangleShape s({1.5f, h});
    s.setPosition({x, y});
    s.setFillColor(col);
    window.draw(s);
}

// Draws a small badge with text and border
void GUI::drawBadge(const std::string& s, float x, float y, sf::Color col) {
    sf::Text t(font);
    t.setString(s);
    t.setCharacterSize(13);
    t.setFillColor(col);

    auto b = t.getLocalBounds();

    sf::RectangleShape bg({b.size.x + 16.f, b.size.y + 10.f});
    bg.setPosition({x, y});

    sf::Color fc = col;
    fc.a = 30;

    bg.setFillColor(fc);
    bg.setOutlineThickness(1.f);
    bg.setOutlineColor(col);
    window.draw(bg);

    t.setPosition({x + 8.f, y + 5.f});
    window.draw(t);
}

// Creates the window, loads the font, and initializes pause button settings
void GUI::initializeWindow() {
    window.create(sf::VideoMode({1120, 700}), "QUEUE SIMULATION SYSTEM");
    window.setFramerateLimit(60);

    // Load font file used by the GUI
    if (!font.openFromFile("../assets/font.ttf")) {
        std::cout << "Error: font.ttf not found!\n";
    }

    float radius = 18.f;

    // Setup pause button shape
    pauseButton.setRadius(radius);
    pauseButton.setOrigin(sf::Vector2f(radius, radius));
    pauseButton.setPosition(sf::Vector2f(1050.f, 34.f));

    pauseButton.setFillColor(Style::GREEN);
    pauseButton.setOutlineThickness(1.5f);
    pauseButton.setOutlineColor(sf::Color(200, 255, 220, 150));

    // Setup pause button text
    pauseText.setFont(font);
    pauseText.setString("P"); // P means Pause
    pauseText.setCharacterSize(16);
    pauseText.setFillColor(sf::Color(8, 10, 22));

    // Center the text inside the circular button
    auto b = pauseText.getLocalBounds();
    pauseText.setOrigin(
        sf::Vector2f(
            b.position.x + b.size.x / 2.f,
            b.position.y + b.size.y / 2.f
        )
    );

    pauseText.setPosition(pauseButton.getPosition());
}

// Connects the GUI with the simulation object
void GUI::connectToSimulation(Simulation* sim) {
    simRef = sim;
}

// Handles all window events such as closing and mouse clicks
void GUI::handleEvents() {
    while (const auto event = window.pollEvent()) {

        // Close the program when the window close button is clicked
        if (event->is<sf::Event::Closed>()) {
            closeWindow();
        }

        // Handle mouse button press events
        if (event->is<sf::Event::MouseButtonPressed>()) {

            // Convert mouse pixel position to window coordinates
            sf::Vector2f mousePos = window.mapPixelToCoords(
                sf::Mouse::getPosition(window)
            );

            // Check if the mouse click is inside the circular pause button
            float dx = mousePos.x - pauseButton.getPosition().x;
            float dy = mousePos.y - pauseButton.getPosition().y;

            if (sqrt(dx * dx + dy * dy) <= pauseButton.getRadius()) {

                // Toggle simulation pause/resume state
                simRef->togglePause();

                // Update pause button color and text depending on simulation state
                if (simRef->getIsPaused()) {
                    pauseButton.setFillColor(Style::RED);
                    pauseText.setString("R"); // R means Resume
                }
                else {
                    pauseButton.setFillColor(Style::GREEN);
                    pauseText.setString("P"); // P means Pause
                }
            }
        }
    }
}

// Updates and redraws the entire GUI
void GUI::updateGUI() {
    float aT = animClock.getElapsedTime().asSeconds();

    // Creates a smooth pulsing value between 0 and 1
    float pulse = (sinf(aT * 3.0f) + 1.0f) * 0.5f;

    window.clear(Style::BG);

    drawGrid(1120, 700);
    displayTime();
    displaySimulationStatus(pulse);
    drawServers(pulse);
    drawQueue();
    drawGraph();

    // Draw pause button glow
    drawGlow(
        pauseButton.getPosition(),
        pauseButton.getRadius() - 8.f,
        simRef->getIsPaused() ? Style::RED : Style::GREEN,
        4
    );

    window.draw(pauseButton);
    window.draw(pauseText);

    refreshDisplay();
}

// Displays top bar information such as title and current time
void GUI::displayTime() {
    drawPanel(0, 0, 1120, 68, Style::CYAN, sf::Color(10, 14, 32, 255));

    txt("QUEUE SIMULATION", 22, 10, 28, Style::CYAN);

    drawVSep(310, 12, 44);

    txt("T =", 325, 12, 16, Style::DIM);
    txt(std::to_string(simRef->getCurrentTime()), 360, 8, 32, Style::WHITE);
    txt("/ " + std::to_string(simRef->getMaxTime()), 400, 18, 16, Style::DIM);

    drawVSep(490, 12, 44);
}

// Displays simulation statistics such as arrived, served, and queue size
void GUI::displaySimulationStatus(float pulse) {
    txt("ARRIVED", 505, 8, 12, Style::DIM);
    txt(std::to_string(simRef->getArrivedCount()), 505, 26, 22, Style::WHITE);

    drawVSep(610, 12, 44);

    txt("SERVED", 625, 8, 12, Style::GREEN);
    txt(std::to_string(simRef->getServedCount()), 625, 26, 22, Style::GREEN);

    drawVSep(720, 12, 44);

    txt("IN QUEUE", 735, 8, 12, Style::ORANGE);
    txt(std::to_string(simRef->getQueue().getQueueSize()), 735, 26, 22, Style::ORANGE);

    drawVSep(840, 12, 44);

    // Display simulation state badge
    if (!simRef->getIsRunning()) {
        drawBadge("SIMULATION COMPLETE", 855, 20, Style::ORANGE);
    }
    else {
        sf::Color runCol(
            Style::GREEN.r,
            Style::GREEN.g,
            Style::GREEN.b,
            (uint8_t)(160 + (int)(pulse * 95))
        );

        drawBadge("RUNNING", 855, 20, runCol);
    }

    txt("", 1120 - 110, 24, 16, Style::VERY_DIM);
}

// Draws all servers and their current status
void GUI::drawServers(float pulse) {
    float sX = 730.f;
    float sY = 80.f;
    float sW = 1120.f - sX - 12.f;

    txt("SERVERS", sX + 4, sY + 2, 12, Style::DIM);

    const auto& servers = simRef->getServers();

    for (size_t i = 0; i < servers.size(); i++) {
        float pY = sY + 22.f + i * 192.f;
        float pH = 180.f;

        bool free = servers[i].isFree();
        sf::Color border = free ? Style::CYAN : Style::PURPLE;

        drawPanel(sX, pY, sW, pH, border);

        // Display how many customers this server has served
        int servedByThis = servers[i].getTotalServedCount();
        txt("Total Served: " + std::to_string(servedByThis), sX + 10.f, pY + 155.f, 13, Style::CYAN);

        // Draw server name tag
        sf::RectangleShape tag({90.f, 22.f});
        tag.setPosition({sX + 8.f, pY + 10.f});
        tag.setFillColor(border);
        window.draw(tag);

        txt("SERVER " + std::to_string(i + 1), sX + 11.f, pY + 11.f, 13, sf::Color(8, 10, 22));

        // Draw status LED
        float ledR = 7.f;
        sf::Vector2f ledPos = {sX + sW - 22.f, pY + 21.f};

        if (!free) {
            sf::Color gc = Style::RED;
            gc.a = (uint8_t)(80 + (int)(pulse * 120));
            drawGlow(ledPos, ledR, gc, 3);
        }

        sf::CircleShape led(ledR);
        led.setOrigin({ledR, ledR});
        led.setPosition(ledPos);
        led.setFillColor(free ? Style::GREEN : Style::RED);
        window.draw(led);

        txt(free ? "FREE" : "BUSY", sX + sW - 75.f, pY + 12.f, 13, free ? Style::GREEN : Style::RED);

        // Separator line inside server panel
        sf::RectangleShape sep({sW - 16.f, 1.f});
        sep.setPosition({sX + 8.f, pY + 40.f});
        sep.setFillColor(Style::BORDER);
        window.draw(sep);

        if (!free) {
            // If server is busy, display the customer being served
            Customer currentCust = servers[i].getCurrentCustomer();
            bool isVIP = currentCust.getIsVIP();

            sf::Color custColor = isVIP ? Style::GOLD : Style::GREEN;

            float cR = 30.f;
            sf::Vector2f cPos = {sX + 50.f, pY + 95.f};

            drawGlow(cPos, cR, custColor, 4);

            // Draw customer circle
            sf::CircleShape cc(cR);
            cc.setOrigin({cR, cR});
            cc.setPosition(cPos);
            cc.setFillColor(isVIP ? sf::Color(200, 150, 0) : sf::Color(0, 190, 100));
            cc.setOutlineThickness(2.f);
            cc.setOutlineColor(custColor);
            window.draw(cc);

            // Draw customer ID inside the circle
            sf::Text cn(font);
            cn.setString("#" + std::to_string(currentCust.getId()));
            cn.setCharacterSize(16);
            cn.setFillColor(sf::Color(8, 10, 22));

            auto cb = cn.getLocalBounds();
            cn.setOrigin({cb.size.x / 2.f, cb.size.y / 2.f});
            cn.setPosition({cPos.x, cPos.y - 3.f});
            window.draw(cn);

            // Display VIP label if the customer is VIP
            if (isVIP) {
                txt("VIP", cPos.x - 10.f, cPos.y - 45.f, 14, Style::GOLD);
            }

            txt("->", sX + 88.f, pY + 82.f, 18, Style::BORDER);
            txt("SERVING", sX + 118.f, pY + 50.f, 11, Style::DIM);
            txt("CUSTOMER #" + std::to_string(currentCust.getId()), sX + 115.f, pY + 65.f, 17, Style::WHITE);

            // Calculate service progress
            float maxServiceTime = currentCust.getServiceTime();
            float remaining = servers[i].getRemainingTime();
            float prog = (maxServiceTime - remaining) / maxServiceTime;

            txt("TIME REMAINING", sX + 115.f, pY + 100.f, 11, Style::DIM);

            // Draw remaining time progress bar
            drawProgressBar(sX + 115.f, pY + 118.f, sW - 125.f, 10.f, 1.0f - prog, Style::YELLOW);

            txt(std::to_string((int)remaining) + " ticks", sX + 115.f, pY + 135.f, 11, Style::YELLOW);
        }
        else {
            // If server is free, display idle state
            txt("AWAITING", sX + 20.f, pY + 65.f, 13, Style::DIM);
            txt("CUSTOMER...", sX + 20.f, pY + 83.f, 13, Style::DIM);

            sf::CircleShape ic(28.f);
            ic.setOrigin({28.f, 28.f});
            ic.setPosition({sX + sW - 65.f, pY + 100.f});
            ic.setFillColor(sf::Color(18, 24, 50));
            ic.setOutlineThickness(2.f);

            sf::Color idleBorder = Style::CYAN;
            idleBorder.a = (uint8_t)(40 + (int)(pulse * 60));

            ic.setOutlineColor(idleBorder);
            window.draw(ic);

            txt("--", sX + sW - 78.f, pY + 89.f, 14, Style::VERY_DIM);
        }
    }
}

// Draws the waiting queue area and customers inside it
void GUI::drawQueue() {
    float qX = 12.f;
    float qY = 80.f;
    float qW = 730.f - 24.f;
    float qH = 400.f;

    drawPanel(qX, qY, qW, qH, Style::ORANGE);

    txt("WAITING QUEUE", qX + 14.f, qY + 10.f, 20, Style::ORANGE);

    int qSize = simRef->getQueue().getQueueSize();

    drawBadge(std::to_string(qSize) + " customers", qX + 230.f, qY + 11.f, Style::ORANGE);

    // Show queue direction labels
    txt("BACK <--", qX + 14.f, qY + 46.f, 11, Style::DIM);
    txt("FRONT -->", qX + qW - 85.f, qY + 46.f, 11, Style::DIM);

    // Separator line under the queue title
    sf::RectangleShape qdiv({qW - 16.f, 1.f});
    qdiv.setPosition({qX + 8.f, qY + 44.f});
    qdiv.setFillColor(Style::BORDER);
    window.draw(qdiv);

    float cR = 28.f;
    float cSpacing = 70.f;

    // First customer starts from the right side because the front is on the right
    float rowStartX = qX + qW - 50.f;
    float rowY1 = qY + 110.f;

    int maxPerRow = (int)((qW - 60.f) / cSpacing);

    for (int i = 0; i < qSize; i++) {
        int row = i / maxPerRow;
        int col = i % maxPerRow;

        // Display only two rows to keep the GUI clean
        if (row >= 2) {
            break;
        }

        Customer cust = simRef->getQueue().getCustomerAtIndex(i);
        bool isVIP = cust.getIsVIP();

        // Move customers from right to left
        float cx = rowStartX - (col * cSpacing);
        float cy = rowY1 + row * 120.f;

        sf::Color custColor = isVIP ? Style::GOLD : sf::Color(200, 120, 25);
        sf::Color custGlow = isVIP ? Style::GOLD : Style::ORANGE;

        // VIP customers get stronger glow
        drawGlow({cx, cy}, cR, custGlow, isVIP ? 5 : 2);

        // Draw customer circle
        sf::CircleShape cc(cR);
        cc.setOrigin({cR, cR});
        cc.setPosition({cx, cy});
        cc.setFillColor(custColor);
        cc.setOutlineThickness(2.f);
        cc.setOutlineColor(custGlow);
        window.draw(cc);

        // Draw customer ID inside the circle
        sf::Text cn(font);
        cn.setString("#" + std::to_string(cust.getId()));
        cn.setCharacterSize(15);
        cn.setFillColor(sf::Color(8, 10, 22));

        auto cb = cn.getLocalBounds();
        cn.setOrigin({cb.size.x / 2.f, cb.size.y / 2.f});
        cn.setPosition({cx, cy - 3.f});
        window.draw(cn);

        // Display VIP label if needed
        if (isVIP) {
            txt("VIP", cx - 10.f, cy - 45.f, 12, Style::GOLD);
        }

        // Draw arrows between customers
        if (col < maxPerRow - 1 && i < qSize - 1) {
            txt(">", cx - 45.f, cy - 9.f, 14, Style::VERY_DIM, false);
        }
    }

    // Display message when the queue is empty
    if (qSize == 0) {
        txt("NO CUSTOMERS WAITING", qX + qW / 2.f - 130.f, qY + 160.f, 20, sf::Color(35, 45, 80));
    }
}

// Draws a line graph showing queue size over time
void GUI::drawGraph() {
    float gX = 12.f;
    float gY = 490.f;
    float gW = 730.f - 24.f;
    float gH = 200.f;

    drawPanel(gX, gY, gW, gH, Style::PURPLE);

    txt("PEAK HOURS TIMELINE (QUEUE SIZE)", gX + 14.f, gY + 10.f, 16, Style::PURPLE);

    // Separator line under graph title
    sf::RectangleShape gdiv({gW - 16.f, 1.f});
    gdiv.setPosition({gX + 8.f, gY + 35.f});
    gdiv.setFillColor(Style::BORDER);
    window.draw(gdiv);

    const std::vector<int>& history = simRef->getQueueHistory();

    // Do not draw graph if there is no history yet
    if (history.empty()) {
        return;
    }

    // Line strip connects all graph points together
    sf::VertexArray graphLines(sf::PrimitiveType::LineStrip);

    // Minimum Y-axis max value is 5, so the graph does not look too flat
    int maxQueueSize = 5;

    for (int q : history) {
        if (q > maxQueueSize) {
            maxQueueSize = q;
        }
    }

    float maxTimeX = simRef->getMaxTime();
    float stepX = (gW - 40.f) / maxTimeX;

    float graphBottom = gY + gH - 20.f;
    float graphHeight = gH - 60.f;

    for (size_t i = 0; i < history.size(); i++) {
        float px = gX + 20.f + (i * stepX);
        float py = graphBottom - ((float)history[i] / maxQueueSize) * graphHeight;

        // Add point to graph line
        graphLines.append({{px, py}, Style::CYAN});

        // Draw a small point on the graph
        sf::CircleShape point(2.f);
        point.setOrigin({2.f, 2.f});
        point.setPosition({px, py});
        point.setFillColor(Style::WHITE);
        window.draw(point);
    }

    window.draw(graphLines);

    // Draw simple graph labels
    txt("Max: " + std::to_string(maxQueueSize), gX + 15.f, gY + 45.f, 12, Style::DIM);
    txt("Time ->", gX + gW - 60.f, graphBottom + 2.f, 12, Style::DIM);
}

// Displays everything drawn on the window
void GUI::refreshDisplay() {
    window.display();
}

// Closes the GUI window
void GUI::closeWindow() {
    window.close();
}

// Returns true if the GUI window is still open
bool GUI::isOpen() const {
    return window.isOpen();
}