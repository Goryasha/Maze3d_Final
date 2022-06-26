//// Главный скрипт нашей прогрмаммы, ответственный за генерацию лабиринта и его отрисовку.
#include <windows.h>
#include <gl/gl.h>
#include <cmath>
#include "function.h"
#include "camera.h"
#include "vector"

/**
 * @param hwnd - Маркер окна Windows, показывающий верхнее открытое окно. Вынесен из WinMain для возможности использования в других функциях;
 * @param texture - Переменная, в которую далее будет записана текстура;
 * @param texIndCnt - Длина набора индексов отрисовываемых текстур.
 */
HWND hwnd;
unsigned int texture;
int texIndCnt;

void compare(std::vector<int> &current,bool &back,bool &right,bool &forw,bool &left,bool &bot,bool &top){
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

void texindForm(int c,std::vector<int> &v2,std::vector <std::vector <int>> &baseInd){
    bool top =true;
    bool bot =true;
    bool right =true;
    bool left =true;
    bool forw =true;
    bool back =true;
    std::vector <int> current={};

    for (int i = 0; i < v2.size(); i+=2) {
        if (i!=0) {
            if (v2[i-2] != v2[i]) {
                compare(current,back,right,forw,left,bot,top);
                baseInd.emplace(baseInd.begin() + v2[i-2], current);
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
    compare(current,back,right,forw,left,bot,top);
    baseInd.emplace(baseInd.begin() + v2[v2.size()-2], current);
}

void Load_Texture(){
    /**
     * @param width - ширина текстуры;
     * @param hight - высота текстуры.
     */
    int width=2;
    int height=2;

    /**
     * Структурка, хранящая в себе для каждого из блоков цвет и альфа-канал.
     * @param r - красный;
     * @param g - зеленый;
     * @param b - синий;
     * @param a - альфа-канал.
     */
    struct {unsigned char r,g,b,a;} data[2][2] = {{0,0,0,0},
                                                 {0,0,0,0}};
    data[0][0].r=255;
    data[1][0].g=255;
    data[1][1].b=255;
    data[0][1].r=255;
    data[0][1].g=255;


    /**
     * Эта часть кода создает на движке gl одну текстуру, записывает параметры ее распространения на область тектсурирования,
     * параметры цвета из data и наконец очищает буфер текстур.
     */
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0, GL_RGBA,GL_UNSIGNED_BYTE,data);
    glBindTexture(GL_TEXTURE_2D,0);
    glBindTexture(0,texture);
}

void Win_Resize(int x, int y){
    glViewport(0,0,x,y);
    /**
     * @param k - отношение длины к ширине окна.
     * @param sz - коэффициент проектирования.
     */
    float k = x/(float)y;
    float sz=0.1;
    glLoadIdentity();
    glFrustum(-k*sz,k*sz,-sz,sz,sz*2,80);
    //// Вот и наша перспективная проекция.
}

void GameInit(){
    Load_Texture();

    /**
     * Получаем координаты клиентской области окна, переделываем перспективную проекцию и включаем тест глубины.
     * @param rct - определяет прямоугольник по координатам его верхнего левого и нижнего правых углов.
     */
    RECT rct;
    GetClientRect(hwnd,&rct);
    Win_Resize(rct.right,rct.bottom);
    glEnable(GL_DEPTH_TEST);
}

void Player_Move(){
    if(GetForegroundWindow()!=hwnd)return;
    Camera_MoveByMouse(400,400);
}

void ShowWorld(float *vert,GLuint *ind, float *ppp, int ind_size, int vert_size,float *tex_coord,float *vertex,std::vector <std::vector <int>> &baseInd){
    //// Устанавливаем цвет фона и вклбчаем очищения буффера цвета и глубины.
    glClearColor(0.6196078431372549f, 0.9725490196078431f, 0.9333333333333333f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    //// Биндим текстуру
    glBindTexture(GL_TEXTURE_2D,texture);
    glPushMatrix();
    //// Добавляем камеру и увеличиваем размер изображения в 5 раз.
    Camera_Apply(coordinatex,coordinatey,coordinatez);
    glScalef(5,5,5);
    glEnableClientState(GL_VERTEX_ARRAY);


//// Отрисовка лабиринта как дерева
//    glVertexPointer(3,GL_FLOAT,0,vert);
//    glColor3f(0.203921568627451,0.5333333333333333,0.5333333333333333);
//    glLineWidth(3);
//    glDrawElements(GL_LINES,ind_size,GL_UNSIGNED_INT,ind);

//// Отрисовка финальной точки.
    glVertexPointer(3,GL_FLOAT,0,ppp);
//    glColor3f(0.9490196078431373,0.2666666666666667,0.0196078431372549);
    glColor3f(0,0,0);
    glPointSize(50);
    glDrawArrays(GL_POINTS,0,1);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glColor3f(1,1,1);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    /**
     * На каждой итерации цикла для соответствующего индекса ноды из вектора набора индексов выбираются нужные координаты,
     * отрисовываются кубы и текстуры на них.
     */
    for (int i=0;i<ind_size;i+=2){
        glVertexPointer(3,GL_FLOAT,0,vertex);
        glTexCoordPointer(2,GL_FLOAT,0,tex_coord);


        GLuint curr[baseInd[ind[i]].size()];
        std::copy(baseInd[ind[i]].begin(),baseInd[ind[i]].end(),curr);
        texIndCnt = sizeof(curr)/sizeof(GLuint);


        glPushMatrix();

        glTranslatef(vert[3*ind[i]],vert[3*ind[i]+1],vert[3*ind[i]+2]);
        glDrawElements(GL_TRIANGLES,texIndCnt,GL_UNSIGNED_INT,curr);
        glPopMatrix();
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glPopMatrix();


}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    /**
     * @param vertex - координаты единичного куба;
     * @param tex_coord - массив текстурных координат.
     * @param baseInd - двумерный вектор, в котором для каждого индекса единичного куба лежит набор индексов отрисовываемых текстур;
     * @param v1 - вектор координат нод;
     * @param v2 - вектор индексов нод;
     */
    float vertex[]={-0.5,-0.5,-0.5, 0.5,-0.5,-0.5, 0.5,0.5,-0.5, -0.5,0.5,-0.5,
                    -0.5,-0.5,0.5, 0.5,-0.5,0.5, 0.5,0.5,0.5, -0.5,0.5,0.5};
    float tex_coord[]={0,1, 1,1, 0,1, 1,1,
                       0,0,1,0,0,0,1,0};
    std::vector <std::vector <int>> baseInd;
    auto v1 =std::vector<float>();
    auto v2 =std::vector<int>();
    auto p = gen(coordinatex,coordinatey,coordinatez,x_weight,y_weight,z_weight,v1,v2);
    //// Формирование векторов и вектора координта текстур.
    texindForm(coordinatez,v2,baseInd);


    /**
     * Переписывание векторов в массивы для дальнейшей отрисовки.
     */
    float vert[v1.size()];
    GLuint ind[v2.size()];
    float ppp[]={(float)p.x,(float)p.y,(float)p.z};
    std::copy(v1.begin(),v1.end(),vert);
    std::copy(v2.begin(),v2.end(),ind);
    int ind_size = v2.size();
    int vert_size = v1.size();


    /**
     *  Введение главных переменных для сообщением с Windows.
     *  @param wcex - информация о классе окна;
     *  @param hDC - дескриптор контекста устройства для отрисовки на окне;
     *  @param msg - содержит сведения о сообщениях из очереди сообщений потока;
     *  @param bQuit - переменная отвечающая за статус окна.
     */
    WNDCLASSEX wcex;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;

    /**
     *  @param WNDCLASSEX содержит информацию о классе окна:
     *  @param cbSize устанавливает размер этой структуры, в байтах.
     *  @param style устанавливает стиль класса.
     *  @param lpfnWndProc указатель на оконную процедуру.
     *  @param cbClsExtra устанавливает число дополнительных байт, которые размещаются вслед за структурой класса окна.
     *  @param cbWndExtra устанавливает число дополнительных байтов, которые размещаются вслед за экземпляром окна.
     *  @param hInstance дескриптор экземпляра, который содержит оконную процедуру для класса.
     *  @param hIcon дескриптор значка класса.
     *  @param hCursor дескриптор курсора класса.
     *  @param hbrBackground дескриптор кисти фона класса.
     *  @param lpszMenuName указатель на символьную строку с символом конца строки.
     *  @param lpszClassName указатель на символьную строку с нулем в конце или атом.
     *  @param hIconSm дескриптор маленького значка, который связан с классом окна.
     */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;

    if (!RegisterClassEx(&wcex))
        return 0;

    //// Задаем параметры открывающегося окна, в том числе размемер и наваниею
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

    //// Открытие окна.
    ShowWindow(hwnd, nCmdShow);

    ////Применяем OpenGl для Windows.
    EnableOpenGL(hwnd, &hDC, &hRC);

    GameInit();
    //// Тело цикла в котором и происходит отрисовка объектов.
    while (!bQuit)
    {
        //// Реакция программы на всплявающие сообщения.
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {

            Player_Move();
            ShowWorld(vert,ind,ppp,ind_size,vert_size,tex_coord,vertex,baseInd);

            SwapBuffers(hDC);

            Sleep (1);
        }
    }

    //// Отключение OpenGl.
    DisableOpenGL(hwnd, hDC, hRC);

    //// Закрытие окна.
    DestroyWindow(hwnd);
    return msg.wParam;
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
            break;

        case WM_SIZE:
            Win_Resize(LOWORD(lParam),HIWORD(lParam));
            break;

        case WM_SETCURSOR:
            ShowCursor(FALSE);
            break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
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

//// Базовые строки кода для OpenGL. Написаны не мной.
void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
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

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}
