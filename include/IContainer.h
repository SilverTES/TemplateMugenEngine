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
            if (!_vecChild.empty())
            {
                for (auto & it: _vecChild)
                {
                    if (it != nullptr)
                    {
                        delete it;
                        it = nullptr;
                    }
                }
                _vecChild.clear();
            }
        }

        void add(OBJECT * object)
        {
            if (object != nullptr)
            {
                _vecChild.push_back(object);
            }
        }
        void del(int id)
        {

        }
        void del(const char *name)
        {

        }

        int vecSize()
        {
            return _vecChild.size();
        }

        OBJECT *index(int index)
        {
            return _vecChild[index];
        }

        OBJECT *at(int id)
        {
            for (auto & it: _vecChild)
            {
                if (it->id() == id)
                    return it;
            }
            return log("OBJECT not found !",nullptr);
        }
        OBJECT *at(const char *name)
        {
            for (auto & it: _vecChild)
            {
                if (it->name() == name)
                    return it;
            }
            return log("OBJECT not found !",nullptr);
        }

    protected:
        OBJECT *_parent = nullptr;
        std::vector<OBJECT*> _vecChild;

    private:
};

#endif // ICONTAINER_H
