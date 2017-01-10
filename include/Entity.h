#ifndef ENTITY_H
#define ENTITY_H

#include "MugenEngine.h"
#include "IPlayable.h"

extern std::map<std::string, int> _mapComponentType; // extern for avoid multiple definition

inline int lastComponent()
{
    if (!_mapComponentType.empty())
    {

        // Get the highest element values in the map !
        auto it = std::max_element(_mapComponentType.begin(), _mapComponentType.end(),
                                   [](const std::pair<std::string, int>& p1, const std::pair<std::string, int>& p2)
        {
            return p1.second < p2.second;
        });

        return it->second;
    }
    else
        return 0;
}

inline int componentType (std::string componentName)
{
    if (_mapComponentType.find(componentName) == _mapComponentType.end())
    {

        _mapComponentType[componentName] = lastComponent()+1;
    }

    return _mapComponentType[componentName];
}

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
        _type = componentType("POSITION");

        //_type = POSITION;

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
        _type = componentType("VELOCITY");
        _x = x;
        _y = y;
        _z = z;
    }
};

struct Tempo : public ComponentHelper<Tempo>
{
    int _tempo;
    int _duration;
    bool _tic;

    Tempo(int duration = 100)
    {
        _type = componentType("TEMPO");
        _tempo = 0;
        _duration = duration;
        _tic = false;
    }

    void update()
    {
        _tempo++;

        if (_tempo < _duration)
            _tic = false;

        if (_tempo >_duration)
        {
            _tic = true;
            _tempo = 0;
        }
    }
};


struct Lambda : public ComponentHelper<Lambda>
{
    int _lambda;

    Lambda()
    {
        _type = componentType("LAMBDA");
        _lambda = 0;
    }
};

struct Entity : public IPlayable
{
    int _id = 0;
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
        //log ("--- Begin deep copy ---\n");
        std::map<int,Component*>::const_iterator it = original->_mapMember.begin();

        while (it != original->_mapMember.end())
        {
            //clone->_mapMember[it->first] = new Component(*(it->second));
            clone->_mapMember[it->first] = (*(it->second)).clone();
            it++;
        }
        return clone;
    }

    Entity(Entity *parent = nullptr, std::string name="", int id = 0)
    {
        _id = id;
        _name = name;
        _parent = parent;

        //log("- Entity created !\n");

    }
    virtual ~Entity()
    {
        std::map<int,Component*>::iterator it = _mapMember.begin();

        while (it != _mapMember.end())
        {
            if (it->second != nullptr)
            {
                //log ("- Delete Component:"+ std::to_string(it->second->_type) + " of Entity: " + _name + "\n");
                delete it->second;
                it->second = nullptr;
            }

            it++;
        }
        _mapMember.clear();

        //log("- Delete Entity: " + _name + "\n");
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
