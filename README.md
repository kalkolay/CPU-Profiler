# CPU Profiler

[![Build](https://github.com/kalkolay/CPU-Profiler/actions/workflows/macos-cmake-build.yml/badge.svg)](https://github.com/kalkolay/CPU-Profiler/actions/workflows/macos-cmake-build.yml)

## Команда проекта

[M34122] **Витязев Арсений Павлович** – _тестировщик_\
[M34031] **Иофинов Платон Артемович** – _разработчик (системная часть)_\
[M34122] **Кукулиди Дмитрий Анатольевич** – _Project Manager_\
[M34122] **Федотенко Николай Владимирович** – _разработчик (графическая часть)_\
[M34122] **Шевченко Арсений Владимирович** – _DevOps-инженер_

## Описание

Десктопное приложение (утилита) на macOS, отображающее производительность центрального процессора (CPU) на графиках.\
В приложении -- график общей нагрузки, а также графики распределения нагрузки по ядрам. В зависимости от степени нагрузки цвет графика функции будет меняться по градиенту от зеленого до красного.\
Вдохновлялись монитором ресурсов на Windows.

## Функциональные требования

- Отображение общего графика нагрузки и ее распределения по ядрам;
- Использование разных цветов в зависимости от степени нагрузки (например
диапазон пиковой загрузки - красный);
- Обновление с частотой не менее чем раз в секунду.

## Нефункциональные требования

- Проект реализован на языке C++17;
- Использование графического API OpenGL (v. 3.0+);
- Отрисовка каждого ядра в отдельном потоке;
- Данные о нагрузке берутся из Mach API (ядро macOS);
- Шейдеры написаны на GLSL (версия 330 core).
___
## Deliverables

### MVP [_текущая версия_]
1. Отображение общего графика нагрузки;
2. Использование разных цветов в зависимости от степени нагрузки.

## Лицензия

_Данный проект находится под лицензией [**MIT**](https://github.com/kalkolay/CPU-Profiler/blob/main/LICENSE)._
