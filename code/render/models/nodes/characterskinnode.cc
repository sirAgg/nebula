//------------------------------------------------------------------------------
//  charactermaterialskinnode.cc
//  (C) 2011-2013 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "render/stdneb.h"
#include "characterskinnode.h"
#include "coregraphics/shaderserver.h"

namespace Models
{

using namespace Util;
using namespace Models;
using namespace IO;
using namespace CoreGraphics;
using namespace Resources;

//------------------------------------------------------------------------------
/**
*/
CharacterSkinNode::CharacterSkinNode()
{
    this->skinnedShaderFeatureBits = ShaderServer::Instance()->FeatureStringToMask("Skinned");
}

//------------------------------------------------------------------------------
/**
*/
CharacterSkinNode::~CharacterSkinNode()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
bool
CharacterSkinNode::Load(const Util::FourCC& fourcc, const Util::StringAtom& tag, const Ptr<IO::BinaryReader>& reader)
{
    bool retval = true;
    if (FourCC('NSKF') == fourcc)
    {
        // NumSkinFragments
        this->ReserveFragments(reader->ReadInt());
    }
    else if (FourCC('SFRG') == fourcc)
    {
        // SkinFragment
        IndexT primGroupIndex = reader->ReadInt();
        Array<IndexT> jointPalette;
        SizeT numJoints = reader->ReadInt();
        jointPalette.Reserve(numJoints);
        IndexT i;
        for (i = 0; i < numJoints; i++)
        {
            jointPalette.Append(reader->ReadInt());
        }
        this->AddFragment(primGroupIndex, jointPalette);
    }
    else
    {
        retval = PrimitiveNode::Load(fourcc, tag, reader);
    }
    return retval;
}

//------------------------------------------------------------------------------
/**
*/
void
CharacterSkinNode::ReserveFragments(SizeT numFragments)
{
    this->skinFragments.Clear();
    this->skinFragments.Reserve(numFragments);
}

//------------------------------------------------------------------------------
/**
*/
void
CharacterSkinNode::AddFragment(IndexT primGroupIndex, const Util::Array<IndexT>& jointPalette)
{
    Fragment fragment;
    this->skinFragments.Append(fragment);
    this->skinFragments.Back().primGroupIndex = primGroupIndex;
    this->skinFragments.Back().jointPalette = jointPalette;
}

//------------------------------------------------------------------------------
/**
void
CharacterSkinNode::ApplySharedState(IndexT frameIndex)
{
    n_assert(this->managedMesh.isvalid());
    
    // apply render states, skip ShapeNode class, because the skinned character renderer manages this itself
    StateNode::ApplySharedState(frameIndex);

    // set the Skinned shader feature bit so that the shader
    // variation for skinned geometry is used instead of static geometry
	if (SkinningTechnique::GPUSkinning == Characters::CharacterServer::Instance()->GetSkinningTechnique())
	{
		//ShaderServer::Instance()->SetFeatureBits(this->skinnedShaderFeatureBits);
	}

	const Ptr<Mesh>& mesh = this->managedMesh->GetMesh();
	mesh->ApplySharedMesh();

    // primitives must be applied in node instance, since each 
    // node may render several skin fragments!
}
*/

} // namespace Characters
