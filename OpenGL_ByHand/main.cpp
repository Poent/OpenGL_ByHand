#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <Callbacks.h>
#include <VertexAttributes.h>
#include <Windows.h>
#include <shaderClass.h>
#include <vao.h>
#include <vbo.h>
#include <ebo.h>

//#define GLEW_STATIC  //tell it to use the static dll // MOVED TO PROJECT SETTINGS
// 
// Learning Links
// http://glew.sourceforge.net/basic.html
// https://www.glfw.org/docs/3.3/quick_guide.html


static void  cursorPositionCallback(GLFWwindow* window, double xPos, double yPos);

float mouseX, mouseY;

int main() {


	/*============ INITIALIZE STUFF ========================*/
	//Try to init glfw, report failure if you can't (Should probably break here...)
	glfwInit() ? std::cout << "glfwInit Success!\n" : std::cout << "glfwInit Failed!\n";
	
	//variable setup
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

	glfwSwapInterval(1);


	//Now that we've made the window, set it as the openGL Context.
	//should still make it crash here like under GLFWwindow....
	glfwMakeContextCurrent(window);
	glewInit() == GLEW_OK ? std::cout << "GLEW_OK! Version: " << glewGetString(GLEW_VERSION) << "\n" : std::cout << "GLEW_NOT_OK!\n";

	//setup callbacks - key callback only used to close window for now. 
	glfwSetKeyCallback(window, key_callback);
	//Need to do this properly. Cherno has a tutorial on wrapping openGL calls with a message checker... 
	glfwSetErrorCallback(error_callback);
	//setup window resize callback
	glfwSetWindowSizeCallback(window, window_size_callback);
	//setup cursor position callback
	glfwSetCursorPosCallback(window, cursorPositionCallback);
	//set default viewport Should move settings to define

	glViewport(0, 0, 800, 800);

	/*==========  END DEFAULT INITIALIZE STUFF ====================*/


	//setup our default shaders... basic and still learning
	Shader shaderProgram("vert.shader", "frag.shader");

	//We moved all the complex 
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

	//VAO vaoArray[2];
	


	//PROGRAM HERE
	while (!glfwWindowShouldClose(window)) {

		glLineWidth(4);
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

		VBO2.Update(line, sizeof(line));
		
		#ifdef DEBUG
		GLuint* vaoID = VAO1.GetID();
		GLuint* vboID = VBO1.GetID();
		std::cout << "VAO1 ID Memory Location: " << vaoID << " ID Value: " << *vaoID << std::endl;
		std::cout << "VBO1 ID Memory Location: " << vboID << " ID Value: " << *vboID << std::endl;
		#endif


		glDrawArrays(GL_LINES,0 , 2);

		
		VAO2.Unbind();
		VBO2.Unbind();

		glfwSwapBuffers(window);

		//if (line[0] > 1 || line[0] < -1) {
		//	mod *= -1;
		//}
		//line[0] += mod;
		//line[1] += mod;

		line[0] = 2.0f * mouseX / 800 -1.0f;
		line[1] = 1.0f - 2.0f * mouseY / 800;


		//std::cout << line[0] << " : " << line[1] << std::endl;
		
		
		//Sleep(10);
		//take care of all the glfw events
		glfwWaitEvents(); // get window events (mouse, keypress, etc...)

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

static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos) {

	//std::cout << xPos << " : " << yPos << std::endl;
	mouseX = xPos;
	mouseY = yPos;


}