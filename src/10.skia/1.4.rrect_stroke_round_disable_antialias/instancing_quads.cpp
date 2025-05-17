#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader.h>

#include <iostream>
#include <limits>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 940;
float INF = INFINITY;

int main()
{
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // glfw window creation
  // --------------------
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // configure global opengl state
  // -----------------------------
  glEnable(GL_DEPTH_TEST);

  // build and compile shaders
  // -------------------------
  Shader shader("10.1.1.instancing.vs", "10.1.1.instancing.fs");

  float vertexData[] = {
      110.000000, 100.000000, 110.000000, 100.000000, 690.000000, 100.000000, 690.000000, 100.000000, 100, 100,
      690.000000, 100.000000, 700.000000, 100.000000, 700.000000, 110.000000, 0.707106769, INF, 110, 100,
      700.000000, 110.000000, 700.000000, 110.000000, 700.000000, 490.000000, 700.000000, 490.000000, 700, 100,
      700.000000, 490.000000, 700.000000, 500.000000, 690.000000, 500.000000, 0.707106769, INF, 700, 110,
      690.000000, 500.000000, 690.000000, 500.000000, 110.000000, 500.000000, 110.000000, 500.000000, 700, 500,
      110.000000, 500.000000, 100.000000, 500.000000, 100.000000, 490.000000, 0.707106769, INF, 690, 500,
      100.000000, 490.000000, 100.000000, 490.000000, 100.000000, 110.000000, 100.000000, 110.000000, 100, 500,
      100.000000, 110.000000, 100.000000, 100.000000, 110.000000, 100.000000, 0.707106769, INF, 100, 490,
  };

  // configure instanced array
  // -------------------------
  unsigned int buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  // set attribute pointers for matrix (4 times vec4)
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(4 * sizeof(float)));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(8 * sizeof(float)));

  glVertexAttribDivisor(0, 1);
  glVertexAttribDivisor(1, 1);
  glVertexAttribDivisor(2, 1);

  glBindVertexArray(0);

  // render loop
  // -----------
  while (!glfwWindowShouldClose(window))
  {

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw meteorites
    shader.use();
    shader.setVec4("sk_RTAdjust", 0.000781250012f, -1.0f, -0.00106382975f, 1.0f);
    shader.setVec3("utessControlArgs_S0", 1.5745, 4.00, 5.00);
    shader.setVec4("uaffineMatrix_S0", 1, 0, 0, 1.0f);
    shader.setVec2("utranslate_S0", 0, 0);
    shader.setVec4("ucolor_S0", 1.0f, 0.0f, 0.0f, 1.0f);

    glBindVertexArray(VAO);
//    glDrawArrays(GL_TRIANGLES, 0, 28);
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 28, 8);
    glBindVertexArray(0);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  // make sure the viewport matches the new window dimensions; note that width and
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}
