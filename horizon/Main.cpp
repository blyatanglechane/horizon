#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>
#include <random>
#include <conio.h>

using namespace std;

struct Point
{
    double x;
    double y;
};

float randomFloat()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(-1.0f, 1.0f);
    return dis(gen);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    static double lastX = xpos, lastY = ypos;
    static bool isDragging = false;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        if (!isDragging)
        {
            isDragging = true;
            lastX = xpos;
            lastY = ypos;
        }
        else
        {
            float deltaX = (float)(xpos - lastX) / 600.0f;
            float deltaY = (float)(ypos - lastY) / 600.0f;
            glTranslatef(deltaX, -deltaY, 0.0f);
            lastX = xpos;
            lastY = ypos;
        }
    }
    else
    {
        isDragging = false;
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    double scaleFactor = 1.1;
    if (yoffset > 0)
    {
        glScalef(scaleFactor, scaleFactor, 1.0);
    }
    else
    {
        glScalef(1.0 / scaleFactor, 1.0 / scaleFactor, 1.0);
    }
}

void AlgorithmMidpointDisplacement(double x_1, double y_1, double x_2, double y_2, int deep, double roughness, vector<Point>& points)
{
    if (deep == 0)
    {
        points.push_back({ x_1, y_1 });
        points.push_back({ x_2, y_2 });
    }
    else
    {
        double midX = (x_1 + x_2) / 2;
        double midY = (y_1 + y_2) / 2;
        // Find the center and assign a random height to it, then recursively call the function with the left point and center

        double res = midY + roughness * abs(x_1 - x_2) * randomFloat();
        // Left part
        AlgorithmMidpointDisplacement(x_1, y_1, midX, res, deep - 1, roughness, points);
        // Right part
        AlgorithmMidpointDisplacement(midX, res, x_2, y_2, deep - 1, roughness, points);
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

    cout << "Координаты y для левой и правой точки\n"
        << "затем значение - глубина\n";
    cout << "cin >> x_1 >> y_1 >> x_2 >> y_2 >> deep >> roughness;\n";
    glfwSetCursorPosCallback(window, cursor_position_callback);
    double x_1, y_1, x_2, y_2, deep, roughness;
    cin >> x_1 >> y_1 >> x_2 >> y_2 >> deep >> roughness;
    glfwMakeContextCurrent(window);
    glClearColor(0.0f, 0.0f, 0.8f, 1.0f);

    // Register the scroll callback function
    glfwSetScrollCallback(window, scroll_callback);

    vector<Point> points;
    AlgorithmMidpointDisplacement(x_1, y_1, x_2, y_2, deep, roughness, points);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);
        for (const auto& point : points)
        {
            glVertex2f(point.x, point.y);
        }
        glEnd();
        glfwSwapBuffers(window);
        glfwSetScrollCallback(window, scroll_callback);
        glfwSetCursorPosCallback(window, cursor_position_callback);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

// -1 0 1 0 10 0.6