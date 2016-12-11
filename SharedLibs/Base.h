//
// Created by hippolyteb on 11/22/16.
//

#ifndef R_TYPE_BASE_H
#define R_TYPE_BASE_H

#include <initializer_list>

#if MSVC
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

#define RTYPE_ENTITY_REGISTER(Entity)                                                   \
extern "C" DLLEXPORT Entity *create(const std::initializer_list<void *> init) {         \
    return new Entity(init);                                                            \
}                                                                                       \
                                                                                        \
extern "C" DLLEXPORT void destroy(Entity *p) {                                          \
    delete p;                                                                           \
}


#define RTYPE_DRAWABLE_ENTITY_REGISTER(DrawableEntity)                                          \
extern "C" DLLEXPORT DrawableEntity *createDrawable(const std::initializer_list<void *> init) { \
    return new DrawableEntity(init);                                                            \
}                                                                                               \
                                                                                                \
extern "C" DLLEXPORT void destroyDrawable(DrawableEntity *p) {                                  \
    delete p;                                                                                   \
}

template<typename T>
T GetParamFromInitializerList(const std::initializer_list<void *> &init, unsigned int index) {
    unsigned int i = 0;
    for (auto const param : init){
        if (i == index)
            return static_cast<T>(param);
        i++;
    }

    return nullptr;
}

#endif //R_TYPE_BASE_H
