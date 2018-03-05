//#include <iostream>
#include <math.h>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML/Audio.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <SFML/System/Vector2.hpp>
#include "Audio.h"

using namespace cv;

//#include "Song.h"
#include "Input.h"


#include "Scene.h"
Note::Note(int _x, int _y, int _destination, sf::Sprite _sprite) {
	this->x = _x;
	this->y = y;
	this->destination = _destination;
	this->sprite = _sprite;
}

Note::Note() {}

Note::~Note() {}

Scene::Scene(int Resource, sf::RenderWindow &screen, input Input, int BeatsPerBoard = 2) : _screen(screen)
{

	//_notes = new std::vector < std::pair<int, int>>;
	Music *_music = new Music("../Ressources/POPOPOPO.ogg");
	_music->play();

	//parameter type is int in temporary
	//not use any Resource
	b1 = false;
	b2 = false;
	b3 = false;
	b4 = false;
	_input = Input;
	//_song = __song;

	downLeft.loadFromFile("../Ressources/DownLeft.png");
	downRight.loadFromFile("../Ressources/DownRight.png");
	upLeft.loadFromFile("../Ressources/UpLeft.png");
	upRight.loadFromFile("../Ressources/UpRight.png");

	downLeftActive.loadFromFile("../Ressources/DownLeftActive.png");
	downRightActive.loadFromFile("../Ressources/DownRightActive.png");
	upLeftActive.loadFromFile("../Ressources/UpLeftActive.png");
	upRightActive.loadFromFile("../Ressources/UpRightActive.png");

	center.loadFromFile("../Ressources/Center.png");
	glow.loadFromFile("../Ressources/Glow.png");

	//ALL IMAGES HAVE SAME HEIGHT AND WIDTH
	constants.SPRITE_SIZE = glow.getSize().x;

	beatsPerBoard = BeatsPerBoard;

	backgroundColor[3] = { 0 };
	score = 0;

	font.loadFromFile("../Ressources/font.ttf");

	for (int i = 0; i < 4; i++) {
		opacityGlow[i] = 0;
	}

	calculateCenterTargetsDistance();

	constants.SQRT_2 = sqrt(2);

	float targetsHypotenuse = sqrt((2 * centerTargetsDistance - constants.SPRITE_SIZE)*(centerTargetsDistance - constants.SPRITE_SIZE));

	arrowTimeRelation = beatsPerBoard / targetsHypotenuse;

	//_song.play();

	//run();//call main loop
}

Scene::~Scene() {}

////////////////////////////////
void Scene::blitAlpha(sf::Texture source, int x, int y, int opacity) {



	/*
	temp = pygame.Surface((source.get_width(), source.get_height())).convert()
	temp.blit(self.screen, (-x, -y))
	temp.blit(source, (0, 0))
	temp.set_alpha(opacity)
	self.screen.blit(temp, location)
	*/

}

bool tg = true;

void Scene::handleNotes(sf::Clock clock) {
	//cout << "ICIIIIIIII";
	sf::Time T1 = clock.getElapsedTime();
	int nbr = T1.asSeconds();
	//cout << (std::rand() % 4) + 1 << endl;
	int Nbr_random;
	Nbr_random = (std::rand() % 4) + 1;
	if ((nbr % 2) == 0) {
		if (tg == true) {
			sf::Sprite sp;
			int posx;
			int posy;
			if (Nbr_random == 1) {
				sp.setTexture(upLeft);
				sp.setPosition(centerTargetsDistance - constants.SPRITE_SIZE, centerTargetsDistance - constants.SPRITE_SIZE);
			}
			else if (Nbr_random == 2) {
				sp.setTexture(upRight);
				sp.setPosition(constants.SCREEN_WIDTH - centerTargetsDistance, centerTargetsDistance - constants.SPRITE_SIZE);
			}
			else if (Nbr_random == 3) {
				sp.setTexture(downLeft);
				sp.setPosition(centerTargetsDistance - constants.SPRITE_SIZE, constants.SCREEN_HEIGHT - centerTargetsDistance);
			}
			else {
				sp.setTexture(downRight);
				sp.setPosition(constants.SCREEN_WIDTH - centerTargetsDistance, constants.SCREEN_HEIGHT - centerTargetsDistance);
			}
			//sp.setTexture(upLeft);
			//sp.setPosition(constants.SCREEN_WIDTH / 2, constants.SCREEN_HEIGHT / 2);
			_notes.push_back(Note(constants.SCREEN_WIDTH / 2, constants.SCREEN_HEIGHT / 2, Nbr_random, sp));
			
			{
				if ((std::rand() % 2) == 0) {
					int Nbr_random2;
					Nbr_random2 = (nbr % 4) + 1;
					sf::Sprite sp;
					int posx;
					int posy;
					if (Nbr_random2 == 1) {
						sp.setTexture(upLeft);
						sp.setPosition(centerTargetsDistance - constants.SPRITE_SIZE, centerTargetsDistance - constants.SPRITE_SIZE);
					}
					else if (Nbr_random2 == 2) {
						sp.setTexture(upRight);
						sp.setPosition(constants.SCREEN_WIDTH - centerTargetsDistance, centerTargetsDistance - constants.SPRITE_SIZE);
					}
					else if (Nbr_random2 == 3) {
						sp.setTexture(downLeft);
						sp.setPosition(centerTargetsDistance - constants.SPRITE_SIZE, constants.SCREEN_HEIGHT - centerTargetsDistance);
					}
					else {
						sp.setTexture(downRight);
						sp.setPosition(constants.SCREEN_WIDTH - centerTargetsDistance, constants.SCREEN_HEIGHT - centerTargetsDistance);
					}
					//sp.setTexture(upLeft);
					//sp.setPosition(constants.SCREEN_WIDTH / 2, constants.SCREEN_HEIGHT / 2);
					_notes.push_back(Note(constants.SCREEN_WIDTH / 2, constants.SCREEN_HEIGHT / 2, Nbr_random2, sp));

					//clock = sf::seconds(0.01f);
				}
				
			}
			tg = false;
		}
	}
	else 
		tg = true;

	renderNote(clock);
	clock.restart();
}

void Scene::renderNote(sf::Clock clock) {
	for (std::vector<Note>::iterator it = _notes.begin(); it != _notes.end(); ++it) {
		sf::Vector2f rq;
		if (it->destination == 1) 
			rq = sf::Vector2f(-30.0f, -30.0f);
		else if (it->destination == 2)
			rq = sf::Vector2f(30.0f, -30.0f);
		else if (it->destination == 3)
			rq = sf::Vector2f(-30.0f, 30.0f);
		else
			rq = sf::Vector2f(30.0f, 30.0f);
		//cout << "AAAAAAAAAAAAAAAAAAA";
		it->sprite.move(sprite.getPosition() + rq);
		_screen.draw(it->sprite);
	}
	bool isDelete = true;
	for (vector<Note>::iterator it = _notes.begin();
	it != _notes.end();) {
		isDelete = true;
		if (it->destination == 1) {
			if (it->sprite.getPosition().x < 0 || it->sprite.getPosition().y < 0) { //0 0 
				it = _notes.erase(it);
				isDelete = false;
			}
		}
		else if (it->destination == 2) {
			if (it->sprite.getPosition().x > 416 && it->sprite.getPosition().y < 0) {// 416 0
				it = _notes.erase(it);
				isDelete = false;
			}
		}
		else if (it->destination == 3) {
			if (it->sprite.getPosition().x < 0 && it->sprite.getPosition().y > 416) {// 0 416
				it = _notes.erase(it);
				isDelete = false;
			}
		}
		else {
			if (it->sprite.getPosition().x > 416 && it->sprite.getPosition().y > 416) {// 416 416
				it = _notes.erase(it);
				isDelete = false;
			}
		}
		if (isDelete == true) {
			++it;
		}
	}

}

void Scene::calculateCenterTargetsDistance() {
	if (constants.SCREEN_HEIGHT / 2 > constants.SCREEN_WIDTH / 2) {
		centerTargetsDistance = constants.SCREEN_WIDTH / 2;
	}
	else {
		centerTargetsDistance = constants.SCREEN_HEIGHT / 2;
	}
}

void Scene::renderCenterTargets() {

	sprite1.setTexture(center);
	sprite1.setPosition(centerTargetsDistance - constants.SPRITE_SIZE, centerTargetsDistance - constants.SPRITE_SIZE);
	_screen.draw(sprite1);
	//screen.blit(center, (centerTargetsDistance - constants.SPRITE_SIZE, centerTargetsDistance - constants.SPRITE_SIZE));

	sprite2.setTexture(center);
	sprite2.setPosition(constants.SCREEN_WIDTH - centerTargetsDistance, centerTargetsDistance - constants.SPRITE_SIZE);
	_screen.draw(sprite2);
	//screen.blit(center, (constants.SCREEN_WIDTH - centerTargetsDistance, centerTargetsDistance - constants.SPRITE_SIZE));

	sprite3.setTexture(center);
	sprite3.setPosition(centerTargetsDistance - constants.SPRITE_SIZE, constants.SCREEN_HEIGHT - centerTargetsDistance);
	_screen.draw(sprite3);
	//screen.blit(center, (centerTargetsDistance - constants.SPRITE_SIZE, constants.SCREEN_HEIGHT - centerTargetsDistance));

	sprite4.setTexture(center);
	sprite4.setPosition(constants.SCREEN_WIDTH - centerTargetsDistance, constants.SCREEN_HEIGHT - centerTargetsDistance);
	_screen.draw(sprite4);
	//screen.blit(center, (constants.SCREEN_WIDTH - centerTargetsDistance, constants.SCREEN_HEIGHT - centerTargetsDistance));
}

void Scene::renderCornerTargets() {

	if (_input.isActive(0)) {
		s1.setTexture(upLeftActive);
		s1.setPosition(0, 0);
		_screen.draw(s1);
		b1 = true;
		//screen.blit(upLeftActive, (0, 0));
	}
	else {
		s1.setTexture(upLeft);
		s1.setPosition(0, 0);
		_screen.draw(s1);
		b1 = false;
		//screen.blit(upLeft, (0, 0));
	}

	if (_input.isActive(1)) {
		s2.setTexture(upRightActive);
		s2.setPosition(constants.SCREEN_WIDTH - constants.SPRITE_SIZE, 0);
		_screen.draw(s2);
		b2 = true;
		//screen.blit(upRightActive, (constants.SCREEN_WIDTH - constants.SPRITE_SIZE, 0));
	}
	else {
		s2.setTexture(upRight);
		s2.setPosition(constants.SCREEN_WIDTH - constants.SPRITE_SIZE, 0);
		_screen.draw(s2);
		b2 = false;
		//screen.blit(upRight, (constants.SCREEN_WIDTH - constants.SPRITE_SIZE, 0));
	}


	if (_input.isActive(2)) {
		s3.setTexture(downLeftActive);
		s3.setPosition(0, constants.SCREEN_HEIGHT - constants.SPRITE_SIZE);
		_screen.draw(s3);
		b3 = true;
		//screen.blit(downLeftActive, (0, constants.SCREEN_HEIGHT - constants.SPRITE_SIZE));
	}
	else {
		s3.setTexture(downLeft);
		s3.setPosition(0, constants.SCREEN_HEIGHT - constants.SPRITE_SIZE);
		_screen.draw(s3);
		b3 = false;
		//screen.blit(downLeft, (0, constants.SCREEN_HEIGHT - constants.SPRITE_SIZE));
	}


	if (_input.isActive(3)) {
		s4.setTexture(downRightActive);
		s4.setPosition(constants.SCREEN_WIDTH - constants.SPRITE_SIZE, constants.SCREEN_HEIGHT - constants.SPRITE_SIZE);
		_screen.draw(s4);
		b4 = true;
		//screen.blit(downRightActive, (constants.SCREEN_WIDTH - constants.SPRITE_SIZE, constants.SCREEN_HEIGHT - constants.SPRITE_SIZE));
	}
	else {
		s4.setTexture(downRight);
		s4.setPosition(constants.SCREEN_WIDTH - constants.SPRITE_SIZE, constants.SCREEN_HEIGHT - constants.SPRITE_SIZE);
		_screen.draw(s4);
		b4 = false;
		//screen.blit(downRight, (constants.SCREEN_WIDTH - constants.SPRITE_SIZE, constants.SCREEN_HEIGHT - constants.SPRITE_SIZE));
	}
}

void Scene::renderWebCam() {
	sf::Image frame = _input.getCurrentFrameAsImage(); //From input
	sf::Texture textureFrame; //convert to texture type for draw on the screen
	textureFrame.loadFromImage(frame);

	sf::Sprite sprite;
	sprite.setTexture(textureFrame);
	sprite.setPosition(0, 0);
	//sprite.setTextureRect(sf::IntRect(constants.SCREEN_WIDTH, 0, -constants.SCREEN_WIDTH, constants.SCREEN_HEIGHT));
	//sprite.scale(-1.f, 1.f);
	_screen.draw(sprite);
	//_screen.display();
	//screen.blit(frame, (0, 0));
}

void Scene::render(sf::Clock clock) {
	renderWebCam();
	renderCornerTargets();
	handleNotes(clock);
	renderCenterTargets();
	renderGlow();
	fadeGlow();
	updateScore();
	renderScore();
}

void Scene::renderGlow() {

	blitAlpha(glow, 0, 0, opacityGlow[0]);
	blitAlpha(glow, constants.SCREEN_WIDTH - constants.SPRITE_SIZE, 0, opacityGlow[1]);
	blitAlpha(glow, 0, constants.SCREEN_HEIGHT - constants.SPRITE_SIZE, opacityGlow[2]);
	blitAlpha(glow, constants.SCREEN_WIDTH - constants.SPRITE_SIZE, constants.SCREEN_HEIGHT - constants.SPRITE_SIZE, opacityGlow[3]);

}

void Scene::fadeGlow() {

	for (int i = 0; i < 4; i++) {
		if (opacityGlow[i] > 0) {
			opacityGlow[i] -= constants.GLOW_FADE;
		}
	}
}

void Scene::handleRequiredNotes(vector<string> notes) {

	bool arrows[4] = { false, false, false, false };
	/*
	for (vector<string>::iterator it = notes.begin(); it != notes.end(); ++it) {
	if (_input.toggled(notes.number)){
	if (arrows[notes.number] == false){
	score += 50;
	notes.played = true;
	arrows[notes.number] = true;
	opacityGlow[notes.number] = sf::Color(255);
	}
	}
	}
	*/
	///done
	/*
	arrows = [False, False, False, False]
	for time, note in notes:
	if self.input.toggled(note.number):
	if arrows[note.number] == False:
	self.score += 50
	note.played = True
	arrows[note.number] = True
	self.opacityGlow[note.number] = 255
	*/
}

void Scene::renderScore() {
	sf::Text textScore;
	textScore.setFont(font);
	textScore.setString(std::to_string(score));

	float length = textScore.getCharacterSize();
	textScore.setPosition(((float)(constants.SCREEN_WIDTH) / 2 - length / 2), 0);
	_screen.draw(textScore);
	//screen.blit(textScore, (constants.SCREEN_WIDTH / 2 - (score).length / 2, 0));

}

void Scene::updateScore() {
	for (std::vector<Note>::iterator it = _notes.begin(); it != _notes.end(); ++it) {
		if (it->destination == 1)
			if (b1)
				score += 10;
		if (it->destination == 2)
			if (b2)
				score += 10;
		if (it->destination == 3)
			if (b3)
				score += 10;
		if (it->destination == 4)
			if (b4)
				score += 10;
			//cout << "AAAAAAAAAAAAAAAAAAA";
		}
}

void Scene::run(input in, sf::Clock clock) {
	_input = in;
	//_screen.draw(sceneClock.asMicroseconds);   //self.screenDelay = self.sceneClock.tick()
	//self.screen.fill(self.backgroundColor)
	//updateScore();
	_screen.clear(sf::Color::Black);
	render(clock);
	_screen.display(); //	pygame.display.flip()

}

