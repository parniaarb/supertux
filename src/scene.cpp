//
// C Implementation: scene
//
// Description: 
//
//
// Author: Tobias Glaesser <tobi.web@gmx.de>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <stdlib.h>
#include "scene.h"

int score;
int distros;
int level;
int next_level;
int game_pause;
bool quit;
int score_multiplier;
int endpos;
bool counting_distros;
int distro_counter;
timer_type  super_bkgd_timer;
float scroll_x;
int global_frame_counter;
std::vector<bouncy_distro_type> bouncy_distros;
std::vector<broken_brick_type> broken_bricks;
std::vector<bouncy_brick_type> bouncy_bricks;
std::vector<BadGuy> bad_guys;
std::vector<floating_score_type> floating_scores;
std::vector<upgrade_type> upgrades;
std::vector<bullet_type> bullets;
Player tux;
texture_type img_box_full, img_box_empty, img_mints, img_coffee, img_super_bkgd, img_red_glow;
timer_type time_left;
double frame_ratio;

/* Initialize all 'dynamic' arrays */
void arrays_init(void)
{
}

/* Free memory of 'dynamic' arrays */
void arrays_free(void)
{
bad_guys.clear();
bouncy_distros.clear();
broken_bricks.clear();
bouncy_bricks.clear();
floating_scores.clear();
upgrades.clear();
bullets.clear();
}

void set_defaults(void)
{
  /* Set defaults: */
  
  scroll_x = 0;

  score_multiplier = 1;
  timer_init(&super_bkgd_timer, true);

  counting_distros = false;
  distro_counter = 0;

  endpos = 0;

  /* set current song/music */
  set_current_music(LEVEL_MUSIC);
}

/* Add score: */

void add_score(float x, float y, int s)
{
 /* Add the score: */

  score += s;

  floating_score_type new_floating_score;
  floating_score_init(&new_floating_score,x,y,s);
  floating_scores.push_back(new_floating_score);
}

/* Add a bouncy distro: */

void add_bouncy_distro(float x, float y)
{

  bouncy_distro_type new_bouncy_distro;
  bouncy_distro_init(&new_bouncy_distro,x,y);
  bouncy_distros.push_back(new_bouncy_distro);
}


/* Add broken brick pieces: */

void add_broken_brick(float x, float y)
{
  add_broken_brick_piece(x, y, -1, -4);
  add_broken_brick_piece(x, y + 16, -1.5, -3);

  add_broken_brick_piece(x + 16, y, 1, -4);
  add_broken_brick_piece(x + 16, y + 16, 1.5, -3);
}


/* Add a broken brick piece: */

void add_broken_brick_piece(float x, float y, float xm, float ym)
{
  broken_brick_type new_broken_brick;
  broken_brick_init(&new_broken_brick,x,y,xm,ym);
  broken_bricks.push_back(new_broken_brick);
}


/* Add a bouncy brick piece: */

void add_bouncy_brick(float x, float y)
{
  bouncy_brick_type new_bouncy_brick;
  bouncy_brick_init(&new_bouncy_brick,x,y);
  bouncy_bricks.push_back(new_bouncy_brick);
}


/* Add a bad guy: */

void add_bad_guy(float x, float y, BadGuyKind kind)
{
  BadGuy new_bad_guy;
  new_bad_guy.init(x,y,kind);
  bad_guys.push_back(new_bad_guy);
}

/* Add an upgrade: */

void add_upgrade(float x, float y, int dir, int kind)
{
  upgrade_type new_upgrade;
  upgrade_init(&new_upgrade,x,y,dir,kind);
  upgrades.push_back(new_upgrade);
}

/* Add a bullet: */

void add_bullet(float x, float y, float xm, int dir)
{
  bullet_type new_bullet;
  bullet_init(&new_bullet,x,y,xm,dir);
  bullets.push_back(new_bullet);
  
  play_sound(sounds[SND_SHOOT], SOUND_CENTER_SPEAKER);
}

