# Makefile for Student
# Author : Weifei
# Time   : 2016-9-1

all: Chess.o ChessEncoded.o ChessMoveQueue.o AutoSolveHRD.o mainHRD.o
	g++ -o HRD.run "-fno-stack-protector" Chess.o ChessEncoded.o ChessMoveQueue.o AutoSolveHRD.o mainHRD.o 
	rm *.o

Chess.o:Chess.cpp
	g++ -c "-fno-stack-protector" Chess.cpp
ChessEncoded.o:ChessEncoded.cpp
	g++ -c "-fno-stack-protector" ChessEncoded.cpp	
ChessMoveQueue.o:ChessMoveQueue.cpp
	g++ -c "-fno-stack-protector" ChessMoveQueue.cpp
AutoSolveHRD.o:AutoSolveHRD.cpp
	g++ -c "-fno-stack-protector" AutoSolveHRD.cpp	
mainHRD.o:mainHRD.cpp
	g++ -c "-fno-stack-protector" mainHRD.cpp 
clean:
	rm *.o

