
Подтянет зависимости(fmt)
Легковесная команда
```sh
conan install . --build=missing --settings=build_type=Debug
```

Подтянет зависимости и соберет наш проект
Эта еще и запускает билд нашего проекта
```sh
conan build . --build=missing --settings=build_type=Debug
```
