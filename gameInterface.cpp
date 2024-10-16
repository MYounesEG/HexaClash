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

    for (int i = 0; i < birim.sayi / 100; i++)
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



int grafik(Takim insan_imparatorlugu,Takim ork_legi)
{
    {
        srand(time(0));
        // Create a fullscreen window
        sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Hexagonal Rectangular Grid Game", sf::Style::Fullscreen);

        std::vector<sf::CircleShape> hexagons;

        // Reduce offsetX and offsetY more to push grid to the top-left corner
        float offsetX = window.getSize().x / 3.8;  // Shift more to the left
        float offsetY = window.getSize().y / 15;  // Shift more upwards
        float extraSpacing;
        // Generate hexagons in a rectangular grid (10x10)
// Generate hexagons in a rectangular grid (10x10)
        for (int q = 0; q < 10; ++q)    // Columns
        {
            for (int r = 0; r < 10; ++r)    // Rows
            {
                extraSpacing = 0.0f;

                // Add extra spacing after the 5th row
                if (q >= 5)
                {
                    extraSpacing = 50.0f;  // Adjust this value to control the space between the two sets of rows
                }

                // Calculate the hexagon's position with the additional spacing applied
                sf::Vector2f pos = hexToPixel(q, r, offsetX + extraSpacing, offsetY);
                hexagons.push_back(createHexagon(pos.x, pos.y)); // Add hexagon to vector
            }
        }


        // Load multiple PNG images for the sprites
        float hexInnerRadius = HEX_SIZE * std::sqrt(3) / 2.0f;  // Inner radius of the hexagon (height-wise)
        float scaleFactor = hexInnerRadius / 128.0f;  // Assume original size of the image is 256x256 pixels






        int Positions[10][10] = {0};
        std::vector<sf::Sprite> images;
        std::vector<bool> isEnlarged;  // Track whether each image is enlarged

        for (int i = 0; i < insan_imparatorlugu.birimSayisi; i++)
            putImge(1, insan_imparatorlugu.birimler[i], images, isEnlarged, offsetX, offsetY, scaleFactor, Positions, extraSpacing);



        for (int i = 0; i < ork_legi.birimSayisi; i++)
            putImge(2, ork_legi.birimler[i], images, isEnlarged, offsetX, offsetY, scaleFactor, Positions, extraSpacing);

        // Load the background image
        sf::Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("images/background_image.png"))
        {
            std::cerr << "Error loading background image" << std::endl;
            return -1;
        }
        sf::Sprite backgroundSprite;
        backgroundSprite.setTexture(backgroundTexture);

        // Scale the background to fit the window
        backgroundSprite.setScale(
            window.getSize().x / backgroundSprite.getLocalBounds().width,
            window.getSize().y / backgroundSprite.getLocalBounds().height
        );

        // set monester image !!!
        sf::Texture monsterTexture;
        if (!monsterTexture.loadFromFile("images/monster_image.png"))
        {
            std::cerr << "Error loading monster image" << std::endl;
            return -1;
        }

        // Create a sprite for the monster and position it outside the grid
        sf::Sprite monsterSprite;
        monsterSprite.setTexture(monsterTexture);

        // Make the monster image bigger by adjusting the scale factor
        monsterSprite.setScale(scaleFactor * 2.2f, scaleFactor * 2.2f);  // Double the size of the monster

        // Position the monster to the right of the grid (adjust offset as needed)
        float monsterPosX = offsetX + window.getSize().x / 1.8f; // Position the monster further to the right
        float monsterPosY = offsetY + window.getSize().y / 2.5f; // Adjust the Y position as needed

        monsterSprite.setPosition(monsterPosX, monsterPosY);



// Health bar variables
        std::vector<sf::RectangleShape> healthBars(NUM_HEALTH_BARS);
        std::vector<sf::RectangleShape> emptyBars(NUM_HEALTH_BARS); // Empty part of the health bar

        std::vector<int> healths = {10,80,50,90,60,25,40,16};

        float barWidth = 200.0f;
        float barHeight = 20.0f;
        float barSpacing = 50.0f;  // Increased spacing between health bars

        for (int i = 0; i < NUM_HEALTH_BARS; ++i)
        {
            // Set the size and color of the filled portion of the health bar
            healthBars[i].setSize(sf::Vector2f(barWidth, barHeight)); // Set size of the health bar

            if (healths[i]>50)
                healthBars[i].setFillColor(sf::Color(0, 255, 47)); // Set health bar color to green
            else if(healths[i]>20)
                healthBars[i].setFillColor(sf::Color(234, 255, 0)); // Set health bar color to yellow
            else
                healthBars[i].setFillColor(sf::Color(255, 0, 4)); // Set health bar color to red

            // Set the size and color of the empty portion of the health bar
            emptyBars[i].setSize(sf::Vector2f(barWidth, barHeight)); // Same size as the health bar
            emptyBars[i].setFillColor(sf::Color(128, 128, 128)); // Gray color for the empty portion

            // Add outline to health bars
            healthBars[i].setOutlineColor(sf::Color::Black); // Set outline color to black
            healthBars[i].setOutlineThickness(2.0f); // Set outline thickness to 2 pixels

            // Add outline to empty bars as well
            emptyBars[i].setOutlineColor(sf::Color::Black);
            emptyBars[i].setOutlineThickness(2.0f);

            if (i < 4)
            {
                // Position the first 4 health bars on the right
                float barX = window.getSize().x - barWidth - 50; // 50 px padding from the right side
                float barY = offsetY + i * (barHeight + barSpacing); // Stack health bars with spacing

                healthBars[i].setPosition(barX, barY);
                emptyBars[i].setPosition(barX, barY);
            }
            else
            {
                // Position the remaining 4 health bars on the left
                float barX = 50;  // 50 px padding from the left side
                float barY = offsetY + (i - 4) * (barHeight + barSpacing); // Stack health bars with spacing

                healthBars[i].setPosition(barX, barY);
                emptyBars[i].setPosition(barX, barY);
            }

            // Change the size for health bars
            healthBars[i].setSize(sf::Vector2f((healths[i])/100.0 * barWidth, barHeight)); // Set health

        }

        while (window.isOpen())
        {
            window.clear(); // Clear the window before drawing

            // Draw the background
            window.draw(backgroundSprite);

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                // Detect mouse click
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        // Get mouse position
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                        // Loop through all images to check for collision with the mouse
                        for (std::size_t i = 0; i < images.size(); ++i)
                        {
                            sf::Sprite& image = images[i];

                            // Check if the mouse is inside the bounds of the sprite
                            if (image.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                            {
                                if (isEnlarged[i])
                                {
                                    // If already enlarged, reset to normal size
                                    image.setScale(image.getScale().x / 3.0f, image.getScale().y / 3.0f);
                                    isEnlarged[i] = false; // Mark as not enlarged
                                }
                                else
                                {
                                    // If not enlarged, increase the sprite size
                                    image.setScale(image.getScale().x * 3.0f, image.getScale().y * 3.0f);
                                    isEnlarged[i] = true; // Mark as enlarged
                                }
                            }
                        }
                    }
                }


                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                      //  system("taskkill /im OpenConsole.exe /f");
                        window.close();
                        return 0;
                    }
                }
            }


            // Draw hexagons
            for (const auto& hexagon : hexagons)
            {
                window.draw(hexagon);
            }

            // Draw sprites at the hexagons
            for (const sf::Sprite& image : images)
            {
                window.draw(image);
            }


            // Draw the monster sprite
            window.draw(monsterSprite);


            // Draw the empty gray bars first, then draw the filled health bars on top
            for (int i = 0; i < NUM_HEALTH_BARS; ++i)
            {
                window.draw(emptyBars[i]);  // Draw the empty gray bar first
                window.draw(healthBars[i]); // Draw the filled portion on top
            }

            window.display(); // Display everything
        }


        return 0;
    }
}

