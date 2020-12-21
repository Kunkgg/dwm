/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 20;       /* horizontal padding of bar */
static const char *fonts[]          = { "monospace:size=12" };
static const char dmenufont[]       = "monospace:size=12";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#222222";
static char selbordercolor[]        = "#49AEE6";
static char selbgcolor[]            = "#FEA44C";
static char *colors[][3] = {
    /*               fg           bg           border   */
    [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
    [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;

static const char terminal[] = "alacritty";
static const char fm[] = "ranger";
const char *spcmd1[] = {terminal, "--title", "spterm", "--dimensions", "120", "34", NULL };
const char *spcmd2[] = {terminal, "--title", "spfm", "--dimensions", "144", "41", "-e", fm, NULL };
/* const char *spcmd3[] = {"keepassxc", NULL }; */

static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spfm",        spcmd2},
	/* {"keepassxc",   spcmd3}, */
};
/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* xprop(1):
     *      WM_CLASS(STRING) = instance, class
     *      WM_NAME(STRING) = title
     */
	/* class                   instance         title           tags mask  iscentered  isfloating  monitor */
    { "Gimp",                  NULL,            NULL,           1 << 2,    0,          1,          -1 },
    { "VirtualBox Manager",    NULL,            NULL,           1 << 2,    0,          0,          -1 },
    { "VirtualBox",            NULL,            NULL,           1 << 2,    0,          1,          -1 },
    { "firefox",               NULL,            NULL,           0,         0,          0,          -1 },
    { "Brave-browser",         NULL,            NULL,           0,         0,          0,          -1 },
    { "Pavucontrol",           NULL,            NULL,           0,         1,          1,          -1 },
    { "Nvidia-settings",       NULL,            NULL,           0,         1,          1,          -1 },
    { "Anki",                  NULL,            NULL,           0,         1,          1,          -1 },
    { "Blueman-manager",       NULL,            NULL,           0,         1,          1,          -1 },
    { "Blueman-adapters",      NULL,            NULL,           0,         1,          1,          -1 },
    { "Blueman-assistant",     NULL,            NULL,           0,         1,          1,          -1 },
    { "Ibus-setup",            NULL,            NULL,           0,         1,          1,          -1 },
    { "Ibus-setup-libpinyin",  NULL,            NULL,           0,         1,          1,          -1 },
    { "Steam",                 NULL,            NULL,           1 << 3,    0,          1,          -1 },
    { "URxvt",                 "pick emoji",    "fzf_emoji",    0,         1,          1,          -1 },
    { "Electron",              "electron",      NULL,           1 << 8,    1,          1,          -1 },
    { "code-oss",              "code-oss",      NULL,           1 << 8,    1,          1,          -1 },
    { "Alacritty",             "Alacritty",     "Dict",         0,         1,          1,          -1 },
	{ NULL,                    "spterm",        NULL,           SPTAG(0),  1,          1,          -1 },
	{ NULL,                    "spfm",          NULL,           SPTAG(1),  1,          1,          -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
        /* symbol     arrange function */
        { "[]=",      tile },    /* first entry is default */
        { "><>",      NULL },    /* no layout function means floating behavior */
        { "[M]",      monocle },
        { "|M|",      centeredmaster },
        { ">M>",      centeredfloatingmaster },
        { "[@]",      spiral },
        { "[\\]",     dwindle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
        { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
        { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
        { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
        { MODKEY|Mod1Mask,              KEY,      toggletag,      {.ui = 1 << TAG} },
        /* { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, */
#define STACKKEYS(MOD,ACTION) \
        { MOD, XK_j,            ACTION##stack, {.i = INC(+1) } }, \
        { MOD, XK_k,            ACTION##stack, {.i = INC(-1) } }, \
        { MOD, XK_backslash,    ACTION##stack, {.i = PREVSEL } }, \
        { MOD, XK_a,            ACTION##stack, {.i = 0 } }, \
        { MOD, XK_z,            ACTION##stack, {.i = -1 } }, \
        /* { MOD, XK_q,     ACTION##stack, {.i = 0 } }, \ */
        /* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
        /* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run_history", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
/* static const char scratchpadname[] = "ScratchPad"; */
/* static const char *scratchpadcmd[] = { "urxvtc", "-name", scratchpadname, "-geometry", "96x32", NULL }; */
/* static const char *scratchpadcmd[] = { "alacritty", "--title", scratchpadname, "--dimensions", "96", "32", NULL }; */

#include <X11/XF86keysym.h>
#include "shiftview.c"
static Key keys[] = {
        /* modifier                     key        function        argument */
        STACKKEYS(MODKEY,                          focus)
        STACKKEYS(MODKEY|ShiftMask,                push)
        TAGKEYS(                        XK_1,           0)
        TAGKEYS(                        XK_2,           1)
        TAGKEYS(                        XK_3,           2)
        TAGKEYS(                        XK_4,           3)
        TAGKEYS(                        XK_5,           4)
        TAGKEYS(                        XK_6,           5)
        TAGKEYS(                        XK_7,           6)
        TAGKEYS(                        XK_8,           7)
        TAGKEYS(                        XK_9,           8)
        { MODKEY,                       XK_0,           view,           {.ui = ~0 } },
        { MODKEY|ShiftMask,             XK_0,           tag,            {.ui = ~0 } },

        { MODKEY,                       XK_Tab,         view,           {0} },
        { MODKEY,                       XK_semicolon,   shiftview,      { .i = 1 } },
        { MODKEY,                       XK_comma,       shiftview,      { .i = -1 } },
        { MODKEY,                       XK_Page_Down,   shiftview,      { .i = 1 } },
        { MODKEY,                       XK_Page_Up,     shiftview,      { .i = -1 } },

        /* { MODKEY|ShiftMask,             XK_d,           togglegaps,     {0} }, */
        /* { MODKEY,                       XK_z,           incrgaps,       {.i = +1 } }, */
        /* { MODKEY|ShiftMask,             XK_z,           incrgaps,       {.i = -1 } }, */
        { MODKEY,                       XK_f,           togglefullscr,  {0} },
        { MODKEY,                       XK_l,           setmfact,       {.f = +0.05} },
        { MODKEY,                       XK_h,           setmfact,       {.f = -0.05} },
        { MODKEY,                       XK_b,           togglebar,      {0} },

        { MODKEY|ShiftMask,             XK_t,           setlayout,      {.v = &layouts[0]} },
        { MODKEY|ShiftMask,             XK_f,           setlayout,      {.v = &layouts[1]} },
        { MODKEY|ShiftMask,             XK_m,           setlayout,      {.v = &layouts[2]} },
        { MODKEY|ShiftMask,             XK_c,           setlayout,      {.v = &layouts[3]} },
        { MODKEY|ShiftMask,             XK_o,           setlayout,      {.v = &layouts[4]} },

        { MODKEY,                       XK_i,           incnmaster,     {.i = +1 } },
        { MODKEY|ShiftMask,             XK_i,           incnmaster,     {.i = -1 } },
        { MODKEY,                       XK_space,       zoom,           {0} },
        { MODKEY|ShiftMask,             XK_space,       togglefloating, {0} },
        { MODKEY,                       XK_s,           togglesticky,   {0} },
        { MODKEY|ShiftMask,		        XK_b,		    spawn,		    SHCMD("hover left") },
        { MODKEY|ShiftMask,		        XK_n,		    spawn,		    SHCMD("hover right") },
        { MODKEY,                       XK_q,           killclient,     {0} },

        { MODKEY,                       XK_Return,      spawn,          {.v = termcmd } },
        { MODKEY|ShiftMask,             XK_Return,      togglescratch,  {.ui = 0 } },
        { MODKEY,            			XK_grave,  	    togglescratch,  {.ui = 1 } },
        /* { MODKEY|ShiftMask,          XK_Return,      togglescratch,  {.v = scratchpadcmd } }, */
        /* { MODKEY,            		XK_x,	        togglescratch,  {.ui = 2 } }, */
        { MODKEY,                       XK_d,           spawn,          {.v = dmenucmd } },
};

/* button definitions */
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

void
setlayoutex(const Arg *arg)
{
    setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
viewex(const Arg *arg)
{
    view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
    view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
    toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
    tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
    toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
    tag(&((Arg){.ui = ~0}));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
    /* signum           function */
    { "focusstack",     focusstack },
    { "setmfact",       setmfact },
    { "togglebar",      togglebar },
    { "incnmaster",     incnmaster },
    { "togglefloating", togglefloating },
    { "focusmon",       focusmon },
    { "tagmon",         tagmon },
    { "zoom",           zoom },
    { "view",           view },
    { "viewall",        viewall },
    { "viewex",         viewex },
    { "toggleview",     view },
    { "toggleviewex",   toggleviewex },
    { "tag",            tag },
    { "tagall",         tagall },
    { "tagex",          tagex },
    { "toggletag",      tag },
    { "toggletagex",    toggletagex },
    { "killclient",     killclient },
    { "quit",           quit },
    { "setlayout",      setlayout },
    { "setlayoutex",    setlayoutex },
    { "xrdb",           xrdb },
    { "togglegaps",     togglegaps },
};
