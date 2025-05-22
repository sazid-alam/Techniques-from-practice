#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <vector>

// Check if a shape's bounds intersect any walls
bool checkCollision(const sf::FloatRect& bounds, const std::vector<sf::RectangleShape>& walls) {
    for (const auto& wall : walls) {
        if (bounds.intersects(wall.getGlobalBounds())) {
            return true;
        }
    }
    return false;
}

// Generate a valid enemy spawn position (not inside walls)
sf::Vector2f getValidEnemySpawn(const std::vector<sf::RectangleShape>& walls, float enemyRadius, int windowWidth, int windowHeight) {
    sf::CircleShape tempEnemy(enemyRadius);
    int maxTries = 100;

    for (int i = 0; i < maxTries; ++i) {
        float x = static_cast<float>(std::rand() % (windowWidth - static_cast<int>(enemyRadius * 2)));
        float y = static_cast<float>(std::rand() % (windowHeight - static_cast<int>(enemyRadius * 2)));

        tempEnemy.setPosition(x, y);
        if (!checkCollision(tempEnemy.getGlobalBounds(), walls)) {
            return sf::Vector2f(x, y);
        }
    }

    // Default fallback position
    return sf::Vector2f(50.f, 50.f);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Walls, Collision, Constant Enemy");
    window.setFramerateLimit(60);
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Load player texture
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("sprite.png")) {
        return -1;
    }

    sf::Sprite player(playerTexture);
    player.setScale(0.2f, 0.2f);
    player.setPosition(100.f, 100.f);
    float playerSpeed = 5.f;

    // Create walls
    std::vector<sf::RectangleShape> walls;

    sf::RectangleShape wall1(sf::Vector2f(20.f, 400.f));
    wall1.setPosition(200.f, 100.f);
    wall1.setFillColor(sf::Color::Blue);
    walls.push_back(wall1);

    sf::RectangleShape wall2(sf::Vector2f(400.f, 20.f));
    wall2.setPosition(200.f, 400.f);
    wall2.setFillColor(sf::Color::Blue);
    walls.push_back(wall2);

    sf::RectangleShape wall3(sf::Vector2f(20.f, 200.f));
    wall3.setPosition(500.f, 200.f);
    wall3.setFillColor(sf::Color::Blue);
    walls.push_back(wall3);

    // Enemy setup
    float enemyRadius = 30.f;
    sf::CircleShape enemy(enemyRadius);
    enemy.setFillColor(sf::Color::Red);
    enemy.setPosition(getValidEnemySpawn(walls, enemyRadius, 800, 600));
    sf::Vector2f enemyVelocity(4.f, 4.f); // Constant velocity

    // Score setup
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }

    int score = 0;
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 10.f);
    scoreText.setString("Score: 0");

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        // Handle player movement
        sf::FloatRect playerBounds = player.getGlobalBounds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            sf::FloatRect next = playerBounds;
            next.left -= playerSpeed;
            if (!checkCollision(next, walls))
                player.move(-playerSpeed, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            sf::FloatRect next = playerBounds;
            next.left += playerSpeed;
            if (!checkCollision(next, walls))
                player.move(playerSpeed, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            sf::FloatRect next = playerBounds;
            next.top -= playerSpeed;
            if (!checkCollision(next, walls))
                player.move(0.f, -playerSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            sf::FloatRect next = playerBounds;
            next.top += playerSpeed;
            if (!checkCollision(next, walls))
                player.move(0.f, playerSpeed);
        }

        // Clamp player inside window
        sf::Vector2f pos = player.getPosition();
        sf::FloatRect bounds = player.getGlobalBounds();
        if (pos.x < 0) pos.x = 0;
        if (pos.x + bounds.width > 800) pos.x = 800 - bounds.width;
        if (pos.y < 0) pos.y = 0;
        if (pos.y + bounds.height > 600) pos.y = 600 - bounds.height;
        player.setPosition(pos);

        // Enemy movement with wall collision check
        sf::FloatRect enemyBounds = enemy.getGlobalBounds();

        sf::FloatRect nextX = enemyBounds;
        nextX.left += enemyVelocity.x;
        if (checkCollision(nextX, walls))
            enemyVelocity.x = -enemyVelocity.x;

        sf::FloatRect nextY = enemyBounds;
        nextY.top += enemyVelocity.y;
        if (checkCollision(nextY, walls))
            enemyVelocity.y = -enemyVelocity.y;

        enemy.move(enemyVelocity);

        // Bounce off window edges
        if (enemy.getPosition().x <= 0 || enemy.getPosition().x + enemyRadius * 2 >= 800)
            enemyVelocity.x = -enemyVelocity.x;
        if (enemy.getPosition().y <= 0 || enemy.getPosition().y + enemyRadius * 2 >= 600)
            enemyVelocity.y = -enemyVelocity.y;

        // Collision: player vs. enemy
        if (player.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
            score++;
            std::stringstream ss;
            ss << "Score: " << score;
            scoreText.setString(ss.str());

            enemy.setPosition(getValidEnemySpawn(walls, enemyRadius, 800, 600));
            enemyVelocity = sf::Vector2f(4.f, 4.f); // Fixed speed after respawn
        }

        // Draw everything
        window.clear();
        for (const auto& wall : walls)
            window.draw(wall);
        window.draw(enemy);
        window.draw(player);
        window.draw(scoreText);
        window.display();
    }

    return 0;
}
