#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#define WINDOW_TITLE "OpenGL Window"

void drawCone();
void drawBall();
void drawTopping();

float speed = 0;
bool rotate = false;

// use dedicated GPU to run
extern "C"
{
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}
extern "C"
{
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE)
            PostQuitMessage(0);
        else if (wParam == VK_SPACE)
        {
            if (rotate)
                rotate = false;
            else
                rotate = true;
        }
    default:
        break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
    PIXELFORMATDESCRIPTOR pfd;
    ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

    pfd.cAlphaBits = 8;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 0;

    pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

    pfd.iLayerType = PFD_MAIN_PLANE;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;

    // choose pixel format returns the number most similar pixel format available
    int n = ChoosePixelFormat(hdc, &pfd);

    // set pixel format returns whether it sucessfully set the pixel format
    if (SetPixelFormat(hdc, n, &pfd))
    {
        return true;
    }
    else
    {
        return false;
    }
}
//--------------------------------------------------------------------

void display()
{
    // handle resolution problem
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double w = 1920;
    double h = 1080;
    double ar = w / h;
    glOrtho(-2 * ar, 2 * ar, -2, 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // GLUquadricObj *sphere = NULL;
    // sphere = gluNewQuadric();
    // glRotatef(1, 1, 0, 1);
    // glColor3ub(30, 136, 229);
    // glPointSize(2);
    // gluQuadricDrawStyle(sphere, GLU_POINT);
    // gluSphere(sphere, 0.8, 50, 50);
    // gluDeleteQuadric(sphere);

    glRotatef(speed, 0, 1, 0);
    drawBall();
    drawCone();
    drawTopping();
}

void drawCone()
{
    glPushMatrix();
    GLUquadricObj *cylinder = NULL;
    cylinder = gluNewQuadric();
    glRotatef(270, 1, 0, 0);

    glTranslatef(0, 0, -1);
    glColor3ub(186, 129, 83);
    glPointSize(2);
    gluQuadricDrawStyle(cylinder, GLU_FILL);
    gluCylinder(cylinder, 0.01, 0.4, 1.2, 20, 20);
    gluDeleteQuadric(cylinder);
    glPopMatrix();

    glPushMatrix();
    cylinder = gluNewQuadric();
    glRotatef(270, 1, 0, 0);

    glTranslatef(0, 0, -1);
    glColor3ub(98, 66, 40);
    gluQuadricDrawStyle(cylinder, GLU_LINE);
    gluCylinder(cylinder, 0.011, 0.41, 1.2, 15, 15);
    gluDeleteQuadric(cylinder);
    glPopMatrix();
}

void drawBall()
{
    glPushMatrix();
    GLUquadricObj *sphere = NULL;
    sphere = gluNewQuadric();

    glTranslatef(0, 0.6, 0);
    glColor3ub(243, 229, 171);
    gluSphere(sphere, 0.31, 50, 50);
    gluDeleteQuadric(sphere);
    glPopMatrix();

    glPushMatrix();
    sphere = gluNewQuadric();
    glTranslatef(0, 0.3, 0);
    glColor3ub(128, 90, 70);
    gluSphere(sphere, 0.39, 50, 50);
    gluDeleteQuadric(sphere);
    glPopMatrix();
}

void drawTopping()
{
    glPushMatrix();
    GLUquadricObj *cylinder = NULL;
    cylinder = gluNewQuadric();
    glTranslatef(0.2, 0.8, 0.15);
    glColor3ub(61, 36, 28);
    glRotatef(110, 1, 1, 0);
    gluCylinder(cylinder, 0.01, 0.01, 0.1, 15, 15);
    gluDeleteQuadric(cylinder);
    glPopMatrix();

    glPushMatrix();
    cylinder = gluNewQuadric();
    glTranslatef(-0.2, 0.8, 0.155);
    glColor3ub(102, 45, 28);
    glRotatef(50, 0, 1, 0);
    gluCylinder(cylinder, 0.01, 0.01, 0.1, 15, 15);
    gluDeleteQuadric(cylinder);
    glPopMatrix();

    glPushMatrix();
    cylinder = gluNewQuadric();
    glRotatef(50, 0, 1, 0);
    glTranslatef(0.2, 0.85, 0);
    glColor3ub(219, 104, 133);
    gluCylinder(cylinder, 0.01, 0.01, 0.1, 15, 15);
    gluDeleteQuadric(cylinder);
    glPopMatrix();

    glPushMatrix();
    cylinder = gluNewQuadric();
    glColor3ub(234, 171, 102);
    glRotatef(250, 1, 0, 0);
    glTranslatef(0, 0, 0.5);
    gluCylinder(cylinder, 0.05, 0.05 , 0.9, 15, 15);
    gluDeleteQuadric(cylinder);
    glPopMatrix();
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpfnWndProc = WindowProcedure;
    wc.lpszClassName = WINDOW_TITLE;
    wc.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClassEx(&wc))
        return false;

    HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT, CW_USEDEFAULT, 1920, 1080,
                             NULL, NULL, wc.hInstance, NULL);

    //--------------------------------
    //	Initialize window for OpenGL
    //--------------------------------

    HDC hdc = GetDC(hWnd);

    //	initialize pixel format for the window
    initPixelFormat(hdc);

    //	get an openGL context
    HGLRC hglrc = wglCreateContext(hdc);

    //	make context current
    if (!wglMakeCurrent(hdc, hglrc))
        return false;

    //--------------------------------
    //	End initialization
    //--------------------------------

    ShowWindow(hWnd, nCmdShow);

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        display();

        if (rotate)
            speed = 2;
        else
            speed = 0;

        SwapBuffers(hdc);
    }
    UnregisterClass(WINDOW_TITLE, wc.hInstance);
    return true;
}
