#ifndef ENGINE_HPP
#define ENGINE_HPP

#define WORLDSCALE 1
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600



class Engine
{
private:
	int windowHeight;
	int windowWidth;
	bool keys[256];

	Engine() {};
	
	void gameLoop();
	void init(int argc, char** argv);
	static void reshape(int w, int h);
public:
	virtual void update(float elapsedTime) = 0;
	virtual void draw() = 0;
	virtual void loadContent() = 0;
	void close();
	/*static Engine& getInstance()
	{
		static Engine instance;
		return instance;
	}*/
	void run(int argc, char** argv);
};
#endif

