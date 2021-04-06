#include "SceneGraph.h"


 std::unique_ptr<SceneGraph> SceneGraph::sceneGraphInstance = nullptr;

 std::unordered_map <GLuint, std::vector<Model*>> SceneGraph::sceneModels = std::unordered_map<GLuint, std::vector<Model*>>();

 std::map <std::string, GameObject*> SceneGraph::sceneGameObjects = std::map<std::string, GameObject*>();

 SceneGraph::SceneGraph()
 {

 }
SceneGraph* SceneGraph::GetInstance()
{
    if (sceneGraphInstance.get() == nullptr) {
        sceneGraphInstance.reset(new SceneGraph);
    }
	return sceneGraphInstance.get();
}

void SceneGraph::OnDestroy()
{
    if(sceneGameObjects.size() > 0) {
        for (auto go : sceneGameObjects) {
            delete go.second;
            go.second = nullptr;
        }
        sceneGameObjects.clear();
    }

    if (sceneModels.size() > 0) {
        for (auto entry : sceneModels) {
            if (entry.second.size() > 0) {
                for (auto m : entry.second) {
                    delete m;
                    m = nullptr;
                }
                entry.second.clear();
            }
        }
        sceneModels.clear();
    }
}

void SceneGraph::AddModel(Model* model)
{
    GLuint shader = model->GetShaderProgram();
    if (sceneModels.find(shader) == sceneModels.end()) {
        sceneModels.insert(std::pair<GLuint, std::vector<Model*>>(shader, std::vector<Model*>()));
        sceneModels[shader].reserve(30);
        sceneModels[shader].push_back(model);
    }
    sceneModels[shader].push_back(model);
}

void SceneGraph::AddGameObject(GameObject* go, std::string ID_)
{
    if (ID_ == "") {
        std::string newID = "GameObject" + std::to_string(sceneGameObjects.size() + 1);
        go->SetID(newID);
        sceneGameObjects[newID] = go;
    }
    else if (sceneGameObjects.find(ID_) == sceneGameObjects.end()) {
        go->SetID(ID_);
        sceneGameObjects[ID_] = go;
    }
    else {
        Debug::Error("Trying to add game object with tag " + ID_ + "that already exists", "scenegraph.cpp", __LINE__);
        std::string newID = "Game object" + std::to_string(sceneGameObjects.size() + 1);
        go->SetID(newID);
        sceneGameObjects[newID] = go;
    }
}

GameObject* SceneGraph::GetGameObject(std::string ID_) const
{
    if (sceneGameObjects.find(ID_) != sceneGameObjects.end()) {
        return sceneGameObjects[ID_];
   }
    return nullptr;
}

void SceneGraph::Update(const float deltaTime)
{
    for (auto go : sceneGameObjects) {
        go.second->Update(deltaTime);
    }
}

void SceneGraph::Render(Camera* camera)
{
    for (auto entry : sceneModels) {
        glUseProgram(entry.first);
        for (auto m : entry.second) {
            m->Render(camera);
        }
    }
}

SceneGraph::~SceneGraph()
{
    OnDestroy();
}
