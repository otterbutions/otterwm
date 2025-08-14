/* See LICENSE file for copyright and license details. */
#include "colors.h"

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating	issticky   monitor */
	{ "XCalc",     "xcalc",       "Calculator",      0,	1,            0,           -1 }
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	{ "",      tile }    /* first entry is default */
};

/* key definitions */
#define MODKEY Mod1Mask
#define ROTKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define SET_LANG(lang) { .v = (const char*[]){ "setxkbmap", "-layout", lang, NULL } }
#define VOL(mod_vol) { .v = (const char*[]){ "mixer", mod_vol, NULL } }
#define BRIGHT(mod_bri, amount) { .v = (const char*[]){ "backlight", mod_bri, amount, NULL } }
#define POWER { .v = (const char*[]){ "doas", "poweroff", NULL } }
#define RESET { .v = (const char*[]){ "doas", "shutdown", "-r", "now", NULL } }

#define TERM { .v = (const char*[]){ "st", NULL } }
#define WWW { .v = (const char*[]){ "firefox", NULL } }
#define FILE { .v = (const char*[]){ "pcmanfm", NULL } }

/* dmenu */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", gray2, "-nf", gray3, "-sb", selected, "-sf", gray1, NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,            						XK_Return, spawn,          TERM },
	{ MODKEY,             					XK_a,			 spawn,          FILE },
	{ MODKEY,            						XK_s,			 spawn,          WWW },
	{ MODKEY|ShiftMask,            	XK_s,			 togglesticky, 	 {0} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_q,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_w,      incnmaster,     {.i = 0 } },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_j,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_k,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,						XK_c,	zoom,		   {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	//{ MODKEY,                     XK_t,      setlayout,      {.v = &layouts[0]} },
	//{ MODKEY,                     XK_f,      setlayout,      {.v = &layouts[1]} },
	//{ MODKEY,                     XK_m,      setlayout,      {.v = &layouts[2]} },
	//{ MODKEY,                     XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	TAGKEYS(                        XK_1,      0)
	TAGKEYS(                        XK_2,      1)
	TAGKEYS(                        XK_3,      2)
	TAGKEYS(                        XK_4,      3)
	TAGKEYS(                        XK_5,      4)
	TAGKEYS(                        XK_6,      5)
	TAGKEYS(                        XK_7,      6)
	TAGKEYS(                        XK_8,      7)
	TAGKEYS(                        XK_9,      8)
	{ MODKEY|ControlMask,						XK_w,			 toggleWorkMode, {0}, },
	{ MODKEY|ShiftMask,             XK_e,	     quit,           {0} },
	{ MODKEY|ControlMask,						XK_h,	 		 spawn,					 BRIGHT("+", "5") },
	{ MODKEY|ControlMask,						XK_l,			 spawn,					 BRIGHT("-", "5") },
	{ MODKEY|ControlMask,						XK_k,			 spawn,					 VOL("vol=+0.05") },
	{ MODKEY|ControlMask,						XK_j,			 spawn,					 VOL("vol=-0.05") },
	{ MODKEY|ControlMask,						XK_s,			 spawn,					 SET_LANG("us") },
	{ MODKEY|ControlMask,						XK_d,			 spawn,					 SET_LANG("jp") },
	{ MODKEY|ControlMask,						XK_f,			 spawn,					 SET_LANG("fr") },
	{ 0,											0x1008ff13,			 spawn,					 VOL("vol=+0.10") },
	{ 0,											0x1008ff11,			 spawn,					 VOL("vol=-0.10") },
	{ 0,											0x1008ff2a,			 spawn,					 POWER },
	{ ControlMask,											0x1008ff2a,			 spawn,					 RESET },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

