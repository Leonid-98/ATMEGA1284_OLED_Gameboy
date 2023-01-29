/*
 * dino.h
 *
 * Created: 20.01.2023 03:40:58
 *  Author: Leonid Tsigrinski
 */

#ifndef DINO_H_
#define DINO_H_

#define DINO_WIDTH          25
#define DINO_HEIGHT         26
#define DINO_SPAWN_X        10
#define DINO_SPAWN_Y        29

#define TREE1_WIDTH         11
#define TREE1_HEIGHT        23
#define TREE1_SPAWN_X       127
#define TREE2_WIDTH         15
#define TREE2_HEIGHT        23
#define TREE2_SPAWN_X       195
#define TREE_Y              35

#define DINO_JUMP_HEIGHT    22

#define BASE_LINE_X         0
#define BASE_LINE_Y         54
#define BASE_LINE_X1        127
#define BASE_LINE_Y1        54

enum
{
    Dino_Running,
    Dino_Jumping,
    Dino_Falling
};

struct dino_object_st
{
    const uint16_t *bitmap;
    uint8_t width;
    uint8_t height;
    uint16_t x;
    uint16_t y;
    uint8_t type;
};

void dino_gameloop();

#endif /* DINO_H_ */