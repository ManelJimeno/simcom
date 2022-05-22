- 🇪🇸 Español
- 🇺🇸 [English](README.es.md)

# Simulador de comunicaciones

## Índice

- [Como compilar](#como-compilar)
  - [Requisitos previos](#requisitos-previos)
      - [Instalación en macOS](#instalacin-en-macos)
      - [Instalación en Linux](#instalacin-en-linux)
      - [Instalación en Windows](#instalacin-en-windows)
  - [Creando binarios](#creando-binarios)
- [Ejecutando binarios](#ejecutando-binarios)
  - [Servidor de hora](#servidor-de-hora)
  - [Cliente multihilos](#servidor-de-hora)
  - [Diseñando un escenario de test](#diseando-un-escenario-de-test)
  - [Ejecutando un escenario de test](#ejecutando-un-escenario-de-test)

# Resumen
Es un proyecto para experimentar conceptos de comunicación y multitarea usando:

- [Poco project](https://github.com/pocoproject/poco)
- [Google test](https://github.com/google/googletest)
- [Swig](https://github.com/swig/swig)

## Como compilar

### Requisitos previos

Este proyecto necesita estas utilidades para funcionar:
    - cmake: versión >= 3.22
    - clang-format: versión >= 10
    - clang-tidy: versión >= 10
    - python (y el modulo pip): versión >= 3.8
    - conan ( ojo, en Linux necesitaras instalar con ``` sudo pip3 conan ```)

#### Instalación en macOS
```shell
sudo brew install cmake llvm python3-pip
```

#### Instalación en Linux
```shell
sudo apt-get install -y cmake clang-format clang-tidy python3-pip
```
#### Instalación en Windows
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
cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Release
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
- connections, número de conexiones que realizaremos contra el servidor
- delay, tiempo de espera en milisegundos en pedir entre tandas de mensajes
- parallel, número de hebras creadas por tanda
```shell
$ client --server localhost --port 30000 --connections 1000 --delay 20 --parallel 30
2022-05-22T21:27:22Z
2022-05-22T21:27:22Z
....
2022-05-22T21:27:22Z
2022-05-22T21:27:22Z
```


#### Diseñando un escenario de test

#### Ejecutando un escenario de test
