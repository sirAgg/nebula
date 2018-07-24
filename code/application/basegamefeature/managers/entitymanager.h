#pragma once
//------------------------------------------------------------------------------
/**
	Entity Manager

	Keeps track of all existing entites

	(C) 2018 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "core/refcounted.h"
#include "core/singleton.h"
#include "ids/idgenerationpool.h"
#include "game/entity.h"
#include "game/manager.h"
#include "util/delegate.h"
#include "game/component/basecomponent.h"

namespace Game {

class EntityManager : public Game::Manager
{
	__DeclareClass(EntityManager)
	__DeclareSingleton(EntityManager)
public:
	/// constructor
	EntityManager();
	/// destructor
	~EntityManager();

	/// Generate a new entity.
	Entity NewEntity();
	
	/// Delete an entity.
	void DeleteEntity(const Entity& e);
	
	/// Check if an entity ID is still valid.
	bool IsAlive(const Entity& e) const;

	/// Register a deletion callback to an entity
	void RegisterDeletionCallback(const Entity& e, const Ptr<BaseComponent>& component);

	/// Deregister a deletion callback to an entity. Note that this is not super fast.
	void DeregisterDeletionCallback(const Entity& e, const Ptr<BaseComponent>& component);
private:
	Ids::IdGenerationPool pool;

	/// Contains all callbacks for deletion to components for each entity
	Util::HashTable<Entity, Util::Array<Util::Delegate<Entity>>> deletionCallbacks;
};

} // namespace Game