#include "include.h"

#include "jokoa.h"
#include "menua.h"
#include "renderizadorea.h"

int main(void)
{
	/* Memoria ondo borratu den ikusteko, hau borratu entregarako! */
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

	/* jokoa_garbitu() funtzioa programa bukaeran exekutatzeko erregistratu */
	atexit(jokoa_garbitu);
	
	if (jokoa_prestatu() == false)
	{
		ERROREA("Ezin izan da jokoa hasi.");
		exit(EXIT_FAILURE);
	}

	bool menua_martxan = true;

	hartu_running(&menua_martxan);

	while (menua_martxan)
	{
		menu(render_lortu_window(), render_lortu_render(), 500, 500, 0);
		if (lortu_jokoa_hasi() == true)
		{
			if (jokoa_hasi() == false)
			{
				ERROREA("Jokoaren exekuzioan errorea.");
				exit(EXIT_FAILURE);
			}
			else
			{
				jokoa_garbitu();
				if (jokoa_prestatu() == false)
				{
					ERROREA("Ezin izan da jokoa hasi.");
					exit(EXIT_FAILURE);
				}
			}
		}
		else
		{
			controlspantaila(render_lortu_render(), render_lortu_window());
		}
		menuFinala(render_lortu_render(), 500, 500, render_lortu_window());
		SDL_Delay(100);
	}


	return EXIT_SUCCESS;
}