#ifndef ENTITY_H
#define ENTITY_H

#include "MugenEngine.h"
#include "IContainer.h"
#include "IPlayable.h"

extern std::map<std::string, int> _mapComponentType; // extern for avoid multiple definition

inline int componentType (std::string componentName, bool createNewComponentType = false)
{
    // if Name of component don't exist then create a new component name
    // by increase +1 with the highest id of component !
    if (_mapComponentType.find(componentName) == _mapComponentType.end())
    {
        if (createNewComponentType)
        {
            int lastComponent = -1;

            if (!_mapComponentType.empty())
            {
                // Get the highest element values in the map !
                auto it = std::max_element(_mapComponentType.begin(), _mapComponentType.end(),
                                           [](const std::pair<std::string, int>& p1, const std::pair<std::string, int>& p2)
                {
                    return p1.second < p2.second;
                });

                lastComponent = it->second;

            }

            _mapComponentType[componentName] = lastComponent+1;
        }
        else
        {
            return 0;
        }
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
} __attribute__((packed));


template <class DERIVED>
struct ComponentHelper : public Component
{
    virtual Component *clone() const
    {
        return new DERIVED(static_cast<const DERIVED&>(*this));
    }
} __attribute__((packed));


struct Position : public ComponentHelper<Position>
{
    int _x;
    int _y;
    int _z;

    Position(int x = 0, int y = 0, int z = 0)
    {
        _type = componentType("POSITION", true);

        //_type = POSITION;

        _x = x;
        _y = y;
        _z = z;
    }
} __attribute__((packed));

struct Velocity : public ComponentHelper<Velocity>
{
    int _x;
    int _y;
    int _z;

    Velocity(int x = 0, int y = 0, int z = 0)
    {
        _type = componentType("VELOCITY", true);
        _x = x;
        _y = y;
        _z = z;
    }
} __attribute__((packed));

struct Tempo : public ComponentHelper<Tempo>
{
    int _tempo;
    int _duration;
    bool _tic;

    Tempo(int duration = 100)
    {
        _type = componentType("TEMPO", true);
        _tempo = 0;
        _duration = duration;
        _tic = false;
    }

    void update()
    {
        ++_tempo;

        if (_tempo < _duration)
            _tic = false;

        if (_tempo >_duration)
        {
            _tic = true;
            _tempo = 0;
        }
    }
} __attribute__((packed));


struct Animate : public ComponentHelper<Animate>
{
    int _currentFrame;

    int _rangeA;
    int _rangeB;

    int _direction;

    int _countPlayDelay;
    int _playDelay;

    int _countFrameDelay;
    int _frameDelay;

    bool _isPlay;

    Animate()
    {
        _type = componentType("ANIMATE", true);
        _playDelay = 0;
        _currentFrame = 0;
        _rangeA = 0;
        _rangeB = 0;
        _direction = 0;
    }

    void start(int frame, int playDelay = 0, int direction = 1,int rangeA = 0, int rangeB = 0)
    {
        _isPlay = true;
        _playDelay = playDelay;
        _countPlayDelay = 0;
        _countFrameDelay = 0;

        _rangeA = rangeA;
        _rangeB = rangeB;

        _currentFrame = frame;
        _direction = direction;

    }

    void stop()
    {
        _isPlay = false;
    }

    void update()
    {
        //log("--- Begin Animate Update ---\n");
        if (_isPlay)
        {
            if (_countPlayDelay > _playDelay)
            {
                _currentFrame += _direction;
                _countPlayDelay = 0;

                // A to B
                if (_direction > 0 && _currentFrame > _rangeB)
                {
                    _currentFrame = _rangeA;
                }

                // B to A
                if (_direction < 0 && _currentFrame < _rangeA)
                {
                    _currentFrame = _rangeB;
                }


            }

            if (_countFrameDelay > _frameDelay)
            {
                ++_countPlayDelay;
                _countFrameDelay = 0;
            }

            ++_countFrameDelay;

        }
    }


} __attribute__((packed));

struct Lambda : public ComponentHelper<Lambda>
{
    Lambda()
    {
        _type = componentType("LAMBDA", true);
    }
} __attribute__((packed));


struct Entity : public IPlayable, public std::enable_shared_from_this<Entity>
{

    std::shared_ptr<Entity> _parent = nullptr;

    std::map<int, Component*> _mapMember;

    std::function<void(std::shared_ptr<Entity>)> _update = nullptr;
    std::function<void(std::shared_ptr<Entity>)> _render = nullptr;

    std::string name() const
    {
        return _name;
    }

    void setUpdate(std::function<void(std::shared_ptr<Entity>)> update)
    {
        _update = update;
    }

    void setRender(std::function<void(std::shared_ptr<Entity>)> render)
    {
        _render = render;
    }


    static std::shared_ptr<Entity> cloneOf(std::shared_ptr<Entity> original, std::string name = "")
    {


        std::shared_ptr<Entity> clone = std::make_shared<Entity>(*original);

        if (name == "")
            clone->_name = original->_name;
        else
            clone->_name = name;

        //log ("--- Begin deep copy ---\n");
        std::map<int,Component*>::const_iterator it = original->_mapMember.begin();

        while (it != original->_mapMember.end())
        {
            //clone->_mapMember[it->first] = new Component(*(it->second));
            clone->_mapMember[it->first] = (*(it->second)).clone();
            ++it;
        }


        return clone;
    }

    Entity(std::shared_ptr<Entity> parent = nullptr, std::string name = "", int id = 0):
        IPlayable(name)
    {
        _id = id;
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

            ++it;
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
        //return static_cast<COMPONENT*>(_mapMember[component._type]);
        return static_cast<COMPONENT*>(_mapMember[component._type]);
        //return new COMPONENT();
    }

    void update()
    {
        if (_update != nullptr)
            _update(shared_from_this());
        else
            log("- " + _name + " update() not defined !\n");
    }

    void render()
    {


        if (_render != nullptr)
            _render(shared_from_this());
        else
            log("- " + _name + " render() not defined !\n");

    }
};

#endif // ENTITY_H
