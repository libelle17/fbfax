<h3>Manual: 1) <a href="#english_E">english</a>, 2) <a href="#deutsch_D">deutsch (unten anschließend)</a></h3>

<h1 align="center">FBFAX (Version 0.10411) - english<a name="english_D"></a></h1>

<a href="#NAME_D">NAME</a><br>
<a href="#SYNOPSIS_D">SYNOPSIS</a><br>
<a href="#SHORT DESCRIPTION_D">SHORT DESCRIPTION</a><br>
<a href="#INSTALLATION_D">INSTALLATION</a><br>
<a href="#USAGE_D">USAGE</a><br>
<a href="#OPTIONS_D">OPTIONS</a><br>
<a href="#FUNCTIONALITY_D">FUNCTIONALITY</a><br>
<a href="#CONTROL FILE FORMAT_D">CONTROL FILE FORMAT</a><br>
<a href="#PRECONDITIONS_D">PRECONDITIONS</a><br>
<a href="#AUTOMATICALLY INSTALLED SOFTWARE PACKAGES_D">AUTOMATICALLY INSTALLED SOFTWARE PACKAGES</a><br>
<a href="#IMPLICATIONS_D">IMPLICATIONS</a><br>
<a href="#UNINSTALLING_D">UNINSTALLING</a><br>
<a href="#RETURN CODES_D">RETURN CODES</a><br>
<a href="#ERRORS_D">ERRORS</a><br>
<a href="#PROGRAM MODIFICATION_D">PROGRAM MODIFICATION</a><br>
<a href="#LIABILITY_D">LIABILITY</a><br>
<a href="#AUTHOR_D">AUTHOR</a><br>

<hr>


<h2>NAME
<a name="NAME_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em"><b>fbfax &minus;
Fax transmission via Fritz!Box</b>: queues fax jobs and
transmits them via a Fritz!Box using the TR-064 protocol
<br>
(manpage-Hilfe in deutsch verf&uuml;gbar: &rsquo;man
-Lde fbfax&rsquo;)</p>

<h2>SYNOPSIS
<a name="SYNOPSIS_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em"><b>fbfax
[-&lt;shortopt&gt;|--&lt;longopt&gt; [&lt;supplement&gt;]]
...</b></p>

<h2>SHORT DESCRIPTION
<a name="SHORT DESCRIPTION_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em"><b>fbfax</b> is
a command line program that sends TIFF or PDF files as faxes
via a Fritz!Box. It maintains its own send queue with
configurable retry intervals and is typically controlled by
<b>autofax</b>. <br>
When a file is queued, <b>fbfax</b> creates a control file
in the waiting directory. On each subsequent call it checks
whether the next send time has been reached and, if so,
initiates the transmission via the Fritz!Box TR-064
protocol. Afterwards the file is moved to the directory for
successfully sent or failed faxes.</p>

<h2>INSTALLATION
<a name="INSTALLATION_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em">First, please
read the chapters &rsquo;Functionality&rsquo;,
&rsquo;Preconditions&rsquo;, &rsquo;Automatically installed
software packages&rsquo; and &rsquo;Implications&rsquo;
below. Then, if connected to the internet, call (e.g. by
copying the line and pasting it into a terminal): <b><br>
N=fbfax;P=${N}_inst.sh;cd &#732;;wget
https://raw.githubusercontent.com/libelle17/$N/master/install.sh
-O$P&&sh $P</b> <br>
At last, call: <b><br>
fbfax</b> <br>
and answer some questions of the program, in particular
Fritz!Box user, password and MSN.</p>

<h2>USAGE
<a name="USAGE_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em"><b>fbfax</b> is
normally called by <b>autofax</b> rather than directly.
Direct use is possible:</p>

<p style="margin-left:9%; margin-top: 1em"><b>Queue a fax:
<br>
fbfax -fl /path/to/file.tif -to 089123456</b> <br>
or for a PDF file: <b><br>
fbfax -fl /path/to/file.pdf -to 089123456</b> <br>
The file is copied to the waiting directory (TIFF directly,
PDF first converted to TIFF via <b>gs</b>) and a control
file is created. The name of the control file is printed to
<b>stdout</b> (for autofax).</p>

<p style="margin-left:9%; margin-top: 1em"><b>Process the
queue: <br>
fbfax</b> (without further arguments or via cron) <br>
Checks all control files in the waiting directory and sends
overdue faxes.</p>

<p style="margin-left:9%; margin-top: 1em"><b>Display
directories</b> (for autofax): <b><br>
fbfax -zgvz</b> <br>
Prints the waiting, faxed and notfaxed directory paths to
<b>stdout</b>, one per line.</p>

<p style="margin-left:9%; margin-top: 1em"><b>Queue only,
do not send immediately</b> (for autofax): <b><br>
fbfax -fl file.tif -to 089123456 -oi</b></p>

<h2>OPTIONS
<a name="OPTIONS_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em">&rsquo;<b>fbfax
-?</b>&rsquo; or &rsquo;<b>fbfax -h</b>&rsquo; shows the
important command line options and &rsquo;<b>fbfax
-lh</b>&rsquo; all of them. The configuration file can be
edited directly by &rsquo;<b>fbfax -vi</b>&rsquo; or
interactively by &rsquo;<b>fbfax -rf</b>&rsquo;. <br>
Programm: <b>/root/fbfax/fbfax</b>, V: <b>0.10411 <br>
Options which are not saved (current value in parentheses):
<br>
-st, --stop</b>: stop fbfax (<b>0</b>) <b><br>
-n, --reccount &lt;string&gt;</b>: No. of listed entries =
&lt;no&gt; instead of (&rsquo;<b>30</b>&rsquo;) <b><br>
-fl, --file &lt;string&gt;</b>: file to be faxed
(&rsquo;&rsquo;) <b><br>
-to, --to &lt;string&gt;</b>: target fax number
(&rsquo;&rsquo;) <b><br>
-oi, --onlyin</b>: inserts faxes only (<b>0</b>) <b><br>
-shdr, --showdirs</b>: show spool directories like
<b>/var/spool/fbfax/waiting</b> (<b>0</b>) <b><br>
-v, --verbose</b>: screen output more verbose (<b>0</b>)
<b><br>
-mu, --mute</b>: screen output completely mute (<b>0</b>)
<b><br>
-lfn, --logfilenew</b>: delete log file afore (<b>0</b>)
<b><br>
-cf, --conffile &lt;string&gt;</b>: uses configuration file
&lt;string&gt; instead of (&rsquo;&rsquo;) <b><br>
-h, --help</b>: Explanation of frequent options (<b>3</b>)
<b><br>
-lh, --longhelp</b>: Explanation of all options (<b>3</b>)
<b><br>
-vi, --vi</b>: edit/view configuration file , log file etc.
(finish with &rsquo;:qa&rsquo;) (<b>0</b>) <b><br>
-scf, --showconf</b>: show the name of the configuration
file (<b>0</b>) <b><br>
-writec, --writeconf</b>: write configuration file
(<b>0</b>) <b><br>
-vs, --vs</b>: edit/view source files in
<b>/home/schade/fbfax</b>(finish with &rsquo;:qa&rsquo;)
(<b>0</b>) <b><br>
-ia, --interactive</b>: all parameters will be prompted
(some of them not shown here) (<b>0</b>) <b><br>
-noia, --nointeraction</b>: no questions, e.g. for a call
from within cron (<b>0</b>) <b><br>
-info, --version</b>: shows the program version (<b>0</b>)
<b><br>
Options to be saved in the configuration file: (preced.
&rsquo;1&rsquo;=don&rsquo;t save, &rsquo;no&rsquo;=contrary,
e.g. &rsquo;-noocra&rsquo;,&rsquo;-1noocri&rsquo;): <br>
-wdr, --waitdir &lt;path&gt;</b>: files are waiting in
&lt;path&gt; instead of
(&rsquo;<b>/var/spool/fbfax/waiting</b>&rsquo;) <b><br>
-fdr, --faxeddir &lt;path&gt;</b>: Processed faxes are
collected here instead of
(&rsquo;<b>/var/spool/fbfax/faxed</b>&rsquo;) <b><br>
-ndr, --notfaxeddir &lt;path&gt;</b>: Failed faxes are
collected here instead of
(&rsquo;<b>/var/spool/fbfax/notfaxed</b>&rsquo;) <b><br>
-usr, --usr &lt;string&gt;</b>: takes the user
&lt;string&gt; for the fritzbox instead of (&rsquo;&rsquo;)
<b><br>
-pwd, --pwd &lt;string&gt;</b>: uses the password
&lt;string&gt; for the fritz box <b><br>
-host, --host &lt;string&gt;</b>: host address for the fritz
box (&rsquo;<b>fritz.box</b>&rsquo;) <b><br>
-msn, --msn &lt;string&gt;</b>: MSN for faxing
(&rsquo;&rsquo;) <b><br>
-sdrno, --senderno &lt;string&gt;</b>: sender no on fax
(&rsquo;&rsquo;) <b><br>
-sdr, --sender &lt;string&gt;</b>: sender name on fax
(&rsquo;&rsquo;) <b><br>
-msq, --minsequence &lt;string&gt;</b>: comma-separated
sequence of minutes of the send tries
(&rsquo;<b>2,2,3,3,3,5,5,10,10,60,60,60,120,120,720,1440</b>&rsquo;)
<b><br>
-msec, --maxsec &lt;zahl&gt;</b>: no of seconds for a fax
(<b>900</b>) <b><br>
-lg, --language &lt;string&gt;</b>:
Language/Sprache/Lingue/Lingua
[<b>d</b>eutsch,<b>e</b>nglisch] (&rsquo;<b>e</b>&rsquo;)
<b><br>
-ldr, --logdir &lt;path&gt;</b>: choses &lt;path&gt; as log
directory, currently (&rsquo;<b>/var/log</b>&rsquo;) <b><br>
-lf, --logfilename &lt;string&gt;</b>: log file
&lt;string&gt; (in path &rsquo;<b>/var/log</b>&rsquo;) will
be used instead of (&rsquo;<b>fbfax.log</b>&rsquo;) <b><br>
-l, --log &lt;zahl&gt;</b>: put detailed logs in file
&rsquo;<b>/var/log/fbfax.log</b>&rsquo; (otherwise shorter)
(<b>0</b>) <b><br>
-cm, --cronminutes &lt;string&gt;</b>: every how many
minutes shall <b>fbfax</b> be called in crontab (0=not at
all), instead of (&rsquo;<b>0</b>&rsquo;) <b><br>
-autoupd, --autoupdate &lt;zahl&gt;</b>: Update program
automatically (<b>1</b>)</p>

<h2>FUNCTIONALITY
<a name="FUNCTIONALITY_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em">When called,
&rsquo;<b>fbfax</b>&rsquo; accomplishes the following:</p>

<p style="margin-left:9%; margin-top: 1em"><b>1)</b>
General and program-specific defaults are set (directories,
host, minute sequence).</p>

<p style="margin-left:9%; margin-top: 1em"><b>2)</b>
Defaults are loaded from the configuration file, if it
exists (default: <b>fbfax.conf</b> in the program
directory).</p>

<p style="margin-left:9%; margin-top: 1em"><b>3)</b>
Command line arguments are evaluated.</p>

<p style="margin-left:9%; margin-top: 1em"><b>4)</b> If
<b>-shdr</b> is set: the waiting, faxed and notfaxed
directory paths are printed to <b>stdout</b> and the program
exits. This option is used by <b>autofax</b> to determine
the spool directories at runtime.</p>

<p style="margin-left:9%; margin-top: 1em"><b>5)</b> The
three spool directories are checked and created if
needed.</p>

<p style="margin-left:9%; margin-top: 1em"><b>6)</b> If
<b>-fl</b> and <b>-to</b> are given (queue a fax): <b><br>
a)</b> A TIFF file is copied directly to the waiting
directory. <b><br>
b)</b> A PDF file is first converted to TIFF format (Group
4, A4, 204x196 dpi) using <b>gs</b> (Ghostscript). <b><br>
c)</b> A sequentially numbered control file <b>dtN.vw</b> is
created. It contains: the current timestamp, the minute
sequence for send retries, the target number, the source
file path and the total number of send attempts. The program
also enters itself into crontab if needed. <b><br>
d)</b> The name of the control file is printed to
<b>stdout</b>.</p>

<p style="margin-left:9%; margin-top: 1em"><b>7)</b> If
<b>-oi</b> (only insert) is set, the program exits after
queuing without attempting to send.</p>

<p style="margin-left:9%; margin-top: 1em"><b>8)</b>
Regular run (queue processing): the program searches the
waiting directory for control files <b>dt*.vw</b> with a
corresponding non-empty TIFF file. For each file it checks
whether the next send time (stored start time plus next
minute from the minute sequence) has been reached. If so:
<b><br>
a)</b> The page count of the TIFF file is determined and the
timeout calculated accordingly (one minute per page plus
connection setup). <b><br>
b)</b> The program forks a child process that calls
<b>dmain()</b>. <b>dmain()</b> establishes a connection to
the Fritz!Box via the TR-064 protocol (SOAP requests via
<b>libcurl</b>) and submits the TIFF file for fax
transmission. <b><br>
c)</b> The parent process waits up to <b>maxsec</b> seconds
for the child. On timeout the child is terminated.</p>

<p style="margin-left:9%; margin-top: 1em"><b>9)</b>
Depending on the result of the send attempt, the files are
moved to the faxed or notfaxed directory, or the next entry
in the minute sequence is noted for the next retry.</p>

<p style="margin-left:9%; margin-top: 1em"><b>10)</b> The
configuration file is written if necessary.</p>

<h2>CONTROL FILE FORMAT
<a name="CONTROL FILE FORMAT_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em">Each control
file <b>dtN.vw</b> contains line by line:</p>

<p style="margin-left:9%; margin-top: 1em"><b>Line 1:</b>
Unix timestamp of the start time (or last attempt) <b><br>
Line 2:</b> remaining minute sequence, comma-separated (e.g.
<b>0,2,3,5,10</b>); the first value gives the minutes until
the next attempt <b><br>
Line 3:</b> target fax number <b><br>
Line 4:</b> path of the source file <b><br>
Line 5:</b> attempts made/total attempts (e.g.
<b>2/16</b>)</p>

<h2>PRECONDITIONS
<a name="PRECONDITIONS_D"></a>
</h2>



<p style="margin-left:9%; margin-top: 1em"><b>Hardware</b>:
Fritz!Box with active fax function (fax must be configured
in the Fritz!Box web interface), reachable in the local
network under the configured host (default:
<b>fritz.box</b>). <b><br>
Software</b>: Linux (Opensuse &gt;= 42.1, Debian &gt;= 9,
Ubuntu &gt;= 16.04, Mint &gt;= 18, Fedora &gt;= 24).
<b>libcurl</b> must be installed. <b>ghostscript</b>
(<b>gs</b>) is needed for PDF faxing. <b>libtiff</b> must be
installed.</p>

<h2>AUTOMATICALLY INSTALLED SOFTWARE PACKAGES
<a name="AUTOMATICALLY INSTALLED SOFTWARE PACKAGES_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em">(for this
purpose, depending on the distribution, zypper, apt(-get),
dnf or yum are used).</p>


<p style="margin-left:9%; margin-top: 1em"><b>makefile:</b>
<br>
gcc V.6 or higher, g++ V.6 or higher, groff,
libtiff-dev(el)</p>

<p style="margin-left:9%; margin-top: 1em"><b>fbfax:</b>
<br>
boost, boost-devel, boost-locale, capi4linux, cron,
ghostscript, libcurl, libcurl-devel, libtiff, samba</p>

<h2>IMPLICATIONS
<a name="IMPLICATIONS_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em">The program has
to take the following measures for its neat function:</p>

<p style="margin-left:9%; margin-top: 1em"><b>1)</b> Sudo
(is missing per default in debian) will be installed if
needed.</p>

<p style="margin-left:9%; margin-top: 1em"><b>2)</b>
&rsquo;GNU make&rsquo; will be installed if not present,
automatically by calling &rsquo;sh install.sh&rsquo;.</p>

<p style="margin-left:9%; margin-top: 1em"><b>3)</b>
Creation of a logfile, per default
<b>/var/log/fbfaxvorgabe.log</b>.</p>

<p style="margin-left:9%; margin-top: 1em"><b>4)</b>
Creation of the spool directories
<b>/var/spool/fbfax/waiting</b>,
<b>/var/spool/fbfax/faxed</b> and
<b>/var/spool/fbfax/notfaxed</b>.</p>

<p style="margin-left:9%; margin-top: 1em"><b>5)</b> If
necessary, creation of the configuration file
<b>fbfax.conf</b> in the program directory (default:
<b>/usr/local/sbin/</b>).</p>

<p style="margin-left:9%; margin-top: 1em"><b>6)</b>
Insertion of a line for the automatic periodic program call
in root&rsquo;s crontab as soon as the first fax is queued
(interval: 1 minute).</p>

<h2>UNINSTALLING
<a name="UNINSTALLING_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em">Change in a
terminal to the installation directory (for the same
installed user, it&rsquo;s <b>cd &#732;/fbfax</b>, otherwise
it will be displayed by <b>fbfax -info</b>). <br>
Call <b>make uninstall</b>. <br>
Then the installed <b>fbfax</b> will be deleted and the
script <b>uninstallinv</b> will be executed in reverse
order. <br>
Configuration files and accumulated fax data will not be
deleted. <br>
Error messages can be ignored.</p>

<h2>RETURN CODES
<a name="RETURN CODES_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em"><b>0</b>: Normal
return code <b><br>
1</b>: Fork to <b>dmain()</b> failed <b><br>
7</b>: The info screen (<b>fbfax -info</b>) has been
displayed <b><br>
8</b>: The help has been displayed <b><br>
98</b>: Program stopped because it is already running once
<br>
After calling <b>fbfax -vi</b> or <b>fbfax -vs</b> the
return code of <b>vi</b>/<b>vim</b> will be passed</p>

<h2>ERRORS
<a name="ERRORS_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em">Please report
any errors with the word &rsquo;fbfax&rsquo; included in the
email headline. <br>
Please report as well, if different hard- or software yields
a requirement for a program modification.</p>

<h2>PROGRAM MODIFICATION
<a name="PROGRAM MODIFICATION_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em">By calling
&rsquo;<b>sh viall</b>&rsquo; and application of the usual
&rsquo;<b>vim</b>&rsquo;-commands, followed by
&rsquo;<b>make</b>&rsquo; and &rsquo;<b>make
install</b>&rsquo; from the installation directory
(&rsquo;<b>&#732;/fbfax</b>&rsquo;), You may alter the
program.</p>

<h2>LIABILITY
<a name="LIABILITY_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em">The program has
been written with the best aim and has been tested by the
author. <br>
Nevertheless the author cannot be liable for any damage
caused by the program.</p>

<h2>AUTHOR
<a name="AUTHOR_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em">Gerald Schade
(geraldschade@gmx.de; www.diabdachau.de)</p>
<hr>
</body>
</html>

<h1 align="center">FBFAX (Version 0.10411) - deutsch<a name="deutsch_D"></a></h1>

<a href="#NAME_D">NAME</a><br>
<a href="#SYNOPSIS_D">SYNOPSIS</a><br>
<a href="#KURZBESCHREIBUNG_D">KURZBESCHREIBUNG</a><br>
<a href="#INSTALLATION_D">INSTALLATION</a><br>
<a href="#GEBRAUCH_D">GEBRAUCH</a><br>
<a href="#OPTIONEN_D">OPTIONEN</a><br>
<a href="#FUNKTIONSWEISE_D">FUNKTIONSWEISE</a><br>
<a href="#STEUERDATEIFORMAT_D">STEUERDATEIFORMAT</a><br>
<a href="#VORAUSSETZUNGEN_D">VORAUSSETZUNGEN</a><br>
<a href="#AUTOMATISCH INSTALLIERTE PROGRAMMPAKETE_D">AUTOMATISCH INSTALLIERTE PROGRAMMPAKETE</a><br>
<a href="#AUSWIRKUNGEN DES PROGRAMMABLAUFS_D">AUSWIRKUNGEN DES PROGRAMMABLAUFS</a><br>
<a href="#DEINSTALLATION_D">DEINSTALLATION</a><br>
<a href="#R&Uuml;CKGABEWERTE_D">R&Uuml;CKGABEWERTE</a><br>
<a href="#FEHLER_D">FEHLER</a><br>
<a href="#PROGRAMM&Auml;NDERUNG_D">PROGRAMM&Auml;NDERUNG</a><br>
<a href="#HAFTUNG_D">HAFTUNG</a><br>
<a href="#AUTOR_D">AUTOR</a><br>

<hr>


<h2>NAME
<a name="NAME_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em"><b>fbfax &minus;
Faxversand &uuml;ber Fritz!Box</b>: stellt Faxe in eine
Sendewarteschlange und &uuml;bertr&auml;gt sie
&uuml;ber die Fritz!Box per TR-064-Protokoll <br>
(manpage available in english: &rsquo;man fbfax&rsquo; or
&rsquo;man -Len fbfax&rsquo;)</p>

<h2>SYNOPSIS
<a name="SYNOPSIS_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em"><b>fbfax
[-&lt;kurzopt&gt;|--&lt;langopt&gt;
[&lt;erg&auml;nzung&gt;]] ...</b></p>

<h2>KURZBESCHREIBUNG
<a name="KURZBESCHREIBUNG_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em"><b>fbfax</b> ist
ein Befehlszeilenprogramm, das TIFF- oder PDF-Dateien
&uuml;ber die Fritz!Box per Fax versendet. Es verwaltet
dazu eine eigene Sendewarteschlange mit konfigurierbaren
Wiederholungsintervallen und wird typischerweise von
<b>autofax</b> gesteuert. <br>
Beim Einreihen einer Datei erzeugt <b>fbfax</b> eine
Steuerdatei im Warteverzeichnis. Bei jedem weiteren Aufruf
pr&uuml;ft es, ob der n&auml;chste Sendezeitpunkt
erreicht ist, und startet gegebenenfalls den Sendevorgang
&uuml;ber das TR-064-Protokoll der Fritz!Box. Nach dem
Abschluss wird die Datei ins Verzeichnis f&uuml;r
erfolgreiche bzw. gescheiterte Faxe verschoben.</p>

<h2>INSTALLATION
<a name="INSTALLATION_D"></a>
</h2>



<p style="margin-left:9%; margin-top: 1em">Zun&auml;chst
lesen Sie bitte die untenstehenden Kapitel
&rsquo;Funktionsweise&rsquo;, &rsquo;Voraussetzungen&rsquo;,
&rsquo;Automatisch installierte Programmpakete&rsquo; und
&rsquo;Auswirkungen des Programmablaufs&rsquo;. <br>
Anschlie&szlig;end verbinden Sie den Rechner mit dem
Internet und rufen Sie auf (z.B. durch Kopieren der Zeile in
die Zwischenablage und Einf&uuml;gen in einem Terminal):
<b><br>
N=fbfax;P=${N}_inst.sh;cd &#732;;wget
https://raw.githubusercontent.com/libelle17/$N/master/install.sh
-O$P&&sh $P</b> <br>
Zuletzt rufen Sie auf: <b><br>
fbfax</b> <br>
und beantworten einige R&uuml;ckfragen des Programms,
insbesondere Fritzbox-Benutzer, Passwort und MSN.</p>

<h2>GEBRAUCH
<a name="GEBRAUCH_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em"><b>fbfax</b>
wird normalerweise nicht direkt, sondern von <b>autofax</b>
aufgerufen. Direkter Aufruf ist aber m&ouml;glich:</p>

<p style="margin-left:9%; margin-top: 1em"><b>Fax
einreihen: <br>
fbfax -dt /pfad/zur/datei.tif -an 089123456</b> <br>
bzw. f&uuml;r eine PDF-Datei: <b><br>
fbfax -dt /pfad/zur/datei.pdf -an 089123456</b> <br>
Die Datei wird ins Warteverzeichnis kopiert (TIFF direkt,
PDF zun&auml;chst mit <b>gs</b> in TIFF konvertiert) und
eine Steuerdatei angelegt. Der Name der Steuerdatei wird auf
<b>stdout</b> ausgegeben (f&uuml;r autofax).</p>


<p style="margin-left:9%; margin-top: 1em"><b>Warteschlange
abarbeiten: <br>
fbfax</b> (ohne weitere Argumente oder via cron) <br>
Pr&uuml;ft alle Steuerdateien im Warteverzeichnis und
sendet f&auml;llige Faxe.</p>


<p style="margin-left:9%; margin-top: 1em"><b>Verzeichnisse
ausgeben</b> (f&uuml;r autofax): <b><br>
fbfax -zgvz</b> <br>
Gibt Warte-, Gefaxt- und Nichtgefaxt-Verzeichnis auf
<b>stdout</b> aus, je eine Zeile.</p>

<p style="margin-left:9%; margin-top: 1em"><b>Nur
einreihen, nicht sofort senden</b> (f&uuml;r autofax):
<b><br>
fbfax -dt datei.tif -an 089123456 -nr</b></p>

<h2>OPTIONEN
<a name="OPTIONEN_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em">&rsquo;<b>fbfax
-?</b>&rsquo; oder &rsquo;<b>fbfax -h</b>&rsquo; zeigt die
wichtigen Befehlszeilenoptionen und &rsquo;<b>fbfax
-lh</b>&rsquo; alle. Die Konfigurationsdatei kann
&uuml;ber &rsquo;<b>fbfax -vi</b>&rsquo; direkt editiert
oder &uuml;ber &rsquo;<b>fbfax -rf</b>&rsquo; interaktiv
gepflegt werden. <br>
Programm: <b>/root/fbfax/fbfax</b>, V: <b>0.10411 <br>
Optionen, die nicht gespeichert werden (aktueller Wert in
Klammern): <br>
-st, --stop</b>: fbfax anhalten (<b>0</b>) <b><br>
-n, --dszahl &lt;string&gt;</b>: Zahl der aufzulistenden
Datensaetze = &lt;zahl&gt; statt (&rsquo;<b>30</b>&rsquo;)
<b><br>
-dt, --datei &lt;string&gt;</b>: zu faxende Datei
(&rsquo;&rsquo;) <b><br>
-an, --an &lt;string&gt;</b>: Zielfaxnr (&rsquo;&rsquo;)
<b><br>
-nr, --nurrein</b>: stellt Faxe nur rein (<b>0</b>) <b><br>
-zgvz, --zeigverz</b>: Spoolverzeichnisse wie
<b>/var/spool/fbfax/waiting</b>anzeigen (<b>0</b>) <b><br>
-w, --wortreich</b>: Bildschirmausgabe gespraechiger
(<b>0</b>) <b><br>
-stu, --stumm</b>: Bildschirmausgabe ganz stumm (<b>0</b>)
<b><br>
-ldn, --logdateineu</b>: logdatei vorher loeschen (<b>0</b>)
<b><br>
-kd, --konfdatei &lt;string&gt;</b>: verwendet
Konfigurationsdatei &lt;string&gt; anstatt (&rsquo;&rsquo;)
<b><br>
-h, --hilfe</b>: Erklaerung haeufiger Optionen (<b>3</b>)
<b><br>
-lh, --langhilfe</b>: Erklaerung aller Optionen (<b>3</b>)
<b><br>
-vi, --vi</b>: Konfigurationsdatei , Logdatei usw.
bearbeiten/sehen (beenden mit &rsquo;:qa&rsquo;) (<b>0</b>)
<b><br>
-zkf, --konfzeig</b>: Konfigurationsdateinamenanzeigen
(<b>0</b>) <b><br>
-kschrb, --kschreib</b>: Konfigurationsdatei schreiben
(<b>0</b>) <b><br>
-vs, --vs</b>: Quelldateien in <b>/home/schade/fbfax</b>
bearbeiten/sehen (beenden mit &rsquo;:qa&rsquo;) (<b>0</b>)
<b><br>
-rf, --rueckfragen</b>: alle Parameter werden abgefragt
(darunter einige hier nicht gezeigte) (<b>0</b>) <b><br>
-krf, --keinerueckfragen</b>: keine Rueckfragen, z.B. fuer
Aufruf aus cron (<b>0</b>) <b><br>
-info, --version</b>: Zeigt die Programmversion an
(<b>0</b>) <b><br>
Optionen z.Speich. i.Konfigur&rsquo;datei (vorausg.
&rsquo;1&rsquo;=doch nicht speichern,
&rsquo;no&rsquo;=Gegenteil, z.B.
&rsquo;-noocra&rsquo;,&rsquo;-1noocri&rsquo;): <br>
-wvz, --wartevz &lt;pfad&gt;</b>: Dateien warten in
&lt;pfad&gt; anstatt
(&rsquo;<b>/var/spool/fbfax/waiting</b>&rsquo;) <b><br>
-gvz, --gefaxtvz &lt;pfad&gt;</b>: Fertige Faxe werden hier
gesammelt anstatt in
(&rsquo;<b>/var/spool/fbfax/faxed</b>&rsquo;) <b><br>
-ngvz, --nichtgefaxtvz &lt;pfad&gt;</b>: Gescheiterte Faxe
werden hier gesammelt anstatt in
(&rsquo;<b>/var/spool/fbfax/notfaxed</b>&rsquo;) <b><br>
-usr, --usr &lt;string&gt;</b>: verwendet fuer die Fritzbox
den Benutzer &lt;string&gt; anstatt (&rsquo;&rsquo;) <b><br>
-pwd, --pwd &lt;string&gt;</b>: verwendet fuer die Fritzbox
das Passwort <b><br>
-host, --host &lt;string&gt;</b>: Hostadresse der Fritzbox
(&rsquo;<b>fritz.box</b>&rsquo;) <b><br>
-msn, --msn &lt;string&gt;</b>: MSN zum Faxen
(&rsquo;&rsquo;) <b><br>
-absnr, --absendernr &lt;string&gt;</b>: auf Fax angegebene
Absendernummer (&rsquo;&rsquo;) <b><br>
-abs, --absender &lt;string&gt;</b>: auf Fax angegebener
Absendername (&rsquo;&rsquo;) <b><br>
-mfg, --minfolge &lt;string&gt;</b>: kommagetrennte
Minutenfolge der Sendeversuche
(&rsquo;<b>2,2,3,3,3,5,5,10,10,60,60,60,120,120,720,1440</b>&rsquo;)
<b><br>
-msec, --maxsec &lt;zahl&gt;</b>: Zahl der Sekunden fuer ein
Fax (<b>900</b>) <b><br>
-sp, --sprache &lt;string&gt;</b>:
Language/Sprache/Lingue/Lingua
[<b>d</b>eutsch,<b>e</b>nglisch] (&rsquo;<b>d</b>&rsquo;)
<b><br>
-lvz, --logvz &lt;pfad&gt;</b>: waehlt als Logverzeichnis
&lt;pfad&gt;, derzeit (&rsquo;<b>/var/log</b>&rsquo;)
<b><br>
-ld, --logdname &lt;string&gt;</b>: logdatei &lt;string&gt;
(im Pfad &rsquo;<b>/var/log</b>&rsquo;) wird verwendet
anstatt (&rsquo;<b>fbfax.log</b>&rsquo;) <b><br>
-l, --log &lt;zahl&gt;</b>: protokolliert ausfuehrlich in
Datei &rsquo;<b>/var/log/fbfax.log</b>&rsquo; (sonst
knapper) (<b>0</b>) <b><br>
-cm, --cronminuten &lt;string&gt;</b>: alle wieviel Minuten
soll <b>fbfax</b> ueber crontab aufgerufen werden (0=gar
nicht), anstatt (&rsquo;<b>0</b>&rsquo;) <b><br>
-autoakt, --autoaktual &lt;zahl&gt;</b>: Programm
automatisch aktualisieren (<b>1</b>)</p>

<h2>FUNKTIONSWEISE
<a name="FUNKTIONSWEISE_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em">Beim Aufruf
f&uuml;hrt &rsquo;<b>fbfax</b>&rsquo; folgende Schritte
aus:</p>

<p style="margin-left:9%; margin-top: 1em"><b>1)</b>
Allgemeine und programmspezifische Vorgabewerte werden
gesetzt (Verzeichnisse, Host, Minutenfolge).</p>

<p style="margin-left:9%; margin-top: 1em"><b>2)</b> Die
Konfigurationsdatei wird eingelesen, falls vorhanden
(Standard: <b>fbfax.conf</b> im Programmverzeichnis).</p>

<p style="margin-left:9%; margin-top: 1em"><b>3)</b>
Befehlszeilenparameter werden ausgewertet.</p>

<p style="margin-left:9%; margin-top: 1em"><b>4)</b> Falls
<b>-zgvz</b> gesetzt ist: Warte-, Gefaxt- und
Nichtgefaxt-Verzeichnis werden auf <b>stdout</b> ausgegeben
und das Programm beendet. Diese Option wird von
<b>autofax</b> verwendet, um die Verzeichnisse zur Laufzeit
zu ermitteln.</p>

<p style="margin-left:9%; margin-top: 1em"><b>5)</b> Die
drei Spoolverzeichnisse werden gepr&uuml;ft und ggf.
erstellt.</p>

<p style="margin-left:9%; margin-top: 1em"><b>6)</b> Falls
<b>-dt</b> und <b>-an</b> angegeben sind (Fax einreihen):
<b><br>
a)</b> Bei einer TIFF-Datei wird sie direkt ins
Warteverzeichnis kopiert. <b><br>
b)</b> Bei einer PDF-Datei wird sie mit <b>gs</b>
(Ghostscript) in das TIFF-Format (Gruppe 4, A4, 204x196 dpi)
konvertiert. <b><br>
c)</b> Eine fortlaufend nummerierte Steuerdatei
<b>dtN.vw</b> wird angelegt. Sie enth&auml;lt: aktuellen
Zeitstempel, Minutenfolge der Sendeversuche, Zielnummer,
Quelldateiname und Gesamtzahl der Sendeversuche.
Au&szlig;erdem tr&auml;gt das Programm sich bei
Bedarf in den crontab ein. <b><br>
d)</b> Der Name der Steuerdatei wird auf <b>stdout</b>
ausgegeben.</p>

<p style="margin-left:9%; margin-top: 1em"><b>7)</b> Falls
<b>-nr</b> (nur einreihen) gesetzt ist, wird das Programm
nach dem Einreihen ohne Sendeversuch beendet.</p>

<p style="margin-left:9%; margin-top: 1em"><b>8)</b>
Regul&auml;rer Durchlauf (Abarbeitung der
Warteschlange): Das Programm sucht im Warteverzeichnis nach
Steuerdateien <b>dt*.vw</b> mit zugeh&ouml;riger
nichtleerer TIFF-Datei. F&uuml;r jede Datei wird
gepr&uuml;ft, ob der n&auml;chste Sendezeitpunkt
(gespeicherter Startzeitpunkt plus n&auml;chste Minute
aus der Minutenfolge) erreicht ist. Wenn ja: <b><br>
a)</b> Die Seitenzahl der TIFF-Datei wird ermittelt und der
Timeout entsprechend berechnet (pro Seite und
Verbindungsaufbau je eine Minute). <b><br>
b)</b> Das Programm verzweigt per <b>fork()</b> in einen
Kindprozess, der <b>dmain()</b> aufruft. <b>dmain()</b> baut
&uuml;ber das TR-064-Protokoll (SOAP-Anfragen via
<b>libcurl</b>) eine Verbindung zur Fritz!Box auf und
&uuml;bergibt die TIFF-Datei zum Faxversand. <b><br>
c)</b> Der Elternprozess wartet bis zu <b>maxsec</b>
Sekunden auf den Kindprozess. Bei Ablauf des Timeouts wird
der Kindprozess beendet.</p>

<p style="margin-left:9%; margin-top: 1em"><b>9)</b> Je
nach Ergebnis des Sendeversuchs werden die Dateien ins
Gefaxt- oder Nichtgefaxt-Verzeichnis verschoben, oder der
n&auml;chste Eintrag in der Minutenfolge wird
f&uuml;r den n&auml;chsten Sendeversuch
vorgemerkt.</p>

<p style="margin-left:9%; margin-top: 1em"><b>10)</b> Die
Konfigurationsdatei wird ggf. neu geschrieben.</p>

<h2>STEUERDATEIFORMAT
<a name="STEUERDATEIFORMAT_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em">Jede Steuerdatei
<b>dtN.vw</b> enth&auml;lt zeilenweise:</p>

<p style="margin-left:9%; margin-top: 1em"><b>Zeile 1:</b>
Unix-Zeitstempel des Startzeitpunkts (oder des letzten
Versuchs) <b><br>
Zeile 2:</b> verbleibende Minutenfolge, kommagetrennt (z.B.
<b>0,2,3,5,10</b>); der erste Wert gibt die Minuten bis zum
n&auml;chsten Versuch an <b><br>
Zeile 3:</b> Zielfaxnummer <b><br>
Zeile 4:</b> Pfad der Quelldatei <b><br>
Zeile 5:</b> bisherige/gesamte Sendeversuche (z.B.
<b>2/16</b>)</p>

<h2>VORAUSSETZUNGEN
<a name="VORAUSSETZUNGEN_D"></a>
</h2>



<p style="margin-left:9%; margin-top: 1em"><b>Hardware</b>:
Fritz!Box mit aktiver Faxfunktion (Faxeinrichtung in der
Fritz!Box-Oberfl&auml;che notwendig), im selben Netzwerk
erreichbar unter dem konfigurierten Host (Standard:
<b>fritz.box</b>). <b><br>
Software</b>: Linux (Opensuse &gt;= 42.1, Debian &gt;= 9,
Ubuntu &gt;= 16.04, Mint &gt;= 18, Fedora &gt;= 24).
<b>libcurl</b> muss installiert sein. <b>ghostscript</b>
(<b>gs</b>) wird f&uuml;r den PDF-Versand
ben&ouml;tigt. <b>libtiff</b> muss installiert sein.</p>

<h2>AUTOMATISCH INSTALLIERTE PROGRAMMPAKETE
<a name="AUTOMATISCH INSTALLIERTE PROGRAMMPAKETE_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em">(hierzu werden
je nach Distribution <b>zypper</b>, <b>apt(-get)</b>,
<b>dnf</b> oder <b>yum</b> verwendet).</p>


<p style="margin-left:9%; margin-top: 1em"><b>Makefile:</b>
<br>
gcc V.6 oder h&ouml;her, g++ V.6 oder h&ouml;her,
groff, libtiff-dev(el)</p>

<p style="margin-left:9%; margin-top: 1em"><b>fbfax:</b>
<br>
boost, boost-devel, boost-locale, capi4linux, cron,
ghostscript, libcurl, libcurl-devel, libtiff, samba</p>

<h2>AUSWIRKUNGEN DES PROGRAMMABLAUFS
<a name="AUSWIRKUNGEN DES PROGRAMMABLAUFS_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em">Das Programm
muss zum ordentlichen Funktionieren folgende
Ma&szlig;nahmen ergreifen:</p>

<p style="margin-left:9%; margin-top: 1em"><b>1)</b> Sudo
(fehlt anfangs bei Standardinstallation in Debian) wird ggf.
installiert.</p>

<p style="margin-left:9%; margin-top: 1em"><b>2)</b>
&rsquo;GNU make&rsquo; wird, falls nicht vorhanden, durch
Aufruf von &rsquo;sh ./install.sh&rsquo; automatisch
installiert.</p>

<p style="margin-left:9%; margin-top: 1em"><b>3)</b>
Erstellen einer Protokolldatei,
standardm&auml;&szlig;ig
<b>/var/log/fbfaxvorgabe.log</b>.</p>

<p style="margin-left:9%; margin-top: 1em"><b>4)</b>
Erstellen und Zug&auml;nglichmachen der
Spoolverzeichnisse <b>/var/spool/fbfax/waiting</b>,
<b>/var/spool/fbfax/faxed</b> und
<b>/var/spool/fbfax/notfaxed</b>.</p>

<p style="margin-left:9%; margin-top: 1em"><b>5)</b>
Erstellen und Anpassen der Konfigurationsdatei
<b>fbfax.conf</b> im Programmverzeichnis (Standard:
<b>/usr/local/sbin/</b>).</p>

<p style="margin-left:9%; margin-top: 1em"><b>6)</b>
Einf&uuml;gen einer Zeile zum automatischen periodischen
Aufruf des Programms in das crontab von root, sobald das
erste Fax eingereiht wird (Intervall: 1 Minute).</p>

<h2>DEINSTALLATION
<a name="DEINSTALLATION_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em">Wechseln Sie in
einem Terminal in das Installationsverzeichnis (beim selben
eingeloggten Benutzer: <b>cd &#732;/fbfax</b>, ansonsten
wird es &uuml;ber <b>fbfax -info</b> angezeigt). <br>
Rufen Sie dort <b>make uninstall</b> auf. <br>
Dadurch wird das installierte <b>fbfax</b> gel&ouml;scht
und das Script <b>uninstallinv</b> in umgekehrter
Reihenfolge abgearbeitet. <br>
Auf die Deinstallation der Konfigurationsdateien und der
angesammelten Faxdaten wird dabei verzichtet. <br>
Etwaige Fehlermeldungen k&ouml;nnen ignoriert
werden.</p>

<h2>R&Uuml;CKGABEWERTE
<a name="R&Uuml;CKGABEWERTE_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em"><b>0</b>:
Normaler R&uuml;ckgabewert <b><br>
1</b>: Gabelung zu <b>dmain()</b> misslungen <b><br>
7</b>: Der Infobildschirm (<b>fbfax -info</b>) wurde
angezeigt <b><br>
8</b>: Die Hilfe wurde angezeigt <b><br>
98</b>: Programmaufruf abgebrochen, da es bereits einmal
l&auml;uft <br>
Nach Aufruf von <b>fbfax -vi</b> oder <b>fbfax -vs</b> wird
ggf. der R&uuml;ckgabewert von <b>vi</b>/<b>vim</b>
weitergeleitet</p>

<h2>FEHLER
<a name="FEHLER_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em">Fehler bitte mit
u.a. dem Wort &rsquo;fbfax&rsquo; in der
E-Mail-&Uuml;berschrift melden. <br>
Bitte auch melden, wenn sich &Auml;nderungsbedarf durch
andere Hard- bzw. Software ergibt.</p>

<h2>PROGRAMM&Auml;NDERUNG
<a name="PROGRAMM&Auml;NDERUNG_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em">Durch Aufruf von
&rsquo;<b>sh viall</b>&rsquo; mit den &uuml;blichen
&rsquo;<b>vim</b>&rsquo;-Befehlen, gefolgt von
&rsquo;<b>make</b>&rsquo; und &rsquo;<b>make
install</b>&rsquo; vom Installationsverzeichnis
(&rsquo;<b>&#732;/fbfax</b>&rsquo;) aus k&ouml;nnen Sie
das Programm &auml;ndern.</p>

<h2>HAFTUNG
<a name="HAFTUNG_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em">Das Programm
wurde mit bester Absicht entwickelt und durch den Autor
getestet. <br>
Trotzdem kann der Autor f&uuml;r keine Sch&auml;den
haften, die durch das Programm entstehen
k&ouml;nnten.</p>

<h2>AUTOR
<a name="AUTOR_D"></a>
</h2>


<p style="margin-left:9%; margin-top: 1em">Gerald Schade
(geraldschade@gmx.de; www.diabdachau.de)</p>
<hr>
</body>
</html>
