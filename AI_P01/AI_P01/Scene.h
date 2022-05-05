#pragma once
#include "SFML/Graphics.hpp"

class Scene
{

public:

	Scene(class Game* _gameClass, sf::RenderWindow* _window);
	virtual ~Scene();

	//Spawn all objects for the scene
	virtual void Start();

	//Called from the main while loop in CGame() class
	virtual void Update(float _deltaTime);

	//Adds CGameObject() classes that need to be deleted to the DestroySceneObjectQueue vector
	//Objects will not be deleted until ClearDestroySceneObjectQueue() is called at the end of Update()
	virtual void DestroySceneObject(class GameObject* _object);

	//Adds CGameObject() classes that need to be spawned to the AddSceneObjectsQueue vector
	//Objects will not be added until ClearAddSceneObjectQueue() is called at the end of Update()
	virtual void AddSceneObject(class GameObject* _object);

	//Calls ChangeScene() in CGame(), CGameObject() classes do not have access to CGame() class so they will call this funcion
	void ChangeScene(std::string _sceneName);

	class GoblinHordeUI* getUI();

protected:

	Scene();

	//Called at the end of the Update() to delete all CGameObject classes in the queue
	virtual void ClearDestroySceneObjectQueue();

	//Called at the end of the Update() to add/instantiate all CGameObject classes in the queue
	virtual void ClearAddSceneObjectQueue();

	class GoblinHordeUI* UserInterface;

	class Game* game;

	sf::RenderWindow* window;

	//All CGameObjects that exist in the scene are stored here
	std::vector<class GameObject*> sceneObjects;

	//All CGameObjects that need to be deleted are stored here
	std::vector<class GameObject*> destroySceneObjectQueue;

	//All CGameObjects that need to be added are stored here
	std::vector<class GameObject*> addSceneObjectQueue;

	bool SceneActive = true;

	void DeleteAllSceneObjects();

	void CollisionCheck();
};

