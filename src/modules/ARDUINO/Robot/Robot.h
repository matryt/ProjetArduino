//
// Created by mathi on 07/02/2024.
//

#ifndef PROJET_SYSTEME_H
#define PROJET_SYSTEME_H


class Robot {
    void init();

    void config_speed(int speed);

    void speed_up(int speed, int target_speed, int increment);

    void slow_down(int speed, int target_speed, int increment);

    void config_spinning(char direction);

    void start();

    void stop();

    void halfturn();

    void straight_line();

    void journey();

    void process_next_angle();

    int main();
};


#endif //PROJET_SYSTEME_H
