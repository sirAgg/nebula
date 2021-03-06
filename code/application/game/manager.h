#pragma once
//------------------------------------------------------------------------------
/**
    @struct Game::ManagerAPI

    A Manager is just a bundle of function pointers to static or global functions
    that is called by the Game::FeatureUnit it is attached to.
    The managers context/state can be implemented as the developer sees fit, but
    will most likely be some global or static singleton.
    
    @see NebulaApplicationGameManagers

    @copyright
    (C) 2020 Individual contributors, see AUTHORS file
*/
#include "core/refcounted.h"
#include "ids/id.h"

//------------------------------------------------------------------------------
namespace Game
{

//------------------------------------------------------------------------------
/**
*/
ID_32_TYPE(ManagerHandle)

//------------------------------------------------------------------------------
/**
*/
struct ManagerAPI
{
    /// called when attached to game server
    void(*OnActivate)() = nullptr;
    /// called when removed from game server
    void(*OnDeactivate)() = nullptr;
    /// called before frame by the game server
    void(*OnBeginFrame)() = nullptr;
    /// called per-frame by the game server
    void(*OnFrame)() = nullptr;
    /// called after frame by the game server
    void(*OnEndFrame)() = nullptr;
    /// called after loading game state
    void(*OnLoad)() = nullptr;
    /// called before saving game state
    void(*OnSave)() = nullptr;
    /// called by Game::Server::Start()
    void(*OnStart)() = nullptr;
    /// render a debug visualization 
    void(*OnRenderDebug)() = nullptr;
};

}; // namespace Game
//------------------------------------------------------------------------------
 
    
