#include <GL\glew.h>		// automagically links system-specific OpenGL implementations (eg, from your video driver)
#include <GLFW\glfw3.h>		// Cross platform window handler. will probably replace with lmgui later

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <Vendor/imgui-1.87/imgui.h>
#include <vendor/imgui-1.87/example_glfw_opengl3/imgui_impl_opengl3.h>
#include <Vendor/imgui-1.87/example_glfw_opengl3/imgui_impl_glfw.h>

#define _USE_MATH_DEFINES

#include <Callbacks.h>				// lazy input handling
#include <glerror.h>				// OpenGL error handling (#include DEBUG)- because otherwise it sits silently screaming inside
#include <VertexAttributes.h>		// Contains our object/vertex data (until we handle loading meshes)
#include <globject.h>				// Object Management class. Feed this class data to create scene objects
#include <renderer.h>				// Handles 
#include <shaderClass.h>
#include <texture.h>



// #define DEBUG




// Mouse position stuff. Just using it for testing. 
static void  cursorPositionCallback(GLFWwindow* window, double xPos, double yPos);
double mouseX, mouseY; 
const int windowW = 1200, windowH = 1200;



int main() {
	
	std::cout.precision(3);

	int segments = 30;

	float segmentDegrees = 360.0 / segments;
	float SegmentRadians = segmentDegrees * (M_PI / 180);


	float radius = 0.5f;
	float* CircleArray = new float[segments * 2];
	GLuint* CircleElements = new GLuint[segments];

	//calculate angles based on size
	std::cout << "Slices: " << segments << std::endl;
	std::cout << "Segment Degrees: " << segmentDegrees << std::endl;
	std::cout << "Segment Radians: " << SegmentRadians << std::endl;


	for (int i = 0; i < segments; i++)
	{

		float x = radius * sin(i * SegmentRadians);
		float y = radius * cos(i * SegmentRadians);

		CircleArray[i * 2] = x;
		CircleArray[i * 2 + 1] = y;
		std::cout << "Vertex: " << i << " X: " << x << " Y: " << y << std::endl;


	}

	std::cout << std::endl;

	for (int i = 0; i < segments * 2; i += 2)
	{
		std::cout << "Vertex: " << i/2 << " X: " << CircleArray[i] << " Y: " << CircleArray[i + 1] << std::endl;
	}

	for (int i = 0; i <= segments; i++)
	{
		CircleElements[i] = i;
		CircleElements[i+1] = i+1;
		if ((i + 1) == 16) {
			CircleElements[i + 1] = 0;
		}

		std::cout << " X: " << CircleElements[i] << " Y: " << CircleElements[i + 1] << std::endl;
	}

	


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
	
	const char* glsl_version = "#version 330";
		// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	//glViewport(0, 0, windowW, windowH); //set default viewport Should move value to a const uint... can then use window size callback. 

#ifdef DEBUG
	//POINT ERROR HANDLER HERE NOW THAT GL is setup
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	//Tell OpenGL what to do with error (send it to our function in glerror.h)
	glDebugMessageCallback(GLDebugMessageCallback, NULL);

	//get the max number of vertex attributes supported by the GPU
	//Interesting to know but we won't be bumping up against this anytime soon
	//(opengl limits this to 16 by default). 
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Max number of vertex attribs supported: " << nrAttributes << std::endl;
#endif


	//setup our shader objects
	Shader vertexshader("colorvert.shader", "colorfrag.shader");
	Shader textureshader("texvert.shader", "texfrag.shader");
	
	//activate our shaders
	vertexshader.Activate(); //glUseProgram
	textureshader.Activate();

	//initialize our renderer... eventually we will move the shader setup into this.
	Renderer renderer;
	
	


	GLOBJECT OBJECT1(Triforce, sizeof(Triforce), TriforceIndicies, sizeof(TriforceIndicies), GL_FLOAT, GL_FALSE, 2, 3, 6);
	GLOBJECT LINE(line, sizeof(line), GL_FLOAT, GL_FALSE, 1, 2, 2);


	GLOBJECT CIRCLE(CircleArray, segments * 2 * sizeof(float), CircleElements, segments * sizeof(float), GL_FLOAT, GL_FALSE, 1, 2, 2);


	renderer.Draw(OBJECT1, vertexshader, 0);
	//Testing the loading of textures. This uses our texture class to load an image with stb_img.  
	//This is a new overloaded constructor that adds the texture attribute. It just seemed like the simplest way to load the attribute at the time.
	//We confirmed that the constructor is working appropriately by testing it without the texture specified in the shader driver...
	GLOBJECT TESTOBJECT(rect, sizeof(rect), elements, sizeof(elements), GL_FLOAT, GL_FALSE, 3, 3, 8, 1);
	Texture texture("Textures/Jake_small.png");
	renderer.Draw(TESTOBJECT, textureshader, 0); // Tell our rendere class to use the texture shader for draw functions

	//inform glsl shader that we have a texture for it to use. 
	glUniform1i(glGetUniformLocation(textureshader.getID(), "texture1"), 0);
	


	
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


	float scaleAmount = 0.5f;
	bool autoScale = false;
	
	std::cout << "Entering Main Loop..." << std::endl;
	while (!glfwWindowShouldClose(window)) 
	{

		//refresh our loop variables
		float glfwTime = M_PI * sin((float)glfwGetTime());
		glfwPollEvents(); // get window events (mouse, keypress, etc...)
		float time = float(glfwGetTime());
		float greenValue = (sin(time) / 2.0f) + 0.5f;
		line[0] = 2.0 * mouseX / windowW - 1.0;
		line[1] = 1.0 - 2.0 * mouseY / windowH;

		//clear the scene
		renderer.clear(clear_color.x, clear_color.y, clear_color.z, clear_color.w);


		//Display ImGui stuffs
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (true)
		{
			
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Auto Scale", &autoScale);      // Edit bools storing our window open/close state
			ImGui::SliderFloat("Scale", &scaleAmount, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SliderFloat("Rotation", &glfwTime, M_PI, M_PI);           // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*) & clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);
			ImGui::Text("Scale = %d", scaleAmount);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			
			ImVec2 tableEdge(0, 0);
			ImGui::BeginTable("Table1", 2, 0, tableEdge, 0);
			ImGui::TableSetupColumn("X Coordinate");
			ImGui::TableSetupColumn("Y Coordinate");
			ImGui::TableHeadersRow();


			for (int i = 0; i < segments * 2; i += 2)
			{
				ImGui::TableNextColumn();
				ImGui::Text("%f", CircleArray[i]);
				ImGui::TableNextColumn();
				ImGui::Text("%f", CircleArray[i+1]);


			}
			ImGui::EndTable();
			ImGui::End();
		}





		

		textureshader.Activate(); //glUseProgram//GLCall(glActiveTexture(GL_TEXTURE0));

		glm::mat4 trans = glm::mat4(1.0f); //Initialize our translation identity matrix (diagonal 1's)
		//rotate and scale the matrix. 	
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, glfwTime, glm::vec3(0.0f, 0.0f, 1.0f));
		
		trans = glm::scale(trans, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
		//Get the "transform" uniform location from the 'textureshader' shader program (see vert shader)
		unsigned int transformLoc = glGetUniformLocation(textureshader.getID(), "transform");
		//send the matrix data to the shader.
		GLCall(glUniformMatrix4fv(
			transformLoc,			//Uniform location (grabbed from above)
			1,						//Tell Opengl how man y matricies we'd like to send
			GL_FALSE,				//Do we want to transpose the matrix (swap cols and rows)?
			glm::value_ptr(trans)	//send the data to shader
		));


		//update specific shader uniforms
		//vertexColorLocation = glGetUniformLocation(shaderProgram.getID(), "ourColor"); //cycle green
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		texture.Bind();
		renderer.Draw(TESTOBJECT, textureshader, 0);
		


		vertexshader.Activate();
		renderer.Draw(OBJECT1, vertexshader, 0);

		//need to update rendered to accept draw types (line vs element vs array). 
		LINE.Bind();
		LINE.Update(line, sizeof(line), 1, 2, 2);
		glDrawArrays(GL_LINES, 0, 2);
		LINE.Unbind();

		CIRCLE.Bind();
		renderer.Draw(CIRCLE, vertexshader, 1);
		//glDrawArrays(GL_LINES, 0, segments );
		CIRCLE.Unbind();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);


	}


	OBJECT1.Delete();
	LINE.Delete();
	TESTOBJECT.Delete();
	CIRCLE.Delete();

	std::cout << "STOPPING... Cleanup starting..." << std::endl;
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	//broken for some reason
	vertexshader.Delete();
	textureshader.Delete();
	
	std::cout << "Goodbye world!";

	return 0;

}



// need to mobe this to Callbacks.h
static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos) {

	//std::cout << xPos << " : " << yPos << std::endl;
	mouseX = xPos;
	mouseY = yPos;


}