/****************** Header file for NUTS version 3.3.3 ******************/

#define DATAFILES "datafiles"
#define USERFILES "userfiles"
#define HELPFILES "helpfiles"
#define MAILSPOOL "mailspool"
#define CONFIGFILE "config"
#define NEWSFILE "newsfile"
#define MAPFILE "mapfile"
#define SITEBAN "siteban"
#define USERBAN "userban"
#define SYSLOG "syslog"
#define MOTD1 "motd1"
#define MOTD2 "motd2"

#define OUT_BUFF_SIZE 1000
#define MAX_WORDS 10
#define WORD_LEN 40
#define ARR_SIZE 1000
#define MAX_LINES 15
#define NUM_COLS 21

#define USER_NAME_LEN 12
#define USER_DESC_LEN 30
#define AFK_MESG_LEN 60
#define PHRASE_LEN 40
#define PASS_LEN 20 /* only the 1st 8 chars will be used by crypt() though */
#define BUFSIZE 1000
#define ROOM_NAME_LEN 20
#define ROOM_LABEL_LEN 5
#define ROOM_DESC_LEN 810 /* 10 lines of 80 chars each + 10 nl */
#define TOPIC_LEN 60
#define MAX_LINKS 10
#define SERV_NAME_LEN 80
#define SITE_NAME_LEN 80
#define VERIFY_LEN 20
#define REVIEW_LINES 15
#define REVTELL_LINES 5
#define REVIEW_LEN 200
/* DNL (Date Number Length) will have to become 12 on Sun Sep 9 02:46:40 2001 
   when all the unix timers will flip to 1000000000 :) */
#define DNL 11 

#define PUBLIC 0
#define PRIVATE 1
#define FIXED 2
#define FIXED_PUBLIC 2
#define FIXED_PRIVATE 3

#define NEW 0
#define USER 1
#define WIZ 2
#define ARCH 3
#define GOD 4

#define USER_TYPE 0
#define CLONE_TYPE 1
#define REMOTE_TYPE 2
#define CLONE_HEAR_NOTHING 0
#define CLONE_HEAR_SWEARS 1
#define CLONE_HEAR_ALL 2

/* The elements vis, ignall, prompt, command_mode etc could all be bits in 
   one flag variable as they're only ever 0 or 1, but I tried it and it
   made the code unreadable. Better to waste a few bytes */
struct user_struct {
	char name[USER_NAME_LEN+1];
	char desc[USER_DESC_LEN+1];
	char pass[PASS_LEN+6];
	char in_phrase[PHRASE_LEN+1],out_phrase[PHRASE_LEN+1];
	char buff[BUFSIZE],site[81],last_site[81],page_file[81];
	char mail_to[WORD_LEN+1],revbuff[REVTELL_LINES][REVIEW_LEN+2];
	char afk_mesg[AFK_MESG_LEN+1],inpstr_old[REVIEW_LEN+1];
	struct room_struct *room,*invite_room;
	int type,port,site_port,login,socket,attempts,buffpos,filepos;
	int vis,ignall,prompt,command_mode,muzzled,charmode_echo; 
	int level,misc_op,remote_com,edit_line,charcnt,warned;
	int accreq,last_login_len,ignall_store,clone_hear,afk;
	int edit_op,colour,ignshout,igntell,revline;
	time_t last_input,last_login,total_login,read_mail;
	char *malloc_start,*malloc_end;
	struct netlink_struct *netlink,*pot_netlink;
	struct user_struct *prev,*next,*owner;
	};

typedef struct user_struct* UR_OBJECT;
UR_OBJECT user_first,user_last;

struct room_struct {
	char name[ROOM_NAME_LEN+1];
	char label[ROOM_LABEL_LEN+1];
	char desc[ROOM_DESC_LEN+1];
	char topic[TOPIC_LEN+1];
	char revbuff[REVIEW_LINES][REVIEW_LEN+2];
	int inlink; /* 1 if room accepts incoming net links */
	int access; /* public , private etc */
	int revline; /* line number for review */
	int mesg_cnt;
	char netlink_name[SERV_NAME_LEN+1]; /* temp store for config parse */
	char link_label[MAX_LINKS][ROOM_LABEL_LEN+1]; /* temp store for parse */
	struct netlink_struct *netlink; /* for net links, 1 per room */
	struct room_struct *link[MAX_LINKS];
	struct room_struct *next;
	};

typedef struct room_struct *RM_OBJECT;
RM_OBJECT room_first,room_last;
RM_OBJECT create_room();

/* Netlink stuff */
#define UNCONNECTED 0 
#define INCOMING 1 
#define OUTGOING 2
#define DOWN 0
#define VERIFYING 1
#define UP 2
#define ALL 0
#define IN 1
#define OUT 2

/* Structure for net links, ie server initiates them */
struct netlink_struct {
	char service[SERV_NAME_LEN+1];
	char site[SITE_NAME_LEN+1];
	char verification[VERIFY_LEN+1];
	char buffer[ARR_SIZE*2];
	char mail_to[WORD_LEN+1];
	char mail_from[WORD_LEN+1];
	FILE *mailfile;
	time_t last_recvd; 
	int port,socket,type,connected;
	int stage,lastcom,allow,warned,keepalive_cnt;
	int ver_major,ver_minor,ver_patch;
	struct user_struct *mesg_user;
	struct room_struct *connect_room;
	struct netlink_struct *prev,*next;
	};

typedef struct netlink_struct *NL_OBJECT;
NL_OBJECT nl_first,nl_last;
NL_OBJECT create_netlink();

char *syserror="Sorry, a system error has occured";
char *nosuchroom="There is no such room.\n";
char *nosuchuser="There is no such user.\n";
char *notloggedon="There is no one of that name logged on.\n";
char *invisenter="A presence enters the room...\n";
char *invisleave="A presence leaves the room.\n";
char *invisname="A presence";
char *noswearing="Swearing is not allowed here.\n";

char *level_name[]={
"NEW","USER","WIZ","ARCH","GOD","*"
};

char *command[]={
"quit",    "look",     "mode",      "say",    "shout",
"tell",    "emote",    "semote",    "pemote", "echo",
"go",      "ignall",   "prompt",    "desc",   "inphr",
"outphr",  "public",   "private",   "letmein","invite",
"topic",   "move",     "bcast",     "who",    "people",
"help",    "shutdown", "news",      "read",   "write",
"wipe",    "search",   "review",    "home",   "status",
"version", "rmail",    "smail",     "dmail",  "from",
"entpro",  "examine",  "rmst",      "rmsn",   "netstat",
"netdata", "connect",  "disconnect","passwd", "kill",
"promote", "demote",   "listbans",  "ban",    "unban",
"vis",     "invis",    "site",      "wake",   "wizshout",
"muzzle",  "unmuzzle", "map",       "logging","minlogin",
"system",  "charecho", "clearline", "fix",    "unfix",
"viewlog", "accreq",   "revclr",    "clone",  "destroy",
"myclones","allclones","switch",    "csay",   "chear",
"rstat",   "swban",    "afk",       "cls",    "colour",
"ignshout","igntell",  "suicide",   "delete", "reboot",
"recount", "revtell",  "*"
};


/* Values of commands , used in switch in exec_com() */
enum comvals {
QUIT,     LOOK,     MODE,     SAY,    SHOUT,
TELL,     EMOTE,    SEMOTE,   PEMOTE, ECHO,
GO,       IGNALL,   PROMPT,   DESC,   INPHRASE,
OUTPHRASE,PUBCOM,   PRIVCOM,  LETMEIN,INVITE,
TOPIC,    MOVE,     BCAST,    WHO,    PEOPLE,
HELP,     SHUTDOWN, NEWS,     READ,   WRITE,
WIPE,     SEARCH,   REVIEW,   HOME,   STATUS,
VER,      RMAIL,    SMAIL,    DMAIL,  FROM,
ENTPRO,   EXAMINE,  RMST,     RMSN,   NETSTAT,
NETDATA,  CONN,     DISCONN,  PASSWD, KILL,
PROMOTE,  DEMOTE,   LISTBANS, BAN,    UNBAN,
VIS,      INVIS,    SITE,     WAKE,   WIZSHOUT,
MUZZLE,   UNMUZZLE, MAP,      LOGGING,MINLOGIN,
SYSTEM,   CHARECHO, CLEARLINE,FIX,    UNFIX,
VIEWLOG,  ACCREQ,   REVCLR,   CREATE, DESTROY,
MYCLONES, ALLCLONES,SWITCH,   CSAY,   CHEAR,
RSTAT,    SWBAN,    AFK,      CLS,    COLOUR,
IGNSHOUT, IGNTELL,  SUICIDE,  DELETE, REBOOT,
RECOUNT,  REVTELL
} com_num;


/* These are the minimum levels at which the commands can be executed. 
   Alter to suit. */
int com_level[]={
NEW, NEW, NEW, NEW, USER,
USER,USER,USER,USER,USER,
USER,USER,NEW, USER,USER,
USER,USER,USER,USER,USER,
USER,WIZ, WIZ ,NEW, WIZ,
NEW, GOD, USER,NEW, USER,
WIZ, USER,USER,USER, NEW,
NEW, NEW, USER,USER,USER,
USER,USER,NEW, NEW, WIZ,
ARCH,GOD, GOD, USER,ARCH,
WIZ ,WIZ ,WIZ, ARCH,ARCH,
ARCH,ARCH,WIZ, USER,WIZ,
WIZ, WIZ, USER,GOD, GOD,
WIZ, NEW, ARCH,GOD, GOD,
WIZ ,NEW, USER,ARCH,ARCH,
ARCH,USER,ARCH,ARCH,ARCH,
WIZ, ARCH,USER,NEW ,NEW,
USER,USER,NEW, GOD, GOD,
GOD, USER
};

/* 
Colcode values equal the following:
RESET,BOLD,BLINK,REVERSE

Foreground & background colours in order..
BLACK,RED,GREEN,YELLOW/ORANGE,
BLUE,MAGENTA,TURQUIOSE,WHITE
*/

char *colcode[NUM_COLS]={
/* Standard stuff */
"\033[0m", "\033[1m", "\033[4m", "\033[5m", "\033[7m",
/* Foreground colour */
"\033[30m","\033[31m","\033[32m","\033[33m",
"\033[34m","\033[35m","\033[36m","\033[37m",
/* Background colour */
"\033[40m","\033[41m","\033[42m","\033[43m",
"\033[44m","\033[45m","\033[46m","\033[47m"
};

/* Codes used in a string to produce the colours when prepended with a '~' */
char *colcom[NUM_COLS]={
"RS","OL","UL","LI","RV",
"FK","FR","FG","FY",
"FB","FM","FT","FW",
"BK","BR","BG","BY",
"BB","BM","BT","BW"
};


char *month[12]={
"January","February","March","April","May","June",
"July","August","September","October","November","December"
};

char *day[7]={
"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"
};

char *noyes1[]={ " NO","YES" };
char *noyes2[]={ "NO ","YES" };
char *offon[]={ "OFF","ON " };

/* These MUST be in lower case - the contains_swearing() function converts
   the string to be checked to lower case before it compares it against
   these. Also even if you dont want to ban any words you must keep the 
   star as the first element in the array. */
char *swear_words[]={
"fuck","shit","cunt","*"
};

char verification[SERV_NAME_LEN+1];
char text[ARR_SIZE*2];
char word[MAX_WORDS][WORD_LEN+1];
char wrd[8][81];
char progname[40],confile[40];
time_t boot_time;
jmp_buf jmpvar;

int port[3],listen_sock[3],wizport_level,minlogin_level;
int colour_def,password_echo,ignore_sigterm;
int max_users,max_clones,num_of_users,num_of_logins,heartbeat;
int login_idle_time,user_idle_time,config_line,word_count;
int tyear,tmonth,tday,tmday,twday,thour,tmin,tsec;
int mesg_life,system_logging,prompt_def,no_prompt;
int force_listen,gatecrash_level,min_private_users;
int ignore_mp_level,rem_user_maxlevel,rem_user_deflevel;
int destructed,mesg_check_hour,mesg_check_min,net_idle_time;
int keepalive_interval,auto_connect,ban_swearing,crash_action;
int time_out_afks,allow_caps_in_name,rs_countdown;
int charecho_def,time_out_maxlevel;
time_t rs_announce,rs_which;
UR_OBJECT rs_user;

extern char *sys_errlist[];
char *long_date();
