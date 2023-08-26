#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"
#include "Engine2D.h"


class Engine2DLayer : public Walnut::Layer
{
public:
	Engine2DLayer()
	{
		m_ImageData = new uint32_t[WIDTH * HEIGHT];

		m_Image = std::make_shared<Walnut::Image>(WIDTH, HEIGHT, Walnut::ImageFormat::RGBA, m_ImageData);
	}

	virtual void OnUpdate(float ts) override
	{
		for (int i = 0; i < m_Image->GetWidth() * m_Image->GetHeight(); i++)
		{
			m_ImageData[i] = 0xff000000;
		}

		double x0 = (double)m_Image->GetWidth() / (double)2;
		double y0 = (double)m_Image->GetHeight() / (double)2;

		double radius = 50;

		for (uint32_t i = 0; i < m_Image->GetWidth(); i++)
		{
			for (uint32_t j = 0; j < m_Image->GetHeight(); j++)
			{
				if (Engine::Distance(x0, y0, (double)i, (double)j) < radius)
				{
					m_ImageData[i + (j * m_Image->GetWidth())] = 0xffffffff;
				}
			}
		}

		m_Image->SetData(m_ImageData);
	}

	virtual void OnUIRender() override
	{
		ImGui::Begin("Engine2D");

		uint32_t windowWidth = (uint32_t)ImGui::GetContentRegionAvail().x;
		uint32_t windowHeight = (uint32_t)ImGui::GetContentRegionAvail().y;

		ImGui::Image(m_Image->GetDescriptorSet(), ImVec2((float)m_Image->GetWidth(), (float)m_Image->GetHeight()));

		if (windowWidth != m_Image->GetWidth() || windowHeight != m_Image->GetHeight())
		{
			//resize
			m_Image = std::make_shared<Walnut::Image>(windowWidth, windowHeight, Walnut::ImageFormat::RGBA);
			delete[] m_ImageData;
			m_ImageData = new uint32_t[windowWidth * windowHeight];
		}

		m_Image->SetData(m_ImageData);

		ImGui::End();
	}
private:
	std::shared_ptr<Walnut::Image> m_Image;
	uint32_t* m_ImageData = nullptr;
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Engine2D";

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<Engine2DLayer>();
	return app;
}