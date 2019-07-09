#include <string>
#include <vector>
#define EMPTY_STRING(x) (!(x) || !strlen(x))
extern const std::string nix;
std::string xmlex(std::string data,std::string lim,std::string lim2=nix,size_t *p2p=0);
// Active router structure 
//extern struct router *active_router/*=NULL*/;
/** Global router plugin list */
//extern GSList *router_list/*=NULL*/;
/** Router login blocked shield */
//extern gboolean router_login_blocked/*=FALSE*/;
#include <glib.h>
//extern int verbg;
#include <fstream>
// int dmain(int argc, const gchar** argv,fstream vwdt,const string usr,const string pwd,const string host);
int dmain(int argc, string *argv,fstream *vwdtph, const string usr,const string pwd,const string host,int oblog);

class fbcl
{
  private:
    const std::string usr;
    const std::string pwd;
    const std::string host;
	public:
		int controller;
/*static */struct session *session = NULL;
	public:
    fbcl(const string usr,const string pwd,const string host);
		~fbcl();
		// gboolean faxophone_connect(gpointer user_data);
		void waehle(string nr);
		gboolean faxophone_connect_hier();
};
