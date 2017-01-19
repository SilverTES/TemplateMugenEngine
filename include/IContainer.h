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
                    object->setId(freeChildIndex);

                }
                else
                {
                    unsigned id = _vecObject.size();
                    object->setId(id);
                    _vecObject.push_back(object);
                }
                //_vecObject.push_back(object);

            }
        }
        void del(unsigned id)
        {
            //std::cout << "BEFORE object deleted = " << _vecObject[id] << "\n";
            if (!_vecObject.empty())
                if (id >= 0 && id < _vecObject.size() && _vecObject[id] != nullptr)
                {
                    //log ("- " + _vecObject[id]->_name + " deleted !\n");
                    delete _vecObject[id];
                    _vecObject[id] = nullptr;

                    _vecFreeObject.push_back(id);
                }
            //std::cout << "AFTER object deleted = " << _vecObject[id] << "\n";
        }

        void del(const char *name)
        {
            if (!_vecObject.empty())
                for (auto & it: _vecObject)
                {
                    if (it != nullptr)
                        if (it->name() == name)
                            del(it->id());
                }
        }

        void delAll()
        {
            if (!_vecObject.empty())
                for (auto & it: _vecObject)
                {
                    if (it != nullptr)
                        del(it->id());
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
            return _vecObject.front()->id();
        }

        int lastId() const
        {
            return _vecObject.back()->id();
        }

        int getId(int id) const
        {
            if (id >= 0 && id < _vecObject.size() && _vecObject[id] != nullptr)
                return _vecObject[id]->id();
            else
                return nullptr;
        }


        int vecSize() const
        {
            return _vecObject.size();
        }

        int vecSizeFree() const
        {
            return _vecFreeObject.size();
        }

        int numActiveObject() const
        {
            return vecSize() - vecSizeFree();
        }

        bool isFree(int id) const
        {
            if (_vecObject[id] != nullptr)
                return false;
            else
                return true;

        }

        OBJECT *index(int index) const
        {
            return _vecObject[index];
        }

        int indexByName(std::string name) const
        {
            if (!_vecObject.empty())
                for (unsigned i = 0; i<_vecObject.size(); i++)
                {
                    if (_vecObject[i] != nullptr)
                        if (_vecObject[i]->name() == name)
                            return i;
                }
            return 0;
        }

        int idByName(std::string name) const
        {
            if (!_vecObject.empty())
                for (auto & it: _vecObject)
                {
                    if (it != nullptr)
                        if (it->_name == name)
                            return it->id();
                }

            return -1;
        }
        // Get unique Object : return first Object*

        OBJECT *at(int id) const
        {
            if (!_vecObject.empty())
                for (auto & it: _vecObject)
                {
                    if (it != nullptr)
                        if (it->_id == id)
                            return it;
                }
            //log("OBJECT not found !");
            return nullptr;
        }
        OBJECT *at(std::string name) const
        {
            if (!_vecObject.empty())
                for (auto & it: _vecObject)
                {
                    if (it != nullptr)
                        if (it->name() == name)
                            return it;
                }

            log("OBJECT not found !");
            return nullptr;
        }

        // Get group Object : return vector of Object*

        std::vector<OBJECT*> groupAt(int id) const
        {
            std::vector<OBJECT*> vecObject;
            if (!_vecObject.empty())
                for (auto & it: _vecObject)
                {
                    if (it != nullptr)
                        if (it->_id == id)
                            vecObject.push_back(it);
                }
            //log("OBJECT not found !");
            return vecObject;
        }
        std::vector<OBJECT*> groupAt(std::string name) const
        {
            std::vector<OBJECT*> vecObject;

            if (!_vecObject.empty())
                for (auto & it: _vecObject)
                {
                    if (it != nullptr)
                        if (it->name() == name)
                            vecObject.push_back(it);
                }
            //log("OBJECT not found !");

            return vecObject;
        }








    protected:
        OBJECT *_parent = nullptr;
        std::vector<OBJECT*> _vecObject;
        std::vector<int> _vecFreeObject;

    private:
};

#endif // ICONTAINER_H
