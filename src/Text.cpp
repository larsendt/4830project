#include "Text.h"

static GLuint font_vbo;
static GLuint fontprogram;
static GLint attribute_coord;
static GLint font_uniform_tex;
static GLint font_uniform_color;
static FT_Library ft;
static FT_Face face;

static float sx;
static float sy;

static float color[4];

atlas *a48;
atlas *a24;
atlas *a12;
atlas * a;

void setFontColor(float r, float g, float b, float a){

	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = a;
}

void setFontSize(int size){

	switch (size){
		case 48:
			a = a48;
			break;
		case 24:
			a = a24;
			break;
		case 12:
			a = a12;
			break;
	
	}

}

void initFT(){

	for (int i = 0; i<4;i++){
		color[i] = 1.0;
	}
	if (FT_Init_FreeType(&ft)){
		fprintf(stderr, "Freetype Borked\n");
		exit(1);
	}
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	Shader fshader((char*)"shaders/text.vert", (char*)"shaders/text.frag");
	fontprogram = fshader.getID();
	
	const char* attribute_name;
	attribute_name = "pos";
	attribute_coord = glGetAttribLocation(fontprogram, attribute_name);
	if (attribute_coord == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
		exit(0);
	}

	const char* font_uniform_name;
	font_uniform_name = "tex";
	font_uniform_tex = glGetUniformLocation(fontprogram, font_uniform_name);
	if (font_uniform_tex == -1) {
		fprintf(stderr, "Could not bind font_uniform %s\n", font_uniform_name);
		exit(0);
	}

	font_uniform_name = "color";
	font_uniform_color = glGetUniformLocation(fontprogram, font_uniform_name);
	if (font_uniform_color == -1) {
		fprintf(stderr, "Could not bind font_uniform %s\n", font_uniform_name);
		exit(0);
	}
	

	// Create the vertex buffer object
	glGenBuffers(1, &font_vbo);
	
	
}

void initFont(char* font){
	
	if(int fail = FT_New_Face(ft, font, 0, &face)){
		fprintf(stderr,"Can't open %s font because %i\n", font, fail);
		exit(1);
	}
	
	FT_Set_Pixel_Sizes(face, 0, 12);	
	
	glUseProgram(fontprogram);
	
	font_uniform_tex = glGetUniformLocation(fontprogram, (char*)"tex");
	
	glUseProgram(fontprogram);
	a48 = new atlas(face, 48);
	a24 = new atlas(face, 24);
	a12 = new atlas(face, 12);
	
	setFontSize(48);
	
}

void render_text(const char *text, float x, float y, float sx, float sy ) {
	
	glUseProgram(fontprogram);
	const char *pc;
	glBindTexture(GL_TEXTURE_2D, a->tex);
	glUniform1i(font_uniform_tex, 0);
	
	glUniform4fv(font_uniform_color, 4, color);	
	/* Set up the VBO for our vertex data */
	glEnableVertexAttribArray(attribute_coord);
	glBindBuffer(GL_ARRAY_BUFFER, font_vbo);
	glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);

	point coords[6*strlen(text)];
	int c = 0;

	for (pc = text; *pc;pc++){
	/* Calculate the vertex and texture coordinates */
		int p = (int) *pc;
		float x2 =  x + a->c[p].bl * sx;
		float y2 = -y - a->c[p].bt * sy;
		float w = a->c[p].bw * sx;
		float h = a->c[p].bh * sy;

		/* Advance the cursor to the start of the next character */
		x += a->c[p].ax * sx;
		y += a->c[p].ay * sy;

		/* Skip glyphs that have no pixels */
		if(!w || !h)
			continue;

		coords[c++] = (point){x2,     -y2    , a->c[p].tx,                      a->c[p].ty};
		coords[c++] = (point){x2 + w, -y2    , a->c[p].tx + a->c[p].bw / a->w, a->c[p].ty};
		coords[c++] = (point){x2,     -y2 - h, a->c[p].tx,                      a->c[p].ty + a->c[p].bh / a->h};
		coords[c++] = (point){x2 + w, -y2    , a->c[p].tx + a->c[p].bw / a->w, a->c[p].ty};
		coords[c++] = (point){x2,     -y2 - h, a->c[p].tx,                      a->c[p].ty + a->c[p].bh / a->h};
		coords[c++] = (point){x2 + w, -y2 - h, a->c[p].tx + a->c[p].bw / a->w, a->c[p].ty + a->c[p].bh / a->h};
	}

	/* Draw all the character on the screen in one go */
	glBufferData(GL_ARRAY_BUFFER, sizeof coords, coords, GL_DYNAMIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, c);

	glDisableVertexAttribArray(attribute_coord);
	glUseProgram(0);
}

void drawString(const char* text, int x, int y){
	
	render_text(text, x * sx,   y * sy,    sx, sy);

}

void resizeFonts(float x, float y){

	sx = 2.0/x;
	sy = 2.0/y;

}
