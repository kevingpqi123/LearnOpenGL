#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// 窗口大小
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// 顶点着色器
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 aPos;       // 顶点位置
layout (location = 1) in vec3 aColor;    // 实例化颜色

out vec3 instanceColor; // 输出到片段着色器

void main()
{
    gl_Position = vec4(aPos, 0.0, 1.0); // 使用顶点位置
    instanceColor = aColor;            // 传递颜色数据
}
)";

// 片段着色器
const char* fragmentShaderSource = R"(
#version 330 core
in vec3 instanceColor; // 从顶点着色器接收的颜色

out vec4 FragColor;

void main()
{
    FragColor = vec4(instanceColor, 1.0); // 使用实例化颜色
}
)";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

int main() {
  // 初始化 GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // 创建窗口
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Instancing Example", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // 初始化 GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // 编译着色器
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  float instanceVertexData[] = {
      // 实例 1 的三角形
      -0.1f, -0.1f, // 左下角
      0.1f, -0.1f, // 右下角
      0.0f,  0.1f, // 顶部

      // 实例 2 的三角形
      -0.2f, -0.2f, // 左下角
      0.2f, -0.2f, // 右下角
      0.0f,  0.2f, // 顶部

      // 实例 3 的三角形
      -0.3f, -0.3f, // 左下角
      0.3f, -0.3f, // 右下角
      0.0f,  0.3f  // 顶部
  };

  // 创建 VAO 和 VBO
  unsigned int VAO, instanceVBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &instanceVBO);

  glBindVertexArray(VAO);

  // 绑定实例化数据
  glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(instanceVertexData), instanceVertexData, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribDivisor(0, 1); // 设置为实例化属性

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // 渲染循环
  while (!glfwWindowShouldClose(window)) {
    // 清屏
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 绘制
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 3);
    glBindVertexArray(0);

    // 交换缓冲区
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // 清理资源
  glDeleteVertexArrays(1, &VAO);
//  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &instanceVBO);
  glDeleteProgram(shaderProgram);

  glfwTerminate();
  return 0;
}