# Конфигурацию проекта
cmake -B build

# Перенос готовый файл из папки сборки
cp build/Doxyfile .

# Генерация документации
doxygen Doxyfile
