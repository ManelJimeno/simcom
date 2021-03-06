- 馃嚜馃嚫 Espa帽ol
- 馃嚭馃嚫 [English](README.es.md)

# Simulador de comunicaciones

## 脥ndice

- [Simulador de comunicaciones](#simulador-de-comunicaciones)
  - [脥ndice](#铆ndice)
- [Resumen](#resumen)
  - [Como compilar](#como-compilar)
    - [Requisitos previos](#requisitos-previos)
      - [Instalaci贸n en macOS](#instalaci贸n-en-macos)
      - [Instalaci贸n en Linux](#instalaci贸n-en-linux)
      - [Instalaci贸n en Windows](#instalaci贸n-en-windows)
    - [Creando binarios](#creando-binarios)
    - [Ejecutando binarios](#ejecutando-binarios)
      - [Servidor de hora](#servidor-de-hora)
      - [Cliente multihilos](#cliente-multihilos)
      - [Dise帽ando un escenario de test](#dise帽ando-un-escenario-de-test)
      - [Ejecutando un escenario de test](#ejecutando-un-escenario-de-test)

# Resumen
Es un proyecto para experimentar conceptos de comunicaci贸n y multitarea usando:

- [Poco project](https://github.com/pocoproject/poco)
- [Google test](https://github.com/google/googletest)
- [Swig](https://github.com/swig/swig)

## Como compilar

### Requisitos previos

Este proyecto necesita estas utilidades para funcionar:
    - cmake: versi贸n >= 3.22
    - clang-format: versi贸n >= 10
    - clang-tidy: versi贸n >= 10
    - python (y el modulo pip): versi贸n >= 3.8
    - conan ( ojo, en Linux necesitaras instalar con ``` sudo pip3 conan ```)

#### Instalaci贸n en macOS
```shell
sudo brew install cmake llvm python3-pip
```

#### Instalaci贸n en Linux
```shell
sudo apt-get install -y cmake clang-format clang-tidy python3-pip
```
#### Instalaci贸n en Windows
Usando [winget](https://github.com/microsoft/winget-cli/releases)
```powershell
winget install cmake llvm python
```
Usando [chocolatey](https://chocolatey.org/install)
```powershell
choco install cmake llvm python
```
### Creando binarios
El proyecto usa cmake, puedes crear los binarios desde la linea de comandos o utilizar un IDE,
Visual Studio Code o CLion son opciones funcionales.

El proyecto include los siguientes targets:
    - server, El servidor de comunicaciones y sus dependencias
    - client, El cliente de comunicaciones y sus dependencias
    - simcon, La libreria comun del proyecto

```shell
cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Release
```

### Ejecutando binarios

#### Servidor de hora
Ejecutando el servidor en el puerto 30000

```shell
cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 17 2022"
cmake --build build --target server
build/bin/server -p 30000
```

Podemos comprobar que atiende peticiones desde otro shell usando telnet
```shell
$ telnet localhost 30000
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
2022-05-22T20:40:40Z
Connection closed by foreign host.
```

#### Cliente multihilos
El cliente puede recibir los siguientes parametos:
- server
- port
- connections, n煤mero de conexiones que realizaremos contra el servidor
- delay, tiempo de espera en milisegundos en pedir entre tandas de mensajes
- parallel, n煤mero de hebras creadas por tanda
```shell
$ client --server localhost --port 30000 --connections 1000 --delay 20 --parallel 30
2022-05-22T21:27:22Z
2022-05-22T21:27:22Z
....
2022-05-22T21:27:22Z
2022-05-22T21:27:22Z
```


#### Dise帽ando un escenario de test

#### Ejecutando un escenario de test
