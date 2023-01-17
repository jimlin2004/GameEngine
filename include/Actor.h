#ifndef GE_ACTOR_H
#define GE_ACTOR_H

#include "Graphics.h"
#include "ActorComponent/inputComponent/InputComponent.h"
#include "GameObject.h"
#include "ActorComponent/Material/Material.h"
#include "ActorComponent/Mesh/Mesh.h"

namespace GameEngine
{
    //遊戲中的角色基類(不可使用Input event)
    class Actor: public GameObject
    {
    public:
        float x, y;

        Actor();
        Actor(float x, float y);
        Actor(float x, float y, float width, float height);
        ~Actor();
        virtual void HandleEvent();
        //渲染
        virtual void render();
        //設定角色在世界的位置
        virtual void setPosition(float x, float y);
        //綁定角色的Mesh
        template <class T>
        void bindMesh()
        {
            this->mesh->bindMesh<T>();
        }
    protected:
        Material* material;
        Mesh* mesh;
    };

    //可操作的角色(支援Input event)
    class Character: public Actor
    {
    public:
        Character();
        Character(float x, float y);
        Character(float x, float y, float width, float height);
        ~Character();
        virtual void setInputEvent();
    protected:
        //負責註冊InputEvent的Component
        InputComponent* playerInputComponent;
    };
}

#endif