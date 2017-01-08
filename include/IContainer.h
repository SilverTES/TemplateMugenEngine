#ifndef ICONTAINER_H
#define ICONTAINER_H

#include "Mugenengine.h"

template <class OBJECT>
class IContainer
{
    public:
        IContainer()
        {

        }
        virtual ~IContainer()
        {
            if (!_vecObject.empty())
            {
                for (auto & it: _vecObject)
                {
                    if (it != nullptr)
                    {
                        delete it;
                        it = nullptr;
                    }
                }
                _vecObject.clear();
            }

            _vecFreeObject.clear();
        }

        void add(OBJECT * object)
        {
            if (object != nullptr)
            {

                if (!_vecFreeObject.empty())
                {
                    unsigned freeChildIndex = _vecFreeObject.back();
                    _vecFreeObject.pop_back();

                    _vecObject[freeChildIndex] = object;
                    object->_id = freeChildIndex;

                }
                else
                {
                    unsigned id = _vecObject.size();
                    object->_id = id;
                    _vecObject.emplace_back(object);
                }
                //_vecObject.push_back(object);

            }
        }
        void del(unsigned id)
        {
            //std::cout << "BEFORE object deleted = " << _vecObject[id] << "\n";
            if (id >= 0 && id < _vecObject.size() && _vecObject[id] != nullptr)
            {
                log ("- " + _vecObject[id]->_name + " deleted !\n");
                delete _vecObject[id];
                _vecObject[id] = nullptr;

                _vecFreeObject.emplace_back(id);
            }

            //std::cout << "AFTER object deleted = " << _vecObject[id] << "\n";
        }

        void del(const char *name)
        {
            for (auto & it: _vecObject)
            {
                if (it != nullptr)
                    if (it->name() == name)
                        del(it->_id);
            }
        }


        OBJECT *first() const
        {
            return _vecObject.front();
        }

        OBJECT *last() const
        {
            return _vecObject.back();
        }

        int firstId() const
        {
            return _vecObject.front()->_id;
        }

        int lastId() const
        {
            return _vecObject.back()->_id;
        }

        int getId(int id) const
        {
            if (id >= 0 && id < _vecObject.size() && _vecObject[id] != nullptr)
                return _vecObject[id]->_id;
            else
                return nullptr;
        }


        int vecSize() const
        {
            return _vecObject.size();
        }

        OBJECT *index(int index) const
        {
            return _vecObject[index];
        }

        int indexByName(std::string name) const
        {
            for (unsigned i = 0; i<_vecObject.size(); i++)
            {
                if (_vecObject[i]->name() == name)
                    return i;
            }
            return 0;
        }

        OBJECT *at(int id) const
        {
            for (auto & it: _vecObject)
            {
                if (it->id() == id)
                    return it;
            }
            return log("OBJECT not found !",nullptr);
        }
        OBJECT *at(std::string name) const
        {
            for (auto & it: _vecObject)
            {
                if (it->name() == name)
                    return it;
            }
            return log("OBJECT not found !",nullptr);
        }

        int idByName(std::string name) const
        {
            for (auto & it: _vecObject)
            {
                if (it != nullptr)
                    if (it->_name == name)
                        return it->_id;
            }

            return -1;
        }


    protected:
        OBJECT *_parent = nullptr;
        std::vector<OBJECT*> _vecObject;
        std::vector<int> _vecFreeObject;

    private:
};

#endif // ICONTAINER_H
