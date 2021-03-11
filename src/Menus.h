#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

// Render points

void RenderStats (float score, float fps);

// Menu functions

void RenderStartMenu (float timestamp);

void RenderHelpMenu ();

void RenderGameOverMenu (float score);

// Leaderboard functions

int WriteScoreToLeaderboard (float score);

int LeaderboardHighScores (float* first, float* second, float* third);
