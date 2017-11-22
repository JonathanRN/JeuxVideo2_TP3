//Notez que tous les observateurs peuvent réutiliser ce fichier intégralement.  Ce sera toujours la forme de l'observateur
#pragma once

	class Sujet;  //Parce qu'on sera en forward declaration
	class IObservateur
	{
	public:
		virtual void notifier(Sujet* sujet) = 0;
	};
