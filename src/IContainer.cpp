#include "IContainer.h"

//template <class OBJECT>
//IContainer<OBJECT>::IContainer()
//{
//    //ctor
//}
//
//template <class OBJECT>
//IContainer<OBJECT>::~IContainer()
//{
//    if (!_vecObject.empty())
//    {
//        for (auto & it: _vecObject)
//        {
//            if (it != nullptr)
//            {
//                delete it;
//                it = nullptr;
//            }
//        }
//        _vecObject.clear();
//    }
//    //dtor
//}
//
//template <class OBJECT>
//void IContainer<OBJECT>::add(OBJECT* object)
//{
//    _vecObject.push_back(object);
//}
//
//template <class OBJECT>
//void IContainer<OBJECT>::del(int id)
//{
//
//}
//
//template <class OBJECT>
//void IContainer<OBJECT>::del(const char* name)
//{
//
//}
//
//template <class OBJECT>
//OBJECT* IContainer<OBJECT>::at(int id)
//{
//    for (auto & it: _vecObject)
//    {
//        if (it->id() == id)
//            return it;
//    }
//}
//
//template <class OBJECT>
//OBJECT* IContainer<OBJECT>::at(const char* name)
//{
//    for (auto & it: _vecObject)
//    {
//        if (it->name() == name)
//            return it;
//    }
//}
