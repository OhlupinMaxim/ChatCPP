FROM gcc:9

WORKDIR /app

COPY ../ .

RUN apt update && apt upgrade -y && apt install python3-pip cmake -y

RUN pip3 install conan

WORKDIR /app/build

RUN conan profile new default --detect \

    && conan profile update settings.compiler.libcxx=libstdc++11 default \

    && conan install .. \

    && cmake .. \

    && cmake --build .

WORKDIR /app/build/Executable/bin

EXPOSE 8080

CMD ["./Executable","docker"]