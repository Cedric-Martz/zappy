/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Model.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_MODEL_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_MODEL_HPP
    #include "Object.hpp"
    #include "Clickable.hpp"
    #include "Camera3.hpp"
    #define FLT_MAX 340282346638528859811704183484516925440.0f

namespace rl
{
    class Model3 : public Object, public Clickable {
    public:
        Model3();
        Model3(const std::string &modelFilepath, std::shared_ptr<Camera3> camera);
        ~Model3();

        void loadFromFile(const std::string &modelFilepath);
        void setCamera(std::shared_ptr<Camera3> camera);

        void setRawModel(Model &model);

        void draw() override;
        void applyTransform(Transform &transform) override;
        void update(double deltaTime) override;

        VisualElement::Type getType() const override;

        Vector3 getRotationAxis() const;
        void setRotationAxis(const Vector3 &vector);

        Color getBoundingBoxColor() const;
        void setBoundingBoxColor(const Color color);

        bool getBoundingBoxVisibility() const;
        void setBoundingBoxVisibility(const bool status);

        bool isHovered() override;

        void setRawModelTransformation(const Matrix matrix);

        void updateModelTexture(const Texture2D &texture,
                                const MaterialMapIndex materialIndex = MaterialMapIndex::MATERIAL_MAP_ALBEDO);

        Vector3 getSize() const;

    protected:
        std::string _modelFilepath;
        bool _hasModelLoaded;
        bool _hasTextureLoaded;
        Model _model;
        ModelAnimation *_anim;
        int _animsCount;
        int _animFrameCounter;
        int _animId;
        bool _playing;
        bool _isBoundingBoxVisible;

        Vector3 _rotationAxis;
        Color _bboxColor;
        BoundingBox _bbox;
        Ray _ray{};
        RayCollision _boxHitInfo;
        RayCollision _collision{};
        std::shared_ptr<Camera3> _camera;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_MODEL_HPP*/
