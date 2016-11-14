

//#include "gloc/core/util/dcg/dcg.hpp"


#include "main.hpp"

#include "gloam/gloam.hpp"

//#include <GLFW/glfw3.h>

#include "Glew.hpp"
#include "Glfw.hpp"
/*
#include "gloc/gloc.hpp"

using namespace glob;//global namespace for current project
using namespace gloc;*/

using namespace glob;


int main(){
	Glfw::init();
	GLFWwindow* win = glfwCreateWindow(640, 480, "title", NULL, NULL);
	Glew::init(win);
	//
	gloam::Context context;
	context.capabilities.DEPTH_TEST->set(true);
	context.capabilities.DEBUG_OUTPUT->set(true);
	context.defaultFramebuffer.setClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//
	//note:
	while(! glfwWindowShouldClose(win)){
		context.defaultFramebuffer.clear();
		//
		//put code for drawing objects here
		//
		glfwSwapBuffers(win);
		glfwPollEvents();
	}
}


















































































/*
   
   
   
void triangle();
void boringTriangle();
void diamondVAO();
void lambertVAO();

   
   
   
   
   
   
   
   
   
   
   
   
   
   void lambertVAO(){
	Context context;
	ShaderGroup shaders(
		context.targets.programTarget,
		"res/basicShader",
		"res/basicShader_noTexture"
	);
	//
	Scene scene(context, shaders, "res/monkey3.obj");
	//aiScene* scene = loadScene("res/monkey3.obj");
	//aiScene* scene = loadScene("res/testBoxNoUV.obj");
	//assert(scene->mNumMeshes > 0);
	//
	s_ptr<FileTex2D> bricksTex(new FileTex2D(context, "res/bricks.jpg", false));
	//bricksTex.bind();
	//
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	//
	Camera cam(
		1.33f, 
		make_shared<Transform>(
			vec3(0.0f, 0.0f, -10.0f), 
			make_shared<QuatRot>(),
			vec3(1.0f, 1.0f, 1.0f)
		),
		false
	);
	//
	shaders.basic->bind();
	shaders.basic->update();//light direction
	shaders.basic->update(cam);//camera
	//
	shaders.texture->bind();
	shaders.texture->update();//light direction
	shaders.texture->update(cam);//camera
	//
	bricksTex->bind();
	//shaders.texture->bind();
	//
	//shaders.basic->bind();
	//
	assert(scene.meshes.size() > 0);
	scene.root = make_shared<SceneObject>(
		shaders,
		make_shared<Transform>(
			vec3(0.0f, 0.0f, -5.0f), 
			make_shared<QuatRot>(angleAxis(0.5f, vec3(0.0f, 1.0f, 0.0f))),
			vec3(1.0f, 1.0f, 1.0f)
		),
		bricksTex,
		//s_ptr<Texture2D>(),
		vector<w_ptr<Mesh>>{
			scene.meshes[0]
		},
		context
	);
	//scene.root->drawUntextured();
	scene.root->drawTextured();
}









class TestClass{
int n;
public:
	TestClass(){n = -1;}
	~TestClass(){
		dcg::pause();
	}
};

void diamondVAO(){
    const GLfloat diamond[4][2] = {
    {  0.0,  1.0  },
    {  1.0,  0.0  },
    {  0.0, -1.0  },
    { -1.0,  0.0  } };
	//
    const GLfloat colors[4][3] = {
    {  1.0,  0.0,  0.0  },
    {  0.0,  1.0,  0.0  },
    {  0.0,  0.0,  1.0  },
    {  1.0,  1.0,  1.0  } }; 
	//
	//s_ptr<TestClass> t = make_shared<TestClass>();
	//s_ptr<TestClass> t(new TestClass());
	//TestClass t2();
	//
	Shader shader(
		"res/tutorial2", 
		vector<Shader::NamedAttrib>({
			Shader::NamedAttrib("position", 2, GL_FLOAT, GL_TRUE), 
			Shader::NamedAttrib("texCoord", 3, GL_FLOAT, GL_TRUE), 
		}),
		vector<string>()
	);
	//
	s_ptr<VBO_Single> vbo0(new VBO_Single(
		DArray((byte_t*) diamond, 2*sizeof(GLfloat), 4),
		BufferType::STATIC
	));
	s_ptr<VBO_Single> vbo1(new VBO_Single(
		DArray((byte_t*) colors, 3*sizeof(GLfloat), 4),
		BufferType::STATIC
	));
	VAO vao(
		vector<s_ptr<AttribBinding>>({
			s_ptr<AttribBinding_Single>(new AttribBinding_Single(
				shader.getAttrib(0),
				vbo0
			)),
			s_ptr<AttribBinding_Single>(new AttribBinding_Single(
				shader.getAttrib(1),
				vbo1
			))
		}),
		make_shared<IBO>(
			s_ptr<vector<uint>>(new vector<uint>{0, 1, 2, 0, 2, 3}),
			BufferType::STATIC
		)
	);
    //
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	//
	shader.bind();
	vao.draw();
	shader.unbind();
}*/




/*void triangle(){
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
	   -1.0f, -1.0f, 0.0f,
	   1.0f, -1.0f, 0.0f,
	   0.0f,  1.0f, 0.0f,
	};

	
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);
}

void boringTriangle(){
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
	   -1.0f, -1.0f, 0.0f,
	   1.0f, -1.0f, 0.0f,
	   0.0f,  1.0f, 0.0f,
	};

	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
	   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	   3,                  // size
	   GL_FLOAT,           // type
	   GL_FALSE,           // normalized?
	   0,                  // stride
	   (void*)0            // array buffer offset
	);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);
}*/



/*vector<uint> getIndices(aiMesh* mesh){
	vector<uint> results(mesh->mNumFaces);
	for(int i = 0; i < mesh->mNumFaces; i++){
		assert(mesh->mFaces[i].mNumIndices == 3);
		for(int j = 0; j < 3; j++){
			results.push_back((uint) mesh->mFaces[i].mIndices[j]);
		}
	}
	return(results);
}*/












/*
   
   
	GLFWwindow* window;
    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    //gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	dcg::Glew::init();
    glfwSwapInterval(1);
    // NOTE: OpenGL error checks have been omitted for brevity
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 5, (void*) 0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 5, (void*) (sizeof(float) * 2));
    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        mat4x4 m, p, mvp;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
		vector<GLfloat> mvpV{1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
		//m = (1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
		//mat4x4_identity(m);
        //mat4x4_rotate_Z(m, m, (float) glfwGetTime());
        //mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        //mat4x4_mul(mvp, p, m);
        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, mvpV.data());
        //glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
   
   
   
   Mesh* mesh = new Mesh(
		(vec3 *) scene->mMeshes[0]->mVertices,
		meshTexCoords2D(scene->mMeshes[0]),
		(vec3 *) scene->mMeshes[0]->mNormals,
		scene->mMeshes[0]->mNumVertices,
		getIndices(scene->mMeshes[0]),
		BOT_DYNAMIC, BOT_STATIC_INTERLEAVED, BOT_STATIC_INTERLEAVED, BOT_STATIC
	);
	//
	SceneObject obj(
		"foo",
		TransRot(),
		new LambertBasicShader(),
		NULL,
		vector<Mesh*>{mesh}
	);
   
   
   
   
   
   
   
   Mesh* monkey2 = new Mesh(
		monkey->mVertices,
		NULL,
		monkey->mNormals,
		monkey->mNumVertices,
		vector<uint>(monkey->mFaces, monkey->mNumFaces)
	);
   
   
   
   
   
   
   
   
   
   int order = 66;
std::vector<int> v{0, 1, 2};
for(auto e : v){
std::cout << e+order << std::endl;
}*/

/*
using namespace std;
//using namespace glm;
using namespace Assimp;
using namespace dcg;
using namespace dcg::gui;
using namespace dcg::hashing;

const string MODELS_PATH = "res\\";
const string OUT_OF_MEMORY = "out of memory.";
string workingDirectory;
//
//aiScene* scene;
//
//todo: grouping objects together by: [shader][texture][mesh] would probably minimize api calls, increacing performance.
//unordered_map<Mesh, list<SceneObject>>
//unordered_map<Texture, list<SceneObject>> textureGroups;
//
static float deltaTime;
//double mouseX, mouseY;
//
list<Camera*> cameras;

//global non-static data
unsigned short frameNumber = 0;//reset every 3 frames, {0, 1, 2};*/
















/*// Demonstrate using callbacks to draw into overlays -erco 8/23/06
#include <stdlib.h>
#include <vector>
#include <FL/Fl.H>
#include <FL/Fl_Overlay_Window.H>
#include <FL/Fl_Group.H>
#include <FL/fl_draw.H>

using namespace std;

typedef void (OverlayCallback)(void*);

class MyOverlayWindow : public Fl_Overlay_Window {
    vector<OverlayCallback*> oly_callbacks;    // array of child callbacks to draw overlays
    vector<void*> oly_data;                    // array of child userdata
public:
    MyOverlayWindow(int W,int H,const char*L=0):Fl_Overlay_Window(W,H,L) {
    }
    // SETUP AN OVERLAY DRAWING CALLBACK
    //     Called by child widgets to arrange callback to draw into overlay plane.
    //
    void AddOverlayCallback(OverlayCallback *cb, void *data) {
        oly_callbacks.push_back(cb);        // add callback to array
        oly_data.push_back(data);           // add userdata to array
    }
    // INVOKE CHILDREN'S CALLBACKS TO DRAW OVERLAYS
    void draw_overlay() {
        // Invoke all the children's overlay callbacks
        //for ( uint t=0; t<oly_callbacks.size(); t++ ) {
        //    (*oly_callbacks[t])(oly_data[t]);
        //}
        fl_color(rand() % 8);
        fl_line(0, 0,        80, 80);
        fl_line(0, 80, 80, 0);
    }

protected:
	//void draw(){
		//Fl_Overlay_Window::draw();
	//	fl_rect(0, 0, 100, 100, FL_GREEN);
	//}
};

class MyGroup : public Fl_Group {
    MyOverlayWindow *oly;

    // DRAW THE OVERLAY GRAPHIC FOR THIS INSTANCE OF CHILD
    static void OverlayCallback(void *data) {
        MyGroup *o = (MyGroup*)data;
        // Draw a random colored 'x'
        fl_color(rand() % 8);
        fl_line(o->x(), o->y(),        o->x()+o->w(), o->y()+o->h());
        fl_line(o->x(), o->y()+o->h(), o->x()+o->w(), o->y());
    }
public:
    MyGroup(MyOverlayWindow *win,int X,int Y,int W,int H,const char*L=0):Fl_Group(X,Y,W,H,L) {
        oly = win;
        win->AddOverlayCallback(OverlayCallback, (void*)this);
        end();
    }
    void draw() {
        Fl_Group::draw();
		//fl_rectf(0, 0, 200, 200, 50, 50, 50);
		fl_rectf(x(), y(), w(), h(), rand() % 255, rand() % 255, rand() % 255);
        oly->redraw_overlay();          // tell parent to redraw child overlays
    }
};

int main(int argc, char **argv) {
    // Create overlay window
    MyOverlayWindow win(400,400);
    // Create four child groups, each with its own overlay graphic
    MyGroup g1(&win, 0,  0,  200,200);
    MyGroup g2(&win, 200,0,  200,200);
    MyGroup g3(&win, 0,  200,200,200);
    MyGroup g4(&win, 200,200,200,200);
	//
	//
    win.end();
    win.resizable(win);
    win.show();
    return(Fl::run());
}*/














/*#include <stdlib.h>
#include <vector>
#include <FL/Fl.H>
#include <FL/Fl_Overlay_Window.H>
#include <FL/Fl_Group.H>
#include <FL/fl_draw.H>

//AUTOGENERATED_TEXT_75206455E9C4A819_START
//AUTOGENERATED_TEXT_75206455E9C4A819_END

using namespace std;

typedef void (OverlayCallback)(void*);

class MyOverlayWindow : public Fl_Window{
    vector<OverlayCallback*> oly_callbacks;    // array of child callbacks to draw overlays
    vector<void*> oly_data;                    // array of child userdata
public:
    MyOverlayWindow(int W,int H,const char*L=0):Fl_Window(W,H,L) {}

protected:
	void draw(){
		Fl_Window::draw();
		fl_rectf(0, 0, 100, 100, 0, 255, 0);
	}
};

class MyGroup : public Fl_Window {
    MyOverlayWindow *oly;

    // DRAW THE OVERLAY GRAPHIC FOR THIS INSTANCE OF CHILD
    static void OverlayCallback(void *data) {
        MyGroup *o = (MyGroup*)data;
        // Draw a random colored 'x'
        fl_color(rand() % 8);
        fl_line(o->x(), o->y(),        o->x()+o->w(), o->y()+o->h());
        fl_line(o->x(), o->y()+o->h(), o->x()+o->w(), o->y());
    }
public:
    MyGroup(MyOverlayWindow *win,int X,int Y,int W,int H,const char*L=0):Fl_Window(X,Y,W,H,L) {
        oly = win;
        end();
    }
    void draw() {
        Fl_Group::draw();
		//fl_rectf(0, 0, 200, 200, 50, 50, 50);
		fl_rectf(x(), y(), w(), h(), rand() % 255, rand() % 255, rand() % 255);
    }
};

int main(int argc, char **argv) {
    // Create overlay window
    MyOverlayWindow win(400,400);
    // Create four child groups, each with its own overlay graphic
    MyGroup g1(&win, 0,  0,  200,200);
    MyGroup g2(&win, 200,0,  200,200);
    MyGroup g3(&win, 0,  200,200,200);
    MyGroup g4(&win, 200,200,200,200);
	//
	//
    win.end();
    win.resizable(win);
    win.show();
    return(Fl::run());
}*/






















/*getWorkingDirectory(argv[0]);
//
Fl_Window* wnd0 = new Fl_Window(900, 900);
GlWindow* glWnd0 = new GlWindow(800, 800);
Fl_Window* wnd1 = new Fl_Window(700, 700);
GlWindow* glWnd1 = new GlWindow(600, 600);
//
wnd0->add(glWnd0);
wnd0->show();
glWnd0->show();
wnd1->add(glWnd1);
wnd1->show();
glWnd1->show();
//
//glWnd0->show();
//glWnd1->show();
glWnd0->make_current();
glWnd1->make_current();
glWnd1->context(glWnd0->context());*/

/*
glWnd0->show();
glWnd1->show();
glWnd0->make_current();
glWnd1->make_current();
//GetDC(glWnd0->cont
glWnd1->context(glWnd0->context());
*/





/*Fl_Window* mainWindow = new Fl_Window(1600, 900, "main window");
GlWindow* glWnd = new GlWindow(800, 800);
mainWindow->add(glWnd);
mainWindow->show();
glWnd->show();*/


/*static void buttonCallback(Fl_Widget* o, void* data);
static void buttonCallback(Fl_Widget* o, void* data){
	Fl_Button* b = (Fl_Button*) o;
	//
	b->label("Good Job");
	b->resize(10, 150, 140, 30);
	b->redraw();
}*/


/*
getWorkingDirectory(argv[0]);
	Fl_Window* mainWindow = new Fl_Window(1600, 900, "main window");
	mainWindow->begin();
	GlWindow* glWnd = new GlWindow(800, 800, "gl window");
	mainWindow->add(glWnd);
	mainWindow->show();
	glWnd->show();
	return(Fl::run());
*/

/*fl_color(255, 0, 0);
//
Fl_Window win(300, 200, "Testing");
win.color(FL_RED);
win.resizable();
win.begin();
Fl_Button but(10, 150, 70, 30, "click me");
but.color(fl_rgb_color(255, 0, 0));
win.end();
//
but.callback(buttonCallback);
fl_color(255, 0, 0);
win.show();
fl_color(255, 0, 0);*/



/*long* num1 = new long(1);
	long* num2 = new long(2);
	long* num3 = new long(3);
	long* num4 = new long(4);
	long* num5 = new long(5);
	long* num6 = new long(6);
	long* num7 = new long(7);
	long* num8 = new long(8);
	long* num9 = new long(9);
	LinkedHashTable<long*, ptrHasher<long>> table;
	table.init(100);
	table.add(num1);
	table.add(num2);
	table.add(num3);
	table.add(num4);
	table.add(num5);
	table.add(num6);
	table.add(num7);
	table.add(num8);
	table.add(num9);
	cout << table.toString();
	system("pause");*/


//
/*int* num1 = new int(1);
int* num2 = new int(2);
int* num3 = new int(3);
Array<list<int*>> nums;
nums.resize(100);
nums[36].push_back(num1);
cout << **(nums[36].begin());
system("pause");*/
//
/*int* num1 = new int(1);
int* num2 = new int(2);
int* num3 = new int(3);
Array<string> s;
s.resize(100);
s[36] = "d";
s[37] += "c";
s[37] += " e";
cout << s.toString(true);
Array<list<int*>*> nums;
nums.resize(100);
nums[36] = new list<int*>();
nums[36]->push_back(num1);
//Array<list<int*>> numArr;
//Array<int*> numArr2;
//numArr.resize(100);
//numArr2.resize(100);
//list<int*> l;
//l.push_back(num1);
//numArr[36] = list<int*>();
//numArr2[36] = num1;
//numArr[36] = l;
//cout << numArr[0].size();
//numArr[0].push_back(num1);
system("pause");*/







































/*class Test : dcg::range_vector_t<int> {
private:
	vector<int> data;

public:
	Test(){
		data = vector<int>{1, 2, 3};
	}

	std::vector<int>::iterator begin(){
		return(data.begin());
	}

	std::vector<int>::iterator end(){
		return(data.end());
	}
};

int main(){
	Test nums;
	for(int num : nums){
		std::cout << num << endl;
	}
}*/

//AUTOGENERATED_TEXT_75206455E9C4A819_START
/*No Message
*/
//AUTOGENERATED_TEXT_75206455E9C4A819_END
