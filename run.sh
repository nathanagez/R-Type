#!/bin/bash

# delete previous build
rm -Rf build/
rm -f r-type_client
rm -f r-type_server

# build new binary
mkdir build
cd build
conan install .. --build=missing
cmake .. -G "Unix Makefiles"
cmake --build .
cd ..

# check & copy for binary
if [ -f "build/client/bin/r-type_client" ]
then
  cp build/client/bin/r-type_client .
  echo -ne "\n[INFO] Successfully built the \"r-type_client\"."
else
  echo -ne "\n[ERROR] An error occured, the \"r-type_client\" couldn't be created!"
fi
if [ -f "build/server/bin/r-type_server" ]
then
  cp build/server/bin/r-type_server .
  echo -ne "\n[INFO] Successfully built the \"r-type_server\".\n\n"
else
  echo -ne "\n[ERROR] An error occured, the \"r-type_server\" couldn't be created!\n\n"
fi
