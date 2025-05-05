#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;

const int L_EXPLOSION = 300;
const int H_EXPLOSION = 300;



class Explosion
{
public:
    bool visible;
    int x;
    int y;
    int counter;
    Texture textureExplosion;
    Sprite spriteExplosion;

    Explosion()
    {

    }

    ~Explosion()
    {

    }

    void upd()
    {
        if ((counter % 8 == 0) and visible)
        {
            int ind = 1 + counter / 8;
            std::string str = "./images/explosion/explosion" + std::to_string(ind) + ".png";
            textureExplosion.loadFromFile(str);
            spriteExplosion.setTexture(textureExplosion);
            spriteExplosion.setTextureRect(IntRect(0, 0, L_EXPLOSION, H_EXPLOSION));
        }

        counter += 1;

        if (counter == 64)
        {
            visible = false;
        }
    }
};
