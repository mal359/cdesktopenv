/*
 * CDE - Common Desktop Environment
 *
 * Copyright (c) 1993-2012, The Open Group. All rights reserved.
 *
 * These libraries and programs are free software; you can
 * redistribute them and/or modify them under the terms of the GNU
 * Lesser General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * These libraries and programs are distributed in the hope that
 * they will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with these libraries and programs; if not, write
 * to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301 USA
 */
/* $XConsortium: calctool.h /main/7 1996/10/29 14:10:36 mustafa $ */
/*                                                                      *
 *  calctool.h                                                          *
 *   Contains the none user interface includes for the Desktop          *
 *   Calculator.                                                        *
 *                                                                      *
 * (c) Copyright 1993, 1994 Hewlett-Packard Company			*
 * (c) Copyright 1993, 1994 International Business Machines Corp.	*
 * (c) Copyright 1993, 1994 Sun Microsystems, Inc.			*
 * (c) Copyright 1993, 1994 Novell, Inc. 				*
 */
#ifndef _calctool_h
#define _calctool_h 


#include <float.h>
#include <math.h>
#include <locale.h>
#include <X11/Intrinsic.h>
#include <Dt/UserMsg.h>
#include <Dt/DtNlUtils.h>

#ifdef XGETTEXT
#define  MSGFILE_LABEL    "dtcalc.label"
#define  MSGFILE_MESSAGE  "dtcalc.message"
#else
extern char *MSGFILE_LABEL ;
extern char *MSGFILE_MESSAGE ;
#endif

#define  DGET(s)          (s)
#define  LGET(s)          (char *) dgettext(MSGFILE_LABEL,   s)
#define  MGET(s)          (char *) dgettext(MSGFILE_MESSAGE, s)

#define  dgettext(f, s)   (s)
#define  bindtextdomain(f, s)

#ifndef NO_MESSAGE_CATALOG
# define _CLIENT_CAT_NAME "dtcalc"
extern char *_DtGetMessage(char *filename, int set, int n, char *s);
# define GETMESSAGE(set, number, string)\
    (_DtGetMessage(_CLIENT_CAT_NAME, set, number, string))
#else
# define GETMESSAGE(set, number, string)\
    string
#endif

#if !(defined(sun) && (_XOPEN_VERSION==3))
#ifndef DOMAIN
#define DOMAIN     1
#endif
#ifndef SING
#define SING       2
#endif
#ifndef OVERFLOW
#define OVERFLOW   3
#endif
#ifndef UNDERFLOW
#define UNDERFLOW  4
#endif
#ifndef TLOSS
#define TLOSS      5
#endif
#ifndef PLOSS
#define PLOSS      6
#endif
#ifndef HUGE
#define HUGE       FLT_MAX
#endif
#endif  /* sun */

#include <stdlib.h>

#define  MEM	1
#define  FIN	2

#define FIN_EPSILON 1.0e-10
#define MAX_FIN_ITER 1000

#define  MP_SIZE      150     /* Size of the multiple precision values. */

/* Various pseudo events used by the dtcalc program. */
#define  KEYBOARD_DOWN    100    /* Keyboard character was pressed. */
#define  KEYBOARD_UP      101    /* Keyboard character was released. */
#define  LASTEVENTPLUSONE 102    /* Not one of the above. */
#define  F4_PRESS         103    
#define  ARROW            104
#define  TAB              105
#define  CONTROL          106
#define  SHIFT            107
#define  SPACE            108
#define  ESCAPE           109
#define  META             110
#define  ALT              111
#define  NUM_LOCK         77

enum base_type { BIN, OCT, DEC, HEX } ;      /* Base definitions. */

/* Command line options (for saving). */
enum cmd_type { CMD_ACC,    CMD_MODE,  CMD_BASE,  CMD_DISP,  CMD_MENU_BAR,
                CMD_SESSION,  CMD_TRIG,  CMD_DUMMY } ;

/* Frame/Canvas/Pixwin types. */
enum fcp_type  { FCP_KEY, FCP_REG, FCP_MODE, FCP_FIN_REG } ;

/* Help string types. */
enum help_type { H_ACC,        H_BASE,    H_CON,     H_EXCH,
                 H_FUN,        H_MODE,    H_NUM,
                 H_RCL,        H_STO,     H_TRIG,
                 H_ABUT,       H_AFRAME,  H_APANEL,
                 H_APPEARANCE, H_APPLY,   H_ATEXT,   H_CFCBUT,
                 H_CFDESC,     H_CFFRAME, H_CFNO,    H_CFPANEL,
                 H_CFVAL,      H_DEF,     H_DISPLAY, H_PFRAME,
                 H_PPANEL,     H_RESET,   H_STYLE,   H_DUMMY } ;

/* Pseudo panel items. */
enum item_type { BASEITEM, TTYPEITEM, NUMITEM,  HYPITEM,
                 INVITEM,  OPITEM,    MODEITEM, DISPLAYITEM } ;

/* Motif labels for various items. */
enum label_type { L_LCALC,  L_UCALC,  L_CONNO,   L_NEWCON, L_FUNNO,
                  L_NEWFUN, L_MEMT,   L_PROPT,   L_DESC,   L_VALUE,
                  L_CONB,   L_FUNB,   L_FINMEMT, L_DUMMY } ;

/* Popup menu types. */
enum menu_type { M_ACC,  M_BASE, M_CON,  M_EXCH, M_FUN,  M_MODE,
                 M_NUM,  M_RCL,  M_STO,  M_TRIG, M_NONE
} ;

/* Message string types. */
enum mess_type { MESS_PARAM, MESS_CON,  MESS_DUMMY } ;

/* Calculator modes. */
enum mode_type { FINANCIAL, LOGICAL, SCIENTIFIC } ;

enum mp_type { MP_ADD2A, MP_ADD2B, MP_PART1, MP_ASIN,   /* MP error types. */
               MP_ATAN,  MP_CHKC,
               MP_CHKD,  MP_CHKE,  MP_CHKF,  MP_CHKG,
               MP_CHKH,  MP_CHKI,  MP_CHKJ,  MP_CHKL,
               MP_CHKM,  MP_CHKN,  MP_CMD,   MP_CMR,
               MP_CQM,   MP_DIVA,  MP_DIVB,  MP_DIVIA,
               MP_DIVIB, MP_EXPA,  MP_EXPB,  MP_EXP1,
               MP_LNA,   MP_LNB,   MP_LNSA,
               MP_LNSB,  MP_LNSC,  MP_MULA,  MP_MULB,
               MP_MULC,  MP_MUL2A, MP_MUL2B, MP_MULQ,
               MP_NZRA,  MP_NZRB,  MP_NZRC,
               MP_OVFL,  MP_PI,    MP_PWRA,
               MP_PWRB,  MP_PWR2A, MP_PWR2B, MP_RECA,
               MP_RECB,  MP_RECC,  MP_RECD,  MP_ROOTA,
               MP_ROOTB, MP_ROOTC, MP_ROOTD,
               MP_ROOTE, MP_ROOTF, MP_SETB,
               MP_SETC,  MP_SETD,  MP_SETE,  MP_SIN,
               MP_SIN1,  MP_SQRT,  MP_TAN,   MP_DUMMY } ;

enum num_type { ENG, FIX, SCI } ;            /* Number display mode. */

enum op_type { OP_SET, OP_CLEAR, OP_NOP } ;  /* Operation item settings. */

enum opt_type { O_ACCVAL, O_ACCRANGE, O_BASE,     O_DISPLAY,
                O_MODE,   O_TRIG,     O_SESSION,  O_DUMMY } ;

enum prop_type { P_CHAR, P_ASCIIT, P_DUMMY } ;

/* Resources. */
enum res_type { R_ACCURACY, R_BASE,    R_DISPLAY, R_MODE,  R_FREGS,
                R_REGS,     R_TRIG,    R_BEEP,    R_ICON,  R_WORKSPACE,
                R_HEIGHT,   R_WIDTH,   R_X,       R_Y,     R_DISPLAYED,    
                R_REG0,     R_REG1,    R_REG2,    R_REG3,  R_REG4,    
                R_REG5,     R_REG6,    R_REG7,    R_REG8,  R_REG9,    
                R_FREG0,    R_FREG1,   R_FREG2,   R_FREG3, R_FREG4,
                R_FREG5,    R_MENUBAR, R_KEYS,    R_DUMMY } ;

enum trig_type { DEG, GRAD, RAD } ;          /* Trigonometric types. */

/* Usage message types. */
enum usage_type { USAGE1, USAGE2, USAGE3, U_DUMMY } ;

enum var_type { V_CANCEL,
                V_CLR,      V_CONFIRM,  V_CONTINUE,
                V_CONWNAME, V_ERROR,
                V_FUNWNAME, V_HYP,      V_INV,
                V_INVCON,   V_LCON,     V_LFUN,
                V_NOCHANGE, V_NUMSTACK, V_OPSTACK,  V_OWRITE,
                V_RANGE,    V_TRUE,     V_UCON,     V_UFUN,
                V_NORSAVE,  V_DUMMY } ;

/* Abbreviations for the dtcalc keyboard and menu equivalents. */

#define  KEY_BLNKD buttons[0].value       /* q */
#define  KEY_FUN   buttons[1].value       /* F */
#define  KEY_CON   buttons[2].value       /* # */
#define  KEY_KEYS  buttons[3].value       /* k */

#define  KEY_INT   buttons[4].value       /* CTL('i') */
#define  KEY_FRAC  buttons[5].value       /* CTL('f') */
#define  KEY_ABS   buttons[6].value       /* CTL('u') */
#define  KEY_EXP   buttons[7].value       /* E */

#define  KEY_ACC   buttons[8].value       /* A */
#define  KEY_STO   buttons[9].value       /* S */
#define  KEY_RCL   buttons[10].value       /* R */
#define  KEY_EXCH  buttons[11].value       /* X */

#define  KEY_BLNK1 buttons[12].value       /* q */
#define  KEY_BLNK2 buttons[13].value       /* q */
#define  KEY_BLNK3 buttons[14].value       /* q */
#define  KEY_BLNK4 buttons[15].value       /* q */

#define  KEY_BLNK5 buttons[16].value       /* q */
#define  KEY_BLNK6 buttons[17].value       /* q */
#define  KEY_BLNK7 buttons[18].value       /* q */
#define  KEY_BLNK8 buttons[19].value       /* q */

#define  KEY_BLNK9 buttons[20].value       /* q */
#define  KEY_BLNKA buttons[21].value       /* q */
#define  KEY_BLNKB buttons[22].value       /* q */
#define  KEY_BLNKC buttons[23].value       /* q */

#define  KEY_REC   buttons[24].value       /* r */
#define  KEY_SQR   buttons[25].value       /* @ */
#define  KEY_SQRT  buttons[26].value       /* s */
#define  KEY_PER   buttons[27].value       /* % */

#define  KEY_LPAR  buttons[28].value       /* ( */
#define  KEY_RPAR  buttons[29].value       /* ) */
#define  KEY_BSP   buttons[30].value       /* CTL('h') */
#define  KEY_CLR   buttons[31].value       /* del */

#define  KEY_D     buttons[32].value       /* d */
#define  KEY_E     buttons[33].value       /* e */
#define  KEY_F     buttons[34].value       /* f */
#define  KEY_CHS   buttons[35].value       /* C */

#define  KEY_A     buttons[36].value       /* a */
#define  KEY_B     buttons[37].value       /* b */
#define  KEY_C     buttons[38].value       /* c */
#define  KEY_MUL   buttons[39].value       /* x */

#define  KEY_7     buttons[40].value       /* 7 */
#define  KEY_8     buttons[41].value       /* 8 */
#define  KEY_9     buttons[42].value       /* 9 */
#define  KEY_DIV   buttons[43].value       /* / */

#define  KEY_4     buttons[44].value       /* 4 */
#define  KEY_5     buttons[45].value       /* 5 */
#define  KEY_6     buttons[46].value       /* 6 */
#define  KEY_SUB   buttons[47].value       /* - */

#define  KEY_1     buttons[48].value       /* 1 */
#define  KEY_2     buttons[49].value       /* 2 */
#define  KEY_3     buttons[50].value       /* 3 */
#define  KEY_ADD   buttons[51].value       /* + */

#define  KEY_0     buttons[52].value       /* 0 */
#define  KEY_PNT   buttons[53].value       /* . */
#define  KEY_EQ    buttons[54].value       /* = */
#define  KEY_QUIT  buttons[55].value       /* q */

/* these are the extra definitions for MODE, BASE, and DISP */
#define  KEY_BASE  buttons[56].value       /* B */
#define  KEY_DISP  buttons[57].value       /* D */
#define  KEY_MODE  buttons[58].value       /* M */
#define  KEY_TRIG  buttons[59].value       /* T */

#define  ACC_START 0                             /* 0 */
#define  ACC_END   9                             /* 9 */

#define  MEM_START 10                            /* 0 */
#define  MEM_END   19                            /* 9 */

#define  BASE_BIN  menu_entries[20].val          /* b */
#define  BASE_OCT  menu_entries[21].val          /* o */
#define  BASE_DEC  menu_entries[22].val          /* d */
#define  BASE_HEX  menu_entries[23].val          /* h */

#define  DISP_ENG  menu_entries[24].val          /* e */
#define  DISP_FIX  menu_entries[25].val          /* f */
#define  DISP_SCI  menu_entries[26].val          /* s */

#define  TRIG_DEG  menu_entries[27].val          /* d */
#define  TRIG_GRA  menu_entries[28].val          /* g */
#define  TRIG_RAD  menu_entries[29].val          /* r */

#define  MODE_BAS  menu_entries[30].val          /* b */
#define  MODE_FIN  menu_entries[31].val          /* f */
#define  MODE_LOG  menu_entries[32].val          /* l */
#define  MODE_SCI  menu_entries[33].val          /* s */

#define  KEY_TERM  mode_buttons[0].value         /* T */
#define  KEY_RATE  mode_buttons[1].value         /* CTL('r') */
#define  KEY_PV    mode_buttons[2].value         /* p */
#define  KEY_PMT   mode_buttons[3].value         /* P */
#define  KEY_FV    mode_buttons[4].value         /* v */
#define  KEY_PYR   mode_buttons[5].value         /* y */
#define  KEY_FCLR  mode_buttons[6].value         /* L */
#define  KEY_CTRM  mode_buttons[7].value         /* CTL('t') */
#define  KEY_DDB   mode_buttons[8].value         /* CTL('d') */
#define  KEY_SLN   mode_buttons[9].value         /* CTL('s') */
#define  KEY_SYD   mode_buttons[10].value        /* CTL('y') */

#define  KEY_LSFT  mode_buttons[16].value        /* < */
#define  KEY_RSFT  mode_buttons[17].value        /* > */
#define  KEY_16    mode_buttons[18].value        /* [ */
#define  KEY_32    mode_buttons[19].value        /* ] */
#define  KEY_OR    mode_buttons[20].value        /* | */
#define  KEY_AND   mode_buttons[21].value        /* & */
#define  KEY_NOT   mode_buttons[22].value        /* ~ */
#define  KEY_XOR   mode_buttons[23].value        /* ^ */
#define  KEY_XNOR  mode_buttons[24].value        /* n */

#define  KEY_INV   mode_buttons[32].value        /* i */
#define  KEY_HYP   mode_buttons[33].value        /* h */
#define  KEY_ETOX  mode_buttons[34].value        /* { */
#define  KEY_TTOX  mode_buttons[35].value        /* } */
#define  KEY_YTOX  mode_buttons[36].value        /* y */
#define  KEY_FACT  mode_buttons[37].value        /* ! */
#define  KEY_COS   mode_buttons[38].value        /* CTL('c') */
#define  KEY_SIN   mode_buttons[39].value        /* CTL('s') */
#define  KEY_TAN   mode_buttons[40].value        /* CTL('t') */
#define  KEY_LN    mode_buttons[41].value        /* N */
#define  KEY_LOG   mode_buttons[42].value        /* G */
#define  KEY_RAND  mode_buttons[43].value        /* ? */

#define  BCOLS          4          /* No of columns of buttons. */
#define  BROWS          14          /* No of rows of buttons. */
#define  CALC_CANCEL    1          /* Cancel button pressed on notice. */
#define  CALC_CONFIRM   2          /* Confirm button pressed on notice. */
#define  CTL(n)         n - 96     /* Generate control character value. */
#define  EQUAL(a, b)    !strncmp(a, b, strlen(b))
#define  EXTRA          4          /* Extra useful character definitions. */

#define  INC            { argc-- ; argv++ ; }
#define  IS_KEY(v, n)   (v == n)

#ifndef  LINT_CAST
#ifdef   lint
#define  LINT_CAST(arg)  (arg ? 0 : 0)
#else
#define  LINT_CAST(arg)  (arg)
#endif /*lint*/
#endif /*LINT_CAST*/

#define  MAXCMDS        (int) CMD_DUMMY   /* Max. no. of command line opts. */
#define  MAX_DIGITS     41         /* Maximum displayable number of digits. */

/* Maximum number of various graphics pieces. */
#define  MAXFCP         3          /* Max no of frames/canvases/pixwins. */
#define  MAXHELP        (int) H_DUMMY     /* Max. no. help strings. */
#define  MAXIMAGES      3          /* Maximum number of button images. */
#define  MAXITEMS       8          /* Maximum number of panel items. */
#define  MAXLABELS      (int) L_DUMMY     /* Max no. Motif label strings. */
#define  MAXMENUS       13         /* Maximum number of popup menus. */
#define  MAXMESS        (int) MESS_DUMMY  /* Max. no. message strings. */
#define  MAXMPERRS      (int) MP_DUMMY    /* Max. no. MP error types. */

#ifndef  MAXLINE
#define  MAXLINE        256               /* Length of character strings. */
#endif /*MAXLINE*/

#define  MAXBASES       4                 /* Max. no. of numeric bases. */
#define  MAXDISPMODES   3                 /* Max. no. of display modes. */
#define  MAXENTRIES     55                /* Max. no. of menu entries. */
#define  MAXMODES       3                 /* Max. no. of calculator modes. */
#define  MAXOPTS        (int) O_DUMMY     /* Max. no. option types. */
#define  MAXPSTRS       (int) P_DUMMY     /* Max. no. property strings. */
#define  MAXREGS        10                /* Max. no. of memory registers. */
#define  FINREGS        6                 /* Max. no. of Fin. memory regs. */
#define  MAXRESOURCES   (int) R_DUMMY     /* Max. number. of X resources. */
#define  MAXSTACK       256               /* Parenthese stack size. */
#define  MAXTRIGMODES   3                 /* Max. no. of trig. modes. */
#define  MAXUSAGE       (int) U_DUMMY     /* Max. no. usage strings. */
#define  MAXVKEYS       6                 /* No. of valid keys after error. */
#define  MAXVMESS       (int) V_DUMMY     /* Max. no. various messages. */

#define  MCOLS          8              /* No. of columns of "special" keys. */
#define  MROWS          2              /* No. of rows of "special" keys. */
#define  MODEKEYS       MCOLS * MROWS

#define  MAXCOLS        BCOLS
#define  MAXROWS        BROWS

#ifndef  MIN
#define  MIN(x,y)       ((x) < (y) ? (x) : (y))
#endif /*MIN*/

#define  NOBUTTONS      BROWS * BCOLS

#ifndef  RCNAME
#define  RCNAME         ".dtcalcrc"
#endif /*RCNAME*/

#define  TITEMS         NOBUTTONS + EXTRA      /* Total definitions. */

#ifndef  TRUE                    /* Boolean definitions. */
#define  TRUE           1
#endif /*TRUE*/

#ifndef  FALSE
#define  FALSE          0
#endif /*FALSE*/

typedef  unsigned long  BOOLEAN ;

struct button {
  char *str ;               /* Button display string. */
  char *str2 ;              /* Button display string, with key. */
  char value ;              /* Unique button keyboard equivalent. */
  enum op_type opdisp ;     /* Is button selected during operation? */
  enum menu_type mtype ;    /* Type of popup menu (if any). */
  char *resname ;           /* Button resource name. */
  void (*func)() ;          /* Function to obey on button press. */
} ;
extern struct button buttons[] ;           /* Calculator button values. */
extern struct button mode_buttons[] ;      /* Special "mode" buttons. */

struct menu_entry {
  char *str ;               /* Menu entry string to be displayed. */
  char val ;                /* Value when selected. */
} ;
extern struct menu_entry menu_entries[] ;  /* All the menu strings. */

struct menu {
  char *title ;             /* Menu title. */
  int  total ;              /* Number of menu entries. */
  int  mindex ;             /* Index into menu string array. */
  int  defval ;             /* Default menu item position (from 1). */
} ;
extern struct menu cmenus[] ;              /* Calculator menus. */

struct calcVars {                     /* Calctool variables and options. */
  char *appname ;                     /* Application name for resources. */
  char con_names[MAXREGS][MAXLINE] ;  /* Selectable constant names. */
  char cur_op ;                       /* Current arithmetic operation. */
  char current ;                      /* Current button/character pressed. */
  char display[MAXLINE] ;             /* Current calculator display. */
  char *exp_posn ;                    /* Position of the exponent sign. */
  char fnum[MAX_DIGITS+1] ;           /* Scratchpad for fixed numbers. */
  char fun_names[MAXREGS][MAXLINE] ;  /* Function names from .dtcalcrc. */
  char fun_vals[MAXREGS][MAXLINE] ;   /* Function defs from .dtcalcrc. */
  char *iconlabel ;                   /* The dtcalc icon label. */
  char old_cal_value ;                /* Previous calculation operator. */
  char *progname ;                    /* Name of this program. */
  char pstr[5] ;                      /* Current button text string. */
  char *selection ;                   /* Current [Get] selection. */
  char *shelf ;                       /* PUT selection shelf contents. */
  char snum[MAX_DIGITS+1] ;           /* Scratchpad for scientific numbers. */
  char *titleline ;                   /* Value of titleline (if present). */
  char *workspaces ;                  /* workspace names calc is in */

  int x;
  int y;
  int width;
  int height;

  int MPcon_vals[MAXREGS][MP_SIZE] ;  /* Selectable constants. */
  int MPdebug ;                       /* If set, debug info. to stderr. */
  int MPerrors ;                      /* If set, output errors to stderr. */
  int MPdisp_val[MP_SIZE] ;           /* Value of the current display. */
  int MPlast_input[MP_SIZE] ;         /* Previous number input by user. */
  int MPmvals[MAXREGS][MP_SIZE] ;     /* Memory register values. */
  double MPfvals[FINREGS] ;           /* Financial Memory register values. */
  int *MPnumstack[MAXSTACK] ;         /* Numeric stack for parens. */
  int MPresult[MP_SIZE] ;             /* Current calculator total value. */
  int MPtresults[3][MP_SIZE] ;        /* Current trigonometric results. */

  enum base_type base ;            /* Current base: BIN, OCT, DEC or HEX. */
  enum fcp_type curwin ;           /* Window current event occurred in. */
  enum fcp_type pending_win ;      /* Window that pending op came from. */
  enum mode_type modetype ;        /* Current calculator mode. */
  enum mode_type pending_mode ;    /* Mode for pending op. */
  enum num_type dtype ;            /* Number display mode. */
  enum trig_type ttype ;           /* Trig. type (deg, grad or rad). */
  BOOLEAN num_lock;    /* Indicator of the state of NUM_LOCK */
  int accuracy ;      /* Number of digits precision (Max 9). */
  int beep ;          /* Indicates whether there is a beep sound on error. */
  int column ;        /* Column number of current key/mouse press. */
  int cur_ch ;        /* Current character if keyboard event. */
  int error ;         /* Indicates some kind of display error. */
  int event_type ;    /* Type of event being currently processed. */
  int hasicon ;       /* Set if user gave icon name on command line. */
  int hyperbolic ;    /* If set, trig functions will be hyperbolic. */
  int iconic ;        /* Set if window is currently iconic. */
  int inverse ;       /* If set, trig and log functions will be inversed. */
  int ismenu ;        /* Set when do_pending called via a popup menu. */
  int key_exp ;       /* Set if entering exponent number. */
  int new_input ;     /* New number input since last op. */
  int noparens ;      /* Count of left brackets still to be matched. */
  int numsptr ;       /* Pointer into the parenthese numeric stack. */
  int opsptr ;        /* Pointer into the parentheses operand stack. */
  int opstack[MAXSTACK] ;  /* Stack containing parentheses input. */
  int pending ;            /* Set for command depending on multiple presses. */
  int pending_n ;     /* Offset into function table for pending op. */
  int pending_op ;    /* Arithmetic operation for pending command. */
  int pointed ;       /* Whether a decimal point has been given. */
  int row ;           /* Row number of current key/mouse press. */
  int rstate ;        /* Indicates if memory register frame is displayed. */
  int frstate ;       /* Indicates if financial memory register 
                         frame is displayed. */
  int show_paren ;    /* Set if we wish to show DISPLAYITEM during parens. */
  int started ;       /* Set just before window is displayed. */
  int toclear ;       /* Indicates if display should be cleared. */
  int tstate ;        /* Indicates current button set being displayed. */
  int funstate ;      /* whether the last key pressed was a fin. func. key*/
  int defState ;      /* Set when calculator has just been cleared */

};

extern struct calcVars CalcVars;

typedef struct calcVars *Vars ;
extern Vars v ;                 /* Calctool variables and options. */


/*  Structure, resource definitions, for View's optional parameters.  */
typedef struct
{
   short menuBar;
   int accuracy;
   char *base;
   char *display;
   char *mode;
   char *trigType;
   char *session;
} ApplicationArgs, *ApplicationArgsPtr;

extern ApplicationArgs application_args;

/* MP definitions. */

#define  C_abs(x)    ((x) >= 0 ? (x) : -(x))
#define  dabs(x)     (double) C_abs(x)
#define  min(a, b)   ((a) <= (b) ? (a) : (b))
#define  max(a, b)   ((a) >= (b) ? (a) : (b))
#define  dmax(a, b)  (double) max(a, b)
#define  dmin(a, b)  (double) min(a, b)

BOOLEAN ibool(double);
BOOLEAN ibool2(double);

char *convert(char *);
char *get_resource(enum res_type);
char *make_eng_sci(int *);
char *make_fixed(int *, int);
char *make_number(int *, BOOLEAN);

double mppow_di(double *, int *);
double mppow_ri(float *, int *);
double setbool(BOOLEAN);

int char_val(char);
int get_bool_resource(enum res_type, int *);
int get_index(char);
int get_int_resource(enum res_type, int *);
int get_str_resource(enum res_type, char *);
int main(int, char **);

void beep(void);
void check_ow_beep(void);
void clear_display(void);
void doerr(char *);
void do_accuracy(void);
void do_ascii(void);
void do_base(void);
void set_base(enum base_type type);
void do_business(void);
void do_calc(void);
void do_dtcalc(int, char **);
void do_clear(void);
void do_constant(void);
void do_delete(void);
void do_exchange(void);
void do_expno(void);
void do_factorial(int *, int *);
void do_frame(void);
void do_function(void);
void do_immed(void);
void do_keys(void);
void do_mode(void);
void do_none(void);
void do_number(void);
void do_numtype(void);
void do_paren(void);
void set_numtype(enum num_type dtype);
void do_nothing(void);
void do_pending(void);
void do_point(void);
void do_portion(void);
double do_round(double, int);
void do_shift(void);
void do_sto_rcl(void);
void do_trig(void);
void do_trigtype(void);
void draw_button(int, enum fcp_type, int, int, int);
void get_display(void);
void get_key_val(char *, char *);
void get_label(int);
void get_options(int, char **);
void getparam(char *, char **, char *);
void get_rcfile(char *);
void grey_button(int, int, int);
void grey_buttons(enum base_type);
void handle_menu_selection(int, int);
void handle_selection(void);
void initialize(void);
void init_cmdline_opts(void);
void init_graphics(void);
void init_options(void);
void init_text(void);
void init_vars(void);
void key_init(void);
void load_resources(void);
void make_frames(void);
void make_items(void);
void make_modewin(void);
void make_fin_registers(void);
void make_registers(int);
void MPstr_to_num(char *, enum base_type, int *);
void paren_disp(char);
void process_event(int);
void process_item(int);
void process_parens(char);
void process_stack(int, int, int);
void process_str(char *, enum menu_type);
void push_num(int *);
void push_op(int);
void put_resource(enum res_type, char *);
void read_rcfiles(void);
void read_resources(void);
void redraw_buttons(void);
void save_cmdline(int, char **);
void save_pending_values(int);
void save_resources(char *);
void blank_display(void);
void ErrorDialog(char *string);
void set_item(enum item_type, char *);
void set_title(enum fcp_type, char *);
void show_ascii_frame(void);
void show_display(int *);
void srand48(long);
void start_tool(void);
void switch_hands(int);
void usage(char *);
void win_display(enum fcp_type, int);
void write_cmdline(void);
void write_rcfile(enum menu_type, int, int, char *, char *);
void write_resources(char *);
void RestoreSession(void);
void TimerEvent(XtPointer, XtIntervalId *);
void ErrDialog(char *, Widget );

/* MP routines not found in the Brent FORTRAN package. */
void mpacos(int *, int *);
void mpacosh(int *, int *);
void mpasinh(int *, int *);
void mpatanh(int *, int *);
void mplog10(int *, int *);

/* Brent MP routines in mp.c. */
int mpcmpi(int *, int *);
int mpcmpr(int *, float *);
int mpcomp(int *, int *);
int pow_ii(int *, int *);
 
int mpeq(int *, int *);
int mpge(int *, int *);
int mpgt(int *, int *);
int mple(int *, int *);
int mplt(int *, int *);

void mpabs(int *, int *);
void mpadd(int *, int *, int *);
void mpadd2(int *, int *, int *, int *, int *);
void mpadd3(int *, int *, int *, int *, int *);
void mpaddi(int *, int *, int *);
void mpaddq(int *, int *, int *, int *);
void mpart1(int *, int *);
void mpasin(int *, int *);
void mpatan(int *, int *);
void mpcdm(double *, int *);
void mpchk(int *, int *);
void mpcim(int *, int *);
void mpcmd(int *, double *);
void mpcmf(int *, int *);
void mpcmi(int *, int *);
void mpcmim(int *, int *);
void mpcmr(int *, float *);
void mpcos(int *, int *);
void mpcosh(int *, int *);
void mpcqm(int *, int *, int *);
void mpcrm(float *, int *);
void mpdiv(int *, int *, int *);
void mpdivi(int *, int *, int *);
void mperr(void);
void mpexp(int *, int *);
void mpexp1(int *, int *);
void mpext(int *, int *, int *);
void mpgcd(int *, int *);
void mpln(int *, int *);
void mplns(int *, int *);
void mpmaxr(int *);
void mpmlp(int *, int *, int *, int *);
void mpmul(int *, int *, int *);
void mpmul2(int *, int *, int *, int *);
void mpmuli(int *, int *, int *);
void mpmulq(int *, int *, int *, int *);
void mpneg(int *, int *);
void mpnzr(int *, int *, int *, int *);
void mpovfl(int *);
void mppi(int *);
void mppwr(int *, int *, int *);
void mppwr2(int *, int *, int *);
void mprec(int *, int *);
void mproot(int *, int *, int *);
void mpset(int *, int *, int *);
void mpsin(int *, int *);
void mpsin1(int *, int *, int *);
void mpsinh(int *, int *);
void mpsqrt(int *, int *);
void mpstr(int *, int *);
void mpsub(int *, int *, int *);
void mptanh(int *, int *);
void mpunfl(int *);

/* Help routines */
void Help(char *, char *);
void HelpRequestCB(Widget, caddr_t, caddr_t);
void HelpModeCB(Widget, caddr_t, caddr_t);
void DisplayHelp(char *, char *);
void HelpHelp(void);
void SetWmHnts(void);

void _DtmapCB(Widget, XtPointer, XtPointer);

void set_option_menu(int, int);

#endif /* _calctool_h */
