//------------------------------------------------------------------------------
//  graphicscomponent.cc
//  (C) 2018 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "graphicscomponent.h"
#include "basegamefeature/messages/setlocaltransform.h"
#include "graphicsfeature/messages/graphicsprotocol.h"
#include "models/modelcontext.h"
#include "graphics/graphicsserver.h"
#include "visibility/visibilitycontext.h"

namespace GraphicsFeature
{

__ImplementClass(GraphicsFeature::GraphicsComponent, 'GpCM', GraphicsFeature::GraphicsComponentBase)

//------------------------------------------------------------------------------
/**
*/
GraphicsComponent::GraphicsComponent()
{
}

//------------------------------------------------------------------------------
/**
*/
GraphicsComponent::~GraphicsComponent()
{
}

//------------------------------------------------------------------------------
/**
*/
void
GraphicsComponent::SetupAcceptedMessages()
{
	__RegisterMsg(Msg::SetLocalTransform, UpdateTransform)
	__RegisterMsg(Msg::SetModel, SetModel)
}

//------------------------------------------------------------------------------
/**
*/
void
GraphicsComponent::OnActivate(const uint32_t& instance)
{
	auto gfxEntity = Graphics::CreateEntity();
	this->data.Get<GRAPHICSENTITY>(instance) = gfxEntity.id;
	Models::ModelContext::RegisterEntity(gfxEntity);
	Models::ModelContext::Setup(gfxEntity, "mdl:Buildings/castle_tower.n3", "NONE");
	Models::ModelContext::SetTransform(gfxEntity, Math::matrix44::identity());
	Visibility::ObservableContext::RegisterEntity(gfxEntity);
	Visibility::ObservableContext::Setup(gfxEntity, Visibility::VisibilityEntityType::Model);
}

//------------------------------------------------------------------------------
/**
*/
void
GraphicsComponent::OnDeactivate(const uint32_t& instance)
{
	Graphics::GraphicsEntityId gfxEntity = { this->data.Get<GRAPHICSENTITY>(instance) };
	Models::ModelContext::DeregisterEntity(gfxEntity);
	Visibility::ObservableContext::DeregisterEntity(gfxEntity);
	Graphics::DestroyEntity(gfxEntity);
}

//------------------------------------------------------------------------------
/**
*/
void
GraphicsComponent::UpdateTransform(const Game::Entity & entity, const Math::matrix44 & transform)
{
	auto instance = this->GetInstance(entity);
	if (instance != InvalidIndex)
	{
		Graphics::GraphicsEntityId gfxEntity = { this->data.Get<GRAPHICSENTITY>(instance) };
		Models::ModelContext::SetTransform(gfxEntity, transform);
	}
}

//------------------------------------------------------------------------------
/**
*/
void GraphicsComponent::SetModel(const Game::Entity & entity, const Util::String & path)
{
	auto instance = this->GetInstance(entity);
	if (instance != InvalidIndex)
	{
		Graphics::GraphicsEntityId gfxEntity = { this->data.Get<GRAPHICSENTITY>(instance) };
		Models::ModelContext::ChangeModel(gfxEntity, path, "NONE");
	}
}

} // namespace GraphicsFeature
