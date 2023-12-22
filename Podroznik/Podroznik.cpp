#include<gl\glut.h>
#include <GL/freeglut.h>
#include <iostream>



class Renderer {
public:
    static void drawTriangle();
    static void drawCube();
    // Dodaj inne funkcje do rysowania innych obiektów 3D
};

void Renderer::drawTriangle() {
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f); // Czerwony
    glVertex3f(0.0f, 1.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f); // Zielony
    glVertex3f(-1.0f, -1.0f, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f); // Niebieski
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
}

float cubeVertices[][3] = {
    {-0.5, -0.5, 0.5},
    {0.5, -0.5, 0.5},
    {0.5, 0.5, 0.5},
    {-0.5, 0.5, 0.5},
    {-0.5, -0.5, -0.5},
    {0.5, -0.5, -0.5},
    {0.5, 0.5, -0.5},
    {-0.5, 0.5, -0.5}
};

GLfloat Move = 0.0f;
GLfloat trX = 0.0f;
GLfloat trY = 0.0f;
GLfloat trZ = 0.0f;


void Renderer::drawCube() {
    glTranslatef(trX,trY,trZ);
    // Rysuj prostopadłościan o bokach równych 1 w punkcie (0, 0, 0)
    glBegin(GL_QUADS);


    // Przód
    glColor3f(1.0f, 0.0f, 0.0f); // Czerwony
    glVertex3f(-0.5f+Move, -0.5f + Move, 0.5f + Move);
    glVertex3f(0.5f + Move, -0.5f + Move, 0.5f + Move);
    glVertex3f(0.5f + Move, 0.5f + Move, 0.5f + Move);
    glVertex3f(-0.5f + Move, 0.5f + Move, 0.5f + Move);

    // Tył
    glColor3f(0.0f , 1.0f, 0.0f ); // Zielony
    glVertex3f(-0.5f + Move, -0.5f + Move, -0.5f + Move);
    glVertex3f(0.5f + Move, -0.5f + Move, -0.5f + Move);
    glVertex3f(0.5f + Move, 0.5f + Move, -0.5f + Move);
    glVertex3f(-0.5f + Move, 0.5f + Move, -0.5f + Move);

    // Lewo
    glColor3f(0.0f , 0.0f , 1.0f ); // Niebieski
    glVertex3f(-0.5f + Move, -0.5f + Move, 0.5f + Move);
    glVertex3f(-0.5f + Move, 0.5f + Move, 0.5f + Move);
    glVertex3f(-0.5f + Move, 0.5f + Move, -0.5f + Move);
    glVertex3f(-0.5f + Move, -0.5f + Move, -0.5f + Move);

    // Prawo
    glColor3f(1.0f , 1.0f , 0.0f ); // Żółty
    glVertex3f(0.5f + Move, -0.5f + Move, 0.5f + Move);
    glVertex3f(0.5f + Move, 0.5f + Move, 0.5f + Move);
    glVertex3f(0.5f + Move, 0.5f + Move, -0.5f + Move);
    glVertex3f(0.5f + Move, -0.5f + Move, -0.5f + Move);

    // Góra
    glColor3f(1.0f , 0.0f , 1.0f ); // Magenta
    glVertex3f(-0.5f + Move, 0.5f + Move, 0.5f + Move);
    glVertex3f(0.5f + Move, 0.5f + Move, 0.5f + Move);
    glVertex3f(0.5f + Move, 0.5f + Move, -0.5f + Move);
    glVertex3f(-0.5f + Move, 0.5f + Move, -0.5f + Move);

    // Dół
    glColor3f(0.0f , 1.0f , 1.0f ); // Cyan
    glVertex3f(-0.5f + Move, -0.5f + Move, 0.5f + Move);
    glVertex3f(0.5f + Move, -0.5f + Move, 0.5f + Move);
    glVertex3f(0.5f + Move, -0.5f + Move, -0.5f + Move);
    glVertex3f(-0.5f + Move, -0.5f + Move, -0.5f + Move);

    glEnd();
}

float cameraX = 5.0f;
float cameraY = 2.0f;
float cameraZ = 5.0f;
float lookAtX = 0.0f;
float lookAtY = 0.0f;
float lookAtZ = 0.0f;
float upX = 0.0f;
float upY = 1.0f;
float upZ = 0.0f;

class Engine {

public:
    Engine(int argc, char** argv);
    ~Engine();

    void initialize(int width, int height, bool fullscreen);
    void run();
    static void handleKeyboard(unsigned char key, int x, int y);
   static void handleMouse(int button, int state, int x, int y);

   
   static void update();
    static void render();
    static void cleanup();

private:
    int windowWidth;
    int windowHeight;
    bool isFullscreen;
    static Renderer renderer;
    static void renderObjects();


    // Dodaj inne parametry i zmienne, takie jak czasomierz, buforowanie, itp.

    void setupGL();
    //void setViewport();
    // Dodaj inne funkcje pomocnicze związane z OpenGL i FreeGLUT
};

Renderer Engine::renderer;

void Engine::renderObjects() {
    // Tutaj można umieścić kod do renderowania różnych obiektów 3D
    // Na przykład:
    //Renderer::drawTriangle();
     Renderer::drawCube();

}


Engine::Engine(int argc, char** argv) {
    glutInit(&argc, argv);
    windowWidth = 800;
    windowHeight = 600;
    isFullscreen = false;
    // Zainicjuj inne zmienne i parametry
}

Engine::~Engine() {
    cleanup();
}

void Engine::initialize(int width, int height, bool fullscreen) {
    windowWidth = width;
    windowHeight = height;
    isFullscreen = fullscreen;
    // Inicjalizuj OpenGL i FreeGLUT
    setupGL();
}

void Engine::run() {
    glutMainLoop();
}

void Engine::handleKeyboard(unsigned char key, int x, int y) {
    // Obsługa klawiatury
    switch (key) {
    case 27: // ESC
        cleanup();
        exit(0);
        break;
        // Dodaj obsługę innych klawiszy
    case 'a':
        std::cout << "a" << std::endl;
        trX += 0.1f;
       // Move += 1.1f;
        //cameraX = +0.1f;
        //upX = +0.1f;
        ////upY =+0.1f;
        //upZ = +0.1f;
        break;
    case 'd':
        std::cout << "b" << std::endl;
        trX -= 0.1f;
       // Move -= 1.1f;
        /*cameraX = -0.1f;
        upX = -0.1f;
        upY = -0.1f;
        upZ = -0.1f;*/
        break;
    case 's':
        std::cout << "s" << std::endl;
        trZ -= 0.1f;
        break;
    }
    //glLoadIdentity();
    //gluLookAt(cameraX, cameraY, cameraZ, lookAtX, lookAtY, lookAtZ, upX, upY, upZ);
    glutPostRedisplay();
}

void Engine::handleMouse(int button, int state, int x, int y) {
    // Obsługa myszy (kliknięcia)
}


void Engine::update() {
    // Aktualizacja logiki gry
}

void Engine::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Renderowanie sceny
    renderObjects();
    glutSwapBuffers();
}

void Engine::cleanup() {
    // Deinicjalizacja OpenGL i FreeGLUT, sprzątanie pamięci, itp.
}

void Engine::setupGL() {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow("OpenGL Engine");

    if (isFullscreen) {
        glutFullScreen();
    }
    else {
        glutInitWindowSize(windowWidth, windowHeight);
        glutPositionWindow(100, 100);
    }

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutKeyboardFunc(handleKeyboard);
    glutMouseFunc(handleMouse);

    glutIdleFunc(update);
    glutDisplayFunc(render);
   
    // Ustawienie perspektywy
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, static_cast<float>(windowWidth) / static_cast<float>(windowHeight), 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Ustawienie pozycji kamery
    gluLookAt(cameraX, cameraY, cameraZ, lookAtX, lookAtY, lookAtZ, upX, upY, upZ);
}


int main(int argc, char** argv) {
    Engine engine(argc, argv);
    engine.initialize(800, 600, false);

    engine.run();
    return 0;
}
