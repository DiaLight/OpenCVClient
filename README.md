# OpenCVClient
Written in C++ application based on OpenCV library. Main purpose of application is sending handled by OpenCV images from raspberry to another machine.

## Requires
    opencv 3.1
    cmake >= 3.0

## How to build
    pi@raspberrypi:~ $ git clone https://github.com/DiaLight/OpenCVClient.git
    pi@raspberrypi:~ $ cd OpenCVClient/
    pi@raspberrypi:~/OpenCVClient $ mkdir build && cd build
    pi@raspberrypi:~/OpenCVClient/build $ cmake ..
    pi@raspberrypi:~/OpenCVClient/build $ make

## Usage
    pi@raspberrypi:~/OpenCVClient/build $ ./OpenCVClient <host:port>
    
Client closes when receiving the interrupt signal SIGINT(Ctrl+C) or SIGTERM(stop signal from IDE).

## Setup your IDE

There is two IDE's I am working in.

CLion is very convenient development environment and have good design, but it compiles and runs code local machine only.

NetBeans can compile and run code on remote machine through ssh connection.

### CLion
* Select `Import Project from Sources` or open `file/Import Project...`
* `Open Project`
* Select `OpenCVClient` Run/Build Configuration and run

### NetBeans
* `Создать проект`
* `Проект С/С++ с существующими исходными файлами`
* Указываем папку с проектом
* Указываем режим настройки `выборочно`, затем переходим `далее`
* `Требуется действие предварительной сборки` должна стоять галочка
* `Выполнить в папке: ` дописываем `/build` или `/cmake-build-netbeans` по вкусу (в результате должно выглядеть примерно так `/home/pi/OpenCVClient/cmake-build-netbeans`)
* Выбираем `Предварительно настроенная команда:`
* `тип сценария: ` `CMake (CMakeLists.txt)`, затем переходим `далее`
* Нажимаем `далее` до победы и за тем `Готово`.

