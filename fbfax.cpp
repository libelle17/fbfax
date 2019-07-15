// '//α' oder '//ω' als Kommentar sind nur fuer die Verwendung dieses Programms als Programmvorlage wichtig
const double& versnr= //α
#include "versdt"
;
#include "kons.h"
// #include "DB.h" 
#include <tiffio.h>
#define VOMHAUPTCODE // um Funktionsdefinition manchmal mit "__attribute__((weak)) " versehen zu können //ω
#include "fbfax.h"
// fuer verschiedene Sprachen //α
char const *DPROG_T[T_MAX+1][SprachZahl]=
{
	// T_virtVorgbAllg
	{"virtVorgbAllg()","virtgeneralprefs()"},
	// T_pvirtVorgbSpeziell
	{"pvirtVorgbSpeziell()","pvirtspecialprefs()"},
	// T_virtMusterVorgb
	{"virtMusterVorgb()","virtsampleprefs"},
	// T_pvirtvorrueckfragen
	{"pvirtvorrueckfragen()","pvirtbeforecallbacks()"},
	// T_virtrueckfragen
	{"virtrueckfragen()","virtcallbacks()"},
	// T_virtpruefweiteres
	{"virtpruefweiteres()","virtcheckmore()"},
	// T_virtmacherkl_Tx_lgn
	{"pvirtmacherkl, Tx.lgn: ","pvirtmakeexpl, Tx.lgn: "},
	//	T_Fehler_beim_Pruefen_von
	{"Fehler beim Pruefen von: ","Error while examining: "},
	// T_st_k
	{"st","st"},
	// T_stop_l
	{"stop","stop"},
	// T_DPROG_anhalten
	{DPROG " anhalten","stop " DPROG},
	// T_anhalten
	{"anhalten()","stop()"},
	// T_Cron_Aufruf_von
	{"Cron-Aufruf von '","cron call of '"},
	// T_gestoppt
	{"' gestoppt.","' stopped."},
	// T_n_k
	{"n","n"},
	// T_dszahl_l
	{"dszahl","reccount"},
	// T_Zahl_der_aufzulistenden_Datensaetze_ist_zahl_statt
	{"Zahl der aufzulistenden Datensaetze = <zahl> statt","No. of listed entries = <no> instead of"},
	// T_Datenbank_nicht_initialisierbar_breche_ab
	{"Datenbank nicht initialisierbar, breche ab","database init failed, stopping"},
	// T_pvirtvorpruefggfmehrfach,
	{"pvirtvorpruefggfmehrfach()","pvirtbeforecheckmultiple()"},
	// T_pvirtfuehraus,
	{"pvirtfuehraus()","pvirtexecute()"},
	// T_virttesterg,
	{"virttesterg()","virtcheckresult()"},
	// T_virtzeigversion,
	{"virtzeigversion()","virtshowversion()"},
	// T_virtzeigueberschrift, 
	{"virtzeigueberschrift()","virtshowheadline()"},
	// T_Fuege_ein
	{"Fuege ein: ","Inserting: "}, //ω
	// T_wvz_k
	{"wvz","wdr"},
	// T_wartevz_l
	{"wartevz","waitdir"},
	// T_Dateien_warten_in_pfad_anstatt
	{"Dateien warten in <pfad> anstatt","files are waiting in <path> instead of"},
	// T_ngvz_k
	{"ngvz","ndr"},
	// T_nichtgefaxtvz_l
	{"nichtgefaxtvz","notfaxeddir"},
	// T_Gescheiterte_Faxe_werden_hier_gesammelt_anstatt_in
	{"Gescheiterte Faxe werden hier gesammelt anstatt in","Failed faxes are collected here instead of"}, 
	// T_Verzeichnis_mit_wartenden_Dateien
	{"Verzeichnis mit wartenden Dateien","Directory with waiting files"},
	// T_Verzeichnis_mit_gescheiterten_Dateien
	{"Verzeichnis mit gescheiterten Dateien","Directory with failed files"},
	// T_gfvz_k,
	{"gvz","fdr"},
	// T_gefaxtvz_l,
	{"gefaxtvz","faxeddir"},
	// T_Fertige_Faxe_werden_hier_gesammelt_anstatt_in,
	{"Fertige Faxe werden hier gesammelt anstatt in","Processed faxes are collected here instead of"},
	// T_Verzeichnis_mit_gefaxten_Dateien,
	{"Verzeichnis mit fertigen Dateien","Directory with processed files"},
	// T_verzeichnisse
	{"verzeichnisse()","directories()"},
	// T_usr_k,
	{"usr","usr"},
	// T_usr_l,
	{"usr","usr"},
	// T_verwendet_fuer_die_Fritzbox_den_Benutzer_string_anstatt,
	{"verwendet fuer die Fritzbox den Benutzer <string> anstatt","takes the user <string> for the fritzbox instead of"},
	// T_Benutzer_fuer_Fritzbox,
	{"Benutzer fuer die Fritzbox: ","user for the fritz box: "},
	// T_pwd_k,
	{"pwd","pwd"},
	// T_pwd_l,
	{"pwd","pwd"},
	// T_verwendet_fuer_die_Fritzbox_das_Passwort_string,
	{"verwendet fuer die Fritzbox das Passwort","uses the password <string> for the fritz box"}, 
	// T_Passwort_fuer_Fritzbox,
	{"Passwort für Fritzbox:","password for the fritzbox:"},
	// T_host_k,
	{"host","host"},
	// T_host_l,
	{"host","host"},
	// T_Hostadresse_der_Fritzbox,
	{"Hostadresse der Fritzbox","host address for the fritz box"},
	// T_Hostadresse_der_Fritzbox_
	{"Hostadresse der Fritzbox:","host address for the fritz box:"},
	// T_pwd,
	{"Passwort","Password"},
	// T_msn_k,
	{"msn","msn"},
	// T_msn_l,
	{"msn","msn"},
	// T_MSN_zum_Faxen,
	{"MSN zum Faxen","MSN for faxing"},
	// T_absnr_k,
	{"absnr","sdrno"},
	// T_absnr_l,
	{"absendernr","senderno"},
	// T_auf_Fax_angegebene_Absendernummer,
	{"auf Fax angegebene Absendernummer","sender no on fax"},
	// T_absdr_k,
	{"abs","sdr"},
	// T_absdr_l,
	{"absender","sender"},
	// T_auf_Fax_angegebener_Absender,
	{"auf Fax angegebener Absendername","sender name on fax"},
	// T_mfolge_k,
	{"mfg","msq"},
	// T_mfolge_l,
	{"minfolge","minsequence"},
	// T_kommagetrennte_Minutenfolge_der_Sendeversuche,
	{"kommagetrennte Minutenfolge der Sendeversuche","comma-separated sequence of minutes of the send tries"},
	// T_dt_k,
	{"dt","fl"},
	// T_datei_l,
	{"datei","file"},
	// T_zu_faxende_Datei,
	{"zu faxende Datei","file to be faxed"},
	// T_an_k,
	{"an","to"},
	// T_an_l,
	{"an","to"},
	// T_nr_k
	{"nr","oi"},
	// T_nurrein_l
	{"nurrein","onlyin"},
	// T_stellt_Faxe_nur_rein
	{"stellt Faxe nur rein","inserts faxes only"},
	// T_Zielfaxnr,
	{"Zielfaxnr","target fax number"},
	{"",""} //α
}; // char const *DPROG_T[T_MAX+1][SprachZahl]=

class TxB Tx((const char* const* const* const*)DPROG_T);
const char sep = 9; // geht auch: "[[:blank:]]"
const char *logdt="/var/log/" DPROG "vorgabe.log";//darauf wird in kons.h verwiesen;
pidvec pidw;
const unsigned ktage=1; // kurzes Intervall fuer Faxtabellenkorrektur, 1 Tag
const unsigned mtage=30; // mittleres Intervall fuer Faxtabellenkorrektur, 1 Monat
const unsigned ltage=73000; // langes Intervall fuer Faxtabellenkorrektur, 200 Jahre

using namespace std; //ω
hhcl::hhcl(const int argc, const char *const *const argv):hcl(argc,argv,DPROG,/*mitcron*/1,/*parstreng*/0) //α
{
	hLog(violetts+"hhcl::hhcl()"+schwarz);
 // mitcron=0; //ω
} // hhcl::hhcl //α
// Hier neue Funktionen speichern: //ω
//α
// wird aufgerufen in lauf
void hhcl::virtVorgbAllg()
{
	hLog(violetts+Tx[T_virtVorgbAllg]+schwarz); //ω
	const string fbfxvz{"/var/spool/fbfax"};
	wvz=fbfxvz+"/waiting";
	gfvz=fbfxvz+"/faxed";
	ngvz=fbfxvz+"/notfaxed";
	host="fritz.box"; // "169.254.1.2","192.168.178.1"
	hcl::virtVorgbAllg(); //α
} // void hhcl::virtVorgbAllg

// wird aufgerufen in lauf
void hhcl::pvirtVorgbSpeziell()
{
	hLog(violetts+Tx[T_pvirtVorgbSpeziell]+schwarz);
	virtMusterVorgb(); //ω
//	dhcl::pvirtVorgbSpeziell(); //α
} // void hhcl::pvirtVorgbSpeziell

// wird aufgerufen in lauf
void hhcl::virtinitopt()
{
	hLog(violetts+"virtinitopt()"+schwarz); //ω
	opn<<new optcl(/*pptr*/&anhl,/*art*/puchar,T_st_k,T_stop_l,/*TxBp*/&Tx,/*Txi*/T_DPROG_anhalten,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/1); //α //ω
	opn<<new optcl(/*pptr*/&dszahl,/*art*/pdez,T_n_k,T_dszahl_l,/*TxBp*/&Tx,/*Txi*/T_Zahl_der_aufzulistenden_Datensaetze_ist_zahl_statt,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/1); //α //ω
	opn<<new optcl(/*pname*/"wartevz",/*pptr*/&wvz,/*art*/pverz,T_wvz_k,T_wartevz_l,/*TxBp*/&Tx,/*Txi*/T_Dateien_warten_in_pfad_anstatt,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!wvz.empty(),T_Verzeichnis_mit_wartenden_Dateien);
	opn<<new optcl(/*pname*/"gefaxtvz",/*pptr*/&gfvz,/*art*/pverz,T_gfvz_k,T_gefaxtvz_l,/*TxBp*/&Tx,/*Txi*/T_Fertige_Faxe_werden_hier_gesammelt_anstatt_in,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!wvz.empty(),T_Verzeichnis_mit_gefaxten_Dateien);
	opn<<new optcl(/*pname*/"nichtgefaxtvz",/*pptr*/&ngvz,/*art*/pverz,T_ngvz_k,T_nichtgefaxtvz_l,/*TxBp*/&Tx,/*Txi*/T_Gescheiterte_Faxe_werden_hier_gesammelt_anstatt_in,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!ngvz.empty(),T_Verzeichnis_mit_gescheiterten_Dateien);
	opn<<new optcl(/*pname*/"usr",/*pptr*/&usr,/*part*/pstri,T_usr_k,T_usr_l,/*TxBp*/&Tx,/*Txi*/T_verwendet_fuer_die_Fritzbox_den_Benutzer_string_anstatt,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!usr.empty(),T_Benutzer_fuer_Fritzbox);
	opn<<new optcl(/*pname*/"pwd",/*pptr*/&pwd,/*part*/ppwd,T_pwd_k,T_pwd_l,/*TxBp*/&Tx,/*Txi*/T_verwendet_fuer_die_Fritzbox_das_Passwort_string,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!pwd.empty(),T_Passwort_fuer_Fritzbox);
	opn<<new optcl(/*pname*/"host",/*pptr*/&host,/*part*/pstri,T_host_k,T_host_l,/*TxBp*/&Tx,/*Txi*/T_Hostadresse_der_Fritzbox,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!host.empty(),T_Hostadresse_der_Fritzbox_);
	opn<<new optcl(/*pname*/"msn",/*pptr*/&msn,/*art*/pstri,T_msn_k,T_msn_l,/*TxBp*/&Tx,/*Txi*/T_MSN_zum_Faxen,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!msn.empty(),T_MSN_zum_Faxen);
	opn<<new optcl(/*pname*/"absnr",/*pptr*/&absnr,/*art*/pstri,T_absnr_k,T_absnr_l,/*TxBp*/&Tx,/*Txi*/T_auf_Fax_angegebene_Absendernummer,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!msn.empty(),T_auf_Fax_angegebene_Absendernummer);
	opn<<new optcl(/*pname*/"absdr",/*pptr*/&absdr,/*art*/pstri,T_absdr_k,T_absdr_l,/*TxBp*/&Tx,/*Txi*/T_auf_Fax_angegebener_Absender,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!absdr.empty(),T_auf_Fax_angegebener_Absender);
	opn<<new optcl(/*pname*/"mfolge",/*pptr*/&mfolge,/*art*/pstri,T_mfolge_k,T_mfolge_l,/*TxBp*/&Tx,/*Txi*/T_kommagetrennte_Minutenfolge_der_Sendeversuche,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!mfolge.empty(),T_kommagetrennte_Minutenfolge_der_Sendeversuche);
	opn<<new optcl(/*pptr*/&datei,/*art*/pstri,T_dt_k,T_datei_l,/*TxBp*/&Tx,/*Txi*/T_zu_faxende_Datei,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/1);
	opn<<new optcl(/*pptr*/&an,/*art*/pstri,T_an_k,T_an_l,/*TxBp*/&Tx,/*Txi*/T_Zielfaxnr,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/1);
	opn<<new optcl(/*pptr*/&nurrein,/*art*/puchar,T_nr_k,T_nurrein_l,/*TxBp*/&Tx,/*Txi*/T_stellt_Faxe_nur_rein,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/1);
	hcl::virtinitopt(); //α
} // void hhcl::virtinitopt

// wird aufgerufen in lauf
void hhcl::pvirtmacherkl()
{
	hLog(violetts+Tx[T_virtmacherkl_Tx_lgn]+schwarz+ltoan(Tx.lgn));
//	erkl<<violett<<DPROG<<blau<<Txk[T_tut_dieses_und_jenes]<<schwarz; //ω 
} // void hhcl::pvirtmacherkl //α
//ω
//α
// wird aufgerufen in lauf
void hhcl::virtMusterVorgb()
{
	hLog(violetts+Tx[T_virtMusterVorgb]+schwarz); //ω
	hcl::virtMusterVorgb(); //α
} // void hhcl::MusterVorgb

// wird aufgerufen in lauf
void hhcl::pvirtvorzaehler()
{ //ω
} // void hhcl::virtvorzaehler() //α
//ω
// wird aufgerufen in lauf //α
void hhcl::virtzeigversion(const string& ltiffv/*=string()*/)
{
	hLog(violetts+Tx[T_virtzeigversion]+schwarz);
	hcl::virtzeigversion(ltiffv);  //ω
} // void hhcl::virtzeigversion //α
//ω
//α
// wird aufgerufen in lauf
void hhcl::pvirtvorrueckfragen()
{
	hLog(violetts+Tx[T_pvirtvorrueckfragen]+schwarz); //ω
} // void hhcl::pvirtvorrueckfragen //α


void hhcl::neurf()
{
	for(auto omit=opn.schl.end();omit!=opn.schl.begin();) {
		omit--;
		if ((*omit)->Txrf!=-1) {
		 const char* const text=(*(*omit)->TxBp)[(*omit)->Txrf];
		cout<<text<<endl;
		}
	}
} // void hhcl::neurf
 //ω
// wird aufgerufen in lauf //α
void hhcl::virtrueckfragen()
{
	hLog(violetts+Tx[T_virtrueckfragen]+", rzf: "+blau+ltoan(rzf)+schwarz);
	if (rzf) { //ω
		wvz=Tippverz(Tx[T_Verzeichnis_mit_wartenden_Dateien],&wvz);
		gfvz=Tippverz(Tx[T_Verzeichnis_mit_gefaxten_Dateien],&gfvz);
		ngvz=Tippverz(Tx[T_Verzeichnis_mit_gescheiterten_Dateien],&ngvz);
		usr=Tippstr(Tx[T_Benutzer_fuer_Fritzbox],&usr);
		string pwd2;
		pwd.clear();
		do {
			pwd= Tippstr(string(Tx[T_pwd])+Txk[T_fuer_Benutzer]+dblau+usr+schwarz+"'"/*,&smtppwd*/);
			pwd2=Tippstr(string(Tx[T_pwd])+Txk[T_fuer_Benutzer]+dblau+usr+schwarz+"'"+" ("+Txk[T_erneute_Eingabe]+")"/*,&mpw2*/);
		} while (pwd!=pwd2);
		host=Tippstr(Tx[T_Hostadresse_der_Fritzbox],&host);
		msn=Tippstr(Tx[T_MSN_zum_Faxen],&msn);
		if (absnr.empty()) absnr=msn;
		absnr=Tippstr(Tx[T_auf_Fax_angegebene_Absendernummer],&absnr);
		absdr=Tippstr(Tx[T_auf_Fax_angegebener_Absender],&absdr);
		mfolge=Tippstr(Tx[T_kommagetrennte_Minutenfolge_der_Sendeversuche],&mfolge);
	} // if (rzf) //α
	hcl::virtrueckfragen();
	//// opn.oausgeb(rot);
} // void hhcl::virtrueckfragen
//ω
//α
// wird aufgerufen in lauf
void hhcl::virtpruefweiteres()
{
	hLog(violetts+Tx[T_virtpruefweiteres]+schwarz); //ω
	// if (initDB()) exit(schluss(10,Tx[T_Datenbank_nicht_initialisierbar_breche_ab])); //α //ω
	verzeichnisse();
	hcl::virtpruefweiteres(); // z.Zt. leer //α
} // void hhcl::virtpruefweiteres

// wird aufgerufen in: virtpruefweiteres
void hhcl::verzeichnisse()
{
	hLog(violetts+Tx[T_verzeichnisse]+schwarz);
	pruefverz(wvz,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/1);
	pruefverz(gfvz,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/1);
	pruefverz(ngvz,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/1);
} // hhcl:: verzeichnisse


// wird aufgerufen in lauf
void hhcl::virtzeigueberschrift()
{ 
	hLog(violetts+Tx[T_virtzeigueberschrift]+schwarz); //ω
	// hier ggf. noch etwas an 'uebers' anhaengen //α
	hcl::virtzeigueberschrift();
} // void hhcl::virtzeigueberschrift
//ω
//α
// Parameter -st / --stop
// wird aufgerufen in: main
void hhcl::anhalten()
{
	hLog(violetts+Tx[T_anhalten]+schwarz);
	// crontab
	/*
	setztmpcron();
	for(int iru=0;iru<1;iru++) {
		const string befehl=
			"bash -c 'grep \""+saufr[iru]+"\" -q <(crontab -l)&&{ crontab -l|sed \"/"+zsaufr[iru]+"/d\">"+tmpcron+";crontab "+tmpcron+";};:'";
		systemrueck(befehl,obverb,oblog,*//*rueck=*//*0,*//*obsudc=*//*1);
	} // 	for(int iru=0;iru<2;iru++)
  */
	pruefcron("0"); // soll vor Log(Tx[T_Verwende ... stehen
	fLog(blaus+Tx[T_Cron_Aufruf_von]+schwarz+mpfad+blau+Tx[T_gestoppt]+schwarz,1,oblog); //ω
} // void hhcl::anhalten() //α
//ω
//α
void hhcl::pvirtvorpruefggfmehrfach()
{
	hLog(violetts+Tx[T_pvirtvorpruefggfmehrfach]+schwarz);
	// if (initDB()) exit(schluss(10,Tx[T_Datenbank_nicht_initialisierbar_breche_ab]));  //ω
	if (!an.empty()) {
		struct stat dstat{0};
		const char* const darten[]{".tif",".pdf"};
		int dart{0}; // Dateiart: 1=tif, 2=pdf
		if (datei.length()>=4) {
			for(size_t aktart=0;aktart<elemzahl(darten);aktart++) {
				if (!strcasecmp(datei.substr(datei.length()-4).c_str(),darten[aktart])) {
					dart=aktart+1;
					break;
				}
			}
		}
		// wenn die gewünschte Datei existiert
		if (dart && !lstat(datei.c_str(),&dstat) && dstat.st_size) {
			// Nummer ermitteln
			long long nr{0};
			string nrz;
			string nrdatei{wvz+"/nr"};
      if (nstumm) fLog("nrdatei: "+blaus+nrdatei+schwarz,1,oblog);
			for(int runde=0;runde<100000;runde++) {
				fstream fil(nrdatei,ios::in|ios::out);
				if (!fil.is_open()) {
					fil.clear();
					fil.open(nrdatei,ios::in|ios::out|ios::trunc); // erstellen
				}
				if (!fil.is_open()) {
					struct stat nstat{0};
					if (lstat(nrdatei.c_str(),&nstat) && runde>3)
						break; // wenn Datei nicht erstellbar, dann gleich aufgeben
					continue; // wenn andere Instanz damit arbeitet, dann warten
				}
				getline(fil,nrz);
				if (nrz.empty()) nrz="0";
				nr=stoll(nrz);
				nr++;
				fil.seekg(0,ios::beg);
				fil.clear(); // wenn Datei neu erstellt, ist das auch noch noetig
				fil<<nr<<endl;
        if (nstumm) fLog("nr: "+blaus+ltoan(nr)+schwarz,1,oblog);
				fil.close();
				break;
			}
			if (nr) {
				const string dname{wvz+"/dt"+nrz+".tif"},
							vname{wvz+"/dt"+nrz+".vw"};
				mdatei vw(vname,ios::out);
				if (vw.is_open()) {
					if (dart==1) {
						systemrueck("cp -L --preserve=timestamps \""+datei+"\" \""+dname+"\"",obverb);
					} else {
						const string bef{"gs -q -dNOPAUSE -dSAFER -dBATCH -sDEVICE=tiffg4 -sPAPERSIZE=a4 -dFIXEDMEDIA -r204x196 -sOutputFile=\""+dname+"\" \""+datei+"\" && touch -r \""+datei+"\" \""+dname+"\""};
						systemrueck(bef,obverb);
					}
					struct stat tstat{0};
					if (!lstat(dname.c_str(),&tstat) && tstat.st_size) {
						vw<<time(0)<<endl;
						string gesfolge{"0,"+mfolge};
						vw<<gesfolge<<endl;
						vw<<an<<endl;
						vw<<datei<<endl;
            gtrim(&gesfolge);
            int versz{1};
            for(string::iterator it=gesfolge.begin();it!=gesfolge.end()-1;++it) // wenn am Schluß ein Komma steht, zählt es nicht
              if (*it==',')
                versz++; // und für jedes Komma eins mehr
            vw<<"0/"<<versz<<endl;
            if (cronminut=="0") {
              cronminut="1"; // wenn root, so wird dann der cronjob ueberprueft und ggf. eingetragen
							hccd.obzuschreib=1;
            }
					} // 					if (!lstat(dname.c_str(),&tstat) && tstat.st_size)
				} // 				if (vw.is_open())
			} // 			if (nr)
		} // 		if (dart && !lstat(datei.c_str(),&dstat) && dstat.st_size)
	} // 	if (!an.empty())
  if (nurrein) keineverarbeitung=1; // wenn von autofax faxe reingestellt werden, sollen die aus Zeitgruenden nicht gleich verarbeitet werden 
} // void hhcl::pvirtvorpruefggfmehrfach //α
//ω

void hhcl::pvirtfuehraus() //α
{ 
	hLog(violetts+Tx[T_pvirtfuehraus]+schwarz); //ω
	svec dtn;
	systemrueck("find "+wvz+" -maxdepth 1 -size +0c -name 'dt*.vw'",obverb,oblog,&dtn);
	for(size_t i=0;i<dtn.size();i++) {
    if (nstumm) {fLog(blaus+dtn[i]+schwarz+":",1,oblog);}
		string tifd{dtn[i].substr(0,dtn[i].length()-3)+".tif"};
    if (nstumm) {fLog(blaus+" tifd:    "+schwarz+tifd,1,oblog);}
		struct stat tstat{0};
		if (lstat(tifd.c_str(),&tstat) || !tstat.st_size) continue;
		fstream vwdt(dtn[i].c_str(),ios::in|ios::out);
		if (vwdt.is_open()) {
			while (1) { // wird nur einmal durchlaufen
				char buffer[64];
				time_t jetzt{time(0)};
				tm *jetzttm{localtime(&jetzt)};
				strftime(buffer,sizeof buffer,"%a, %d.%m.%Y %H:%M:%S", jetzttm);
        if (nstumm) fLog(blaus+" jetzt:   "+tuerkis+ltoan(jetzt)+schwarz+" "+buffer,1,oblog);
        string zpabstr;
				if (!getline(vwdt,zpabstr)) break; // Einstell- bzw. naechster Faxzeitpunkt
				long zpab{atol(zpabstr.c_str())};
				string gesfolge;
				if (!getline(vwdt,gesfolge)) break; // naechste Aufrufe in Minuten
				const size_t kpos=gesfolge.find(",");
				const long min{atol(gesfolge.substr(0,kpos).c_str())};
				zpab+=60*min; // in Sekunden
				tm *zptm{localtime(&zpab)};
				strftime(buffer,sizeof buffer,"%a, %d.%m.%Y %H:%M:%S", zptm);
        if (nstumm) fLog(blaus+" zpab:    "+tuerkis+ltoan(zpab)+schwarz+" "+buffer,1,oblog);
				string ziel;
				if (!getline(vwdt,ziel)) break; // Zielrufnummer
        if (nstumm) fLog(blaus+" ziel:    "+schwarz+ziel+schwarz,1,oblog);
				string ursp;
				if (!getline(vwdt,ursp)) break; // Ursprungsdatei
        if (nstumm) fLog(blaus+" ursp:    "+schwarz+ursp+schwarz,1,oblog);
        string versz,gesz;
				getline(vwdt,versz);
				if (!versz.empty()) {
          if (nstumm) fLog(blaus+" versz:   "+schwarz+versz+schwarz,1,oblog);
					size_t pos{versz.find('/')};
					if (pos!=string::npos) {
						gesz=versz.substr(pos+1);
						versz=versz.substr(0,pos);
					}
				}
				if (jetzt>=zpab) {
          if (nstumm) fLog(blaus+" MinFolge:"+schwarz+gesfolge,1,oblog);
          if (nstumm) fLog(blaus+" Minuten: "+schwarz+ltoan(min),1,oblog);
					const string rest{kpos==string::npos?"":gesfolge.substr(kpos+1)};
          if (nstumm) fLog(blaus+" Rest:    "+string(kpos+1,' ')+schwarz+rest,1,oblog);
					if (!versz.empty()) {
						const long vers{atol(versz.c_str())+1};
						versz=ltoan(vers);
					}
          if (nstumm) fLog(tuerkiss+" jetzt >= zpab "+schwarz,1,oblog);
					//					const gchar *ptr[6]; // die Aktionen nach Faxen müssen auch in dmain, genauer fax_connection_status_cb geschehen, da oft danach Crash
					string ptr[/*14*/]{DPROG,tifd,msn,ziel,absnr,absdr,dtn[i],gfvz,ngvz,rest,ltoan(zpab),ursp,versz,gesz};
					retu=dmain(sizeof ptr/sizeof *ptr,ptr,&vwdt,usr,pwd,host,obverb);
//					caus<<"retu: "<<retu<<endl;
					/*
					if (!retu) {
						vwdt.close(); // Faxen erfolgreich, Dateien nach gfvz verschieben
						systemrueck("mv \""+tifd+"\" \""+dtn[i]+"\" \""+gfvz+"/\"",obverb,oblog);
					} else if (rest.empty()) {
						vwdt.close(); // Faxen erfolglos, Dateien nach ngvz verschieben
						obverb=1;
						systemrueck("mv \""+tifd+"\" \""+dtn[i]+"\" \""+ngvz+"/\"",obverb,oblog);
					} else {
						vwdt.seekg(0,ios::beg); // aktuelle Runde erfolglos, neue Daten schreiben
						vwdt.clear(); // wenn Datei neu erstellt, ist das auch noch noetig
						vwdt<<zpab<<endl;
						vwdt<<rest<<endl;
						vwdt<<ziel<<endl;
						vwdt<<ursp<<endl;
					}
					*/
					// Speicherzugriffsfehler aufspüren; wenn erfolgreich, dann verschieben und nicht mehr neu schreiben; am Ende des Schreibvorgangs Datei beenden
					// wenn aufgebraucht, in nichtgefaxt verschieben
					// wenn aufgebraucht, in nichtgefaxt verschieben
				} else {
          if (nstumm) fLog(tuerkiss+" jetzt <= zpab "+schwarz,1,oblog);
				}
				break;
			}
      if (nstumm) fLog(string(),1,oblog);
		}
	}
} // void hhcl::pvirtfuehraus  //α

// wird aufgerufen in lauf
void hhcl::virtschlussanzeige()
{  
	hLog(violetts+Txk[T_virtschlussanzeige]+schwarz); //ω
	hcl::virtschlussanzeige(); //α
} // void hhcl::virtschlussanzeige
 
// wird aufgerufen in: main
void hhcl::virtautokonfschreib()
{
// const int altobverb=obverb;
// obverb=1;
	hLog(violetts+Txk[T_autokonfschreib]+schwarz+", "+Txk[T_zu_schreiben]+((rzf||hccd.obzuschreib)?Txk[T_ja]:Txk[T_nein])); //ω
	struct stat kstat{0}; //α
	if (lstat(akonfdt.c_str(),&kstat))
		hccd.obzuschreib=1;
	if (rzf||hccd.obzuschreib) {
		hLog(gruens+Txk[T_schreibe_Konfiguration]+schwarz);
		// restliche Erklaerungen festlegen
		////    agcnfA.setzbem("language",sprachstr);
		hcl::virtautokonfschreib(); //ω
	} // if (rzf||hccd.obzuschreib) //α
// obverb=altobverb;
} // void hhcl::virtautokonfschreib

hhcl::~hhcl() 
{ //ω
} // hhcl::~hhcl //α

// wird nur im Fall obhilfe==3 nicht aufgerufen
void hhcl::virtlieskonfein()
{
	const int altobverb{obverb};
	//	obverb=1;
	hLog(violetts+Txk[T_virtlieskonfein]+schwarz); //ω
  nstumm=!stumm;
	hcl::virtlieskonfein(); //α //ω
	hLog(violetts+Txk[T_Ende]+Txk[T_virtlieskonfein]+schwarz); //α
	obverb=altobverb;
} // void hhcl::virtlieskonfein() //ω

int main(int argc,char** argv) //α
{
	if (argc>1) { //ω
	} //α
	hhcl hhi(argc,argv); // hiesige Hauptinstanz, mit lngzuw, setzlog und pruefplatte
	hhi.lauf(); // Einleitungsteil mit virtuellen Funktionen, 
	// mit virtVorgbAllg,pvirtVorgbSpeziell,initopt,parsecl,pvirtmacherkl,zeighilfe,virtlieskonfein,verarbeitkonf,lieszaehlerein,MusterVorgb,dovi,dovs,virtzeigversion
	// virtautokonfschreib,update,
	return hhi.retu;
} // int main 

void hhcl::virttesterg()
{
	hLog(violetts+Txk[T_virttesterg]+schwarz);
} //ω
