#include "include.h"

#include "jokoa.h"
#include "menua.h"
#include "renderizadorea.h"
#include "musika.h"

static void dena_garbitu(void);

int main(void)
{
	/* Memoria ondo borratu den ikusteko, hau borratu entregarako! */
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

	srand((unsigned int)(time(NULL)));

	/* jokoa_garbitu() funtzioa programa bukaeran exekutatzeko erregistratu */
	atexit(dena_garbitu);
	
	if (jokoa_prestatu() == false)
	{
		ERROREA("Ezin izan da jokoa hasi.");
		exit(EXIT_FAILURE);
	}

	if (musika_prestatu() == false)
	{
		ERROREA("Ezin izan da musika prestatu.");
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
				if (jokoa_reset() == false)
				{
					ERROREA("Ezin izan da reseteatu hasi.");
					exit(EXIT_FAILURE);
				}
			}
			musika_gelditu();
		}
		else
		{
			controlspantaila(render_lortu_render(), render_lortu_window());
		}
		menuFinala(render_lortu_render(), 500, 500, render_lortu_window());
		SDL_Delay(500);
	}


	return EXIT_SUCCESS;
}

void dena_garbitu(void)
{
	jokoa_garbitu();
	musika_garbitu();
}
