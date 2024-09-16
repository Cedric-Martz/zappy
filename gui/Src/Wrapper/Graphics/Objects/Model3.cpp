/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** Model3.cpp
*/

#include "Model3.hpp"
#include <cfloat>

namespace rl
{
    Model3::Model3()
        : Object(),
        _hasModelLoaded(false),
        _hasTextureLoaded(false),
        _isBoundingBoxVisible(false),
        _rotationAxis({0, 0, 0}),
        _bboxColor(TRANSPARENT)
    {
        _position = Vector3(0, 0, 0);
        _rotation = 0;
        _size = Vector3(1, 1, 1);
        _scale = Vector3(1, 1, 1);
        _color = WHITE;
    }

    Model3::Model3(const std::string &modelFilepath, std::shared_ptr<Camera3> camera)
        : Object(),
        _hasModelLoaded(false),
        _hasTextureLoaded(false),
        _isBoundingBoxVisible(false),
        _rotationAxis({0, 0, 0}),
        _bboxColor(TRANSPARENT),
        _camera(camera)
    {
        loadFromFile(modelFilepath);
        _position = Vector3(0, 0, 0);
        _rotation = 0;
        _size = Vector3(1, 1, 1);
        _scale = Vector3(1, 1, 1);
        _color = WHITE;
    }

    Model3::~Model3() {}

    void Model3::loadFromFile(const std::string &modelFilepath)
    {
        _hasModelLoaded = true;
        _modelFilepath = modelFilepath;
        _model = LoadModel(_modelFilepath.c_str());
        _animsCount = 0;
        //_anim = LoadModelAnimations(_modelFilepath.c_str(), &_animsCount);
        _animFrameCounter = 0;
        _animId = 0;
        _playing = false;
    }

    void Model3::setCamera(std::shared_ptr<Camera3> camera)
    {
        _camera = camera;
    }

    void Model3::setRawModel(Model &model)
    {
        _model = model;
    }

    void Model3::draw()
    {
        DrawModelEx(_model, _position, _rotationAxis, _rotation, _scale, _color);
        if (isHovered() || _isBoundingBoxVisible)
            DrawBoundingBox(_bbox, _bboxColor);
        //if (_animsCount == 0)
        //    return;
        //for (int i = 0; i < _model.boneCount - 1; ++i) {
        //    if (!_playing) {
        //        DrawCube(_model.bindPose[i].translation, 0.04f, 0.04f, 0.04f, RED);
        //        if (_model.bones[i].parent >= 0) {
        //            DrawLine3D(_model.bindPose[i].translation,
        //                       _model.bindPose[_model.bones[i].parent].translation, RED);
        //        }
        //    } else {
        //        DrawCube(_anim[_animId].framePoses[_animFrameCounter][i].translation, 0.05f, 0.05f, 0.05f, RED);
        //        if (_anim[_animId].bones[i].parent >= 0) {
        //            DrawLine3D(_anim[_animId].framePoses[_animFrameCounter][i].translation,
        //                       _anim[_animId].framePoses[_animFrameCounter][_anim[_animId].bones[i].parent].translation, RED);
        //        }
        //    }
        //}
    }

    void Model3::applyTransform([[maybe_unused]] Transform &transform) {}

    void Model3::update(double deltaTime)
    {
        updateRainbow(deltaTime);
        //if (_animsCount == 0)
        //    return;
        //_animFrameCounter += 1;
        //if (_animFrameCounter >= _anim[_animId].frameCount)
        //    _animFrameCounter = 0;
        //UpdateModelAnimation(_model, _anim[_animId], _animFrameCounter);
        //if (!_playing)
        //    _playing = true;
    }

    VisualElement::Type Model3::getType() const
    {
        return VisualElement::Type::MODEL;
    }

    Vector3 Model3::getRotationAxis() const
    {
        return _rotationAxis;
    }

    void Model3::setRotationAxis(const Vector3 &vector)
    {
        _rotationAxis = vector;
    }

    Color Model3::getBoundingBoxColor() const
    {
        return _bboxColor;
    }

    void Model3::setBoundingBoxColor(const Color color)
    {
        _bboxColor = color;
    }

    bool Model3::getBoundingBoxVisibility() const
    {
        return _isBoundingBoxVisible;
    }

    void Model3::setBoundingBoxVisibility(const bool status)
    {
        _isBoundingBoxVisible = status;
    }

    bool Model3::isHovered()
    {
        _bbox = GetModelBoundingBox(_model);
        _bbox.min = _bbox.min + _position;
        _bbox.max = _bbox.max + _position;

        _collision.distance = FLT_MAX;
        _collision.hit = false;

        _ray = GetScreenToWorldRay(Mouse::getInstance().getPosition(), _camera->getSource());

        _boxHitInfo = GetRayCollisionBox(_ray, _bbox);

        if (_boxHitInfo.hit && _boxHitInfo.distance < _collision.distance)
            _collision = _boxHitInfo;
        return _boxHitInfo.hit;
    }

    void Model3::setRawModelTransformation(const Matrix matrix)
    {
        _model.transform = matrix;
    }

    void Model3::updateModelTexture(const Texture2D &texture, const MaterialMapIndex materialIndex)
    {
        _model.materials[0].maps[static_cast<int>(materialIndex)].texture = texture;
    }

    Vector3 Model3::getSize() const
    {
        Vector3 size(
                _bbox.max.x - _bbox.min.x,
                _bbox.max.y - _bbox.min.y,
                _bbox.max.z - _bbox.min.z
        );
        return size;
    }
};
