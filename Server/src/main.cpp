//
// Created by hippolyteb on 11/20/16.
//

#include <ExternalClassFactoryLoader.hpp>
#include <IEntity.hpp>

int main()
{
    ManagedExternalInstance<IEntity> monster(ExternalClassFactoryLoader::GetInstanceOf<IEntity>("../SharedLibs/Entities/Monsters/DummyMonster/libDummyMonster.so"));

    return (0);
}
