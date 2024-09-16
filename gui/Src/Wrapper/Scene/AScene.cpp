/*
** EPITECH PROJECT, 2024
** Epitech-Jam-Flamme
** File description:
** AScene
*/

#include "AScene.hpp"
#include "Factory.hpp"
#include "Wrapper.hpp"

namespace rl
{
    AScene::AScene() {}

    void AScene::addButton(
        const std::string &id,
        Vector2 position,
        Vector2 dimension,
        Color color,
        std::function<void()> onClick,
        const std::string &textureName,
        const std::string &textureOnHoverTexture
    )
    {
        if (_elements.contains(id))
            return;
        std::shared_ptr<Button> element =
                Factory::createElement<Button>(
                        Rectangle(position.x, position.y, dimension.x, dimension.y),
                        color,
                        onClick,
                        textureName,
                        textureOnHoverTexture
                );
        _elements[id] = element;
    }

    void AScene::addText(const std::string &id,
                         const std::string &string,
                         const unsigned int characterSize,
                         const Color color,
                         const Vector2 position)
    {
        if (_elements.contains(id))
            return;
        std::shared_ptr<Text> element =
                Factory::createElement<Text>(string, characterSize);
        element->setColor(color);
        element->setPosition(position);
        _elements[id] = element;
    }

    void AScene::addInputText(
        const std::string &id,
        const Rectangle rectangle,
        const size_t maxCharactersNumber,
        const unsigned int characterSize,
        const Color color,
        const std::string &accepted,
        const std::string &rejected,
        std::function<void(Text &, size_t &)> onEnter,
        std::function<void()> onFocus,
        std::function<void()> onUnfocus
    )
    {
        if (_elements.contains(id))
            return;
        std::shared_ptr<InputText> element =
                Factory::createElement<InputText>(
                    rectangle,
                    maxCharactersNumber,
                    accepted,
                    rejected,
                    onEnter,
                    onFocus,
                    onUnfocus
                );
        element->setColor(color);
        element->getText().setPosition(element->getPosition2());
        element->getText().setCharacterSize(characterSize);
        element->getText().setSpacing(3);
        element->getText().updateOrigin();
        _elements[id] = element;
    }

    void AScene::addSplash(const std::string &id,
                           const Vector2 position,
                           const Color color)
    {
        if (_elements.contains(id))
            return;
        std::shared_ptr<Splash> element =
                Factory::createElement<Splash>(color, -20.0f);
        element->setPosition(position);
        _elements[id] = element;
    }

    void AScene::addInventory(const std::string &id)
    {
        if (_elements.contains(id))
            return;
        _elements[id] = Factory::createElement<Inventory>();
    }

    void AScene::addCube(const std::string &id,
                         const Vector3 &position,
                         const Vector3 &size,
                         const Color color,
                         const Color wiresColor)
    {
        std::shared_ptr<Cube> cube = Factory::createElement<Cube>();

        cube->setPosition(position);
        cube->setSize(size);
        cube->setColor(color);
        cube->setWiresColor(wiresColor);
        _elements[id] = cube;
    }

    void AScene::addSphere(const std::string &id,
                           const Vector3 &position,
                           const float radius,
                           const Color color,
                           const Color wiresColor)
    {
        std::shared_ptr<Sphere> sphere = Factory::createElement<Sphere>();

        sphere->setPosition(position);
        sphere->setSize(radius);
        sphere->setColor(color);
        sphere->setWiresColor(wiresColor);
        _elements[id] = sphere;
    }

    void AScene::addSphere(const std::string &id,
                           const Vector3 &position,
                           const float radius,
                           const Color color,
                           const Color wiresColor,
                           const std::string &filepath)
    {
        std::shared_ptr<Sphere> sphere = Factory::createElement<Sphere>(radius, 32, 32, filepath);

        sphere->setPosition(position);
        sphere->setSize(radius);
        sphere->setColor(color);
        sphere->setWiresColor(wiresColor);
        _elements[id] = sphere;
    }

    void AScene::addModel3(const std::string &id,
                           std::shared_ptr <Camera3> camera,
                           const std::string &filepath,
                           const Vector3 &position,
                           const Vector3 &rotationAxis,
                           const double rotationAngle,
                           const Color color,
                           const Color boundingBoxColor,
                           const bool isRainbow)
    {
        std::shared_ptr<Model3> model = Factory::createElement<Model3>(filepath, camera);

        model->setPosition(position);
        model->setRotationAxis(rotationAxis);
        model->setRotation(rotationAngle);
        model->setColor(color);
        model->setBoundingBoxColor(boundingBoxColor);
        model->setRainbowStatus(isRainbow);
        _elements[id] = model;
    }

    void AScene::addPlayer(const std::string &id,
                           std::shared_ptr<Camera3> camera,
                           const std::string &filepath,
                           const Vector3 &position,
                           const Vector3 &rotationAxis,
                           const double rotationAngle,
                           const Color color,
                           const Color boundingBoxColor,
                           const bool isRainbow)
    {
        std::shared_ptr<Player> model = Factory::createElement<Player>(filepath, camera);

        model->setPosition(position);
        model->setRotationAxis(rotationAxis);
        model->setRotation(rotationAngle);
        model->setColor(color);
        model->setBoundingBoxColor(boundingBoxColor);
        model->setRainbowStatus(isRainbow);
        _elements[id] = model;
    }

    void AScene::addTorus(const std::string &id,
                          const float radius,
                          const float size,
                          const int radSeg,
                          const int sides,
                          const std::string &textureFilepath)
    {
        std::shared_ptr<Torus> torus = Factory::createElement<Torus>(radius, size, radSeg, sides, textureFilepath);

        _elements[id] = torus;
    }

    void AScene::addSprite(const std::string &id,
                   const std::string &filepath,
                   const Vector2 &position,
                   const Vector2 &scale,
                   const Color color)
    {
        std::shared_ptr<Sprite> sprite = Factory::createElement<Sprite>(TextureManager::getInstance().loadTexture(filepath));

        sprite->setPosition(position);
        sprite->setScale(scale);
        sprite->setColor(color);
        _elements[id] = sprite;
    }

    void AScene::addPlanet(const std::string &id,
                           const std::string &filepath,
                           const Vector3 &position,
                           const float radius,
                           const Color &color,
                           const std::shared_ptr<Camera3> &camera)
    {
        std::shared_ptr<Planet> planet = std::make_shared<Planet>(
                id,
                position,
                radius,
                color,
                camera,
                0.0f,
                0.0f
        );

        planet->updateModelTexture(TextureManager::getInstance().loadTexture(filepath));
        _elements[id] = planet;
    }

    void AScene::addSatellite(const std::string &id,
                              std::shared_ptr<StellarObject> parent,
                              const std::string &filepath,
                              const Vector3 &position,
                              const float radius,
                              const Color &color,
                              const std::shared_ptr<Camera3> &camera,
                              const float orbitRadius,
                              const float rotationSpeed)
    {
        std::shared_ptr<Planet> planet = std::make_shared<Planet>(
                id,
                position,
                radius,
                color,
                camera,
                orbitRadius,
                rotationSpeed
        );
        planet->updateModelTexture(TextureManager::getInstance().loadTexture(filepath));

        if (!parent)
            return;
        parent->addSatellite(planet, parent);
    }

    void AScene::addSatellite(const std::string &id,
                              std::shared_ptr<StellarObject> parent,
                              const Vector3 &position,
                              const float radius,
                              const Color &color,
                              const std::shared_ptr<Camera3> &camera,
                              const float orbitRadius,
                              const float rotationSpeed)
    {
        std::shared_ptr<Planet> planet = std::make_shared<Planet>(
                id,
                position,
                radius,
                color,
                camera,
                orbitRadius,
                rotationSpeed
        );

        if (!parent)
            return;
        parent->addSatellite(planet, parent);
    }
}
