#include <windows.h>
#include <iostream>
#include <gl/gl.h>
#include <cmath>
#include "function.h"
#include "camera.h"
#include "vector"

const int coordinatex = 5;
const int coordinatey = 5;
const int coordinatez = 5;
const float x_weight = 0.3;
const float y_weight = 0.3;
const float z_weight = 0.3;

HWND hwnd;
unsigned int texture;
float vertex[] = {-0.5, -0.5, -0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, -0.5,
                  -0.5, -0.5, 0.5, 0.5, -0.5, 0.5, 0.5, 0.5, 0.5, -0.5, 0.5, 0.5};
float tex_coord[] = {0, 1, 1, 1, 0, 1, 1, 1,
                     0, 0, 1, 0, 0, 0, 1, 0};

std::vector<std::vector<int>> baseInd;
int texIndCnt;

void compare(std::vector<int> &current, bool &back, bool &right, bool &forw, bool &left, bool &bot, bool &top) {
    if (back) {
        current.push_back(3);
        current.push_back(0);
        current.push_back(4);
        current.push_back(4);
        current.push_back(7);
        current.push_back(3);
    }

    if (right) {
        current.push_back(0);
        current.push_back(1);
        current.push_back(5);
        current.push_back(5);
        current.push_back(4);
        current.push_back(0);
    }
    if (forw) {
        current.push_back(1);
        current.push_back(2);
        current.push_back(6);
        current.push_back(6);
        current.push_back(5);
        current.push_back(1);
    }
    if (left) {
        current.push_back(2);
        current.push_back(3);
        current.push_back(7);
        current.push_back(7);
        current.push_back(6);
        current.push_back(2);
    }
    if (bot) {
        current.push_back(3);
        current.push_back(0);
        current.push_back(1);
        current.push_back(1);
        current.push_back(2);
        current.push_back(3);
    }
    if (top) {
        current.push_back(7);
        current.push_back(4);
        current.push_back(5);
        current.push_back(5);
        current.push_back(6);
        current.push_back(7);
    }

}

void texindForm(int a, int b, int c, std::vector<int> &v2) {
    bool top = true;
    bool bot = true;
    bool right = true;
    bool left = true;
    bool forw = true;
    bool back = true;
    std::vector<int> current = {};

    for (int i = 0; i < v2.size(); i += 2) {
        if (i != 0) {
            if (v2[i - 2] != v2[i]) {
                compare(current, back, right, forw, left, bot, top);
                baseInd.emplace(baseInd.begin() + v2[i - 2], current);
                top = true;
                bot = true;
                right = true;
                left = true;
                forw = true;
                back = true;
                current = {};
            }
        }


        if (v2[i + 1] - v2[i] == -c) {
            right = false;
        } else if (v2[i + 1] - v2[i] < -1) {
            back = false;
        } else if (v2[i + 1] - v2[i] == -1) {
            bot = false;
        } else if (v2[i + 1] - v2[i] == 1) {
            top = false;
        } else if (v2[i + 1] - v2[i] == c) {
            left = false;
        } else if (v2[i + 1] - v2[i] > 1) {
            forw = false;
        }


    }
    compare(current, back, right, forw, left, bot, top);
    baseInd.emplace(baseInd.begin() + v2[v2.size() - 2], current);
}

void Load_Texture() {
    int width, height;
    width = 2;
    height = 2;
    struct {
        unsigned char r, g, b, a;
    } data[2][2];
    memset(data, 0, sizeof(data));
    data[0][0].r = 255;
    data[1][0].g = 255;
    data[1][1].b = 255;
    data[0][1].r = 255;
    data[0][1].g = 255;


    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindTexture(0, texture);
}

void Win_Resize(int x, int y) {
    glViewport(0, 0, x, y);
    float k = x / (float) y;
    float sz = 0.1;
    glLoadIdentity();
    glFrustum(-k * sz, k * sz, -sz, sz, sz * 2, 80);
}

void GameInit() {
    Load_Texture();


    RECT rct;
    GetClientRect(hwnd, &rct);
    Win_Resize(rct.right, rct.bottom);
    glEnable(GL_DEPTH_TEST);
}

void Player_Move() {
    if (GetForegroundWindow() != hwnd)return;
    Camera_MoveByMouse(400, 400);
}

void Game_Move() {
    Player_Move();
}


void ShowWorld(float *vert, GLuint *ind, float *ppp, int ind_size, int vert_size) {
    glClearColor(0.6196078431372549f, 0.9725490196078431f, 0.9333333333333333f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glPushMatrix();
    Camera_Apply();
    glScalef(5, 5, 5);

    glEnableClientState(GL_VERTEX_ARRAY);


//    glVertexPointer(3, GL_FLOAT, 0, vert);
//    glColor3f(0.203921568627451, 0.5333333333333333, 0.5333333333333333);
//    glLineWidth(3);
//    glDrawElements(GL_LINES, ind_size, GL_UNSIGNED_INT, ind);


    glVertexPointer(3, GL_FLOAT, 0, ppp);
    glColor3f(0.9490196078431373, 0.2666666666666667, 0.0196078431372549);
    glPointSize(50);
    glDrawArrays(GL_POINTS, 0, 1);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);


    glColor3f(1, 1, 1);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    for (int i = 0; i < ind_size; i += 2) {
        glVertexPointer(3, GL_FLOAT, 0, vertex);
        glTexCoordPointer(2, GL_FLOAT, 0, tex_coord);


        GLuint curr[baseInd[ind[i]].size()];
        std::copy(baseInd[ind[i]].begin(), baseInd[ind[i]].end(), curr);
        texIndCnt = sizeof(curr) / sizeof(GLuint);


        glPushMatrix();

        glTranslatef(vert[3 * ind[i]], vert[3 * ind[i] + 1], vert[3 * ind[i] + 2]);
        glDrawElements(GL_TRIANGLES, texIndCnt, GL_UNSIGNED_INT, curr);
        glPopMatrix();
    }
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glPopMatrix();


}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    auto v1 = std::vector<float>();
    auto v2 = std::vector<int>();
    auto p = gen(coordinatex, coordinatey, coordinatez, x_weight, y_weight, z_weight, v1, v2);
    texindForm(coordinatex, coordinatey, coordinatez, v2);


    float vert[v1.size()];//координаты
    GLuint ind[v2.size()];// индексы
    float ppp[] = {(float) p.x, (float) p.y, (float) p.z};
    std::copy(v1.begin(), v1.end(), vert);
    std::copy(v2.begin(), v2.end(), ind);
    int ind_size = v2.size();
    int vert_size = v1.size();
    for (int i = 0; i < v2.size(); i += 2) {
//        std::cout<<ind[i]<<' '<<ind[i+1]<<'\t'<<'\t'<<vert[3*ind[i]]<<' '<<vert[3*ind[i]+1]<<' '<<vert[3*ind[i]+2]<<'\t'<<'\t'<<vert[3*ind[i+1]]<<' '<<vert[3*ind[i+1]+1]<<' '<<vert[3*ind[i+1]+2]<<'\n';
//        std::cout<<i<<'\n';
//        for (int j = 0; j < baseInd[i].size(); j++) {
//            std::cout<<baseInd[i][j]<<' ';
//        }
//        std::cout<<'\n';
    }


    WNDCLASSEX wcex;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;
    /*
     *  Введение главных переменных для сообщением с Windows.
     *  bQuit - переменная отвечающая за статус окна.
     *  theta - float для подсчета тиков.
     */

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;
    /*
     *  WNDCLASSEX содержит информацию о классе окна:
     *  cbSize устанавливает размер этой структуры, в байтах.
     *  style устанавливает стиль класса.
     *  lpfnWndProc указатель на оконную процедуру.
     *  cbClsExtra устанавливает число дополнительных байт, которые размещаются вслед за структурой класса окна.
     *  cbWndExtra устанавливает число дополнительных байтов, которые размещаются вслед за экземпляром окна.
     *  hInstance дескриптор экземпляра, который содержит оконную процедуру для класса.
     *  hIcon дескриптор значка класса.
     *  hCursor дескриптор курсора класса.
     *  hbrBackground дескриптор кисти фона класса.
     *  lpszMenuName указатель на символьную строку с символом конца строки.
     *  lpszClassName указатель на символьную строку с нулем в конце или атом.
     *  hIconSm дескриптор маленького значка, который связан с классом окна.
     */

    if (!RegisterClassEx(&wcex))
        return 0;

    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "Maze3D",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          1000,
                          1000,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);
    /*
     * Задаем параметры открывающегося окна, в том числе размемер и навание
     */

    ShowWindow(hwnd, nCmdShow);
    /*
     * Открытие окна
     */


    EnableOpenGL(hwnd, &hDC, &hRC);
    /*
     * Применяем OpenGl для Windows.
     */

    GameInit();
    while (!bQuit) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                bQuit = TRUE;
            } else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            /*
             * Реакция программы на всплявающие сообщения.
             */
        } else {

            Game_Move();
            ShowWorld(vert, ind, ppp, ind_size, vert_size);

            SwapBuffers(hDC);

            Sleep(1);
        }
        /*
         * Проверка на вылетающие сообщения.
         */
    }
    /*
     * Тело цикла в котором и происходит отрисовка объектов.
     */

    DisableOpenGL(hwnd, hDC, hRC);
    /*
     * Отключение OpenGl.
     */

    DestroyWindow(hwnd);
    /*
     * Закрытие окна.
     */

    return msg.wParam;
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CLOSE:
            PostQuitMessage(0);
            break;

        case WM_SIZE:
            Win_Resize(LOWORD(lParam), HIWORD(lParam));
            break;

        case WM_SETCURSOR:
            ShowCursor(FALSE);
            break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN: {
            switch (wParam) {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                    break;
            }
        }
            break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC *hDC, HGLRC *hRC) {
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC) {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}
