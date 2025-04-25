#include "SceneGame.h"
#include "ContentPipeline.h"

SceneGame::SceneGame(RenderWindow& renderWindow, Event& event) : Scene(renderWindow, event)
{
	view = renderWindow.getDefaultView();
}

Scene::scenes SceneGame::run()
{
	while (isRunning)
	{
		calculateDeltaTime();
		getInputs();
		update();
		draw();
	}

	if (!unload()) return scenes::FAIL;

	return transitionToScene;
}

bool SceneGame::init()
{	
	map.setTexture(ContentPipeline::getInstance().getMapTexture(map1));

	hud.hudInit(ContentPipeline::getInstance().getHudmaskTexture(), ContentPipeline::getInstance().getComiciFont());

	return true;
}

void SceneGame::getInputs()
{
	//On passe l'�v�nement en r�f�rence et celui-ci est charg� du dernier �v�nement re�u!
	while (renderWindow.pollEvent(event))
	{
		//x sur la fen�tre
		if (event.type == Event::Closed) exitGame();
	}
}

void SceneGame::update()
{

}

void SceneGame::draw()
{
	//Toujours important d'effacer l'�cran pr�c�dent
	renderWindow.clear();
	renderWindow.draw(map);

	hud.draw(renderWindow);
	renderWindow.display();
}

bool SceneGame::unload()
{
	return true;
}