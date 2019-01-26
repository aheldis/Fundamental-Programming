#include "structs.h"

void move_tank(Tank *tank) {
    int tempx = tank->x;
    int tempy = tank->y;
    if (state[tank->up] && !state[tank->down]) {
        tank->y += step * sin(tank->angle);
        tank->x += step * cos(tank->angle);
    }
    if (state[tank->down] && !state[tank->up]) {
        tank->y -= step * sin(tank->angle);
        tank->x -= step * cos(tank->angle);
    }
    if (tank->x < radius) {
        tank->x = radius;
        tank->y = tempy;
    }
    if (tank->y < radius) {
        tank->x = tempx;
        tank->y = radius;
    }
    if (tank->x > MAP_WIDTH - radius) {
        tank->x = MAP_WIDTH - radius;
        tank->y = tempy;
    }
    if (tank->y > MAP_HEIGHT - radius) {
        tank->x = tempx;
        tank->y = MAP_HEIGHT - radius;
    }
}

void turn_tank(Tank *tank) {
    if (state[tank->right] && !state[tank->left]) tank->angle += degree;
    if (state[tank->left] && !state[tank->right]) tank->angle -= degree;
}

void move_bullet(Bullet *bullet) {
    if ((bullet->n) < 2 * distanceofBullets && !bullet->boolian) (bullet->n)++;
    if (bullet->boolian && bullet->x != -100) {
        bullet->x += step_bullet * cos(bullet->angle);
        bullet->y += step_bullet * sin(bullet->angle);
        (bullet->n)++;
        if (bullet->n == distanceofBullets) {
            bullet->boolian = false;
        }
    }
}

void fire(Tank *tank) {
    static bool flag[] = {true, true};
    static int i[] = {0, 0};
    for (int k = 0; k < 2; k++) {
        if (((tank + k)->bullets + numberofBullets - 1)->n == 2 * distanceofBullets) {
            i[k] = 0;
            for (int j = 0; j < numberofBullets; j++) {
                ((tank + k)->bullets + j)->boolian = true;
                ((tank + k)->bullets + j)->x = -100;
                ((tank + k)->bullets + j)->y = -100;
            }
            ((tank + k)->bullets + numberofBullets - 1)->n = 0;
            printf("hi\n");
        }

        if (state[(tank + k)->shoot]) {
            if (i[k] < numberofBullets && (tank->bullets + i[k])->boolian && flag[k]) {
                ((tank + k)->bullets + i[k])->x = (tank + k)->x + shooter * cos((tank + k)->angle);
                ((tank + k)->bullets + i[k])->y = (tank + k)->y + shooter * sin((tank + k)->angle);
                ((tank + k)->bullets + i[k])->angle = (tank + k)->angle;
                ((tank + k)->bullets + i[k])->n = 0;
                flag[k] = false;
                i[k]++;
                printf ("%d\n", i[k]);
            }
            static int n[numberofTanks] = {0};
            n[k]++;
            if (n[k] == 10) {
                flag[k] = true;
                n[k] = 0;
            }
        }
    }
}
