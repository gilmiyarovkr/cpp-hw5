#pragma once

#include <vector>
#include <memory>
#include "IPrimitive.h"

//----------------------------------------------------------------------------------------
class SceneModel
{
private:
    std::vector<std::shared_ptr<IPrimitive>> primitives;

public:
    void AddPrimitive(std::shared_ptr<IPrimitive> primitive)
    {
        if (primitive)
        {
            primitives.push_back(std::move(primitive));
        }
    }

    bool RemovePrimitive(uint32_t /*id*/)
    {
        // TODO Удалить элемент по id
        return true;
    }

    const std::vector<std::shared_ptr<IPrimitive>>& GetPrimitives() const
    {
        return primitives;
    }
};
