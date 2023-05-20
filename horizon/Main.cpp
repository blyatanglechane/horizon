#include <iostream>
#include <GLFW/glfw3.h>

using namespace std;

void AlgorithmMidpointDisplacement(double y_1, double y_2, int deep)
{
    if (deep == 0)
    {
        glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-1, y_1);
        glVertex2f(1, y_2);
        glEnd();
    }
    else {
        // ����� ����� � ��������� ��� ��������� ������ ����� ����� ���� � �������� ������� ����� ����� � �����������
    }
}


int main()
{
    setlocale(LC_ALL, "Russian");
    /* ����� ������� ����������� ������� GLFW ���������� ������ ���� ����������������.
    ��� ������������� ���������, ����� ������� �������� �� ����������,
    ����������� �������� � ���������, �������������� ������ � ���������
    ����� ��������� �������������, ��������� �� ���������. */
    if (!glfwInit())
        return -1;


    GLFWwindow* window = glfwCreateWindow(900, 900, "Algorithm 'midpoint displacement'", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glViewport(0, 0, 900, 900);
    glClearColor(0.0f, 0.0f, 0.8f, 1.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // ��� ������� ������ ������� �������� � ������ �����
        double y_1, y_2, deep;
        cin >> y_1 >> y_2 >> deep;
        AlgorithmMidpointDisplacement(y_1, y_2, deep);
        glfwSwapBuffers(window);
        // ������������ ��� �������, ������������ � ���� - ����������� ���� ��� ������� ������
        glfwPollEvents();
    }
    glfwTerminate();
	return 0;
}