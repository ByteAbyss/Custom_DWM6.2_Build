/* See LICENSE file for copyright and license details. */

/* Status Bar */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */

/* Gap Config */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 20;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */

/* appearance */
static const unsigned int borderpx  = 6;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const char *fonts[]          = {"Hack Nerd Font:size=15"};
static const char dmenufont[]       = "Hack Nerd Font:size=15";
/* Colors */ 
static const char yell1[]	    = "#fae502";
static const char cyan[]        = "#005577";
static const char navy[]	    = "#000080";
static const char dgray[]	    = "#000000";	
static const char teal[]        = "#008080";
static const char white[]	    = "#FFFFFF";
static const char black[]       = "#000000";
static char normbgcolor[]       = "#222222";
static char normbordercolor[]   = "#444444";
static char normfgcolor[]       = "#bbbbbb";
static char selfgcolor[]        = "#eeeeee";
static char selbordercolor[]    = "#770000";
static char selbgcolor[]        = "#005577";

static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  navy  },
};


/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", ""};
/* Laptop : 2 (1) , LG : 0 , --killled-> Samsung: 1 , Focussed Window: -1 */ 

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Chromium", NULL,	  NULL,	      	0,	        False, 	        -1},
	{ "Mate-calc", "mate-calce", NULL,	0,  	    True,	        -1},	
	{ "Vivaldi-stable", NULL, NULL, 	1 << 0,     False, 	         0},
	{ "Termite",   "termite",  "tmux",	1 << 1,     False,  	     0},
	{ "Termite",   "termite",  NULL,	0,	        False,  	    -1},
	{ "jetbrains-pycharm-ce", NULL, NULL,1 << 2,    False,           0},
	{ "Dbeaver", NULL, NULL,			1 << 2,     False,           0},
	{ "Steam",   NULL,  NULL,	      	1 << 4,	    False,           0},
	{ "Thunar",   "thunar",  NULL,	    1 << 3,	    False,           0},	
	{ "Thunderbird",  "Mail",  NULL,	1 << 6,	    False,           0},
	{ "Ristretto", "ristretto", NULL,	0,		    False,	         0},
	{ "feh", "feh",	 NULL,	      		1 << 0,	    False,           1},
	{ "Deadbeef",	 "deadbeef",NULL,	1 << 5,	    True,            0},
	{ "Clementine",	 "clementine",NULL,	1 << 5,	    False,           0},
	{ "libreoffice", NULL,	  NULL,	    1 << 8,	    False,           0},
	{ "Ghb",	"ghb",	  "HandBrake",	1 << 8,	    False,           0},
	{ "Handbrake",  NULL,	  NULL,	    1 << 8,	    False,           0},
	{ "vlc",	 NULL,	  NULL,	      	1 << 5,	    False,           1},
	{ "mpv",	NULL,	  NULL,	      	1 << 5,	    False,           1},
	
};

/* mbp-mappings -- Special Keys */
#define XF86MonBrightnessDown   0x1008ff03
#define XF86MonBrightnessUp     0x1008ff02
#define XF86LauncherKB1         0x1008ff4a
#define XF86LauncherKB2         0x1008ff4b
#define XF86KbdBrightnessDown   0x1008ff06
#define XF86KbdBrightnessUp     0x1008ff05
#define XF86AudioPrev           0x1008ff16
#define XF86AudioPlay           0x1008ff14
#define XF86AudioNext           0x1008ff17
#define XF86AudioMute           0x1008ff12
#define XF86AudioLowerVolume    0x1008ff11
#define XF86AudioRaiseVolume	0x1008ff13
#define XF86AudioPause		    0x1008ff15

/* layout(s) */
static const float mfact     = 0.6; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{"况",      tile },    /* first entry is default */
	{"ﮊ ",      NULL },    /* no layout function means floating behavior */
	{"{#}",     monocle },
	{" ",      deck},
	{" ",      centeredmaster },
	{"| |",    centeredfloatingmaster },	
};

/* key definitions */
#define MODKEY Mod4Mask
/* Mod4Mask - Super Key */ /* Mod1Mask -- alt key */
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", cyan, "-sf", dgray, NULL };
static const char *termcmd[]  = { "termite", NULL };
static const char *vivaldi[]  = { "vivaldi-stable", NULL };
static const char *chrom[]    = { "chromium", NULL };
static const char *fm[]       = { "thunar", NULL };
static const char *ranger[]   = { "termite", "-e", "ranger", "/home/joe/", NULL };
static const char *pc[]       = { "pycharm", NULL };
static const char *vcode[]    = { "code", NULL}; 
static const char *bpy[]      = { "termite", "-e", "/usr/bin/bpython", NULL};  	
static const char *tunes[]    = { "termite", "-e", "ncmpcpp",  NULL };
static const char *scr[]      = { "scrot", "-q", "100", "%Y-%m-%d-%H-%M-%S.jpg",  NULL };
static const char *x_kill[]   = { "xkill", NULL };
static const char *calc[]     = { "mate-calc", NULL };
static const char *stats[]    = { "termite", "-e", "glances", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	/* -------------------------------- Program Shortcuts ------------------------------------------------------ */
	/* Terminals */
	{ MODKEY,	                    XK_t, 	   spawn,          {.v = termcmd } },
	
	/* Dev */
	{ MODKEY,                   	XK_p,	   spawn,          {.v = pc } },
	{ MODKEY|ShiftMask,            	XK_p,	   spawn,          {.v = bpy } },
	{ MODKEY|ShiftMask,            	XK_c,	   spawn,          {.v = vcode } },

	/* Web Browsers */
	{ MODKEY,                	    XK_w,	   spawn,          {.v = vivaldi } },
	{ MODKEY,                	    XK_c,	   spawn,          {.v = chrom  } },

	/* File Managers */ 	
	{ MODKEY,		                XK_f,      spawn,          {.v = fm } },
	{ MODKEY|ShiftMask,           	XK_f,	   spawn,          {.v = ranger } },
	
	/* ----------------------------  Tools ------------------------------------------------------------------------*/

	/* Launchers  */ 
	{MODKEY|ShiftMask,             XK_a,       spawn,          {.v = dmenucmd } },
	{MODKEY,		               XK_a,	   spawn,SHCMD("rofi -show run -font 'Hack Nerd Font 18'") },
    {MODKEY, 		               XK_x, 	   spawn,SHCMD("/usr/bin/xfce4-appfinder")},  	
	
	/* Change Wallpaper  */
	{MODKEY|ShiftMask,	       XK_o,	   spawn,SHCMD("xwallpaper --daemon --output DP-3 --zoom $(find /mnt/E-Space/Wallpaper/ -maxdepth 3 -type f -iname '*jpg' | shuf -n1) --output DP-0 --zoom $(find /mnt/E-Space/Wallpaper/ -maxdepth 3 -type f -iname '*jpg' | shuf -n1)")},
	
	{ MODKEY,                	XK_z,	   spawn,          {.v = calc } },
	{ MODKEY,                	XK_m,	   spawn,          {.v = tunes } },
	{ MODKEY,                   XK_Print,  spawn,          {.v = scr } },
	{ MODKEY, 			        XK_v,	   spawn,	       SHCMD("termite -e /opt/Vault") },		
	{ MODKEY, 			        XK_g,	   spawn,	       {.v = stats } },		

	/* Media Mappings */ 
	{ 0,             XF86AudioRaiseVolume,	spawn,SHCMD ("amixer -q -D pulse sset Master 5%+; exec pkill -RTMIN+10")},
	{ 0,             XF86AudioLowerVolume,  spawn,SHCMD ("amixer -q -D pulse sset Master 5%-; exec pkill -RTMIN+10") },
	{ 0,	    	 XF86AudioMute,		spawn,SHCMD ("amixer -q -D pulse sset Master toggle; exec pkill -RTMIN+10")},	
	{ 0,             XF86AudioPlay,		spawn,SHCMD ("playerctl play")},
	{ 0,             XF86AudioPause,	spawn,SHCMD ("playerctl pause")},	
	{ 0,        	 XF86AudioNext,		spawn,SHCMD ("playerctl next")},
	{ 0,             XF86AudioPrev,		spawn,SHCMD ("playerctl previous")},
	
	/* ----------------------------- Navigation Key Bindings  --------------------------------------------------------- */ 

	/* Toggle Bar */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	
	/* Stack Focus */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	
	/* Rotate Through Stack */
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },

	/*Resize Left / Right  */
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,           XK_l,      setcfact,       {.f = +0.25} },
	{ MODKEY|ControlMask,           XK_h,      setcfact,       {.f = -0.25} },
	{ MODKEY|ControlMask,           XK_o,      setcfact,       {.f =  0.00} },	

	/* Mannually Update Gaps*/ 
	{ MODKEY,                       XK_minus,  incrgaps,       {.i = +1 } }, 
	{ MODKEY,                       XK_equal,  incrgaps,       {.i = -1 } }, 
	{ MODKEY|ShiftMask,             XK_equal,  defaultgaps,    {0} },

	/* Options for Vanity Gaps -- Overkill ---- 
	{ MODKEY|Mod1Mask,              XK_h,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_l,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },*/


	/* Make Master */
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	
	/* Kill Window - Options */
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	/* - Stubborn Program -*/
	{ MODKEY, 	     	        XK_Escape, spawn, 	   {.v = x_kill } },
	
	/* Set Layouts Mod + Control  + key  Tile , Float , Monacle ,Deck , Center */
	{ MODKEY|ControlMask,           XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ControlMask,           XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ControlMask,           XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ControlMask,           XK_d,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ControlMask,           XK_c,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ControlMask,           XK_space,  setlayout,      {.v = &layouts[5]} },

	/* Cycle through layouts  */
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	/*Toggle Floating */
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

	/*Toggle Left (comma ) / Right (period) between monitors. */
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },

	/* Tag to work areas  */
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	
	/* Shutdown | Reboot Computer / Exit DWM  */
	{MODKEY|ControlMask,  		XK_x, 	spawn, 
		SHCMD("/usr/local/bin/arcolinux-logout")},		
	
	/*Lock Screen  */
	{MODKEY|ControlMask,		XK_s, 	spawn, 
		SHCMD("/usr/bin/slimlock")}, 

	/*Quit DWM */
	{MODKEY|ShiftMask,              XK_x,      quit,           {0} },

};


/*---------------------  button definitions ---------------------------------------------------- */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

