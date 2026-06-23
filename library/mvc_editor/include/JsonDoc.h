#pragma once

#include "IDocIO.h"
#include "SceneModel.h"

class JsonDoc : public IDocIO<SceneModel>
{
public:
    std::optional<SceneModel> Load(const std::string& file) override;
    bool Save(const std::string& file, const SceneModel& data) override;
};
