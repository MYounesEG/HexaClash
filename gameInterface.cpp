#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include <cstring> // For strcpy
#include "classes.h"
#include "gameInterface.h"

using namespace std;

const int HEX_SIZE = 30.0;  // Size of the hexagon
const float SPACING = 20.0f; // Spacing between hexagons
const int NUM_HEALTH_BARS = 8; // Total number of health bars (4 on each side)

// Function to convert hexagonal grid coordinates (q, r) to pixel coordinates
sf::Vector2f hexToPixel(int q, int r, float offsetX, float offsetY)
{
    float x = HEX_SIZE * 3.0f / 2.0f * q;  // Horizontal distance between hexes
    float y = HEX_SIZE * std::sqrt(3) * r; // Vertical distance between hexes

    // Stagger even rows by shifting x position
    if (q % 2 != 0)
    {
        y += HEX_SIZE * std::sqrt(3) / 2.0f;
    }

    // Apply spacing between hexagons
    x += SPACING * q;
    y += SPACING * r;

    // Centering based on offsets
    x += offsetX;
    y += offsetY;

    return sf::Vector2f(x, y);
}

// Function to create a hexagon shape
sf::CircleShape createHexagon(float x, float y)
{
    sf::CircleShape hexagon(HEX_SIZE, 6); // Create a hexagon shape
    hexagon.setPosition(x, y); // Set its position
    hexagon.setFillColor(sf::Color::Red); // Set its color to red
    hexagon.setOrigin(HEX_SIZE, HEX_SIZE); // Set origin to the center for proper rotation

    // Set the outline color and thickness
    hexagon.setOutlineColor(sf::Color::Black); // Set the outline color to black
    hexagon.setOutlineThickness(2.0f); // Set the outline thickness

    return hexagon;
}

// Function to place an image at a specific grid position
sf::Sprite setImage(int row, int col, const std::string& imageName, float offsetX, float offsetY, float scaleFactor)
{
    sf::Texture* texture = new sf::Texture();
    if (!texture->loadFromFile(imageName))
    {
        throw std::runtime_error("Failed to load image: " + imageName);
    }

    // Create a sprite for the texture
    sf::Sprite sprite;
    sprite.setTexture(*texture);

    // Scale the sprite to fit within the hexagons
    sprite.setScale(scaleFactor, scaleFactor);

    // Get the pixel position for the specified grid row and column
    sf::Vector2f pos = hexToPixel(row, col, offsetX, offsetY);

    // Center the sprite inside the hexagon
    sprite.setPosition(pos.x - (128 * scaleFactor), pos.y - (128 * scaleFactor));

    return sprite;
}


void putImge(int mode, Unit birim, std::vector<sf::Sprite>& images, std::vector<bool>& isEnlarged, float offsetX, float offsetY, float scaleFactor, int Positions[10][10], int extraSpacing)
{
    char imgeName[30] = {0};
    sprintf(imgeName, "images/%s.png", birim.isim);
    int randomX = rand() % (5) + (mode == 1 ? 0 : 5);
    int randomY = rand() % 10;

    for (int i = 0; i < birim.sayi / 100.0; i++)
    {
        while (Positions[randomX][randomY])
        {
            randomX = rand() % (5) + (mode == 1 ? 0 : 5);
            randomY = rand() % 10;
        }

        Positions[randomX][randomY] = 1;

        images.push_back(setImage(randomX, randomY, imgeName, offsetX + (mode == 2 ? extraSpacing : 0), offsetY, scaleFactor));
        isEnlarged.push_back(false); // Initialize the image as not enlarged
    }
}

int grafik(Takim insan_imparatorlugu, Takim ork_legi)
{
    {
        srand(time(0));
        // Create a fullscreen window
        sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Hexagonal Rectangular Grid Game", sf::Style::Fullscreen);

        std::vector<sf::CircleShape> hexagons;

        float offsetX = window.getSize().x / 3.8;  // Shift more to the left
        float offsetY = window.getSize().y / 15;   // Shift more upwards
        float extraSpacing;

        // Generate hexagons in a rectangular grid (10x10)
        for (int q = 0; q < 10; ++q)    // Columns
        {
            for (int r = 0; r < 10; ++r)    // Rows
            {
                extraSpacing = 0.0f;

                if (q >= 5)
                {
                    extraSpacing = 50.0f;  // Adjust this value to control the space between the two sets of rows
                }

                sf::Vector2f pos = hexToPixel(q, r, offsetX + extraSpacing, offsetY);
                hexagons.push_back(createHexagon(pos.x, pos.y)); // Add hexagon to vector
            }
        }

        float hexInnerRadius = HEX_SIZE * std::sqrt(3) / 2.0f;
        float scaleFactor = hexInnerRadius / 128.0f;

        int Positions[10][10] = {0};
        std::vector<sf::Sprite> images;
        std::vector<bool> isEnlarged;

        for (int i = 0; i < insan_imparatorlugu.birimSayisi; i++)
            putImge(1, insan_imparatorlugu.birimler[i], images, isEnlarged, offsetX, offsetY, scaleFactor, Positions, extraSpacing);

        for (int i = 0; i < ork_legi.birimSayisi; i++)
            putImge(2, ork_legi.birimler[i], images, isEnlarged, offsetX, offsetY, scaleFactor, Positions, extraSpacing);

        // Load background image
        sf::Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("images/background_image.png"))
        {
            std::cerr << "Error loading background image" << std::endl;
            return -1;
        }
        sf::Sprite backgroundSprite;
        backgroundSprite.setTexture(backgroundTexture);

        backgroundSprite.setScale(
            window.getSize().x / backgroundSprite.getLocalBounds().width,
            window.getSize().y / backgroundSprite.getLocalBounds().height
        );

        // Load monster image
        sf::Texture monsterTexture;
        if (!monsterTexture.loadFromFile("images/monster_image.png"))
        {
            std::cerr << "Error loading monster image" << std::endl;
            return -1;
        }

        sf::Sprite monsterSprite;
        monsterSprite.setTexture(monsterTexture);
        monsterSprite.setScale(scaleFactor * 2.2f, scaleFactor * 2.2f);

        float monsterPosX = offsetX + window.getSize().x / 1.9f;
        float monsterPosY = offsetY + window.getSize().y / 1.8f;
        monsterSprite.setPosition(monsterPosX, monsterPosY);

        // Split health bars into two vectors (human and orc)
        std::vector<sf::RectangleShape> humanHealthBars(4);
        std::vector<sf::RectangleShape> humanEmptyBars(4);
        std::vector<sf::RectangleShape> orcHealthBars(4);
        std::vector<sf::RectangleShape> orcEmptyBars(4);

        float barWidth = 200.0f;
        float barHeight = 20.0f;
        float barSpacing = 50.0f;

        // List of small images representing each unit's health bar
        std::vector<sf::Sprite> unitIcons(8);
        std::vector<sf::Texture> iconTextures(8);

// Set the position of health bars and icons
        for (int i = 0; i < 8; ++i)
        {
            // Load image representing the unit
            std::string iconPath = "images/"+(std::string)((i<4)?insan_imparatorlugu.birimler[i].isim:ork_legi.birimler[i%4].isim)+".png";
            if (!iconTextures[i].loadFromFile(iconPath))
            {
                std::cerr << "Error loading icon: " << iconPath << std::endl;
                printf("(%s)",(std::string)((i<4)?insan_imparatorlugu.birimler[i].isim:ork_legi.birimler[i%4].isim));
                exit(-1);
            }

            // Set the sprite texture
            unitIcons[i].setTexture(iconTextures[i]);
            unitIcons[i].setScale(0.2f, 0.2f);  // Scale down the icons

            // Determine which vector to use (human or orc)
            std::vector<sf::RectangleShape>& healthBars = (i < 4) ? humanHealthBars : orcHealthBars;
            std::vector<sf::RectangleShape>& emptyBars = (i < 4) ? humanEmptyBars : orcEmptyBars;

            // Get health from team members
            float healthValue = ((i < 4) ? insan_imparatorlugu.birimler[i].sayi : ork_legi.birimler[i - 4].sayi) / 230.0 * 100;   /////////////////////////////////////////
            printf("%f\n",healthValue);
            // Set the size and color of the filled portion of the health bar
            healthBars[i % 4].setSize(sf::Vector2f(barWidth, barHeight));

            if (healthValue > 50)
                healthBars[i % 4].setFillColor(sf::Color(0, 255, 47)); // Green for high health
            else if (healthValue > 20)
                healthBars[i % 4].setFillColor(sf::Color(234, 255, 0)); // Yellow for mid health
            else
                healthBars[i % 4].setFillColor(sf::Color(255, 0, 4)); // Red for low health

            emptyBars[i % 4].setSize(sf::Vector2f(barWidth, barHeight));
            emptyBars[i % 4].setFillColor(sf::Color(128, 128, 128));

            healthBars[i % 4].setOutlineColor(sf::Color::Black);
            healthBars[i % 4].setOutlineThickness(2.0f);

            emptyBars[i % 4].setOutlineColor(sf::Color::Black);
            emptyBars[i % 4].setOutlineThickness(2.0f);

            // Position the health bars and icons
            if (i >= 4)  // Now place orc health bars on the right side
            {
                float barX = window.getSize().x - barWidth - 45;
                float barY = offsetY + (i - 4) * (barHeight + barSpacing);

                healthBars[i % 4].setPosition(barX, barY);
                emptyBars[i % 4].setPosition(barX, barY);

                // Position the icon next to the health bar
                unitIcons[i].setPosition(barX - 60, barY - 20); // Adjust as needed
            }
            else  // Place human health bars on the left side
            {
                float barX = 45;
                float barY = offsetY + i * (barHeight + barSpacing);

                healthBars[i % 4].setPosition(barX, barY);
                emptyBars[i % 4].setPosition(barX, barY);

                unitIcons[i].setPosition(barX + 210, barY - 20); // Adjust as needed
            }

            // Adjust the size of the health bar based on the unit's health percentage
            healthBars[i % 4].setSize(sf::Vector2f((healthValue / 100.0) * barWidth, barHeight));/////////////////////////////////////////////////////////////
        }

        while (window.isOpen())
        {
            window.clear();

            window.draw(backgroundSprite);

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                        for (std::size_t i = 0; i < images.size(); ++i)
                        {
                            sf::Sprite& image = images[i];

                            if (image.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                            {
                                if (isEnlarged[i])
                                {
                                    image.setScale(image.getScale().x / 3.0f, image.getScale().y / 3.0f);
                                    isEnlarged[i] = false;
                                }
                                else
                                {
                                    image.setScale(image.getScale().x * 3.0f, image.getScale().y * 3.0f);
                                    isEnlarged[i] = true;
                                }
                            }
                        }
                    }
                }

                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        window.close();
                    }
                }
            }

            for (const auto& hexagon : hexagons)
            {
                window.draw(hexagon); // Draw hexagons on the screen
            }

            for (const auto& image : images)
            {
                window.draw(image); // Draw images on the screen
            }

            window.draw(monsterSprite); // Draw the monster

            // Draw human health bars
            for (int i = 0; i < 4; ++i)
            {
                window.draw(humanEmptyBars[i]);
                window.draw(humanHealthBars[i]);
                window.draw(unitIcons[i]);
            }

            // Draw orc health bars
            for (int i = 0; i < 4; ++i)
            {
                window.draw(orcEmptyBars[i]);
                window.draw(orcHealthBars[i]);
                window.draw(unitIcons[i + 4]);
            }

            window.display();
        }
    }
    return 0;
}

