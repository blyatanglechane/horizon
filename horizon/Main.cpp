#include <iostream>
#include <GLFW/glfw3.h>
#include <random>
#include <conio.h>

using namespace std;

float randomFloat()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(-1.0f, 1.0f);
    return dis(gen);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    float scaleFactor = 1.0f - yoffset * 0.1f;
    glScalef(scaleFactor, scaleFactor, scaleFactor);
}

void AlgorithmMidpointDisplacement(double y_1, double y_2, double x_1, double x_2, int deep)
{
    if (deep == 0)
    {
        glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(x_1, y_1);
        glVertex2f(x_2, y_2);
        glEnd();
    }
    else 
    {
        double midX = (x_1 + x_2) / 2;
        double midY = (y_1 + y_2) / 2;
        // ����� ����� � ��������� ��� ��������� ������ ����� ����� ���� � �������� ������� ����� ����� � �����������
        double roughness = 0.6;

        double res = midY + roughness * abs(x_1 - x_2) * randomFloat();
        // ����� �����
        AlgorithmMidpointDisplacement(y_1, res, x_1, midX, deep - 1);
        // ������ �����
        AlgorithmMidpointDisplacement(res, y_2, midX, x_2, deep - 1);
        // 0 0 13
    }
}


int main()
{
    setlocale(LC_ALL, "Russian");
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(900, 900, "Algorithm 'midpoint displacement'", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    cout << "���������� y ��� ����� � ������ �����\n"
        << "����� �������� - �������\n";
    cout << "cin >> y_1 >> y_2 >> deep;\n";

    double y_1, y_2, deep;
    cin >> y_1 >> y_2 >> deep;

    glfwMakeContextCurrent(window);
    bool flag = true;
    glViewport(0, 0, 900, 900);
    glClearColor(0.0f, 0.0f, 0.8f, 1.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // ��� ������� ������ ������� �������� � ������ �����
        AlgorithmMidpointDisplacement(y_1, y_2, -1, 1, deep);
        glfwSetScrollCallback(window, scroll_callback);
        glfwSwapBuffers(window);

        // ������������ ��� �������, ������������ � ���� - ����������� ���� ��� ������� ������
        //cout << "������� ����� �������, ����� ������������� ����� ��������\n";
        //_getch();

        glfwPollEvents();
    }
    glfwTerminate();
	return 0;
}