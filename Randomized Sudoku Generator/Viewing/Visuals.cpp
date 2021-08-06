#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "BuffersAndStorage/Buffer.h"
#include "BuffersAndStorage/Shader.h"
#include "BuffersAndStorage/Texture.h"
#include <array>
#include <tuple>
#include "SetVertexBuffer.h"

extern std::array<int, 81> matrix;

void SetUpWindowAndVisuals() {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1024, 768, "Sudoku Board", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    std::array<Vertex, 82 * 4> array;           //this holds all the necessary vertices to be drawn, and there being 4 vertices per quadrilater
    Vertex* index = array.data();               //and 82 quadrilaterals, that means that we need 82 * 4 vertices (each comprised of 5 floats
    setSudokuStage(index);                      //for our x, y position, texture coordinates, and our texture slot) to be stored inside of our
                                                //vertex buffer.

    for (auto [y, start1, heightDisplacement] = std::tuple{ 0, 0.48f, 0.11f }; y < 9; y++, start1 -= heightDisplacement) {     
        for (auto [x, start2, distance] = std::tuple{ 0, -0.46f, 0.11f }; x < 9; x++, start2 += distance) {
            getBackThing(index, start2, start1, matrix[y * 9 + x]);                     //simple array indexing to set the texture slot for each vertex.
        }
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        return;
    }

    glEnable(GL_BLEND);                                     //textures don't blend well to quadrilaterals underneath without this.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    unsigned int va;
    glGenVertexArrays(1, &va);                      //bind vertex array which binds the index buffer and the vertex buffer because it has a reference to them.
    glBindVertexArray(va);

    VertexBuffer vb( array.data(), sizeof(Vertex) * 4 * 82 );
    vb.setLayout(0, 2, 5 * sizeof(float), 0);                       //data containing all the vertices.
    vb.setLayout(1, 2, 5 * sizeof(float), 2 * sizeof(float));       //2 first floats in a vertex are the x, y, the next 2 floats are 
    vb.setLayout(2, 1, 5 * sizeof(float), 4 * sizeof(float));       //the texture coordinates and the last is the texture slot. 
                                                                    //we specify the layout of the vertex here, which holds up for all 82 * 4 vertices because they have the same layout each.
    unsigned int indices[82 * 6];
    for (int i = 0; i < 82; i++) {                                  //every quadrilateral has 6 points for efficiency. There being 82 quadrilaterals
        indices[6 * i] = 4 * i;                                     //means there are 82 * 6 points.
        indices[(6 * i) + 1] = (4 * i) + 1;
        indices[(6 * i) + 2] = (4 * i) + 2;
        indices[(6 * i) + 3] = (4 * i) + 2;
        indices[(6 * i) + 4] = (4 * i) + 3;                         //they repeat in a predictable manner so we devise a formula to set how each quadrilateral is to be drawn.
        indices[(6 * i) + 5] = 4*i;
    }

    IndexBuffer ib{ indices, 82* 6 };                           //bind and transfer data from right above into here.

    Shader program( "Viewing/BuffersAndStorage/ShaderInfo.text" );                //read our vertex and fragment shaders and tether them into our program here.
    program.Use();
    //program.setUniform("u_Color", 1.0f, 0.7f, 1.0f, 1.0f);        //color here if you would like to use it. Not necessary since we use the colors from the textures.


    std::array<Texture, 10> textures{
        Texture{"testImages/blank-sudoku-grid.png"} ,
        Texture{"testImages/sudokuNumber1.png" },
        Texture{ "testImages/sudokuNumber2.png" },
        Texture{ "testImages/sudokuNumber3.png" },
        Texture{ "testImages/sudokuNumber4.png" },                  //all of our textures here. Isn't encapsulated because their main usage is already
        Texture{ "testImages/sudokuNumber5.png" },                  //abstracted, and it's usage here is really simple. 
        Texture{ "testImages/sudokuNumber6.png" },
        Texture{ "testImages/sudokuNumber7.png" },
        Texture{ "testImages/sudokuNumber8.png" },
        Texture{ "testImages/sudokuNumber9.png" }
    };

    for (int i = 0; i < textures.size(); i++) {
        textures[i].Bind(i);                                        //have a distinct texture slot for each texture that we use as a marker for each quadrilateral.
    }

    int samplers[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    program.setUniform("u_Textures", 10, samplers);                 //uniforms for the textures.
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 82 * 6, GL_UNSIGNED_INT, nullptr);         //drawcall that you need if using an index buffer.
                                                                                //There are 82 * 6 indices as mentioned above.
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}