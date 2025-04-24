#include <SFML/Graphics.hpp>
using namespace sf;

const int L_B17 = 176;
const int H_B17 = 136;

class B17
{
public:
    bool destroyed;
    int speed;
    Texture texture;
    Sprite sprite;

    B17()
    {
        texture.loadFromFile("./images/planes/b17.png");
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, L_B17, H_B17));
        sprite.setPosition(1000, 500);
    }
};
