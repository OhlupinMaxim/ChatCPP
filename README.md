# Чат на С++

#### Program Stack:
- C++ 14
- Poco C++ Libraries
- ArduinoJson

#### HOWTO:

##### Использование чата:
- Нажать кнопку начать чат (вы попадаете в комнату)
- В комнате внизу есть ссылка, передайте ее вашему собеседнику
- Можете начинать общаться!

##### Сборка и запуск:
####CMake и Conan:
- mkdir build && cd build/ && conan install .. && cmake ../
- cmake --build . --target all
- cd ./Executable/bin
- ./Executable local
####Docker:
docker build . -t omdmaxim/cpp-chat
docker run -d -p 8080:8080  omdmaxim/cpp-chat
    


