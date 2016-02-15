#include "maptype.h"

MapType::MapType(const std::string& type)
{
    m_type = type;
}

void MapType::addMap(MMap *map)
{
    m_list_maps.push_back(map);
}

int MapType::size() const
{
    int size = 0;
    for (MMap* map : m_list_maps)
        size += map->size();
    return size;
}

int MapType::largest() const
{
    int size = 0;
    for (MMap* map : m_list_maps)
        if (map->size() > size)
            size = map->size();
    return size;
}
