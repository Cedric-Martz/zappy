/*
** EPITECH PROJECT, 2024
** Epitech-Jam-Flamme
** File description:
** AScene
*/

#ifndef ASCENE_HPP_
    #define ASCENE_HPP_
    #include "IScene.hpp"
    #include "RayLib.hpp"
    #include "VisualElement.hpp"
    #include "Camera3.hpp"
    #include "Player.hpp"
    #include "Planet.hpp"

namespace rl
{
    class AScene : public IScene {
        public:
            AScene();
            ~AScene() = default;

            virtual std::string getId() const = 0;

            template<typename Element>
            std::shared_ptr<Element> getElement(const std::string &id)
            {
                if (!_elements.contains(id))
                    return nullptr;
                return std::dynamic_pointer_cast<Element>(_elements[id]);
            }

            void addButton(
                const std::string &id,
                Vector2 position,
                Vector2 dimension,
                Color color,
                std::function<void()> onClick,
                const std::string &textureName = "",
                const std::string &textureOnHoverTexture = ""
            );
            void addText(const std::string &id,
                         const std::string &string,
                         const unsigned int characterSize = 15,
                         const Color color = BLACK,
                         const Vector2 position = Vector2(0, 0));
            void addInputText(
                const std::string &id,
                const Rectangle rectangle,
                const size_t maxCharactersNumber,
                const unsigned int characterSize,
                const Color color,
                const std::string &accepted = "",
                const std::string &rejected = "",
                std::function<void(Text &, size_t &)> onEnter = nullptr,
                std::function<void()> onFocus = nullptr,
                std::function<void()> onUnfocus = nullptr
            );
            void addSplash(const std::string &id,
                           const Vector2 position,
                           const Color color);
            void addInventory(const std::string &id);
            void addCube(const std::string &id,
                         const Vector3 &position,
                         const Vector3 &size,
                         const Color color,
                         const Color wiresColor);
            void addSphere(const std::string &id,
                           const Vector3 &position,
                           const float radius,
                           const Color color,
                           const Color wiresColor);
            void addSphere(const std::string &id,
                           const Vector3 &position,
                           const float radius,
                           const Color color,
                           const Color wiresColor,
                           const std::string &filepath);
            void addModel3(const std::string &id,
                           std::shared_ptr<Camera3> camera,
                           const std::string &filepath,
                           const Vector3 &position,
                           const Vector3 &rotationAxis,
                           const double rotationAngle,
                           const Color color,
                           const Color boundingBoxColor,
                           const bool isRainbow = false);
            void addPlayer(const std::string &id,
                               std::shared_ptr<Camera3> camera,
                               const std::string &filepath,
                               const Vector3 &position,
                               const Vector3 &rotationAxis,
                               const double rotationAngle,
                               const Color color,
                               const Color boundingBoxColor,
                               const bool isRainbow);
            void addTorus(const std::string &id,
                          const float radius,
                          const float size,
                          const int radSeg,
                          const int sides,
                          const std::string &textureFilepath);
            void addSprite(const std::string &id,
                           const std::string &filepath,
                           const Vector2 &position,
                           const Vector2 &scale,
                           const Color color);
            void addPlanet(const std::string &id,
                           const std::string &filepath,
                           const Vector3 &position,
                           const float radius,
                           const Color &color,
                           const std::shared_ptr<Camera3> &camera);
            void addSatellite(const std::string &id,
                              std::shared_ptr<StellarObject> parent,
                              const std::string &filepath,
                              const Vector3 &position,
                              const float radius,
                              const Color &color,
                              const std::shared_ptr<Camera3> &camera,
                              const float orbitRadius,
                              const float rotationSpeed);
            void addSatellite(const std::string &id,
                              std::shared_ptr<StellarObject> parent,
                              const Vector3 &position,
                              const float radius,
                              const Color &color,
                              const std::shared_ptr<Camera3> &camera,
                              const float orbitRadius,
                              const float rotationSpeed);


    protected:
        std::unordered_map<std::string, std::shared_ptr<VisualElement>> _elements;
    };
}

#endif /* !ASCENE_HPP_ */
