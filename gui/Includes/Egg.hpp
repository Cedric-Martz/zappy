/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Egg.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_EGG_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_EGG_HPP
    #include "Model3.hpp"

namespace rl
{
    class Egg : public Model3 {
    public:
        Egg(const std::string &id,
            const std::string &modelFilepath,
            std::shared_ptr<Camera3> &camera);
        ~Egg();

        void draw() override;

        std::string getId() const;
        void setId(const std::string &id);

    private:
        std::string _id;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_EGG_HPP*/
