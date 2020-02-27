/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
using namespace std;
#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#include<iostream>

static int slices = 16;
static int stacks = 16;

const int MAX_VERTICES = 1000000;
const int MAX_FACES = 1000000;
const int MAX_NORMALS = 1000000;

float vertices[MAX_VERTICES][3];
int vertex_count = 0;
int faces[MAX_FACES][6];
int face_count = 0;
float normals[MAX_NORMALS][3];
int normal_count = 0;
int moving, startx, starty;
GLfloat angle, angle2;
int usesnormals = 0;
float minx = -1, maxx = 1, miny = -1, maxy = 1, minz = -1, maxz = 1;
/* GLUT callback Handlers */
void mouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        moving = 1;
        startx = x;
        starty = y;
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        moving = 0;
    }
}
void motion(int x, int y)
{
    if (moving)
    {
        angle = angle + (x - startx);
        angle2 = angle2 + (y - starty);
        startx = x;
        starty = y;
        glutPostRedisplay();
    }
}
static void resize(int width, int height)
{
    const float ar = (float)width / (float)height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(minx * 1.5f, maxx * 1.5f, miny * 1.5f, maxy * 1.5f, minz * 1.5f, maxz * 1.5f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void emitVertex(float x, float y, float z)
{
    vertices[vertex_count][0] = x;
    vertices[vertex_count][1] = y;
    vertices[vertex_count++][2] = z;
}
void emitNormal(float vx, float vy, float vz)
{
    normals[normal_count][0] = vx;
    normals[normal_count][1] = vy;
    normals[normal_count++][2] = vz;
}
char** str_split(char* str, char delim, int* numSplits)
{
    char** ret;
    int retLen;
    char* c;

    if ((str == NULL) ||
        (delim == '\0'))
    {
        /* Either of those will cause problems */
        ret = NULL;
        retLen = -1;
    }
    else
    {
        retLen = 0;
        c = str;

        /* Pre-calculate number of elements */
        do
        {
            if (*c == delim)
            {
                retLen++;
            }

            c++;
        } while (*c != '\0');

        ret = (char**)malloc((retLen + 1) * sizeof(*ret));
        ret[retLen] = NULL;

        c = str;
        retLen = 1;
        ret[0] = str;

        do
        {
            if (*c == delim)
            {
                ret[retLen++] = &c[1];
                *c = '\0';
            }

            c++;
        } while (*c != '\0');
    }

    if (numSplits != NULL)
    {
        *numSplits = retLen;
    }

    return ret;
}

void emitFace1(char s1[16], char s2[16], char s3[16])
{
    int num1, num2, num3, num4, num5, num6;
    char** split1, ** split2, ** split3;

    split1 = str_split(s1, '/', &num1);
    split2 = str_split(s2, '/', &num2);
    split3 = str_split(s3, '/', &num3);
    if (num1 > 1) usesnormals = 1;
    if (num1 == 1)
    {
        num1 = atoi(split1[0]);
        num2 = atoi(split2[0]);
        num3 = atoi(split3[0]);
        // printf("%d %d %d\n",num1,num2,num3);
        faces[face_count][0] = num1 - 1;
        faces[face_count][1] = num2 - 1;
        faces[face_count++][2] = num3 - 1;
        usesnormals = 0;
    }
    else {
        num1 = atoi(split1[0]);
        num2 = atoi(split2[0]);
        num3 = atoi(split3[0]);
        num4 = atoi(split1[2]);
        num5 = atoi(split2[2]);
        num6 = atoi(split3[2]);
        //    printf("%d//%d %d//%d %d//%d\n",num1,num4,num2,num5,num3,num6);
        faces[face_count][0] = num1 - 1;
        faces[face_count][1] = num2 - 1;
        faces[face_count][2] = num3 - 1;
        faces[face_count][3] = num4 - 1;
        faces[face_count][4] = num5 - 1;
        faces[face_count++][5] = num6 - 1;

    }
}
void emitFace2(char s1[16], char s2[16], char s3[16], char s4[16])
{
    int num1, num2, num3, num4, num5, num6, num7, num8;
    char** split1, ** split2, ** split3, ** split4;

    split1 = str_split(s1, '/', &num1);
    split2 = str_split(s2, '/', &num2);
    split3 = str_split(s3, '/', &num3);
    split4 = str_split(s4, '/', &num4);
    if (num1 > 2) usesnormals = 1;
    num1 = atoi(split1[0]);
    num2 = atoi(split2[0]);
    num3 = atoi(split3[0]);
    num4 = atoi(split4[0]);

    num5 = atoi(split1[2]);
    num6 = atoi(split2[2]);
    num7 = atoi(split3[2]);
    num8 = atoi(split4[2]);
    faces[face_count][0] = num1 - 1;
    faces[face_count][1] = num2 - 1;
    faces[face_count][2] = num3 - 1;
    faces[face_count][3] = num5 - 1;
    faces[face_count][4] = num6 - 1;
    faces[face_count++][5] = num7 - 1;
    faces[face_count][0] = num1 - 1;
    faces[face_count][1] = num3 - 1;
    faces[face_count][2] = num4 - 1;
    faces[face_count][3] = num5 - 1;
    faces[face_count][4] = num7 - 1;
    faces[face_count++][5] = num8 - 1;




}
void removeSpaces(string& str)
{
    // n is length of the original string
    int n = str.length();

    // i points to next postion to be filled in
    // output string/ j points to next character
    // in the original string
    int i = 0, j = -1;

    // flag that sets to true is space is found
    bool spaceFound = false;

    // Handles leading spaces
    while (++j < n && str[j] == ' ');

    // read all characters of original string
    while (j < n)
    {
        // if current characters is non-space
        if (str[j] != ' ')
        {
            // remove preceding spaces before dot,
            // comma & question mark
            if ((str[j] == '.' || str[j] == ',' ||
                str[j] == '?') && i - 1 >= 0 &&
                str[i - 1] == ' ')
                str[i - 1] = str[j++];

            else
                // copy current character at index i
                // and increment both i and j
                str[i++] = str[j++];

            // set space flag to false when any
            // non-space character is found
            spaceFound = false;
        }
        // if current character is a space
        else if (str[j++] == ' ')
        {
            // If space is encountered for the first
            // time after a word, put one space in the
            // output and set space flag to true
            if (!spaceFound)
            {
                str[i++] = ' ';
                spaceFound = true;
            }
        }
    }

    // Remove trailing spaces
    if (i <= 1)
        str.erase(str.begin() + i, str.end());
    else
        str.erase(str.begin() + i - 1, str.end());
}

void loadObj(char* fname)
{
    FILE* fp;
    int read, num1, offset = 0;
    GLfloat x, y, z, vnx, vny, vnz;
    char ch;
    string linestr;
    char linestr1[60], * s1, * s2, * s3, * s4;
    char** split1;
    errno_t fp1 = fopen_s(&fp, "data/hbm.obj","w");
    if (!fp)
    {
        printf("can't open file %s\n", fname);
        exit(1);
    }




    while (!(feof(fp)))
    {
        fscanf_s(fp, "%[^\n]", linestr1);
        // printf("%s\n",linestr1);
        linestr = linestr1;
        removeSpaces(linestr);
        fscanf_s(fp, "\n");
        strcpy_s(linestr1, linestr.c_str());
        //printf("%s" , linestr);
        split1 = str_split(linestr1, ' ', &num1);
        //printf(" splits=> %s %s %s %s ",split1[0],split1[1],split1[2],split1[3]);
        //printf("Number of splits=%d\n",num1);

        if (num1 == 0)
        {

        }
        else if (split1[0][0] == 'v')
        {

            if (split1[0][1] == 'n')
            {
                if (num1 == 5)
                {
                    offset = 1;
                }
                else offset = 0;
                vnx = atof(split1[1 + offset]);
                vny = atof(split1[2 + offset]);
                vnz = atof(split1[3 + offset]);
                //printf("%f %f %f\n",vnx,vny,vnz);
                emitNormal(vnx, vny, vnz);
            }
            else {
                if (num1 == 5)
                {
                    offset = 1;
                    printf("TRUE\n");
                }
                else offset = 0;
                x = atof(split1[1 + offset]);
                y = atof(split1[2 + offset]);
                z = atof(split1[3 + offset]);
                if (x < minx) minx = x;
                if (x > maxx) maxx = x;
                if (y < miny) miny = y;
                if (y > maxy) maxy = y;
                if (z < minz) minz = z;
                if (z > maxz) maxz = z;
                // printf("%f %f %f\n",x,y,z);
                emitVertex(x, y, z);
            }
        }
        else if (!strcmp(split1[0], "s"))
        {
            //consume off in statement s off

        }

        else if (split1[0][0] == 'f')
        {
            s1 = split1[1];
            s2 = split1[2];
            s3 = split1[3];
            if (num1 == 5)
            {
                s4 = split1[4];
                //  printf("%s %s %s %s face2\n",s1,s2,s3,s4);
                emitFace2(s1, s2, s3, s4);
            }
            else
            {
                // printf("%s %s %s face1 ",s1,s2,s3);
                emitFace1(s1, s2, s3);
            }

        }
    }



    fclose(fp);
}

static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t * 90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    glLoadIdentity();
    glEnable(GL_SMOOTH);
    glShadeModel(GL_SMOOTH);
    glRotatef(angle, 0, 1, 0);
    glRotatef(angle2, 0, 0, 1);
    glPointSize(3.0);
    glBegin(GL_TRIANGLES);
    for (int i = 0;i < vertex_count;i++)
    {
        if (usesnormals == 1)
        {
            glNormal3f(normals[faces[i][3]][0], normals[faces[i][3]][1], normals[faces[i][3]][2]);
        }
        glVertex3f(vertices[faces[i][0]][0], vertices[faces[i][0]][1], vertices[faces[i][0]][2]);
        if (usesnormals == 1)
        {
            glNormal3f(normals[faces[i][4]][0], normals[faces[i][4]][1], normals[faces[i][4]][2]);
        }
        glVertex3f(vertices[faces[i][1]][0], vertices[faces[i][1]][1], vertices[faces[i][1]][2]);
        if (usesnormals == 1)
        {
            glNormal3f(normals[faces[i][5]][0], normals[faces[i][5]][1], normals[faces[i][5]][2]);
        }
        glVertex3f(vertices[faces[i][2]][0], vertices[faces[i][2]][1], vertices[faces[i][2]][2]);
    }
    glEnd();
    glFlush();
    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
    case 'q':
        exit(0);
        break;
    }

    glutPostRedisplay();
}



const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    char* name{};
    glutCreateWindow("GLUT Shapes");
    //   loadObj("data/teddy.obj");//replace elepham.obj withp orsche.obj or radar.obj or any other .obj to display it
    loadObj(name);
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    //   glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glClearColor(0, 0, 0, 0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    //
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    //
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    printf("%f %f %f %f %f %f", minx, maxx, miny, maxy, minz, maxz);
    glutMainLoop();

    return EXIT_SUCCESS;
}
