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
