#ifndef MAPTYPE_H
#define MAPTYPE_H

#include "mmap.h"

class MapType
{

public:
    MapType(const std::string& type);

    void addMap(MMap* map);

    // getters
    int size() const;
    int largest() const;
private:
    std::string m_type;
    int m_size;
    int m_committed;
    int m_private;
    int m_largest;
    std::vector<MMap*> m_list_maps;

};

#endif // MAPTYPE_H
