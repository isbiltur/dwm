/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const double activeopacity   = 1.0f;     /* Window opacity when it's focused (0 <= opacity <= 1) */
static const double inactiveopacity = 0.7f;   /* Window opacity when it's inactive (0 <= opacity <= 1) */
static       Bool bUseOpacity       = True;     /* Starts with opacity on any unfocused windows */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6" };

static const Rule rules[] = {
    /* class            instance  title   tags mask   switch    float mon */
    {"Thunderbird",     NULL,     NULL,   1 << 5,     1,        0,    -1},
    {"Gimp",            NULL,     NULL,   1 << 5,     1,        0,    -1},
    {"firefox",         NULL,     NULL,   1 << 2,     1,        0,    -1},
    {"Chromium",        NULL,     NULL,   1 << 2,     1,        0,    -1},
    {"LibreWolf",       NULL,     NULL,   1 << 2,     1,        0,    -1},
    {"qBittorrent",     NULL,     NULL,   1 << 4,     1,        0,    -1},
	  { "st",         		NULL,     NULL,   0,          0,        1,    -1},
    {"kitty",           NULL,     NULL,   0,          0,        1,    -1},
    {"Alacritty",       NULL,     NULL,   0,          0,        1,    -1},
    {"Tor Browser",     NULL,     NULL,   1 << 4,     1,        0,    -1},
    {"GParted",         NULL,     NULL,   0,          0,        1,    -1},
};

/* layout(s) */
static const float mfact     = 0.6; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      monocle },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      tile },
	{ "HHH",      grid },
};

/* key definitions */
#define Super   Mod4Mask
#define Alt     Mod1Mask
#define Shift   ShiftMask
#define Ctrl    ControlMask

#define TAGKEYS(KEY, TAG)                                         \
{Super,               KEY,                view,           {.ui = 1 << TAG}},\
{Super | Ctrl,        KEY,                toggleview,     {.ui = 1 << TAG}},\
{Super | Shift,       KEY,                tag,            {.ui = 1 << TAG}},\
{Super | Ctrl | Shift,KEY,                toggletag,      {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
/*#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }*/

/* commands */
/*static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };*/

static const Key keys[] = {
	/* modifier                     key        function        argument */
/*	{ Super,                  XK_p,      spawn,          {.v = dmenucmd } },
	{ Super|Shift,             XK_Return, spawn,          {.v = termcmd } },
	{ Super,                   XK_b,      togglebar,      {0} },*/
	{ Super|Shift,             XK_b,      hideborder,     {0} },
	{ Super,                   XK_j,      focusstack,     {.i = +1 } },
	{ Super,                   XK_k,      focusstack,     {.i = -1 } },
	{ Super|Shift,             XK_j,      inplacerotate,  {.i = +1} },
	{ Super|Shift,             XK_k,      inplacerotate,  {.i = -1} },
	{ Super,                   XK_h,      inplacerotate,  {.i = +2} },
	{ Super,                   XK_l,      inplacerotate,  {.i = -2} },
	{ Super,                   XK_i,      incnmaster,     {.i = +1 } },
	{ Super,                   XK_o,      incnmaster,     {.i = -1 } },
	{ Super|Shift,             XK_h,      setmfact,       {.f = -0.05} },
	{ Super|Shift,             XK_l,      setmfact,       {.f = +0.05} },
	{ Super|Shift,             XK_Return, zoom,           {0} },
	{ Super,                   XK_Tab,    view,           {0} },
	{ Super,                   XK_a,      toggleopacity,  {0} },
	{ Super,                   XK_q,      killclient,     {0} },
	{ Super,                   XK_m,      setlayout,      {.v = &layouts[0]} },
	{ Super,                   XK_f,      setlayout,      {.v = &layouts[1]} },
	{ Super,                   XK_t,      setlayout,      {.v = &layouts[2]} },
	{ Super,                   XK_g,      setlayout,      {.v = &layouts[3]} },
	{ Super|Shift,             XK_space,  setlayout,      {0} },
	{ Super|Shift,             XK_f,      togglefloating, {0} },
	{ Super,                   XK_0,      view,           {.ui = ~0 } },
	{ Super|Shift,             XK_0,      tag,            {.ui = ~0 } },
/*	{ Super,                   XK_comma,  focusmon,       {.i = -1 } },
	{ Super,                   XK_period, focusmon,       {.i = +1 } },
	{ Super|Shift,             XK_comma,  tagmon,         {.i = -1 } },
	{ Super|Shift,             XK_period, tagmon,         {.i = +1 } },*/
	TAGKEYS(                   XK_1,                      0)
	TAGKEYS(                   XK_2,                      1)
	TAGKEYS(                   XK_3,                      2)
	TAGKEYS(                   XK_4,                      3)
	TAGKEYS(                   XK_5,                      4)
	TAGKEYS(                   XK_6,                      5)
/*	TAGKEYS(                  XK_7,                      6)
	TAGKEYS(                   XK_8,                      7)
	TAGKEYS(                   XK_9,                      8)*/
	{ Super|Shift,             XK_q,      quit,           {0} },
	{ Super|Shift,             XK_r,      quit,           {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
/*	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },*/
	{ ClkClientWin,         Super,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         Super,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         Super,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,             Button1,        view,           {0} },
	{ ClkTagBar,            0,             Button3,        toggleview,     {0} },
	{ ClkTagBar,            Super,         Button1,        tag,            {0} },
	{ ClkTagBar,            Super,         Button3,        toggletag,      {0} },
};

