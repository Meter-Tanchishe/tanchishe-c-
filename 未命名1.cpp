#include <iostream>
#include <conio.h> // ����_getch()������ȡ��������
#include <windows.h> // ���ڿ���̨��ʱ

using namespace std;

// ������Ϸ�Ŀ�Ⱥ͸߶�
const int WIDTH = 20;
const int HEIGHT = 17;

// �����ߵĳ�ʼλ�úʹ�С
int x = WIDTH / 2, y = HEIGHT / 2; // ��ͷλ��
int fruitX, fruitY; // ʳ��λ��
int score = 0; // ��ǰ����
int tailX[100], tailY[100]; // �����ÿ������
int nTail = 0; // �ߵĳ���
bool gameOver = false; // ��Ϸ�Ƿ����
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN}; // �ߵ��ƶ�����
eDirection dir; // ��ǰ�ƶ�����

// ���ÿ���̨���λ��
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// ��ʼ����Ϸ
void Setup() {
    dir = STOP; // ��ʼ����Ϊֹͣ
    x = WIDTH / 2; // ��ͷ��ʼλ��
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH; // �������ʳ��λ��
    fruitY = rand() % HEIGHT;
    score = 0; // ��ʼ����Ϊ0
}

// ������Ϸ����
void Draw() {
    system("cls"); // ������ע��: Windows���У�����ƽ̨������Ҫ�滻Ϊ��Ӧ������

    // �����ϱ߽�
    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;

    // ������Ϸ������
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0) {
                cout << "#"; // ��߽�
            }
            if (i == y && j == x) {
                cout << "O"; // ��ͷ
            }
            else if (i == fruitY && j == fruitX) {
                cout << "F"; // ʳ��
            }
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; // ����
                        print = true;
                    }
                }
                if (!print) {
                    cout << " "; // �հ�����
                }
            }

            if (j == WIDTH - 1) {
                cout << "#"; // �ұ߽�
            }
        }
        cout << endl;
    }

    // �����±߽�
    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;

    // ��ʾ����
    cout << "Score: " << score << endl;
}

// ���봦��
void Input() {
    if (_kbhit()) { // ����м�������
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

// �߼�����
void Logic() {
    // ��������ĵ�ǰλ��
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    // ��������
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // ������ͷ�ķ���
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

    // �����ײǽ����ײ���Լ�����Ϸ����
    if (x >= WIDTH || x < 0 || y >= HEIGHT || y < 0) {
        gameOver = true;
    }
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }

    // ����߳Ե�ʳ������ߵĳ��Ⱥͷ���
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        nTail++;
    }
}

// ��Ϸѭ��
void Run() {
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100); // ������Ϸ�ٶȣ���λ�����룩
    }
}

int main() {
    Setup();
    Run();
    cout << "Game Over!" << endl;
    return 0;
}

