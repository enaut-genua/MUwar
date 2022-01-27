#include "musika.h"

Mix_Music* MENUA_MUSIKA = NULL;
Mix_Music* JOKUA_MUSIKA = NULL;

Mix_Chunk* AUKERATU_EFEKTO = NULL;
Mix_Chunk* KOTXEA_EFEKTO = NULL;
Mix_Chunk* INFANTERIA_TIRO_EFEKTO = NULL;
Mix_Chunk* INFANTERIA_MEK_TIRO_EFEKTO = NULL;
Mix_Chunk* TANKE_TIRO_EFEKTO = NULL;
Mix_Chunk* REKON_TIRO_EFEKTO = NULL;

bool musika_prestatu(void)
{
	bool dena_ondo = true;

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
	{
		ERROREA(Mix_GetError());
		dena_ondo = false;
		goto atera;
	}

	if ((MENUA_MUSIKA = Mix_LoadMUS("res/musika/menua_musika.wav")) == NULL)
	{
		ERROREA(Mix_GetError());
		dena_ondo = false;
		goto atera;
	}

	if ((JOKUA_MUSIKA = Mix_LoadMUS("res/musika/jokua_musika.wav")) == NULL)
	{
		ERROREA(Mix_GetError());
		dena_ondo = false;
		goto atera;
	}

	if ((AUKERATU_EFEKTO = Mix_LoadWAV("res/musika/aukeratu_efekto.wav")) == NULL)
	{
		ERROREA(Mix_GetError());
		dena_ondo = false;
		goto atera;
	}

	if ((KOTXEA_EFEKTO = Mix_LoadWAV("res/musika/kotxea_efekto.wav")) == NULL)
	{
		ERROREA(Mix_GetError());
		dena_ondo = false;
		goto atera;
	}

	if ((INFANTERIA_TIRO_EFEKTO = Mix_LoadWAV("res/musika/infanteria_tiro_efekto.wav")) == NULL)
	{
		ERROREA(Mix_GetError());
		dena_ondo = false;
		goto atera;
	}

	if ((INFANTERIA_MEK_TIRO_EFEKTO = Mix_LoadWAV("res/musika/infanteria_mek_tiro_efekto.wav")) == NULL)
	{
		ERROREA(Mix_GetError());
		dena_ondo = false;
		goto atera;
	}

	if ((TANKE_TIRO_EFEKTO = Mix_LoadWAV("res/musika/tanke_tiro_efekto.wav")) == NULL)
	{
		ERROREA(Mix_GetError());
		dena_ondo = false;
		goto atera;
	}

	if ((REKON_TIRO_EFEKTO = Mix_LoadWAV("res/musika/rekon_tiro_efekto.wav")) == NULL)
	{
		ERROREA(Mix_GetError());
		dena_ondo = false;
		goto atera;
	}

	Mix_VolumeChunk(AUKERATU_EFEKTO, SDL_MIX_MAXVOLUME);
	Mix_VolumeChunk(KOTXEA_EFEKTO, SDL_MIX_MAXVOLUME);
	Mix_VolumeChunk(INFANTERIA_TIRO_EFEKTO, SDL_MIX_MAXVOLUME);
	Mix_VolumeChunk(INFANTERIA_MEK_TIRO_EFEKTO, SDL_MIX_MAXVOLUME);
	Mix_VolumeChunk(TANKE_TIRO_EFEKTO, SDL_MIX_MAXVOLUME);
	Mix_VolumeChunk(REKON_TIRO_EFEKTO, SDL_MIX_MAXVOLUME);

atera:
	return dena_ondo;
}

void musika_garbitu(void)
{
	Mix_FreeMusic(MENUA_MUSIKA);
	Mix_FreeMusic(JOKUA_MUSIKA);

	Mix_FreeChunk(AUKERATU_EFEKTO);
	Mix_FreeChunk(KOTXEA_EFEKTO);
	Mix_FreeChunk(INFANTERIA_TIRO_EFEKTO);
	Mix_FreeChunk(INFANTERIA_MEK_TIRO_EFEKTO);
	Mix_FreeChunk(TANKE_TIRO_EFEKTO);
	Mix_FreeChunk(REKON_TIRO_EFEKTO);
}

bool musika_hasi_menua(void)
{
	bool dena_ondo = true;

	if (Mix_PlayingMusic() == false)
	{
		Mix_VolumeMusic(MIX_MAX_VOLUME);
		if (Mix_PlayMusic(MENUA_MUSIKA, -1) < 0)
		{
			dena_ondo = false;
			ERROREA(Mix_GetError());
		}
	}

	return dena_ondo;
}

bool musika_hasi_jokoa(void)
{
	bool dena_ondo = true;

	if (Mix_PlayingMusic() == false)
	{
		Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
		if (Mix_PlayMusic(JOKUA_MUSIKA, -1) < 0)
		{
			dena_ondo = false;
			ERROREA(Mix_GetError());
		}
	}

	return dena_ondo;
}

void musika_gelditu(void)
{
	if (Mix_PlayingMusic() == true)
	{
		Mix_HaltMusic();
	}
}

bool musika_aukeratu_efekto(void)
{
	bool dena_ondo = true;

	if (Mix_PlayChannel(-1, AUKERATU_EFEKTO, 0) < 0)
	{
		dena_ondo = false;
		ERROREA(Mix_GetError());
	}

	return dena_ondo;
}

bool musika_kotxea_efekto(void)
{
	bool dena_ondo = true;

	if (Mix_PlayChannel(-1, KOTXEA_EFEKTO, 0) < 0)
	{
		dena_ondo = false;
		ERROREA(Mix_GetError());
	}

	return dena_ondo;
}

bool musika_infanteria_tiro_efekto(void)
{
	bool dena_ondo = true;

	if (Mix_PlayChannel(-1, INFANTERIA_TIRO_EFEKTO, 0) < 0)
	{
		dena_ondo = false;
		ERROREA(Mix_GetError());
	}

	return dena_ondo;
}

bool musika_infanteria_mek_tiro_efekto(void)
{
	bool dena_ondo = true;

	if (Mix_PlayChannel(-1, INFANTERIA_MEK_TIRO_EFEKTO, 0) < 0)
	{
		dena_ondo = false;
		ERROREA(Mix_GetError());
	}

	return dena_ondo;
}

bool musika_tanke_tiro_efekto(void)
{
	bool dena_ondo = true;

	if (Mix_PlayChannel(-1, TANKE_TIRO_EFEKTO, 0) < 0)
	{
		dena_ondo = false;
		ERROREA(Mix_GetError());
	}

	return dena_ondo;
}

bool musika_rekon_tiro_efekto(void)
{
	bool dena_ondo = true;

	if (Mix_PlayChannel(-1, REKON_TIRO_EFEKTO, 0) < 0)
	{
		dena_ondo = false;
		ERROREA(Mix_GetError());
	}

	return dena_ondo;
}
