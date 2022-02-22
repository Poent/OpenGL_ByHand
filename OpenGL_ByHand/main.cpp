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

/*
!!!NOTES!!!
In Progress:
- https://learnopengl.com/Getting-started/Shaders
- Studying shaders and uniforms. Getting ready to updated VertexAttribs to include additional... vertex attribs
- Specifically looking to update attribs from just pos - will eventually include position, color, and texture coord (S, T, R). 
- once we can draw a texture on a single square we'll transform that squares position and start thinking about how we handle multiples on the screen


Change Log:

06/21/21
- introduced change log
- Implemented first Uniform and used it to cycle shader "green" color. 
- changed glfwWaitEvents() to glfwPollEvents() in main while loop. Was causing updates to pause until window event occured (makes sense). 
- Previous research recommended change for performance. Will need to investigate further. This seems fine for now. 
- added square the the middle of the rander to eventually draw a texture on. 

*/


//will move this to callback header later. still playing. 
static void  cursorPositionCallback(GLFWwindow* window, double xPos, double yPos);

double mouseX, mouseY;
const int windowW = 800, windowH = 800;



int main() {


	/*============ INITIALIZE STUFF ========================*/
	//Try to init glfw, report failure if you can't (Should probably break here...)
	glfwInit() ? std::cout << "glfwInit Success!\n" : std::cout << "glfwInit Failed!\n";
	
	//variable setup



	


	//setup our opengl window with the below parameters. 
	GLFWwindow* window = glfwCreateWindow(windowW, windowH, "Hello World", NULL, NULL);
	if (!window)
	{
		std::cout << "failed to make the window!";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSwapInterval(1); //limit draw to screen refresh rate. 


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
	//set default viewport Should move value to a const uint... can then use window size callback. 
	glViewport(0, 0, windowW, windowH);

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

	//Setup uniforms now that the shaders are defined and activated
#ifdef DEBUG
	int vertexColorLocation = glGetUniformLocation(shaderProgram.getID(), "ourColor");
	std::cout << std::endl << "ourColor uniform location: " << vertexColorLocation << std::endl;
#endif


	shaderProgram.Activate(); //glUseProgram

//    Testing uniforms
	int location = glGetUniformLocation(shaderProgram.getID(), "u_Color");
	std::cout << "Uniform u_Color Location: " << location << std::endl;

	//glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f);
	
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



	//==== Initialize Line Draw Function ====
	VAO VAO2;
	VAO2.Bind();

	VBO VBO2(line, sizeof(line));

	VAO2.LinkVBO(VBO2, 0, 2, 0, 0);

	VAO2.Unbind();
	VBO2.Unbind();
	//==== End Line Draw init

	VAO BRICKVAO1;
	BRICKVAO1.Bind();

	VBO BRICKVBO1(brick, sizeof(brick));
	EBO BRICKEBO1(brickEDO, sizeof(brickEDO));

	BRICKVAO1.LinkVBO(BRICKVBO1, 0, 3, 0, 0);

	BRICKVAO1.Unbind();
	BRICKVBO1.Unbind();
	BRICKEBO1.Unbind();


	// ===============


	//PROGRAM HERE
	while (!glfwWindowShouldClose(window)) {

		float time = float(glfwGetTime());
		float greenValue = (sin(time) / 2.0f) + 0.5f;

		//set the width of our glLines. This could be anywhere after GLFW and GLEW init functions. 
		glLineWidth(4);

		//set the background color
		glClearColor(0.2f, 0.2f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT); // clear the screen

		//set the specific Shader object as active. 
		

		//update specific shader uniforms
		//vertexColorLocation = glGetUniformLocation(shaderProgram.getID(), "ourColor"); //cycle green
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);


		VAO1.Bind();

		////Draw the Triangle using the specified primitive
		////glDrawArrays(GL_TRIANGLES, 0, 3); // replaced when implementing ebos
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		VAO1.Unbind();

		BRICKVAO1.Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		BRICKVAO1.Unbind();

		VAO2.Bind();
		VBO2.Bind();

		VBO2.Update(line, sizeof(line));
		
		#ifdef DEBUG
		GLuint* vaoID = VAO1.GetID();
		GLuint* vboID = VBO1.GetID();
		std::cout << "VAO1 ID Memory Location: " << vaoID << " ID Value: " << *vaoID << std::endl;
		std::cout << "VBO1 ID Memory Location: " << vboID << " ID Value: " << *vboID << std::endl;
		std::cout << std::endl << " greenValue: " << greenValue << std::endl;
		#endif


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