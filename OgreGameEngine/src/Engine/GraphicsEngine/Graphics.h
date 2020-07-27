#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "Window.h"

class OverlaySystem;

class Graphics
{
public:
	static float FPS;

private:
	static Window* window;
	static Ogre::Root* root;
	static bool isRendering;

	static Ogre::SceneManager* sceneManager;
	static Ogre::Viewport* viewport;
	static Ogre::Camera* mainCamera;

	static float fpsTimer;
	static int frames;

public:
	static void Init();
	static void Release();

	static void Update(float deltaTime);
	static void ResizeWindow();
	static void StopRendering();

	static void CreateViewport();
	static void CreateMainCamera();

	static Window* GetWindow() { return window; }
	static Ogre::Root* GetRoot() { return root; }
	static Ogre::SceneManager* getSceneManager() { return sceneManager; }
	static bool IsRendering() { return isRendering; }

protected:
	static void CreateRoot();
	static void DestroyRoot();
	static void CreateSceneManager();
	static void CreateGraphicContext();
	static void DestroyGraphicContext();

	static void CountFPS(float dt);
};

#endif // !__GRAPHICS_H__
