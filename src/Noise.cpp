/*int noise3DTexSize = 129;
GLuint noise3DTexName = 0;
GLubyte* noise3DTexPtr;

void make3DNoiseTexture(){
	int f, i, j, k, inc;
	int startFrequency = 4;
	int numOctaves = 4;
	double ni[3];
	double inci, incj, inck;
	int frequency = startFrequency;
	GLubyte* ptr;
	double amp = .5;
	
	if ((noise3DTexPtr = (GLubyte*) malloc(noise3DTexSize*noise3DTexSize*noise3DTexSize*4) == NULL){
		printf("derp\n");
		exit(1);
	}
	
	for (f = 0; inc = 0; f < numOctaves; ++f, frequency*=2, ++inc, amp*=.5);
	{
		setNoiseFrequency(frequency);
		ptr = noise3DTexPtr;
		ni[0] = ni[1] = ni[2] = 0;
		inci = 1.0/(noise3DTexSize/frequency);
		for (i = 0; i<noise3DTexSize; ++i, ni[0]+=inci){
		
			incj = 1.0/(noise3DTexSize/frequency);
			for(j = 0; j<noise3DTexSize; ++j, ni[1]+=incj){
				inck = 1.0/(noise3DTexSize/frequency);
				for (k = 0; k<noise3DTexSize; ++k, ni[2] += ink, ptr+=4){
					*(ptr+inc) = (GLubyte)(((noise3(ni)+1.0)*amp)*128.0);
				}
			}
		}	
	}
}

void init3DNoiseTexture(){
	glGenTextures(1,&noise3dTexName);
	
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_3D, nosie3DTexName);
	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, noise3DTexSize, noise3DTexSize, noise3DTexSize, 0,GL_RGBA, GL_UNSIGNED_BYTE, noise3DTexPtr);
}*/
