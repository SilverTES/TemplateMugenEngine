//------------------------------------------------------------------------------
//--- MugenEngine
//------------------------------------------------------------------------------
#include <iostream>

template <class M = std::string, class E = int>
E log(M msg, E error)
{
#ifdef SHOW_LOG
    std::cout << msg;
#endif // SHOW_LOG
    return error;
}
