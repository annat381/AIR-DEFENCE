#include <SFML/Graphics.hpp>
using namespace sf;

const int L_B17 = 176;
const int H_B17 = 136;

class B17
{
public:
    bool destroyed;
    int speed;
    Texture textureB17;
    Sprite spriteB17;

    B17()
    {
        textureB17.loadFromFile("./images/planes/b17.png");
        spriteB17.setTexture(textureB17);
        spriteB17.setTextureRect(IntRect(0, 0, L_B17, H_B17));
        spriteB17.setPosition(1000, 500);
    }
};
