#ifndef GAME_SETUP_H
#define GAME_SETUP_H

#include<iostream>
#include<map>
#include<string>
#include<vector> 

using namespace std;

typedef unsigned long long  U64;

#define WHITE 0 // define value for white player
#define BLACK 1 // define value for black player

// define board alpha-numeric vaules per tile 
enum boardRepresentation {
    a1, b1, c1, d1, e1, f1, g1, h1,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a8, b8, c8, d8, e8, f8, g8, h8 
};

// define game pieces and their values
enum gamePieceType {
    nil = 0,
    pawn = 1,
    knight = 2,
    bishop = 3,
    rook = 4,
    queen = 5,
    king = 6,
};

enum gamePieceValue {
    whitePawn = pawn,
    whiteKinght = knight,
    whiteBishop = bishop,
    whiteRook = rook,
    whiteQueen = queen,
    whiteKing = king,

    convertor = 8, // color code to divide black and white pieces

    blackPawn = pawn + convertor,
    blackKinght = knight + convertor,
    blackBishop = bishop + convertor,
    blackRook = rook + convertor,
    blackQueen = queen + convertor,
    blackKing = king + convertor,
};


#endif