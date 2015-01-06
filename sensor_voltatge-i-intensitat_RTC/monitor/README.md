serial.lua
--

Llegeix el port serie on està l'ardunio connectat i emmagatzema les dades en un fitxer temporal a /tmp/serial.log

#falta perque s'inici amb la maquina l'afegirem al rc.local

/usr/bin/lua /www/serial.lua

# falta copiar-lo a la carpeta /www/
# falta modificar potser l'adreça on llegir el serial, especificar pins 28 i 29 per Tx i Rx





aigua.lua
--

Llegeix les dades de /tmp/serial.log i les serveix en format JSON i compatible amb crides HTTP
També emmagatzema les dades en format JSON en el directori /root/db per poder accedir a l'històric

# falta copiar la carpeta cgi-bin a /www/
# falta editar el cron

# s'ha de modificar pel contador_energetic
