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

03/19/2022
- implemented texture class and included stb_image to load textures into memory. 
- created new overloaded globject constructor to handle textured objects. This type of GLOBJECT takes an additional texture mapping attribute from the attribute vertex and binds it to ID2.
- The overloaded constructor seems to not break anything. 
- vertex and fragment shaders are now mixing textures and vertexColors. Need to probably write two different shaders to handle different render scenarios. 


03/06/2022
- expanded GLOBJECT to manage vertex types, attribute/vertex/element count, and normal state.
- updated GLOBJECT::GLOBJECT to use object variables for glVertexAttribPointer.
- Created and implemented RENDERER class to handle clear and draw functions.
- removed old VAO, VBO, and EBO classes.


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