#define DPROG "fbfax"
#include "direkt.h"
// fuer verschiedene Sprachen //α
enum T_      
{
	T_virtVorgbAllg,
	T_pvirtVorgbSpeziell,
	T_virtMusterVorgb,
	T_pvirtvorrueckfragen,
	T_virtrueckfragen,
	T_virtpruefweiteres,
	T_virtmacherkl_Tx_lgn,
	T_Fehler_beim_Pruefen_von,
	T_st_k,
	T_stop_l,
	T_DPROG_anhalten,
	T_anhalten,
	T_Cron_Aufruf_von,
	T_gestoppt,
	T_n_k,
	T_dszahl_l,
	T_Zahl_der_aufzulistenden_Datensaetze_ist_zahl_statt,
	T_Datenbank_nicht_initialisierbar_breche_ab,
	T_pvirtvorpruefggfmehrfach,
	T_pvirtfuehraus,
	T_virttesterg,
	T_virtzeigversion,
	T_virtzeigueberschrift, 
	T_Fuege_ein, //ω
	T_wvz_k,
	T_wartevz_l,
	T_Dateien_warten_in_pfad_anstatt,
	T_ngvz_k,
	T_nichtgefaxtvz_l,
	T_Gescheiterte_Faxe_werden_hier_gesammelt_anstatt_in,
	T_Verzeichnis_mit_wartenden_Dateien,
	T_Verzeichnis_mit_gescheiterten_Dateien,
	T_gfvz_k,
	T_gefaxtvz_l,
	T_Fertige_Faxe_werden_hier_gesammelt_anstatt_in,
	T_Verzeichnis_mit_gefaxten_Dateien,
	T_verzeichnisse,
	T_usr_k,
	T_usr_l,
	T_verwendet_fuer_die_Fritzbox_den_Benutzer_string_anstatt,
	T_Benutzer_fuer_Fritzbox,
	T_pwd_k,
	T_pwd_l,
	T_verwendet_fuer_die_Fritzbox_das_Passwort_string,
	T_Passwort_fuer_Fritzbox,
	T_host_k,
	T_host_l,
	T_Hostadresse_der_Fritzbox,
	T_Hostadresse_der_Fritzbox_,
	T_pwd,
	T_msn_k,
	T_msn_l,
	T_MSN_zum_Faxen,
	T_absnr_k,
	T_absnr_l,
	T_auf_Fax_angegebene_Absendernummer,
	T_absdr_k,
	T_absdr_l,
	T_auf_Fax_angegebener_Absender,
	T_mfolge_k,
	T_mfolge_l,
	T_kommagetrennte_Minutenfolge_der_Sendeversuche,
	T_maxsec_k,
	T_maxsec_l,
	T_Zahl_der_Sekunden_fuer_ein_fax,
	T_dt_k,
	T_datei_l,
	T_zu_faxende_Datei,
	T_an_k,
	T_an_l,
	T_nr_k,
	T_nurrein_l,
	T_stellt_Faxe_nur_rein,
	T_Zielfaxnr,
	T_zgvz_k,
	T_zgvz_l,
	T_Spoolverzeichnisse_wie,
	T_anzeigen_,
	T_Gabelung_zu_dmain_misslungen,
	T_in_pvirtfuehraus,
	T_holtif,
	T_MAX //α
}; // enum T_ //ω
//α
class hhcl:public hcl
{
	private: 
		uchar anhl{0};    // <DPROG> anhalten
		string dszahl{"30"}; // Datensatzzahl fuer Tabellenausgaben
		//ω
	protected: //α
		string p1;
		int p2;
		string p3;
		uchar oblista{0};
    uchar nurrein{0};
    uchar zgvz=0; // zeig Verzeichnisse
		long listz{30}; //ω
		string wvz; // Warteverzeichnis
		string gfvz; // gefaxt-Verzeichnis (Fertige)
		string ngvz; // Nichtgefaxt-Verzeichnis (Gescheiterte)
		string usr;
		string pwd;
		string host;
		string msn; 
		string absnr; // auf Fax angegebene Absendernummer
		string absdr; // auf Fax angegebener Absender
		string mfolge{"2,2,3,3,3,5,5,10,10,60,60,60,120,120,720,1440"}; // kommagetrennte Minutenfolge der Sendeversuche
		int maxsec{900}; // Zahl der Sekunden bis zum timeout
		string datei; // zu faxende (in Spool zu stellende) Datei
		string an; // Zielfaxnr
	public: //α //ω
	private: //α //ω
		void verzeichnisse();
		void virttesterg(); //α
		void virtlieskonfein();
		void virtautokonfschreib();
		void anhalten(); //ω
	protected: //α
		// void virtlgnzuw(); // wird aufgerufen in: virtrueckfragen, parsecl, lieskonfein, hcl::hcl nach holsystemsprache
		void virtVorgbAllg();
		void pvirtVorgbSpeziell()
#ifdef VOMHAUPTCODE
			__attribute__((weak)) // implementationsspezifische Vorgaben, Modul vgb.cpp)
#endif
			;
		void virtinitopt(); // (programm-)spezifische Optionen
		void pvirtmacherkl();
		void virtMusterVorgb();
		void pvirtvorzaehler();
		void virtzeigversion(const string& ltiffv=string());
		void pvirtvorrueckfragen();
		void virtrueckfragen();
		void neurf();
		void pvirtvorpruefggfmehrfach();
		void virtpruefweiteres();
		void virtzeigueberschrift();
		int holtif(const string& datei,ulong *seitenp=0,struct tm *tmp=0,struct stat *elogp=0,
		           string *absdrp=0,string *tsidp=0,string *calleridp=0,string *devnamep=0);
		void pvirtfuehraus();
		void virtschlussanzeige();
		void zeigdienste(); //ω
	public: //α
		hhcl(const int argc, const char *const *const argv);
		~hhcl();
		friend class fsfcl;
}; // class hhcl //ω
