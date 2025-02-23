#pragma once

namespace KeyBindings {
    constexpr int UP_ARROW                                                                                = 72;
    constexpr int DOWN_ARROW                                                                              = 80;
    constexpr int LEFT_ARROW                                                                              = 75;
    constexpr int RIGHT_ARROW                                                                             = 77;
    constexpr int ESC_KEY                                                                                 = 27;
    constexpr int ENTER_KEY                                                                               = 13;
    constexpr int SPACE_KEY                                                                               = 32;
    constexpr int Q_KEY                                                                                   = 81;
    constexpr int q_KEY                                                                                   = 113;
    constexpr int COL_KEY                                                                                 = 58;
    constexpr int J_KEY                                                                                   = 74;
    constexpr int j_KEY                                                                                   = 106;
    constexpr int K_KEY                                                                                   = 107;
    constexpr int H_KEY                                                                                   = 76;
    constexpr int h_KEY                                                                                   = 104;
    constexpr int L_KEY                                                                                   = 108;
    constexpr int A_KEY                                                                                   = 64;
    constexpr int a_KEY                                                                                   = 97;
    constexpr int w_KEY                                                                                   = 119;
    constexpr int W_KEY                                                                                   = 87;
    constexpr int S_KEY                                                                                   = 82;
    constexpr int s_KEY                                                                                   = 115;
    constexpr int d_KEY                                                                                   = 100;
    constexpr int D_KEY                                                                                   = 68;
}

#ifndef AUDIO_PATHS_H
#define AUDIO_PATHS_H

namespace Audio {
  constexpr const char* BGM                                                                               = "./audio/background.wav";
} 

#endif

namespace GameConstants {

    const std::string __game_title__                                                 = R"(

                           DDDDDD       EEEEEEEEE     FFFFFFFFF     EEEEEEEEE     NN       N       DDDDDD       EEEEEEEEE     RRRRRRRRRRR     !!         SSSSSSSS
                          D      D      E             F             E             N N      N      D      D      E             R          R     !!       SS       
                          D       D     E             F             E             N  N     N      D       D     E             R           R     !!      SS 
                          D       D     E             F             E             N   N    N      D       D     E             R          R       !!       SS
                          D       D     EEEEEE        FFFFFF        EEEEEE        N    N   N      D       D     EEEEEE        RRRRRRRRRRRR                  SS
                          D       D     E             F             E             N     N  N      D       D     E             R        R                       SS
                          D       D     E             F             E             N      N N      D       D     E             R         R                       SS
                          D      D      E             F             E             N       NN      D      D      E             R          R                     SS 
                           DDDDDD       EEEEEEEEE     F             EEEEEEEEE     N        N       DDDDDD       EEEEEEEEE     R           R             SSSSSSSS


                                           DDDDDD            OOOOOO          MM             MM          AAAA            |#|     NN       N     
                                          D      D         OO      OO        M M           M M         AA  AA           |#|     N N      N
                                          D       D       OO        OO       M  M         M  M        AA    AA          |#|     N  N     N
                                          D       D      OO          OO      M   M       M   M       AA      AA         |#|     N   N    N
                                          D       D     OO            OO     M    M     M    M      AA        AA        |#|     N    N   N
                                          D       D      OO          OO      M     M   M     M     AAAAAAAAAAAAAA       |#|     N     N  N 
                                          D       D       OO        OO       M      M M      M    AA            AA      |#|     N      N N
                                          D      D         OO      00        M       M       M   AA              AA     |#|     N       NN
                                           DDDDDD            OOOOOO          M               M  AA                AA    |#|     N        N

    )";

    const std::string __game_lose__                                                  = R"(
              
                          GGGGGGGG                AAAA             MM             MM     EEEEEEEEE                OOOOOO         VV                VV      EEEEEEEEE          RRRRRRRRRRR  
                        G         G              AA  AA            M M           M M     E                      OO      OO        VV              VV       E                  R          R 
                        G                       AA    AA           M  M         M  M     E                     OO        OO        VV            VV        E                  R           R
                        G                      AA      AA          M   M       M   M     E                    OO          OO        VV          VV         E                  R          R  
                        G    GGGGGG           AA        AA         M    M     M    M     EEEEEE              OO            OO        VV        VV          EEEEEE             RRRRRRRRRRRR   
                        G         G          AAAAAAAAAAAAAA        M     M   M     M     E                    OO          OO          VV      VV           E                  R        R    
                        G         G         AA            AA       M      M M      M     E                     OO        OO            VV    VV            E                  R         R  
                        G         G        AA              AA      M       M       M     E                      OO      00              VV  VV             E                  R          R 
                          GGGGGGGGG       AA                AA     M               M     EEEEEEEEE                OOOOOO                 VVVV              EEEEEEEEE          R           R




    )";

    constexpr const float INITIAL_SPAWN_INTERVAL                                                          = 1.2f;
    constexpr const float MIN_SPAWN_INTERVAL                                                              = 0.2f;
    constexpr const float SPAWN_INTERVAL_DECAY_RATE                                                       = 0.2f;
    constexpr const float TIME_TO_DECREASE_SPAWN_INTERVAL                                                 = 30.0f;

    constexpr const int MAX_ENEMIES                                                                       = 90;
    constexpr const char* EMPTY                                                                           = "     ";
    constexpr const char BORDER_CORNER                                                                    = '+';
    constexpr const char BORDER_WALL_Y                                                                    = '|';
    constexpr const char* BORDER_WALL_X                                                                   = "-----";
    constexpr const char* DOOR                                                                            = "[(.)]";

    const float MIN_BOMB_TIMER[]                                                                          = { 3, 4, 7, 5, 4.5, 1, 7.5 };
    const int UPGRADE_TIME[]                                                                              = { 5, 7, 7, 6, 6, 7, 9 };
    const int MAX_BOMB_LEVEL[7]                                                                           = { 6, 6, 6, 6, 6, 10, 6 };
    const int MAX_BOMB_RANGE[7]                                                                           = { 5, 6, 4, 3, 5, 7, 3 };

    constexpr const char* RESET                                                                           = "\033[37m";

    constexpr const char* ICE_BOMBS[] = {
        "\033[38;5;81m  *  \033[37m",
        "\033[38;5;81m  *> \033[37m",
        "\033[38;5;81m <*> \033[37m",
        "\033[38;5;81m <*>>\033[37m",
        "\033[38;5;81m<<*>>\033[37m"
    };

    constexpr const char* WIND_BOMBS[] = {
        "\033[38;5;159m  *  \033[37m",
        "\033[38;5;159m  *> \033[37m",
        "\033[38;5;159m <*> \033[37m",
        "\033[38;5;159m <*>>\033[37m",
        "\033[38;5;159m<<*>>\033[37m"
    };

    constexpr const char* SHADOW_BOMBS[] = {
        "\033[38;5;23m  *  \033[37m",
        "\033[38;5;23m  *> \033[37m",
        "\033[38;5;23m <*> \033[37m",
        "\033[38;5;23m <*>>\033[37m",
        "\033[38;5;23m<<*>>\033[37m"
    };

    constexpr const char* ELECTRO_BOMBS[] = {
        "\033[38;5;214m  *  \033[37m",
        "\033[38;5;214m  *> \033[37m",
        "\033[38;5;214m <*> \033[37m",
        "\033[38;5;214m <*>>\033[37m",
        "\033[38;5;214m<<*>>\033[37m"
    };

    constexpr const char* FIRE_BOMBS[] = {
        "\033[38;5;196m  *  \033[37m",
        "\033[38;5;196m  *> \033[37m",
        "\033[38;5;196m <*> \033[37m",
        "\033[38;5;196m <*>>\033[37m",
        "\033[38;5;196m<<*>>\033[37m"
    };

    constexpr const char* POISON_BOMBS[] = {
        "\033[38;5;93m  *  \033[37m",
        "\033[38;5;93m  *> \033[37m",
        "\033[38;5;93m <*> \033[37m",
        "\033[38;5;93m <*>>\033[37m",
        "\033[38;5;93m<<*>>\033[37m"
    };

    constexpr const char* WATER_BOMBS[] = {
        "\033[38;5;39m  *  \033[37m",
        "\033[38;5;39m  *> \033[37m",
        "\033[38;5;39m <*> \033[37m",
        "\033[38;5;39m <*>>\033[37m",
        "\033[38;5;39m<<*>>\033[37m"
    };
} 
