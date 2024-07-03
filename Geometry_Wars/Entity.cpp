
#include "Entity.h"

//constructor
Entity::Entity(const size_t& id, const std::string& tag)
    : m_id(id)
    , m_tag(tag)
{
    // Initialize components
    cTransform  = std::make_shared<CTransform>();
    cShape      = std::make_shared<CShape>();
    cCollision  = std::make_shared<CCollision>();
    cInput      = std::make_shared<CInput>();
    cScore      = std::make_shared<CScore>();
    cLifespan   = std::make_shared<CLifespan>();
}

bool Entity::isActive() const
{
    return m_active;
}

const std::string& Entity::tag() const
{
    return m_tag;
}

const size_t Entity::id() const
{
    return m_id;
}

void Entity::destroy()
{
    m_active = false;
}
