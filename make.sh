#!/bin/sh

modeMake=$1

if [ "$modeMake" = "-r" ];
then
	qmake TaskTravelingSalesman.pro -o build/
	cd build
	make -B -s >&1 | tee log
	exit 0
else
	qmake TaskTravelingSalesman.pro -o build/
	cd build
	make -s >&1 | tee log
	exit 0
fi
	
