#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"

class Engine2D : public Walnut::Layer
{
public:
	virtual void OnUIRender() override
	{
		ImGui::Begin("Engine");
		ImGui::End();
	}
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Engine2D";

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<Engine2D>();
	app->SetMenubarCallback([app]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		}
	});
	return app;
}