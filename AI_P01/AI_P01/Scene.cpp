#include "Game.h"
#include "GameObject.h"
#include "Collider.h"
#include "Scene.h"
#include "GoblinHordeUI.h"

Scene::Scene() 
{
	game = nullptr;
	window = nullptr;
	UserInterface = new GoblinHordeUI(window);
}

Scene::Scene(Game* _gameClass, sf::RenderWindow* _window)
{
	game = _gameClass;
	window = _window;
}

Scene::~Scene()
{
	DeleteAllSceneObjects();
}

void Scene::Start()
{
	SceneActive = true;
}

void Scene::Update(float _deltaTime)
{
	if (SceneActive)
	{
		window->clear();

		int Length = (int)sceneObjects.size();
		//Loop through all SceneObjects
		for (int i = 0; i < Length; i++)
		{
			//Call the Update on CGameObject and pass through deltaTime
			sceneObjects[i]->Update(_deltaTime);
			sceneObjects[i]->Render();
		}

		UserInterface->Render(window);
			
		
	}
	window->display();
	CollisionCheck();
	//Add/Destroy any CGameObjects in queues
	ClearAddSceneObjectQueue();
	ClearDestroySceneObjectQueue();
}

void Scene::DestroySceneObject(GameObject* _object)
{
	// check if object already exists in queue
	int length = (int)destroySceneObjectQueue.size();
	for (int i = 0; i < length; i++)
	{
		std::vector<GameObject*>::iterator it = destroySceneObjectQueue.begin() + i;
		if (*it == _object)
		{
			return;
		}
	}
	
	//Add CGameObject ptr to queue to be deleted at end of Update()
	destroySceneObjectQueue.push_back(_object);
}

void Scene::AddSceneObject(GameObject* _object)
{
	//Add CGameObject ptr to queue to be added at end of Update()
	addSceneObjectQueue.push_back(_object);
}

void Scene::ChangeScene(std::string _sceneName)
{
	//Set true to stop Update
	SceneActive = false;
	//Pass scene name to CGame() class
	game->ChangeScene(_sceneName);
}

GoblinHordeUI* Scene::getUI()
{
	return UserInterface;
}

void Scene::ClearDestroySceneObjectQueue()
{
	//Check if there is anything to delete
	if ((int)destroySceneObjectQueue.size() > 0)
	{
		int Length = (int)sceneObjects.size();
		//create iterator that points to start of queue
    		std::vector<GameObject*>::iterator iter = destroySceneObjectQueue.begin();
		//Loop through all CGameObjects stored in SceneObjects to find the one to delete
		for (int i = 0; i < Length; i++)
		{
			if (*iter == sceneObjects[i])
			{
				std::vector<GameObject*>::iterator sceneObj_iter = sceneObjects.begin() + i;

				//Create ptr to CGameObject that needs to be deleted
				GameObject* SceneObjectToDelete = *sceneObj_iter;
				//Remove from SceneObjects
				sceneObjects.erase(sceneObj_iter);
				//Remove from queue
				destroySceneObjectQueue.erase(iter);
				//delete CGameObject class
				delete SceneObjectToDelete;

				//The length of both SceneOjects and DestroySceneObjectQueue has changed so break and call function again
				break;
			}
		}
		ClearDestroySceneObjectQueue();
	}
}

void Scene::ClearAddSceneObjectQueue()
{
	//Check if any CGameObjects need to be added to SceneObject vector
	if (addSceneObjectQueue.size() > 0)
	{
		//Get iterator to beginning of queue
		std::vector<GameObject*>::iterator iter = addSceneObjectQueue.begin();
		//Add CGameObject ptr to SceneObjects vector
		sceneObjects.push_back(*iter);
		//Remove from queue
		addSceneObjectQueue.erase(iter);
		//call function again until size() returns 0
		ClearAddSceneObjectQueue();
	}
}

void Scene::DeleteAllSceneObjects()
{
	int SceneObjectsLength = (int)sceneObjects.size();
	for (int i = 0; i < SceneObjectsLength; i++)
	{
		std::vector<GameObject*>::iterator iter = sceneObjects.begin();
		//CGameObject* ObjectToDelete = *iter;
		if (*iter != nullptr)
		{
			delete* iter;
			*iter = nullptr;
		}
		sceneObjects.erase(iter);
	}

	int AddObjectQueueLength = (int)addSceneObjectQueue.size();
	for (int i = 0; i < AddObjectQueueLength; i++)
	{
		std::vector<GameObject*>::iterator iter = addSceneObjectQueue.begin();
		if (*iter != nullptr)
		{
			delete* iter;
			*iter = nullptr;
		}
		addSceneObjectQueue.erase(iter);
	}
}

void Scene::CollisionCheck()
{
	std::vector<GameObject*>::iterator otherObjectIterator;
	for (int i = 0; i < (int)sceneObjects.size(); i++)
	{
		otherObjectIterator = sceneObjects.begin() + i;
		GameObject* other = *otherObjectIterator;
		if (other->GetCollider() != nullptr)
		{
			std::vector<GameObject*>::iterator it;
			for (int j = 0; j < (int)sceneObjects.size(); j++)
			{
				it = sceneObjects.begin() + j;
				GameObject* go = *it;
				if (go != other)
				{
					if (go->GetCollider() != nullptr)
					{
						go->GetCollider()->CheckForCollision(other);
					}
					
				}

			}
		}
	}
}
