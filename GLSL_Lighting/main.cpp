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
#include <FreeImage.h>//*** Para Textura: Incluir librer�a


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
   GLMmodel* objmodel_ptr6;
   //IDENTIFICADORES PARA LAS TEXTURAS USADAS EN LOS MODELOS
   GLuint texid;
   GLuint texid2;
   GLuint texid3;
   GLuint texid4;
   GLuint texid5;
   //VARIABLES PARA EL MOVIMIENTO DE LA C�MARA.
   float camX, camY, camZ;
   bool moveXD, moveXI, moveYU, moveYD, moveZD, moveZA;
   //VARIABLES PARA EL MOVIMIENTO DEL TALADRO.
   float taladroX, taladroY, taladroZ;
   bool movTaladroXD, movTaladroXI, movTaladroYU, movTaladroYD, movTaladroZD, movTaladroZA;

public:
	myWindow(){}
    //FUNCI�N PARA MOVIMIENTO DE LA C�MARA EN EJES X, Y, Z
    void movimientoCamara() 
    {
        if (moveXI == true)
        {
            camX = camX + 0.1;
        }

        if (moveXD == true)
        {
            camX = camX - 0.1;
        }

        if (moveYU == true)
        {
            camY = camY - 0.1;
        }

        if (moveYD == true)
        {
            camY = camY + 0.1;
        }

        if (moveZD == true)
        {
            camZ = camZ + 0.1;
        }

        if (moveZA == true)
        {
            camZ = camZ - 0.1;
        }

        glTranslatef(camX, camY, camZ);
    }

    void movimientoTaladro()
    {
        if (movTaladroXI == true)
        {
            taladroX = taladroX - 0.1;
        }

        if (movTaladroXD == true)
        {
            taladroX = taladroX + 0.1;
        }

        if (movTaladroYU == true)
        {
            taladroY = taladroY + 0.1;
        }

        if (movTaladroYD == true)
        {
            taladroY = taladroY - 0.1;
        }

        if (movTaladroZD == true)
        {
            taladroZ = taladroZ + 0.1;
        }

        if (movTaladroZA == true)
        {
            taladroZ = taladroZ - 0.1;
        }

        //glTranslatef(camX, camY, camZ);
    }

    //PARA PODER LEER LAS TEXTURAS DE LOS ARCHIVOS JPG, SE DECIDI� IMPLEMENTAR UNA MEDIDA QUE SE CONSIDERA TEMPORAL Y ES CREAR UNA FUNCI�N PARA CADA TEXTURA.
    //ESTA DECISI�N SE TOM� PORQUE LO PRINCIPAL ES VER EL ASPECTO DEL PROYECTO USANDO TEXTURAS, VER C�MO SE COMPORTAN Y SI QUEDAN BIEN.

    //FUNCI�N DONDE SE LEE LA TEXTURA PARA EL TALADRO, ESTE SER�A EL ELEMENTO ARTIFICIAL QUE SE PIDE EN LA ENTREGA.
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

    //FUNCI�N DONDE SE LEE LA TEXTURA PARA LOS �RBOLES, ESTE SER�A EL ELEMENTO NATURAL QUE PIDE LA ENTREGA.
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

    //FUNCI�N DONDE SE LEE LA TEXTURA PARA LAS CASAS, ESTE SER�A EL ELEMENTO CREADO POR LA TRIBU CON TEXTURA.
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

    //FUNCI�N DONDE SE LEE LA TEXTURA DE LOS EDIFICIOS. OTRO ELEMENTO CREADO POR LA TRIBU Y SOBRE EL CUAL SE USAN TEXTURAS.
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

    //FUNCI�N DONDE SE LEE LA TEXTURA PARA LA MINA. ESTE SER�A OTRO ELEMENTO NATURAL.
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

      //Movimiento de c�mara
      movimientoCamara();
      movimientoTaladro();
      
         //glRotatef(timer010*360, 0.5, 1.0f, 0.1f);

      //SECCI�N DONDE SE DIBUJAN LOS �RBOLES (ELEMENTO NATURAL).
      if (shader1) shader1->begin();
          glPushMatrix();      
          glTranslatef(0, 0.5, 0);
          glTranslatef(-1.6, 0, -2);
          glBindTexture(GL_TEXTURE_2D, texid2);
          //�RBOL # 1
          glmDraw(objmodel_ptr2, GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
          //�RBOL # 2
          glTranslatef(-1.5, 0, -2);
          glmDraw(objmodel_ptr2, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
          //�RBOL # 3
          glTranslatef(-1, 0, -2);
          glmDraw(objmodel_ptr2, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
          //�RBOL # 4
          glTranslatef(-1.9, 0, -2);
          glmDraw(objmodel_ptr2, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
          //�RBOL # 5
          glTranslatef(-1.8, 0, -1.5);
          glmDraw(objmodel_ptr2, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
          glPopMatrix();
      if (shader1) shader1->end();

      //SECCI�N DONDE SE DIBUJA EL TALADRO, CON SU RESPECTIVO USO DE MATERIALES Y TEXTURAS.
      if (shader1) shader1->begin();
        glPushMatrix();
        glTranslatef(taladroX, taladroY, taladroZ);
        //glTranslatef(-0.5, 0.5, -0.5);
        glRotatef(140, 0, 1, 0);
        glScalef(1.5, 1.5, 1.5);
        glBindTexture(GL_TEXTURE_2D, texid);
        glmDraw(objmodel_ptr4, GLM_SMOOTH | GLM_MATERIAL| GLM_TEXTURE);
        glPopMatrix();
      if (shader1) shader1->end();

      //SECCI�N DONDE SE DIBUJAN LAS CASAS, SOBRE LAS CUALES SE APLICAN TEXTURAS.
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

      //SECCCI�N DONDE SE DIBUJAN LOS EDIFICIOS.
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

      //SECCI�N DONDE SE DIBUJA LA MINA Y SOBRE LA CUAL SE APLICAN MATERIALES Y TEXTURAS.
      if (shader1) shader1->begin();
        glTranslatef(1, -1.3, 1);
        glBindTexture(GL_TEXTURE_2D, texid5);
        glmDraw(objmodel_ptr, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
      if (shader1) shader1->end();

      //SECCI�N DONDE SE DIBUJA EL PASTO.
      if (shader1) shader1->begin();
        glTranslatef(-2, 1, 2);
        glmDraw(objmodel_ptr6, GLM_SMOOTH | GLM_MATERIAL);
        glTranslatef(0, 0,-0.5);
        glmDraw(objmodel_ptr6, GLM_SMOOTH | GLM_MATERIAL);
        glTranslatef(0, 0, -0.5);
        glmDraw(objmodel_ptr6, GLM_SMOOTH | GLM_MATERIAL);
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
        //INICIALIZACI�N DE LA VARIABLES USADAS PARA EL MOVIMIENTO DE LA C�MARA.
        camX = 0.0;
        camY = 0.0;
        camZ = 0.0;
        moveXD = false;
        moveXI = false;
        moveYU = false;
        moveYD = false;
        moveZD = false;
        moveZA = false;
        //INICIALIZACI�N DE LAS VARIABLES USADAS PARA EL MOVIMIENTO DEL TALADRO.
        taladroX = -0.5;
        taladroY = 0.5;
        taladroZ = -0.5;
        movTaladroXD = false;
        movTaladroXI = false;
        movTaladroYU = false;
        movTaladroYD = false;
        movTaladroZD = false;
        movTaladroZA = false;
       
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

        //DEFINICI�N DE LAS MALLAS UTILIZADAS EN EL PROYECTO

        objmodel_ptr = NULL;
        objmodel_ptr2 = NULL;
        objmodel_ptr3 = NULL;
        objmodel_ptr4 = NULL;
        objmodel_ptr5 = NULL;
        objmodel_ptr6 = NULL;

        //ESTA SECCI�N CORRESPONDE A LA DEFINICI�N DE LA MALLA PARA LA MINA.
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

        //ESTA SECCI�N CORRESPONDE A LA DEFINICI�N DE LA MALLA PARA LOS �RBOLES.
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
        //ESTA SECCI�N CORRESPONDE A LA DEFINICI�N DE LA MALLA PARA LAS CASAS.
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

        //ESTA SECCI�N CORRESPONDE A LA DEFINICI�N DE LA MALLA PARA EL TALADRO
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
        

        //ESTA SECCI�N CORRESPONDE A LA DEFINICI�N DE LA MALLA PARA LOS EDIFICIOS.
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

        //ESTA SECCI�N CORRESPONDE A LA DEFINICI�N DEL PASTO COMO ELEMENTO REALISTA ADICIONAL.
        if (!objmodel_ptr6)
        {
            objmodel_ptr6 = glmReadOBJ("./models/pasto.obj");
            if (!objmodel_ptr6)
                exit(0);

            glTranslatef(1, 1, 0);

            glmUnitize(objmodel_ptr6);
            glmFacetNormals(objmodel_ptr6);
            glmVertexNormals(objmodel_ptr6, 90.0);
        }

	  //LLAMADOS A TODAS LAS FUNCIONES NECESARIAS PARA EFECTOS DE REALISMO, ES DECIR, TEXTURAS E ILUMUNACI�N.  	
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
        else if (cAscii == 'a')
        {
            moveXI = true;
        }

        else if (cAscii == 'd') 
        {
            moveXD = true;
        }
        
        else if (cAscii == 'w') 
        {
            moveYU = true;
        }

        else if (cAscii == 's') 
        {
            moveYD = true;
        }

        else if (cAscii == 'o')
        {
            moveZD = true;
        }

        else if (cAscii == 'l')
        {
            moveZA = true;
        }

        else if (cAscii == 'h')
        {
            movTaladroXI = true;
        }

        else if (cAscii == 'k')
        {
            movTaladroXD = true;
        }

        else if (cAscii == 'u')
        {
            movTaladroYU = true;
        }

        else if (cAscii == 'j')
        {
            movTaladroYD = true;
        }

        else if (cAscii == 't')
        {
            movTaladroZD = true;
        }

        else if (cAscii == 'g')
        {
            movTaladroZA = true;
        }
	};

	virtual void OnKeyUp(int nKey, char cAscii)
	{
      if (cAscii == 'q')      // s: Shader
         shader->enable();
      else if (cAscii == 'f') // f: Fixed Function
         shader->disable();

      else if (cAscii == 'a')
      {
          moveXI = false;
      }

      else if (cAscii == 'd')
      {
          moveXD = false;
      }

      else if (cAscii == 'w')
      {
          moveYU = false;
      }

      else if (cAscii == 's')
      {
          moveYD = false;
      }

      else if (cAscii == 'o')
      {
          moveZD = false;
      }

      else if (cAscii == 'l')
      {
          moveZA = false;
      }

      else if (cAscii == 'h')
      {
          movTaladroXI = false;
      }

      else if (cAscii == 'k')
      {
          movTaladroXD = false;
      }

      else if (cAscii == 'u')
      {
          movTaladroYU = false;
      }

      else if (cAscii == 'j')
      {
          movTaladroYD = false;
      }

      else if (cAscii == 't')
      {
          movTaladroZD = false;
      }

      else if (cAscii == 'g')
      {
          movTaladroZA = false;
      }
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

