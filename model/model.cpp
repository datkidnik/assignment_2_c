#include "model.h"

std::unique_ptr<draughts::model::model> draughts::model::model::instance =
nullptr;

const int BOARD_SIZE = 8;
std::map<int, std::string> nameslist;
int player_1_num;
int player_2_num;
int current_player;

int board[BOARD_SIZE][BOARD_SIZE];

draughts::model::model::model(void) 
{
}

draughts::model::model * draughts::model::model::get_instance(void)
{
    if(instance == nullptr)
    {
        instance = std::unique_ptr<model>(new model);	
    }
    return instance.get();    
}

int draughts::model::model::get_player_score(int playernum)
{
    return EOF;
}

void draughts::model::model::start_game(int plr1, int plr2)
{
    player_1_num = plr1;
    player_2_num = plr2;

    if(get_random(1, 2) == 1) {
        current_player = player_1_num;
    }
    else {
        current_player = player_2_num;
    }

    for(int row = 0; row < 3; row++) {
        for(int col = 0; col < BOARD_SIZE; col++) {
            if((row + col) % 2 == 1) {
                board[row][col] = player_1_num;
            }
        }
    }

    for(int row = 5; row < BOARD_SIZE; row++) {
        for(int col = 0; col < BOARD_SIZE; col++) {
            if((row + col) % 2 == 1) {
                board[row][col] = player_2_num;
            }
        }
    }
}

int draughts::model::model::get_winner()
{
    return EOF;
}

std::string draughts::model::model::get_player_name(int id)
{
    return nameslist[id];
}

char draughts::model::model::get_token(int x ,int y)
{
    if(board[x - 1][y - 1] == player_1_num) {
        return 'O';
    }

    if(board[x - 1][y - 1] == player_2_num) {
        return 'X';
    }

    return ' ';
}

void draughts::model::model::make_move(int playernum,
        int startx, int starty, int endx, int endy)
{
    int sx = startx - 1;
    int sy = starty - 1;
    int ex = endx - 1;
    int ey = endy - 1;

    if(board[sx][sy] != playernum)
    {
        throw std::invalid_argument("Not the player's piece");
    }

    if(endx < 1 || endx > BOARD_SIZE || endy < 1 || endy > BOARD_SIZE)
    {
        throw std::invalid_argument("Not within bounds of board");
    }

    board[ex][ey] = board[sx][sy];
    board[sx][sy] = 0;
}

void draughts::model::model::add_player(const std::string& p)
{
    nameslist.insert(std::pair<int, std::string>(nameslist.size() + 1, p));
}

bool draughts::model::model::player_exists(const std::string& pname)
{
    std::map<int, std::string>::iterator it;
    for(it = nameslist.begin(); it != nameslist.end(); it++)
    {
        if(it->second == pname) {
            return true;
        }
    }

    return false;
}

int draughts::model::model::get_current_player(void)
{
    return current_player;
}

std::map<int, std::string> draughts::model::model::get_player_list(void) 
    const
{
    return nameslist;
}

void draughts::model::model::delete_instance(void)
{
    instance.reset(nullptr);
}


int draughts::model::model::get_width()
{
    return BOARD_SIZE;
}

int draughts::model::model::get_height()
{
    return BOARD_SIZE;
}

int draughts::model::model::get_random(int min, int max)
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(min, max);
    
    return distribution(generator);
}

draughts::model::model::~model(void)
{
}

