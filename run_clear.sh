#!/bin/bash

# delete previous build
rm -Rf build/
rm -f r-type_client
rm -f r-type_server

# feedback message
echo -ne "\n[CMD] rm build/*"
echo -ne "\n[CMD] rm r-type_client/"
echo -ne "\n[CMD] rm r-type_server/\n"
echo -ne "\n[INFO] Successfully cleared the repository.\n\n"
