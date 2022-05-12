#include "Game.h"
#include "GameObject.h"
#include "Collider.h"
#include "Scene.h"
#include "GoblinHordeUI.h"

Scene::Scene() 
{
	game = nullptr;
	window = nullptr;
	userInterface = nullptr;
}

Scene::Scene(Game* _gameClass, sf::RenderWindow* _window)
{
	game = _gameClass;
	window = _window;
	userInterface = new GoblinHordeUI(window);
}

Scene::~Scene()
{
	DeleteAllSceneObjects();
}

void Scene::Start()
{
	sceneActive = true;
}

void Scene::Update(float _deltaTime)
{
	if (sceneActive)
	{
		window->clear();

		int length = (int)sceneObjects.size();
		//Loop through all SceneObjects
		for (int i = 0; i < length; i++)
		{
			//Call the Update on CGameObject and pass through deltaTime
			sceneObjects[i]->Update(_deltaTime);
			sceneObjects[i]->Render();
		}

		userInterface->Render(window);
			
		
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
	sceneActive = false;
	//Pass scene name to CGame() class
	game->ChangeScene(_sceneName);
}

GoblinHordeUI* Scene::GetUI() // coding convention issue
{
	return userInterface;
}

void Scene::ClearDestroySceneObjectQueue()
{
	//TODO: Re-Write these functions to use iteration better
	//Check if there is anything to delete
	if ((int)destroySceneObjectQueue.size() > 0)
	{
		int length = (int)sceneObjects.size();
		//create iterator that points to start of queue
    	std::vector<GameObject*>::iterator iter = destroySceneObjectQueue.begin();
		//Loop through all CGameObjects stored in SceneObjects to find the one to delete
		for (int i = 0; i < length; i++)
		{
			if (*iter == sceneObjects[i])
			{
				std::vector<GameObject*>::iterator sceneObj_iter = sceneObjects.begin() + i;

				//Create ptr to CGameObject that needs to be deleted
				GameObject* sceneObjectToDelete = *sceneObj_iter;
				//Remove from SceneObjects
				sceneObjects.erase(sceneObj_iter);
				//Remove from queue
				destroySceneObjectQueue.erase(iter);
				//delete CGameObject class
				delete sceneObjectToDelete;

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

	//TODO: Re-Write these functions to use iteration better
	int sceneObjectsLength = (int)sceneObjects.size();
	for (int i = 0; i < sceneObjectsLength; i++)
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

	int addObjectQueueLength = (int)addSceneObjectQueue.size();
	for (int i = 0; i < addObjectQueueLength; i++)
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
	//TODO: Re-Write these functions to use iteration better
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
