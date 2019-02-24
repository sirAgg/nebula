#pragma once
//------------------------------------------------------------------------------
/**
    @class AudioFeature::AudioFeatureUnit

    (C) 2019 Individual contributors, see AUTHORS file
*/
#include "game/featureunit.h"

namespace Audio { class AudioServer; }

//------------------------------------------------------------------------------
namespace AudioFeature
{

class AudioFeatureUnit : public Game::FeatureUnit    
{
	__DeclareClass(AudioFeatureUnit)
	__DeclareSingleton(AudioFeatureUnit)

public:

    /// constructor
    AudioFeatureUnit();
    /// destructor
    ~AudioFeatureUnit();

	/// Called upon activation of feature unit
	void OnActivate();
	/// Called upon deactivation of feature unit
	void OnDeactivate();
private:
	Ptr<Audio::AudioServer> server;
};

} // namespace AudioFeature
//------------------------------------------------------------------------------
