#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 945;

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
    Shader shader("1.2.instancing.vs", "1.2.instancing.fs");

    float vertexData[] = {
        22.524559, 323.047363, 25.000000, 310.000000, 25.366116, 311.919434, 22.524559, 323.047363, 25.366116,
        311.919434, 26.060093, 324.511841, 26.464462, 313.535522, 26.060093, 324.511841, 25.366116, 311.919434,
        26.060093, 324.511841, 26.464462, 313.535522, 28.080585, 314.633881, 26.060093, 324.511841, 28.080585,
        314.633881, 30.000000, 325.000000, 30.000000, 315.000000, 30.000000, 325.000000, 28.080585, 314.633881,
        30.000000, 325.000000, 30.000000, 315.000000, 510.000000, 325.000000, 510.000000, 315.000000, 510.000000,
        325.000000, 30.000000, 315.000000, 510.000000, 325.000000, 510.000000, 315.000000, 511.919403, 314.633881,
        510.000000, 325.000000, 511.919403, 314.633881, 513.535522, 313.535522, 510.000000, 325.000000, 513.535522,
        313.535522, 513.939880, 324.511841, 514.633911, 311.919403, 513.939880, 324.511841, 513.535522, 313.535522,
        513.939880, 324.511841, 514.633911, 311.919403, 515.000000, 310.000000, 515.000000, 310.000000, 515.000000,
        30.000000, 517.475403, 323.047363, 513.939880, 324.511841, 515.000000, 310.000000, 517.475403, 323.047363,
        15.000000, 310.000000, 15.000000, 30.000000, 15.488155, 313.939911, 15.488155, 26.060068, 15.488155,
        313.939911, 15.000000, 30.000000, 15.488155, 313.939911, 15.488155, 26.060068, 16.952623, 317.475433,
        16.952623, 22.524536, 16.952623, 317.475433, 15.488155, 26.060068, 16.952623, 317.475433, 16.952623,
        22.524536, 19.393402, 320.606567, 19.393402, 19.393402, 19.393402, 320.606567, 16.952623, 22.524536,
        19.393402, 320.606567, 19.393402, 19.393402, 22.524536, 16.952623, 19.393402, 320.606567, 22.524536,
        16.952623, 22.524559, 323.047363, 26.060070, 15.488155, 25.366116, 28.080578, 25.000000, 30.000000,
        25.000000, 30.000000, 25.000000, 310.000000, 22.524559, 323.047363, 25.000000, 30.000000, 22.524559,
        323.047363, 22.524536, 16.952623, 26.060070, 15.488155, 25.000000, 30.000000, 22.524536, 16.952623,
        25.366116, 28.080578, 26.060070, 15.488155, 26.464462, 26.464462, 30.000000, 15.000000, 30.000000,
        25.000000, 28.080578, 25.366116, 30.000000, 15.000000, 28.080578, 25.366116, 26.464462, 26.464462,
        30.000000, 15.000000, 26.464462, 26.464462, 26.060070, 15.488155, 30.000000, 25.000000, 30.000000,
        15.000000, 510.000000, 25.000000, 510.000000, 15.000000, 510.000000, 25.000000, 30.000000, 15.000000,
        510.000000, 25.000000, 510.000000, 15.000000, 511.919403, 25.366116, 513.939941, 15.488155, 513.535522,
        26.464462, 511.919403, 25.366116, 513.939941, 15.488155, 511.919403, 25.366116, 510.000000, 15.000000,
        513.535522, 26.464462, 513.939941, 15.488155, 514.633911, 28.080589, 517.475464, 16.952623, 517.475403,
        323.047363, 515.000000, 30.000000, 517.475464, 16.952623, 515.000000, 30.000000, 514.633911, 28.080589,
        517.475464, 16.952623, 514.633911, 28.080589, 513.939941, 15.488155, 517.475403, 323.047363, 517.475464,
        16.952623, 520.606567, 320.606567, 520.606567, 19.393402, 520.606567, 320.606567, 517.475464, 16.952623,
        520.606567, 320.606567, 520.606567, 19.393402, 523.047363, 317.475433, 523.047363, 22.524559, 523.047363,
        317.475433, 520.606567, 19.393402, 523.047363, 317.475433, 523.047363, 22.524559, 524.511841, 313.939911,
        524.511841, 26.060093, 524.511841, 313.939911, 523.047363, 22.524559, 524.511841, 313.939911, 524.511841,
        26.060093, 525.000000, 310.000000, 525.000000, 30.000000, 525.000000, 310.000000, 524.511841, 26.060093
    };

    // create VAO and VBO
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    // configure vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

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
        shader.setVec4("tgfx_RTAdjust", 0.00156250002, -1, 0.00211640215, -1);
        glm::mat3 const matrix(
            glm::vec3(1.0f, 0.0f, 80.0f),
            glm::vec3(0.0f, 1.0f, 80.0f),
            glm::vec3(0.0f, 0.0f, 1.0f));
        shader.setMat3("Matrix_P0", matrix);
        shader.setVec4("Color_P0", 1.0f, 0.0f, 0.0f, 1.0f);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 144);
        glBindVertexArray(0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
//    glDeleteVertexArrays(1, &quadVAO);
//    glDeleteBuffers(1, &quadVBO);

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
