#pragma once

#include "IDocIO.h"
#include "SceneModel.h"

/**
 * @class JsonDoc
 * @brief Класс для сохранения и загрузки графической сцены в формате JSON.
 *
 * Данный класс является конкретной реализацией стратегии ввода-вывода (`IDocIO`)
 * для типа `SceneModel`.
 */
class JsonDoc : public IDocIO<SceneModel>
{
public:
    /**
     * @brief Деструктор по умолчанию.
     */
    virtual ~JsonDoc() override = default;

    /**
     * @brief Загружает и восстанавливает модель сцены из JSON-файла.
     *
     * Считывает файл, парсит его структуру и воссоздает объекты `Line`, `Circle`
     * и другие примитивы, наполняя ими новую модель сцены.
     *
     * @param file Путь к импортируемому файлу JSON.
     * @return std::optional<SceneModel> Заполненная модель сцены в случае успеха,
     *                                 или std::nullopt при ошибке чтения/валидации файла.
     */
    std::optional<SceneModel> Load(const std::string& file) override;

    /**
     * @brief Сериализует и сохраняет текущую модель сцены в файл JSON.
     *
     * Метод обходит все примитивы сцены, вызывая для каждого метод `Accept(*this)`,
     * что позволяет преобразовать их специфичные данные в JSON-формат.
     *
     * @param file Путь к файлу для сохранения данных.
     * @param data Константная ссылка на сохраняемую модель сцены.
     * @return true Если сцена успешно сериализована и записана на диск.
     * @return false Если в процессе записи или конвертации произошла ошибка.
     */
    bool Save(const std::string& file, const SceneModel& data) override;
};
