/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 12;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 12;       /* vert inner gap between windows */
static const unsigned int gappoh    = 12;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 12;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const double activeopacity   = 1.0f;     /* Window opacity when it's focused (0 <= opacity <= 1) */
static const double inactiveopacity = 0.6f;     /* Window opacity when it's inactive (0 <= opacity <= 1) */
static       Bool bUseOpacity       = True;     /* Starts with opacity on any unfocused windows */
static const char *fonts[]          = { "CaskaydiaCove NF:size=12", "JoyPixels:pixelsize=12" };
static const char col_gray1[]       = "#1A202D";
static const char col_gray2[]       = "#000000";
static const char col_gray3[]       = "#82868E";
static const char col_gray4[]       = "#4F5666";
static const char col_cyan[]        = "#EACA8A";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray4 },
	[SchemeSel]  = { col_cyan, 	col_gray1, col_cyan },
};

/* tagging */
static const char *tags[] = { "🖥️", "🎬", "🐺", "🗃️", "👻", "💩"};
static const char ptagf[] = "%s %s";	/* format of a tag label */
static const char etagf[] = "%s";			/* format of an empty tag */
static const int lcaselbl = 0;				/* 1 means make tag label lowercase */	

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            	instance    title   tags mask  	switch  float mon */
	{ "Thunderbird", 			NULL, 			NULL, 	1 << 5, 		1, 			0, 		-1 },
	{ "Gimp", 						NULL, 			NULL, 	1 << 5, 		1, 			1, 		-1 },
	{ "firefox",        	NULL,       NULL,   1 << 2,     1,      0,    -1 },
	{ "Chromium",        	NULL,       NULL,   1 << 2,     1,      0,    -1 },	
	{ "librewolf",      	NULL,       NULL,   1 << 2,     1,      0,    -1 },
  { "qBittorrent",			NULL,       NULL,   1 << 4,     1,      0,    -1 },
  { "st",             	NULL,       NULL,   0,          0,      1,    -1 },
  { "kitty",          	NULL,       NULL,   0,          0,      1,    -1 },
  { "Alacritty",      	NULL,       NULL,   0,          0,      1,    -1 },
  { "Tor-browser",    	NULL,       NULL,   1 << 4,     1,      0,    -1 },
	{ "GParted", 					NULL, 			NULL, 	0, 					0, 			1, 		-1 },
};

/* layout(s) */
static const float mfact     		= 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster     		= 1;    /* number of clients in master area */
static const int resizehints 		= 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; 		/* 1 will force focus on the fullscreen window */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      monocle }, /* first entry is default */
	{ "",      NULL },    /* no layout function means floating */
	{ "",      tile },
  { "",      grid },
	{ "",      deck },
};

/* key definitions */
#define Super Mod4Mask
#define Alt Mod1Mask
#define Shift ShiftMask
#define Ctrl ControlMask 
#define TAGKEYS(KEY,TAG) \
	{ Super,            KEY,      view,           {.ui = 1 << TAG} }, \
	{ Super|Ctrl,       KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ Super|Shift,      KEY,      tag,            {.ui = 1 << TAG} }, \
	{ Super|Ctrl|Shift, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static Key keys[] = {
	/* modifier                     key        	function        argument */
	{ Super, 						 XK_bracketright,				togglebar,      {0} },
	{ Super|Shift,       XK_bracketright,	      hideborder,     {0} },

	{ Super, 												XK_j, 			focusstack,     {.i = +1 } },
	{ Super,              	       	XK_k, 			focusstack,     {.i = -1 } },
	
	{ Super|Shift,      		       	XK_j,      	inplacerotate,  {.i = +1} },
	{ Super|Shift,             		 	XK_k,      	inplacerotate,  {.i = -1} },
	{ Super,                       	XK_h,      	inplacerotate,  {.i = +2} },
	{ Super,                       	XK_l,      	inplacerotate,  {.i = -2} },
	
	{ Super,                       	XK_i,      	incnmaster,     {.i = +1 } },
	{ Super,                       	XK_o,      	incnmaster,     {.i = -1 } },
	
	{ Super|Shift,             			XK_h,      	setmfact,       {.f = -0.05} },
	{ Super|Shift,             			XK_l,      	setmfact,       {.f = +0.05} },
	
	{ Super|Alt,              			XK_h,      	incrgaps,       {.i = +5 } },
	{ Super|Alt,              			XK_l,      	incrgaps,       {.i = -5 } },
	
	{ Super|Alt|Shift,    					XK_h,      	incrogaps,      {.i = +5 } },
	{ Super|Alt|Shift,    					XK_l,      	incrogaps,      {.i = -5 } },

	{ Super|Alt|Ctrl,  							XK_h,	      incrigaps,      {.i = +5 } },
	{ Super|Alt|Ctrl,  							XK_l,	      incrigaps,      {.i = -5 } },
	
	{ Super,       									XK_Home,		togglegaps,     {0} },
	{ Super, 												XK_End, 	  defaultgaps,    {0} },
	
	{ Super,                       	XK_y,       incrihgaps,     {.i = +5 } },
	{ Super,                       	XK_o,       incrihgaps,     {.i = -5 } },
	
	{ Super|Ctrl,           				XK_y,       incrivgaps,     {.i = +5 } },
	{ Super|Ctrl,           				XK_o,       incrivgaps,     {.i = -5 } },
	
	{ Super|Alt,              			XK_y,       incrohgaps,     {.i = +5 } },
	{ Super|Alt,              			XK_o,       incrohgaps,     {.i = -5 } },
	
	{ Super|Shift,             			XK_y,       incrovgaps,     {.i = +5 } },
	{ Super|Shift,             			XK_o,       incrovgaps,     {.i = -5 } },	
	
	{ Super|Shift,             			XK_Return,  zoom,           {0} },
	{ Super,                       	XK_Tab,     view,           {0} },
	{ Super,                       	XK_a,       toggleopacity,  {0} },
	{ Super,                       	XK_q,       killclient,     {0} },
	{ Super,                       	XK_m,       setlayout,      {.v = &layouts[0]} },
	{ Super,                       	XK_f,       setlayout,      {.v = &layouts[1]} },
	{ Super,                       	XK_t,       setlayout,      {.v = &layouts[2]} },
	{ Super,                       	XK_g,       setlayout,      {.v = &layouts[3]} },
	{ Super,                       	XK_s, 	    setlayout,      {.v = &layouts[4]} },
	
	{ Super|Shift,             			XK_space,   setlayout,      {0} },
	{ Super|Shift,             			XK_f,       togglefloating, {0} },
	
	{ Super,                       	XK_Down,    moveresize,     {.v = "0x 25y 0w 0h" } },
	{ Super,                       	XK_Up,      moveresize,     {.v = "0x -25y 0w 0h" } },
	{ Super,                       	XK_Right,   moveresize,     {.v = "25x 0y 0w 0h" } },
	{ Super,                       	XK_Left,    moveresize,     {.v = "-25x 0y 0w 0h" } },
	
	{ Super|Shift,             			XK_Down,    moveresize,     {.v = "0x 0y 0w 25h" } },
	{ Super|Shift,             			XK_Up,      moveresize,     {.v = "0x 0y 0w -25h" } },
	{ Super|Shift,             			XK_Right,   moveresize,     {.v = "0x 0y 25w 0h" } },
	{ Super|Shift,             			XK_Left,    moveresize,     {.v = "0x 0y -25w 0h" } },
	
	{ Super,                       	XK_0,       view,           {.ui = ~0 } },
	{ Super|Shift,             			XK_0,       tag,            {.ui = ~0 } },
	
	{ Super,                       	XK_comma,   focusmon,       {.i = -1 } },
	{ Super,                       	XK_period,  focusmon,       {.i = +1 } },
	{ Super|Shift,             			XK_comma,   tagmon,         {.i = -1 } },
	{ Super|Shift,             			XK_period,  tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                       0)
	TAGKEYS(                        XK_2,                       1)
	TAGKEYS(                        XK_3,                       2)
	TAGKEYS(                        XK_4,                       3)
	TAGKEYS(                        XK_5,                       4)
	TAGKEYS(                        XK_6,                       5)
	{ Super|Shift,             			XK_q,       quit,         	{0} },
	{ Super,                      	XK_r,		  	quit,         	{1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask     button         function        argument */
	{ ClkLtSymbol,          0,             Button1,       setlayout,      {0} },
	{ ClkLtSymbol,          0,             Button3,       setlayout,      {.v = &layouts[2]} },

	{ ClkClientWin,         Super,         Button1,       movemouse,      {0} },
	{ ClkClientWin,         Super,         Button2,       togglefloating, {0} },
	{ ClkClientWin,         Super,         Button3,       resizemouse,    {0} },
	{ ClkTagBar,            0,             Button1,       view,           {0} },
	{ ClkTagBar,            0,             Button3,       toggleview,     {0} },
	{ ClkTagBar,            Super,         Button1,       tag,            {0} },
	{ ClkTagBar,            Super,         Button3,       toggletag,      {0} },
};

