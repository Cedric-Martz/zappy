/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Grid.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_GRID_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_GRID_HPP
    #include "Drawable.hpp"

namespace rl
{
    class Grid : public Drawable {
    public:
        Grid(const int size = 16, const float spacing = 4);
        ~Grid();

        int getSize() const;
        float getSpacing() const;

        void setSize(const int size);
        void setSpacing(const float spacing);

        void draw() override;
    private:
        int _size;
        float _spacing;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_GRID_HPP*/
