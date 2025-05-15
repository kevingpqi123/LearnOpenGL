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
    Shader shader("10.7.instancing.vs", "10.7.instancing.fs");

//    float vertexData[] = {
//        94.500000, 94.500000, 15.500000, 15.500000, 0.066667, 0.066667, 0.200000, 0.200000,
//        110.000000, 94.500000, 0.000244, 15.500000, 0.066667, 0.066667, 0.200000, 0.200000,
//        690.000000, 94.500000, 0.000244, 15.500000, 0.066667, 0.066667, 0.200000, 0.200000,
//        705.500000, 94.500000, 0.000244, 15.500000, 0.066667, 0.066667, 0.200000, 0.200000,
//        94.500000, 110.000000, 15.500000, 0.000244, 0.066667, 0.066667, 0.200000, 0.200000,
//        110.000000, 110.000000, 0.000244, 0.000244, 0.066667, 0.066667, 0.200000, 0.200000,
//        690.000000, 110.000000, 0.000244, 0.000244, 0.066667, 0.066667, 0.200000, 0.200000,
//        705.500000, 110.000000, 0.000244, 0.000244, 0.066667, 0.066667, 0.200000, 0.200000,
//        94.500000, 490.000000, 15.500000, 0.000244, 0.066667, 0.066667, 0.200000, 0.200000,
//        110.000000, 490.000000, 0.000244, 0.000244, 0.066667, 0.066667, 0.200000, 0.200000,
//        690.000000, 490.000000, 0.000244, 0.000244, 0.066667, 0.066667, 0.200000, 0.200000,
//        705.500000, 490.000000, 0.000244, 0.000244, 0.066667, 0.066667, 0.200000, 0.200000,
//        94.500000, 505.500000, 15.500000, 15.500000, 0.066667, 0.066667, 0.200000, 0.200000,
//        110.000000, 505.500000, 0.000244, 15.500000, 0.066667, 0.066667, 0.200000, 0.200000,
//        690.000000, 505.500000, 0.000244, 15.500000, 0.066667, 0.066667, 0.200000, 0.200000,
//        705.500000, 505.500000, 0.000244, 15.500000, 0.066667, 0.066667, 0.200000, 0.200000
//    };
//    float vertexData[] = {
//        94.500000, 94.500000, 0.0, 15.500000, 15.500000, 0.066667, 0.066667, 0.200000, 0.200000,
//        110.000000, 94.500000, 0.0, 0.000244, 15.500000, 0.066667, 0.066667, 0.200000, 0.200000,
//        690.000000, 94.500000, 0.0, 0.000244, 15.500000, 0.066667, 0.066667, 0.200000, 0.200000,
//        705.500000, 94.500000, 0.0, 0.000244, 15.500000, 0.066667, 0.066667, 0.200000, 0.200000,
//        94.500000, 110.000000, 0.0, 15.500000, 0.000244, 0.066667, 0.066667, 0.200000, 0.200000,
//        110.000000, 110.000000, 0.0, 0.000244, 0.000244, 0.066667, 0.066667, 0.200000, 0.200000,
//        690.000000, 110.000000, 0.0, 0.000244, 0.000244, 0.066667, 0.066667, 0.200000, 0.200000,
//        705.500000, 110.000000, 0.0, 0.000244, 0.000244, 0.066667, 0.066667, 0.200000, 0.200000,
//        94.500000, 490.000000, 0.0, 15.500000, 0.000244, 0.066667, 0.066667, 0.200000, 0.200000,
//        110.000000, 490.000000, 0.0, 0.000244, 0.000244, 0.066667, 0.066667, 0.200000, 0.200000,
//        690.000000, 490.000000, 0.0, 0.000244, 0.000244, 0.066667, 0.066667, 0.200000, 0.200000,
//        705.500000, 490.000000, 0.0, 0.000244, 0.000244, 0.066667, 0.066667, 0.200000, 0.200000,
//        94.500000, 505.500000, 0.0, 15.500000, 15.500000, 0.066667, 0.066667, 0.200000, 0.200000,
//        110.000000, 505.500000, 0.0, 0.000244, 15.500000, 0.066667, 0.066667, 0.200000, 0.200000,
//        690.000000, 505.500000, 0.0, 0.000244, 15.500000, 0.066667, 0.066667, 0.200000, 0.200000,
//        705.500000, 505.500000, 0.0, 0.000244, 15.500000, 0.066667, 0.066667, 0.200000, 0.200000
//    };

    float vertexData[] = {
        94.500000, 94.500000, 1.0, 0.0, 0.0, 1.0, 15.500000, 15.500000, 0.066667, 0.066667, 0.200000, 0.200000,
        110.000000, 94.500000, 1.0, 0.0, 0.0, 1.0, 0.000244, 15.500000, 0.066667, 0.066667, 0.200000, 0.200000,
        690.000000, 94.500000, 1.0, 0.0, 0.0, 1.0, 0.000244, 15.500000, 0.066667, 0.066667, 0.200000, 0.200000,
        705.500000, 94.500000, 1.0, 0.0, 0.0, 1.0, 0.000244, 15.500000, 0.066667, 0.066667, 0.200000, 0.200000,
        94.500000, 110.000000, 1.0, 0.0, 0.0, 1.0, 15.500000, 0.000244, 0.066667, 0.066667, 0.200000, 0.200000,
        110.000000, 110.000000, 1.0, 0.0, 0.0, 1.0, 0.000244, 0.000244, 0.066667, 0.066667, 0.200000, 0.200000,
        690.000000, 110.000000, 1.0, 0.0, 0.0, 1.0, 0.000244, 0.000244, 0.066667, 0.066667, 0.200000, 0.200000,
        705.500000, 110.000000, 1.0, 0.0, 0.0, 1.0, 0.000244, 0.000244, 0.066667, 0.066667, 0.200000, 0.200000,
        94.500000, 490.000000, 1.0, 0.0, 0.0, 1.0, 15.500000, 0.000244, 0.066667, 0.066667, 0.200000, 0.200000,
        110.000000, 490.000000, 1.0, 0.0, 0.0, 1.0, 0.000244, 0.000244, 0.066667, 0.066667, 0.200000, 0.200000,
        690.000000, 490.000000, 1.0, 0.0, 0.0, 1.0, 0.000244, 0.000244, 0.066667, 0.066667, 0.200000, 0.200000,
        705.500000, 490.000000, 1.0, 0.0, 0.0, 1.0, 0.000244, 0.000244, 0.066667, 0.066667, 0.200000, 0.200000,
        94.500000, 505.500000, 1.0, 0.0, 0.0, 1.0, 15.500000, 15.500000, 0.066667, 0.066667, 0.200000, 0.200000,
        110.000000, 505.500000, 1.0, 0.0, 0.0, 1.0, 0.000244, 15.500000, 0.066667, 0.066667, 0.200000, 0.200000,
        690.000000, 505.500000, 1.0, 0.0, 0.0, 1.0, 0.000244, 15.500000, 0.066667, 0.066667, 0.200000, 0.200000,
        705.500000, 505.500000, 1.0, 0.0, 0.0, 1.0, 0.000244, 15.500000, 0.066667, 0.066667, 0.200000, 0.200000
    };

    static const uint16_t gOverstrokeRRectIndices[] = {
        // clang-format off
        // overstroke quads
        // we place this at the beginning so that we can skip these indices when rendering normally
//        16, 17, 19, 16, 19, 18,
//        19, 17, 23, 19, 23, 21,
//        21, 23, 22, 21, 22, 20,
//        22, 16, 18, 22, 18, 20,

        // corners
        0, 1, 5, 0, 5, 4,
        2, 3, 7, 2, 7, 6,
        8, 9, 13, 8, 13, 12,
        10, 11, 15, 10, 15, 14,

        // edges
        1, 2, 6, 1, 6, 5,
        4, 5, 9, 4, 9, 8,
        6, 7, 11, 6, 11, 10,
        9, 10, 14, 9, 14, 13,

        // center
        // we place this at the end so that we can ignore these indices when not rendering as filled
        5, 6, 10, 5, 10, 9,

    };

    const uint16_t* indices = gOverstrokeRRectIndices + 24;

//    float vertices[] = {
//        0.5f,  0.5f, 0.0f,  // top right
//        0.5f, -0.5f, 0.0f,  // bottom right
//        -0.5f, -0.5f, 0.0f,  // bottom left
//        -0.5f,  0.5f, 0.0f   // top left
//    };
//    unsigned int indices[] = {  // note that we start from 0!
//        0, 1, 3,  // first Triangle
//        1, 2, 3   // second Triangle
//    };


    // create VAO and VBO
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    // configure vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(8 * sizeof(float)));

//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(2 * sizeof(float)));
//    glEnableVertexAttribArray(2);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(3);
//    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(5 * sizeof(float)));


    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(2 * sizeof(float)));
//    glEnableVertexAttribArray(2);
//    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(4 * sizeof(float)));



    // 创建并绑定 EBO
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(gOverstrokeRRectIndices), gOverstrokeRRectIndices, GL_STATIC_DRAW);

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
        shader.setVec4("sk_RTAdjust", 0.000781250012f, -1.0f, -0.00105820107f, 1.0f);
        shader.setVec4("sk_Color", 1.0f, 0.0f, 0.0f, 1.0f);

        glBindVertexArray(VAO);
//        glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_SHORT, nullptr);
        glDrawRangeElements(GL_TRIANGLES, 0, 15, 48, GL_UNSIGNED_SHORT, (void*)0);

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

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

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
