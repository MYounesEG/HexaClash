@echo off
IF EXIST Y.cpp (
    rename gameInterface.cpp M.cpp
	rename Y.cpp gameInterface.cpp
) ELSE (
    rename gameInterface.cpp Y.cpp
	rename M.cpp gameInterface.cpp
)

