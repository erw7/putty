#include <windows.h>
#ifndef AUTO_WINSOCK
#ifdef WINSOCK_TWO
#include <winsock2.h>
#else
#include <winsock.h>
#endif
#endif
#include <stdio.h>
#include "putty.h"

static unsigned char win2koi[] =
{
      0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
     32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
     48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
     64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
     80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
     96, 97, 98, 99,100,101,102,103,104,105,106,107,108,109,110,111,
    112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,
    128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,
    144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
    160,161,162,163,164,189,166,167,179,169,180,171,172,173,174,183,
    176,177,182,166,173,181,182,183,163,185,164,187,188,189,190,167,
    225,226,247,231,228,229,246,250,233,234,235,236,237,238,239,240,
    242,243,244,245,230,232,227,254,251,253,255,249,248,252,224,241,
    193,194,215,199,196,197,214,218,201,202,203,204,205,206,207,208,
    210,211,212,213,198,200,195,222,219,221,223,217,216,220,192,209
};

static unsigned char koi2win[] =
{
      0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
     32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
     48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
     64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
     80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
     96, 97, 98, 99,100,101,102,103,104,105,106,107,108,109,110,111,
    112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,
    128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,
    144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
    160,161,162,184,186,165,179,191,168,169,170,171,172,180,174,175,
    176,177,178,168,170,181,178,175,184,185,186,187,188,165,190,191,
    254,224,225,246,228,229,244,227,245,232,233,234,235,236,237,238,
    239,255,240,241,242,243,230,226,252,251,231,248,253,249,247,250,
    222,192,193,214,196,197,212,195,213,200,201,202,203,204,205,206,
    207,223,208,209,210,211,198,194,220,219,199,216,221,217,215,218
};

static unsigned char xlatWIN1250toISO88592[] =
{
      0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
     32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
     48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
     64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
     80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
     96, 97, 98, 99,100,101,102,103,104,105,106,107,108,109,110,111,
    112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,
    128,129, 39,131, 34, 46,124,124,136, 47,169, 60,166,171,174,172,
    144, 96, 39, 34, 34, 42, 45, 45,152, 84,185, 62,182,187,190,188,
    160,183,162,163,164,161,124,167,168, 99,170, 34, 39,173, 82,175,
    176, 63,178,179,180,117,182,255,184,177,186, 34,165,189,181,191,
    192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,
    208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,
    224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,
    240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255
};

static unsigned char xlatISO88592toWIN1250[] =
{
      0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
     32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
     48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
     64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
     80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
     96, 97, 98, 99,100,101,102,103,104,105,106,107,108,109,110,111,
    112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,
    128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,
    144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
    160,165,162,163,164,188,140,167,168,138,170,141,143,173,142,175,
    176,185,178,179,180,190,156,161,184,154,186,157,159,189,158,191,
    192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,
    208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,
    224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,
    240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255
};

unsigned char xlat_kbd2tty(unsigned char c)
{
    if(cfg.xlat_enablekoiwin)
	return win2koi[c];
    else if (cfg.xlat_88592w1250)
        return xlatWIN1250toISO88592[c];
    return c;
}

unsigned char xlat_tty2scr(unsigned char c)
{
    if(cfg.xlat_enablekoiwin)
	return koi2win[c];
    else if (cfg.xlat_88592w1250)
        return xlatISO88592toWIN1250[c];
    return c;
}


static unsigned char latkbd2_win[]=
{
      0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
     32, 33,221, 35, 36, 37, 38,253, 40, 41, 42,178,225,186,254, 46,
     48, 49, 50, 51, 52, 53, 54, 55, 56, 57,198,230,193,179,222, 44,
     64,212,200,209,194,211,192,207,208,216,206,203,196,220,210,217,
    199,201,202,219,197,195,204,214,215,205,223,245,191,250, 94,170,
     96,244,232,241,226,243,224,239,240,248,238,235,228,252,242,249,
    231,233,234,251,229,227,236,246,247,237,255,213,175,218,126,127,
    128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,
    144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
    160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,
    176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,
    192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,
    208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,
    224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,
    240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255
};

unsigned char xlat_latkbd2win(unsigned char  c)
{
    if(cfg.xlat_capslockcyr)
	return latkbd2_win[c];
    return c;
}
