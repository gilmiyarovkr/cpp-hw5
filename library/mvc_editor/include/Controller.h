#pragma once

#include <string>
#include <memory>
#include <functional>
#include <unordered_map>

#include "SceneModel.h"
#include "IDocIO.h"

//----------------------------------------------------------------------------------------
class ViewModel
{
public:
    void Render(const SceneModel& scene);
};

//----------------------------------------------------------------------------------------
class Controller
{
public:
    using StrategyFactory = std::function<std::unique_ptr<IDocIO<SceneModel>>()>;

private:
    SceneModel m_scene;
    ViewModel m_view;
    std::unordered_map<std::string, StrategyFactory> m_io_factories;

    std::string GetExtension(const std::string& fileName) const;

public:
    Controller() = default;
    ~Controller() = default;

    void RegisterFormat(const std::string& ext, StrategyFactory factory);
    void HandleLoadFile(const std::string& fileName);
    void HandleSaveFile(const std::string& fileName);
    void DeletePrimitive(uint32_t id);

    const SceneModel& GetScene() const
    {
        return m_scene;
    }

    void CreatePrimitive(std::shared_ptr<IPrimitive> primitive);
};
