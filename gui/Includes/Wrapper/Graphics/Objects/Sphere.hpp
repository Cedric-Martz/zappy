/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Sphere.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_SPHERE_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_SPHERE_HPP
    #include "Model3.hpp"

namespace rl
{
    class Sphere : public virtual Model3 {
    public:
        Sphere();
        Sphere(const float scale, const int rings, const int slices);
        Sphere(const float scale, const int rings, const int slices, const std::string &filepath);
        ~Sphere();

        void draw() override;
        void applyTransform(Transform &transform) override;
        void update(double deltaTime) override;

        void setSize(const float radius);
        float getSize() const;

        void setWiresColor(const Color color);
        Color getWiresColor();

        void adjust();

        VisualElement::Type getType() const override;

    private:
        void updateModel();
        bool _hasModelLoaded;
        Color _wiresColor;
        int _rings;
        int _slices;
    };
}

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_SPHERE_HPP*/
