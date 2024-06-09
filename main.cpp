#ifndef UNICODE
#define UNICODE
#endif
#include <Windows.h>
#include <math.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")


struct Color{
    double r,g,b;
};

/*---------------------Standard Cube--------------------------*/
void DrawCube(double size,Color front,Color back,Color left,Color right,bool borders, double borderThick = 0.0) {
    glBegin(GL_QUADS);
    // Front Face
    glColor3d(front.r,front.g,front.b); //RED
    glVertex3d(-size, -size, -size);
    glVertex3d(-size,  size, -size);
    glVertex3d( size,  size, -size);
    glVertex3d( size, -size, -size);

    // Back Face
    glColor3d(back.r, back.g, back.b);
    glVertex3d(-size, -size,  size);
    glVertex3d(-size,  size,  size);
    glVertex3d( size,  size,  size);
    glVertex3d( size, -size,  size);

    // Right face
    glColor3d(right.r, right.g, right.b);
    glVertex3d( size, -size, -size);
    glVertex3d( size,  size, -size);
    glVertex3d( size,  size,  size);
    glVertex3d( size, -size,  size);

    // Left Face
    glColor3d(left.r, left.g, left.b);
    glVertex3d(-size, -size, -size);
    glVertex3d(-size,  size, -size);
    glVertex3d(-size,  size,  size);
    glVertex3d(-size, -size,  size);


    // Top Face
    glColor3d(144.0/255.0,202.0/255.0,249.0/255.0); //BLUE
    glVertex3d(-size,  size, -size);
    glVertex3d(-size,  size,  size);
    glVertex3d( size,  size,  size);
    glVertex3d( size,  size, -size);

    // Bottom Face
    glColor3d(144.0/255.0,202.0/255.0,249.0/255.0); //PINK
    glVertex3d(-size, -size, -size);
    glVertex3d( size, -size, -size);
    glVertex3d( size, -size,  size);
    glVertex3d(-size, -size,  size);
    glEnd();

    if(borders) {
        glLineWidth(borderThick);
        glColor3d(0, 0, 0);
        glBegin(GL_LINE_LOOP);
        glVertex3d(-size, -size, -size);
        glVertex3d(-size, size, -size);
        glVertex3d(size, size, -size);
        glVertex3d(size, -size, -size);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex3d(-size, -size, size);
        glVertex3d(size, -size, size);
        glVertex3d(size, size, size);
        glVertex3d(-size, size, size);
        glEnd();

        glBegin(GL_LINES);
        // Connect the corners
        glVertex3d(-size, -size, -size);
        glVertex3d(-size, -size, size);

        glVertex3d(-size, size, -size);
        glVertex3d(-size, size, size);

        glVertex3d(size, size, -size);
        glVertex3d(size, size, size);

        glVertex3d(size, -size, -size);
        glVertex3d(size, -size, size);
        glEnd();
    }
}

/*----------------------Window Model-------------------------*/
void WindowLeft(double theta){
    double size = 0.02;
    double thickness = 0.018;
    Color color = {144.0/255.0,202.0/255.0,249.0/255.0};

    glPushMatrix();
    glTranslated(-size,0,0);
    glRotated(theta, 0, 1, 0);
    glScaled(1.0,2.5,thickness);
    glTranslated(size,0,0);
    DrawCube(size, color, {1,1,1},color,color, true,1.6);
    glPopMatrix();
}

void WindowRight(double theta){
    double size = 0.02;
    double thickness = 0.018;
    Color color = {144.0/255.0,202.0/255.0,249.0/255.0};

    glPushMatrix();
    glTranslated(size,0,0);
    glRotated(theta, 0, -1, 0);
    glScaled(1.0,2.5,thickness);
    glTranslated(-size,0,0);
    DrawCube(size,color, {1,1,1},color,color, true,1.6);
    glPopMatrix();
}

void DrawWindow(double theta, double x, double y, double z){
    //BackGround
    glPushMatrix();
    Color color ={179.0/255.0,178.0/255.0,179.0/255.0};
    glTranslated(x+0.02,y,z + 0.02); // increase z to go far
    glScaled(1.0,1.3,0.01);
    DrawCube(0.04,color,color,color,color,false);
    glPopMatrix();

    //Left Window
    glPushMatrix();
    glTranslated(x,y,z);
    WindowLeft(theta);
    glPopMatrix();

    //Right Window
    glPushMatrix();
    glTranslated(x+0.04,y,z);
    WindowRight(theta);
    glPopMatrix();
}

/*----------------------Door Model-------------------------*/
void DoorLogic(double theta){
    double size = 0.05;
    double thickness = 0.018;

    glPushMatrix();
    glTranslated(-size,0,0);
    glRotated(theta,0,1,0);
    glScaled(1.0,2.5,thickness);
    glTranslated(size,0,0);
    Color color = {113.0/255.0,103.0/255,103.0/255.0};
    DrawCube(size,color, {1,1,1},{1,1,1},{1,1,1}, true,1.6);

    // corridor اكره
    glTranslated(0.035,0.0001,-0.4);
    glScaled(0.003,0.005,0.003);
    color = {0,0,0};
    DrawCube(0.5,color,color,color,color, true,1.6);
    glPopMatrix();


}

void DrawDoor(double theta,double x, double y, double z){
    // BackGround
    glPushMatrix();
    Color color ={179.0/255.0,178.0/255.0,179.0/255.0};
    glTranslated(x,y,z + 0.02);
    glScaled(1.0,2.5,0.01);
    DrawCube(0.05,color,color,color,color,false);
    glPopMatrix();


    glPushMatrix();
    glTranslated(x,y,z);
    DoorLogic(theta);
    glPopMatrix();
}

/*----------------------Building Model-------------------------*/
void DrawBuilding(double thetaWindow, double thetaDoor){
    // Draw the first floor
    glPushMatrix();
    glTranslated(0,-0.2,0.5);
    glScaled(1.0,1.0,1.0);
    Color color = {255.0/255, 197.0/255, 39.0/255};
    DrawCube(0.3,color,color,color,color, true,2.0);
    glPopMatrix();

    // Draw the second floor
    glPushMatrix();
    glTranslated(0,0.4,0.5); // Adjust the y-coordinate to place the second floor on top of the first
    glScaled(1.0,1.0,1.0);
    DrawCube(0.3,color,color,color,color, true,2.0);
    glPopMatrix();

    // Draw the third floor (Roof)
    glPushMatrix();
    glTranslated(0,0.7,0.495); // Adjust the y-coordinate to place the third floor on top of the first
    glScaled(2.9,0.5,2.9);
    color = {76.0/255.0,76.0/255.0,76.0/255.0};
    DrawCube(0.1,color,color,color,color, true,2.0);
    glPopMatrix();

    // Left Window
    DrawWindow(thetaWindow,-0.19,0.55,0.18);
    // Right Window
    DrawWindow(thetaWindow,0.13,0.55,0.18);

    //LeftDown Window
    DrawWindow(thetaWindow,-0.19,0.25,0.18);
    //RightDown Window
    DrawWindow(thetaWindow,0.13,0.25,0.18);

    //LeftDown Window
    DrawWindow(thetaWindow,-0.19,-0.1,0.18);
    //RightDown Window
    DrawWindow(thetaWindow,0.13,-0.1,0.18);

    //Door
    DrawDoor(thetaDoor,-0.01,-0.36,0.18);

    // Floor under the building
    glPushMatrix();
    glTranslated(0,-4,0.5);
    glRotated(90,1,0,0);
    glScaled(3,4,-3);
    DrawCube(1,{1,1,1},{1,1,1},{1,1,1},{1,1,1},false);
    glPopMatrix();
}

/*---------------------Complex Shapes--------------------------*/
void DrawCylinder(double radius, double height, Color color) {
    GLUquadric* quadric = gluNewQuadric();
    glPushMatrix();
    glColor3d(color.r, color.g, color.b);
    gluCylinder(quadric, radius, radius, height, 32, 32);
    glPopMatrix();
    gluDeleteQuadric(quadric);
}

void DrawCone(double base, double height, Color color) {
    GLUquadric* quadric = gluNewQuadric();
    glPushMatrix();
    glColor3d(color.r, color.g, color.b);
    gluCylinder(quadric, base, 0.0, height, 32, 32);
    glPopMatrix();
    gluDeleteQuadric(quadric);
}
/*---------------------Bike Model--------------------------*/
void DrawTire() {
    DrawCylinder(0.1,0.05,{0.0f, 0.0f, 0.0f});
}

void DrawSpokes(){
    int numSpokes = 12; // Number of spokes
    for (int i = 0; i < numSpokes; i++) {
        float angle = i * 360.0 / numSpokes;
        glPushMatrix();
        glRotated(angle, 0, 0, 1); // Rotate to the correct angle for the spoke
        glBegin(GL_LINES);
        glVertex3f(0, 0, 0); // Center of the wheel
        glVertex3f(0, 0.1, 0); // Edge of the wheel
        glEnd();
        glPopMatrix();
    }
}

void DrawWheels(double thetaLeft, double thetaRight, bool isForward) {
    // Draw first wheel
    glPushMatrix();
    glTranslated(0.1, -0.6, -1.0);
    if(isForward)
        glRotated(-thetaLeft,0,0,1);
    else glRotated(thetaLeft,0,0,1);
    DrawTire();
    DrawSpokes();
    glPopMatrix();

    // Draw second wheel
    glPushMatrix();
    glTranslated(-0.5, -0.6, -1.0);
    if(isForward)
        glRotated(-thetaRight,0,0,1);
    else glRotated(thetaRight,0,0,1);
    DrawTire();
    DrawSpokes();
    glPopMatrix();
}

void DrawLineWheels(){
    glPushMatrix();
    glBegin(GL_LINE_LOOP); // line around the wheel
    glColor3d(250.0/255.0,222.0/255.0,222.0/255.0);
    glVertex3d(0.1,-0.6,-0.99);
    glVertex3d(0.1,-0.6,-0.99);
    glVertex3d(-0.01,-0.45,-0.99);
    glVertex3d(-0.01,-0.45,-0.99);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_LINE_LOOP); // line around the wheel
    glColor3d(250.0/255.0,222.0/255.0,222.0/255.0);
    glVertex3d(-0.5,-0.6,-0.99);
    glVertex3d(-0.5,-0.6,-0.99);
    glVertex3d(-0.41,-0.45,-0.99);
    glVertex3d(-0.41,-0.45,-0.99);
    glEnd();
    glPopMatrix();
}

void DrawCore(){
    // Connect two wheels
    glPushMatrix();
    glTranslated(-0.215,-0.45,-1.0);
    glScaled(1.12,0.1,0.1);
    Color color = {0,0,0};
    DrawCube(0.2,color,color,color,color,true,2.0);
    glPopMatrix();

    // Chair Back
    glPushMatrix();
    color = {250.0/255.0,222.0/255.0,222.0/255.0};
    glTranslated(-0.41,-0.31,-1.0);
    glScaled(0.1,0.6,0.1);
    DrawCube(0.2,color,color,color,color,true,2.0);
    glPopMatrix();

    // Chair Bottom
    glPushMatrix();
    glTranslated(-0.32,-0.41,-1.0);
    glScaled(0.5,0.1,0.1);
    DrawCube(0.2,color,color,color,color,true,2.0);
    glPopMatrix();

    //Handler
    glPushMatrix();
    glTranslated(-0.01,-0.37,-1.0);
    glScaled(0.03,0.4,0.1);
    DrawCube(0.2,color,color,color,color,true,2.0);
    glPopMatrix();

    //Handler2
    glPushMatrix();
    glTranslated(-0.01,-0.29,-1.0);
    glRotated(75,0,0,1);
    glScaled(0.01,0.4,0.1);
    DrawCube(0.2,color,color,color,color,true,2.0);
    glPopMatrix();
}

/*--------------------Rotate Window and Door---------------------------*/
// use to rotate the window and door for half a rotation
void rotate(double& angle, double& rotationSpeed, bool& clockWise){
    if (clockWise) {
        angle += rotationSpeed;
        if (angle >= 180.0f){ // Reached a half rotation
            rotationSpeed = 0.0; // stop the rotation stay open
        }
    } else {
        angle -= rotationSpeed;
        if (angle <= 0.0f){ // Reached original position
            rotationSpeed = 0.0; // stop the rotation stay closed
        }
    }
}


/*-------------------Projection Model----------------------------*/
static double fov = 50;
void setupProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, 1.0, 1.0, 100.0);
}

/*-------------------Camera Model----------------------------*/
static double cameraHeight = 0.0;
static double cameraAngle = 0.0;
static double cameraDistance = -2.5;
void setupCamera() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    double x = cameraDistance * cos(cameraAngle);
    double z = cameraDistance * sin(cameraAngle);
    gluLookAt(x, cameraHeight, z,  // Camera position (x,y,z)
              0.0, 0.3, 0.3,  // Look at point (x,y,z)
              0.0, 1.0, 0.0); // Up direction (x,y,z)
}

/*-------------------Tree Model----------------------------*/
void DrawTree(double trunkRadius, double trunkHeight, double foliageBase, double foliageHeight) {
    Color trunkColor = {0.545, 0.271, 0.075};  // Brown color for the trunk
    Color foliageColor = {0.0, 0.5, 0.0};     // Green color for the foliage

    glPushMatrix();
    // Draw the trunk
    DrawCylinder(trunkRadius, trunkHeight, trunkColor);

    // Draw the foliage
    glTranslated(0.0, 0.0, trunkHeight);
    DrawCone(foliageBase, foliageHeight, foliageColor);
    glPopMatrix();
}


LRESULT WINAPI WndProc(HWND hwnd, UINT m, WPARAM wp, LPARAM lp)
{
    static PIXELFORMATDESCRIPTOR pfd = {
            sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd
            1,                     // version number
            PFD_DRAW_TO_WINDOW |   // support window
            PFD_SUPPORT_OPENGL |   // support OpenGL
            PFD_DOUBLEBUFFER,      // double buffered
            PFD_TYPE_RGBA,         // RGBA type
            24,                    // 24-bit color depth
            0, 0, 0, 0, 0, 0,      // color bits ignored
            0,                     // no alpha buffer
            0,                     // shift bit ignored
            0,                     // no accumulation buffer
            0, 0, 0, 0,            // accum bits ignored
            32,                    // 32-bit z-buffer
            0,                     // no stencil buffer
            0,                     // no auxiliary buffer
            PFD_MAIN_PLANE,        // main layer
            0,                     // reserved
            0, 0, 0                // layer masks ignored
    };
    static HDC hdc;
    static HGLRC hgl;
    int  iPixelFormat,w,h;


    // angle to handle the rotation of Wheels
    static double wheelsSpeedLeft = 0.0;
    static double wheelsSpeedRight = 0.0;
    static double thetaWheelsLeft = 0.0;
    static double thetaWheelsRight = 0.0;
    // to handle whether the wheel will rotate forward or backward
    static bool isForward = true;

    // Handle Window angle and rotation
    static double angleClockWiseWindow= 0.0;
    static double rotationSpeedClockWindow = 0.0;
    static bool rotateClockwiseWindow = true;

    // handle door angles and rotation
    static double angleClockWiseDoor = 0.0;
    static double rotationSpeedClockDoor = 0.0;
    static bool rotateClockwiseDoor = true;

    // The Angle that the Bike Rotate With
    static double thetaBike = 0.0;
    // bike position change from forward to circular
    static double BikePosition = 0.0;
    // the speed of Bike in Circular Path
    static double bikeRotationSpeed = 0.0;
    // the speed of Bike in forward backward path
    static double bikeForwardSpeed = 0.0;
    // to Draw the paths circle or forward.
    static bool moveCircular = false;
    static bool moveForward = true;

    switch (m)
    {
        case WM_CREATE:
            hdc = GetDC(hwnd);
            iPixelFormat = ChoosePixelFormat(hdc, &pfd);
            SetPixelFormat(hdc, iPixelFormat, &pfd);
            hgl=wglCreateContext(hdc);
            wglMakeCurrent(hdc,hgl);
            glClearColor(146.0/255.0, 227.0/255.0,169.0/255.0, 0);
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
            SetTimer(hwnd,1,10,NULL);
            InvalidateRect(hwnd,NULL,FALSE);
            break;
        case WM_SIZE:
            w = LOWORD(lp);
            h = HIWORD(lp);
            glViewport(0, 0, w, h);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glFlush();
            SwapBuffers(hdc);
            break;
        case WM_RBUTTONDOWN:
            moveForward = false;
            moveCircular = true;
            bikeRotationSpeed = 0.0;
            break;
        case WM_LBUTTONDOWN:
            // wheels moves forward, stop the BikePosition-axis move and return bike to original
            // position
            moveForward = false;
            moveCircular = true;
            isForward = true;
            bikeForwardSpeed = 0.0;
            BikePosition = 0.0;
            bikeRotationSpeed = 1.2;
            break;
        case WM_KEYDOWN:
            switch (wp) {
                case VK_LEFT:
                    cameraAngle += 0.05;
                    break;
                case VK_RIGHT:
                    cameraAngle -= 0.05;
                    break;
                case VK_UP:
                    cameraHeight += 0.05;
                    break;
                case VK_DOWN:
                    cameraHeight -= 0.05;
                    break;
                case 'S':
                    fov += 1;
                    break;
                case 'W':
                    fov -= 1;
                    break;
                case 'F':
                    moveForward = true;
                    moveCircular = false;
                    if(bikeForwardSpeed != 0.01) {
                        thetaBike = 0.0;
                        isForward = true;
                        bikeForwardSpeed = 0.01;
                    }
                    else bikeForwardSpeed = 0.0;
                    break;

                case 'B':
                    moveForward = true;
                    moveCircular = false;
                    if(bikeForwardSpeed != -0.01) {
                        thetaBike = 0.0;
                        isForward = false;
                        bikeForwardSpeed = -0.01;
                    }
                    else bikeForwardSpeed = 0.0;
                    break;
                case 'L':
                    if(wheelsSpeedLeft != 1.1)
                        wheelsSpeedLeft = 1.1;
                    else wheelsSpeedLeft = 0.0;
                    break;
                case 'R':
                    if(wheelsSpeedRight != 1.1)
                        wheelsSpeedRight = 1.1;
                    else wheelsSpeedRight = 0.0;
                    break;
                case 'C':
                case 'O':
                    // Capital O C Window
                    if(GetKeyState(VK_SHIFT) & 0x8000 ||GetKeyState(VK_CAPITAL) & 1){
                        rotationSpeedClockWindow = 2.0;
                        switch (wp) {
                            case 'O':
                                if(angleClockWiseWindow < 180.0f){ // Window closed so open
                                    angleClockWiseWindow = 0.0f;
                                    rotateClockwiseWindow = true;
                                }
                                else angleClockWiseWindow = 180.0f;
                                break;
                            case 'C':
                                if(angleClockWiseWindow > 0.0f){ // Window open so close it
                                    angleClockWiseWindow = 180.0f;
                                    rotateClockwiseWindow = false;
                                }
                                else angleClockWiseWindow = 0.0f;
                                break;
                        }
                    }
                    // Small o c Door
                    else{
                        rotationSpeedClockDoor = 2.0;
                        switch (wp) {
                            case 'O':
                                if(angleClockWiseDoor < 180.0f){ // door closed so open
                                    angleClockWiseDoor = 0.0f;
                                    rotateClockwiseDoor = true;
                                    }
                                else angleClockWiseDoor = 180.0f;
                                break;
                            case 'C':
                                if(angleClockWiseDoor > 0.0f){ // door open so close it
                                    angleClockWiseDoor = 180.0f;
                                    rotateClockwiseDoor = false;
                                    }
                                else angleClockWiseDoor = 0.0f;
                                break;
                        }
                    }
                    break;
            }
        break;
        case WM_TIMER:
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);
            glFlush();

            setupProjection(); // to change FOV
            setupCamera();


            DrawBuilding(angleClockWiseWindow, angleClockWiseDoor);

            glLoadIdentity();
            setupCamera();

            glPushMatrix();
            glTranslated(BikePosition, 0.12, 0.5);
            glRotated(thetaBike,0,-1,0);
            glTranslated(0.0,0.0,-0.40); // decrease z increase radius

            DrawWheels(thetaWheelsLeft, thetaWheelsRight, isForward);
            DrawLineWheels();
            DrawCore();
            glPopMatrix();

            thetaBike += bikeRotationSpeed;
            thetaWheelsLeft += wheelsSpeedLeft;
            thetaWheelsRight += wheelsSpeedRight;
            BikePosition += bikeForwardSpeed;
            // if the bike move out of the floor return again
            if(BikePosition >= 3.0) BikePosition = -3.0;
            if(BikePosition < -3.0) BikePosition = 3.0;

            if(moveCircular){
                // Circular Path
                glPushMatrix();
                glTranslated(0.01,-1.6,0.45);
                glColor3d(0.5,0.5,0.5);
                glBegin(GL_QUAD_STRIP);
                for (int i = 0; i <= 360; i++) {
                    double degInRad = i * M_PI / 180.0;
                    glVertex3d(cos(degInRad) * 1.0, 1, sin(degInRad) * 1.0);  // Inner edge of the street
                    glVertex3d(cos(degInRad) * 1.8, 1, sin(degInRad) * 1.8);  // Outer edge of the street
                }
                glEnd();
                glPopMatrix();

                //Line in Street
                glPushMatrix();
                glTranslated(0.01,-1.58,0.45);
                glColor3d(1,1,1);
                glBegin(GL_LINE_LOOP);
                for (int i = 0; i <= 360; i++) {
                    double degInRad = i * M_PI / 180.0;
                    glVertex3d(cos(degInRad) * 1.4, 1, sin(degInRad) * 1.4);  // Inner edge of the street
                }
                glEnd();
                glPopMatrix();
            }
            // Straight street to move forward and backward
            else if(moveForward){
                // Draw the street surface
                glPushMatrix();
                glColor3d(0.5, 0.5, 0.5);
                glScaled(1,1,3);
                glTranslated(0,0,0.55);
                glBegin(GL_QUADS);
                glVertex3d(-3.0, -0.6, -0.7);
                glVertex3d(3.0, -0.6, -0.7);
                glVertex3d(3.0, -0.6, -1.0);
                glVertex3d(-3.0, -0.6, -1.0);
                glEnd();
                glPopMatrix();

                // Draw the street lines
                glPushMatrix();
                glScaled(1.0, 0.1, 0.1);
                glTranslated(0, -5.2, -8.0); // Use the loop variable to translate each line along the path
                glColor3d(1, 1, 1); // Set color to red
                glBegin(GL_QUADS);
                glVertex3d(-3.0, -0.6, -0.7);
                glVertex3d(3.0, -0.6, -0.7);
                glVertex3d(3.0, -0.6, -1.0);
                glVertex3d(-3.0, -0.6, -1.0);
                glEnd();
                glPopMatrix();
            }

            // Draw trees
            glPushMatrix();
            glTranslated(-0.5, -0.6, -0.01);
            glRotated(180.0f,0,1,1);
            DrawTree(0.05, 0.3, 0.15, 0.4);
            glPopMatrix();

            glPushMatrix();
            glTranslated(0.5, -0.6, -0.01);
            glRotated(180.0f,0,1,1);
            DrawTree(0.05, 0.3, 0.15, 0.4);
            glPopMatrix();

            // Update the angleClockWise  windows
            rotate(angleClockWiseWindow,rotationSpeedClockWindow,rotateClockwiseWindow);
            rotate(angleClockWiseDoor,rotationSpeedClockDoor,rotateClockwiseDoor);

            SwapBuffers(hdc);
            break;
        case WM_DESTROY:
            wglMakeCurrent(NULL, NULL);
            wglDeleteContext(hgl);
            ReleaseDC(hwnd, hdc);
            PostQuitMessage(0);
            break;
        default: return DefWindowProc(hwnd, m, wp, lp);
    }
    return 0;
}

int APIENTRY WinMain(HINSTANCE hi, HINSTANCE pi, LPSTR c, int ns)
{
    WNDCLASS wc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.hInstance = hi;
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = L"MyClass";
    wc.lpszMenuName = NULL;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&wc);
    HWND hwnd = CreateWindow(L"MyClass", L"Hello World", WS_OVERLAPPEDWINDOW, 0, 0, 600, 400, NULL, NULL, hi, 0);
    ShowWindow(hwnd, ns);
    UpdateWindow(hwnd);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
