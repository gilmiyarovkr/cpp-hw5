#include "include/JsonDoc.h"
#include "include/Primitive.h"
#include <iostream>

class JsonSerializer : public IPrimitiveVisitor
{
public:
    void Visit(const Line& line) override { std::cout << "  JSON Line: " << line.GetID() << "\n"; }
    void Visit(const Circle& circle) override { std::cout << "  JSON Circle: " << circle.GetID() << "\n"; }
};

std::optional<SceneModel> JsonDoc::Load(const std::string& /*file*/)
{
    SceneModel scene;
    //TODO Загрука и заполнение сцены
    return scene;
}

bool JsonDoc::Save(const std::string& /*file*/, const SceneModel& /*data*/)
{
    // TODO Сохранение сцены в файл
    return true;
}
