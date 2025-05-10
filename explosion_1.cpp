#include <SFML/Graphics.hpp>
#include <array>

class Explosion {
public:
    Explosion(float x, float y, const std::array<sf::Texture*, 10>& textures);
    ~Explosion();
    void update();
    void draw(sf::RenderWindow& window);
    bool is_finished() const;

private:
    sf::Sprite sprite;
    std::array<sf::Texture*, 10> textures;
    int frame;
    bool finished;
    bool has_textures;
};

Explosion::Explosion(float x, float y, const std::array<sf::Texture*, 10>& textures) : textures(textures), frame(0), finished(false), has_textures(false)
{
    if (!textures.empty() && textures[0]) {
        sprite.setTexture(*textures[0]);
        sprite.setPosition(x, y);
    }
}

Explosion::~Explosion() {
    if (ownsTextures) {
        for (auto texture : textures) {
            delete texture;
        }
    }
}

void Explosion::update() {
    if (frame < 9) {
        frame++;
        if (textures[frame]) {
            sprite.setTexture(*textures[currentFrame]);
        }
    }
    else {
        finished = true;
    }
}

void Explosion::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

bool Explosion::is_finished() const {
    return finished;
}
