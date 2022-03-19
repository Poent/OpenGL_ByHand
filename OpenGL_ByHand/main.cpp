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

#include <globject.h>	//Tries (and failes) to combine the above classes into a single class...
#include <renderer.h>

#include <shaderClass.h>

#include <texture.h>


//#define DEBUG



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
	//glfwSwapInterval(1); //limit draw to screen refresh rate. 


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
	GLOBJECT OBJECT1(Triforce, sizeof(Triforce), TriforceIndicies, sizeof(TriforceIndicies), GL_FLOAT, GL_FALSE, 2, 3, 6);
	GLOBJECT LINE(line, sizeof(line), GL_FLOAT, GL_FALSE, 1, 2, 2);



	
	
	//Testing the loading of textures. This uses our texture class to load an image with stb_img.  
	
	//This is a new overloaded constructor that adds the texture attribute. It just seemed like the simplest way to load the attribute at the time.
	//We confirmed that the constructor is working appropriately by testing it without the texture specified in the shader driver...
	GLOBJECT TESTOBJECT(rect, sizeof(rect), elements, sizeof(elements), GL_FLOAT, GL_FALSE, 3, 3, 8, 1);
	Texture texture("Textures/Jake_small.png");

	glUniform1i(glGetUniformLocation(shaderProgram.getID(), "texture1"), 0);


	Renderer renderer;

	std::cout << "Entering Main Loop..." << std::endl;
	while (!glfwWindowShouldClose(window)) 
	{

		glfwPollEvents(); // get window events (mouse, keypress, etc...)
		float time = float(glfwGetTime());
		float greenValue = (sin(time) / 2.0f) + 0.5f;
		line[0] = 2.0 * mouseX / windowW - 1.0;
		line[1] = 1.0 - 2.0 * mouseY / windowH;
		//glLineWidth(1); //must be <= 1. Thick lines is depreciated.

		
		renderer.clear(0.2f, 0.2f, 0.8f, 1.0f);
							
		shaderProgram.Activate(); //glUseProgram


		//update specific shader uniforms
		//vertexColorLocation = glGetUniformLocation(shaderProgram.getID(), "ourColor"); //cycle green
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		GLCall(glActiveTexture(GL_TEXTURE0));
		texture.Bind();
		renderer.Draw(TESTOBJECT, shaderProgram);
		
		renderer.Draw(OBJECT1, shaderProgram);

		//need to update rendered to accept draw types (line vs element vs array). 
		LINE.Bind();
		LINE.Update(line, sizeof(line), 1, 2, 2);
		glDrawArrays(GL_LINES, 0, 2);
		LINE.Unbind();

		
		glfwSwapBuffers(window);


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