#!/bin/bash


if [ "$1" = "-m" ]
then
	make re
	make re -C r-type-client
fi
if [ "$1" = "-c" ]
then
	make fclean
	make fclean -C r-type-client
	exit
fi
gnome-terminal -e ./socket --geometry=100x30+0+0
cd r-type-client

gnome-terminal -e ./application --geometry=100x30+0+1000
gnome-terminal -e ./application --geometry=100x30+1000+1000
