#pragma once

namespace KeyBindings {
    constexpr int UP_ARROW              = 72;
    constexpr int DOWN_ARROW            = 80;
    constexpr int LEFT_ARROW            = 75;
    constexpr int RIGHT_ARROW           = 77;
    constexpr int ESC                   = 27;
    constexpr int ENTER                 = 13;
    constexpr int Q_KEY                 = 81;
    constexpr int q_KEY                 = 113;
    constexpr int COL_KEY               = 58;
    constexpr int J_KEY                 = 74;
    constexpr int j_KEY                 = 106;
    constexpr int K_KEY                 = 107;
    constexpr int H_KEY                 = 76;
    constexpr int h_KEY                 = 104;
    constexpr int L_KEY                 = 108;
    constexpr int A_KEY                 = 64;
    constexpr int a_KEY                 = 97;
    constexpr int w_KEY                 = 119;
    constexpr int W_KEY                 = 87;
    constexpr int S_KEY                 = 82;
    constexpr int s_KEY                 = 115;
    constexpr int d_KEY                 = 100;
    constexpr int D_KEY                 = 68;
}


namespace GameConstants {
    constexpr const char* EMPTY           = "     ";
    constexpr char BORDER_CORNER          = '+';
    constexpr char BORDER_WALL_Y          = '|';
    constexpr const char* BORDER_WALL_X   = "-----";
    constexpr const char* ELECTRIC_TOWER  = "\033[38;5;214m Λ  \033[37m";
    constexpr const char* FIRE_TOWER      = "\033[38;5;196m Λ  \033[37m";
    constexpr const char* POISON_TOWER    = "\033[38;5;93m Λ  \033[37m";
    constexpr const char* WATER_TOWER     = "\033[38;5;39m Λ  \033[37m";
    constexpr const char* ICE_TOWER       = "\033[38;5;81m Λ  \033[37m";
    constexpr const char* WIND_TOWER      = "\033[38;5;159m Λ  \033[37m";
    constexpr const char* SHADOW_TOWER    = "\033[38;5;23m Λ  \033[37m";;
}
