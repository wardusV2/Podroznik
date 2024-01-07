#include<gl\glut.h>
#include <GL/freeglut.h>

#include<math.h>
#include <GL/glut.h>

class CameraObserver {
public:
    CameraObserver() : positionX(0.0f), positionY(0.0f), positionZ(5.0f),
        lookAtX(0.0f), lookAtY(0.0f), lookAtZ(0.0f),
        upX(0.0f), upY(1.0f), upZ(0.0f) {}

    void applyTransformations() {
        gluLookAt(positionX, positionY, positionZ, lookAtX, lookAtY, lookAtZ, upX, upY, upZ);
    }

    void setPosition(float x, float y, float z) {
        positionX = x;
        positionY = y;
        positionZ = z;
    }

    void setLookAt(float x, float y, float z) {
        lookAtX = x;
        lookAtY = y;
        lookAtZ = z;
    }

    void setUpVector(float x, float y, float z) {
        upX = x;
        upY = y;
        upZ = z;
    }

    void updateCamera() {
        gluLookAt(positionX, positionY, positionZ, lookAtX, lookAtY, lookAtZ, upX, upY, upZ);
    }

private:
    float positionX, positionY, positionZ;
    float lookAtX, lookAtY, lookAtZ;
    float upX, upY, upZ;
};

