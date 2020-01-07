# CMake



### Pré-requis:

1. Installer **`conan`**.

```
pip install conan
```

Sinon: [**conan.io/installation**](https://docs.conan.io/en/latest/installation.html)

2. Ajouter les repos de **`bincrafters`** et **`epitech`**.

```
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
conan remote add epitech https://api.bintray.com/conan/epitech/public-conan
```

3. Configurer **`conan`** avec  **`GCC >= 5.1`** pour que ça compile la **`SFML`** en **`C++ 11`**.

```
conan profile new default --detect
conan profile update settings.compiler.libcxx=libstdc++11 default
```



### Build:

* **`Linux`**

Un script bash nommé **`run.sh`** est présent.

```
$ cat run.sh

--- run.sh ---
#!/bin/bash

# delete previous build
rm -Rf build/

# build new binary
mkdir build
cd build
conan install .. --build=missing
cmake .. -G "Unix Makefiles"
cmake --build .
--- end ---
```



* **`Windows`**