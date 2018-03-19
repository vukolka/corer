#include "CorewarVis.h"

int		CorewarVis::OnExecute()
{
	if (!OnInit())
		return (1);
	if (!OnLoad())
		return (1);
	while (running)
	{
		OnEvent();
		OnLoop();
		OnRender();
		//SDL_Delay(1);
	}
	OnCleanup();
	return (0);
}
