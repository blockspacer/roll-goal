#include "game.h"

#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <debug_break/debug_break.h>
#include <imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_opengl3.h>

bool Game::m_instanciated = false;

Game::Game() {
    assert(!m_instanciated);
	m_instanciated = true;

    // Init logger
    spdlog::set_pattern("[%l] %^ %v %$");

    // Init SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		spdlog::critical("[SDL2] Unable to initialize SDL: {}", SDL_GetError());
		debug_break();
	}
	SDL_GL_LoadLibrary(NULL);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
	SDL_GL_SetSwapInterval(1);

	m_window = SDL_CreateWindow(
		"Roll Goal",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		500, 500,
		SDL_WINDOW_OPENGL
    );
	if (m_window == nullptr) {
        spdlog::critical("[SDL2] Window is null: {}", SDL_GetError());
        debug_break();
    }

    m_context = SDL_GL_CreateContext(m_window);
    if (m_context == nullptr) {
        spdlog::critical("[SDL2] OpenGL context is null: {}",  SDL_GetError());
        debug_break();
    }

	if (!gladLoadGLES2Loader(SDL_GL_GetProcAddress)) {
		spdlog::critical("[Glad] Glad not init");
		debug_break();
	}

	// ImGui
    IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
    ImGui_ImplSDL2_InitForOpenGL(m_window, m_context);
	ImGui_ImplOpenGL3_Init("#version 300 es");
	ImGui::StyleColorsDark();
}

Game::~Game() {
    ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
    SDL_DestroyWindow(m_window);
	SDL_Quit();
}

/////////////////////////////////////////////////////////////////////////////
//////////////////////////// GETTERS & SETTERS //////////////////////////////
/////////////////////////////////////////////////////////////////////////////

SDL_Window* Game::getWindow() const { return m_window; }