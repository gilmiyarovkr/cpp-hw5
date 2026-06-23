#include <iostream>
#include <memory>
#include <optional>
#include <functional>
#include <unordered_map>

class Line;
class Circle;

class IPrimitiveVisitor
{
public:
    virtual ~IPrimitiveVisitor() = default;
    virtual void Visit(const Line& line) = 0;
    virtual void Visit(const Circle& circle) = 0;
};

class IPrimitive
{
private:
    uint32_t m_id;
    static inline uint32_t m_next_id = 1;

public:
    IPrimitive() : m_id(m_next_id++){}
    virtual ~IPrimitive() = default;
    uint32_t GetID() const
    {
        return m_id;
    }
    virtual void Draw() const = 0;
    virtual void Accept(IPrimitiveVisitor& visitor) const = 0;
};

struct Point
{
    double x, y;
};

class Line : public IPrimitive
{
public:
    Point start{0.0, 0.0}, end{0.0, 0.0};

    void Draw() const override
    {
        std::cout << "Draw Line!";
    }

    void Accept(IPrimitiveVisitor& visitor) const override
    {
        visitor.Visit(*this);
    }
};

class Circle : public IPrimitive
{
public:
    Point center{0.0, 0.0};
    double radius{0.0};

    void Draw() const override
    {
        std::cout << "Draw Circle!";
    }

    void Accept(IPrimitiveVisitor& visitor) const override
    {
        visitor.Visit(*this);
    }
};

//----------------------------------------------------------------------------------------
class SceneModel
{
private:
    std::vector<std::shared_ptr<IPrimitive>> primitives;

public:
    template<typename T, typename... Args>
    void AddPrimitive(Args&&... args)
    {
        primitives.push_back(std::make_shared<T>(std::forward<Args>(args)...));
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

//----------------------------------------------------------------------------------------
template <typename DataType>
class IDocIO
{
public:
    virtual ~IDocIO() = default;
    virtual std::optional<DataType> Load(const std::string& file) = 0; // Загрузить
    virtual bool Save(const std::string& file, const DataType& data) = 0; // Сохранить
};

class JsonSerializer : public IPrimitiveVisitor {
public:
    void Visit(const Line& line) override { std::cout << "  JSON Line: " << line.GetID() << "\n"; }
    void Visit(const Circle& circle) override { std::cout << "  JSON Circle: " << circle.GetID() << "\n"; }
};

class JsonDoc : public IDocIO<SceneModel>
{
public:
    std::optional<SceneModel> Load(const std::string& /*file*/) override
    {
        SceneModel scene;
        //TODO Загрука и заполнение сцены
        return scene;
    }

    bool Save(const std::string& /*file*/, const SceneModel& /*data*/) override
    {
        // TODO Сохранение сцены в файл
        return true;
    }
};

//----------------------------------------------------------------------------------------
class ViewModel
{
public:
    void Render(const SceneModel& scene)
    {
        const auto& prs = scene.GetPrimitives();
        for(const auto& pr : prs)
        {
            pr->Draw();
        }
    }
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

    std::string GetExtension(const std::string& /*fileName*/) const
    {
        // TODO Выделение из имени файла расширения;
        return ".json";
    }

public:
    void RegisterFormat(const std::string& ext, StrategyFactory factory)
    {
        m_io_factories[ext] = std::move(factory);
    }

    void HandleLoadFile(const std::string& fileName)
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

    void HandleSaveFile(const std::string& fileName)
    {
        auto it = m_io_factories.find(GetExtension(fileName));
        if(it != m_io_factories.end())
        {
            std::unique_ptr<IDocIO<SceneModel>> doc = it->second();
            doc->Save(fileName, m_scene);
        }
    }

    const SceneModel& GetScene() const
    {
        return m_scene;
    }

    template<typename T>
    void CreatePrimitive()
    {
        m_scene.AddPrimitive<T>();
        m_view.Render(m_scene);
    }

    void DeletePrimitive(uint32_t id)
    {
        m_scene.RemovePrimitive(id);
        m_view.Render(m_scene);
    }
};


//---------------------------------------------------------------------------
Controller ctrl;

//---------------------------------------------------------------------------
// GUI
//---------------------------------------------------------------------------
void GUI_CreateDocument(const std::string& file) { ctrl.HandleSaveFile(file); }
void GUI_ExportDocument(const std::string& file) { ctrl.HandleSaveFile(file); }
void GUI_ImportDocument(const std::string& file){ ctrl.HandleLoadFile(file); }

//---------------------------------------------------------------------------
void GUI_AddLineElement(){ ctrl.CreatePrimitive<Line>(); }
void GUI_AddCircleElement(){ ctrl.CreatePrimitive<Circle>(); }
void GUI_DeleteElement(uint32_t ID){ ctrl.DeletePrimitive(ID); }

//---------------------------------------------------------------------------
int main()
{
    ctrl.RegisterFormat(".json", [](){return std::make_unique<JsonDoc>();});
    // TODO ctrl.RegisterFormat(".csv", [](){return std::make_unique<CsvDoc>();});

    // FIXME имитация работы GUI
    int enter = 0;
    while(true)
    {
        std::cout << "Draw: \n"
                  << "1 - Line \n"
                  << "2 - Circle \n"
                  << "0 - Exit \n";

        std::cin >> enter;

        if(enter == 0)
            break;

        switch(enter)
        {
            case 1: GUI_AddLineElement();
                break;
            case 2: GUI_AddCircleElement();
                break;
            default:
                break;
        }
    }
    return 0;
}

