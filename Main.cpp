// Include necessary header files
#include <iostream> // for input/output operations (like printing to the console)
#include <glad/glad.h> // for loading OpenGL functions (might differ based on your setup)
#include <GLFW/glfw3.h> // for creating windows and handling user input

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


int main() {
    // Initialize GLFW 
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }

    // Set OpenGL context version (specifies which OpenGL features we want to use)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Use the core profile (without deprecated functions)

    GLfloat verticies[] =
    {
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
    };

    // Create a window with specific title, dimensions, and no context sharing
    GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Test", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window!" << std::endl;
        glfwTerminate(); // Clean up GLFW resources
        return -1;
    }

    // Make the created window the current context for drawing
    glfwMakeContextCurrent(window);

    // Load GLAD to cofigure OpenGl
    gladLoadGL();

    // setup viewport size
    glViewport(0, 0, 800, 800);


     
        // **Shader Creation and Compilation**

        // Create a vertex shader object
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Load the vertex shader source code
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

    // Compile the vertex shader
    glCompileShader(vertexShader);

    // Create a fragment shader object
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Load the fragment shader source code
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    // Compile the fragment shader
    glCompileShader(fragmentShader);

    // **Shader Program Creation and Linking**

    // Create a shader program object
    GLuint shaderProgram = glCreateProgram();

    // Attach the compiled vertex shader to the program
    glAttachShader(shaderProgram, vertexShader);

    // Attach the compiled fragment shader to the program
    glAttachShader(shaderProgram, fragmentShader);

    // Link the vertex and fragment shaders into a shader program
    glLinkProgram(shaderProgram);

    // **Shader Cleanup**

    // Delete the vertex shader object (no longer needed after linking)
    glDeleteShader(vertexShader);

    // Delete the fragment shader object (no longer needed after linking)
    glDeleteShader(fragmentShader);

    // **Vertex Array and Buffer Object Creation**

    // Generate a Vertex Array Object (VAO)
    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    // Generate a Vertex Buffer Object (VBO)
    GLuint VBO;
    glGenBuffers(1, &VBO);

    // **Vertex Data Binding**

    // Bind the VAO for subsequent vertex attribute configuration
    glBindVertexArray(VAO);

    // Bind the VBO to the GL_ARRAY_BUFFER target
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Upload vertex data to the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    // Configure the vertex attribute pointer for position data (location 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // Enable the vertex attribute array for location 0
    glEnableVertexAttribArray(0);

    // Unbind the VBO and VAO (optional, but good practice)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // set navy blue color
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

    // write color to buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap the front and back buffers (shows the rendered output)
    glfwSwapBuffers(window);

    // Main rendering loop - keeps the window open and responsive
    while (!glfwWindowShouldClose(window)) {
        // **Add your rendering code here** (e.g., clear the screen, draw objects)
        glClearColor(0.10f, 0.10f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);



        // Check for events like keyboard or mouse input
        glfwPollEvents();

   

    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // Clean up resources before terminating
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0; // Exit program successfully
}
