#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <memory>
#include <unordered_map>
#include <map>
#include <vector>

#include "GameObject.h"

class SceneGraph
{
public:
	SceneGraph(const SceneGraph&) = delete;
	SceneGraph(SceneGraph&&) = delete;
	SceneGraph& operator=(const SceneGraph&) = delete;
	SceneGraph& operator= (SceneGraph&&) = delete;
	
	static SceneGraph* GetInstance();
	void OnDestroy();
	void AddModel(Model* model);
	void AddGameObject(GameObject* go, std::string ID_ = "");
	GameObject* GetGameObject(std::string ID_) const;

	void Update(const float dletaTime);
	void Render(Camera* camera);

private:
	SceneGraph();
	~SceneGraph();

	static std::unique_ptr<SceneGraph> sceneGraphInstance;
	friend std::default_delete<SceneGraph>;

	static std::unordered_map < GLuint, std::vector<Model*>> sceneModels;
	static std::map<std::string, GameObject*> sceneGameObjects;
};
#endif
