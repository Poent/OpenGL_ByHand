#include <GL\glew.h>		// automagically links system-specific OpenGL implementations (eg, from your video driver)
#include <GLFW\glfw3.h>		// Cross platform window handler. will probably replace with lmgui later

#include <Callbacks.h>		// lazy input handling
#include <glerror.h>		// OpenGL error handling - because otherwise it sits silently screaming inside

#include <VertexAttributes.h> //contains manual vertices (until we handle loading meshes)
#include <vao.h>		// VAO class
#include <vbo.h>		// VBO class
#include <ebo.h>		// EBO class
#include <globject.h>	//Tries (and failes) to combine the above classes into a single class...

#include <shaderClass.h>

#define DEBUG


// Learning Links
// http://glew.sourceforge.net/basic.html
// https://www.glfw.org/docs/3.3/quick_guide.html

/*
!!!NOTES!!!
In Progress:
- https://learnopengl.com/Getting-started/Shaders
- Studying shaders and uniforms. Getting ready to updated VertexAttribs to include additional... vertex attribs
- Specifically looking to update attribs from just pos - will eventually include position, color, and texture coord (S, T, R). 
- once we can draw a texture on a single square we'll transform that squares position and start thinking about how we handle multiples on the screen

Change Log:

03/01/2022
- Implemented OpenGL error handling with both glGetError and GLDebugMessageCallback
-- glGetError is legacy but compatible with older versions of OpenGL.
-- GLDebugMessageCallback is more robust but does not work on OpenGL versins 4.3 or earlier
- Based on error messages corrected the following:
-- glLineWidth(x); x must be <= 1. I prefer the thick lines but will need to replace with a poly
-- globject::bind had VBO.Bind() commented out. Thought this was the cause of my issue but did not change anything. 
-- 

02/28/2022
- Added globject.h and globject.cpp to create GLOBJECT class to combine VAO, VBO, and EBO... 
- Not able to get it working though.. Should draw a multi-color triangle on the screen based off content of VertexAttributes.h (specifically Triforce and TriforceIndices). This worked before classifying.
- Commented out lines 122-144 which were the original independent class calls...
- Likely need to setup OpenGL error handling to identify issue... 


06/21/21
- introduced change log
- Implemented first Uniform and used it to cycle shader "green" color. 
- changed glfwWaitEvents() to glfwPollEvents() in main while loop. Was causing updates to pause until window event occured (makes sense). 
- Previous research recommended change for performance. Will need to investigate further. This seems fine for now. 
- added square the the middle of the rander to eventually draw a texture on. 

*/



// Mouse position stuff. Just using it for testing. 
static void  cursorPositionCallback(GLFWwindow* window, double xPos, double yPos);
double mouseX, mouseY; 
const int windowW = 800, windowH = 800;


int main() {


	/*============ INITIALIZE STUFF ========================*/
	//Try to initialize glfw, report failure if you can't (Should probably break here...)
	glfwInit() ? std::cout << "glfwInit Success!\n" : std::cout << "glfwInit Failed!\n";
	
	GLFWwindow* window = glfwCreateWindow(windowW, windowH, "Hello World", NULL, NULL);
	if (!window)
	{
		std::cout << "failed to make the window!";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}


	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); //limit draw to screen refresh rate. 


	glewInit() == GLEW_OK ? std::cout << "GLEW_OK! Version: " << glewGetString(GLEW_VERSION) << "\n" : std::cout << "GLEW_NOT_OK!\n";

	//setup callbacks - key callback only used to close window for now. 
	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);		//setup window resize callback
	glfwSetCursorPosCallback(window, cursorPositionCallback);		//setup cursor position callback
	
	glViewport(0, 0, windowW, windowH); //set default viewport Should move value to a const uint... can then use window size callback. 

#ifdef DEBUG
	//POINT ERROR HANDLER HERE NOW THAT GL is setup
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	//Tell OpenGL what to do with error (send it to our function in glerror.h)
	glDebugMessageCallback(GLDebugMessageCallback, NULL);
#endif

#ifdef DEBUG
	//get the max number of vertex attributes supported by the GPU
	//Interesting to know but we won't be bumping up against this anytime soon
	//(opengl limits this to 16 by default). 
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Max number of vertex attribs supported: " << nrAttributes << std::endl;
#endif

	/*==========  END DEFAULT INITIALIZE STUFF ====================*/


	//setup our default shaders... basic and still learning
	Shader shaderProgram("vert.shader", "frag.shader");
	shaderProgram.Activate(); //glUseProgram

	/*
	//playing with  uniforms now that the shaders are defined and activated
	int vertexColorLocation = glGetUniformLocation(shaderProgram.getID(), "ourColor");
	std::cout << std::endl << "ourColor uniform location: " << vertexColorLocation << std::endl;
	int location = glGetUniformLocation(shaderProgram.getID(), "u_Color");
	std::cout << "Uniform u_Color Location: " << location << std::endl;

	//glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f);
	*/



	// Trying to replace VAO1 (below) with our combnined buffer object
	// This object is supposed to combine all VAO, VBO, and EBO setu
	// ACTIVE PROBLEM, CURRENTLY NOT WORKING
	std::cout << "INIT OBJECT1..." << std::endl;
	GLOBJECT OBJECT1(Triforce, TriforceIndicies, 2, 3, 6);
	OBJECT1.Unbind();


	OBJECT1.GetID();

	
	VAO VAO1;
	VAO1.Bind();

	// Generate Vertex Buffer Object and link it to verts
	// Initialize the object with the set of verts we want to control. 
	VBO VBO1(Triforce, sizeof(Triforce));

	// Generate Element Buffer and link it to indices
	// Element buffers allow us to link the vertex of individual verticies together
	// This allows us to reference and transform the verticies in specific ways. 
	EBO EBO1(TriforceIndicies, sizeof(TriforceIndicies));

	// link vbo to vao
	VAO1.LinkVBO(VBO1, 0, 3, 6, 0);	//position attribute
	VAO1.LinkVBO(VBO1, 1, 3, 6, 3);	//color attribute

	// unbind everything to prevent accidentally modifying them
	
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	//*/

	//Working use of VAO, VBO outside of GLOBJECT
	//==== Initialize Line Draw Function ====
	
	VAO VAO2;							// Generate Vertex Array Object (This is nothing but a state wrapper)
	VAO2.Bind();						// Set that buffer as active
	VBO VBO2(line, sizeof(line));		// Initialize the VBO with actual data

	VAO2.LinkVBO(VBO2, 0, 2, 0, 0);		//link the VBO to the VAO and tell it how to read the data

	VAO2.Unbind();						//cleanup after setup
	VBO2.Unbind();						//cleanup after setup
	//==== End Line Draw init



	/*
	VAO BRICKVAO1;
	BRICKVAO1.Bind();

	VBO BRICKVBO1(brick, sizeof(brick));
	EBO BRICKEBO1(brickEDO, sizeof(brickEDO));

	BRICKVAO1.LinkVBO(BRICKVBO1, 0, 3, 0, 0);

	BRICKVAO1.Unbind();
	BRICKVBO1.Unbind();
	BRICKEBO1.Unbind();
	//*/

	// ===============


	//PROGRAM HERE
	while (!glfwWindowShouldClose(window)) {

		std::cout << "Entered Main Loop..." << std::endl;

		float time = float(glfwGetTime());
		float greenValue = (sin(time) / 2.0f) + 0.5f;

		
		glClearColor(0.2f, 0.2f, 0.8f, 1.0f);		// set the background color
		glClear(GL_COLOR_BUFFER_BIT);				// clear the screen
		glLineWidth(1);								// Must be < 1.0. Will need to make a poly for thick lines...

		shaderProgram.Activate(); //glUseProgram


		//update specific shader uniforms
		//vertexColorLocation = glGetUniformLocation(shaderProgram.getID(), "ourColor"); //cycle green
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		std::cout << "Bind the Object..." << std::endl;
		//OBJECT1.Bind();
		OBJECT1.VAO1.Bind();
		OBJECT1.VBO1.Bind();

		GetActiveVBO();
		std::cout << "Update the object (OBJECT1)..." << std::endl;
		OBJECT1.VBO1.Update( Triforce, sizeof(TriforceIndicies) );
		//OBJECT1.Update(Triforce, TriforceIndicies);
		


		////Draw the Triangle using the specified primitive
		//glDrawArrays(GL_TRIANGLES, 0, 3); // replaced when implementing ebos
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		OBJECT1.Unbind();







		VAO2.Bind();
		VBO2.Bind();
		VBO2.Update(line, sizeof(line));
		GetActiveVBO();
		glDrawArrays(GL_LINES,0 , 2);

		VAO2.Unbind();
		VBO2.Unbind();



		//if (line[0] > 1 || line[0] < -1) {
		//	mod *= -1;
		//}
		//line[0] += mod;
		//line[1] += mod;

		line[0] = 2.0 * mouseX / windowW -1.0;
		line[1] = 1.0 - 2.0 * mouseY / windowH;


		//std::cout << line[0] << " : " << line[1] << std::endl;

		
		
		//Sleep(10);
		//swap buffer and poll IO events
		glfwSwapBuffers(window);
		glfwPollEvents(); // get window events (mouse, keypress, etc...)

	}

	std::cout << "STOPPING... Cleanup starting..." << std::endl;

	//delete all the stuff we made
	//VAO1.Delete();
	//VBO1.Delete();
	//EBO1.Delete();
	OBJECT1.Delete();


	/*
	BRICKEBO1.Delete();
	BRICKVAO1.Delete();
	BRICKVBO1.Delete();
	*/
	VAO2.Delete();
	VBO2.Delete();
	



	//busted.... triggers opengl breakpoint.. havn't looked into yet. 
	shaderProgram.Delete();
	
	std::cout << "Goodbye world!";
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;

}



// need to mobe this to Callbacks.h
static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos) {

	//std::cout << xPos << " : " << yPos << std::endl;
	mouseX = xPos;
	mouseY = yPos;


}