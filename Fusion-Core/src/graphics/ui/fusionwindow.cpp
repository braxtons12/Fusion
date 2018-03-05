#include "fusionwindow.h"

namespace fusion { namespace core { namespace graphics { namespace ui { 
	
	
	void FusionWindow::init() {
		
		m_Window = new Window(m_Name, m_Width, m_Height);
		m_Signal = m_Window->getSignalServer();
		
		m_Mouse = &input::Mouse::GetInstance();
		m_Keyboard = &input::Keyboard::GetInstance();
		
		m_Shader = new Shader(m_VertexShaderPath, m_FragmentShaderPath);
		m_Shader->enable();

		m_Renderables = new std::vector<Renderable2D*>;

		m_Shader->enable();
	}
	
	FusionWindow::FusionWindow(const char* name, int width, int height, const char* vertexShaderPath, const char* fragmentShaderPath, bool hasMenu)
		: m_Name(name), m_Width(width), m_Height(height), m_VertexShaderPath(vertexShaderPath), m_FragmentShaderPath(fragmentShaderPath),
		m_HasMenu(hasMenu)
	{
		init();
	}
	
	void FusionWindow::scale(double x, double y) {

		m_Width *= x;
		m_Height *= y;
		m_Window->setWidth(((int)m_Width));
		m_Window->setHeight(((int)m_Height));

		for(int i = 0; i < m_Renderables->size(); ++i) {
			m_Renderables->at(i)->scale(x, y);
		} 
	}

	void FusionWindow::setMenu(math::vec3 position, math::vec2 size, Color colorOff, Color colorNormal, Color colorHover, 
							   int state, int menuType, int numMenus, int numEntries, bool alwaysVisible,
							   std::vector<FusionMenu*> subMenus) 
	{
		m_Menu = new FusionMenu(position, size, colorOff, colorNormal, colorHover, state, menuType, numMenus, 
								numEntries, alwaysVisible, m_Window);
		for (int i = 0; i < numMenus; ++i) {
			m_Menu->addSubMenu(subMenus.at(i));
		}
	}

	void FusionWindow::update() {

		double x, y = 0.0;

		if (m_Signal->getSignal(x, y)) {
			
			x /= m_Width;
			y /= m_Height;
			m_Window->m_XScaleFactor *= x;
			m_Window->m_YScaleFactor *= y;
			this->scale(x, y);
			m_Signal->resetSignal();
		}	

		if(m_HasMenu) {

			m_Menu->checkHover();
			m_Menu->checkClicked();
		}
		
	}

	void FusionWindow::render() {

		m_Window->clear();

		m_Renderer->begin();

		for(int i = 0; i < m_Renderables->size(); ++i) {

			m_Renderables->at(i)->submit(m_Renderer);
		}

		if(m_HasMenu) m_Menu->submit(m_Renderer);

		m_Renderer->end();
		m_Renderer->flush();

		m_Window->update();

		m_Renderables = new std::vector<Renderable2D*>; 
	}

}}}}