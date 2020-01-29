#include "stdneb.h"
#include "scenes.h"

using namespace Timing;
using namespace Graphics;
using namespace Visibility;
using namespace Models;

namespace BenchmarkSceneData
{

Graphics::GraphicsEntityId ground;
Util::Array<Graphics::GraphicsEntityId> entities;
Util::Array<Util::String> entityNames;
Util::Array<Graphics::GraphicsEntityId> pointLights;
Util::Array<Graphics::GraphicsEntityId> spotLights;

//------------------------------------------------------------------------------
/**
*/
static const char*
GraphicsEntityToName(GraphicsEntityId id)
{
    if (ModelContext::IsEntityRegistered(id)) return "Model";
    if (Lighting::LightContext::IsEntityRegistered(id)) return "Light";
    return "Entity";
}


//------------------------------------------------------------------------------
/**
    Open scene, load resources
*/
void OpenScene()
{
    ground = Graphics::CreateEntity();
    Graphics::RegisterEntity<ModelContext, ObservableContext>(ground);
    ModelContext::Setup(ground, "mdl:environment/plcholder_world.n3", "Viewer");
    ModelContext::SetTransform(ground, Math::matrix44::multiply(Math::matrix44::scaling(1000, 1, 1000), Math::matrix44::translation(Math::float4(0, 0, 0, 1))));
    entities.Append(ground);
    entityNames.Append("Ground");

    // setup visibility
    ObservableContext::Setup(ground, VisibilityEntityType::Model);

    const Util::StringAtom modelRes[] = { "mdl:Units/Unit_Archer.n3",  "mdl:Units/Unit_Footman.n3",  "mdl:Units/Unit_Spearman.n3" };
    //const Util::StringAtom modelRes[] = { "mdl:system/placeholder.n3",  "mdl:system/placeholder.n3",  "mdl:system/placeholder.n3" };
    const Util::StringAtom skeletonRes[] = { "ske:Units/Unit_Archer.nsk3",  "ske:Units/Unit_Footman.nsk3",  "ske:Units/Unit_Spearman.nsk3" };
    const Util::StringAtom animationRes[] = { "ani:Units/Unit_Archer.nax3",  "ani:Units/Unit_Footman.nax3",  "ani:Units/Unit_Spearman.nax3" };

    ModelContext::BeginBulkRegister();
    ObservableContext::BeginBulkRegister();
    static const int NumModels = 40;
    for (IndexT i = -NumModels; i < NumModels; i++)
    {
        for (IndexT j = -NumModels; j < NumModels; j++)
        {
            Graphics::GraphicsEntityId ent = Graphics::CreateEntity();
            Graphics::RegisterEntity<ModelContext, ObservableContext>(ent);
            entities.Append(ent);
            Util::String sid;
            sid.Format("%s: %d", GraphicsEntityToName(ent), ent);
            entityNames.Append(sid);

            const IndexT resourceIndex = ((i + NumModels) * NumModels + (j + NumModels)) % 3;
            const float timeOffset = Math::n_rand();// (((i + NumModels)* NumModels + (j + NumModels)) % 4) / 3.0f;

            // create model and move it to the front
            ModelContext::Setup(ent, modelRes[resourceIndex], "NotA");
            ModelContext::SetTransform(ent, Math::matrix44::translation(Math::float4(i * 16, 0, j * 16, 1)));
            ObservableContext::Setup(ent, VisibilityEntityType::Model);

            //Characters::CharacterContext::Setup(ent, skeletonRes[resourceIndex], animationRes[resourceIndex], "Viewer");
            //Characters::CharacterContext::PlayClip(ent, nullptr, 0, 0, Characters::Append, 1.0f, 1, Math::n_rand() * 100.0f, 0.0f, 0.0f, Math::n_rand() * 100.0f);
        }
    }
    ModelContext::EndBulkRegister();
    ObservableContext::EndBulkRegister();
};

//------------------------------------------------------------------------------
/**
    Close scene, clean up resources
*/
void CloseScene()
{
    n_error("implement me!");
};

//------------------------------------------------------------------------------
/**
    Per frame callback
*/
void StepFrame()
{
    // animate the spotlights
    IndexT i;
    for (i = 0; i < spotLights.Size(); i++)
    {
        Math::matrix44 spotLightTransform;
        spotLightTransform = Math::matrix44::rotationyawpitchroll(Graphics::GraphicsServer::Instance()->GetTime() * 2 + i, Math::n_deg2rad(-55), 0);
        spotLightTransform.set_position(Lighting::LightContext::GetTransform(spotLights[i]).get_position());
        Lighting::LightContext::SetTransform(spotLights[i], spotLightTransform);
    }

    /*
        Math::matrix44 globalLightTransform = Lighting::LightContext::GetTransform(globalLight);
        Math::matrix44 rotY = Math::matrix44::rotationy(Math::n_deg2rad(0.1f));
        Math::matrix44 rotX = Math::matrix44::rotationz(Math::n_deg2rad(0.05f));
        globalLightTransform = globalLightTransform * rotX * rotY;
        Lighting::LightContext::SetTransform(globalLight, globalLightTransform);
    */
};

//------------------------------------------------------------------------------
/**
*/
void RenderUI()
{
    //Models::ModelId model = ModelContext::GetModel(this->entity);
    //auto modelPool = Resources::GetStreamPool<Models::StreamModelPool>();
    //auto resource = modelPool->GetName(model);    
    //ImGui::Separator();
    //ImGui::Text("Resource: %s", resource.AsString().AsCharPtr());
    //ImGui::Text("State: %s", stateToString(modelPool->GetState(model)));
    //if (ImGui::Button("Browse"))
    //{
    //    ImGui::OpenPopup("Browse for Model");        
    //    this->Browse();
    //}
    //if (ImGui::BeginPopupModal("Browse for Model"))
    //{
    //    ImGui::BeginChild("##browserheader", ImVec2(0, 300), true);// ImGui::GetTextLineHeightWithSpacing() + ImGui::GetStyle().ItemSpacing.y));
    //    ImGui::Columns(2);
    //    ImGui::Text("Folder");
    //    for (int i = 0; i < this->folders.Size(); i++)
    //    {
    //        if (ImGui::Selectable(this->folders[i].AsCharPtr(), i == this->selectedFolder))
    //        {
    //            this->selectedFolder = i;
    //            this->files = IO::IoServer::Instance()->ListFiles("mdl:" + this->folders[i], "*");
    //        }
    //    }
    //    ImGui::NextColumn();
    //    ImGui::Text("Files");
    //        
    //    for (int i = 0; i < this->files.Size(); i++)
    //    {
    //        if (ImGui::Selectable(this->files[i].AsCharPtr(), i == this->selectedFile))
    //        {
    //            this->selectedFile = i;                    
    //        }
    //    }
    //    ImGui::EndChild();
    //    if (ImGui::Button("OK",ImVec2(120, 40))) 
    //    {
    //        ImGui::CloseCurrentPopup(); 
    //        Util::String file = "mdl:" + this->folders[this->selectedFolder] + "/" + this->files[this->selectedFile];                                   
    //        ModelContext::ChangeModel(this->entity, file, "Viewer");
    //    }
    //    ImGui::SameLine();
    //    if (ImGui::Button("Cancel",ImVec2(120, 40))) { ImGui::CloseCurrentPopup(); }
    //    ImGui::EndPopup();
    //}

    ImGui::Begin("Entities", nullptr, 0);
    ImGui::SetWindowSize(ImVec2(240, 400));
    ImGui::BeginChild("##entities", ImVec2(0, 300), true);

    static int selected = 0;
    for (int i = 0; i < entityNames.Size(); i++)
    {
        if (ImGui::Selectable(entityNames[i].AsCharPtr(), i == selected))
        {
            selected = i;
        }
    }
    ImGui::EndChild();
    ImGui::End();
    auto id = entities[selected];
    if (ModelContext::IsEntityRegistered(id))
    {
        Im3d::Mat4 trans = ModelContext::GetTransform(id);
        if (Im3d::Gizmo("GizmoEntity", trans))
        {
            ModelContext::SetTransform(id, trans);
        }
    }
    else if (Lighting::LightContext::IsEntityRegistered(id))
    {
        Im3d::Mat4 trans = Lighting::LightContext::GetTransform(id);
        if (Im3d::Gizmo("GizmoEntity", trans))
        {
            Lighting::LightContext::SetTransform(id, trans);
        }
    }
};

} // namespace ClusteredSceneData


Scene BenchmarkScene =
{
    "BenchmarkScene",
    BenchmarkSceneData::OpenScene,
    BenchmarkSceneData::CloseScene,
    BenchmarkSceneData::StepFrame,
    BenchmarkSceneData::RenderUI
};