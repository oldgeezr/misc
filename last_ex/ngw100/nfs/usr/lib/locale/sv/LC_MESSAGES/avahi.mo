��    �      �  �   �	      �  �  �  h   �  �   
  i  �  �   e     �       %   !  5   G     }     �     �  !   �     �     �     �                6     W     r  	   �     �  6   �  '   �  '   	  "   1  4   T  *   �  .   �     �  
   �     �               .     @     ]     u     �     �     �     �     �     �               4     I     b     u     }     �     �     �     �     �          *  %   J  &   p  #   �  #   �  #   �  !     (   %  <   N  %   �     �      �     �  #        3     S  #   k  %   �  ?   �  	   �     �  %        9     I     Y     k     �     �     �     �     �     �     �                   4   8     m          �     �     �     �     �     �          %     .     C     L     ]  '   b     �  &   �  	   �     �     �     �     �     �            "   /     R     _     l     u  *   ~  $   �  +   �  #   �  7     %   V  "   |  4   �  (   �  (   �     &      6      I      ]      n            �      �      �   
   �   &   �   '   �   ,   !     E!     Z!     ^!      z!  C  �!  �  �"  r   �%    *&  u  8'  �   �(     S)     c)  #   v)  ?   �)     �)     �)     �)  %   �)     #*     6*     Q*     l*     �*      �*     �*     �*     �*     +  A    +  .   b+  .   �+  #   �+  @   �+  0   %,  5   V,     �,  
   �,  
   �,     �,     �,     �,     �,     �,     -     #-     4-     D-     U-     g-     x-     �-     �-     �-  "   �-     �-  	   �-      .     $.     +.     K.     `.  (   }.  )   �.  5   �.  .   /  0   5/  1   f/  ,   �/  /   �/  )   �/  9   0  K   Y0  /   �0  )   �0  *   �0  0   *1  6   [1  '   �1      �1  0   �1  3   2  O   @2  	   �2     �2     �2     �2     �2     �2     �2     3     "3     13     ?3     N3     `3     v3     �3     �3     �3  9   �3     4     4     #4     74     V4     c4     v4     �4     �4     �4     �4     �4     �4     �4  '   �4     5  0   ;5     l5     z5     �5     �5     �5     �5     �5  !   �5  !   �5     6     6     %6     .6  *   76  %   b6  (   �6  %   �6  9   �6  (   7  *   :7  >   e7  +   �7  *   �7     �7     8     !8     78     L8     _8     r8     v8     �8  
   �8  ,   �8  -   �8  2   9     >9     Y9  !   k9  &   �9                 $                  y   M   C   E                 �           :   ~   6   |   9      �   �      m                      K       W   }   k   ^   �      �   "   X       =   p   -   I   t      �   2   V       F   �   \   �   	   �           #       b   J          /   e   i   �   H   c       1   _         5   g             T   ?                    @   l   {              +   <   �       '   A   
   *   q       [   a               �   .   �   f   L   U       0          n   G   v   �   �   (                 �       w   )           4       o       7       B   !   �          ;   &   Y               �   u       S           �   8      %   s   �   R   d   Q   N       >   j           �   x   ,   z          �       ]      �   O      D      �   Z   r   `   P               �   �   h              3              -h --help            Show this help
    -V --version         Show version
    -D --browse-domains  Browse for browsing domains instead of services
    -a --all             Show all services, regardless of the type
    -d --domain=DOMAIN   The domain to browse in
    -v --verbose         Enable verbose mode
    -t --terminate       Terminate after dumping a more or less complete list
    -c --cache           Terminate after dumping all entries from the cache
    -l --ignore-local    Ignore local services
    -r --resolve         Resolve services found
    -f --no-fail         Don't fail if the daemon is not available
    -p --parsable        Output in parsable format
     -k --no-db-lookup    Don't lookup service types
    -b --dump-db         Dump service type database
 %s [options]

    -h --help            Show this help
    -s --ssh             Browse SSH servers
    -v --vnc             Browse VNC servers
    -S --shell           Browse both SSH and VNC
    -d --domain=DOMAIN   The domain to browse in
 %s [options] %s <host name ...>
%s [options] %s <address ... >

    -h --help            Show this help
    -V --version         Show version
    -n --name            Resolve host name
    -a --address         Resolve address
    -v --verbose         Enable verbose mode
    -6                   Lookup IPv6 address
    -4                   Lookup IPv4 address
 %s [options] <new host name>

    -h --help            Show this help
    -V --version         Show version
    -v --verbose         Enable verbose mode
 : All for now
 : Cache exhausted
 <i>No service currently selected.</i> A NULL terminated list of service types to browse for Access denied Address Address family An unexpected D-Bus error occured Avahi Discovery Avahi SSH Server Browser Avahi VNC Server Browser Avahi Zeroconf Browser Avahi client failure: %s Avahi domain browser failure: %s Avahi resolver failure: %s Bad number of arguments
 Bad state Browse Service Types Browse for Zeroconf services available on your network Browse for Zeroconf-enabled SSH Servers Browse for Zeroconf-enabled VNC Servers Browse service type list is empty! Browsing for service type %s in domain %s failed: %s Browsing for services in domain <b>%s</b>: Browsing for services on <b>local network</b>: Browsing... Canceled.
 Change domain Choose SSH server Choose Shell Server Choose VNC server Client failure, exiting: %s
 Connecting to '%s' ...
 DNS failure: FORMERR DNS failure: NOTAUTH DNS failure: NOTIMP DNS failure: NOTZONE DNS failure: NXDOMAIN DNS failure: NXRRSET DNS failure: REFUSED DNS failure: SERVFAIL DNS failure: YXDOMAIN DNS failure: YXRRSET Daemon connection failed Daemon not running Desktop Disconnected, reconnecting ...
 Domain E Ifce Prot %-*s %-20s Domain
 E Ifce Prot Domain
 Established under name '%s'
 Failed to add address: %s
 Failed to add service: %s
 Failed to add subtype '%s': %s
 Failed to connect to Avahi server: %s Failed to create address resolver: %s
 Failed to create browser for %s: %s Failed to create client object: %s
 Failed to create domain browser: %s Failed to create entry group: %s
 Failed to create host name resolver: %s
 Failed to create resolver for %s of type %s in domain %s: %s Failed to create simple poll object.
 Failed to parse address '%s'
 Failed to parse port number: %s
 Failed to query host name: %s
 Failed to query version string: %s
 Failed to read Avahi domain: %s Failed to register: %s
 Failed to resolve address '%s': %s
 Failed to resolve host name '%s': %s
 Failed to resolve service '%s' of type '%s' in domain '%s': %s
 Host Name Host name conflict
 Host name successfully changed to %s
 Initializing... Invalid DNS TTL Invalid DNS class Invalid DNS return code Invalid DNS type Invalid Error Code Invalid RDATA Invalid address Invalid argument Invalid configuration Invalid domain name Invalid flags Invalid host name Invalid interface index Invalid number of arguments, expecting exactly one.
 Invalid operation Invalid packet Invalid port number Invalid protocol specification Invalid record Invalid record key Invalid service name Invalid service subtype Invalid service type Is empty Local name collision Location Memory exhausted Name Name collision, picking new name '%s'.
 No command specified.
 No suitable network protocol available Not found Not permitted Not supported OK OS Error Operation failed Port Resource record key is pattern Server version: %s; Host name: %s
 Service Name Service Type TXT Data Terminal The IP port number of the resolved service The TXT data of the resolved service The address family for host name resolution The address of the resolved service The domain to browse in, or NULL for the default domain The host name of the resolved service The object passed in was not valid The requested operation is invalid because redundant The service name of the selected service The service type of the selected service Timeout reached Too few arguments
 Too many arguments
 Too many clients Too many entries Too many objects Type Version mismatch Waiting for daemon ...
 _Domain... avahi_domain_browser_new() failed: %s
 avahi_service_browser_new() failed: %s
 avahi_service_type_browser_new() failed: %s
 execlp() failed: %s
 n/a service_browser failed: %s
 service_type_browser failed: %s
 Project-Id-Version: avahi
Report-Msgid-Bugs-To: 
POT-Creation-Date: 2010-07-13 03:02+0200
PO-Revision-Date: 2009-07-28 00:28+0100
Last-Translator: Daniel Nylander <po@danielnylander.se>
Language-Team: Swedish <tp-sv@listor.tp-sv.se>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
     -h --help            Visa denna hjälp
    -V --version         Visa version
    -D --browse-domains  Bläddra efter bläddringsdomäner istället för tjänster
    -a --all             Visa alla tjänster, oavsett typen
    -d --domain=DOMÄN    Domänen att bläddra i
    -v --verbose         Aktivera informativt läge
    -t --terminate       Avsluta efter dumpning av en mer eller mindre komplett lista
    -c --cache           Avsluta efter dumpning av alla poster från cachen
    -l --ignore-local    Ignorera lokala tjänster
    -r --resolve         Slå upp tjänster som hittats
    -f --no-fail         Misslycka inte om demonen inte är tillgänglig
    -p --parsable        Skriv ut i tolkningsbart format
     -k --no-db-lookup    Slå inte upp tjänstetyper
    -b --dump-db         Dumpa databasen över tjänstetyper
 %s [flaggor]

    -h --help            Visa denna hjälp
    -s --ssh             Bläddra bland SSH-servrar
    -v --vnc             Bläddra bland VNC-servrar
    -S --shell           Bläddra bland både SSH och VNC
    -d --domain=DOMÄN    Domänen att bläddra i
 %s [flaggor] %s <värdnamn ...>
%s [flaggor] %s <adress ... >

    -h --help            Visa denna hjälp
    -V --version         Visa version
    -n --name            Slå upp värdnamn
    -a --address         Slå upp adress
    -v --verbose         Aktivera informativt läge
    -6                   Slå upp IPv6-adress
    -4                   Slå upp IPv4-adress
 %s [flaggor] <nytt värdnamn>

    -h --help            Visa denna hjälp
    -V --version         Visa version
    -v --verbose         Aktivera informativt läge
 : Alla just nu
 : Cachen är full
 <i>Ingen tjänst har markerats.</i> En NULL-terminerad lista över tjänstetyper att bläddra efter Åtkomst nekad Adress Adressfamilj Ett oväntat D-Bus-fel har inträffat Avahi-upptäckning Avahi SSH-serverbläddrare Avahi VNC-serverbläddrare Avahi Zeroconf-bläddrare Fel i Avahi-klient: %s Fel i Avahi-domänbläddrare: %s Fel i Avahi-uppslag: %s Dåligt antal argument
 Felaktigt tillstånd Bläddra efter tjänstetyper Bläddra efter Zeroconf-tjänster tillgängliga på ditt nätverk Bläddra efter Zeroconf-aktiverade SSH-servrar Bläddra efter Zeroconf-aktiverade VNC-servrar Listan över tjänstetyper är tom! Bläddring efter tjänstetypen %s i domänen %s misslyckades: %s Bläddring efter tjänster i domänen <b>%s</b>: Bläddrar efter tjänster på <b>lokalt nätverk</b>: Bläddrar... Avbruten.
 Byt domän Välj SSH-server Välj skalserver Välj VNC-server Klientfel, avslutar: %s
 Ansluter till "%s"...
 DNS-fel: FORMERR DNS-fel: NOTAUTH DNS-fel: NOTIMP DNS-fel: NOTZONE DNS-fel: NXDOMAIN DNS-fel: NXRRSET DNS-fel: REFUSED DNS-fel: SERVFAIL DNS-fel: YXDOMAIN DNS-fel: YXRRSET Anslutning till demon misslyckades Demonen är inte igång Skrivbord Frånkopplad, återansluter ...
 Domän H Grän Prot %-*s %-20s Domän
 H Grän Prot Domän
 Etablerad under namnet "%s"
 Misslyckades att lägga till adress: %s
 Misslyckades att lägga till tjänst: %s
 Misslyckades med att lägga till undertypen "%s": %s
 Misslyckades att ansluta till Avahi-server: %s Misslyckades med att skapa adressuppslagare: %s
 Misslyckades med att skapa bläddrare för %s: %s Misslyckades med att skapa klientobjekt: %s
 Misslyckades med att skapa domänbläddrare: %s Misslyckades med att skapa postgrupp: %s
 Misslyckades med att skapa uppslagare för värdnamn: %s
 Misslyckades med att skapa uppslagare för %s av typen %s i domänen %s: %s Misslyckades med att skapa enkelt poll-objekt.
 Misslyckades med att tolka adressen "%s"
 Misslyckades med att tolka portnummer: %s
 Misslyckades med att fråga efter värdnamn: %s
 Misslyckades med att fråga efter versionssträng: %s
 Misslyckades att läsa Avahi-domän: %s Misslyckades att registrera: %s
 Misslyckades med att slå upp adressen "%s": %s
 Misslyckades med att slå upp värdnamnet "%s": %s
 Misslyckades med att slå upp tjänsten "%s" av typen "%s" i domänen "%s": %s
 Värdnamn Värdnamnskonflikt
 Värdnamnet ändrades till %s
 Initierar... Ogiltigt DNS TTL Ogiltig DNS-klass Ogiltig DNS-svarskod Ogiltig DNS-typ Ogiltig felkod Ogiltig RDATA Ogiltig adress Ogiltigt argument Ogiltig konfiguration Ogiltigt domännamn Ogiltiga flaggor Ogiltigt värdnamn Ogiltigt gränssnittsindex Ogiltigt antal argument, exakt ett argument förväntas.
 Ogiltig åtgärd Ogiltigt paket Ogiltigt portnummer Ogiltig protokollspecifikation Ogiltig post Ogiltig postnyckel Ogiltigt tjänstenamn Ogiltig undertyp för tjänst Ogiltig tjänstetyp Är tom Lokal namnkollision Plats Minnet är slut Namn Namnkollision, väljer nytt namn "%s".
 Inget kommando specificerat.
 Inget lämpligt nätverksprotokoll tillgängligt Hittades inte Inte tillåten Stöds inte OK Operativsystemsfel Åtgärden misslyckades Port Resursens postnyckel är mönster Serverversion: %s; Värdnamn: %s
 Tjänstenamn Tjänstetyp TXT Data Terminal IP-portnumret för den uppslagna tjänsten TXT-data för den uppslagna tjänsten Adressfamiljen för värdnamnets uppslag Adressen för den uppslagna tjänsten Domänen att bläddra i, eller NULL för standarddomänen Värdnamnet för den uppslagna tjänsten Objektet som skickades in var inte giltigt Den begärda åtgärden är ogiltig därför den är redundant Tjänstenamnet för den markerade tjänsten Tjänstetypen för den markerade tjänsten Tidsgräns nåddes För få argument
 För många argument
 För många klienter För många poster För många objekt Typ Versionen stämmer inte Väntar på demon ...
 _Domän... avahi_domain_browser_new() misslyckades: %s
 avahi_service_browser_new() misslyckades: %s
 avahi_service_type_browser_new() misslyckades: %s
 execlp() misslyckades: %s
 Inte tillgänglig service_browser misslyckades: %s
 service_type_browser misslyckades: %s
 