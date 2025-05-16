#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader.h>

#include <iostream>
#include <limits>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// settings
const unsigned int SCR_WIDTH = 2560;
const unsigned int SCR_HEIGHT = 1880;

float infinite = 1000;

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
      100.000000, 110.000000, 100.000000, 100.000000, 110.000000, 100.000000, 0.707107, infinite, 0, 0,
      110.000000, 100.000000, 110.000000, 100.000000, 690.000000, 100.000000, 690.000000, 100.000000, 100, 100,
      690.000000, 100.000000, 700.000000, 100.000000, 700.000000, 110.000000, 0.707107, infinite, 110, 100,
      700.000000, 110.000000, 700.000000, 110.000000, 700.000000, 490.000000, 700.000000, 490.000000, 700, 100,
      700.000000, 490.000000, 700.000000, 500.000000, 690.000000, 500.000000, 0.707107, infinite, 700, 110,
      690.000000, 500.000000, 690.000000, 500.000000, 110.000000, 500.000000, 110.000000, 500.000000, 700, 500,
      110.000000, 500.000000, 100.000000, 500.000000, 100.000000, 490.000000, 0.707107, infinite, 690, 500,
      100.000000, 490.000000, 100.000000, 490.000000, 100.000000, 110.000000, 100.000000, 110.000000, 100, 500
  };



    // create VAO and VBO
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    unsigned int instanceVBO;
    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    // configure vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)0);
    glVertexAttribDivisor(0, 1);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(4 * sizeof(float)));
    glVertexAttribDivisor(1, 1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(8 * sizeof(float)));
    glVertexAttribDivisor(2, 1);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // render
        // ------
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        shader.use();
        shader.setVec4("sk_RTAdjust", 0.000781250012, -1, -0.00105596625, 1);
        shader.setVec3("utessControlArgs_S0", 1.5745033, 4, 5);
        shader.setVec4("uaffineMatrix_S0", 1.0, 0, 0, 1);
        shader.setVec2("utranslate_S0", 0, 0);

        glBindVertexArray(instanceVBO);
//        glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_SHORT, nullptr);
//        glDrawRangeElements(GL_TRIANGLES, 0, 15, 48, GL_UNSIGNED_SHORT, (void*)0);
        glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 28, 8);
//        glDrawArrays(GL_TRIANGLE_STRIP, 0, 28 * 8);

        glBindVertexArray(0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);

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
