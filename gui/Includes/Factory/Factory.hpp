/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Factory.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_FACTORY_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_FACTORY_HPP
    #include "VisualElement.hpp"

namespace rl
{
    class Factory {
    public:
        template<typename Element, typename... Args>
        static std::shared_ptr<Element> createElement(Args&&... args)
        {
            return std::make_shared<Element>(std::forward<Args>(args)...);
        }
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_FACTORY_HPP*/
