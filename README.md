# Sound Processor

## Описание
Программа `sound_processor` предназначена для обработки аудиофайлов в формате WAV, применяя к ним различные преобразования согласно конфигурационному файлу. 

## Запуск программы
```sh
sound_processor [-h] - help
sound_processor -c <config.txt> <output.wav> <input1.wav> [<input2.wav> ...]
```

### Аргументы командной строки
- `-h` – вывод справки об использовании программы.
- `-c <config.txt>` – путь к файлу конфигурации.
- `<output.wav>` – выходной WAV-файл.
- `<input1.wav> [<input2.wav> ...]` – входные WAV-файлы.

## Поддерживаемый формат WAV
- Аудио-формат: PCM (без кодирования).
- Каналы: моно (1 канал).
- Разрядность: 16 бит (signed 16-bit little-endian).
- Частота дискретизации: 44100 Гц.

## Поддерживаемые конвертеры

### 1. Заглушение интервала (`mute`)
**Синтаксис:**
```config.txt
mute <start_time> <end_time>
```
- `start_time` – начало интервала (в секундах).
- `end_time` – конец интервала (в секундах).
- В указанном интервале звуковые данные заменяются тишиной.

### 2. Миксер (`mix`)
**Синтаксис:**
```config.txt
mix $n <insert_time>
```
- `$n` – ссылка на дополнительный поток (например, `$2` означает второй входной файл).
- `insert_time` - время вставки (в секундах).
- Объединяет два аудиопотока, усредняя их значения.

### 3. Эхо (`echo`)
```config.txt
echo <start_time> <end_time>
```
- `<start_time>` - начало интервала (в секундах)
- `<end_time>` - конец интервала (в секундах)
- delay = 44100 (int)
- decay = 0.5 (float)
- Добавляет эхо в аудиопоток.

## Формат конфигурационного файла
Конфигурационный файл определяет последовательность применения конвертеров (пример):
```sh
# заглушить первые 30 секунд input1
mute 0 30

# смиксовать с input2, начиная с 10-й секунды
mix $2 10

# заглушить 3-ю минуту в миксованном потоке
mute 120 180

# добавить эхо в период с 60 секунды по 75 в миксованном потоке
echo 60 75
```
- Строки, начинающиеся с `#`, являются комментариями.
- Конвертеры применяются последовательно.

## Технические аспекты
- Работа с WAV и конвертеры - независимые компоненты.
- Используется шаблон проектирования «Фабричный метод» для создания конвертеров.
- Разбор конфигурационного файла выполняется отдельным классом.
- В случае ошибки программа выводит сообщение в `std::cerr` и завершается с соответствующим кодом ошибки.

## Ошибки и обработка исключений
Программа должна корректно обрабатывать следующие ошибки (но maybe ошибки всё ещё будут :/):
- Некорректные аргументы командной строки.
- Неподдерживаемый формат входного WAV-файла.
- Ошибки в файле конфигурации.
- Отсутствие входных файлов.

