#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <Header.h>
#include <Windows.h>
#include <shaderClass.h>
#include <vao.h>
#include <vbo.h>
#include <ebo.h>

//#define GLEW_STATIC  //tell it to use the static dll
// http://glew.sourceforge.net/basic.html
// https://www.glfw.org/docs/3.3/quick_guide.html
//error handler


float points[] = {
   -0.5f, -0.5f * float(sqrt(3)) / 3,  0.0f,		//Lower Left
   0.5f,  -0.5f * float(sqrt(3)) / 3,  0.0f,		//upper corner
   0.0f, 0.5f * float(sqrt(3)) * 2 / 3,  0.0f,			//Lower Right

  -0.5f / 2, 0.5f * float(sqrt(3)) / 6,  0.0f,			//Inner Left
  0.5f / 2, 0.5f * float(sqrt(3)) / 6,  0.0f,			//Inner right
  0.0f, -0.5f * float(sqrt(3)) / 3,  0.0f			//Inner Down
};

unsigned int indicies[] = {
	0, 3, 5,
	3, 2, 4,
	5, 4, 1
};

float line[] = {
	-0.5, 0.5,
	0.5, -0.5
};

float newLine[];




int main() {


	/*============ INITIALIZE STUFF ========================*/

	glfwInit() ? std::cout << "glfwInit Success!\n" : std::cout << "glfwInit Failed!\n";
	
	//might use
	double time = glfwGetTime();
	float mod = 0.01;


	//setup our opengl window with the below parameters. 
	GLFWwindow* window = glfwCreateWindow(800, 800, "Hello World", NULL, NULL);
	if (!window)
	{
		std::cout << "failed to make the window!";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Now that we've made the window, set it as the openGL Context.
	glfwMakeContextCurrent(window);
	glewInit() == GLEW_OK ? std::cout << "GLEW_OK! Version: " << glewGetString(GLEW_VERSION) << "\n" : std::cout << "GLEW_NOT_OK!\n";

	//setup callbacks
	glfwSetKeyCallback(window, key_callback);
	glfwSetErrorCallback(error_callback);

	glViewport(0, 0, 800, 800);

	/*==========  END INITIALIZE STUFF ====================*/


	Shader shaderProgram("vert.shader", "frag.shader");

	//generate Vertex Array Object and bind it
	VAO VAO1;
	VAO1.Bind();

	//Generate Vertex Buffer Object and link it to verts
	VBO VBO1(points, sizeof(points));

	//Generate Element Buffer and link it to indices
	EBO EBO1(indicies, sizeof(indicies));

	//link vbo to vao
	VAO1.LinkVBO(VBO1, 3, 0);

	// unbind everything to prevent accidentally modifying them
	
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();




	VAO VAO2;
	VAO2.Bind();

	VBO VBO2(line, sizeof(line));

	VAO2.LinkVBO(VBO2, 2, 0);

	VAO2.Unbind();
	VBO2.Unbind();


	


	//PROGRAM HERE
	while (!glfwWindowShouldClose(window)) {

		float newPoints[9];
		glLineWidth(2);
		//set the background color
		glClearColor(0.2f, 0.2f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT); // clear the screen

		shaderProgram.Activate();

		VAO1.Bind();

		////Draw the Triangle using the specified primitive
		////glDrawArrays(GL_TRIANGLES, 0, 3); // replaced when implementing ebos
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		VAO1.Unbind();


		VAO2.Bind();
		VBO2.Bind();

		//std::wcout << line[0] << " " << line[1] << std::endl;
		VBO2.Update(line, sizeof(line));
		GLuint* vaoID = VAO1.GetID();
		GLuint* vboID = VBO1.GetID();
		std::cout << "VAO1 ID Memory Location: " << vaoID << " ID Value: " << *vaoID << std::endl;
		std::cout << "VBO1 ID Memory Location: " << vboID << " ID Value: " << *vboID << std::endl;


		//float fXOffset = 0.0f, fYOffset = 0.0f;
		//ComputePositionOffsets(fXOffset, fYOffset);
		//AdjustVertexData(fXOffset, fYOffset);

		//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		//glClear(GL_COLOR_BUFFER_BIT);

		//glUseProgram(theProgram);

		//glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

		//glDrawArrays(GL_TRIANGLES, 0, 3);

		//glDisableVertexAttribArray(0);
		//glUseProgram(0);

		//glutSwapBuffers();
		//glutPostRedisplay();


		glDrawArrays(GL_LINES,0 , 2);

		
		VAO2.Unbind();
		VBO2.Unbind();

		glfwSwapBuffers(window);

		if (line[0] > 1 || line[0] < -1) {
			mod *= -1;
		}
		line[0] += mod;
		
		
		Sleep(10);
		//take care of all the glfw events
		glfwPollEvents(); // get window events (mouse, keypress, etc...)

	}

	//delete all the stuff we made
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	
	std::cout << "Goodbye world!";
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;

}