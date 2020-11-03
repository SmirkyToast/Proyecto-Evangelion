//=============================================================================
// Sample Application: Lighting (Per Fragment Phong)
//=============================================================================

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>
#include "glm/glm.h"
#include <FreeImage.h>//*** Para Textura: Incluir librería


//-----------------------------------------------------------------------------


class myWindow : public cwc::glutWindow
{
protected:
   cwc::glShaderManager SM;
   cwc::glShader *shader;
   cwc::glShader *shader1;
   GLuint ProgramObject;
   clock_t time0,time1;
   float timer010;  // timer counting 0->1->0
   bool bUp;        // flag if counting up or down.
   //IDENTIFICADORES PARA LOS MODELOS USADOS EN EL PROYECTO
   GLMmodel* objmodel_ptr;
   GLMmodel* objmodel_ptr2;
   GLMmodel* objmodel_ptr3;
   GLMmodel* objmodel_ptr4;
   GLMmodel* objmodel_ptr5;
   //IDENTIFICADORES PARA LAS TEXTURAS USADAS EN LOS MODELOS
   GLuint texid;
   GLuint texid2;
   GLuint texid3;
   GLuint texid4;
   GLuint texid5;


public:
	myWindow(){}

    //PARA PODER LEER LAS TEXTURAS DE LOS ARCHIVOS JPG, SE DECIDIÓ IMPLEMENTAR UNA MEDIDA QUE SE CONSIDERA TEMPORAL Y ES CREAR UNA FUNCIÓN PARA CADA TEXTURA.
    //ESTA DECISIÓN SE TOMÓ PORQUE LO PRINCIPAL ES VER EL ASPECTO DEL PROYECTO USANDO TEXTURAS, VER CÓMO SE COMPORTAN Y SI QUEDAN BIEN.

    //FUNCIÓN DONDE SE LEE LA TEXTURA PARA EL TALADRO, ESTE SERÍA EL ELEMENTO ARTIFICIAL QUE SE PIDE EN LA ENTREGA.
    void initialize_textures(void)
    {       
        GLubyte* data = 0;
        glGenTextures(1, &texid);
        glBindTexture(GL_TEXTURE_2D, texid);
        glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        // Loading JPG file
        FIBITMAP* bitmap = FreeImage_Load(
            FreeImage_GetFileType("./mallas/metal.jpg", 0),
            "./mallas/metal.jpg");  //*** Para Textura: esta es la ruta en donde se encuentra la textura

        FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
        int nWidth = FreeImage_GetWidth(pImage);
        int nHeight = FreeImage_GetHeight(pImage);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
            0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

        FreeImage_Unload(pImage);
        //
        glEnable(GL_TEXTURE_2D);
    }

    //FUNCIÓN DONDE SE LEE LA TEXTURA PARA LOS ÁRBOLES, ESTE SERÍA EL ELEMENTO NATURAL QUE PIDE LA ENTREGA.
    void initialize_textures2(void)
    {
        GLubyte* data = 0;      

        glGenTextures(1, &texid2);
        glBindTexture(GL_TEXTURE_2D, texid2);
        glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        // Loading JPG file
        FIBITMAP* bitmap = FreeImage_Load(
            FreeImage_GetFileType("./mallas/madera.jpg", 0),
            "./mallas/madera.jpg");  //*** Para Textura: esta es la ruta en donde se encuentra la textura

        FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
        int nWidth = FreeImage_GetWidth(pImage);
        int nHeight = FreeImage_GetHeight(pImage);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
            0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

        FreeImage_Unload(pImage);
        //
        glEnable(GL_TEXTURE_2D);
    }

    //FUNCIÓN DONDE SE LEE LA TEXTURA PARA LAS CASAS, ESTE SERÍA EL ELEMENTO CREADO POR LA TRIBU CON TEXTURA.
    void initialize_textures3(void)
    {
        GLubyte* data = 0;

        glGenTextures(1, &texid3);
        glBindTexture(GL_TEXTURE_2D, texid3);
        glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        // Loading JPG file
        FIBITMAP* bitmap = FreeImage_Load(
            FreeImage_GetFileType("./mallas/casat2.jpg", 0),
            "./mallas/casat2.jpg");  //*** Para Textura: esta es la ruta en donde se encuentra la textura

        FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
        int nWidth = FreeImage_GetWidth(pImage);
        int nHeight = FreeImage_GetHeight(pImage);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
            0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

        FreeImage_Unload(pImage);
        //
        glEnable(GL_TEXTURE_2D);
    }

    //FUNCIÓN DONDE SE LEE LA TEXTURA DE LOS EDIFICIOS. OTRO ELEMENTO CREADO POR LA TRIBU Y SOBRE EL CUAL SE USAN TEXTURAS.
    void initialize_textures4(void)
    {
        GLubyte* data = 0;

        glGenTextures(1, &texid4);
        glBindTexture(GL_TEXTURE_2D, texid4);
        glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        // Loading JPG file
        FIBITMAP* bitmap = FreeImage_Load(
            FreeImage_GetFileType("./mallas/edificiot.jpg", 0),
            "./mallas/edificiot.jpg");  //*** Para Textura: esta es la ruta en donde se encuentra la textura

        FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
        int nWidth = FreeImage_GetWidth(pImage);
        int nHeight = FreeImage_GetHeight(pImage);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
            0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

        FreeImage_Unload(pImage);
        //
        glEnable(GL_TEXTURE_2D);
    }

    //FUNCIÓN DONDE SE LEE LA TEXTURA PARA LA MINA. ESTE SERÍA OTRO ELEMENTO NATURAL.
    void initialize_textures5(void)
    {
        GLubyte* data = 0;

        glGenTextures(1, &texid5);
        glBindTexture(GL_TEXTURE_2D, texid5);
        glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        // Loading JPG file
        FIBITMAP* bitmap = FreeImage_Load(
            FreeImage_GetFileType("./mallas/roca.jpg", 0),
            "./mallas/roca.jpg");  //*** Para Textura: esta es la ruta en donde se encuentra la textura

        FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
        int nWidth = FreeImage_GetWidth(pImage);
        int nHeight = FreeImage_GetHeight(pImage);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
            0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

        FreeImage_Unload(pImage);
        //
        glEnable(GL_TEXTURE_2D);
    }

	virtual void OnRender(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
      //timer010 = 0.09; //for screenshot!
      glPushMatrix();
      
         //glRotatef(timer010*360, 0.5, 1.0f, 0.1f);

      //SECCIÓN DONDE SE DIBUJAN LOS ÁRBOLES (ELEMENTO NATURAL).
      if (shader1) shader1->begin();
          glPushMatrix();      
          glTranslatef(0, 0.5, 0);
          glTranslatef(-1.6, 0, -2);
          glBindTexture(GL_TEXTURE_2D, texid2);
          //ÁRBOL # 1
          glmDraw(objmodel_ptr2, GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
          //ÁRBOL # 2
          glTranslatef(-1.5, 0, -2);
          glmDraw(objmodel_ptr2, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
          //ÁRBOL # 3
          glTranslatef(-1, 0, -2);
          glmDraw(objmodel_ptr2, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
          //ÁRBOL # 4
          glTranslatef(-1.9, 0, -2);
          glmDraw(objmodel_ptr2, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
          //ÁRBOL # 5
          glTranslatef(-1.8, 0, -1.5);
          glmDraw(objmodel_ptr2, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
          glPopMatrix();
      if (shader1) shader1->end();

      //SECCIÓN DONDE SE DIBUJA EL TALADRO, CON SU RESPECTIVO USO DE MATERIALES Y TEXTURAS.
      if (shader1) shader1->begin();
        glPushMatrix();
        glTranslatef(-0.5, 0.5, -0.5);
        glRotatef(140, 0, 1, 0);
        glScalef(1.5, 1.5, 1.5);
        glBindTexture(GL_TEXTURE_2D, texid);
        glmDraw(objmodel_ptr4, GLM_SMOOTH | GLM_MATERIAL| GLM_TEXTURE);
        glPopMatrix();
      if (shader1) shader1->end();

      //SECCIÓN DONDE SE DIBUJAN LAS CASAS, SOBRE LAS CUALES SE APLICAN TEXTURAS.
      if (shader1) shader1->begin();
        glPushMatrix();
      //CASAS
        glTranslatef(0, 0, 0);
        glTranslatef(3, 0, -8);
        glBindTexture(GL_TEXTURE_2D, texid3);
        glmDraw(objmodel_ptr3, GLM_SMOOTH | GLM_TEXTURE);
        glTranslatef(5, 0, -8);
        glmDraw(objmodel_ptr3, GLM_SMOOTH | GLM_TEXTURE);
        glTranslatef(-4, 0, -8);
        glmDraw(objmodel_ptr3, GLM_SMOOTH | GLM_TEXTURE);
        glTranslatef(3, 0, -8);
        glmDraw(objmodel_ptr3, GLM_SMOOTH | GLM_TEXTURE);
        glPopMatrix();
      if (shader1) shader1->end();

      //SECCCIÓN DONDE SE DIBUJAN LOS EDIFICIOS.
      if (shader1) shader1->begin();
        glPushMatrix();
        glTranslatef(5, 0, -8);
        glBindTexture(GL_TEXTURE_2D, texid4);
        glmDraw(objmodel_ptr5, GLM_SMOOTH | GLM_TEXTURE);
        glTranslatef(-2, 0, -3);
        glmDraw(objmodel_ptr5, GLM_SMOOTH | GLM_TEXTURE);
        glTranslatef(4, 0, -6);
        glmDraw(objmodel_ptr5, GLM_SMOOTH | GLM_TEXTURE);
        glPopMatrix();
      if (shader1) shader1->end();

      //SECCIÓN DONDE SE DIBUJA LA MINA Y SOBRE LA CUAL SE APLICAN MATERIALES Y TEXTURAS.
      if (shader1) shader1->begin();
        glTranslatef(1, -1.3, 1);
        glBindTexture(GL_TEXTURE_2D, texid5);
        glmDraw(objmodel_ptr, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);      
      if (shader1) shader1->end();      
     
      glutSwapBuffers();
      glPopMatrix();

      UpdateTimer();

		Repaint();
	}

	virtual void OnIdle() {}

	// When OnInit is called, a render context (in this case GLUT-Window) 
	// is already available!
	virtual void OnInit()
	{
		glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
        //texturas
        shader = SM.loadfromFile("vertexshader.txt", "fragmentshader.txt"); // load (and compile, link) from file
        if (shader == 0)
            std::cout << "Error Loading, compiling or linking shader\n";
        else
        {
            ProgramObject = shader->GetProgramObject();
        }
        shader1 = SM.loadfromFile("vertexshaderT.txt", "fragmentshaderT.txt"); // load (and compile, link) from file
        if (shader1 == 0)
            std::cout << "Error Loading, compiling or linking shader1\n";
        else
        {
            ProgramObject = shader1->GetProgramObject();
        }

        time0 = clock();
        timer010 = 0.0f;
        bUp = true;

        //DEFINICIÓN DE LAS MALLAS UTILIZADAS EN EL PROYECTO

        objmodel_ptr = NULL;
        objmodel_ptr2 = NULL;
        objmodel_ptr3 = NULL;
        objmodel_ptr4 = NULL;
        objmodel_ptr5 = NULL;        

        //ESTA SECCIÓN CORRESPONDE A LA DEFINICIÓN DE LA MALLA PARA LA MINA.
        if (!objmodel_ptr)
        {
            objmodel_ptr = glmReadOBJ("./models/mina.obj");
            if (!objmodel_ptr)
                exit(0);
            
            glTranslatef(-1, -1, 0);
            glmUnitize(objmodel_ptr);
            glmFacetNormals(objmodel_ptr);
            glmVertexNormals(objmodel_ptr, 90.0);
        }

        //ESTA SECCIÓN CORRESPONDE A LA DEFINICIÓN DE LA MALLA PARA LOS ÁRBOLES.
        if (!objmodel_ptr2)
        {
            objmodel_ptr2 = glmReadOBJ("./models/arbolarreglado.obj");
            if (!objmodel_ptr2)
                exit(0);
            
            glTranslatef(1, 1, 0);
            
            glmUnitize(objmodel_ptr2);
            glmFacetNormals(objmodel_ptr2);
            glmVertexNormals(objmodel_ptr2, 90.0);
        }
        //ESTA SECCIÓN CORRESPONDE A LA DEFINICIÓN DE LA MALLA PARA LAS CASAS.
        if (!objmodel_ptr3)
        {
            objmodel_ptr3 = glmReadOBJ("./models/casa.obj");
            if (!objmodel_ptr3)
                exit(0);

            glTranslatef(1, 1, 0);

            glmUnitize(objmodel_ptr3);
            glmFacetNormals(objmodel_ptr3);
            glmVertexNormals(objmodel_ptr3, 90.0);
        }

        //ESTA SECCIÓN CORRESPONDE A LA DEFINICIÓN DE LA MALLA PARA EL TALADRO
        if (!objmodel_ptr4)
        {
            objmodel_ptr4 = glmReadOBJ("./models/drill.obj");
            if (!objmodel_ptr4)
                exit(0);

            glTranslatef(1, 1, 0);

            glmUnitize(objmodel_ptr4);
            glmFacetNormals(objmodel_ptr4);
            glmVertexNormals(objmodel_ptr4, 90.0);
        }
        

        //ESTA SECCIÓN CORRESPONDE A LA DEFINICIÓN DE LA MALLA PARA LOS EDIFICIOS.
        if (!objmodel_ptr5)
        {
            objmodel_ptr5 = glmReadOBJ("./models/Edificio.obj");
            if (!objmodel_ptr5)
                exit(0);

            glTranslatef(1, 1, 0);

            glmUnitize(objmodel_ptr5);
            glmFacetNormals(objmodel_ptr5);
            glmVertexNormals(objmodel_ptr5, 90.0);
        }

	  //LLAMADOS A TODAS LAS FUNCIONES NECESARIAS PARA EFECTOS DE REALISMO, ES DECIR, TEXTURAS E ILUMUNACIÓN.  	
      initialize_textures();
      initialize_textures2();
      initialize_textures3();
      initialize_textures4();
      initialize_textures5();
      DemoLight();
	}

	virtual void OnResize(int w, int h)
   {
      if(h == 0) h = 1;
	   float ratio = 1.0f * (float)w / (float)h;

      glMatrixMode(GL_PROJECTION);
	   glLoadIdentity();
	
	   glViewport(0, 0, w, h);

      gluPerspective(45,ratio,1,100); //Cono de visibilidad
	   glMatrixMode(GL_MODELVIEW);
	   glLoadIdentity();
	   gluLookAt(0.0f,0.0f,4.0f, 
		          0.0,0.0,-1.0,
			       0.0f,1.0f,0.0f);
   }
	virtual void OnClose(void){}
	virtual void OnMouseDown(int button, int x, int y) {}    
	virtual void OnMouseUp(int button, int x, int y) {}
	virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y){}

	virtual void OnKeyDown(int nKey, char cAscii)
	{       
		if (cAscii == 27) // 0x1b = ESC
		{
			this->Close(); // Close Window!
		} 
	};

	virtual void OnKeyUp(int nKey, char cAscii)
	{
      if (cAscii == 's')      // s: Shader
         shader->enable();
      else if (cAscii == 'f') // f: Fixed Function
         shader->disable();
	}

   void UpdateTimer()
   {
      time1 = clock();
      float delta = static_cast<float>(static_cast<double>(time1-time0)/static_cast<double>(CLOCKS_PER_SEC));
      delta = delta / 4;
      if (delta > 0.00005f)
      {
         time0 = clock();
         if (bUp)
         {
            timer010 += delta;
            if (timer010>=1.0f) { timer010 = 1.0f; bUp = false;}
         }
         else
         {
            timer010 -= delta;
            if (timer010<=0.0f) { timer010 = 0.0f; bUp = true;}
         }
      }
   }

   void DemoLight(void)
   {
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glEnable(GL_NORMALIZE);
     
     // Light model parameters:
     // -------------------------------------------
     /**/
     /*GLfloat lmKa[] = {0.0, 0.0, 0.0, 0.0 };
     glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);
     
     glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
     glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
     
     // -------------------------------------------
     // Spotlight Attenuation
     
     GLfloat spot_direction[] = {1.0, -1.0, -1.0 };
     GLint spot_exponent = 30;
     GLint spot_cutoff = 180;
     
     glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
     glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
     glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);
    
     GLfloat Kc = 1.0;
     GLfloat Kl = 0.0;
     GLfloat Kq = 0.0;
     
     glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,Kc);
     glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
     glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);
    
     
     // ------------------------------------------- 
     // Lighting parameters:

     GLfloat light_pos[] = {0.0f, 5.0f, 5.0f, 1.0f};
     GLfloat light_Ka[]  = {1.0f, 0.5f, 0.5f, 1.0f};
     GLfloat light_Kd[]  = {1.0f, 0.1f, 0.1f, 1.0f};
     GLfloat light_Ks[]  = {1.0f, 1.0f, 1.0f, 1.0f};
    /*
     glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
     glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
     glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
     glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);
     */
     // -------------------------------------------
     // Material parameters:

     //GLfloat material_Ka[] = {0.5f, 0.0f, 0.0f, 1.0f};
     //GLfloat material_Kd[] = {0.4f, 0.4f, 0.5f, 1.0f};
     //GLfloat material_Ks[] = {0.8f, 0.8f, 0.0f, 1.0f};
     //GLfloat material_Ke[] = {0.1f, 0.0f, 0.0f, 0.0f};
     //GLfloat material_Se = 20.0f;
     
     /*
     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
     glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
     glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
     */
   }
};

//-----------------------------------------------------------------------------

class myApplication : public cwc::glApplication
{
public:
	virtual void OnInit() {std::cout << "Hello World!\n"; }
};

//-----------------------------------------------------------------------------

int main(void)
{
	myApplication*  pApp = new myApplication;
	myWindow* myWin = new myWindow();

	pApp->run();
	delete pApp;
	return 0;
}

//-----------------------------------------------------------------------------

