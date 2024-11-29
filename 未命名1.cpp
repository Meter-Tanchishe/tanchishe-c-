#include <iostream>
#include <conio.h> // 用于_getch()函数获取键盘输入
#include <windows.h> // 用于控制台延时

using namespace std;

// 定义游戏的宽度和高度
const int WIDTH = 20;
const int HEIGHT = 17;

// 定义蛇的初始位置和大小
int x = WIDTH / 2, y = HEIGHT / 2; // 蛇头位置
int fruitX, fruitY; // 食物位置
int score = 0; // 当前分数
int tailX[100], tailY[100]; // 蛇身的每个部分
int nTail = 0; // 蛇的长度
bool gameOver = false; // 游戏是否结束
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN}; // 蛇的移动方向
eDirection dir; // 当前移动方向

// 设置控制台光标位置
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// 初始化游戏
void Setup() {
    dir = STOP; // 初始方向为停止
    x = WIDTH / 2; // 蛇头初始位置
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH; // 随机生成食物位置
    fruitY = rand() % HEIGHT;
    score = 0; // 初始分数为0
}

// 绘制游戏区域
void Draw() {
    system("cls"); // 清屏（注意: Windows特有，其他平台可能需要替换为相应方法）

    // 绘制上边界
    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;

    // 绘制游戏区内容
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0) {
                cout << "#"; // 左边界
            }
            if (i == y && j == x) {
                cout << "O"; // 蛇头
            }
            else if (i == fruitY && j == fruitX) {
                cout << "F"; // 食物
            }
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; // 蛇身
                        print = true;
                    }
                }
                if (!print) {
                    cout << " "; // 空白区域
                }
            }

            if (j == WIDTH - 1) {
                cout << "#"; // 右边界
            }
        }
        cout << endl;
    }

    // 绘制下边界
    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;

    // 显示分数
    cout << "Score: " << score << endl;
}

// 输入处理
void Input() {
    if (_kbhit()) { // 如果有键盘输入
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

// 逻辑处理
void Logic() {
    // 保存蛇身的当前位置
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    // 更新蛇身
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // 更新蛇头的方向
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    // 如果蛇撞墙或者撞到自己，游戏结束
    if (x >= WIDTH || x < 0 || y >= HEIGHT || y < 0) {
        gameOver = true;
    }
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }

    // 如果蛇吃到食物，增加蛇的长度和分数
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        nTail++;
    }
}

// 游戏循环
void Run() {
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100); // 控制游戏速度（单位：毫秒）
    }
}

int main() {
    Setup();
    Run();
    cout << "Game Over!" << endl;
    return 0;
}

