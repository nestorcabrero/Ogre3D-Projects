#include "Window.h"
#include "Graphics.h"
#include "SDL_syswm.h"

Window::Window(Ogre::RenderWindow* render, SDL_Window* native) :
	render_(render),
	native_(native)
{
}

void Window::initWindow(const Ogre::String& name, uint32_t w, uint32_t h)
{
    Ogre::NameValuePairList miscParams;
    auto d = Graphics::GetRoot()->getRenderSystem()->getRenderWindowDescription();
    miscParams.insert(d.miscParams.begin(), d.miscParams.end());
    d.miscParams = miscParams;
    if (w > 0) d.width = w;
    if (h > 0) d.height = h;
    d.name = name;

    int flags = d.useFullScreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE;
    native_ = SDL_CreateWindow(d.name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, d.width, d.height, flags);

    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(native_, &wmInfo);
    d.miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));
    d.miscParams["currentGLContext"] = "true";

    render_ = Graphics::GetRoot()->createRenderWindow(d);
}

void Window::setWindowName(const Ogre::String& name)
{
    SDL_SetWindowTitle(native_, name.c_str());
}

void Window::setWindowGrab(bool grab)
{
    SDL_SetWindowGrab(native_, SDL_bool(grab));
    SDL_ShowCursor(!SDL_bool(grab));
}

void Window::destroyWindow()
{
    Graphics::GetRoot()->destroyRenderTarget(render_);
    if (native_) SDL_DestroyWindow(native_);
}