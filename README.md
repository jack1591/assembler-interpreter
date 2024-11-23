# Репозиторий с 4 заданием по конфигурационному управлению
Перед загрузкой репозитория необходимо установить **cmake** https://cmake.org/download/
## Загрузка репозитория на компьютер
1. Откройте терминал
2. Перейдите в папку, где вы хотите разместить проект
3. Выполните команду:
```
git clone https://github.com/jack1591/assembler-interpreter.git
```
## Запуск программы
1. Перейти в папку build из папки third в терминале
```
cd assembler-interpreter/build
```  
2. При первом запуске программы ввести следующие команды:
```
cmake -G "MinGW Makefiles" ..
cmake ..
mingw32-make
```  

## Задание  
Разработать ассемблер и интерпретатор для учебной виртуальной машины
(УВМ). Система команд УВМ представлена далее.  
Для ассемблера необходимо разработать читаемое представление команд
УВМ. Ассемблер принимает на вход файл с текстом исходной программы, путь к
которой задается из командной строки. Результатом работы ассемблера является
бинарный файл в виде последовательности байт, путь к которому задается из
командной строки. Дополнительный ключ командной строки задает путь к файлу-логу, в котором хранятся ассемблированные инструкции в духе списков
“ключ=значение”, как в приведенных далее тестах.  
Интерпретатор принимает на вход бинарный файл, выполняет команды УВМ
и сохраняет в файле-результате значения из диапазона памяти УВМ. Диапазон
также указывается из командной строки.  
Форматом для файла-лога и файла-результата является **xml**.  
Необходимо реализовать приведенные тесты для всех команд, а также
написать и отладить тестовую программу.  

### Загрузка константы
| A | B | C |
|----------|----------|----------|
| Биты 0-3    | Биты 4-22  | Биты 23-25  |
|   0  | Константа   | Адрес   |

Размер команды: 4 байт. Операнд: поле B. Результат: регистр по адресу,
которым является поле C.  
Тест (A=0, B=218, C=7):  
0xA0, 0x0D, 0x80, 0x03

### Чтение значения из памяти
| A | B | C |
|----------|----------|----------|
| Биты 0-3    | Биты 4-6  | Биты 7-21  |
|  15  | Адрес   | Адрес   |

Размер команды: 4 байт. Операнд: значение в памяти по адресу, которым
является поле C. Результат: регистр по адресу, которым является поле B.  
Тест (A=15, B=6, C=196):
0x6F, 0x62, 0x00, 0x00

### Запись значения в память
| A | B | C |
|----------|----------|----------|
| Биты 0-3    | Биты 4-18  | Биты 19-21  |
|  7  | Адрес   | Адрес   |

Размер команды: 4 байт. Операнд: регистр по адресу, которым является поле
C. Результат: значение в памяти по адресу, которым является поле B.  
Тест (A=7, B=557, C=0):
0xD7, 0x22, 0x00, 0x00

### Унарная операция: bitreverse
| A | B | C |
|----------|----------|----------|
| Биты 0-3    | Биты 4-6  | Биты 7-9  |
|  12  | Адрес   | Адрес   |

Размер команды: 4 байт. Операнд: значение в памяти по адресу, которым
является регистр по адресу, которым является поле C. Результат: регистр по
адресу, которым является поле B.  
Тест (A=12, B=7, C=5):
0xFC, 0x02, 0x00, 0x00

### Тестовая программа
Выполнить поэлементно операцию bitreverse() над вектором длины 8.  
Результат записать в исходный вектор  

## Функции программы  
### main
Чтение путей до файлов и диапазон регистров УВМ, запуск ассемблера и интерпретатора  

### read_input
Чтение исходного файла с командами, вызов функции построения лог-файла и бинарного файла

### log_in
Создание лог-файла

### transformate
Преобразование строки в исходном файле в двоичное представление  

### error_detected
Вывод названия ошибки 

### interpreter
Чтение и преобразование бинарного файла, выполнение команд

### bin_to_dec
Преобразование числа из двоичного формата в десятичный

### bitreverse
Разворот двоичного представления числа

### out_result
Вывод результата в выходной файл

### string_reverse
Разворот строки  

## Запуск .exe файлов
Запуск .exe файла программы:
```
./main.exe ./ ./ ./ 0-3
```

Запуск .exe файла с тестами:
```
./tests.exe
```

## Тестирование
Список тестов:
1. **Преобразование файла input1.txt**
2. **Преобразование файла input2.txt**
3. **Преобразование файла input3.txt**
4. **Преобразование файла input4.txt**
5. **Преобразование файла input5.txt**
6. **Преобразование файла input6.txt - неизвестная команда**
7. **Преобразование файла input7.txt - неправильный идентификатор команды**
8. **Преобразование файла input8.txt - пустой регистр**
9. **Преобразование файла input9.txt - пустое значение в памяти**

Содержимое файла test_main.cpp:
```
#include <gtest/gtest.h>
#include "interpreter.cpp"

TEST(SampleTest, Test_1) {
    l=0;
    r=2;
    read_input("./","./","./","input1.txt");
    EXPECT_EQ(interpreter(), "<result>\n<register address=0>8</register>\n<register address=1>5</register>\n<register address=2>15</register>\n<result>\n");
}

TEST(SampleTest, Test_2) {
    l=1;
    r=3;
    read_input("./","./","./","input2.txt");
    EXPECT_EQ(interpreter(), "<result>\n<register address=1>5</register>\n<register address=2>15</register>\n<register address=3>15</register>\n<result>\n");
}

TEST(SampleTest, Test_3) {
    l=0;
    r=2;
    read_input("./","./","./","input3.txt");
    EXPECT_EQ(interpreter(), "<result>\n<register address=0>8</register>\n<register address=1>5</register>\n<register address=2>6</register>\n<result>\n");
}

TEST(SampleTest, Test_4) {
    l=0;
    r=6;
    read_input("./","./","./","input4.txt");
    EXPECT_EQ(interpreter(), "<result>\n<register address=0>54</register>\n<register address=1>5</register>\n<register address=2>6</register>\n<register address=3>15</register>\n<register address=4>-1</register>\n<register address=5>-1</register>\n<register address=6>3</register>\n<result>\n");
}

TEST(SampleTest, Test_5) {
    l=0;
    r=7;
    read_input("./","./","./","input5.txt");
    EXPECT_EQ(interpreter(), "<result>\n<register address=0>0</register>\n<register address=1>4</register>\n<register address=2>2</register>\n<register address=3>6</register>\n<register address=4>1</register>\n<register address=5>5</register>\n<register address=6>3</register>\n<register address=7>7</register>\n<result>\n");
}

TEST(SampleTest, Test_6) {
    l=0;
    r=7;
    string error = read_input("./","./","./","input6.txt");
    EXPECT_EQ(error, "The undefined name of command!\n");
}

TEST(SampleTest, Test_7) {
    l=0;
    r=7;
    read_input("./","./","./","input7.txt");
    EXPECT_EQ(interpreter(), "The unknown index of command!\n");
}

TEST(SampleTest, Test_8) {
    l=0;
    r=7;
    read_input("./","./","./","input8.txt");
    EXPECT_EQ(interpreter(), "register is empty!\n");
}

TEST(SampleTest, Test_9) {
    l=0;
    r=7;
    read_input("./","./","./","input9.txt");
    EXPECT_EQ(interpreter(), "memory is empty!\n");
}
```

Результаты тестирования
![photo_2024-11-23_20-12-47](https://github.com/user-attachments/assets/51f7ec98-4400-4646-aad0-827853752ed3)

### Тестовая программа
Выполнить поэлементно операцию bitreverse() над вектором длины 8.  
Результат записать в исходный вектор.  

Содержимое входного файла  
![input](https://github.com/user-attachments/assets/bd03eb7f-3dc1-4c8c-a578-c5a6f3caa4e8)  


