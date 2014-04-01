SoundCity
=========

Générateur de playlists intelligentes.

Installation
------------

Dans le dossier racine:

    mkdir build
    cd build
    cmake ..
    make

On peut changer le compilateur a utiliser en utilisant la variable `CMAKE_CXX_COMPILER`.
Par exemple pour utiliser clang :

    cmake -DCMAKE_CXX_COMPILER=clang++ ..

Pour compiler une version debug il faut utiliser la variable `CMAKE_BUILD_TYPE`.

    cmake -DCMAKE_BUILD_TYPE=Debug ..

Tests
-----

Pour lancer la suite de test il faut se placer dans le sous dossier test/ du
dossier dans lequel à été lancé CMake (après avoir compilé).
Ensuite il suffit d'utiliser la commande `ctest` en ligne de commande.
