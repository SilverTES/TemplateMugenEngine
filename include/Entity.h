#ifndef ENTITY_H
#define ENTITY_H

#include "MugenEngine.h"
#include "IPlayable.h"
//#include "Base.h"
//
//
//class Entity : public Base, public IPlayable
//{
//    public:
//
//        Entity();
//        virtual ~Entity();
//
//        virtual void update() = 0;
//        virtual void render() = 0;
//
//    protected:
//
//        Vec3 _pos;
//        Vec3 _vel;
//
//    private:
//};
enum
{
    POSITION = 10,
    VELOCITY
};


struct Component
{
    int _type;
    virtual Component *clone() const = 0;
    virtual ~Component() // Avoid warning when we want to delete Component !
    {

    }
};


template <class DERIVED>
struct ComponentHelper : public Component
{
    virtual Component *clone() const
    {
        return new DERIVED(static_cast<const DERIVED&>(*this));
    }
};


struct Position : public ComponentHelper<Position>
{
    int _x;
    int _y;
    int _z;

    Position(int x = 0, int y = 0, int z = 0)
    {
        _type = POSITION;
        _x = x;
        _y = y;
        _z = z;
    }
};

struct Velocity : public ComponentHelper<Velocity>
{
    int _x;
    int _y;
    int _z;

    Velocity(int x = 0, int y = 0, int z = 0)
    {
        _type = VELOCITY;
        _x = x;
        _y = y;
        _z = z;
    }
};

struct Entity : public IPlayable
{
    std::string _name="";

    Entity *_parent = nullptr;

    std::map<int, Component*> _mapMember;

    std::function<void(Entity*)> _update = nullptr;
    std::function<void(Entity*)> _render = nullptr;

    std::string name() const
    {
        return _name;
    }

    void setUpdate(std::function<void(Entity*)> update)
    {
        _update = update;
    }

    void setRender(std::function<void(Entity*)> render)
    {
        _render = render;
    }


    static Entity *cloneOf(Entity *original, std::string name = "")
    {


        Entity *clone = new Entity(*original);

        if (name == "")
            clone->_name = original->_name;
        else
            clone->_name = name;


        //clone = original;
        log ("--- Begin deep copy ---\n");
        std::map<int,Component*>::const_iterator it = original->_mapMember.begin();

        while (it != original->_mapMember.end())
        {
            //clone->_mapMember[it->first] = new Component(*(it->second));
            clone->_mapMember[it->first] = (*(it->second)).clone();
            it++;
        }
        return clone;
    }

    Entity(Entity *parent = nullptr, std::string name="")
    {
        _name = name;
        _parent = parent;

        log("- Entity created !\n");

    }
    virtual ~Entity()
    {
        std::map<int,Component*>::iterator it = _mapMember.begin();

        while (it != _mapMember.end())
        {
            if (it->second != nullptr)
            {
                log ("- Delete Component:"+ std::to_string(it->second->_type) + " of Entity: " + _name + "\n");
                delete it->second;
                it->second = nullptr;
            }

            it++;
        }
        _mapMember.clear();

        log("- Delete Entity: " + _name + "\n");
    }

    void add(Component* component)
    {
        _mapMember[component->_type] = component;
    }

    void del(int type)
    {
        if (_mapMember[type] != nullptr)
            delete _mapMember[type];
        _mapMember.erase(type);
    }


    template <class COMPONENT>
    COMPONENT *get()
    {
        COMPONENT component;
        return static_cast<COMPONENT*>(_mapMember[component._type]);
    }

    void update()
    {
        if (_update != nullptr)
            _update(this);
        else
            log("- " + _name + " update() not defined !\n");
    }

    void render()
    {


        if (_render != nullptr)
            _render(this);
        else
            log("- " + _name + " render() not defined !\n");

    }
};



#endif // ENTITY_H
