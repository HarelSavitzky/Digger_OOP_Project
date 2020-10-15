#pragma once

//window size consts-----------------
const int WINDOW_HEIGHT = 1000;
const int WINDOW_WIDTH = 1600;
const int FRAME_GAP = 200;

//level char representation consts-----------------
const char DIGGER = '/';
const char MONSTER = '!';
const char DIAMOND = 'D';
const char ROCK = '@';
const char EMPTY = ' ';
const char WALL = '#';
const char GIFT = '+';

//game messages consts-----------------
const int GAME_MESSAGES = 5;
const int GAME_OVER = 0;
const int LOSE = 1;
const int WIN = 2;
const int LEVEL_UP = 3;
const int QUIT = 4;

//gift messages consts-----------------
const int GIFT_MESSAGE = 3;
const int SCORE_MESSAGE = 0;
const int ROCK_MESSAGE = 1;
const int TIME_MESSAGE = 2;
const int NO_GIFT = 666;

//score const consts-----------------
const int GIFT_SCORE = 50;
const int GIFT_TIME = 30;
const int DIAMOND_SCORE = 15;
const int LEVEL_SCORE = 20;

//starting consts-----------------
const int STARTING_LIFES = 3;
const int STARTING_SCORE = 0;

//music consts-----------------
const int MUSIC_FILES = 2;
const int MENU_MUSIC = 0;
const int GAME_MUSIC = 1;

//sound consts-----------------
const int SOUND_FILES = 9;
const int MET_MONSTER_SOUND = 0;
const int EAT_ROCK_SOUND = 1;
const int EAT_DIAMOND_SOUND = 2;
const int LEVEL_FAILED_SOUND = 3;
const int FINISH_LEVEL_SOUND = 4;
const int START_LEVEL_SOUND = 5;
const int WON_GAME_SOUND = 6;
const int LOST_GAME_SOUND = 7;
const int GIFT_SOUND = 8;

//volume consts-----------------
const int MENU_VOLUME = 80;
const int GAME_VOLUME = 20;

//stats consts-----------------
const int LEVEL = 0;
const int LIFE = 1;
const int ROCKS = 2;
const int TIME = 3;
const int SCORE = 4;
const int DIAMONDS = 5;
const int INFO_ITEMS = 5;
const int GAME_STATS = 6;

//direction consts-----------------
const sf::Keyboard::Key KEYBOARD_UP = sf::Keyboard::Key::Up;
const sf::Keyboard::Key KEYBOARD_DOWN = sf::Keyboard::Key::Down;
const sf::Keyboard::Key KEYBOARD_RIGHT = sf::Keyboard::Key::Right;
const sf::Keyboard::Key KEYBOARD_LEFT = sf::Keyboard::Key::Left;
const sf::Keyboard::Key KEYBOARD_SPACE = sf::Keyboard::Key::Space;

//menu consts -----------------------
const int MAX_NUMBER_OF_ITEMS = 2;
