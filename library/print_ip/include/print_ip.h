#pragma once

#include <iostream>
#include <string>
#include <tuple>
#include <concepts>

/**
 * @brief Выводит IP-адрес, представленный в виде строки.
 * @param[in] ip Строка, содержащая IP-адрес.
 */
void print_ip(const std::string& ip)
{
    std::cout << ip << std::endl;
}

/**
 * @brief Шаблонная функция для вывода IP-адреса, представленного целочисленным типом.
 * @details Выводит адрес побайтово, начиная со старшего байта к младшему.
 * @tparam T Целочисленный тип (должен удовлетворять концепту std::integral).
 * @param[in] ip Числовое представление IP-адреса.
 */
template <std::integral T>
void print_ip(T ip)
{
    for (int i = sizeof(T) - 1; i >= 0; --i)
    {
        std::cout << ((ip >> (i * 8)) & 0xFF);
        if (i > 0)
            std::cout << ".";
    }
    std::cout << std::endl;
}

/**
 * @brief Концепт для проверки, является ли тип стандартным контейнером.
 * @details Проверяет наличие вложенного типа value_type, а также методов begin() и end().
 * Исключает тип std::string из рассмотрения.
 * @tparam T Проверяемый тип.
 */
template <typename T>
concept IsContainer = requires(T container)
{
    typename T::value_type;
    container.begin();
    container.end();
} && !std::same_as<T, std::string>;

/**
 * @brief Шаблонная функция для вывода IP-адреса, сохраненного в контейнере.
 * @tparam T Тип контейнера, удовлетворяющий концепту IsContainer.
 * @param[in] container Контейнер с элементами IP-адреса.
 */
template <IsContainer T>
void print_ip(const T& container)
{
    bool first = true;
    for (const auto& bytes : container)
    {
        if (!first)
            std::cout << ".";
        std::cout << +bytes;
        first = false;
    }
    std::cout << std::endl;
}

/**
 * @brief Вспомогательная функция для поочередного вывода элементов кортежа.
 * @tparam Tuple Тип кортежа.
 * @tparam Is Последовательность индексов для развертывания кортежа.
 * @param[in] t Ссылка на кортеж.
 */
template <typename Tuple, std::size_t... Is>
void print_tuple_ip(const Tuple& t, std::index_sequence<Is...>)
{
    bool first = true;
    auto print_elem = [&](const auto& x)
    {
        if (!first)
            std::cout << ".";
        std::cout << +x;
        first = false;
    };
    (print_elem(std::get<Is>(t)), ...);
    std::cout << std::endl;
}

/**
 * @brief Вспомогательный концепт для проверки однородности пакета параметров.
 * @tparam T Базовый тип, с которым сравниваются остальные.
 * @tparam Args Пакет типов для сравнения.
 */
template <typename T, typename... Args>
concept AllSameAs = (std::same_as<T, Args> && ...);

/**
 * @brief Концепт для проверки валидности кортежа в качестве IP-адреса.
 * @details Проверяет, что тип является std::tuple и все его элементы имеют абсолютно одинаковый тип.
 * @tparam T Проверяемый тип.
 */
template <typename T>
concept ValidTuple = requires
{
    typename std::tuple_size<T>::type;
} && []<std::size_t... Is>(std::index_sequence<Is...>)
{
    return AllSameAs<typename std::tuple_element<0, T>::type, typename std::tuple_element<Is, T>::type...>;
}(std::make_index_sequence<std::tuple_size_v<T>>{});

/**
 * @brief Шаблонная функция для вывода IP-адреса, представленного в виде кортежа (std::tuple).
 * @details Функция доступна только если кортеж не пустой и содержит строго одинаковые типы элементов.
 * @tparam Args Типы элементов кортежа.
 * @param[in] t Кортеж, содержащий элементы IP-адреса.
 */
template <typename... Args>
    requires ValidTuple<std::tuple<Args...>>
void print_ip(const std::tuple<Args...>& t)
{
    print_tuple_ip(t, std::make_index_sequence<sizeof...(Args)>{});
}
