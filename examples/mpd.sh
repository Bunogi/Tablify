#!/usr/bin/bash
#Select a new song from your mpd playlist. Reqires mpd and mpc.
#To be run inside the examples directory.

changeto=$(mpc --format "%position%\t%artist%\t%title%" playlist | tablify -r 0 Number Artist Title)

if [ ! -z "$changeto" ]
then
	mpc play $changeto
fi
