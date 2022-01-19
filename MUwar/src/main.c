#include "include.h"

#include "jokoa.h"

int main(void)
{
	/* Memoria ondo borratu den ikusteko, hau borratu entregarako! */
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

	bool errorea = false;

	if (jokoa_prestatu() == false)
	{
		fprintf(stderr, "Errorea: Ezin izan da jokoa hasi.\n");
		errorea = true;
	}

	if (jokoa_hasi() == false)
	{
		fprintf(stderr, "Errorea: Jokoaren exekuzioan errorea.\n");
		errorea = true;
	}

	jokoa_garbitu();

	return (int)(errorea);
}