#pragma once

class Menu {

	GLuint mLogoTextureId;
	GLuint mCreditTextureId;
	GLuint mOptionsTextureId;
	GLuint mQuitTextureId;
	GLuint mStartTextureIdl;

public:
	Menu(GLuint logoTextureId, GLuint creditTextureId, 
		GLuint optionsTextureId, GLuint quitTextureId, 
		GLuint startTextureId);
	Menu();
	~Menu();

	void drawLogo();
	void draw();
	void update(float elapsedTime);
	void drawStart();
	void drawOptions();
	void drawCredits();
	void drawQuit();
};