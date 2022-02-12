# R-TYPE [EPITECH PROJECT] [DOCUMENTATION]

<a href="https://img.shields.io/badge/MADE%20WITH-SFML-brightgreen" alt="SFML">
        <img src="https://img.shields.io/badge/MADE%20WITH-SFML-brightgreen" /></a>
<a href="https://img.shields.io/badge/MADE%20WITH-C%2B%2B-ff69b4" alt="C++">
        <img src="https://img.shields.io/badge/MADE%20WITH-C%2B%2B-ff69b4" /></a>
<a href="https://img.shields.io/badge/MADE%20WITH-CONAN-blueviolet" alt="Conan">
        <img src="https://img.shields.io/badge/MADE%20WITH-CONAN-blueviolet" /></a>
<a href="https://img.shields.io/badge/MADE%20WITH-CMAKE-red" alt="Cmake">
        <img src="https://img.shields.io/badge/MADE%20WITH-CMAKE-red" /></a>
	
![ScreenMenu](https://github.com/CamilleSA/R-type-Epitech/blob/master/Assets/Menu_r_type.png)

> For this Advanced C ++ Knowledge Unit project, R-Type will present the development of network video games. Implementation of a multi-threaded server and a graphical client, using a reusable game engine of our own design. The game should also be fun to play! The purpose of this project is to create a one-to-four player game, using a client/server architecture. This is important. It MUST be a client/server architecture. Peer-to-peer communication is not allowed.

## Installation

**Linux:**

```sh
conan install . --build=missing && cmake . -G "Unix Makefiles" && cmake --build .
```

**Windows:**

```sh
Launch with visual studio
cmake
```

## Usage Example

**Products to be delivered**
`r-type_server` `r-type_client`

**In Terminal**

```sh
./r-type_server [PORT]
```

**In another terminal**

```sh
./r-type_client
```

## Constraints

* **Crosse-platform (CMake Linux & CMake Windows)**
* **Build:**
CMake [cf.CMake](https://github.com/EpitechIT2020/B-CPP-500-PAR-5-1-babel-lal.joncoux-aydin/wiki/CMake-page)
* **Dependencies:**
Conan [cf.Conan](https://github.com/EpitechIT2020/B-CPP-500-PAR-5-1-babel-lal.joncoux-aydin/wiki/Conan-page)
* **Protocol:**
[cf.Protocol](https://docs.google.com/document/d/1WeyYqK_QE0NCwvK-uL8AysZ3JGsEQNvESVlmBz_kMpU/edit)
* **Library:**
SFML Library [cf.SFML](https://github.com/SFML/SFML)

## Controller

**Player**

 Button        | Direction
 --------------|-------------
 Arrow Up      | Top
 Arrow Down    | Down
 Arrow Left    | Left
 Arrow Right   | Right
 Space         | Shoot

## Norme Commit

_Git is a fast, scalable, distributed revision control system with an unusually rich command set that provides both high-level operations and full access to internals._

In order to keep things organized, here is the commit style we should try to respect. Doing so will not only clarify the changes we made with each commit, but also increase our capacity to summarize those changes.
	- Commits have to be in english.
	- Each commit should start with a square bracket enclosed key to declare the reason of the commit. Those keys can be found among those :
  ### [ADD] -- if you add files, features, and so on
  ### [FIX] -- if you were working on a bug or any form of default that you corrected 
  ### [DEL] -- if you removed files, features, assets, and so on
  ### [UP] -- if you change something without adding any features or content

  
Each commit should then be followed by a single line (around 50 characters) explaining basics of the changes. For instance, you can have messages such as "[ADD] Collision system".

## UML
[cf.UML](https://lucid.app/lucidchart/0f8d573e-bad0-4fbb-9fe9-4b4b560e6606/edit?shared=true&page=0_0#?folder_id=home&browser=icon)

**Game Engine**\
<a href="https://ibb.co/khTqR6X"><img src="https://i.ibb.co/zSgPyHZ/RTYPE-Game-Engine.png" alt="RTYPE-Game-Engine" border="0"></a>

**Client**\
<a href="https://ibb.co/9vpkgM1"><img src="https://i.ibb.co/RSgkb5s/RTYPE-Client.png" alt="RTYPE-Client" border="0"></a>

**Server**\
<a href="https://ibb.co/ykrQxJV"><img src="https://i.ibb.co/KsJr8Hm/RTYPE-Server.png" alt="RTYPE-Server" border="0"></a>

## Auteurs

* **Lal Joncoux-Aydin** _alias_ [@LalJoncoux-Aydin](https://github.com/LalJoncoux-Aydin)
* **Zoé Lenglemetz** _alias_ [@zoleng](https://github.com/zoleng)
* **Camille Sayous** _alias_ [@CamilleSA](https://github.com/CamilleSA)

