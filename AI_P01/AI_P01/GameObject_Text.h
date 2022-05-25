#pragma once
#include "GameObject.h"
class GameObject_Text :
    public GameObject
{
public:

    GameObject_Text(sf::RenderWindow* _window, class Scene* _scene, std::string _text);
    // Render() override. called every frame from Scene() class
    virtual void Render() override;

    void SetText(std::string _text);

protected:

    sf::Text textObject;
    sf::Font font;
    std::string text = "";
};

