#include "include/Controller.h"

void ViewModel::Render(const SceneModel& scene)
{
    const auto& prs = scene.GetPrimitives();
    for(const auto& pr : prs)
    {
        pr->Draw();
    }
}

//----------------------------------------------------------------------------------------
std::string Controller::GetExtension(const std::string& /*fileName*/) const
{
    // TODO Выделение из имени файла расширения;
    return ".json";
}

void Controller::RegisterFormat(const std::string& ext, StrategyFactory factory)
{
    m_io_factories[ext] = std::move(factory);
}

void Controller::HandleLoadFile(const std::string& fileName)
{
    auto it = m_io_factories.find(GetExtension(fileName));
    if(it != m_io_factories.end())
    {
        std::unique_ptr<IDocIO<SceneModel>> doc = it->second();

        auto res = doc->Load(fileName);
        if(res.has_value())
        {
            m_scene = std::move(res.value());
        }
    }
}

void Controller::HandleSaveFile(const std::string& fileName)
{
    auto it = m_io_factories.find(GetExtension(fileName));
    if(it != m_io_factories.end())
    {
        std::unique_ptr<IDocIO<SceneModel>> doc = it->second();
        doc->Save(fileName, m_scene);
    }
}

void Controller::CreatePrimitive(std::shared_ptr<IPrimitive> primitive)
{
    m_scene.AddPrimitive(std::move(primitive));
    m_view.Render(m_scene);
}

void Controller::DeletePrimitive(uint32_t id)
{
    m_scene.RemovePrimitive(id);
    m_view.Render(m_scene);
}
