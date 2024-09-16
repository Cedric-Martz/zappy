/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Cube.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_CUBE_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_CUBE_HPP
    #include "Object.hpp"
    #include "Clickable.hpp"
    #include "Model3.hpp"

namespace rl
{
    class Cube : public Model3 {
    public:
        Cube();
        Cube(const std::string &textureFilepath);
        ~Cube();

        void draw() override;
        void applyTransform(Transform &transform) override;
        void update(double deltaTime) override;
        void loadTextureFromFile(const std::string &filepath);

        void setSize(const Vector3 &size);
        void setSize(const float x, const float y, const float z);
        Vector3 getSize();

        void setWiresColor(const Color color);
        Color getWiresColor();

        VisualElement::Type getType() const override;

        bool isHovered() override;

    private:
        Color _wiresColor = MAROON;
        bool _hasTextureLoaded;
        bool _hasMeshLoaded;
        bool _hasModelLoaded;
        Material _material;
        void createTextured();
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_CUBE_HPP*/
