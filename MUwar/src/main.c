#include "include.h"

#include "jokoa.h"

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

	if (jokoa_hasi() == false)
	{
		ERROREA("Jokoaren exekuzioan errorea.");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}