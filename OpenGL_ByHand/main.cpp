#include <GL\glew.h>		// automagically links system-specific OpenGL implementations (eg, from your video driver)
#include <GLFW\glfw3.h>		// Cross platform window handler. will probably replace with lmgui later

//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <glm/ext/matrix_float3x4.hpp>
//#include <glm/ext/matrix_transform.hpp>

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




	//setup our shader object
	Shader shaderProgram("vert.shader", "frag.shader");
	shaderProgram.Activate(); //glUseProgram


	//Object setup (what we're drawing on the screen
	GLOBJECT OBJECT1(Triforce, sizeof(Triforce), TriforceIndicies, sizeof(TriforceIndicies), 2, 3, 6);
	GLOBJECT TESTOBJECT(rect, sizeof(rect), elements, sizeof(elements), 2, 3, 6);
	GLOBJECT LINE(line, sizeof(line), 1, 2, 2);

	

	std::cout << "Entering Main Loop..." << std::endl;
	while (!glfwWindowShouldClose(window)) {


		float time = float(glfwGetTime());
		float greenValue = (sin(time) / 2.0f) + 0.5f;

		
		glClearColor(0.2f, 0.2f, 0.8f, 1.0f);		// set the background color
		glClear(GL_COLOR_BUFFER_BIT);				// clear the screen
		glLineWidth(1);								// Must be < 1.0. Will need to make a poly for thick lines...

		shaderProgram.Activate(); //glUseProgram


		//update specific shader uniforms
		//vertexColorLocation = glGetUniformLocation(shaderProgram.getID(), "ourColor"); //cycle green
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);


		//glDrawElements
		//		Mode (The type of primative to render)
		//      Count (number of elemtns to be rendered)
		//      Type (type of values in the indicies) 
		//      and pointer to the indicies (null pointer valid). 

		TESTOBJECT.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		TESTOBJECT.Unbind();

		OBJECT1.Bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		OBJECT1.Unbind();



		LINE.Bind();
		LINE.Update(line, sizeof(line), 1, 2, 2);
		glDrawArrays(GL_LINES, 0, 2);
		LINE.Unbind();


		line[0] = 2.0 * mouseX / windowW -1.0;
		line[1] = 1.0 - 2.0 * mouseY / windowH;

		
		glfwSwapBuffers(window);
		glfwPollEvents(); // get window events (mouse, keypress, etc...)

	}

	std::cout << "STOPPING... Cleanup starting..." << std::endl;

	//broken for some reason
	//shaderProgram.Delete();
	
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