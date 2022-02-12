#ifndef TYPEENUM_HPP_
#define TYPEENUM_HPP_

enum ObjectType {
  BACKGROUND = 1,
  BUTTONS = 2,
  BUTTONS_CONNECT = 3,
  BUTTONS_JOIN = 4,
  BUTTONS_READY = 5,
  ICONS = 6,
  INPUT_HOST = 7,
  INPUT_PORT = 8,
  TEXT = 9,
};

enum EntityType {
    PLAYER = 1,
};

enum MoveState {
  TOP = 1,
  BOT = 2,
  RIGHT = 3,
  LEFT = 4,
  ATTACK = 5,
};

#endif
