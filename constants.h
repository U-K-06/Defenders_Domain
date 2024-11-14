#pragma once

namespace KeyBindings {
    constexpr int UP_ARROW              = 72;
    constexpr int DOWN_ARROW            = 80;
    constexpr int LEFT_ARROW            = 75;
    constexpr int RIGHT_ARROW           = 77;
    constexpr int ESC                   = 27;
    constexpr int SPACE                 = 32;
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
    constexpr const int MAX_ENEMIES        = 90;
    constexpr const char* EMPTY            = "     ";
    constexpr const char BORDER_CORNER     = '+';
    constexpr const char BORDER_WALL_Y     = '|';
    constexpr const char* BORDER_WALL_X    = "-----";

    const int UPGRADE_TIMES[7][5] = {
                                      {2000, 3500, 4500, 5000, 7000}, // Electric Tower
                                      {1500, 2500, 3500, 4500, 6500}, // Fire Tower
                                      {2500, 3800, 4250, 6500, 9000}, // Poison Tower
                                      {1400, 2400, 3400, 4400, 5400}, // Water Tower
                                      {1800, 2800, 3800, 5000, 6000}, // Ice Tower
                                      {1600, 3600, 4600, 5500, 7400}, // Wind Tower
                                      {2600, 3800, 5000, 6800, 9500}  // Shadow Tower
                                    };

    constexpr const char* ICE_TOWERS[] = {
        "\033[38;5;81m  *  \033[37m",
        "\033[38;5;81m  *> \033[37m",
        "\033[38;5;81m <*> \033[37m",
        "\033[38;5;81m <*>>\033[37m",
        "\033[38;5;81m<<*>>\033[37m"
    };

    constexpr const char* WIND_TOWERS[] = {
        "\033[38;5;159m  *  \033[37m",
        "\033[38;5;159m  *> \033[37m",
        "\033[38;5;159m <*> \033[37m",
        "\033[38;5;159m <*>>\033[37m",
        "\033[38;5;159m<<*>>\033[37m"
    };

    constexpr const char* SHADOW_TOWERS[] = {
        "\033[38;5;23m  *  \033[37m",
        "\033[38;5;23m  *> \033[37m",
        "\033[38;5;23m <*> \033[37m",
        "\033[38;5;23m <*>>\033[37m",
        "\033[38;5;23m<<*>>\033[37m"
    };

    constexpr const char* ELECTRIC_TOWERS[] = {
        "\033[38;5;214m  *  \033[37m",
        "\033[38;5;214m  *> \033[37m",
        "\033[38;5;214m <*> \033[37m",
        "\033[38;5;214m <*>>\033[37m",
        "\033[38;5;214m<<*>>\033[37m"
    };

    constexpr const char* FIRE_TOWERS[] = {
        "\033[38;5;196m  *  \033[37m",
        "\033[38;5;196m  *> \033[37m",
        "\033[38;5;196m <*> \033[37m",
        "\033[38;5;196m <*>>\033[37m",
        "\033[38;5;196m<<*>>\033[37m"
    };

    constexpr const char* POISON_TOWERS[] = {
        "\033[38;5;93m  *  \033[37m",
        "\033[38;5;93m  *> \033[37m",
        "\033[38;5;93m <*> \033[37m",
        "\033[38;5;93m <*>>\033[37m",
        "\033[38;5;93m<<*>>\033[37m"
    };

    constexpr const char* WATER_TOWERS[] = {
        "\033[38;5;39m  *  \033[37m",
        "\033[38;5;39m  *> \033[37m",
        "\033[38;5;39m <*> \033[37m",
        "\033[38;5;39m <*>>\033[37m",
        "\033[38;5;39m<<*>>\033[37m"
    };
} 
