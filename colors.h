static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "DejaVu Serif:size=12" };
static const char dmenufont[]       = "DejaVu Serif:size=12";
static const char gray1[]       = "#DCDCDC";
static const char gray2[]       = "#CFD3DA";
static const char gray3[]       = "#373737";
static const char gray4[]       = "#1D2021";
static const char bgcolor[]       = "#C1BDE1";	/* Wallpaper Color */
static const char selected[]       = "#6F66B7";
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { gray3, gray2, gray3 },
    [SchemeSel]  = { gray1, selected,  gray3  },
};
