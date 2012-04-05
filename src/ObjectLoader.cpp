#include "ObjectLoader.h"

void ErrCheck(char* where)
{
   int err = glGetError();
   if (err) fprintf(stderr,"ERROR: %s [%s]\n",gluErrorString(err),where);
}

void Fatal(const char* format , ...)
{
   va_list args;
   va_start(args,format);
   vfprintf(stderr,format,args);
   va_end(args);
   exit(1);
}

static void Reverse(void* x,const int n)
{
   int k;
   char* ch = (char*)x;
   for (k=0;k<n/2;k++)
   {
      char tmp = ch[k];
      ch[k] = ch[n-1-k];
      ch[n-1-k] = tmp;
   }
}
//
//  Return true if CR or LF
//
static int CRLF(char ch)
{
   return ch == '\r' || ch == '\n';
}

//
//  Read line from file
//    Returns pointer to line or NULL on EOF
//
static int linelen=0;    //  Length of line
static char* line=NULL;  //  Internal storage for line

static char* readline(FILE* f)
{
   char ch;  //  Character read
   int k=0;  //  Character count
   while ((ch = fgetc(f)) != EOF)
   {
      //  Allocate more memory for long strings
      if (k>=linelen)
      {
         linelen += 8192;
         line = (char*)realloc(line,linelen);
         if (!line) Fatal("Out of memory in readline\n");
      }
      //  End of Line
      if (CRLF(ch))
      {
         // Eat extra CR or LF characters (if any)
         while ((ch = fgetc(f)) != EOF)
           if (!CRLF(ch)) break;
         //  Stick back the overrun
         if (ch != EOF) ungetc(ch,f);
         //  Bail
         break;
      }
      //  Pad character to line
      else
         line[k++] = ch;
   }
   //  Terminate line if anything was read
   if (k>0) line[k] = 0;
   //  Return pointer to line or NULL on EOF
   return k>0 ? line : NULL;
}

int LoadOBJ(char* file)
{
	int list;
	FILE* f = fopen(file,"r");
	if (!f) Fatal("Cannot open obj file %s\n",file);
	list = glGenLists(1);
	glNewList(list, GL_COMPILE);
	glEndList();
	char* line;
	int fcount = 0;
	int ncount = 0;
	int vcount = 0;
	while ((line = readline(f))){
	
		if(line[0] == 'v' && line[1] == ' '){
			vcount++;
		}
		if(line[0] == 'v' && line[1] == 'n'){
			ncount++;
		}
		if(line[0] == 'f' && line[1] == ' '){
			fcount++;
		}
	
	}
	fclose(f);
	int ** faces = new int*[fcount];
	float ** verts = new float*[vcount];
	float ** norms = new float*[ncount];
	int totalf = fcount;
	int totaln = ncount;
	int totalv = vcount;
	fcount = ncount = vcount = 0;
	f = fopen(file,"r");
	float vx, vy, vz; // vert vars
	int f1, f2, f3, n1, n2, n3; // face vars
	while ((line = readline(f))){
	
		if(line[0] == 'v' && line[1] == ' '){
			verts[vcount] = new float[3];
			sscanf(line, "%*s %f %f %f", &vx, &vy, &vz); // scans the line for the x/y/z coords
			verts[vcount][0] = vx;
			verts[vcount][1] = vy;
			verts[vcount][2] = vz;
			vcount++;
		}
		if(line[0] == 'v' && line[1] == 'n'){
			norms[ncount] = new float[3];
			sscanf(line, "%*s %f %f %f", &vx, &vy, &vz); // scans the line for the x/y/z vector
			norms[ncount][0] = vx;
			norms[ncount][1] = vy;
			norms[ncount][2] = vz;
			ncount++;
		}
		if(line[0] == 'f' && line[1] == ' '){
			faces[fcount] = new int[6];
			sscanf(line, "%*s %d//%d %d//%d %d//%d", &f1,&n1, &f2,&n2, &f3,&n3); // scans the line for the x/y/z coords
			faces[fcount][0] = f1;
			faces[fcount][1] = f2;
			faces[fcount][2] = f3;
			faces[fcount][3] = n1;
			faces[fcount][4] = n2;
			faces[fcount][5] = n3;
			fcount++;
		}
	
	}
	glNewList(list, GL_COMPILE);
	float emission[] = {0,0,0,1.0};
	glMaterialfv(GL_FRONT,GL_EMISSION,emission);
	glBegin(GL_TRIANGLES);
	
	for (int i = 0; i<totalf; i++){
	
		for (int j = 0; j<3; j++){
			glNormal3f(norms[faces[i][j+3]-1][0],norms[faces[i][j+3]-1][1],norms[faces[i][j+3]-1][2]);
			glVertex3f(verts[faces[i][j]-1][0],verts[faces[i][j]-1][1],verts[faces[i][j]-1][2]);
		
		}
	
	}
	glEnd();
	glEndList();
	for (int i = 0; i<totalv;i++){
		
		delete verts[i];
	
	}
	delete verts;
	for (int i = 0; i<totaln;i++){
		
		delete norms[i];
	
	}
	delete norms;
	for (int i = 0; i<totalf;i++){
		
		delete faces[i];
	
	}
	delete faces;
	return list;

}

unsigned int LoadTexBMP(char* file)
{
   unsigned int   texture;    // Texture name
   FILE*          f;          // File pointer
   unsigned short magic;      // Image magic
   unsigned int   dx,dy,size; // Image dimensions
   unsigned short nbp,bpp;    // Planes and bits per pixel
   unsigned char* image;      // Image data
   unsigned int   k;          // Counter

   //  Open file
   f = fopen(file,"rb");
   if (!f) Fatal("Cannot open file %s\n",file);
   //  Check image magic
   if (fread(&magic,2,1,f)!=1) Fatal("Cannot read magic from %s\n",file);
   if (magic!=0x4D42 && magic!=0x424D) Fatal("Image magic not BMP in %s\n",file);
   //  Seek to and read header
   if (fseek(f,16,SEEK_CUR) || fread(&dx ,4,1,f)!=1 || fread(&dy ,4,1,f)!=1 ||
       fread(&nbp,2,1,f)!=1 || fread(&bpp,2,1,f)!=1 || fread(&k,4,1,f)!=1)
     Fatal("Cannot read header from %s\n",file);
   //  Reverse bytes on big endian hardware (detected by backwards magic)
   if (magic==0x424D)
   {
      Reverse(&dx,4);
      Reverse(&dy,4);
      Reverse(&nbp,2);
      Reverse(&bpp,2);
      Reverse(&k,4);
   }
   //  Check image parameters
   if (dx<1 || dx>65536) Fatal("%s image width out of range: %d\n",file,dx);
   if (dy<1 || dy>65536) Fatal("%s image height out of range: %d\n",file,dy);
   if (nbp!=1)  Fatal("%s bit planes is not 1: %d\n",file,nbp);
   if ((bpp!=24) && (bpp!=32)) Fatal("%s bits per pixel is not 24 or 32: %d\n",file,bpp);
   if (k!=0)    Fatal("%s compressed files not supported\n",file);
#ifndef GL_VERSION_2_0
   //  OpenGL 2.0 lifts the restriction that texture size must be a power of two
   for (k=1;k<dx;k*=2);
   if (k!=dx) Fatal("%s image width not a power of two: %d\n",file,dx);
   for (k=1;k<dy;k*=2);
   if (k!=dy) Fatal("%s image height not a power of two: %d\n",file,dy);
#endif
	if (bpp == 32){
   //  Allocate image memory
   size = 4*dx*dy;
   image = (unsigned char*) malloc(size);
   if (!image) Fatal("Cannot allocate %d bytes of memory for image %s\n",size,file);
   //  Seek to and read image
   if (fseek(f,20,SEEK_CUR) || fread(image,size,1,f)!=1) Fatal("Error reading data from image %s\n",file);
   fclose(f);
   //  Reverse colors (BGR -> RGB)
   // I assume ABGR -> RGBA?
   unsigned char temp;
   for (k=0;k<size;k+=4)
   {
      //temp = image[k];
      //temp2 = image[k+1];
      //image[k] = image[k+3];
      //image[k+1] = image[k+2];
      //image[k+2] = temp2;
      //image[k+3] = temp;
      temp = image[k];
      image[k] = image[k+2];
      image[k+2] = temp;
   }

   //  Sanity check
   ErrCheck((char *)"LoadTexBMP");
   //  Generate 2D texture
   glGenTextures(1,&texture);
   glBindTexture(GL_TEXTURE_2D,texture);
   //  Copy image
   glTexImage2D(GL_TEXTURE_2D,0,4,dx,dy,0,GL_RGBA,GL_UNSIGNED_BYTE,image);
   }
   else{
      //  Allocate image memory
   size = 3*dx*dy;
   image = (unsigned char*) malloc(size);
   if (!image) Fatal("Cannot allocate %d bytes of memory for image %s\n",size,file);
   //  Seek to and read image
   if (fseek(f,20,SEEK_CUR) || fread(image,size,1,f)!=1) Fatal("Error reading data from image %s\n",file);
   fclose(f);
   //  Reverse colors (BGR -> RGB)
   for (k=0;k<size;k+=3)
   {
      unsigned char temp = image[k];
      image[k]   = image[k+2];
      image[k+2] = temp;
   }

   //  Sanity check
   ErrCheck((char*)"LoadTexBMP");
   //  Generate 2D texture
   glGenTextures(1,&texture);
   glBindTexture(GL_TEXTURE_2D,texture);
   //  Copy image
   glTexImage2D(GL_TEXTURE_2D,0,3,dx,dy,0,GL_RGB,GL_UNSIGNED_BYTE,image);
	}  
   if (glGetError()) Fatal("Error in glTexImage2D %s %dx%d\n",file,dx,dy);
   //  Scale linearly when image size doesn't match
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

   //  Free image memory
   free(image);
   //  Return texture name
   return texture;
}
