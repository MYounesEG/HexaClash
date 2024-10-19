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

// Main function to draw the grid and health bars
void grafik(Takim insan_imparatorlugu, Takim ork_legi)
{
    srand(time(0));

    // Create a fullscreen window
    sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Hexagonal Rectangular Grid Game", sf::Style::Fullscreen);

    std::vector<sf::CircleShape> hexagons;
    float offsetX = window.getSize().x / 3.8;
    float offsetY = window.getSize().y / 15;
    float extraSpacing;

    // Generate hexagons in a rectangular grid (10x10)
    for (int q = 0; q < 10; ++q)
    {
        for (int r = 0; r < 10; ++r)
        {
            extraSpacing = (q >= 5) ? 50.0f : 0.0f;
            sf::Vector2f pos = hexToPixel(q, r, offsetX + extraSpacing, offsetY);
            hexagons.push_back(createHexagon(pos.x, pos.y));
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
        return;
    }
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        window.getSize().x / backgroundSprite.getLocalBounds().width,
        window.getSize().y / backgroundSprite.getLocalBounds().height
    );


    std::vector<sf::Sprite> mainCharacters;
    sf::Texture heroTextureOrkLegi;
    sf::Texture monsterTextureOrkLegi;
    sf::Texture heroTextureInsanImparatorlugu;
    sf::Texture monsterTextureInsanImparatorlugu;

    float characterPosX, characterPosY;

    // Load images for ork_legi
    std::string orkHeroImagePath = "images/" + (std::string)ork_legi.kahramanlar[0].isim + ".png";
    std::string orkMonsterImagePath = "images/" + (std::string)ork_legi.canavarlar[0].isim + ".png";

    // Load hero for ork_legi
    if (!heroTextureOrkLegi.loadFromFile(orkHeroImagePath)) {
        std::cerr << "Error loading " + orkHeroImagePath + " image" << std::endl;
        return;
    }

    sf::Sprite orkHeroSprite;
    orkHeroSprite.setTexture(heroTextureOrkLegi);
    orkHeroSprite.setScale(scaleFactor * 2.2f, scaleFactor * 2.2f);
    orkHeroSprite.setPosition(offsetX + 600, offsetY + 350);
    mainCharacters.push_back(orkHeroSprite);

    // Load monster for ork_legi
    if (!monsterTextureOrkLegi.loadFromFile(orkMonsterImagePath)) {
        std::cerr << "Error loading " + orkMonsterImagePath + " image" << std::endl;
        return;
    }

    sf::Sprite orkMonsterSprite;
    orkMonsterSprite.setTexture(monsterTextureOrkLegi);
    orkMonsterSprite.setScale(scaleFactor * 2.2f, scaleFactor * 2.2f);
    orkMonsterSprite.setPosition(offsetX + 700.0f, offsetY + 170); // Adjust position
    mainCharacters.push_back(orkMonsterSprite);

    // Load images for insan_imparatorlugu
    std::string insanHeroImagePath = "images/" + (std::string)insan_imparatorlugu.kahramanlar[0].isim + ".png";
    std::string insanMonsterImagePath = "images/" + (std::string)insan_imparatorlugu.canavarlar[0].isim + ".png";

    // Load hero for insan_imparatorlugu
    if (!heroTextureInsanImparatorlugu.loadFromFile(insanHeroImagePath)) {
        std::cerr << "Error loading " + insanHeroImagePath + " image" << std::endl;
        return;
    }

    sf::Sprite insanHeroSprite;
    insanHeroSprite.setTexture(heroTextureInsanImparatorlugu);
    insanHeroSprite.setScale(scaleFactor * 2.2f, scaleFactor * 2.2f);
    insanHeroSprite.setPosition(offsetX - 400, offsetY + 350.0f); // Adjust position
    mainCharacters.push_back(insanHeroSprite);

    // Load monster for insan_imparatorlugu
    if (!monsterTextureInsanImparatorlugu.loadFromFile(insanMonsterImagePath)) {
        std::cerr << "Error loading " + insanMonsterImagePath + " image" << std::endl;
        return;
    }

    sf::Sprite insanMonsterSprite;
    insanMonsterSprite.setTexture(monsterTextureInsanImparatorlugu);
    insanMonsterSprite.setScale(scaleFactor * 2.2f, scaleFactor * 2.2f);
    insanMonsterSprite.setPosition(offsetX - 450.0f, offsetY + 170); // Adjust position
    mainCharacters.push_back(insanMonsterSprite);








    // Split health bars into two vectors (human and orc)
    std::vector<sf::RectangleShape> humanHealthBars(4);
    std::vector<sf::RectangleShape> humanEmptyBars(4);
    std::vector<sf::RectangleShape> orcHealthBars(4);
    std::vector<sf::RectangleShape> orcEmptyBars(4);

    float barWidth = 200.0f;
    float barHeight = 20.0f;
    float barSpacing = 50.0f;

    // Load a font for health percentage text
    sf::Font font;
    if (!font.loadFromFile("fonts/arial.ttf"))
    {
        std::cerr << "Error loading font" << std::endl;
        return;
    }

    // Create health percentage texts
    std::vector<sf::Text> healthTexts(8);  // 4 for human, 4 for orc
    std::vector<sf::Sprite> unitIcons(8);
    std::vector<sf::Texture> iconTextures(8);

    for (int i = 0; i < 8; ++i)
    {
        std::string iconPath = "images/" + (std::string)((i < 4) ? insan_imparatorlugu.birimler[i].isim : ork_legi.birimler[i % 4].isim) + ".png";
        if (!iconTextures[i].loadFromFile(iconPath))
        {
            std::cerr << "Error loading icon: " << iconPath << std::endl;
            return;
        }

        // Set the sprite texture and scale
        unitIcons[i].setTexture(iconTextures[i]);
        unitIcons[i].setScale(0.2f, 0.2f);

        float healthValue = ((i < 4) ? insan_imparatorlugu.birimler[i].sayi : ork_legi.birimler[i - 4].sayi) / 230.0 * 100;
        healthTexts[i].setFont(font);
        healthTexts[i].setString(std::to_string(static_cast<int>(healthValue)) + "%"); // Display health as percentage
        healthTexts[i].setCharacterSize(18);
        healthTexts[i].setFillColor(sf::Color::White);

        // Determine bar positions and text alignment
        std::vector<sf::RectangleShape>& healthBars = (i < 4) ? humanHealthBars : orcHealthBars;
        std::vector<sf::RectangleShape>& emptyBars = (i < 4) ? humanEmptyBars : orcEmptyBars;

        healthBars[i % 4].setSize(sf::Vector2f((healthValue / 100.0) * barWidth, barHeight));
        healthBars[i % 4].setFillColor((healthValue > 50) ? sf::Color(0, 255, 47) : (healthValue > 20) ? sf::Color(234, 255, 0) : sf::Color(255, 0, 4));
        healthBars[i % 4].setOutlineColor(sf::Color::Black);
        healthBars[i % 4].setOutlineThickness(2.0f);

        emptyBars[i % 4].setSize(sf::Vector2f(barWidth, barHeight));
        emptyBars[i % 4].setFillColor(sf::Color(128, 128, 128));
        emptyBars[i % 4].setOutlineColor(sf::Color::Black);
        emptyBars[i % 4].setOutlineThickness(2.0f);

        if (i >= 4)  // Orc side
        {
            float barX = window.getSize().x - barWidth - 45;
            float barY = offsetY + (i - 4) * (barHeight + barSpacing);
            healthBars[i % 4].setPosition(barX, barY);
            emptyBars[i % 4].setPosition(barX, barY);
            unitIcons[i].setPosition(barX - 60, barY - 20);
            healthTexts[i].setPosition(barX + barWidth / 2 - 15, barY - 25);
        }
        else  // Human side
        {
            float barX = 45;
            float barY = offsetY + i * (barHeight + barSpacing);
            healthBars[i % 4].setPosition(barX, barY);
            emptyBars[i % 4].setPosition(barX, barY);
            unitIcons[i].setPosition(barX + 210, barY - 20);
            healthTexts[i].setPosition(barX + barWidth / 2 - 15, barY - 25);
        }
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
                    for (int i = 0; i < images.size(); ++i)
                    {
                        sf::Sprite& image = images[i];
                        if (image.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                        {
                            if (isEnlarged[i])
                            {
                                image.setScale(image.getScale().x / 3.5f, image.getScale().y / 3.5f);
                                isEnlarged[i] = false;
                            }
                            else
                            {
                                image.setScale(image.getScale().x * 3.5f, image.getScale().y * 3.5f);
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
                else if (event.key.code == sf::Keyboard::Space)
                {
                    window.close();
                    grafik(insan_imparatorlugu,ork_legi);
                    return;
                }
            }
        }

        // Draw human health bars and texts
        for (int i = 0; i < 4; ++i)
        {
            window.draw(humanEmptyBars[i]);
            window.draw(humanHealthBars[i]);
            window.draw(unitIcons[i]);
            window.draw(healthTexts[i]);  // Draw health percentage
        }

        // Draw orc health bars and texts
        for (int i = 0; i < 4; ++i)
        {
            window.draw(orcEmptyBars[i]);
            window.draw(orcHealthBars[i]);
            window.draw(unitIcons[i + 4]);
            window.draw(healthTexts[i + 4]);  // Draw health percentage
        }

        for (const auto& hexagon : hexagons)
        {
            window.draw(hexagon); // Draw hexagons
        }

        for (const auto& image : images)
        {
            window.draw(image); // Draw images
        }

        for(int i=mainCharacters.size()-1;i>=0;i--)
        {
            window.draw(mainCharacters[i]); // Draw every kahraman/canavar image
        }

        window.display();
    }

    return;
}


