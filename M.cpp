//M.cpp
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include <cstring> // For strcpy
#include <ctime> // For time(0)
#include "classes.h"
#include "gameInterface.h"

using namespace sf;
using namespace std;


// Constants for hexagon size and spacing
const float HEX_SIZE = 30.0f;
const float SPACING = 20.0f;

// Convert hexagonal grid coordinates to pixel coordinates
Vector2f hexToPixel(int q, int r, float offsetX, float offsetY, float hexSize, float spacing)
{
    float x = hexSize * 3.0f / 2.0f * q;   // Horizontal distance
    float y = hexSize * sqrt(3) * r;       // Vertical distance

    // Stagger for odd rows
    if (q % 2 != 0) y += hexSize * sqrt(3) / 2.0f;

    // Apply spacing and offsets
    x += spacing * q + offsetX;
    y += spacing * r + offsetY;

    return Vector2f(x, y);
}

// Create a hexagonal shape
CircleShape createHexagon(float x, float y, float hexSize)
{
    CircleShape hexagon(hexSize, 6); // Hexagon shape
    hexagon.setPosition(x, y);
    hexagon.setFillColor(Color::Red);
    hexagon.setOrigin(hexSize, hexSize);
    hexagon.setOutlineColor(Color::Black);
    hexagon.setOutlineThickness(2.0f);
    return hexagon;
}

// Load and place an image at a specific grid position
Sprite loadImageAt(int row, int col, const string imageName, float offsetX, float offsetY, float scaleFactor, float hexSize, float spacing)
{
    Texture* texture = new Texture();
    if (!texture->loadFromFile(imageName)) throw runtime_error("Failed to load image: " + imageName);

    Sprite sprite;
    sprite.setTexture(*texture);
    sprite.setScale(scaleFactor, scaleFactor);

    Vector2f pos = hexToPixel(row, col, offsetX, offsetY, hexSize, spacing);
    sprite.setPosition(pos.x - (128 * scaleFactor), pos.y - (128 * scaleFactor));

    return sprite;
}

// Place unit images on the grid
void placeUnits(int teamMode, Unit unit, vector<Sprite>& unitImages, vector<bool>& isEnlarged, float offsetX, float offsetY, float scaleFactor, int positions[10][10], float hexSize, float spacing, float extraSpacing)
{
    char imageName[30] = {0};
    sprintf(imageName, "images/%s.png", unit.isim);

    int randomX = rand() % 5 + (teamMode == 1 ? 0 : 5); // Random position based on team
    int randomY = rand() % 10;

    for (int i = 0; i < unit.sayi / 100.0; i++)
    {
        while (positions[randomX][randomY])
        {
            randomX = rand() % 5 + (teamMode == 1 ? 0 : 5);
            randomY = rand() % 10;
        }

        positions[randomX][randomY] = 1; // Mark position as taken

        // Add image to vector
        unitImages.push_back(loadImageAt(randomX, randomY, imageName, offsetX + (teamMode == 2 ? extraSpacing + 10 : 10), offsetY, scaleFactor, hexSize, spacing));
        isEnlarged.push_back(false);
    }
}

// Main game interface function
void renderInterface(Takim insan_imparatorlugu, Takim ork_legi)
{
    srand(time(0));

    RenderWindow window(VideoMode::getFullscreenModes()[0], "Hexagonal Grid Game", Style::Fullscreen);

    // Adjust based on screen size
    float hexSize = window.getSize().y / 25.0f;
    float spacing = hexSize * 0.6f;
    float offsetX = window.getSize().x / 3.8;
    float offsetY = window.getSize().y / 15;

    vector<CircleShape> hexagons;
    float extraSpacing;

    // Create a 10x10 grid of hexagons
    for (int q = 0; q < 10; ++q)
    {
        for (int r = 0; r < 10; ++r)
        {
            extraSpacing = (q >= 5) ? 70.0f : 0.0f;
            Vector2f pos = hexToPixel(q, r, offsetX + extraSpacing + 10, offsetY, hexSize, spacing);
            hexagons.push_back(createHexagon(pos.x, pos.y, hexSize));
        }
    }

    // Setup scaling and positioning for units
    float hexInnerRadius = hexSize * sqrt(3) / 2.0f;
    float scaleFactor = hexInnerRadius / 128.0f;

    int positions[10][10] = {0}; // Position tracker for units
    vector<Sprite> unitImages;
    vector<bool> isEnlarged;

    // Place human and orc units on the grid
    for (int i = 0; i < insan_imparatorlugu.birimSayisi; i++) placeUnits(1, insan_imparatorlugu.birimler[i], unitImages, isEnlarged, offsetX, offsetY, scaleFactor, positions, hexSize, spacing, extraSpacing);
    for (int i = 0; i < ork_legi.birimSayisi; i++) placeUnits(2, ork_legi.birimler[i], unitImages, isEnlarged, offsetX, offsetY, scaleFactor, positions, hexSize, spacing, extraSpacing);

    // Load background
    Texture bgTexture;
    if (!bgTexture.loadFromFile("images/background_image.png"))
    {
        cerr << "Error loading background image" << endl;
        return;
    }
    Sprite bgSprite;
    bgSprite.setTexture(bgTexture);
    bgSprite.setScale(window.getSize().x / bgSprite.getLocalBounds().width, window.getSize().y / bgSprite.getLocalBounds().height);
    vector<Sprite> mainCharacters;
    // Load heroes and monsters
    vector<string> orkImagePaths = {"images/" + string(ork_legi.kahramanlar[0].isim) + ".png", "images/" + string(ork_legi.canavarlar[0].isim) + ".png"};
    vector<string> humanImagePaths = {"images/" + string(insan_imparatorlugu.kahramanlar[0].isim) + ".png", "images/" + string(insan_imparatorlugu.canavarlar[0].isim) + ".png"};

    Texture orkHeroTexture, orkMonsterTexture, humanHeroTexture, humanMonsterTexture;
    Sprite orkHeroSprite, orkMonsterSprite, humanHeroSprite, humanMonsterSprite;

    if(ork_legi.kahramanSayisi)
    {

        // Ork monster
        if (!orkMonsterTexture.loadFromFile(orkImagePaths[1]))
        {
            cerr << "Error loading " + orkImagePaths[1] + " image" << endl;
            return;
        }
        orkMonsterSprite.setTexture(orkMonsterTexture);
        orkMonsterSprite.setScale(scaleFactor * 2.2f, scaleFactor * 2.2f);
        orkMonsterSprite.setPosition(window.getSize().x - 500, offsetY + 150);
        mainCharacters.push_back(orkMonsterSprite);


        // Ork hero
        if (!orkHeroTexture.loadFromFile(orkImagePaths[0]))
        {
            cerr << "Error loading " + orkImagePaths[0] + " image" << endl;
            return;
        }
        orkHeroSprite.setTexture(orkHeroTexture);
        orkHeroSprite.setScale(scaleFactor * 2.2f, scaleFactor * 2.2f);
        orkHeroSprite.setPosition(window.getSize().x - 500, offsetY + 500);
        mainCharacters.push_back(orkHeroSprite);

    }
    if(insan_imparatorlugu.kahramanSayisi)
    {

        // Human monster
        if (!humanMonsterTexture.loadFromFile(humanImagePaths[1]))
        {
            cerr << "Error loading " + humanImagePaths[1] + " image" << endl;
            return;
        }
        humanMonsterSprite.setTexture(humanMonsterTexture);
        humanMonsterSprite.setScale(scaleFactor * 2.2f, scaleFactor * 2.2f);
        humanMonsterSprite.setPosition(offsetX - 550, offsetY + 150);
        mainCharacters.push_back(humanMonsterSprite);


        // Human hero
        if (!humanHeroTexture.loadFromFile(humanImagePaths[0]))
        {
            cerr << "Error loading " + humanImagePaths[0] + " image" << endl;
            return;
        }
        humanHeroSprite.setTexture(humanHeroTexture);
        humanHeroSprite.setScale(scaleFactor * 2.2f, scaleFactor * 2.2f);
        humanHeroSprite.setPosition(offsetX - 550, offsetY + 500);
        mainCharacters.push_back(humanHeroSprite);
    }





    // Load a font for health percentage text
    Font font;
    if (!font.loadFromFile("fonts/arial.ttf"))
    {
        cerr << "Error loading font" << endl;
        return;
    }


    // Create health percentage texts
    vector<Text> humanHealthTexts(insan_imparatorlugu.birimSayisi);  // 4 for human, 4 for orc
    vector<Sprite> humanUnitIcons(insan_imparatorlugu.birimSayisi);
    vector<Texture> humanIconTextures(insan_imparatorlugu.birimSayisi);
    vector<Text> orcHealthTexts(ork_legi.birimSayisi);  // 4 for human, 4 for orc
    vector<Sprite> orcUnitIcons(ork_legi.birimSayisi);
    vector<Texture> orcIconTextures(ork_legi.birimSayisi);

    for (int i = 0; i < insan_imparatorlugu.birimSayisi; ++i)
    {
        string humanIconPath = "images/" + (string)(insan_imparatorlugu.birimler[i].isim) + ".png";
        string orcIconPath = "images/" + (string)(ork_legi.birimler[i].isim) + ".png";
        if (!humanIconTextures[i].loadFromFile(humanIconPath))
        {
            cerr << "Error loading icon: " << humanIconPath << endl;
            return;
        }
        if (!orcIconTextures[i].loadFromFile(orcIconPath))
        {
            cerr << "Error loading icon: " << orcIconPath << endl;
            return;
        }

        // Set the sprite texture and scale
        humanUnitIcons[i].setTexture(humanIconTextures[i]);
        humanUnitIcons[i].setScale(0.2f, 0.2f);

        humanHealthTexts[i].setFont(font);
        humanHealthTexts[i].setString("%"+to_string((int)(insan_imparatorlugu.birimler[i].saglik*100/insan_imparatorlugu.birimler[i].orjinal_saglik))); // Display health as percentage
        humanHealthTexts[i].setCharacterSize(18);
        humanHealthTexts[i].setFillColor(Color::Black);

        // Set the sprite texture and scale
        orcUnitIcons[i].setTexture(orcIconTextures[i]);
        orcUnitIcons[i].setScale(0.2f, 0.2f);

        orcHealthTexts[i].setFont(font);
        orcHealthTexts[i].setString("%"+to_string(((int)(ork_legi.birimler[i].saglik*100/ork_legi.birimler[i].orjinal_saglik)))); // Display health as percentage
        orcHealthTexts[i].setCharacterSize(18);
        orcHealthTexts[i].setFillColor(Color::Black);

    }



    // Health bars setup
    vector<RectangleShape> humanHealthBars(insan_imparatorlugu.birimSayisi), humanEmptyBars(insan_imparatorlugu.birimSayisi), orcHealthBars(ork_legi.birimSayisi), orcEmptyBars(ork_legi.birimSayisi);
    float barWidth = 300.0f*1.15, barHeight = 20.0f*1.45, barSpacing = 60.0f;
    float humanHealth,orcHealth;
    // Health bar and unit image setup loop
    for (int i = 0; i < insan_imparatorlugu.birimSayisi; ++i)
    {
        float yOffset = 300.0f + i * barSpacing;

        // Calculate health percentage
        humanHealth = (insan_imparatorlugu.birimler[i].saglik) /
                      (insan_imparatorlugu.birimler[i].orjinal_saglik);
        orcHealth = (ork_legi.birimler[i].saglik) /
                    (ork_legi.birimler[i].orjinal_saglik);

        if(!humanHealth)humanHealth=0.02; // gosteris
        if(!orcHealth)orcHealth=0.02; // gosteris

        // Set colors based on health percentage
        humanHealthBars[i].setFillColor(humanHealth > 0.5 ? Color::Green : (humanHealth > 0.2 ? Color::Yellow : Color::Red));
        orcHealthBars[i].setFillColor(orcHealth > 0.5 ? Color::Green : (orcHealth > 0.2 ? Color::Yellow : Color::Red));

        // Set size and position for health and empty bars (after setting the color)
        humanHealthBars[i].setSize(Vector2f(barWidth * humanHealth, barHeight));
        humanEmptyBars[i].setSize(Vector2f(barWidth, barHeight));
        humanEmptyBars[i].setPosition(35,  offsetY + (i) * (barSpacing));
        humanHealthBars[i].setPosition(35, offsetY + (i) * (barSpacing));
        humanEmptyBars[i].setFillColor(sf::Color(128, 128, 128));

        orcHealthBars[i].setSize(Vector2f(barWidth * orcHealth, barHeight));
        orcEmptyBars[i].setSize(Vector2f(barWidth, barHeight));
        orcEmptyBars[i].setPosition(window.getSize().x - barWidth - 35, offsetY + (i) * (barSpacing));
        orcHealthBars[i].setPosition(window.getSize().x - barWidth - 35, offsetY + (i) * (barSpacing));
        orcEmptyBars[i].setFillColor(sf::Color(128, 128, 128));

        // Set outline colors
        humanEmptyBars[i].setOutlineColor(Color::Black);
        humanEmptyBars[i].setOutlineThickness(2.0f);
        orcEmptyBars[i].setOutlineColor(Color::Black);
        orcEmptyBars[i].setOutlineThickness(2.0f);


        /**/

        humanUnitIcons[i].setPosition(barWidth+40, offsetY + (i) * (barSpacing)-15);
        humanHealthTexts[i].setPosition(25 + barWidth / 2,offsetY + (i) * (barSpacing)-25);

        orcUnitIcons[i].setPosition(window.getSize().x - (barWidth+90), offsetY + (i) * (barSpacing)-15);
        orcHealthTexts[i].setPosition(window.getSize().x - (55 + barWidth / 2),offsetY + (i) * (barSpacing)-25);

        /**/
    }


    // Main rendering loop
    while (window.isOpen())
    {
        window.clear();
        window.draw(bgSprite);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            {
                window.close();
            }
            if (event.key.code == Keyboard::Space)
            {
                window.close();
                renderInterface(insan_imparatorlugu,ork_legi);
                return;
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2i mousePos = Mouse::getPosition(window);
                for (int i = 0; i < unitImages.size(); ++i)
                {
                    Sprite& unitSprite = unitImages[i];
                    if (unitSprite.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
                    {
                        float scaleFactor = isEnlarged[i] ? 1.0f / 3.5f : 3.5f;
                        unitSprite.setScale(unitSprite.getScale().x * scaleFactor, unitSprite.getScale().y * scaleFactor);
                        isEnlarged[i] = !isEnlarged[i];
                    }
                }
            }
        }

        // Draw hexagons, unit images, health bars, and main characters
        for (const auto& hex : hexagons) window.draw(hex);
        for (const auto& unit : unitImages) window.draw(unit);
        if(insan_imparatorlugu.kahramanSayisi||insan_imparatorlugu.canavarSayisi||ork_legi.kahramanSayisi||ork_legi.canavarSayisi)
            for (const auto& hero : mainCharacters) window.draw(hero);

        // Draw health bars with color changes based on health percentage
        for (int i = 0; i < insan_imparatorlugu.birimSayisi; ++i)
        {
            window.draw(humanEmptyBars[i]);
            window.draw(humanHealthBars[i]);
            window.draw(orcEmptyBars[i]);
            window.draw(orcHealthBars[i]);
            window.draw(humanUnitIcons[i]);
            window.draw(orcUnitIcons[i]);
            window.draw(humanHealthTexts[i]);
            window.draw(orcHealthTexts[i]);
        }

        window.display();
    }
}
