#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "glm/detail/type_mat.hpp"
#include "glm/gtc/matrix_transform.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "Engine/Src/Core/Camera.h"
#include "Engine/Src/Core/ShaderUtility.h"
#include <glm/gtx/io.hpp>

const char* glsl_version = "#version 130";

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){
    GLuint VertexShaderID = LoadShader(vertex_file_path, GL_VERTEX_SHADER);
    GLuint FragmentShaderID = LoadShader(fragment_file_path, GL_FRAGMENT_SHADER);

    GLint Result = GL_FALSE;
    int InfoLogLength;

    GLuint ProgramID = glCreateProgram();

    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);

    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}



// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


const int WIDTH = 640;
const int HEIGHT = 480;
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

Core::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(Core::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(Core::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(Core::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(Core::RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glewInit() != GLEW_OK)std::cerr << "Glew init fail";

	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	ImVec4 clear_color = ImColor(0x49,0xA6,0x95);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders( "../TransformVertexShader.vertexshader", "../ColorFragmentShader.fragmentshader" );


    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("../kot.png", &width, &height, &nrChannels, 0);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");
    // Get a handle for our "MVP" uniform
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");


    // Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 Projection = glm::perspective(glm::radians(camera.Zoom), 4.0f / 3.0f, 0.1f, 100.0f);

    glm::mat4 View       = glm::lookAt(
            glm::vec3(4,4,4), // Camera is at (4,3,-3), in World Space
            glm::vec3(0,0,0), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model      = glm::mat4(1.0f);

    static const GLfloat g_vertex_buffer_data[] = {
            1.f, 1.f, 1.f,
            -1.f, 1.f, 1.f,
            1.f, -1.f, 1.f,
            -1.f, -1.f, 1.f,

            1.f, 1.f, -1.f,
            -1.f, 1.f, -1.f,
            1.f, -1.f, -1.f,
            -1.f, -1.f, -1.f,
    };

    static const GLuint g_vertex_index_buffer_data[] = {
            //front
            0, 1, 2,
            3 ,1, 2,

            // back
            4, 5, 6,
            5, 6, 7,

            //top
            0, 1, 4,
            1, 4, 5,

            //bottom
            2, 3, 6,
            3, 6, 7,

            //left
            1, 3, 5,
            3, 5, 7,

            //right
            0, 2, 4,
            2, 4, 6
    };

    static const GLfloat g_uv_buffer_data[] = {
        1.f, 1.f,
        0.f, 1.f,
        1.f, 0.f,

        0.f, 0.f,
        0.f, 1.f,
        1.f, 0.f,

        0.f, 0.f,
        0.f, 1.f,
        1.f, 0.f,

        0.f, 0.f,
        0.f, 1.f,
        1.f, 0.f,

        0.f, 0.f,
        0.f, 1.f,
        1.f, 0.f,

        0.f, 0.f,
        0.f, 1.f,
        1.f, 0.f,

        0.f, 0.f,
        0.f, 1.f,
        1.f, 0.f,

        0.f, 0.f,
        0.f, 1.f,
        1.f, 0.f,

        0.f, 0.f,
        0.f, 1.f,
        1.f, 0.f,

        0.f, 0.f,
        0.f, 1.f,
        1.f, 0.f,

        0.f, 0.f,
        0.f, 1.f,
        1.f, 0.f,

        0.f, 0.f,
        0.f, 1.f,
        1.f, 0.f,
    };


    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint uvBuffer;
    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

    GLuint elementBuffer;
    glGenBuffers(1, &elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_vertex_index_buffer_data), g_vertex_index_buffer_data, GL_STATIC_DRAW);

    std::string inputfile = "../de_dust2-cs-map/source/de_dust2/de_dust2.obj";
    tinyobj::ObjReaderConfig reader_config;
    reader_config.mtl_search_path = "../de_dust2-cs-map/source/de_dust2/"; // Path to material files

    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(inputfile, reader_config)) {
        if (!reader.Error().empty()) {
            std::cerr << "TinyObjReader: " << reader.Error();
        }
        exit(1);
    }

    if (!reader.Warning().empty()) {
        std::cout << "TinyObjReader: " << reader.Warning();
    }

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();
    auto& materials = reader.GetMaterials();

    auto vertices = attrib.GetVertices();
    std::vector<float> scaledVertices;
    auto max = std::max_element(vertices.begin(), vertices.end());
    auto min = std::min_element(vertices.begin(), vertices.end());

    std::transform(vertices.begin(),
                   vertices.end(),
                   std::back_inserter(scaledVertices),
                   [&max, &min](float x) { return (1 - (( *max - x) / (*max - *min))) ; });


    GLuint shapesVertexBuffer;
    glGenBuffers(1, &shapesVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, shapesVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, scaledVertices.size() * sizeof (float), scaledVertices.data(), GL_STATIC_DRAW);

    std::vector<GLuint> elementsBuffers = {};
    for (auto shape: shapes) {
        auto shapeIndecesBufferData = shape.mesh.indices;
        std::vector<GLuint> shapeIndexBufferData;
        std::transform(shapeIndecesBufferData.begin(),
                       shapeIndecesBufferData.end(),
                       std::back_inserter(shapeIndexBufferData),
                       [](tinyobj::index_t x) { return x.vertex_index; });


        GLuint shapeElementBuffer;
        glGenBuffers(1, &shapeElementBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shapeElementBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, shapeIndexBufferData.size() * sizeof (GLuint), shapeIndexBufferData.data(), GL_STATIC_DRAW);

        elementsBuffers.push_back(shapeElementBuffer);
    }

    auto rotVec = glm::vec3(1.0f, 0,0);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		{
			static float f = 0.0f;
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}
        ImGui::Text("%s", camera.Debug().c_str());

		ImGui::Render();

        processInput(window);

        glm::mat4 Projection = glm::perspective(glm::radians(camera.Zoom), 4.0f / 3.0f, 0.1f, 100.0f);
        Model = glm::mat4();
        Model = scale(Model, glm::vec3(5,5,5));
        glm::mat4 MVP = Projection * camera.GetViewMatrix() * Model ; // Remember, matrix multiplication is the other way around
        // Clear the screen

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        glUseProgram(programID);

        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);


        for (int i = 1; i <= 1; i++) {
            // 1rst attribute buffer : vertices
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, shapesVertexBuffer);
            glVertexAttribPointer(
                    0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)0            // array buffer offset
            );


            // Index buffer
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsBuffers[i]);

            // Draw the triangles !
            glDrawElements(
                    GL_TRIANGLES,      // mode
                    shapes[i].mesh.indices.size(),    // count
                    GL_UNSIGNED_INT,   // type
                    (void*)0           // element array buffer offset
            );

            glDisableVertexAttribArray(0);
        }

//        glEnableVertexAttribArray(0);
//        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//        glVertexAttribPointer(
//                0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
//                3,                  // size
//                GL_FLOAT,           // type
//                GL_FALSE,           // normalized?
//                0,                  // stride
//                (void*)0            // array buffer offset
//        );
//
//
//        // Index buffer
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
//
//        // Draw the triangles !
//        glDrawElements(
//                GL_TRIANGLES,      // mode
//                36,    // count
//                GL_UNSIGNED_INT,   // type
//                (void*)0           // element array buffer offset
//        );
//
//        glDisableVertexAttribArray(0);


		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
    glDeleteBuffers(1, &vertexbuffer);


	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}