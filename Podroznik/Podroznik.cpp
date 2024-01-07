#include <GL/freeglut.h>
#include <cmath>

class Engine {
private:
    float angle = 0.0f;
    float cameraAngleX = 0.0f;
    float cameraAngleY = 0.0f;
    float cameraDistance = 5.0f;

public:
    Engine() : angle(0.0f), cameraAngleX(0.0f), cameraAngleY(0.0f), cameraDistance(5.0f) {}
    void drawCube() {
        glPushMatrix();  // Push the current matrix onto the stack

        // Przekształcenia geometryczne
        //glTranslatef(0.0f, 0.0f, -5.0f);  // translation 
        //glRotatef(angle, 1.0f, 1.0f, 1.0f);  // rotation
        glScalef(0.5f, 0.5f, 0.5f);  // scaling


        glBegin(GL_QUADS);

        // Front face
        glColor3f(1.0f, 0.0f, 0.0f);  // Red
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);

        // Back face
        glColor3f(0.0f, 1.0f, 0.0f);  // Green
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);
        glVertex3f(1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);

        // Right face
        glColor3f(0.0f, 0.0f, 1.0f);  // Blue
        glVertex3f(1.0f, -1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);
        glVertex3f(1.0f, 1.0f, -1.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);

        // Left face
        glColor3f(1.0f, 1.0f, 0.0f);  // Yellow
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);

        // Top face
        glColor3f(0.0f, 1.0f, 1.0f);  // Cyan
        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);

        // Bottom face
        glColor3f(1.0f, 0.0f, 1.0f);  // Magenta
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);

        glEnd();
        glPopMatrix();
    }
    static void renderSceneWrapper() {
        Engine* engine = static_cast<Engine*>(glutGetWindowData());
        engine->renderScene();
    }
    void renderScene() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();

        // Ustawienie pozycji kamery
        gluLookAt(cameraDistance * sin(cameraAngleY) * cos(cameraAngleX),
            cameraDistance * sin(cameraAngleX),
            cameraDistance * cos(cameraAngleY) * cos(cameraAngleX),
            0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f);

        glRotatef(angle, 1.0f, 1.0f, 1.0f);

        drawCube();

        glutSwapBuffers();
    }

    static void updateWrapper(int value) {
        Engine* engine = static_cast<Engine*>(glutGetWindowData());
        engine->update(value);
    }

    void update(int value) {
        glutPostRedisplay();
        glutTimerFunc(16, updateWrapper, 0);
    }

    static void handleKeypressWrapper(unsigned char key, int x, int y) {
        Engine* engine = static_cast<Engine*>(glutGetWindowData());
        engine->handleKeypress(key, x, y);
    }

    void handleKeypress(unsigned char key, int x, int y) {
        switch (key) {
        case 'w':
            cameraAngleX += 0.1f;
            break;
        case 's':
            cameraAngleX -= 0.1f;
            break;
        case 'a':
            cameraAngleY -= 0.1f;
            break;
        case 'd':
            cameraAngleY += 0.1f;
            break;
        case 'z':
            cameraDistance -= 0.1f;
            break;
        case 'x':
            cameraDistance += 0.1f;
            break;
        }
        glutPostRedisplay();
    }
    void init() {
        glEnable(GL_DEPTH_TEST);
    }
    static void reshapeWrapper(int width, int height) {
        Engine* engine = static_cast<Engine*>(glutGetWindowData());
        engine->reshape(width, height);
    }
    void reshape(int width, int height) {
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 100.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
    void run(int argc, char** argv) {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(800, 600);

        glutCreateWindow("OpenGL 3D Cube Example");
        glutSetWindowData(this);

        init();

        glutDisplayFunc(renderSceneWrapper);
        glutReshapeFunc(reshapeWrapper);
        glutTimerFunc(25, updateWrapper, 0);
        glutKeyboardFunc(handleKeypressWrapper);

        glutMainLoop();
    }
};
int main(int argc, char** argv) {
    Engine engine;
    engine.run(argc, argv);
    return 0;
}
