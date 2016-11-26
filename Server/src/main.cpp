//
// Created by hippolyteb on 11/20/16.
//

#include <ExternalClassFactoryLoader.hpp>
#include <IEntity.hpp>
#include <Timer.hpp>

int main()
{
    Timer *tmer = new Timer(std::chrono::system_clock::now());
    ManagedExternalInstance<IEntity> monster(ExternalClassFactoryLoader::GetInstanceOf<IEntity>("../SharedLibs/Entities/Monsters/DummyMonster/libDummyMonster.so", { tmer }));

    std::cin.get();
    std::cout << tmer->getCurrent().getMilliseconds().count() << std::endl;
    return (0);
}