#pragma once
#include <vector>

class IObserver;

//Universel; � r�cup�rer tel quel.
class Subject
{
public:
	static void addObserver(IObserver* observer);
	static void removeObserver(IObserver* observer);
	static void removeAllObservers();   //NOUVEAU - Important � faire � la fin des sc�nes qui ont des sujets dedans, 
										//pour qu'il ne reste pas des pointeurs vides de l'autre sc�ne d'avant.  
										//Unload pourrait enfin servir.

	virtual void notifyAllObservers();  //Virtuel seulement pour que typeid fonctionne avec IObserver.notify

private:
	static std::vector<IObserver*> observers;
};