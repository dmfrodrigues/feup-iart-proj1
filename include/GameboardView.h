#pragma once

#include "GameboardModel.h"
#include "TerminalGUI.h"

class GameboardView {
private:
    const GameboardModel &_gameboardModel;
public:
    GameboardView(const GameboardModel &gameboardModel);
    void display(TerminalGUI &terminal);
private:
    TerminalGUI::coord_t TUBE_MARGIN_X = 3;
    TerminalGUI::coord_t PIECE_MARGIN_Y = 1;
    TerminalGUI::coord_t PIECE_X = 4;
    TerminalGUI::coord_t PIECE_Y = 3;
    TerminalGUI::coord_t TUBE_PADDING_X = 2;
    TerminalGUI::coord_t TUBE_PADDING_Y = 1;
    void displayTube (TerminalGUI &terminal, size_t tube);
    void displayPiece(TerminalGUI &terminal, size_t tube, size_t place, color_t piece_color);
};
