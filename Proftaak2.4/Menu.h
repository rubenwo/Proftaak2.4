#pragma once

class Menu {

	GLuint mLogoTextureId;
	GLuint mCreditTextureId;
	GLuint mCreditSelectedTextureId;
	GLuint mOptionsTextureId;
	GLuint mOptionsSelectedTextureId;
	GLuint mQuitTextureId;
	GLuint mQuitSelectedTextureId;
	GLuint mStartTextureIdl;
	GLuint mStartSelectedTextureIdl;

	int mIndex;

public:
	Menu(GLuint logoTextureId, GLuint creditTextureId, GLuint creditSelectedTextureId,
		GLuint optionsTextureId, GLuint opetionsSelectedTextureId,
		GLuint quitTextureId, GLuint quitSelectedTextureId, 
		GLuint startTextureId, GLuint startSelectedTextureId);
	Menu();
	~Menu();

	void drawLogo();
	void draw();
	void update(float elapsedTime, int index);
	void drawStart(GLuint texture);
	void drawOptions(GLuint texture);
	void drawCredits(GLuint texture);
	void drawQuit(GLuint texture);
};