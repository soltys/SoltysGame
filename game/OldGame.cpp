#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>

#include "Game.h"

constexpr int FPS = 60;
constexpr int palette_w = 350;
constexpr int maxBallSpeed = 10.0;

struct gameScreen {
	int Width = 1260;
	int Height = 720;
} gameScreen;

enum KEYS_PLAYER_1
{
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT
};
enum KEYS_PLAYER_2
{
	W,
	A,
	S,
	D
};
struct padStruct
{
	float speed = 1000.0;
	float x1 = gameScreen.Width / 2 - palette_w / 2;
	float x2 = gameScreen.Width / 2 + palette_w / 2;
} padData;
struct ballStruct
{
	float rad = 10;
	float speedX = 0.0;
	float speedY = maxBallSpeed;
	float x = gameScreen.Width / 2;
	float y = gameScreen.Height / 2;
	void reset()
	{
		x = gameScreen.Width / 2;
		y = gameScreen.Height / 2;
		speedY = maxBallSpeed;
		speedX = 0.0;
	}
	void checkHit()
	{
		if (x < 0 || x > gameScreen.Width)
			speedX = -speedX;
	}
	void updatePos()
	{
		x = x + speedX;
		y = y + speedY;
	}
} ballData;

padStruct paddle;
padStruct paddle2;
ballStruct ball;

void checkCollisionWithPad(void)
{
	if (ball.y >= 700 - ball.rad || ball.y <= 20 + ball.rad)
	{
		if ((ball.x >= paddle.x1 && ball.x <= paddle.x2) || (ball.x >= paddle2.x1 && ball.x <= paddle2.x2))
		{
			float dist, distSpeed;
			bool down = false;
			if (ball.y <= 20 + ball.rad)
			{
				dist = ball.x - paddle2.x1;
				down = true;
			}
			else
			{
				dist = ball.x - paddle.x1;
			}
			distSpeed = -(palette_w / 2 - dist);
			ball.speedX = distSpeed * (maxBallSpeed / (palette_w / 2.0));
			ball.speedY = (std::sqrt(maxBallSpeed * maxBallSpeed - (ball.speedX * ball.speedX)));
			if (!down)
			{
				ball.speedY *= (-1);
			}
		}
	}
}



static bool keyP1[4] = { false, false, false, false };
static bool keyP2[4] = { false, false, false, false };
static ALLEGRO_COLOR AL_WHITE = al_map_rgb(255, 255, 255);
static ALLEGRO_COLOR AL_FGREEN = al_map_rgb(34, 139, 34);
void Game::Initialize() {

	al_init();
	al_init_primitives_addon();
	al_install_keyboard();
	timer = al_create_timer(1.0 / FPS);
	display = al_create_display(gameScreen.Width, gameScreen.Height);
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_flip_display();
	al_start_timer(timer);

	gameTime = std::make_unique<GameTime>(al_get_time());
}

bool Game::IsRunning() {
	return noexit;
}

void Game::Terminate() {
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	al_destroy_timer(timer);
}
void Game::Update()
{
	auto ev = this->WaitForEvent();
	auto dt = this->gameTime->GetTick();
	Update(dt, &ev);
}
void Game::Update(double dt, ALLEGRO_EVENT* ev) {

	if (ev->type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		noexit = false;
		return;
	}
	if (ev->type == ALLEGRO_EVENT_TIMER)
	{
		redraw = true;
	}
	else if (ev->type == ALLEGRO_EVENT_KEY_DOWN)
	{
		//	paddle.speed += 10;
		switch (ev->keyboard.keycode)
		{
		case ALLEGRO_KEY_UP:
			keyP1[KEY_UP] = true;
			break;

		case ALLEGRO_KEY_DOWN:
			keyP1[KEY_DOWN] = true;
			break;

		case ALLEGRO_KEY_LEFT:
			keyP1[KEY_LEFT] = true;
			break;

		case ALLEGRO_KEY_RIGHT:
			keyP1[KEY_RIGHT] = true;
			break;
		case ALLEGRO_KEY_W:
			keyP2[W] = true;
			break;
		case ALLEGRO_KEY_A:
			keyP2[A] = true;
			break;
		case ALLEGRO_KEY_S:
			keyP2[S] = true;
			break;
		case ALLEGRO_KEY_D:
			keyP2[D] = true;
			break;
		case ALLEGRO_KEY_R:
			ball.reset();
			break;
		}
	}
	else if (ev->type == ALLEGRO_EVENT_KEY_UP)
	{
		//paddle.reset();
		switch (ev->keyboard.keycode)
		{
		case ALLEGRO_KEY_UP:
			keyP1[KEY_UP] = false;
			break;

		case ALLEGRO_KEY_DOWN:
			keyP1[KEY_DOWN] = false;
			break;

		case ALLEGRO_KEY_LEFT:
			keyP1[KEY_LEFT] = false;
			break;

		case ALLEGRO_KEY_RIGHT:
			keyP1[KEY_RIGHT] = false;
			break;
		case ALLEGRO_KEY_W:
			keyP2[W] = false;
			break;
		case ALLEGRO_KEY_A:
			keyP2[A] = false;
			break;
		case ALLEGRO_KEY_S:
			keyP2[S] = false;
			break;
		case ALLEGRO_KEY_D:
			keyP2[D] = false;
			break;
		case ALLEGRO_KEY_ESCAPE:
			noexit = false;
			break;
		}
	}

	if (keyP1[KEY_LEFT] && paddle.x1 > 0)
	{
		paddle.x1 -= paddle.speed * dt;
		paddle.x2 -= paddle.speed * dt;
	}
	if (keyP2[A] && paddle2.x1 > 0)
	{
		paddle2.x1 -= paddle2.speed * dt;
		paddle2.x2 -= paddle2.speed * dt;
	}
	if (keyP1[KEY_RIGHT] && paddle.x2 < gameScreen.Width)
	{
		paddle.x1 += paddle.speed * dt;
		paddle.x2 += paddle.speed * dt;
	}
	if (keyP2[D] && paddle2.x2 < gameScreen.Width)
	{
		paddle2.x1 += paddle2.speed * dt;
		paddle2.x2 += paddle2.speed * dt;
	}

}

void Game::Draw() {
	if (redraw && al_is_event_queue_empty(event_queue)) {
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_filled_rectangle(paddle.x1, 720, paddle.x2, 700, AL_WHITE);
		al_draw_filled_rectangle(paddle2.x1, 0, paddle2.x2, 20, AL_FGREEN);
		al_draw_filled_circle(ball.x, ball.y, ball.rad, AL_WHITE);
		checkCollisionWithPad();
		ball.updatePos();
		ball.checkHit();
		al_flip_display();
		redraw = false;
	}
}