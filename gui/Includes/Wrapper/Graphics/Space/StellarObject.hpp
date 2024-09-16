/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** StellarObject.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_STELLAROBJECT_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_STELLAROBJECT_HPP
    #include "Sphere.hpp"

namespace rl
{
    class StellarObject : public virtual Sphere {
    public:
        enum class OrbitAxis {
            Y,
            Z
        };

        StellarObject();
        ~StellarObject();

        void addSatellite(std::shared_ptr<StellarObject> planet,
                          std::shared_ptr<StellarObject> parent);
        void setSatelliteState(const std::string &id, const bool status);
        std::shared_ptr<StellarObject> getSatellite(const std::string &id);
        size_t getSatellitesNumber() const;

        std::string getId() const;

        VisualElement::Type getType() const override;

        Vector3 getTransformedPosition() const;

        void setOrbitRadius(const float orbitRadius);
        float getOrbitRadius() const;

        void setRotationSpeed(const float rotationSpeed);
        float getRotationSpeed() const;

        void setOrbitAxis(const OrbitAxis orbitAxis);
        OrbitAxis getOrbitAxis() const;

        void applyTransformations();

    protected:
        std::unordered_map<std::string, std::shared_ptr<StellarObject>> _objects;
        bool _isSatellite;
        float _orbitRotation;
        float _orbitRadius;
        float _rotationSpeed;
        OrbitAxis _orbitAxis;
        Vector3 _transformedPosition;
        std::string _id;
        size_t _index;
        std::shared_ptr<StellarObject> _parent;
    };
};

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_STELLAROBJECT_HPP*/
