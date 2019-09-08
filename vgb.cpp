#include "kons.h"
#include "fbfax.h"

enum Txvg_ {
  T_VorgbSpeziell_Ueberlad,
  T_vgMAX,
};

const char *vgb_T[T_vgMAX+1][SprachZahl]{
      // T_VorgbSpeziell_Ueberlad
      {"VorgbSpeziell_Ueberlad()","specificprefs_overload()"},
      {"",""}
}; // const char *Txvgcl::TextC[T_vgMAX+1][SprachZahl]=

// class Txvgcl Txv;
class TxB Txv((const char* const* const* const*)vgb_T);

void hhcl::pvirtVorgbSpeziell()
{
	hLog(violetts+Txv[T_VorgbSpeziell_Ueberlad]+schwarz);
	usr="";
	msn="";
	absnr=""+msn;
	absdr="";
	hLog(violetts+Txk[T_Ende]+Txv[T_VorgbSpeziell_Ueberlad]+schwarz);
} // void hhcl::pvirtVorgbSpeziell
