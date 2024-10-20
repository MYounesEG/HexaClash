#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include <cstring> // For strcpy
#include "classes.h"
#include "gameInterface.h"

using namespace std;
using namespace sf;

float HEX_SIZE = 30.0;  // Default size of the hexagon
float SPACING = 20.0f;  // Default spacing between hexagons

// Function to convert hexagonal grid coordinates (q, r) to pixel coordinates
Vector2f hexToPixel(int q, int r, float offsetX, float offsetY, float hexSize, float spacing)
{
    float x = hexSize * 3.0f / 2.0f * q;  // Horizontal distance between hexes
    float y = hexSize * sqrt(3) * r; // Vertical distance between hexes

    // Stagger even rows by shifting x position
    if (q % 2 != 0)
    {
        y += hexSize * sqrt(3) / 2.0f;
    }

    // Apply spacing between hexagons
    x += spacing * q;
    y += spacing * r;

    // Centering based on offsets
    x += offsetX;
    y += offsetY;

    return Vector2f(x, y);
}

// Function to create a hexagon shape
CircleShape createHexagon(float x, float y, float hexSize)
{
    CircleShape hexagon(hexSize, 6); // Create a hexagon shape
    hexagon.setPosition(x, y); // Set its position
    hexagon.setFillColor(Color::Red); // Set its color to red
    hexagon.setOrigin(hexSize, hexSize); // Set origin to the center for proper rotation

    // Set the outline color and thickness
    hexagon.setOutlineColor(Color::Black); // Set the outline color to black
    hexagon.setOutlineThickness(2.0f); // Set the outline thickness

    return hexagon;
}

// Function to place an image at a specific grid position
Sprite setImage(int row, int col, const string& imageName, float offsetX, float offsetY, float scaleFactor, float hexSize, float spacing)
{
    Texture* texture = new Texture();
    if (!texture->loadFromFile(imageName))
    {
        throw runtime_error("Failed to load image: " + imageName);
    }

    // Create a sprite for the texture
    Sprite sprite;
    sprite.setTexture(*texture);

    // Scale the sprite to fit within the hexagons
    sprite.setScale(scaleFactor, scaleFactor);

    // Get the pixel position for the specified grid row and column
    Vector2f pos = hexToPixel(row, col, offsetX, offsetY, hexSize, spacing);

    // Center the sprite inside the hexagon
    sprite.setPosition(pos.x - (128 * scaleFactor), pos.y - (128 * scaleFactor));

    return sprite;
}

void putImge(int mode, Unit birim, vector<Sprite>& images, vector<bool>& isEnlarged, float offsetX, float offsetY, float scaleFactor, int Positions[10][10], int extraSpacing, float hexSize, float spacing)
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

        images.push_back(setImage(randomX, randomY, imgeName, offsetX + (mode == 2 ? extraSpacing + 10 : 10), offsetY, scaleFactor, hexSize, spacing));
        isEnlarged.push_back(false); // Initialize the image as not enlarged
    }
}

// Main function to draw the grid and health bars
void grafik(Takim insan_imparatorlugu, Takim ork_legi)
{
    srand(time(0));

    // Create a fullscreen window
    RenderWindow window(VideoMode::getFullscreenModes()[0], "Hexagonal Rectangular Grid Game", Style::Fullscreen);

    // Adjust HEX_SIZE and SPACING based on the screen size
    HEX_SIZE = window.getSize().y / 25.0f; // Dynamic size based on the window height
    SPACING = HEX_SIZE * 0.6f;             // Dynamic spacing proportional to hex size

    vector<CircleShape> hexagons;
    float offsetX = window.getSize().x / 3.8;
    float offsetY = window.getSize().y / 15;
    float extraSpacing;

    // Generate hexagons in a rectangular grid (10x10)
    for (int q = 0; q < 10; ++q)
    {
        for (int r = 0; r < 10; ++r)
        {
            extraSpacing = (q >= 5) ? 40.0f : 0.0f;
            Vector2f pos = hexToPixel(q, r, offsetX + extraSpacing + 10, offsetY, HEX_SIZE, SPACING);
            hexagons.push_back(createHexagon(pos.x, pos.y, HEX_SIZE));
        }
    }

    float hexInnerRadius = HEX_SIZE * sqrt(3) / 2.0f;
    float scaleFactor = hexInnerRadius / 128.0f;

    int Positions[10][10] = {0};
    vector<Sprite> images;
    vector<bool> isEnlarged;

    for (int i = 0; i < insan_imparatorlugu.birimSayisi; i++)
        putImge(1, insan_imparatorlugu.birimler[i], images, isEnlarged, offsetX, offsetY, scaleFactor, Positions, extraSpacing, HEX_SIZE, SPACING);

    for (int i = 0; i < ork_legi.birimSayisi; i++)
        putImge(2, ork_legi.birimler[i], images, isEnlarged, offsetX, offsetY, scaleFactor, Positions, extraSpacing, HEX_SIZE, SPACING);

    // Load background image
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images/background_image.png"))
    {
        cerr << "Error loading background image" << endl;
        return;
    }
    Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        window.getSize().x / backgroundSprite.getLocalBounds().width,
        window.getSize().y / backgroundSprite.getLocalBounds().height
    );



    vector<Sprite> mainCharacters;
    Texture heroTextureOrkLegi;
    Texture monsterTextureOrkLegi;
    Texture heroTextureInsanImparatorlugu;
    Texture monsterTextureInsanImparatorlugu;

    float characterPosX, characterPosY;

    // Load images for ork_legi
    string orkHeroImagePath = "images/" + (string)ork_legi.kahramanlar[0].isim + ".png";
    string orkMonsterImagePath = "images/" + (string)ork_legi.canavarlar[0].isim + ".png";

    // Load hero for ork_legi
    if (!heroTextureOrkLegi.loadFromFile(orkHeroImagePath))
    {
        cerr << "Error loading " + orkHeroImagePath + " image" << endl;
        return;
    }

    Sprite orkHeroSprite;
    orkHeroSprite.setTexture(heroTextureOrkLegi);
    orkHeroSprite.setScale(scaleFactor * 2.2f, scaleFactor * 2.2f);
    orkHeroSprite.setPosition(offsetX + 600, offsetY + 350);
    mainCharacters.push_back(orkHeroSprite);

    // Load monster for ork_legi
    if (!monsterTextureOrkLegi.loadFromFile(orkMonsterImagePath))
    {
        cerr << "Error loading " + orkMonsterImagePath + " image" << endl;
        return;
    }

    Sprite orkMonsterSprite;
    orkMonsterSprite.setTexture(monsterTextureOrkLegi);
    orkMonsterSprite.setScale(scaleFactor * 2.2f, scaleFactor * 2.2f);
    orkMonsterSprite.setPosition(offsetX + 700.0f, offsetY + 170); // Adjust position
    mainCharacters.push_back(orkMonsterSprite);

    // Load images for insan_imparatorlugu
    string insanHeroImagePath = "images/" + (string)insan_imparatorlugu.kahramanlar[0].isim + ".png";
    string insanMonsterImagePath = "images/" + (string)insan_imparatorlugu.canavarlar[0].isim + ".png";

    // Load hero for insan_imparatorlugu
    if (!heroTextureInsanImparatorlugu.loadFromFile(insanHeroImagePath))
    {
        cerr << "Error loading " + insanHeroImagePath + " image" << endl;
        return;
    }

    Sprite insanHeroSprite;
    insanHeroSprite.setTexture(heroTextureInsanImparatorlugu);
    insanHeroSprite.setScale(scaleFactor * 2.2f, scaleFactor * 2.2f);
    insanHeroSprite.setPosition(offsetX - 400, offsetY + 350.0f); // Adjust position
    mainCharacters.push_back(insanHeroSprite);

    // Load monster for insan_imparatorlugu
    if (!monsterTextureInsanImparatorlugu.loadFromFile(insanMonsterImagePath))
    {
        cerr << "Error loading " + insanMonsterImagePath + " image" << endl;
        return;
    }

    Sprite insanMonsterSprite;
    insanMonsterSprite.setTexture(monsterTextureInsanImparatorlugu);
    insanMonsterSprite.setScale(scaleFactor * 2.2f, scaleFactor * 2.2f);
    insanMonsterSprite.setPosition(offsetX - 450.0f, offsetY + 170); // Adjust position
    mainCharacters.push_back(insanMonsterSprite);






    // Split health bars into two vectors (human and orc)
    vector<RectangleShape> humanHealthBars(4);
    vector<RectangleShape> humanEmptyBars(4);
    vector<RectangleShape> orcHealthBars(4);
    vector<RectangleShape> orcEmptyBars(4);

    float barWidth = 200.0f;
    float barHeight = 20.0f;
    float barSpacing = 50.0f;

    // Load a font for health percentage text
    Font font;
    if (!font.loadFromFile("fonts/arial.ttf"))
    {
        cerr << "Error loading font" << endl;
        return;
    }

    // Create health percentage texts
    vector<Text> healthTexts(8);  // 4 for human, 4 for orc
    vector<Sprite> unitIcons(8);
    vector<Texture> iconTextures(8);

    for (int i = 0; i < 8; ++i)
    {
        string iconPath = "images/" + (string)((i < 4) ? insan_imparatorlugu.birimler[i].isim : ork_legi.birimler[i % 4].isim) + ".png";
        if (!iconTextures[i].loadFromFile(iconPath))
        {
            cerr << "Error loading icon: " << iconPath << endl;
            return;
        }

        // Set the sprite texture and scale
        unitIcons[i].setTexture(iconTextures[i]);
        unitIcons[i].setScale(0.2f, 0.2f);

        float healthValue ;
        if(i<4)
            healthValue = insan_imparatorlugu.birimler[i].sayi * insan_imparatorlugu.birimler[i].saglik / (insan_imparatorlugu.birimler[i].orjinal_sayi * insan_imparatorlugu.birimler[i].orjinal_saglik) * 100;
        else
            healthValue = ork_legi.birimler[i - 4].sayi * ork_legi.birimler[i - 4].saglik / (ork_legi.birimler[i - 4].orjinal_sayi * ork_legi.birimler[i - 4].orjinal_saglik) * 100;

        healthTexts[i].setFont(font);
        healthTexts[i].setString(to_string(static_cast<int>(healthValue)) + "%"); // Display health as percentage
        healthTexts[i].setCharacterSize(18);
        healthTexts[i].setFillColor(Color::White);

        // Determine bar positions and text alignment
        vector<RectangleShape>& healthBars = (i < 4) ? humanHealthBars : orcHealthBars;
        vector<RectangleShape>& emptyBars = (i < 4) ? humanEmptyBars : orcEmptyBars;

        healthBars[i % 4].setSize(Vector2f((healthValue / 100.0) * barWidth, barHeight));
        healthBars[i % 4].setFillColor((healthValue > 50) ? Color(0, 255, 47) : (healthValue > 20) ? Color(234, 255, 0) : Color(255, 0, 4));
        healthBars[i % 4].setOutlineColor(Color::Black);
        healthBars[i % 4].setOutlineThickness(2.0f);

        emptyBars[i % 4].setSize(Vector2f(barWidth, barHeight));
        emptyBars[i % 4].setFillColor(Color(128, 128, 128));
        emptyBars[i % 4].setOutlineColor(Color::Black);
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

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    Vector2i mousePos = Mouse::getPosition(window);
                    for (int i = 0; i < images.size(); ++i)
                    {
                        Sprite& image = images[i];
                        if (image.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
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

            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape)
                {
                    window.close();
                }
                else if (event.key.code == Keyboard::Space)
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

        for(int i=mainCharacters.size()-1; i>=0; i--)
        {
            window.draw(mainCharacters[i]); // Draw every kahraman/canavar image
        }

        window.display();
    }
}
