#include "Sprite2D.h"
#include "ramses-utils.h"
#include "Math3d/Vector3.h"
#include "Math3d/Vector4.h"
#include "Math3d/Matrix44f.h"
#include "Utils/LogMacros.h"



namespace ramses_internal
{
    Sprite2D::Sprite2D(GameEngine& engine, Scene& scene, const ramses::Effect& effect, uint32_t renderOrderBuffer /*= 1*/)
        : m_engine(engine)
        , m_scene(scene)
        , m_effect(effect)
        , m_translateNode           (*m_scene.createNode("T"))
        , m_rotationNode            (*m_scene.createNode("R"))
        , m_scaleNode               (*m_scene.createNode("S"))
        , m_meshNode                (*m_scene.createMeshNode("triangle mesh node"))
        , m_rootNode                (m_translateNode)
        , m_appearance              (*m_scene.createAppearance(m_effect, "triangle appearance"))
        , m_geometryBinding         (*m_scene.createGeometryBinding(m_effect, "triangle appearance"))
        , m_lastTime                (0.0f)
        , m_timeDiff                (0.0f)
        , m_translateSpriteToCenter (*m_scene.createNode("T"))
        , m_visibilityNode          (*m_scene.createNode("V"))
    {
        status_t status = StatusOK;

        m_rotationNode              .setParent(m_translateNode);
        m_scaleNode                 .setParent(m_rotationNode);
        m_translateSpriteToCenter   .setParent(m_scaleNode);
        m_visibilityNode            .setParent(m_translateSpriteToCenter);
        m_meshNode                  .setParent(m_visibilityNode);

        m_translateSpriteToCenter.setTranslation(-0.5f, 0.5f, 0);

        ramses::UniformInput resolution;
        status = m_effect.findUniformInput("iResolution", resolution);
        if (StatusOK == status)
        {
            m_appearance.setInputValueVector2f(resolution, static_cast<Float>(Pos2D::s_WindowWidth), static_cast<Float>(Pos2D::s_WindowHeight));
        }

        ramses::AttributeInput vertexPosInput;
        ramses::AttributeInput texcoordInput;
        status = m_effect.findAttributeInput("a_position", vertexPosInput);
        assert(StatusOK == status);
        status = m_effect.findAttributeInput("a_texcoord", texcoordInput);

        // get input data of appearance and bind required data
        m_geometryBinding.setInputBuffer(vertexPosInput, engine.QuadVertexPositions);

        if (texcoordInput.isValid())
        {
            m_geometryBinding.setInputBuffer(texcoordInput, engine.QuadTexCoords);
        }
        m_geometryBinding.setIndices(engine.QuadIndices);

        m_appearance.setCullingMode(ECullMode_Disabled);
        m_appearance.setDepthFunction(EDepthFunc_Disabled);

        // create a mesh node to define the triangle with chosen appearance
        status = m_meshNode.setAppearance(m_appearance);
        assert(StatusOK == status);
        status = m_meshNode.setGeometryBinding(m_geometryBinding);
        assert(StatusOK == status);

        static int32_t RenderOrer = 0;
        RenderOrer += renderOrderBuffer;
        setBlending(true);

        engine.addSprite(*this, RenderOrer);

        UNUSED(status);
    }

    Sprite2D::~Sprite2D()
    {
        m_engine.removeSprite(*this);

        m_scene.destroy(m_translateSpriteToCenter);
        m_scene.destroy(m_rotationNode);
        m_scene.destroy(m_scaleNode);
        m_scene.destroy(m_meshNode);
        m_scene.destroy(m_appearance);
    }

    void Sprite2D::setSize(float width, float height)
    {
        m_scaleNode.setScaling(width, height, 0.0f);
    }

    void Sprite2D::setPosition(float x, float y)
    {
        m_translateNode.setTranslation(x, Pos2D::s_WindowHeight - y, 0.0f);
    }

    void Sprite2D::getPosition(float& x, float& y) const
    {
        float unused;
        m_translateNode.getTranslation(x, y, unused);
        y = Pos2D::s_WindowHeight - y;
    }

    Vector2 Sprite2D::getAbsolute2DPosition() const
    {
        Vector3 position(0.0);

        const Node* node = &m_rootNode;
        while (0 != node)
        {
            if (node->getName() == std::string("T"))
            {
                float x, y, z;
                node->getTranslation(x, y, z);
                position += Vector3(x, y, z);
            }
            else if (node->getName() == std::string("R"))
            {
                float x, y, z;
                node->getRotation(x, y, z);

                // ############### HACK ################
                // Get the rotation angles in radians
                const float rotX = PlatformMath::Deg2Rad(x);
                const float rotY = PlatformMath::Deg2Rad(y);
                const float rotZ = PlatformMath::Deg2Rad(z);

                // Save some sin and cos values for reuse in the computations
                const float sinX = sin(rotX);
                const float cosX = cos(rotX);
                const float sinY = sin(rotY);
                const float cosY = cos(rotY);
                const float sinZ = sin(rotZ);
                const float cosZ = cos(rotZ);

                // Creation form below utilizes sign change in comparison to regular XYZ construction.
                // This change is tolerated back when angles are extracted back from the matrix in toRotationEulerXYZ() method

                Matrix33f matrix(
                    cosY * cosZ, cosY * sinZ, -sinY,
                    sinX * sinY * cosZ - cosX * sinZ, cosX * cosZ + sinX * sinY * sinZ, sinX * cosY,
                    sinX * sinZ + cosX * sinY * cosZ, cosX * sinY * sinZ - sinX * cosZ, cosX * cosY);

                // ############### ENDHACK ################
                position = Vector3(matrix * position);
            }
            else if (node->getName() == std::string("S"))
            {
                float x, y, z;
                node->getScaling(x, y, z);
                position = Vector3(x, y, z) * position;
            }

            node = node->getParent();
        }
        return Vector2(position.x, Pos2D::s_WindowHeight - position.y);
    }

    ramses_internal::Vector2 Sprite2D::getAbsolute2DSize() const
    {
        Vector3 size;
        m_scaleNode.getScaling(size.x, size.y, size.z);

        const Node* node = &m_rootNode;
        while (0 != node)
        {
            if (node->getName() == std::string("S"))
            {
                float x, y, z;
                node->getScaling(x, y, z);
                size = Vector3(x, y, z) * size;
            }

            node = node->getParent();
        }
        return Vector2(size.x, size.y);
    }

    void Sprite2D::setBlending(bool enabled)
    {
        if (enabled)
        {
            m_appearance.setBlendingOperations(ramses::EBlendOperation_Add, ramses::EBlendOperation_Add);
            m_appearance.setBlendingFactors(ramses::EBlendFactor_SrcAlpha, ramses::EBlendFactor_OneMinusSrcAlpha, ramses::EBlendFactor_One, ramses::EBlendFactor_One);
        }
        else
        {
            m_appearance.setBlendingOperations(ramses::EBlendOperation_Disabled, ramses::EBlendOperation_Disabled);
        }
    }

    void Sprite2D::setVisibility(bool enabled)
    {
        m_visibilityNode.setVisibility(enabled);
    }

    TexturedSprite2D::TexturedSprite2D(GameEngine& engine, Scene& scene, const Texture2D& texture, const Effect& effect, uint32_t renderOrderBuffer /*= 1*/)
        : Sprite2D(engine, scene, effect, renderOrderBuffer)
        , m_texture(texture)
        , m_sampler(*m_scene.createTextureSampler(
            ramses::ETextureAddressMode_Clamp,
            ramses::ETextureAddressMode_Clamp,
            ramses::ETextureSamplingMethod_Trilinear,
            m_texture))
    {
        ramses::UniformInput textureInput;
        status_t status = m_effect.findUniformInput("u_texture", textureInput);
        assert(status == StatusOK);
        m_appearance.setInputTexture(textureInput, m_sampler);

        const uint32_t texWidth = m_texture.getWidth();
        const uint32_t texHeight = m_texture.getHeight();
        setSize(float(texWidth), float(texHeight));
    }

    TexturedSprite2D::~TexturedSprite2D()
    {
        m_scene.destroy(m_sampler);
    }

    AnimatedSprite2D::AnimatedSprite2D(GameEngine& engine, ramses::Scene& scene, const Texture2D& texture, const Effect& effect, int32_t tilesX, int32_t tilesY, uint32_t renderOrderBuffer /*= 1*/)
        : TexturedSprite2D(engine, scene, texture, effect, renderOrderBuffer)
        , m_tilesX(tilesX)
        , m_tilesY(tilesY)
        , m_sizeX(1.0f / m_tilesX)
        , m_sizeY(1.0f / m_tilesY)
    {
        m_effect.findUniformInput("textureTile", m_textureTile);

        if (tilesX * tilesY > 1)
        {
            assert(m_textureTile.isValid());
        }

        m_effect.findUniformInput("iGlobalTime", m_time);

        setSize(m_sizeX * m_texture.getWidth(), m_sizeY * m_texture.getHeight());

        if (m_textureTile.isValid())
        {
            setTile(0, 0);
        }

        engine.addAnimatedSprite(*this);
    }

    AnimatedSprite2D::~AnimatedSprite2D()
    {
        m_engine.removeAnimatedSprite(*this);
    }

    void AnimatedSprite2D::setTile(int32_t x, int32_t y)
    {
        float sizeX = 1.0f / m_tilesX;
        float sizeY = 1.0f / m_tilesY;
        float offsetX = x * sizeX;
        float offsetY = y * sizeY;
        m_appearance.setInputValueVector4f(m_textureTile, sizeX, sizeY, offsetX, offsetY);
    }

    void AnimatedSprite2D::updateTime(float timeVal)
    {
        if (m_lastTime != 0.0f)
        {
            m_timeDiff = timeVal - m_lastTime;
        }
        m_lastTime = timeVal;

        if (m_time.isValid())
        {
            m_appearance.setInputValueFloat(m_time, timeVal);
        }
    }

}
