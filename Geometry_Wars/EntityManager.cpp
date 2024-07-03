

#include "EntityManager.h"
#include "Entity.h"


EntityManager::EntityManager() {} //constructor


void EntityManager::update()
{
	removeDeadEntities(m_entities);

	//update entity by adding the listed entity in entitiesToAdd
	for (auto e : m_entitiesToAdd) 
	{
		m_entities.push_back(e);
		m_entityMap[e->tag()].push_back(e);
	}
	m_entitiesToAdd.clear();
	
}

void EntityManager::removeDeadEntities(EntityVec& vec)
{
	//reamove all dead element
	EntityVec activeEntityVec ;
	EntityMap activeEntityMap ;

	for (auto e : m_entities) 
	{
		if (e->isActive())
		{
			activeEntityVec.push_back(e);
			activeEntityMap[e->tag()].push_back(e);
		}
	}

	m_entities = activeEntityVec;
	m_entityMap = activeEntityMap;
}


std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
	auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));
	m_entitiesToAdd.push_back(entity);
	return entity;
}

const EntityVec& EntityManager::getEntities()
{
	return m_entities;
}

const EntityVec& EntityManager::getEntities(std::string& tag)
{
	return m_entityMap[tag] ;
}