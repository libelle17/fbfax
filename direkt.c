#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libsoup/soup.h>
#include <iostream>
#include <capiutils.h>
#include <sys/stat.h>

#include "fax.h"
#include "phone.h"
#include "faxophone.h"
#include "fax_phone.h"
#include "audio.h"
#include "appobject.h"
#include "appobject-emit.h"
#include "logging.h"
#include "net_monitor.h"
#include "routermanager.h"
// #include "router.h"
// #include "firmware-04-00.h"
// #include "firmware-common.h"
#include <string>
#include <vector>
using namespace std;
#include "tr64.h"
#include "direkt.h"
#undef g_debug
#define g_debug(format...)    g_log_structured (G_LOG_DOMAIN, G_LOG_LEVEL_DEBUG,     \
                                                "CODE_FILE", __FILE__,               \
                                                "CODE_LINE", G_STRINGIFY (__LINE__), \
                                                "CODE_FUNC", G_STRFUNC,               \
                                                "MESSAGE", format)

//int verbg{1};
GMainContext *ctx;


fbcl::fbcl(const string usr,const string pwd,const string host)
	:usr(usr),pwd(pwd),host(host)
{
//  host="fritz.box";//"192.168.178.1";
	controller=4;
}

void fbcl::waehle(string nr)
{
	// controlURL: /upnp/control/x_voip
	// serviceType: urn:dslforum-org:service:X_VoIP:1
	// action:      X_AVM-DE_DialNumber
	tr64cl tr64(usr,pwd);
	string ubuf;
	vector<string> iname; iname.push_back("NewX_AVM-DE_PhoneNumber");
	vector<string> ival; ival.push_back(nr);
	tr64.fragurl("/upnp/control/x_voip","urn:dslforum-org:service:X_VoIP:1","X_AVM-DE_DialNumber",&ubuf,&iname,&ival);
//	if (verbg) printf("Ergebnis nach Wahl: %s\n",ubuf.c_str());
}

/**
 * \brief Faxophone connect
 * \param user_data faxophone plugin pointer
 * \return error code
 */
gboolean fbcl::faxophone_connect_hier()
{
//	struct profile *profile = profile_get_active();
	gboolean retry = TRUE;
	const gchar* _host=(const gchar*)"fritz.box"; // router_get_host(profile);
	if (!session) {
//		if (verbg) printf("Beginn faxophone_connect_hier, host: %s, phone-controller: %i\n",_host,controller);
again:
		session = faxophone_init(&session_handlers, _host, controller + 1);
//		if (verbg) printf("Mitte faxophone_connect_hier, host: %s, phone-controller: %i\n",_host,controller);
		if (!session && retry) {
			// Maybe the port is closed, try to activate it and try again 
			waehle(/*PORT_ISDN1, */"#96*3*");
			g_usleep(G_USEC_PER_SEC * 2);
			retry = FALSE;
			goto again;
		}
//		if (verbg) printf("Ende faxophone_connect_hier, host: %s, phone-controller: %i\n",_host,controller);
	}
	return session != NULL;
}

fbcl::~fbcl()
{
	if (session) {
		faxophone_close(TRUE);
		session=0;
	}
}

// aus main_cli.c
#include "config.h"
#undef _
#define _(x) x
static gboolean debug = FALSE;
/*
static gboolean journal = FALSE;
static gboolean sendfax = FALSE;
static gboolean call = FALSE;
static gchar *file_name = NULL;
static gchar *number = NULL;
static GOptionEntry entries[] = {
	{"debug", 'd', 0, G_OPTION_ARG_NONE, &debug, "Enable debug messages", NULL},
	{"journal", 'j', 0, G_OPTION_ARG_NONE, &journal, "Prints journal", NULL},
	{"sendfax", 's', 0, G_OPTION_ARG_NONE, &sendfax, "Send fax", NULL},
	{"file", 'f', 0, G_OPTION_ARG_STRING, &file_name, "PDF/PS file", NULL},
	{"number", 'n', 0, G_OPTION_ARG_STRING, &number, "Remote phone number", NULL},
	{"call", 'c', 0, G_OPTION_ARG_NONE, &call, "Call number", NULL},
	{NULL}
};
*/
/** Internal main loop */
GMainLoop *main_loop = NULL;
static gboolean success = FALSE;

/**
 * \brief FAX connection status - show status message
 * \param object appobject
 * \param status fax connection status
 * \param connection capi connection pointer
 * \param user_data user data pointer (NULL)
 */
void fax_connection_status_cb(AppObject *object, gint status, struct capi_connection *connection, gpointer user_data)
{
	struct fax_status *fax_status;
	gchar buffer[256];
//	if (verbg) printf("Begin fax_connection_status_cb\n");

	fax_status = (struct fax_status*)connection->priv;
	if (!fax_status) {
		g_warning("No status available");
		return;
	}

	if (!status && !fax_status->done) {
		switch (fax_status->phase) {
		case PHASE_B:
			g_debug("Ident: %s", fax_status->remote_ident);
			snprintf(buffer, sizeof(buffer), "%d/%d", fax_status->page_current, fax_status->page_total);

			g_message(_("Transfer starting:"));
			g_message("%s", buffer);
			break;
		case PHASE_D:
			snprintf(buffer, sizeof(buffer), "%d", fax_status->page_current);
			g_message(_("Transferring page"));
			g_message("%s", buffer);
			break;
		case PHASE_E:
			if (!fax_status->error_code) {
				g_message("%s", "Fax transfer successful");
				success = TRUE;
			} else {
				g_message("%s", "Fax transfer failed");
				success = FALSE;
			}
			phone_hangup(connection);
			fax_status->done = TRUE;
			g_main_loop_quit(main_loop);
			break;
		default:
			g_debug("Unhandled phase (%d)", fax_status->phase);
			break;
		}
	} else if (status == 1) {
		float percentage = 0.0f;
		gchar text[6];
		int percent = 0;
		static int old_percent = 0;

		percentage = (float) fax_status->bytes_sent / (float) fax_status->bytes_total;

		if (percentage > 1.0f) {
			percentage = 1.0f;
		}

		percent = percentage * 100;
		if (old_percent == percent) {
			return;
		}
		old_percent = percent;

		snprintf(text, sizeof(text), "%d%%", percent);
		g_message("Transfer at %s", text);
	}
}

/**
 * \brief CAPI connection established callback - just print message
 * \param object appobject
 * \param connection capi connection pointer
 * \param user_data user data pointer (NULL)
 */
static void capi_connection_established_cb(AppObject *object, struct capi_connection *connection, gpointer user_data)
{
	g_message(_("Connected"));
}

/**
 * \brief CAPI connection terminated callback - just print message
 * \param object appobject
 * \param connection capi connection pointer
 * \param user_data user data pointer (NULL)
 */
static void capi_connection_terminated_cb(AppObject *object, struct capi_connection *connection, gpointer user_data)
{
	g_message(_("Disconnected"));
}

int dmain(int argc, const gchar** argv,const string usr,const string pwd,const string host)
{
	// mit G_MESSAGES_DEBUG=all werden die Debug-Infos angezeigt
	// die Telefonnummer soll mit 0 statt +49 anfangen
//	GOptionContext *context;
	// gchar *tiff = NULL;
	// int ret = 0;
#if !GLIB_CHECK_VERSION(2, 36, 0)
	/* Init g_type */
	g_type_init();
#endif
//	context = g_option_context_new("-");
//	g_option_context_add_main_entries(context, entries, GETTEXT_PACKAGE);
	/*
	GError *error{0};
	if (!g_option_context_parse(context, &argc, (gchar***)&argv, &error)) {
		g_print("option parsing failed: %s\n", error->message);
		exit(1);
	}
	*/
//		routermanager_new(debug, NULL);
	rmcl rm(debug,0);
	/* Initialize routermanager */
	//		routermanager_init(NULL);
	rm.init(0);
	/*static*/ aocl ao; //app_object
//	__attribute__((unused)) aocl *ao=new aocl; //app_object
	//faxophone_setup();
	// static gconstpointer net_event;
	//	net_event = net_add_event(faxophone_connect_hier, faxophone_disconnect, NULL);

	/* Only show messages >= INFO */
	log_set_level(G_LOG_LEVEL_INFO);

//  fb.loadj();
//  fb.fb_get_settings_05_50();
	g_signal_connect(app_object, "connection-status", G_CALLBACK(fax_connection_status_cb), NULL);
	g_signal_connect(app_object, "connection-established", G_CALLBACK(capi_connection_established_cb), NULL);
	g_signal_connect(app_object, "connection-terminated", G_CALLBACK(capi_connection_terminated_cb), NULL);

//	system("gs -q -dNOPAUSE -dSAFER -dBATCH -sDEVICE=tiffg4 -sPAPERSIZE=a4 -dFIXEDMEDIA -r204x98 -sOutputFile=t0.pdf.tif ~/rogerj/wand/t0.pdf");
	// gpointer user_data;
	fbcl fb(usr,pwd,host);
//	if(argc>1) fb.controller=atoi(argv[1]); /* 4 */
  const char *datei;
  string ndat;
  if (argc==6) {
    datei=argv[1];
    struct stat dstat{0};
    if (lstat(datei,&dstat)) {
      printf("Datei %s nicht gefunden.\n",datei);
      return(3);
    }
    size_t dlen{strlen(datei)};
    const char* tif{".tif"};
    ndat=datei;
    if (strcasecmp(datei+dlen-4,tif)) {
      string bef{"gs -q -dNOPAUSE -dSAFER -dBATCH -sDEVICE=tiffg4 -sPAPERSIZE=a4 -dFIXEDMEDIA -r204x196 -sOutputFile="};
      ndat+=tif;
      bef+="\""+ndat+"\" \""+datei+"\"";
      printf("bef: %s\n",bef.c_str());
      if (system(bef.c_str())) {
        printf("Umwandlung %s fehlgeschlagen.\n",bef.c_str());
        return(5);
      }
      if (lstat(ndat.c_str(),&dstat)) {
        printf("Datei %s nicht gefunden.\n",ndat.c_str());
        return(3);
      }
    }
  } else {
    printf("Parameterzahl %i statt 5; Benutzung: %s <datei> <msn> <zielnr> <absnr> <autor>\n", argc-1,argv[0]);
    return(2);
  }

	if (fb.faxophone_connect_hier()) {
    const char *msn{argv[2]};
    const char *ziel{argv[3]};
    const char *abs{argv[4]};
    const char *autor{argv[5]};
		// aus fax_dial
//		struct capi_connection * conn=fax_send((gchar*)"t0.pdf.tif",/*modem,3=14400*/3,/*ecm*/1,/*controller*/5,/*cip,4=speech,0x11=fax,geht beides*/4,
//				(gchar*)"616381",(gchar*)"6150166",/*lsi*/(gchar*)"+49616381",/*local_header_info*/(gchar*)"G.Schade",/*return error code*/0);
    printf("Sende: Datei: %s, Msn: %s, Ziel: %s, Absender: %s, Autor: %s\n",ndat.c_str(),msn,ziel,abs,autor);
		__attribute__ ((unused)) struct capi_connection * conn=fax_send((gchar*)ndat.c_str(),/*modem,3=14400*/3,/*ecm*/1,/*controller*/5,/*cip,4=speech,0x11=fax,geht beides*/4,
				(gchar*)msn,(gchar*)ziel,/*lsi*/(gchar*)abs,/*local_header_info*/(gchar*)autor,/*return error code*/0);
		/* Create and start g_main_loop */
    
//		if (verbg) printf("Vor main_loop\n");
		// fax_transfer
    if (1) {
		ctx=g_main_context_new();
		main_loop = g_main_loop_new(ctx, FALSE);
		g_main_loop_run(main_loop);
    g_main_context_unref(ctx);
		g_main_loop_unref(main_loop);
    }
//		if (verbg) printf("Nach main_loop\n");
	}

	/* Shutdown routermanager */
	//routermanager_shutdown();
	/* Destroy app_object */
//	g_clear_object(&app_object);

	/* Shutdown logging */
	log_shutdown();
	return 0;
}
