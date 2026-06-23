#pragma once

#include <string>
#include <optional>

template <typename DataType>
class IDocIO
{
public:
    virtual ~IDocIO() = default;
    virtual std::optional<DataType> Load(const std::string& file) = 0; // Загрузить
    virtual bool Save(const std::string& file, const DataType& data) = 0; // Сохранить
};
