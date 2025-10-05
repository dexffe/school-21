// I WANT TO PLAY WITH YOU
//         YOUR FRIEND, AI

#include <stdio.h>

int main(void) {
    int ball_x = 40, ball_y = 12, speed_ball_x = 1, speed_ball_y = 1;
    int player_1 = 11, player_2 = 11;
    int point_player_1 = 0, point_player_2 = 0;
    char c;

    // drow field
    while (point_player_1 < 21 && point_player_2 < 21) {
        printf("\033[H\033[J");
        for (int y = 0; y < 25; y++) {
            for (int x = 0; x < 80; x++) {
                char ch = ' ';
                if (x == 0 || x == 79)
                    ch = (y == 0 || y == 24) ? '+' : '|';
                else if (y == 0 || y == 24)
                    ch = '-';
                if (x == ball_x && y == ball_y) ch = 'O';
                if (x == 1 && y >= player_1 && y < player_1 + 3) ch = '#';
                if (x == 78 && y >= player_2 && y < player_2 + 3) ch = '#';
                putchar(ch);
            }
            putchar('\n');
        }
        printf("P1: %d  P2: %d\n", point_player_1, point_player_2);
        printf("\nPress 'a'/'z' to move paddle 1\n");
        printf("Press 'k'/'m' to move paddle 2\n");

        // input step
        c = getchar();

        if ((c != '\n') && (c == 'a' || c == 'z' || c == 'k' || c == 'm' || c == ' ')) {
            // check input
            if (c == 'a' && player_1 > 1) player_1--;
            if (c == 'z' && player_1 < 21) player_1++;
            if (c == 'k' && player_2 > 1) player_2--;
            if (c == 'm' && player_2 < 21) player_2++;

            // change coords ball
            ball_x += speed_ball_x;
            ball_y += speed_ball_y;

            // TODO: Реализовать момент отскока по верхнему и нижнему краю поля
            //  code
            if (ball_y == 1) speed_ball_y *= -1;
            if (ball_y == 23) speed_ball_y *= -1;

            // TODO: Реализовать момент отскока от ракеток(то чем управляют игроки)
            //  code
            if ((ball_x == 2) && (ball_y >= player_1) && (ball_y <= player_1 + 2)) speed_ball_x *= -1;
            if ((ball_x == 77) && (ball_y >= player_2) && (ball_y <= player_2 + 2)) speed_ball_x *= -1;

            // TODO: Реализовать момент забитого мяча(после гола направить мяч в другую сторону)
            //  code
            if (ball_x == 1) {
                ball_x = 40;
                ball_y = 12;
                point_player_2++;
                speed_ball_x *= -1;
                speed_ball_y *= -1;
            }
            if (ball_x == 78) {
                ball_x = 40;
                ball_y = 12;
                point_player_1++;
                speed_ball_x *= -1;
                speed_ball_y *= -1;
            }
        }
    }

    if (point_player_1 == 21)
        printf("Player 1 wins!\n");
    else
        printf("Player 2 wins!\n");

    return 0;
}
