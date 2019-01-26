#include "structs.h"

int vertex(int x, int y) {
    return (x - house / 2) / house + (y - house / 2) / house * numberofColumns;
}

bool movement_collids_walls(Tank *tank, Map *map) {
    //////the house where tank is in it
    short vert = vertex(tank->x, tank->y);
    short left = vert % numberofColumns + vert / numberofColumns * (numberofColumns + 1);
    short right = left + 1;
    short up = vert + numberofRows * (numberofColumns + 1);
    short down = up + numberofColumns;
    int b[] = {right, down, left, up};
    for (int j = 0; j < 4; j++) {
        int i = b[j];
        if ((map->walls + i)->boolian) {
            int max_x, max_y;
            int sign_x = (cos(tank->angle) > 0 ? 1 : -1);
            int sign_y = (sin(tank->angle) > 0 ? 1 : -1);
            if ((radius_shooter + shooter) * cos(tank->angle) * sign_x > radius_circle)         max_x = (radius_shooter + shooter) * cos(tank->angle);
            else max_x = radius_circle * sign_x;
            if ((radius_shooter + shooter) * sin(tank->angle) * sign_y > radius_circle)         max_y = (radius_shooter + shooter) * sin(tank->angle);
            else max_y = radius_circle * sign_y;

            ////////////////////collision
            if ((((abs(tank->x + max_x + step * cos(tank->angle) - (map->walls + i)->x1) <= thick) && (state[tank->up])) ||
                 ((abs(tank->x - radius_circle * sign_x - step * cos(tank->angle) - (map->walls + i)->x1) <= thick) && (state[tank->down])))  &&
                (((map->walls + i)->x1 - (map->walls + i)->x2 == 0) &&
                 (abs(tank->y - ((map->walls + i)->y1 + (map->walls + i)->y2) / 2) <= abs((map->walls + i)->y1 - (map->walls + i)->y2) / 2 + radius_circle + thick / 2))
                    )
                return false;
            if ((((abs(tank->y + max_y + step * sin(tank->angle) - (map->walls + i)->y1) <= thick) && (state[tank->up])) ||
                 ((abs(tank->y - radius_circle * sign_y + step * cos(tank->angle) - (map->walls + i)->y1) <= thick) && (state[tank->down]))) &&
                ((map->walls + i)->y1 - (map->walls + i)->y2 == 0) &&
                (abs(tank->x - ((map->walls + i)->x1 + (map->walls + i)->x2) / 2) <= abs((map->walls + i)->x1 - (map->walls + i)->x2) / 2 + radius_circle + thick / 2))
                return false;


            ////////////////////rotation
            if ((((abs(tank->x + (shooter + radius_shooter) * cos(tank->angle + degree) - (map->walls + i)->x1) <= thick) && (state[tank->right])) ||
                 ((abs(tank->x + (shooter + radius_shooter) * cos(tank->angle - degree) - (map->walls + i)->x1) <= thick) && (state[tank->left]))) &&
                ((map->walls + i)->x1 - (map->walls + i)->x2 == 0) &&
                (abs(tank->y - ((map->walls + i)->y1 + (map->walls + i)->y2) / 2) <= abs((map->walls + i)->y1 - (map->walls + i)->y2) / 2 + thick))
                return false;
            if ((((abs(tank->y + (shooter + radius_shooter) * sin(tank->angle + degree) - (map->walls + i)->y1) <= thick) && (state[tank->right])) ||
                 ((abs(tank->y + (shooter + radius_shooter) * sin(tank->angle - degree) - (map->walls + i)->y1) <= thick) && (state[tank->left]))) &&
                ((map->walls + i)->y1 - (map->walls + i)->y2 == 0) &&
                (abs(tank->x - ((map->walls + i)->x1 + (map->walls + i)->x2) / 2) <= abs((map->walls + i)->x1 - (map->walls + i)->x2) / 2 + thick))
                return false;
        }
    }
    short vertl = vertex(tank->x - (radius_circle + (radius_shooter * 2 + step) * cos(tank->angle)), tank->y);
    short vertr = vertex(tank->x + (radius_circle + (radius_shooter * 2 + step) * cos(tank->angle)), tank->y);
    short vertu = vertex(tank->x, tank->y - (radius_circle + (radius_shooter * 2 + step) * sin(tank->angle)));
    short vertd = vertex(tank->x, tank->y + (radius_circle + (radius_shooter * 2 + step) * sin(tank->angle)));
    return true;
}

///////////////for reading from file. it works correctly

/*
bool movement_collids_walls(Tank *tank, Map *map) {
    for (int i = 0; i < numberofWalls; i++) {
        int max_x, max_y;
        int sign_x = (cos(tank->angle) > 0 ? 1 : -1);
        int sign_y = (sin(tank->angle) > 0 ? 1 : -1);
        if ((radius_shooter + shooter) * cos(tank->angle) * sign_x > radius_circle)         max_x = (radius_shooter + shooter) * cos(tank->angle);
        else max_x = radius_circle * sign_x;
        if ((radius_shooter + shooter) * sin(tank->angle) * sign_y > radius_circle)         max_y = (radius_shooter + shooter) * sin(tank->angle);
        else max_y = radius_circle * sign_y;

        ////////////////////
        if ((((abs(tank->x + max_x + step * cos(tank->angle) - (map->walls + i)->x1) <= thick) && (state[SDL_SCANCODE_UP])) ||
                ((abs(tank->x - radius_circle * sign_x - step * cos(tank->angle) - (map->walls + i)->x1) <= thick) && (state[SDL_SCANCODE_DOWN])))  &&
                (((map->walls + i)->x1 - (map->walls + i)->x2 == 0) &&
                (abs(tank->y - ((map->walls + i)->y1 + (map->walls + i)->y2) / 2) <= abs((map->walls + i)->y1 - (map->walls + i)->y2) / 2 + radius_circle + thick / 2))
                )
            return false;
        if ((((abs(tank->y - max_y - step * sin(tank->angle) - (map->walls + i)->y1) <= thick) && (state[SDL_SCANCODE_UP])) ||
                ((abs(tank->y + radius_circle * sign_y + step * cos(tank->angle) - (map->walls + i)->y1) <= thick) && (state[SDL_SCANCODE_DOWN]))) &&
                ((map->walls + i)->y1 - (map->walls + i)->y2 == 0) &&
                (abs(tank->x - ((map->walls + i)->x1 + (map->walls + i)->x2) / 2) <= abs((map->walls + i)->x1 - (map->walls + i)->x2) / 2 + radius_circle + thick / 2))
            return false;

        if (!(state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_LEFT])) {
            if (((((tank->y - radius_circle * sign_y - step * sin(tank->angle) >
                    min((map->walls + i)->y1, (map->walls + i)->y2)) &&
                   (tank->y - radius_circle * sign_y <= min((map->walls + i)->y1, (map->walls + i)->y2))) ||
                  ((tank->y - radius_circle * sign_y - step * sin(tank->angle) <
                    max((map->walls + i)->y1, (map->walls + i)->y2)) &&
                   (tank->y - radius_circle * sign_y >= max((map->walls + i)->y1, (map->walls + i)->y2))) &&
                  (state[SDL_SCANCODE_UP])) ||
                 ((abs(tank->y + radius_circle * sign_y + step * sin(tank->angle) - (map->walls + i)->y1) <= step) &&
                  (state[SDL_SCANCODE_DOWN]))) &&
                (abs(tank->x - (map->walls + i)->x1) <= step) && ((map->walls + i)->x1 - (map->walls + i)->x2 == 0))
                return false;
            if (((((tank->x + radius_circle * sign_x + step * cos(tank->angle) >
                    min((map->walls + i)->x1, (map->walls + i)->x2)) &&
                   (tank->x + radius_circle * sign_x <= min((map->walls + i)->x1, (map->walls + i)->x2))) ||
                  ((tank->x + radius_circle * sign_x + step * cos(tank->angle) <
                    max((map->walls + i)->x1, (map->walls + i)->x2)) &&
                   (tank->x + radius_circle * sign_x >= max((map->walls + i)->x1, (map->walls + i)->x2))) &&
                  (state[SDL_SCANCODE_UP])) ||
                 ((abs(tank->x - radius_circle * sign_x - step * cos(tank->angle) - (map->walls + i)->x1) <= step) &&
                  (state[SDL_SCANCODE_DOWN]))) &&
                (abs(tank->y - (map->walls + i)->y1) <= step) && ((map->walls + i)->y1 - (map->walls + i)->y2 == 0))
                return false;
        }

        ////////////////////
        if ((((abs(tank->x + (shooter + radius_shooter) * cos(tank->angle - degree) - (map->walls + i)->x1) <= thick) && (state[SDL_SCANCODE_RIGHT])) ||
                ((abs(tank->x + (shooter + radius_shooter) * cos(tank->angle + degree) - (map->walls + i)->x1) <= thick) && (state[SDL_SCANCODE_LEFT]))) &&
                ((map->walls + i)->x1 - (map->walls + i)->x2 == 0) &&
                (abs(tank->y - ((map->walls + i)->y1 + (map->walls + i)->y2) / 2) <= abs((map->walls + i)->y1 - (map->walls + i)->y2) / 2 + thick))
            return false;
        if ((((abs(tank->y - (shooter + radius_shooter) * sin(tank->angle - degree) - (map->walls + i)->y1) <= thick) && (state[SDL_SCANCODE_RIGHT])) ||
                ((abs(tank->y - (shooter + radius_shooter) * sin(tank->angle + degree) - (map->walls + i)->y1) <= thick) && (state[SDL_SCANCODE_LEFT]))) &&
                ((map->walls + i)->y1 - (map->walls + i)->y2 == 0) &&
                (abs(tank->x - ((map->walls + i)->x1 + (map->walls + i)->x2) / 2) <= abs((map->walls + i)->x1 - (map->walls + i)->x2) / 2 + thick))
            return false;
    }
    return true;
}*/
