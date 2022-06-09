#pragma once
#include "GameObjectRectangle.h"
class LobbySlot :
    public GameObjectRectangle
{
public:

    LobbySlot(sf::RenderWindow* _window, Scene* _scene, int _controllerIndex);

    virtual void Update(float _deltaTime) override;
    virtual void Render() override;

    void AutoActivate();

protected:

    sf::Texture controllerIconTexture;
    sf::Sprite controllerIcon;
    sf::Texture buttonPromptIconTexture;
    sf::Sprite buttonPromptIcon;

    sf::Font font;
    sf::Text statusMessage;
    std::string statusMessageString;
    sf::Text promptMessage;

    int controllerIndex = 0;

    float promptFluctSpeed = 1.0f;
    float promptFluctMin = 0.5f;
    float promptFluctMax = 0.95f;
    float currentFluct = 0;

    bool noControllerStatus = false;
    bool unActiveStatus = false;
    bool activeStatus = false;

    void NoControllerStatus();
    void UnActivatedStatus();
    void ActivatedStatus();

    bool isAutoActive = false;
};

