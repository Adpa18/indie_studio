//
// Created by gaspar_q on 6/2/16.
//

#include <queue>
#include <algorithm>
#include <ostream>
#include <BomberMap.hpp>
#include "DangerMap.hpp"

DangerMap::DangerMap(size_t mapSize) :
    mapSize(mapSize)
{
    dangers = new State*[mapSize];
    for (size_t i = 0; i < mapSize; ++i)
    {
        dangers[i] = new State[mapSize];
        memset(dangers[i], 0, mapSize);
    }
}

DangerMap::DangerMap(DangerMap const &ref) :
    DangerMap(ref.mapSize)
{
    *this = ref;
}

DangerMap::~DangerMap()
{
    for (size_t i = 0; i < mapSize; ++i)
    {
        delete [] dangers[i];
    }
    delete[] dangers;
}

DangerMap &DangerMap::operator=(DangerMap const &ref)
{
    for (size_t i = 0; i < mapSize; ++i)
    {
        memcpy(dangers[i], ref.dangers[i], mapSize);
    }
    return *this;
}

void      DangerMap::addDeflagration(ABomb *bomb, irr::core::vector2df const &pos)
{
    irr::core::vector2df    newpos;
    std::vector<irr::core::vector2df>    dir = {
            {1, 0},
            {-1, 0},
            {0, 1},
            {0, -1}
    };

    for (int i = 1, max = bomb->getPower(); i <= max; ++i)
    {
        for (std::vector<irr::core::vector2df>::iterator it = dir.begin(); it != dir.end(); )
        {
            newpos = pos + *it * i;
            int x = static_cast<int>(newpos.X);
            int y = static_cast<int>(newpos.Y);

            if (!isPosValid(x, y))
            {
                ++it;
                continue;
            }

            if (dangers[y][x] != DangerMap::BLOCKED)
            {
                dangers[y][x] = DangerMap::DANGEROUS;
                ++it;
            }
            else
            {
                it = dir.erase(it);
            }
        }
    }
}

void DangerMap::resolveDangerAt(int x, int y, BomberMap *map, std::map<irr::core::vector2df, ABomb *> &mapBombs)
{
    std::vector<AGameObject *>  tocheck;

    tocheck = map->getObjsFromVector2(irr::core::vector2df(x, y));
    dangers[y][x] = DangerMap::SAFE;
    for (std::vector<AGameObject *>::iterator it = tocheck.begin(), end = tocheck.end(); it != end; ++it)
    {
        if ((*it)->getType() == AGameObject::BOMB)
            mapBombs[irr::core::vector2df(x, y)] = dynamic_cast<ABomb *>(*it);
        switch ((*it)->getType())
        {
            case AGameObject::BLOCK:
                dangers[y][x] = DangerMap::BLOCKED;
                break;
            case AGameObject::BOMB:
                dangers[y][x] = DangerMap::BLOCKED;
                break;
            case AGameObject::BOOM:
                dangers[y][x] = DangerMap::BLOCKED;
                break;
            case AGameObject::OTHER:
                dangers[y][x] = DangerMap::BLOCKED;
                break;
            case AGameObject::BONUS:
                dangers[y][x] = DangerMap::BONUSED;
                break;
            case AGameObject::ITEM:
                dangers[y][x] = DangerMap::BONUSED;
                break;
            default:
                break;
        }
    }
}

void DangerMap::refresh(BomberMap *map)
{
    std::map<irr::core::vector2df, ABomb *> mapBombs;

    for (size_t i = 0, max = mapSize * mapSize; i < max; ++i)
    {
        resolveDangerAt(static_cast<int>(i % mapSize), static_cast<int>(i / mapSize), map, mapBombs);
    }
    for (std::map<irr::core::vector2df, ABomb *>::iterator it = mapBombs.begin(), end = mapBombs.end(); it != end; ++it)
    {
        addDeflagration(it->second, it->first);
    }
}

size_t DangerMap::getSize(void) const
{
    return mapSize;
}

std::ostream    &operator<<(std::ostream &output, DangerMap const &ref)
{
    for (int y = 0, size = static_cast<int>(ref.getSize()); y < size; ++y)
    {
        output << "{";
        for (int x = 0; x < size; ++x)
        {
            output << ref.getDangerAt(x, y);
            if (x + 1 < size)
                output << ", ";
        }
        output << "}";
        if (y + 1 < size)
            output << ",";
        output << std::endl;
    }
    return output;
}

DangerMap::State DangerMap::getDangerAt(int x, int y) const
{
    if (!isPosValid(x, y))
        return ERROR;
    return dangers[y][x];
}

DangerMap::State DangerMap::getDangerAt(irr::core::vector2df const &pos) const
{
    return getDangerAt(static_cast<int>(pos.X), static_cast<int>(pos.Y));
}

DangerMap::State &DangerMap::at(int x, int y) throw(std::out_of_range)
{
    if (!isPosValid(x, y))
        throw std::out_of_range("Position (" + std::to_string(x) + ", " + std::to_string(y) + ") is out of range in a map of " + std::to_string(mapSize) + " length");
    return dangers[y][x];
}

DangerMap::State &DangerMap::at(irr::core::vector2df const &pos)
{
    return at(static_cast<int>(pos.X), static_cast<int>(pos.Y));
}

bool DangerMap::isPosValid(int x, int y) const
{
    if (x < 0 || x >= static_cast<int>(mapSize) || y < 0 || y >= static_cast<int>(mapSize))
        return false;
    return true;
}

bool DangerMap::isPosValid(irr::core::vector2df const &pos) const
{
    return isPosValid(static_cast<int>(pos.X), static_cast<int>(pos.Y));
}

irr::core::vector2df DangerMap::getFirstFallBackPosition(irr::core::vector2df const &from)
{
    std::queue<irr::core::vector2df>    file;
    std::vector<irr::core::vector2df>   alreadySaw;
    irr::core::vector2df                tocheck;
    irr::core::vector2df                dir[4] = {
            {1, 0},
            {-1, 0},
            {0, 1},
            {0, -1}
    };
    irr::core::vector2df                lastFallBack(-1, -1);

    file.push(from);
    while (!file.empty())
    {
        for (int i = 0; i < 4; ++i)
        {
            tocheck = file.front() + dir[i];
            if (!isPosValid(tocheck) || std::find(alreadySaw.begin(), alreadySaw.end(), tocheck) != alreadySaw.end())
                continue;
            alreadySaw.push_back(tocheck);
            switch (getDangerAt(tocheck))
            {
                case DangerMap::SAFE:
                    lastFallBack = tocheck;
                case DangerMap::DANGEROUS:
                    file.push(tocheck);
                    break;
                default:
                    break;
            }
        }
        file.pop();
    }
    return lastFallBack;
}