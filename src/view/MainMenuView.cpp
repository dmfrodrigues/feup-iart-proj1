// Copyright (C) 2021 Diogo Rodrigues, Rafael Ribeiro, Bernardo Ferreira
// Distributed under the terms of the GNU General Public License, version 3

#include "view/MainMenuView.h"
#include "view/gui/TerminalGUISprite.h"


using namespace std;
using coord_t = TerminalGUI::coord_t;
using pos_t   = TerminalGUI::pos_t;
using Color   = TerminalGUI::Color;

const Color DEFAULT = TerminalGUI::DEFAULT;
const Color GRAY    = TerminalGUI::GRAY   ;
const Color WHITE   = TerminalGUI::WHITE  ;
const Color BLUE    = TerminalGUI::BLUE   ;
const Color RED     = TerminalGUI::RED    ;
const Color YELLOW  = TerminalGUI::YELLOW ;

MainMenuView::MainMenuView(const MainMenuModel &mainMenuModel): menuView(mainMenuModel)
{
}

void MainMenuView::draw(TerminalGUI &terminal){
    terminal.setCorner(-terminal.getSize()/2);
    pos_t POS0 = pos_t(-31,-12);

    TerminalGUISprite iconSprite(
        {
            {" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
            {" "," ","╗"," "," ","╔"," ","╗"," "," ","╔"," ","╗"," "," ","╔"," "," "},
            {" "," ","║"," "," ","║"," ","║"," "," ","║"," ","║"," "," ","║"," "," "},
            {" "," ","║","▇","▇","║"," ","║","▇","▇","║"," ","║","▇","▇","║"," "," "},
            {" "," ","║","▇","▇","║"," ","║","▇","▇","║"," ","║","▇","▇","║"," "," "},
            {" "," ","║","▇","▇","║"," ","║","▇","▇","║"," ","║","▇","▇","║"," "," "},
            {" "," ","║","▇","▇","║"," ","║","▇","▇","║"," ","║","▇","▇","║"," "," "},
            {" "," ","╚","═","═","╝"," ","╚","═","═","╝"," ","╚","═","═","╝"," "," "},
            {" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
        },
        {
            {GRAY   ,GRAY   ,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,GRAY   ,GRAY   },
            {DEFAULT,DEFAULT,WHITE  ,DEFAULT,DEFAULT,WHITE  ,DEFAULT,WHITE  ,DEFAULT,DEFAULT,WHITE  ,DEFAULT,WHITE  ,DEFAULT,DEFAULT,WHITE  ,DEFAULT,DEFAULT},
            {DEFAULT,DEFAULT,WHITE  ,DEFAULT,DEFAULT,WHITE  ,DEFAULT,WHITE  ,DEFAULT,DEFAULT,WHITE  ,DEFAULT,WHITE  ,DEFAULT,DEFAULT,WHITE  ,DEFAULT,DEFAULT},
            {DEFAULT,DEFAULT,WHITE  ,RED    ,RED    ,WHITE  ,DEFAULT,WHITE  ,GRAY   ,GRAY   ,WHITE  ,DEFAULT,WHITE  ,GRAY   ,GRAY   ,WHITE  ,DEFAULT,DEFAULT},
            {DEFAULT,DEFAULT,WHITE  ,RED    ,RED    ,WHITE  ,DEFAULT,WHITE  ,BLUE   ,BLUE   ,WHITE  ,DEFAULT,WHITE  ,GRAY   ,GRAY   ,WHITE  ,DEFAULT,DEFAULT},
            {DEFAULT,DEFAULT,WHITE  ,YELLOW ,YELLOW ,WHITE  ,DEFAULT,WHITE  ,BLUE   ,BLUE   ,WHITE  ,DEFAULT,WHITE  ,YELLOW ,YELLOW ,WHITE  ,DEFAULT,DEFAULT},
            {DEFAULT,DEFAULT,WHITE  ,BLUE   ,BLUE   ,WHITE  ,DEFAULT,WHITE  ,RED    ,RED    ,WHITE  ,DEFAULT,WHITE  ,YELLOW ,YELLOW ,WHITE  ,DEFAULT,DEFAULT},
            {DEFAULT,DEFAULT,WHITE  ,WHITE  ,WHITE  ,WHITE  ,DEFAULT,WHITE  ,WHITE  ,WHITE  ,WHITE  ,DEFAULT,WHITE  ,WHITE  ,WHITE  ,WHITE  ,DEFAULT,DEFAULT},
            {GRAY   ,GRAY   ,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,GRAY   ,GRAY   }
        },
        {
            {DEFAULT,DEFAULT,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,DEFAULT,DEFAULT},
            {GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   },
            {GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   },
            {GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   },
            {GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   },
            {GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   },
            {GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   },
            {GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   },
            {DEFAULT,DEFAULT,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,GRAY   ,DEFAULT,DEFAULT}
        }
    );
    iconSprite.setPosition(POS0);
    terminal.draw(iconSprite);

    TerminalGUISprite textSprite(
        {
            {"█","▀","▀","▙"," ","▗","▄","▄","▖"," ","▀","█"," "," ","▀","█"," "," "," "," "," "," ","▟","▀","▀","▀"," ","▗","▄","▄","▖"," ","▄","▗","▄"," ","▄","█","▄","▄"," "},
            {"█","▀","▀","▙"," ","▗","▄","▄","█"," "," ","█"," "," "," ","█"," "," "," "," "," "," ","▝","▀","▀","▙"," ","█"," "," ","█"," ","█","▀"," "," "," ","█"," "," "," "},
            {"█","▄","▄","▛"," ","▜","▄","▄","█"," "," ","▜","▄","▖"," ","▜","▄","▖"," "," "," "," ","▜","▄","▄","▛"," ","▜","▄","▄","▛"," ","█"," "," "," "," ","▜","▄","▄"," "},
            {},
            {"█","▀","▀","▙"," ","▄"," "," ","▄"," ","▄","▄","▄","▄"," ","▄","▄","▄","▄"," ","▀","█"," "," ","▗","▄","▄","▖"," "},
            {"█","▄","▄","▛"," ","█"," "," ","█"," "," ","▄","▟","▘"," "," ","▄","▟","▘"," "," ","█"," "," ","█","▄","▄","▛"," "},
            {"█"," "," "," "," ","▜","▄","▄","▛"," ","▟","▙","▄","▄"," ","▟","▙","▄","▄"," "," ","▜","▄","▖","▜","▄","▄","▖"," "}
        }
    );
    textSprite.setPosition(POS0+pos_t(21, 1));
    terminal.draw(textSprite);

    menuView.setPosition(pos_t(0, POS0.y) + pos_t(0, 10));
    menuView.draw(terminal);
}
