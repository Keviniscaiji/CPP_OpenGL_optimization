/*
Author: Kaiwen Gong
Class: ECE6122
Last Date Modified: 12/04/2024
Description:
Implementing required functions
*/

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <random>
#include <thread>
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>

void moveAndDetectCollisionAndRotate(GLfloat &x, GLfloat &y, GLfloat &z, GLfloat &dirx, GLfloat &diry, GLfloat &dirz,
                                     GLfloat &angle);
float getRandomFloat(float min, float max);
void detectAndRespondCollision(GLfloat& x1, GLfloat& y1, GLfloat& z1, GLfloat& dirx1, GLfloat& diry1, GLfloat& dirz1,
                               GLfloat& x2, GLfloat& y2, GLfloat& z2, GLfloat& dirx2, GLfloat& diry2, GLfloat& dirz2);



int main( void )
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow( 1024, 768, "Tutorial 09 - Rendering several models", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders( "StandardShading.vertexshader", "StandardShading.fragmentshader" );

    // Get a handle for our "MVP" uniform

    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
    GLuint ModelMatrixID = glGetUniformLocation(programID, "M");

    // Load the texture
    GLuint Texture1 = loadDDS("Background.DDS");
    GLuint Texture2 = loadDDS("uvmap.DDS");
    
    // Get a handle for our "myTextureSampler" uniform
    GLuint TextureID1  = glGetUniformLocation(programID, "myTextureSampler1");
    GLuint TextureID2  = glGetUniformLocation(programID, "myTextureSampler2");
    
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture1);
    glUniform1i(TextureID1, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, Texture2);
    glUniform1i(TextureID2, 1);

    
    
    // Read our .obj file
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    
    bool res = loadOBJ("suzanne.obj", vertices, uvs, normals);

    std::vector<unsigned short> indices;
    std::vector<glm::vec3> indexed_vertices;
    std::vector<glm::vec2> indexed_uvs;
    std::vector<glm::vec3> indexed_normals;
    indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);

    // Load it into a VBO

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

    GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

    GLuint normalbuffer;
    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

    // Generate a buffer for the indices as well
    GLuint elementbuffer;
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);

    // Get a handle for our "LightPosition" uniform
    glUseProgram(programID);
    
    GLuint LightID1 = glGetUniformLocation(programID, "LightPosition_worldspace1");
    GLuint LightID2 = glGetUniformLocation(programID, "LightPosition_worldspace2");
    GLuint LightID3 = glGetUniformLocation(programID, "LightPosition_worldspace3");
    GLuint LightID4 = glGetUniformLocation(programID, "LightPosition_worldspace4");
    // For speed computation
    double lastTime = glfwGetTime();
    
    
    int nbFrames = 0;
    GLint onlyAmbi;
    GLint move = 0;
    
    GLfloat x1 = 1.0f,x2 = -1.0f,x3 = 0.0f, x4 = 0.0f;
    GLfloat y1 = 0.0f,y2 = 0.0f,y3 = 1.0f, y4 = -1.0f;
    GLfloat z1 = 0.0f,z2 = 0.0f,z3 = 0.0f, z4 = 0.0f;
    GLfloat angle1 = 0.0f,angle2 = 0.0f,angle3 = 0.0f, angle4 = 0.0f;
    
    
    GLfloat dirx1 = getRandomFloat(-0.1f, 0.1f);
    GLfloat dirx2 = getRandomFloat(-0.1f, 0.1f);
    GLfloat dirx3 = getRandomFloat(-0.1f, 0.1f);
    GLfloat dirx4 = getRandomFloat(-0.1f, 0.1f);

    GLfloat diry1 = getRandomFloat(-0.1f, 0.1f);
    GLfloat diry2 = getRandomFloat(-0.1f, 0.1f);
    GLfloat diry3 = getRandomFloat(-0.1f, 0.1f);
    GLfloat diry4 = getRandomFloat(-0.1f, 0.1f);

    GLfloat dirz1 = getRandomFloat(-0.1f, 0.1f);
    GLfloat dirz2 = getRandomFloat(-0.1f, 0.1f);
    GLfloat dirz3 = getRandomFloat(-0.1f, 0.1f);
    GLfloat dirz4 = getRandomFloat(-0.1f, 0.1f);

    // Define vertices for a square
    static const GLfloat g_vertex_buffer_data[] = {
        // Vertex positions     // Texture coordinates
        -10.0f, -10.0f, -10.0f,
         10.0f, -10.0f, -10.0f,
         10.0f,  10.0f, -10.0f,
        -10.0f,  10.0f, -10.0f    };

    // You also need to define indices for the rectangle (two triangles)



    
    static const GLfloat g_vertex_rect_data[] = {
      50.0f, 50.0f, -10.0f,
      50.0f, -50.0f, -10.0f,
      -50.0f, -50.0f, -10.0f,
      -50.0f, 50.0f, -10.0f
    };

    static const GLushort square_indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // Define UVs for the square
    static const GLfloat g_uv_buffer_data[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
    };

    // Define indices for the square (to render it as 2 triangles)
    double startTime = glfwGetTime();
    float moveX = 0;
    
    
    
    
    
    
    ////////////////////////////////////////////// code for animation ///////////////////////////////////////////////////
    do{
        double currentTime = glfwGetTime();
        if(move == 0){
            currentTime = startTime;
        }
        float deltaTime = float(currentTime - startTime);
        if(glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
            if(move == 1){
                move = 0;
            }else{
                move = 1;
            }
        }
                // Measure speed
        nbFrames++;
        if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1sec ago
            // printf and reset
            printf("%f ms/frame\n", 1000.0/double(nbFrames));
            nbFrames = 0;
            lastTime += 1.0;
        }

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // Compute the MVP matrix from keyboard and mouse input
        computeMatricesFromInputs();
        glm::mat4 ProjectionMatrix = getProjectionMatrix();
        glm::mat4 ViewMatrix = getViewMatrix();
        
        
        ////// Start of the rendering of the first object //////
        
        // Use our shader
        glUseProgram(programID);
    
         // This one doesn't change between objects, so this can be done once for all objects that use "programID"
        


        // Define light position vectors using the x, y, z coordinates
        glm::vec3 lightPos1 = glm::vec3(x1, y1, z1);
        glm::vec3 lightPos2 = glm::vec3(x2, y2, z2);
        glm::vec3 lightPos3 = glm::vec3(x3, y3, z3);
        glm::vec3 lightPos4 = glm::vec3(x4, y4, z4);

        // Set the light position for each light source in your shader
        glUniform3f(LightID1, lightPos1.x, lightPos1.y, lightPos1.z);
        glUniform3f(LightID2, lightPos2.x, lightPos2.y, lightPos2.z);
        glUniform3f(LightID3, lightPos3.x, lightPos3.y, lightPos3.z);
        glUniform3f(LightID4, lightPos4.x, lightPos4.y, lightPos4.z);
        
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
        
        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        // 2nd attribute buffer : UVs
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
            1,                                // attribute
            2,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        // 3rd attribute buffer : normals
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glVertexAttribPointer(
            2,                                // attribute
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        // Index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
        
        // if the value : move is 1 then activate movements and collision detection
        if(move == 1){
            
            std::thread thread1(detectAndRespondCollision, std::ref(x1), std::ref(y1), std::ref(z1), std::ref(dirx1), std::ref(diry1), std::ref(dirz1), std::ref(x2), std::ref(y2), std::ref(z2), std::ref(dirx2), std::ref(diry2), std::ref(dirz2));
              std::thread thread2(detectAndRespondCollision, std::ref(x1), std::ref(y1), std::ref(z1), std::ref(dirx1), std::ref(diry1), std::ref(dirz1), std::ref(x3), std::ref(y3), std::ref(z3), std::ref(dirx3), std::ref(diry3), std::ref(dirz3));
              std::thread thread3(detectAndRespondCollision, std::ref(x1), std::ref(y1), std::ref(z1), std::ref(dirx1), std::ref(diry1), std::ref(dirz1), std::ref(x4), std::ref(y4), std::ref(z4), std::ref(dirx4), std::ref(diry4), std::ref(dirz4));
              std::thread thread4(detectAndRespondCollision, std::ref(x2), std::ref(y2), std::ref(z2), std::ref(dirx2), std::ref(diry2), std::ref(dirz2), std::ref(x3), std::ref(y3), std::ref(z3), std::ref(dirx3), std::ref(diry3), std::ref(dirz3));
              std::thread thread5(detectAndRespondCollision, std::ref(x2), std::ref(y2), std::ref(z2), std::ref(dirx2), std::ref(diry2), std::ref(dirz2), std::ref(x4), std::ref(y4), std::ref(z4), std::ref(dirx4), std::ref(diry4), std::ref(dirz4));
              std::thread thread6(detectAndRespondCollision, std::ref(x3), std::ref(y3), std::ref(z3), std::ref(dirx3), std::ref(diry3), std::ref(dirz3), std::ref(x4), std::ref(y4), std::ref(z4), std::ref(dirx4), std::ref(diry4), std::ref(dirz4));


            std::thread thread7(moveAndDetectCollisionAndRotate, std::ref(x1), std::ref(y1), std::ref(z1), std::ref(dirx1), std::ref(diry1), std::ref(dirz1), std::ref(angle1));
            std::thread thread8(moveAndDetectCollisionAndRotate, std::ref(x2), std::ref(y2), std::ref(z2), std::ref(dirx2), std::ref(diry2), std::ref(dirz2), std::ref(angle2));
            std::thread thread9(moveAndDetectCollisionAndRotate, std::ref(x3), std::ref(y3), std::ref(z3), std::ref(dirx3), std::ref(diry3), std::ref(dirz3), std::ref(angle3));
            std::thread thread10(moveAndDetectCollisionAndRotate, std::ref(x4), std::ref(y4), std::ref(z4), std::ref(dirx4), std::ref(diry4), std::ref(dirz4), std::ref(angle4));


            // Wait for threads to finish
            thread1.join();
            thread2.join();
            thread3.join();
            thread4.join();
            thread5.join();
            thread6.join();
            thread7.join();
            thread8.join();
            thread9.join();
            thread10.join();
        }


//        std::thread first (moveAndDetectCollision, x1,y1,z1,dirx1,diry1,dirz1);
        
        glm::mat4 ModelMatrix1 = glm::mat4(1.0);
        ModelMatrix1 = glm::translate(ModelMatrix1, glm::vec3(x1, y1, z1));
        ModelMatrix1 = glm::rotate(ModelMatrix1, angle1, glm::vec3(0.0f, 0.0f, 1.0f));
        ModelMatrix1 = glm::rotate(ModelMatrix1, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 MVP1 = ProjectionMatrix * ViewMatrix * ModelMatrix1;
        
        
        glm::mat4 ModelMatrix2 = glm::mat4(1.0);
        ModelMatrix2 = glm::translate(ModelMatrix2, glm::vec3(x2, y2, z2));
        ModelMatrix2 = glm::rotate(ModelMatrix2, angle2, glm::vec3(0.0f, 0.0f, 1.0f));
        ModelMatrix2 = glm::rotate(ModelMatrix2, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 MVP2 = ProjectionMatrix * ViewMatrix * ModelMatrix2;
        
        glm::mat4 ModelMatrix3 = glm::mat4(1.0);
        ModelMatrix3 = glm::translate(ModelMatrix3, glm::vec3(x3, y3, z3));
        ModelMatrix3 = glm::rotate(ModelMatrix3, angle3, glm::vec3(0.0f, 0.0f, 1.0f));
        ModelMatrix3 = glm::rotate(ModelMatrix3, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 MVP3 = ProjectionMatrix * ViewMatrix * ModelMatrix3;
        
        glm::mat4 ModelMatrix4 = glm::mat4(1.0);
        ModelMatrix4 = glm::translate(ModelMatrix4, glm::vec3(x4, y4, z4));
        ModelMatrix4 = glm::rotate(ModelMatrix4, angle4, glm::vec3(0.0f, 0.0f, 1.0f));
        ModelMatrix4 = glm::rotate(ModelMatrix4, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 MVP4 = ProjectionMatrix * ViewMatrix * ModelMatrix4;
       


        //<------------------------------draw floor--------------------------->
        

        
        glUniform1i(glGetUniformLocation(programID, "isrect"), 1);
        
        // Use the shader program
        glUseProgram(programID);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, Texture2);
        glUniform1i(TextureID2, 1);
        
        GLuint squareVertexBuffer, squareUVBuffer, squareElementBuffer;
        glGenBuffers(1, &squareVertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, squareVertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

        glGenBuffers(1, &squareUVBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, squareUVBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

        glGenBuffers(1, &squareElementBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareElementBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square_indices), square_indices, GL_STATIC_DRAW);


        // Set up the matrices for the floor
        glm::mat4 FloorModelMatrix = glm::mat4(1.0);
        FloorModelMatrix = glm::translate(FloorModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f)); // Adjust position as needed
        glm::mat4 MVPSquare = ProjectionMatrix * ViewMatrix * FloorModelMatrix;
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVPSquare[0][0]);

        // Bind and set up the vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, squareVertexBuffer);
        glVertexAttribPointer(
           0,
           3,
           GL_FLOAT,
           GL_FALSE,
           0,
           (void*)0
        );

        // Bind and set up the UV buffer
        glBindBuffer(GL_ARRAY_BUFFER, squareUVBuffer);
        glVertexAttribPointer(
           1,
           2,
           GL_FLOAT,
           GL_FALSE,
           0,
           (void*)0
        );

        // Bind the element buffer and draw the elements
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareElementBuffer);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*)0);
        
        
        
        
        
        
        
 
        //draw 1st head
        
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP1[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix1[0][0]);
        
        glUniform1i(glGetUniformLocation(programID, "isrect"), 0);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Texture1);
        glUniform1i(TextureID1, 0);
        
        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                              0,                  // attribute
                              3,                  // size
                              GL_FLOAT,           // type
                              GL_FALSE,           // normalized?
                              0,                  // stride
                              (void*)0            // array buffer offset
                              );
        
        // 2nd attribute buffer : UVs
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
                              1,                                // attribute
                              2,                                // size
                              GL_FLOAT,                         // type
                              GL_FALSE,                         // normalized?
                              0,                                // stride
                              (void*)0                          // array buffer offset
                              );
        
        // 3rd attribute buffer : normals
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glVertexAttribPointer(
                              2,                                // attribute
                              3,                                // size
                              GL_FLOAT,                         // type
                              GL_FALSE,                         // normalized?
                              0,                                // stride
                              (void*)0                          // array buffer offset
                              );
        
        // Index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
        
        // Draw the triangles !
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void*)0);
        
//draw 2nd head
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP2[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix2[0][0]);
        
        
        // Bind our texture in Texture Unit 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Texture1);
        // Set our "myTextureSampler" sampler to use Texture Unit 0
        glUniform1i(TextureID1, 0);
        
        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                              0,                  // attribute
                              3,                  // size
                              GL_FLOAT,           // type
                              GL_FALSE,           // normalized?
                              0,                  // stride
                              (void*)0            // array buffer offset
                              );
        
        // 2nd attribute buffer : UVs
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
                              1,                                // attribute
                              2,                                // size
                              GL_FLOAT,                         // type
                              GL_FALSE,                         // normalized?
                              0,                                // stride
                              (void*)0                          // array buffer offset
                              );
        
        // 3rd attribute buffer : normals
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glVertexAttribPointer(
                              2,                                // attribute
                              3,                                // size
                              GL_FLOAT,                         // type
                              GL_FALSE,                         // normalized?
                              0,                                // stride
                              (void*)0                          // array buffer offset
                              );
        
        // Index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
        
        // Draw the triangles !
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void*)0);
        
        
//draw 3rd head
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP3[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix3[0][0]);
        
        
        // Bind our texture in Texture Unit 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Texture1);
        // Set our "myTextureSampler" sampler to use Texture Unit 0
        glUniform1i(TextureID1, 0);
        
        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                              0,                  // attribute
                              3,                  // size
                              GL_FLOAT,           // type
                              GL_FALSE,           // normalized?
                              0,                  // stride
                              (void*)0            // array buffer offset
                              );
        
        // 2nd attribute buffer : UVs
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
                              1,                                // attribute
                              2,                                // size
                              GL_FLOAT,                         // type
                              GL_FALSE,                         // normalized?
                              0,                                // stride
                              (void*)0                          // array buffer offset
                              );
        
        // 3rd attribute buffer : normals
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glVertexAttribPointer(
                              2,                                // attribute
                              3,                                // size
                              GL_FLOAT,                         // type
                              GL_FALSE,                         // normalized?
                              0,                                // stride
                              (void*)0                          // array buffer offset
                              );
        
        // Index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
        
        // Draw the triangles !
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void*)0);
        
        
//draw 4th head
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP4[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix4[0][0]);
        
        
        // Bind our texture in Texture Unit 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Texture1);
        // Set our "myTextureSampler" sampler to use Texture Unit 0
        glUniform1i(TextureID1, 0);
        
        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                              0,                  // attribute
                              3,                  // size
                              GL_FLOAT,           // type
                              GL_FALSE,           // normalized?
                              0,                  // stride
                              (void*)0            // array buffer offset
                              );
        
        // 2nd attribute buffer : UVs
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
                              1,                                // attribute
                              2,                                // size
                              GL_FLOAT,                         // type
                              GL_FALSE,                         // normalized?
                              0,                                // stride
                              (void*)0                          // array buffer offset
                              );
        
        // 3rd attribute buffer : normals
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glVertexAttribPointer(
                              2,                                // attribute
                              3,                                // size
                              GL_FLOAT,                         // type
                              GL_FALSE,                         // normalized?
                              0,                                // stride
                              (void*)0                          // array buffer offset
                              );
        
        // Index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void*)0);
        
        
        // draw background
        

        
        
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        
        
        
        ////// End of rendering of the four objects //////
        


        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    // Cleanup VBO and shader
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &uvbuffer);
    glDeleteBuffers(1, &normalbuffer);
    glDeleteBuffers(1, &elementbuffer);
    glDeleteProgram(programID);
    glDeleteTextures(1, &Texture1);
    glDeleteTextures(1, &Texture2);
    glDeleteVertexArrays(1, &VertexArrayID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}



void moveAndDetectCollisionAndRotate(GLfloat &x, GLfloat &y, GLfloat &z, GLfloat &dirx, GLfloat &diry, GLfloat &dirz,
                            GLfloat &angle) {

    x += dirx;
    y += diry;
    z += dirz;
    
    angle += getRandomFloat(0.0f, 0.2f);

    if (x <= -5 || x >= 5) {
        dirx = -dirx;
    }


    if (y <= -5 || y >= 5) {
        diry = -diry;
    }


    if (z <= -5 || z >= 5) {
        dirz = -dirz;
    }
}

float getRandomFloat(float min, float max) {
    static std::random_device rd; // Obtain a random number from hardware
    static std::mt19937 eng(rd()); // Seed the generator
    std::uniform_real_distribution<> distr(min, max); // Define the range

    return static_cast<float>(distr(eng));
}



void detectAndRespondCollision(GLfloat& x1, GLfloat& y1, GLfloat& z1, GLfloat& dirx1, GLfloat& diry1, GLfloat& dirz1,
                               GLfloat& x2, GLfloat& y2, GLfloat& z2, GLfloat& dirx2, GLfloat& diry2, GLfloat& dirz2) {
    glm::vec3 pos1(x1, y1, z1);
    glm::vec3 pos2(x2, y2, z2);

    // Distance between objects
    float distance = glm::distance(pos1, pos2);

    // Collision threshold, replace with appropriate value
    float collisionThreshold = 0.5f; // Example value

    if (distance < collisionThreshold) {
        // Collision detected, reverse directions
        dirx1 = -dirx1;
        diry1 = -diry1;
        dirz1 = -dirz1;
        dirx2 = -dirx2;
        diry2 = -diry2;
        dirz2 = -dirz2;
    }
}
