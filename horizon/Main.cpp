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
        // найдём центр и придумаем ему рандомную высоту после этого уйдём в рекурсию передав левую точку и центральную
    }
}


int main()
{
    setlocale(LC_ALL, "Russian");
    /* Перед вызовом большинства функций GLFW библиотека должна быть инициализирована.
    Эта инициализация проверяет, какие функции доступны на компьютере,
    перечисляет мониторы и джойстики, инициализирует таймер и выполняет
    любую требуемую инициализацию, зависящую от платформы. */
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

        // Эта функция меняет местами передний и задний буфер
        double y_1, y_2, deep;
        cin >> y_1 >> y_2 >> deep;
        AlgorithmMidpointDisplacement(y_1, y_2, deep);
        glfwSwapBuffers(window);
        // обрабатывает все события, произошедшие в окне - перемещение мыши или нажатие клавиш
        glfwPollEvents();
    }
    glfwTerminate();
	return 0;
}