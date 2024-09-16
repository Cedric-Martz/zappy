/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Shape.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_VISUALELEMENT_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_VISUALELEMENT_HPP
    #include "Transformable.hpp"
    #include "Drawable.hpp"
    #include "Transform.hpp"
    #include "Time.hpp"

namespace rl
{
    class VisualElement : public Drawable, public Transformable {
    public:
        enum class Dimension {
            DIMENSION2,
            DIMENSION3
        };

        enum class Type {
            RECTANGLE,
            CIRCLE,
            SPRITE,
            TEXT,
            INPUT_TEXT,
            SPLASH,
            CUBE,
            MODEL,
            SPHERE,
            INVENTORY,
            TORUS,
            TILE,
            STELLAR_OBJECT,
            STAR,
            PLANET
        };

        virtual ~VisualElement();

        void setTexture(const Texture texture);
        void setTextureRect(const Rectangle textureRect);
        void setColor(const Color color);
        void setOrigin(const Vector2 &vector);
        void setOrigin(int x, int y);

        Texture getTexture() const;
        Rectangle getTextureRect() const;
        Color getColor() const;
        Vector2 getOrigin() const;

        void draw() override;
        virtual void update(double deltaTime) = 0;
        virtual Dimension getDimension() const;
        virtual Type getType() const = 0;

        bool isRainbow() const;
        void setRainbowStatus(const bool status);
        double getRainbowSpeed() const;
        void setRainbowSpeed(const double speed);

        virtual void applyTransform(Transform &transform) = 0;

        void setDisplayed(const bool state);
        bool getDisplayed() const;

    protected:
        VisualElement();
        void updateRainbow(double deltaTime);
        Texture _texture;
        Rectangle _textureRect;
        Color _color;
        Vector2 _origin;
        Vector3 _size;
        bool _isRainbow;
        Time _rainbowTimeBank;
        double _rainbowSpeed;
        bool _displayed;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_VISUALELEMENT_HPP*/
